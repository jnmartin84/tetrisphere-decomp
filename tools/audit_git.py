#!/usr/bin/env python3
"""Reject binary content, binary artifacts and symlinks in the Git index."""
from pathlib import PurePosixPath
import subprocess
import sys


def main():
    errors=[]
    rows=subprocess.check_output(['git','ls-files','--stage','-z']).split(b'\0')
    count=0
    for row in rows:
        if not row:continue
        meta,rawname=row.split(b'\t',1)
        mode,oid,stage=meta.split()
        name=rawname.decode('utf-8');p=PurePosixPath(name)
        if mode not in (b'100644',b'100755') or stage!=b'0':
            errors.append(f'{name}: non-regular or unresolved index entry');continue
        data=subprocess.check_output(['git','cat-file','blob',oid.decode()])
        if b'\0' in data:
            errors.append(f'{name}: NUL bytes')
        try:data.decode('utf-8')
        except UnicodeDecodeError:errors.append(f'{name}: not UTF-8 text')
        if p.suffix.lower() in ('.bin','.z64','.n64','.v64','.elf','.o','.a','.so','.dylib','.exe','.dll','.png','.jpg','.jpeg','.wav','.xm','.mp3','.ogg','.zip','.gz','.tar','.pdf') or name.startswith(('build/','work/','tools/ido5.3/')):
            errors.append(f'{name}: forbidden generated/binary artifact path')
        count+=1
    if errors:sys.exit('\n'.join(errors))
    print(f'SOURCE-ONLY INDEX: {count} regular UTF-8 text files; no binary artifacts.')


if __name__=='__main__':main()
