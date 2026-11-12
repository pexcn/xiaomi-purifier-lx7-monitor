#!/usr/bin/env python3
"""Download OTA candidates using an existing mit Mijia login; never flash devices.

Standard library only. Queries all configured endpoints before selecting a
version; API results do not establish a globally latest or hardware-safe image.
Authentication crypto retains the repository's original Mijia transport.
"""
import argparse
import base64
import gzip
import hashlib
import json
import os
import re
import secrets
import sys
import tempfile
import time
import urllib.error
import urllib.parse
import urllib.request
from dataclasses import dataclass, field
from pathlib import Path

API = 'https://api.mijia.tech/app'
MODEL = 'yunmi.waterpuri.lx7'
MAX_RESPONSE = 4 * 1024 * 1024
URL_KEYS = {'url', 'downloadurl', 'firmwareurl', 'fileurl', 'fwurl',
            'mcuurl', 'appurl', 'wifiurl'}
VERSION_KEYS = ('latestversion', 'version', 'fwversion', 'fwver')
ROLES = {'app': 'wifi', 'wifi': 'wifi', 'mcu': 'mcu'}


class OTAError(ValueError):
    """A static, credential-free diagnostic safe to show or save."""


def normalized(key):
    return str(key).replace('_', '').replace('-', '').lower()


def numeric_version(value):
    if not isinstance(value, (str, int)) or isinstance(value, bool):
        return None
    value = str(value)
    if len(value) > 48 or not re.fullmatch(r'[0-9]+(?:\.[0-9]+)*', value):
        return None
    return tuple(int(part) for part in value.split('.'))


def compare_versions(left, right):
    a, b = numeric_version(left), numeric_version(right)
    if a is None or b is None or (len(a) == 1) != (len(b) == 1):
        return None
    length = max(len(a), len(b))
    a, b = a + (0,) * (length - len(a)), b + (0,) * (length - len(b))
    return (a > b) - (a < b)


def valid_url(value):
    if not isinstance(value, str):
        return False
    try:
        parts = urllib.parse.urlsplit(value)
        return parts.scheme == 'https' and bool(parts.hostname) and not parts.username and not parts.password
    except ValueError:
        return False


class AuthNoRedirect(urllib.request.HTTPRedirectHandler):
    def redirect_request(self, req, fp, code, msg, headers, newurl):
        return None  # Never forward Mijia cookies to a redirect destination.


class HTTPSRedirect(urllib.request.HTTPRedirectHandler):
    def redirect_request(self, req, fp, code, msg, headers, newurl):
        if not valid_url(newurl):
            raise OTAError('拒绝非 HTTPS 或带用户名密码的下载重定向')
        return super().redirect_request(req, fp, code, msg, headers, newurl)


def request_mijia(uri, auth, payload):
    body, signed_key = encrypt_form(uri, auth, payload)
    identity = auth.get('userId') or auth.get('cUserId')
    cookie = ('userId={};cUserId={};yetAnotherServiceToken={};serviceToken={};'
              'locale=zh_CN;timezone=GMT+08:00;is_daylight=0;dst_offset=0;'
              'channel=MI_APP_STORE;PassportDeviceId={};').format(
                  identity, auth.get('cUserId', ''), auth['serviceToken'],
                  auth['serviceToken'], auth['deviceId'])
    request = urllib.request.Request(API + uri, data=body, method='POST', headers={
        'User-Agent': auth['ua'], 'Content-Type': 'application/x-www-form-urlencoded',
        'Accept-Encoding': 'identity', 'miot-accept-encoding': 'GZIP',
        'miot-encrypt-algorithm': 'ENCRYPT-RC4', 'x-xiaomi-protocal-flag-cli': 'PROTOCAL-HTTP2',
        'Cookie': cookie,
    })
    with urllib.request.build_opener(AuthNoRedirect()).open(request, timeout=25) as response:
        data = response.read(MAX_RESPONSE + 1)
    if len(data) > MAX_RESPONSE:
        raise OTAError('OTA 响应过大')
    try:
        return json.loads(data.decode('utf-8'))
    except (UnicodeDecodeError, ValueError):
        raw = rc4_drop1024(signed_key, base64.b64decode(data.strip(), validate=True))
        if raw.startswith(b'\x1f\x8b'):
            import io
            with gzip.GzipFile(fileobj=io.BytesIO(raw)) as zipped:
                raw = zipped.read(MAX_RESPONSE + 1)
        if len(raw) > MAX_RESPONSE:
            raise OTAError('解压后的 OTA 响应过大')
        return json.loads(raw.decode('utf-8'))


@dataclass
class Candidate:
    url: str = field(repr=False)
    component: str
    version: str | None
    endpoint: str
    location: str
    scope: str
    md5: str | None = None
    sha256: str | None = None
    issue: str | None = None
    selected: bool = False
    reason: str = ''
    artifact: dict | None = None

    @property
    def identifier(self):
        parts = urllib.parse.urlsplit(self.url)
        # A provided digest identifies content despite rotating signed URLs.
        # Without it, query parameters can select different files: hash, never omit them.
        key = [parts.hostname, parts.path, self.component, self.version, self.md5, self.sha256]
        if not (self.md5 or self.sha256):
            key.append(hashlib.sha256(parts.query.encode()).hexdigest())
        return hashlib.sha256(json.dumps(key).encode()).hexdigest()[:12]

    def public(self):
        return dict(id=self.identifier, component=self.component, version=self.version,
                    endpoint=self.endpoint, location=self.location, scope=self.scope,
                    host=urllib.parse.urlsplit(self.url).hostname, md5=self.md5,
                    sha256=self.sha256, issue=self.issue, selected=self.selected,
                    reason=self.reason, artifact=self.artifact)


def collect_candidates(response, endpoint, model, did):
    """Extract all candidates; never carry another device's metadata into a hit."""
    found = []

    def walk(node, inherited, location='root', depth=0):
        if depth > 40:
            return
        if isinstance(node, list):
            for i, child in enumerate(node):
                walk(child, inherited, f'{location}[{i}]', depth + 1)
            return
        if not isinstance(node, dict):
            return
        values = {normalized(k): v for k, v in node.items()}
        context = dict(inherited)
        if 'model' in values and str(values['model']) != model:
            return
        if 'did' in values:
            if str(values['did']) != str(did):
                return
            context['matched_did'] = True
        role = context.get('role', 'package')
        for key in ('component', 'type'):
            if isinstance(values.get(key), str):
                role = ROLES.get(values[key].lower(), role)
        context['role'] = role
        local_generic = False
        for key in VERSION_KEYS:
            if key in values:
                value = values[key]
                context['generic_version'] = (str(value) if numeric_version(value) else None, role)
                local_generic = True
                break
        for component, prefixes in [('wifi', ('app', 'wifi')), ('mcu', ('mcu',))]:
            for prefix in prefixes:
                for suffix in ('latestversion', 'version', 'fwversion', 'fwver', 'ver'):
                    key = prefix + suffix
                    if key in values:
                        value = values[key]
                        context[component + '_version'] = str(value) if numeric_version(value) else None
        urls = [(key, value) for key, value in values.items() if key in URL_KEYS and valid_url(value)]
        for key, url in urls:
            component = 'mcu' if key == 'mcuurl' else 'wifi' if key in ('appurl', 'wifiurl') else role
            version = context.get(component + '_version')
            if version is None:
                general, owner = context.get('generic_version', (None, 'package'))
                # A release/app version on a shared app_url+mcu_url node is not the MCU version.
                if component != 'mcu' or owner == 'mcu' or (len(urls) == 1 and local_generic):
                    version = general
            checksums = {}
            issue = None
            prefixes = ('mcu',) if component == 'mcu' else ('app', 'wifi') if component == 'wifi' else ()
            for algorithm, aliases, length in [('md5', ('md5', 'filemd5', 'firmwaremd5'), 32),
                                                ('sha256', ('sha256', 'sha256sum', 'filesha256'), 64)]:
                names = tuple(p + algorithm for p in prefixes)
                if len(urls) == 1:
                    names += aliases
                value = next((values[name] for name in names if name in values), None)
                if value is not None:
                    if isinstance(value, str) and re.fullmatch('[0-9a-fA-F]{' + str(length) + '}', value):
                        checksums[algorithm] = value.lower()
                    else:
                        issue = 'invalid_' + algorithm
            generic_checksum = values.get('checksum') if len(urls) == 1 else None
            if isinstance(generic_checksum, str):
                for algorithm, length in [('md5', 32), ('sha256', 64)]:
                    if re.fullmatch('[0-9a-fA-F]{' + str(length) + '}', generic_checksum):
                        checksums.setdefault(algorithm, generic_checksum.lower())
            scope = 'matched-did' if context.get('matched_did') else 'device-query' if endpoint != '/home/latest_version' else 'model-query'
            found.append(Candidate(url, component, version, endpoint, location, scope,
                                   checksums.get('md5'), checksums.get('sha256'), issue))
        # Ordinal locations deliberately omit arbitrary response keys (which may contain DIDs).
        for i, (key, child) in enumerate(node.items()):
            child_context = dict(context)
            key_text = str(key)
            if key_text.isdecimal() and len(key_text) >= 8:
                if key_text != str(did):
                    continue
                child_context['matched_did'] = True
            child_context['role'] = ROLES.get(normalized(key), role)
            walk(child, child_context, f'{location}.field{i}', depth + 1)

    walk(response, {})
    return found


def choose_candidates(candidates, current_version=None, current_mcu=None,
                      component='all', requested=()):
    for candidate in candidates:
        candidate.selected = False
        candidate.reason = ''
    selected = []
    requested = set(requested)
    unknown = requested - {c.identifier for c in candidates}
    if unknown:
        raise OTAError('指定的候选 ID 不存在；链接可能变化，请重新 --info-only 查看')
    for group in ('wifi', 'mcu'):
        if component not in ('all', group):
            continue
        baseline = current_version if group == 'wifi' else current_mcu
        pool = []
        for candidate in candidates:
            if ('mcu' if candidate.component == 'mcu' else 'wifi') != group:
                continue
            if candidate.issue:
                candidate.reason = '校验字段格式错误，排除'
                continue
            if requested and candidate.identifier not in requested:
                candidate.reason = '未指定此候选'
                continue
            version = candidate.version
            relation = compare_versions(version, baseline) if baseline else None
            if baseline and relation is not None and relation < 0:
                candidate.reason = '低于当前版本，排除'
                continue
            ambiguous_package = candidate.component == 'package' and version and len(numeric_version(version)) > 3
            if not requested and (not version or (baseline and relation is None) or ambiguous_package):
                candidate.reason = '版本未知/格式不可比较/可能为复合包；需显式 --candidate ID'
                continue
            pool.append(candidate)
        if requested:
            winners = pool
        elif pool:
            tiers = {'matched-did': 0, 'device-query': 1, 'model-query': 2}
            best_tier = min(tiers[c.scope] for c in pool)
            tier_pool = [c for c in pool if tiers[c.scope] == best_tier]
            families = {'.' in c.version for c in tier_pool}
            if len(families) > 1:
                for c in tier_pool:
                    c.reason = '版本格式混杂，无法排序；需 --candidate ID'
                continue
            winner = max(tier_pool, key=lambda c: numeric_version(c.version))
            # Equal versions with different download identities are not interchangeable.
            tied = {c.identifier for c in tier_pool if compare_versions(c.version, winner.version) == 0}
            if len(tied) > 1:
                for c in tier_pool:
                    c.reason = '最高版本存在多个不同文件；需 --candidate ID'
                continue
            winners = [winner]
        else:
            winners = []
        for c in winners:
            if c.identifier in {x.identifier for x in selected}:
                continue
            c.selected = True
            c.reason = '显式指定（未证明最新版）' if requested else '该组件可比较候选中优先设备定向、再取最高版本'
            selected.append(c)
        for c in pool:
            if not c.selected and not c.reason:
                c.reason = '其他候选，未选择'
    return selected


def query_all(auth, did, model, pid=None, delay=1.0, request=request_mijia):
    queries = [('/home/multi_checkversion', {'dids': [str(did)]})]
    if pid is not None:
        queries.append(('/home/checkversion', {'did': str(did), 'pid': pid}))
    queries.append(('/home/latest_version', {'model': model}))
    candidates, outcomes = [], []
    throttled = False
    for index, (endpoint, payload) in enumerate(queries):
        if index:
            time.sleep(delay)
        print('查询 ' + endpoint + ' ...')
        try:
            response = request(endpoint, auth, payload)
        except urllib.error.HTTPError as error:
            outcomes.append(dict(endpoint=endpoint, status='http-error', code=error.code))
            if error.code == 429:
                throttled = True
                break
            continue
        except (urllib.error.URLError, OSError, ValueError):
            outcomes.append(dict(endpoint=endpoint, status='request-or-decode-error'))
            continue
        if not isinstance(response, dict):
            outcomes.append(dict(endpoint=endpoint, status='invalid-response'))
            continue
        code = response.get('code', 0)
        if str(code) == '-127':
            result = response.get('result')
            wait = result.get('wait_second') if isinstance(result, dict) else None
            outcomes.append(dict(endpoint=endpoint, status='rate-limited',
                                 wait_seconds=wait if isinstance(wait, (int, float)) else None))
            throttled = True
            break
        if str(code) not in ('0', 'None'):
            outcomes.append(dict(endpoint=endpoint, status='business-error',
                                 code=int(code) if str(code).lstrip('-').isdigit() else None))
            continue
        hits = collect_candidates(response, endpoint, model, did)
        outcomes.append(dict(endpoint=endpoint, status='ok', candidate_count=len(hits)))
        candidates.extend(hits)
    return candidates, outcomes, throttled


def download_candidate(candidate, directory, model, max_bytes, current_version=None,
                       opener=None):
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    opener = opener or urllib.request.build_opener(HTTPSRedirect())
    suffix = Path(urllib.parse.urlsplit(candidate.url).path).suffix.lower()
    suffix = suffix if suffix in ('.bin', '.zip', '.img', '.gz', '.ota') else '.bin'
    label = candidate.version or 'unknown'
    filename = f'{model}-{candidate.component}-{label}-{candidate.identifier}{suffix}'
    target = directory / filename
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(prefix='.ota-', suffix='.part', dir=directory, delete=False) as output:
            temporary = Path(output.name)
            request = urllib.request.Request(candidate.url, headers={'User-Agent': 'Mozilla/5.0'})
            with opener.open(request, timeout=60) as response:
                if not valid_url(response.geturl()):
                    raise OTAError('拒绝非 HTTPS 下载')
                length = response.headers.get('Content-Length')
                if length and (not length.isdecimal() or int(length) > max_bytes):
                    raise OTAError('下载长度无效或超过 --max-mib')
                md5, sha256, size = hashlib.md5(), hashlib.sha256(), 0
                first = b''
                while chunk := response.read(1024 * 1024):
                    size += len(chunk)
                    if size > max_bytes:
                        raise OTAError('文件超过 --max-mib')
                    if not first:
                        first = chunk[:128].lstrip().lower()
                    output.write(chunk)
                    md5.update(chunk)
                    sha256.update(chunk)
                if length and size != int(length):
                    raise OTAError('下载被截断')
        if not size or first.startswith((b'<html', b'<!doctype', b'{', b'[')):
            raise OTAError('空文件或收到网页/JSON，拒绝作为固件保存')
        if candidate.md5 and candidate.md5 != md5.hexdigest():
            raise OTAError('MD5 不匹配')
        if candidate.sha256 and candidate.sha256 != sha256.hexdigest():
            raise OTAError('SHA-256 不匹配')
        known_old = sha256.hexdigest() == 'f20d634664918a9e5ab483774c1fd3b80afae2bfd6a5416619a56aaa1093a1c5'
        if known_old and (candidate.version not in (None, '1.3.9') or
                          (current_version and compare_versions('1.3.9', current_version) == -1)):
            raise OTAError('下载内容是已分析的旧 1.3.9 镜像，与目标版本不符')
        try:
            os.link(temporary, target)  # Exclusive publication; never overwrite an existing file.
        except FileExistsError:
            if target.is_symlink() or not target.is_file() or target.stat().st_size != size:
                raise OTAError('目标文件已存在且不匹配；不覆盖') from None
            existing = hashlib.sha256()
            with target.open('rb') as saved:
                while chunk := saved.read(1024 * 1024):
                    existing.update(chunk)
            if existing.hexdigest() != sha256.hexdigest():
                raise OTAError('目标文件已存在且内容不同；不覆盖')
        return dict(file=filename, bytes=size, md5=md5.hexdigest(), sha256=sha256.hexdigest(),
                    expected_checksum_verified=bool(candidate.md5 or candidate.sha256),
                    internal_version='1.3.9' if known_old else 'unverified')
    finally:
        if temporary:
            temporary.unlink(missing_ok=True)


def save_manifest(path, candidates, outcomes, args, throttled):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    record = dict(model=args.model, current_version=args.current_version,
                  current_mcu_version=args.current_mcu_version, rate_limited=throttled,
                  queries=outcomes, candidates=[c.public() for c in candidates],
                  limitation='仅代表此次接口提供的候选，不保证全球最新；硬件适用性及未知内部版本未验证')
    with tempfile.NamedTemporaryFile(mode='w', encoding='utf-8', prefix='.manifest-',
                                     dir=path.parent, delete=False) as output:
        temp = Path(output.name)
        try:
            json.dump(record, output, ensure_ascii=False, indent=2)
            output.write('\n')
        except BaseException:
            temp.unlink(missing_ok=True)
            raise
    try:
        os.replace(temp, path)
    finally:
        temp.unlink(missing_ok=True)


def version_argument(value):
    if numeric_version(value) is None:
        raise argparse.ArgumentTypeError('版本必须是数字或点分数字，例如 2.1.3 或 0012')
    return value


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--did', required=True, help='目标设备 DID；只用于云端查询')
    parser.add_argument('--model', default=MODEL)
    parser.add_argument('--uid', help='多个 mit 账号时指定 UID')
    parser.add_argument('--pid', type=int, help='已知的 pid/connect_type；不猜测')
    parser.add_argument('--current-version', type=version_argument, help='当前 fw_ver，例如 2.1.3')
    parser.add_argument('--current-mcu-version', type=version_argument, help='当前 mcu_fw_ver，例如 0012')
    parser.add_argument('--component', choices=('all', 'wifi', 'mcu'), default='all')
    parser.add_argument('--candidate', action='append', default=[], metavar='ID', help='显式选择候选，可重复；仍禁止已知降级和无效校验字段')
    parser.add_argument('--info-only', action='store_true', help='查询所有接口、保存脱敏清单，不下载')
    parser.add_argument('--out', type=Path, default=Path('firmware/downloads'))
    parser.add_argument('--manifest', type=Path, help='默认 <out>/ota-candidates.json；不含下载 URL 或凭据')
    parser.add_argument('--query-delay', type=float, default=1.0, help='接口之间等待秒数，默认 1')
    parser.add_argument('--max-mib', type=int, default=64, help='单文件最大 MiB，默认 64')
    args = parser.parse_args(argv)
    if not re.fullmatch(r'[A-Za-z0-9._-]+', args.model) or len(args.model) > 100:
        parser.error('model 必须是长度不超过 100 的字母、数字、点、下划线或短横线')
    if not 0 <= args.query_delay <= 30 or not 1 <= args.max_mib <= 512:
        parser.error('query-delay 范围 0–30；max-mib 范围 1–512')
    if not args.current_version:
        print('未提供 --current-version：无法排除低于实机版本的应用包。')
    if not args.current_mcu_version:
        print('未提供 --current-mcu-version：无法排除低于实机版本的 MCU 包。')
    manifest = args.manifest or args.out / 'ota-candidates.json'
    try:
        try:
            path, accounts = open_mit_store()
            _, auth = select_auth(accounts, args.did, args.uid, path.parent)
        except RuntimeError as error:
            # These helpers emit only authored cache/login/UID-selection instructions.
            raise OTAError(str(error)) from None
        print('已读取 mit 米家缓存；不输出凭据，不连接设备或执行 OTA。')
        candidates, outcomes, throttled = query_all(auth, args.did, args.model, args.pid, args.query_delay)
        save_manifest(manifest, candidates, outcomes, args, throttled)
        selected = [] if throttled else choose_candidates(candidates, args.current_version,
                                                           args.current_mcu_version, args.component,
                                                           args.candidate)
        save_manifest(manifest, candidates, outcomes, args, throttled)
        for c in candidates:
            print(f'{c.identifier} {c.component} {c.version or "未知版本"} [{c.scope}] {c.reason or "未选择"}')
        for outcome in outcomes:
            if outcome['status'] != 'ok':
                print(f'接口 {outcome["endpoint"]}: {outcome["status"]}；候选覆盖不完整。')
        print('脱敏候选清单已保存；结果仅代表此次接口可见候选，不保证全球最新。')
        if throttled:
            print('云端限流，停止后续查询和下载；请稍后再试，不自动重试。')
            return 3
        if args.info_only:
            return 0 if candidates else 1
        if not selected:
            print('没有可自动选择的候选；检查清单，不将旧版或未知组件当作最新版下载。')
            return 1
        failed = False
        for candidate in selected:
            try:
                candidate.artifact = download_candidate(candidate, args.out, args.model,
                                                         args.max_mib * 1024 * 1024, args.current_version)
                print('已保存 ' + candidate.artifact['file'])
                if not candidate.artifact['expected_checksum_verified']:
                    print('  云端未提供对应校验值；只计算了本地哈希，未验证官方校验值。')
            except (OSError, ValueError, urllib.error.URLError) as error:
                failed = True
                # Exception text can contain signed URLs. Store/report only its type.
                candidate.reason = '下载或校验失败：' + (str(error) if isinstance(error, OTAError) else type(error).__name__)
                print(candidate.identifier + ' ' + candidate.reason)
            save_manifest(manifest, candidates, outcomes, args, throttled)
        return 2 if failed else 0
    except (OSError, ValueError, RuntimeError, urllib.error.URLError, KeyError) as error:
        detail = str(error) if isinstance(error, OTAError) else type(error).__name__
        print('查询未完成：' + detail + '；请检查 mit 米家登录缓存、参数及网络。', file=sys.stderr)
        return 2


# Mijia authentication and mit cache helpers.

def b64(x):
    return base64.b64encode(x).decode('ascii')


def nonce():
    # Exact mit strategy: 8 secure random bytes + minimal big-endian minute counter.
    minute = int(time.time() // 60)
    byte_len = max(1, (minute.bit_length() + 7) // 8)
    return b64(secrets.token_bytes(8) + minute.to_bytes(byte_len, 'big'))


def rc4_drop1024(key, content):
    # Matches ttys026/mit's rc4_crypt. Not for generic new cryptographic designs.
    if not key:
        raise ValueError('Empty RC4 key')
    s = list(range(256))
    j = 0
    for i in range(256):
        j = (j + s[i] + key[i % len(key)]) & 255
        s[i], s[j] = s[j], s[i]
    i = j = 0
    for _ in range(1024):
        i = (i + 1) & 255
        j = (j + s[i]) & 255
        s[i], s[j] = s[j], s[i]
        _ = s[(s[i] + s[j]) & 255]
    out = bytearray(len(content))
    for pos, byte in enumerate(content):
        i = (i + 1) & 255
        j = (j + s[i]) & 255
        s[i], s[j] = s[j], s[i]
        out[pos] = byte ^ s[(s[i] + s[j]) & 255]
    return bytes(out)


def signature(uri, key, params):
    items = ['POST', uri] + [f'{k}={v}' for k, v in params] + [key]
    return b64(hashlib.sha1('&'.join(items).encode()).digest())


def encrypt_form(uri, auth, payload):
    n = nonce()
    secret = base64.b64decode(auth['ssecurity'], validate=True)
    signed = hashlib.sha256(secret + base64.b64decode(n)).digest()
    skey = b64(signed)
    data = json.dumps(payload, ensure_ascii=False, separators=(',', ':'))
    plain = [('data', data)]
    plain.append(('rc4_hash__', signature(uri, skey, plain)))
    encrypted = [(k, b64(rc4_drop1024(signed, v.encode('utf-8')))) for k, v in plain]
    encrypted.extend([('signature', signature(uri, skey, encrypted)),
                      ('ssecurity', auth['ssecurity']), ('_nonce', n)])
    return urllib.parse.urlencode(encrypted).encode('ascii'), signed


def open_mit_store():
    root = next((os.environ[x] for x in ('MIT_PROFILE_DIR','MIT_HOME','XMCLI_HOME')
                 if os.environ.get(x)), str(Path.home()))
    path = Path(root).expanduser() / '.mit' / 'auth.json'
    if not path.is_file():
        raise RuntimeError(f'找不到 {path}；请确认 mit 使用同一用户及 MIT_HOME 配置')
    state = json.loads(path.read_text(encoding='utf-8'))
    accounts = state.get('accounts', [])
    if not isinstance(accounts, list):
        raise RuntimeError('mit 认证缓存格式异常：accounts 不是数组')
    return path, accounts


def has_did(node, did):
    if isinstance(node, dict):
        if str(node.get('did', '')) == str(did):
            return True
        return any(has_did(v, did) for v in node.values() if isinstance(v, (list, dict)))
    if isinstance(node, list):
        return any(has_did(v, did) for v in node)
    return False


def select_auth(accounts, did, uid, auth_dir):
    candidates = []
    for acc in accounts:
        if not isinstance(acc, dict):
            continue
        account_uid = str(acc.get('user', {}).get('uid') or '')
        if uid and uid != account_uid:
            continue
        m = acc.get('mijia')
        if not isinstance(m, dict):
            continue
        if not all(m.get(k) for k in ('serviceToken','ssecurity','ua','deviceId')):
            continue
        identity = m.get('userId') or m.get('cUserId')
        if not identity:
            continue
        devices_file = auth_dir / 'accounts' / account_uid / 'devices.json'
        match = False
        if devices_file.is_file():
            try:
                match = has_did(json.loads(devices_file.read_text()), did)
            except (OSError, ValueError):
                pass
        candidates.append((int(match), account_uid, m))
    if not candidates:
        raise RuntimeError('mit 没有可用的米家 ssecurity/serviceToken；如只登录了 Xiaomi OAuth 或只有设备 Token，请运行 mit auth login mijia')
    candidates.sort(key=lambda item: -item[0])
    if len(candidates) > 1 and candidates[0][0] == candidates[1][0]:
        raise RuntimeError('检测到多个米家账号，无法确定设备所属账号，请加 --uid 指定账号（可运行 mit auth list 查看）')
    return candidates[0][1], candidates[0][2]


if __name__ == "__main__":
    sys.exit(main())
