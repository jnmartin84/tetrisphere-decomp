#!/usr/bin/env python3
"""Verify the source-only distribution manifest or compare the full ROM."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys

root=Path(__file__).resolve().parent
if sys.argv[1:]==['--rom']:
    raise SystemExit(subprocess.call([sys.executable,str(root/'tools/rom.py'),'verify']))
if sys.argv[1:]:sys.exit('Usage: python3 check-package.py [--rom]')
manifest=json.loads((root/'MANIFEST.json').read_text())
errors=[]
for name,entry in manifest.items():
    path=root/name
    if path.is_symlink() or not path.is_file():errors.append(f'{name}: missing or symlink')
    elif hashlib.sha256(path.read_bytes()).hexdigest()!=entry['sha256']:errors.append(f'{name}: content changed')
    elif path.stat().st_mode & 0o111 != int(entry['mode'],8) & 0o111:errors.append(f'{name}: executable mode changed')
if errors:sys.exit('\n'.join(errors))
print(f'SOURCE PACKAGE VERIFIED: {len(manifest)} files; local ROM/assets/tool downloads are excluded.')
