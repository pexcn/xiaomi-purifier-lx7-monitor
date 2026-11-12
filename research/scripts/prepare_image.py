#!/usr/bin/env python3
"""Read ESP8266 v2 OTA image; emit an analysis-only ELF and offset manifest.

The ELF is a synthetic container, not recovered vendor ELF. IROM mapping assumes
user1 at flash 0x1000; validate it against embedded pointers before using it.
"""
import argparse
import hashlib
import json
import struct
from pathlib import Path


def prepare(source, destination):
    data = source.read_bytes()
    if data[0] != 0xEA:
        raise ValueError('Expected ESP8266 v2 0xEA image')
    _, _, mode, size_freq, entry = struct.unpack_from('<BBBBI', data)
    address, length = struct.unpack_from('<II', data, 8)
    if address != 0:
        raise ValueError('Unexpected IROM header')
    segments = [dict(name='.irom0.text', file_offset=16, address=0x40201010,
                     length=length, flags=5)]
    position = 16 + length
    magic, count, _, _, inner_entry = struct.unpack_from('<BBBBI', data, position)
    if magic != 0xE9 or inner_entry != entry:
        raise ValueError('Invalid inner ESP image')
    position += 8
    checksum = 0xEF
    for i in range(count):
        address, length = struct.unpack_from('<II', data, position)
        position += 8
        payload = data[position:position + length]
        if len(payload) != length:
            raise ValueError('Truncated segment')
        for byte in payload:
            checksum ^= byte
        segments.append(dict(name='.iram0.text' if address >= 0x40000000 else f'.dram{i}',
                             file_offset=position, address=address, length=length,
                             flags=5 if address >= 0x40000000 else 6))
        position += length
    # ESP checksum is the last byte of the next 16-byte aligned image block.
    checksum_offset = position | 15
    if checksum_offset >= len(data) or data[checksum_offset] != checksum:
        raise ValueError('Truncated image or RAM XOR checksum mismatch')
    manifest = dict(source=str(source), sha256=hashlib.sha256(data).hexdigest(),
                    size=len(data), format='ESP8266 v2 OTA', entry=entry,
                    spi_mode=mode, size_frequency=size_freq, segments=segments,
                    checksum_offset=checksum_offset, checksum_computed=checksum,
                    checksum_stored=data[checksum_offset],
                    trailing_bytes=len(data) - checksum_offset - 1,
                    caveat='Synthetic ELF; IROM flash slot assumption 0x1000')
    destination.mkdir(parents=True, exist_ok=True)
    names = b'\0.shstrtab\0'
    name_offsets = []
    for segment in segments:
        name_offsets.append(len(names))
        names += segment['name'].encode() + b'\0'
    blob = bytearray(52 + len(segments) * 32)
    records = []
    for segment in segments:
        blob += b'\0' * (-len(blob) % 16)
        offset = len(blob)
        payload = data[segment['file_offset']:segment['file_offset'] + segment['length']]
        blob += payload
        records.append((offset, segment))
    string_offset = len(blob)
    blob += names
    blob += b'\0' * (-len(blob) % 4)
    section_offset = len(blob)
    blob += bytes(40)
    blob += struct.pack('<10I', 1, 3, 0, 0, string_offset, len(names), 0, 0, 1, 0)
    for name_offset, (offset, segment) in zip(name_offsets, records):
        flags = 6 if segment['flags'] == 5 else 3
        blob += struct.pack('<10I', name_offset, 1, flags, segment['address'], offset,
                            segment['length'], 0, 0, 4, 0)
    ident = b'\x7fELF\x01\x01\x01' + bytes(9)
    blob[:52] = struct.pack('<16sHHIIIIIHHHHHH', ident, 2, 94, 1, entry, 52,
                            section_offset, 0, 52, 32, len(segments), 40,
                            2 + len(segments), 1)
    for i, (offset, segment) in enumerate(records):
        struct.pack_into('<8I', blob, 52 + i * 32, 1, offset, segment['address'],
                         segment['address'], segment['length'], segment['length'],
                         segment['flags'], 1)
    (destination / 'lx7-analysis.elf').write_bytes(blob)
    (destination / 'image-map.json').write_text(json.dumps(manifest, indent=2) + '\n')
    print(json.dumps(manifest, indent=2))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('destination', type=Path)
    args = parser.parse_args()
    prepare(args.source, args.destination)
