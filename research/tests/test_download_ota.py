"""Offline tests: no account files, real firmware writes, devices, or network."""
import contextlib
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location('download_ota', Path(__file__).parents[1] / 'firmware/download_ota.py')
ota = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = ota
spec.loader.exec_module(ota)

MODEL, DID = 'yunmi.waterpuri.lx7', '123456789'
DEVICE, GENERAL = '/home/multi_checkversion', '/home/latest_version'


def collect(node, endpoint=DEVICE):
    return ota.collect_candidates(node, endpoint, MODEL, DID)


class Response(io.BytesIO):
    def __init__(self, body, length=None):
        super().__init__(body)
        self.headers = {'Content-Length': str(len(body) if length is None else length)}

    def geturl(self):
        return 'https://example.invalid/firmware.bin?signature=private-test-value'


class Opener:
    def __init__(self, body, length=None):
        self.body, self.length = body, length

    def open(self, request, timeout):
        return Response(self.body, self.length)


class SelectionTests(unittest.TestCase):
    def test_queries_continue_after_first_hit_and_select_current(self):
        called = []

        def request(endpoint, auth, payload):
            called.append(endpoint)
            return {'code': 0, 'result': {'version': '1.3.9' if endpoint == GENERAL else '2.1.3',
                                         'url': 'https://example.invalid/' + endpoint.rsplit('/', 1)[-1]}}

        candidates, results, limited = ota.query_all({}, DID, MODEL, delay=0, request=request)
        self.assertEqual(called, [DEVICE, GENERAL])
        self.assertFalse(limited)
        self.assertEqual(len(results), 2)
        chosen = ota.choose_candidates(candidates, '2.1.3', '0012')
        self.assertEqual([c.version for c in chosen], ['2.1.3'])
        self.assertIn('低于', candidates[1].reason)

    def test_two_components_get_separate_versions_and_digests(self):
        candidates = collect({'version': '2.1.3', 'mcu_version': '0012',
                              'app_url': 'https://example.invalid/wifi.bin',
                              'mcu_url': 'https://example.invalid/mcu.bin',
                              'app_md5': 'a' * 32, 'mcu_md5': 'b' * 32,
                              'md5': 'c' * 32})
        chosen = ota.choose_candidates(candidates, '2.1.3', '0012')
        self.assertEqual({c.component: (c.version, c.md5) for c in chosen},
                         {'wifi': ('2.1.3', 'a' * 32), 'mcu': ('0012', 'b' * 32)})

    def test_shared_release_version_not_assigned_to_mcu(self):
        candidates = collect({'version': '2.1.3', 'app_url': 'https://example.invalid/wifi',
                              'mcu_url': 'https://example.invalid/mcu', 'md5': 'a' * 32})
        self.assertIsNone(candidates[1].version)
        self.assertTrue(all(c.md5 is None for c in candidates))
        self.assertEqual(len(ota.choose_candidates(candidates, '2.1.3', '0012')), 1)

    def test_generic_checksum_is_bound_to_single_file_only(self):
        candidate = collect({'version': '2.1.3', 'url': 'https://example.invalid/a', 'checksum': 'a' * 32})[0]
        self.assertEqual(candidate.md5, 'a' * 32)
        candidates = collect({'version': '2.1.3', 'app_url': 'https://example.invalid/a',
                              'mcu_url': 'https://example.invalid/b', 'checksum': 'a' * 32})
        self.assertTrue(all(c.md5 is None for c in candidates))

    def test_child_mcu_with_own_generic_version(self):
        candidates = collect({'version': '2.1.3', 'files': [
            {'version': '0013', 'mcu_url': 'https://example.invalid/mcu'}]})
        self.assertEqual(candidates[0].version, '0013')

    def test_parent_wifi_version_not_inherited_by_mcu_child(self):
        candidates = collect({'version': '2.1.3', 'mcu': {'url': 'https://example.invalid/mcu'}})
        self.assertEqual(candidates[0].component, 'mcu')
        self.assertIsNone(candidates[0].version)

    def test_wrong_models_devices_and_did_dictionary_are_excluded(self):
        candidates = collect({'result': [
            {'model': 'another.model', 'version': '9.9.9', 'url': 'https://example.invalid/wrong-model'},
            {'did': '987654321', 'version': '9.9.9', 'url': 'https://example.invalid/wrong-did'},
            {DID: {'version': '2.1.3', 'url': 'https://example.invalid/right'},
             '987654321': {'version': '9.9.9', 'url': 'https://example.invalid/wrong-key'}},
        ]})
        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0].scope, 'matched-did')

    def test_device_targeting_wins_over_higher_model_only_version(self):
        candidates = collect({'version': '2.1.3', 'url': 'https://example.invalid/device'})
        candidates += collect({'version': '9.9.9', 'url': 'https://example.invalid/model'}, GENERAL)
        self.assertEqual(ota.choose_candidates(candidates, '2.1.3')[0].version, '2.1.3')

    def test_same_version_different_files_requires_explicit_choice(self):
        candidates = collect([{'version': '2.1.3', 'url': f'https://example.invalid/{name}'} for name in ('a', 'b')])
        self.assertEqual(ota.choose_candidates(candidates, '2.1.3'), [])
        self.assertEqual(ota.choose_candidates(candidates, '2.1.3', requested=[candidates[1].identifier]), [candidates[1]])

    def test_manual_choice_cannot_bypass_known_downgrade_or_bad_checksum(self):
        candidates = collect([{'version': '1.3.9', 'url': 'https://example.invalid/old'},
                              {'version': '2.1.3', 'url': 'https://example.invalid/bad', 'md5': 'invalid'}])
        self.assertEqual(ota.choose_candidates(candidates, '2.1.3', requested=[c.identifier for c in candidates]), [])

    def test_composite_package_not_compared_as_wifi_version(self):
        candidates = collect({'version': '2.1.3.0012', 'url': 'https://example.invalid/bundle'})
        self.assertEqual(ota.choose_candidates(candidates, '2.1.3'), [])

    def test_query_selected_files_do_not_collapse_without_digest(self):
        candidates = collect([{'version': '2.1.3', 'url': 'https://example.invalid/download?file=' + name}
                              for name in ('a', 'b')])
        self.assertNotEqual(candidates[0].identifier, candidates[1].identifier)
        self.assertEqual(ota.choose_candidates(candidates, '2.1.3'), [])

    def test_mcu_numeric_counter_and_numeric_version_order(self):
        candidates = collect([{'mcu_url': 'https://example.invalid/' + v, 'mcu_version': v}
                              for v in ['0011', '0012', '0013']])
        self.assertEqual(ota.choose_candidates(candidates, current_mcu='0012')[0].version, '0013')
        self.assertEqual(ota.compare_versions('2.1.10', '2.1.9'), 1)
        self.assertIsNone(ota.compare_versions('213', '2.1.3'))

    def test_rate_limit_stops_later_queries(self):
        called = []

        def request(endpoint, auth, payload):
            called.append(endpoint)
            return {'code': -127, 'result': {'wait_second': 30}}

        _, outcomes, limited = ota.query_all({}, DID, MODEL, pid=1, delay=0, request=request)
        self.assertTrue(limited)
        self.assertEqual(len(called), 1)
        self.assertEqual(outcomes[0]['wait_seconds'], 30)


class DownloadTests(unittest.TestCase):
    body = b'\xea\x04\x00\x50' + b'example firmware fixture' * 20

    def candidate(self, md5=None):
        return ota.Candidate('https://example.invalid/image.bin?signature=private-test-value',
                             'wifi', '2.1.3', DEVICE, 'root', 'device-query', md5)

    def test_hash_verification_and_identical_existing_file(self):
        with tempfile.TemporaryDirectory() as directory:
            candidate = self.candidate(hashlib.md5(self.body).hexdigest())
            first = ota.download_candidate(candidate, directory, MODEL, 4096, opener=Opener(self.body))
            second = ota.download_candidate(candidate, directory, MODEL, 4096, opener=Opener(self.body))
            self.assertEqual(first, second)
            self.assertTrue(first['expected_checksum_verified'])
            self.assertEqual(len(list(Path(directory).iterdir())), 1)

    def test_checksum_failure_cleans_temporary_files(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaises(ValueError):
                ota.download_candidate(self.candidate('0' * 32), directory, MODEL, 4096, opener=Opener(self.body))
            self.assertEqual(list(Path(directory).iterdir()), [])

    def test_different_existing_file_is_not_overwritten(self):
        with tempfile.TemporaryDirectory() as directory:
            result = ota.download_candidate(self.candidate(), directory, MODEL, 4096, opener=Opener(self.body))
            target = Path(directory) / result['file']
            target.write_bytes(b'previous user file')
            with self.assertRaises(ValueError):
                ota.download_candidate(self.candidate(), directory, MODEL, 4096, opener=Opener(self.body))
            self.assertEqual(target.read_bytes(), b'previous user file')

    def test_html_truncation_and_oversize_are_rejected(self):
        for body, length, maximum in [(b'<html>error</html>', None, 4096),
                                      (self.body, len(self.body) + 1, 4096),
                                      (self.body, None, 10)]:
            with self.subTest(length=length, maximum=maximum), tempfile.TemporaryDirectory() as directory:
                with self.assertRaises(ValueError):
                    ota.download_candidate(self.candidate(), directory, MODEL, maximum, opener=Opener(body, length))
                self.assertEqual(list(Path(directory).iterdir()), [])

    def test_manifest_does_not_save_url_query_or_credentials(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'manifest.json'
            args = SimpleNamespace(model=MODEL, current_version='2.1.3', current_mcu_version='0012')
            ota.save_manifest(path, [self.candidate()], [], args, False)
            text = path.read_text()
            self.assertNotIn('private-test-value', text)
            self.assertNotIn('https://', text)
            self.assertNotIn('token', text.lower())
            self.assertNotIn(DID, text)
            self.assertEqual(json.loads(text)['candidates'][0]['host'], 'example.invalid')

    def test_main_info_only_does_not_download(self):
        with tempfile.TemporaryDirectory() as directory, \
             patch.object(ota, 'open_mit_store', return_value=(Path(directory) / 'auth.json', [])), \
             patch.object(ota, 'select_auth', return_value=('unused', {})), \
             patch.object(ota, 'query_all', return_value=([self.candidate()], [], False)), \
             patch.object(ota, 'download_candidate') as download, contextlib.redirect_stdout(io.StringIO()):
            result = ota.main(['--did', DID, '--out', directory, '--info-only', '--current-version', '2.1.3'])
            self.assertEqual(result, 0)
            download.assert_not_called()
            self.assertTrue((Path(directory) / 'ota-candidates.json').exists())

    def test_main_rate_limit_does_not_download_earlier_candidate(self):
        with tempfile.TemporaryDirectory() as directory, \
             patch.object(ota, 'open_mit_store', return_value=(Path(directory) / 'auth.json', [])), \
             patch.object(ota, 'select_auth', return_value=('unused', {})), \
             patch.object(ota, 'query_all', return_value=([self.candidate()], [], True)), \
             patch.object(ota, 'download_candidate') as download, contextlib.redirect_stdout(io.StringIO()):
            result = ota.main(['--did', DID, '--out', directory, '--current-version', '2.1.3'])
            self.assertEqual(result, 3)
            download.assert_not_called()

    def test_redirect_policies_keep_auth_and_downloads_separate(self):
        request = ota.urllib.request.Request('https://example.invalid/api', headers={'Cookie': 'test-only'})
        self.assertIsNone(ota.AuthNoRedirect().redirect_request(request, None, 302, '', {}, 'https://elsewhere.invalid'))
        with self.assertRaises(ota.OTAError):
            ota.HTTPSRedirect().redirect_request(request, None, 302, '', {}, 'http://example.invalid/image')


if __name__ == '__main__':
    unittest.main()
