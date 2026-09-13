#!/usr/bin/env python3
"""Install the pinned, hash-checked IDO 5.3 release for this host."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import shutil
import subprocess
import tarfile
import tempfile

RELEASE = 'v1.2'
SHA256 = {
    'linux': 'ab5c741561f80913d58c8b074771f23941a3edd312505a8ebed6d1dfeb65e506',
    'linux-arm': 'b6844c986fa65d7de4ce10b27583769a5ec7a88ae37a151f6dc66c929d3e1c92',
    'macos': '5b1ca006ee4b158ffba0422fc3f00b9b330f9036f279bae2ea1b4703317ad9c0',
    'windows': '2268f64cab973750e78bdf7aa2ff3cccf78ad1d181507da6faeb61f3d22c2e1e',
}
ROOT = Path(__file__).resolve().parent.parent


def host_id(system=None, machine=None):
    system = system or platform.system()
    machine = (machine or platform.machine()).lower()
    if system == 'Linux':
        if machine in ('x86_64', 'amd64'):
            return 'linux'
        if machine in ('aarch64', 'arm64'):
            return 'linux-arm'
    if system == 'Darwin' and machine in ('arm64', 'aarch64', 'x86_64', 'amd64'):
        return 'macos'  # upstream universal x86_64 + arm64 executable
    if system == 'Windows' and machine in ('x86_64', 'amd64'):
        return 'windows'
    raise ValueError(f'Unsupported IDO host: {system}/{machine}. Use Linux x86_64/ARM64, macOS x86_64/ARM64, or Windows x86_64 (WSL recommended for the full build).')


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def installed(directory, host):
    try:
        stamp = json.loads((directory / '.installed.json').read_text())
        if stamp['archive_sha256'] != SHA256[host] or stamp['release'] != RELEASE:
            return False
        return bool(stamp['files']) and all(
            not (directory / name).is_symlink()
            and digest(directory / name) == info['sha256']
            and (os.name == 'nt' or (directory / name).stat().st_mode & 0o111 == info['executable'])
            for name, info in stamp['files'].items())
    except (OSError, ValueError, KeyError):
        return False


def unpack(archive, destination):
    # Official archives are flat regular files. Refuse links or path traversal.
    with tarfile.open(archive, 'r:gz') as tar:
        members = tar.getmembers()
        names = set()
        for member in members:
            if not member.isfile() or '/' in member.name or '\\' in member.name or member.name in ('', '.', '..') or member.name in names:
                raise ValueError(f'Unexpected archive member: {member.name}')
            names.add(member.name)
        for member in members:
            target = destination / member.name
            with tar.extractfile(member) as source, target.open('wb') as output:
                shutil.copyfileobj(source, output)
            target.chmod(member.mode & 0o777)


def install(host, archive=None):
    parent = ROOT / 'tools' / 'ido5.3' / RELEASE
    directory = parent / host
    if installed(directory, host):
        print(f'IDO 5.3 {RELEASE} verified: {directory.relative_to(ROOT)}')
        return
    parent.mkdir(parents=True, exist_ok=True)
    # A single setup target services all parallel object builds in make.
    with tempfile.TemporaryDirectory(prefix=f'.{host}-', dir=parent) as temp:
        temp = Path(temp)
        package = temp / 'release.tar.gz'
        if archive:
            shutil.copyfile(archive, package)
        else:
            url = f'https://github.com/decompals/ido-static-recomp/releases/download/{RELEASE}/ido-5.3-recomp-{host}.tar.gz'
            print(f'Downloading {url}', flush=True)
            subprocess.run(['curl', '--fail', '--location', '--retry', '3', '--silent', '--show-error', url, '--output', str(package)], check=True)
        if digest(package) != SHA256[host]:
            raise ValueError('IDO archive SHA-256 mismatch; installation was not changed.')
        new = temp / 'install'
        new.mkdir()
        unpack(package, new)
        compiler = 'cc.exe' if host == 'windows' else 'cc'
        if not (new / compiler).is_file():
            raise ValueError('IDO archive has no compiler driver.')
        files = {p.name: {'sha256': digest(p), 'executable': p.stat().st_mode & 0o111} for p in sorted(new.iterdir())}
        (new / '.installed.json').write_text(json.dumps({'release': RELEASE, 'archive_sha256': SHA256[host], 'files': files}, indent=2) + '\n')
        # Preserve an existing installation until its verified replacement is ready.
        previous = temp / 'previous'
        if directory.exists():
            directory.rename(previous)
        try:
            new.rename(directory)
        except OSError:
            if previous.exists():
                previous.rename(directory)
            raise
    print(f'Installed IDO 5.3 {RELEASE}: {directory.relative_to(ROOT)}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cc-path', action='store_true', help='print host compiler path without downloading')
    parser.add_argument('--archive', type=Path, help='use a local official archive (same SHA-256 verification)')
    args = parser.parse_args()
    try:
        host = host_id()
        if args.cc_path:
            print(f'tools/ido5.3/{RELEASE}/{host}/' + ('cc.exe' if host == 'windows' else 'cc'))
        else:
            install(host, args.archive)
    except (ValueError, OSError, subprocess.CalledProcessError) as exc:
        parser.exit(1, f'{exc}\n')


if __name__ == '__main__':
    main()
