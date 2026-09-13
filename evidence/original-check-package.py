#!/usr/bin/env python3
"""Verify snapshot integrity, or compare every byte of a rebuilt ROM."""
import hashlib
import json
from pathlib import Path
import sys

root = Path(__file__).resolve().parent
expected = 'f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87'
if sys.argv[1:] == ['--rom']:
    reference = (root / 'tetrisphere.z64').read_bytes()
    built = (root / 'build/tetrisphere.us.z64').read_bytes()
    if len(reference) != 8388608 or hashlib.sha256(reference).hexdigest() != expected:
        sys.exit('Reference ROM does not have the landed hash.')
    if built != reference:
        sys.exit('ROM MISMATCH (comparison includes the header).')
    print(f'FULL ROM MATCH: {len(built):,} bytes including header; SHA256 {expected}')
elif not sys.argv[1:]:
    manifest = json.loads((root / 'MANIFEST.json').read_text())
    errors = []
    for name, entry in manifest.items():
        p = root / name
        if p.is_symlink() or not p.is_file():
            errors.append(f'{name}: missing or symlink')
        elif hashlib.sha256(p.read_bytes()).hexdigest() != entry['sha256']:
            errors.append(f'{name}: content changed')
        elif (p.stat().st_mode & 0o111) != (int(entry['mode'], 8) & 0o111):
            errors.append(f'{name}: executable mode changed')
    if errors:
        sys.exit('\n'.join(errors))
    print(f'PACKAGE VERIFIED: {len(manifest)} files, contents and executable modes intact.')
else:
    sys.exit('Usage: python3 check-package.py [--rom]')
