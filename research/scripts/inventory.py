#!/usr/bin/env python3
"""Inventory exact tables/strings in the supplied lx7 1.3.9 Wi-Fi image.

Static reads only. Offsets are specific to the SHA-256 checked below.
"""
import argparse
import hashlib
import json
import struct
from pathlib import Path


def inventory(source):
    data = source.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    if digest != 'f20d634664918a9e5ab483774c1fd3b80afae2bfd6a5416619a56aaa1093a1c5':
        raise ValueError('Table offsets have only been validated for the supplied image')
    segments = [(0x10, 0x40201010, 0x65260), (0x65280, 0x40100000, 0x7af8),
                (0x6cd80, 0x3ffe8000, 0xc80), (0x6da08, 0x3ffe8c80, 0x1e8c)]

    def offset(address):
        for start, base, length in segments:
            if base <= address < base + length:
                return start + address - base
        raise ValueError(hex(address))

    def string(address):
        start = offset(address)
        return data[start:data.index(0, start)].decode('ascii')

    methods = []
    for i in range(16):
        start = 0x6d980 + i * 8
        function, name = struct.unpack_from('<II', data, start)
        symbol = string(name)
        namespace = 'miIO' if i < 15 else 'user'
        method = symbol.removesuffix('_JsDlgt')
        methods.append(dict(namespace=namespace, method=f'{namespace}.{method}',
                            symbol=symbol, table_offset=hex(start),
                            function=hex(function), function_offset=hex(offset(function)),
                            string_offset=hex(offset(name))))
    commands = []
    for i in range(30):
        start = 0x6d800 + i * 12
        name, help_address, function = struct.unpack_from('<III', data, start)
        commands.append(dict(command=string(name), help=string(help_address) if help_address else None,
                             function=hex(function), function_offset=hex(offset(function)),
                             table_offset=hex(start), string_offset=hex(offset(name))))
    search = {}
    for term in ['usedflow', 'get_prop', 'tds_warn_thd', 'lightMode', 'filter',
                 'yunmi.waterpuri.lx7', 'MR532-D', '3600', '7200', '8640', '17280']:
        result = {}
        for encoding in ['ascii', 'utf-16le', 'utf-16be']:
            needle = term.encode(encoding)
            result[encoding] = [hex(i) for i in range(len(data)) if data.startswith(needle, i)]
        search[term] = result
    return dict(sha256=digest, native_delegates=methods, uart_commands=commands,
                exact_string_search=search,
                limitations=['A string absence is not proof that runtime MCU lacks a method.',
                             'IROM assumes OTA user1 at flash 0x1000.',
                             'user.bind_key is also resolved by unprefixed bind_key.'])


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    args = parser.parse_args()
    print(json.dumps(inventory(args.source), ensure_ascii=False, indent=2))
