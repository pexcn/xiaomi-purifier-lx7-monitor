#!/usr/bin/env python3
"""Statically split a Metro indexed RAM bundle; never execute plugin code."""
import argparse
import hashlib
import json
import struct
from pathlib import Path


def unpack(source, destination):
    data = source.read_bytes()
    if len(data) < 12:
        raise ValueError('Truncated header')
    magic, count, startup_size = struct.unpack_from('<III', data)
    if magic != 0xFB0BD1E5 or count > 1000000:
        raise ValueError('Not a supported Metro indexed RAM bundle')
    base = 12 + 8 * count
    if base + startup_size > len(data):
        raise ValueError('Truncated table/startup')
    if destination.exists():
        raise FileExistsError(destination)
    records = []
    for index in range(count):
        offset, size = struct.unpack_from('<II', data, 12 + 8 * index)
        if not size:
            continue
        start = base + offset
        if start < base + startup_size or start + size > len(data):
            raise ValueError(f'Invalid range for module {index}')
        raw = data[start:start + size]
        text = raw.rstrip(b'\0').decode('utf-8')
        records.append((index, start, size, text, hashlib.sha256(raw).hexdigest()))
    destination.mkdir(parents=True)
    (destination / 'startup.js').write_bytes(data[base:base + startup_size].rstrip(b'\0'))
    manifest = dict(source=source.name, sha256=hashlib.sha256(data).hexdigest(),
                    format='Metro indexed RAM bundle', magic=hex(magic),
                    table_entries=count, startup_size=startup_size, data_base=hex(base), modules=[])
    for index, start, size, text, digest in records:
        name = f'{index}.js'
        (destination / name).write_text(text, encoding='utf-8')
        manifest['modules'].append(dict(id=index, file=name, offset=hex(start),
                                        length=size, raw_sha256=digest))
    (destination / 'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
    print(f'{len(records)} modules; input SHA-256 {manifest["sha256"]}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('destination', type=Path)
    args = parser.parse_args()
    unpack(args.source, args.destination)
