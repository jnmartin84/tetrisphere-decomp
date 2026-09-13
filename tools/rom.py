#!/usr/bin/env python3
"""Validate the supplied USA ROM, extract raw inputs, or verify a rebuilt ROM."""
import argparse
import hashlib
import os
from pathlib import Path
import tempfile

ROOT = Path(__file__).resolve().parent.parent
ROM_SHA256 = 'f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87'
ROM_SIZE = 8388608
ASSETS = {'ipl3.bin': (0x40, 0x1000), 'CD3F0.bin': (0xCD3F0, 0x800000)}


def reference(root=ROOT):
    path = root / 'tetrisphere.z64'
    try:
        data = path.read_bytes()
    except FileNotFoundError:
        raise ValueError(f'Place your original USA ROM at {path}. It is not downloaded or included in Git.') from None
    if len(data) != ROM_SIZE or hashlib.sha256(data).hexdigest() != ROM_SHA256:
        raise ValueError('Wrong reference ROM: expected the 8,388,608-byte big-endian USA ROM, SHA-256 ' + ROM_SHA256)
    return data


def extract(root=ROOT):
    data = reference(root)
    output = root / 'assets'
    output.mkdir(exist_ok=True)
    for name, (start, end) in ASSETS.items():
        path = output / name
        payload = data[start:end]
        if path.is_file() and path.read_bytes() == payload:
            continue
        with tempfile.NamedTemporaryFile(dir=output, delete=False) as tmp:
            tmp.write(payload)
            temporary = Path(tmp.name)
        try:
            os.replace(temporary, path)
        finally:
            temporary.unlink(missing_ok=True)
        print(f'Extracted assets/{name}: {len(payload):,} bytes')


def verify(root=ROOT):
    data = reference(root)
    if (root / 'build/tetrisphere.us.z64').read_bytes() != data:
        raise ValueError('ROM MISMATCH (comparison includes all 64 header bytes).')
    print(f'FULL ROM MATCH: {ROM_SIZE:,} bytes including header; SHA256 {ROM_SHA256}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action', choices=['check', 'extract', 'verify'])
    args = parser.parse_args()
    try:
        if args.action == 'extract':
            extract()
        elif args.action == 'verify':
            verify()
        else:
            reference()
            print('Reference ROM verified.')
    except (OSError, ValueError) as exc:
        parser.exit(1, str(exc) + '\n')


if __name__ == '__main__':
    main()
