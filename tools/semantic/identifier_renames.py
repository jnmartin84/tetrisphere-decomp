#!/usr/bin/env python3
"""Apply/check a reviewed file-scoped C identifier ledger without other edits.

This is a lexical byte guard, not a C binding/type checker. Assembly renames,
trigraphs, universal-character identifiers and identifiers split by a physical
line splice are deliberately unsupported. Full linked-ROM verification remains
mandatory. Only --apply writes source; all inputs are checked before writing.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess


class Invalid(ValueError):
    pass


IDENT = re.compile(rb"[A-Za-z_][A-Za-z_0-9]*")
KEYWORDS = set(b"auto break case char const continue default do double else enum extern float for goto if int long register return short signed sizeof static struct switch typedef union unsigned void volatile while inline restrict _Bool _Complex _Imaginary".split())


def require(condition, message):
    if not condition:
        raise Invalid(message)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def identifiers(raw):
    """Yield (spelling, physical start, physical end) outside protected tokens."""
    require(b'\0' not in raw, 'NUL byte in C input')
    require(not re.search(rb"\?\?[=/'()!<>-]", raw), 'trigraph requires separate review')
    logical = bytearray()
    positions = []
    p = 0
    while p < len(raw):
        if raw[p:p+2] == b'\\\n':
            p += 2
        elif raw[p:p+3] == b'\\\r\n':
            p += 3
        else:
            logical.append(raw[p])
            positions.append(p)
            p += 1
    data = bytes(logical)
    i = 0
    line_start = True
    directive = False
    header = False
    while i < len(data):
        c = data[i]
        if c in b' \t\v\f\r\n':
            if c == 10:
                line_start, directive, header = True, False, False
            i += 1
            continue
        if data[i:i+2] == b'//':
            end = data.find(b'\n', i + 2)
            i = len(data) if end < 0 else end
            continue
        if data[i:i+2] == b'/*':
            end = data.find(b'*/', i + 2)
            require(end >= 0, 'unterminated block comment')
            require(not ((directive or header) and b'\n' in data[i:end]),
                    'multiline directive comment requires separate review')
            i = end + 2
            continue
        if line_start and (c == 35 or data[i:i+2] == b'%:'):
            i += 1 if c == 35 else 2
            line_start, directive = False, True
            continue
        line_start = False
        if header and c == 60:
            end = data.find(b'>', i + 1)
            require(end >= 0 and b'\n' not in data[i:end], 'unterminated include header')
            i, header = end + 1, False
            continue
        # Recognize prefixes together with their string/character literals.
        literal = re.match(rb"(?:u8|u|U|L)?[\"']", data[i:i+3])
        if literal:
            quote = literal.group()[-1]
            i += len(literal.group())
            while i < len(data) and data[i] != quote:
                require(data[i] not in (10, 13), 'newline in literal')
                i += 2 if data[i] == 92 else 1
            require(i < len(data), 'unterminated literal')
            i += 1
            header = directive = False
            continue
        if 48 <= c <= 57 or (c == 46 and i+1 < len(data) and 48 <= data[i+1] <= 57):
            # A preprocessing number consumes identifier-like suffixes too.
            i += 1
            while i < len(data):
                c = data[i]
                if c in b'._' or 48 <= c <= 57 or 65 <= c <= 90 or 97 <= c <= 122:
                    i += 1
                elif c in b'+-' and data[i-1] in b'eEpP':
                    i += 1
                else:
                    break
            header = directive = False
            continue
        match = IDENT.match(data, i)
        if match:
            word = match.group()
            end = match.end()
            start_physical, end_physical = positions[i], positions[end-1] + 1
            yield word, start_physical, end_physical
            header = directive and word in (b'include', b'include_next', b'import')
            directive = False
            i = end
            continue
        require(c < 128 and c not in (36, 92), 'unsupported C identifier/token encoding')
        header = directive = False
        i += 1


def substitute(raw, mapping):
    encoded = {a.encode('ascii'): b.encode('ascii') for a, b in mapping.items()}
    for a, b in encoded.items():
        require(IDENT.fullmatch(a) and IDENT.fullmatch(b), 'invalid identifier')
        require(a not in KEYWORDS and b not in KEYWORDS, 'keyword in rename')
    require(len(set(encoded.values())) == len(encoded), 'non-injective rename')
    require(not set(encoded) & set(encoded.values()), 'overlapping old/new names')
    tokens = list(identifiers(raw))
    require(not {w for w, _, _ in tokens} & set(encoded.values()), 'new name already exists')
    parts, events, last = [], [], 0
    for word, start, end in tokens:
        if word in encoded:
            require(raw[start:end] == word, 'renamed identifier crosses a line splice')
            parts.extend((raw[last:start], encoded[word]))
            events.append({'old': word.decode(), 'new': encoded[word].decode(),
                           'offset': start, 'line': raw.count(b'\n', 0, start) + 1})
            last = end
    parts.append(raw[last:])
    return b''.join(parts), events


def verify_bytes(before, after, mapping, counts):
    expected, events = substitute(before, mapping)
    actual = {old: sum(e['old'] == old for e in events) for old in mapping}
    require(actual == counts and all(actual.values()), 'occurrence counts differ from ledger')
    require(after == expected, 'bytes differ beyond the approved identifier substitutions')
    reversed_bytes, _ = substitute(after, {b: a for a, b in mapping.items()})
    require(reversed_bytes == before, 'inverse substitutions do not reproduce baseline')
    return events


def git(root, *args):
    return subprocess.check_output(['git', '-C', str(root), *args])


def local_file(root, name):
    relative = Path(name)
    require(not relative.is_absolute() and '..' not in relative.parts and name != '.', 'unsafe path')
    path = root / relative
    require(path.resolve() == path.absolute(), 'symlink in input path: ' + name)
    return path


def prepare(root, ledger, applying=False, previous=None):
    current = {}
    if previous is not None:
        require(applying, 'previous ledger requires apply mode')
        for key in ('baseline_commit', 'input_manifest', 'input_manifest_sha256'):
            require(ledger[key] == previous[key], 'incremental baseline/input manifest differs')
        for name, spec in previous['files'].items():
            require(name in ledger['files'], 'incremental ledger drops file: ' + name)
            next_spec = ledger['files'][name]
            require(spec['baseline_sha256'] == next_spec['baseline_sha256'], 'incremental source baseline differs')
            for key in ('renames', 'counts'):
                require(all(next_spec[key].get(old) == value for old, value in spec[key].items()),
                        'incremental ledger changes previous ' + key + ': ' + name)
        _, current, _ = prepare(root, previous)
    base = ledger['baseline_commit']
    require(re.fullmatch(r'[0-9a-f]{40}', base), 'baseline must be a full commit hash')
    require(git(root, 'rev-parse', base + '^{commit}').decode().strip() == base, 'invalid baseline')
    files = ledger['files']
    require(files, 'empty ledger')
    expected = {}
    results = {}
    originals = {}
    for name, spec in files.items():
        require(Path(name).suffix in ('.c', '.h'), 'only C/header renames supported')
        path = local_file(root, name)
        before = git(root, 'show', base + ':' + name)
        require(sha(before) == spec['baseline_sha256'], 'baseline hash differs: ' + name)
        after, _ = substitute(before, spec['renames'])
        results[name] = verify_bytes(before, after, spec['renames'], spec['counts'])
        originals[name], expected[name] = before, after
        require(path.read_bytes() == (current.get(name, before) if applying else after), 'unexpected source bytes: ' + name)

    # Check every provisioned production input, including generated/untracked ones.
    manifest_bytes = local_file(root, ledger['input_manifest']).read_bytes()
    require(sha(manifest_bytes) == ledger['input_manifest_sha256'], 'input manifest hash differs')
    manifest = json.loads(manifest_bytes)
    require(set(files) <= set(manifest), 'ledger file absent from input manifest')
    for name, spec in manifest.items():
        path = local_file(root, name)
        data = path.read_bytes()
        want = sha(current.get(name, originals[name]) if applying else expected[name]) if name in files else spec['sha256']
        require(sha(data) == want, 'production input changed: ' + name)
        require((path.stat().st_mode & 0o111) == (int(spec['mode'], 8) & 0o111), 'mode changed: ' + name)

    # Any existing tracked file outside the rename set must remain unchanged.
    baseline_files = set(git(root, 'ls-tree', '-r', '--name-only', base).decode().splitlines())
    changed = git(root, 'diff', '--name-only', base, '--').decode().splitlines()
    for name in changed:
        if name in files:
            continue
        require(name not in baseline_files and name.startswith(('analysis/semantic/', 'tools/semantic/')),
                'out-of-scope tracked change: ' + name)
    # Catch newly introduced compiler inputs even when Git ignores them.
    for directory in ('src', 'include', 'asm', 'assets', 'tools/ido5.3', 'tools/ultralib'):
        for path in (root / directory).rglob('*'):
            if path.is_file() or path.is_symlink():
                require(path.relative_to(root).as_posix() in manifest, 'unexpected production file: ' + str(path))
    # A successful worktree check must not conceal a stale/different staged file.
    for name in git(root, 'diff', '--cached', '--name-only').decode().splitlines():
        require(git(root, 'show', ':' + name) == local_file(root, name).read_bytes(), 'index/worktree differ: ' + name)
    return originals, expected, results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path.cwd())
    parser.add_argument('--ledger', default='analysis/semantic/batch_001.json')
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--from-ledger', help='Verified previous cumulative ledger, only with --apply')
    parser.add_argument('--report', type=Path)
    args = parser.parse_args()
    root = args.root.resolve()
    ledger = json.loads(local_file(root, args.ledger).read_bytes())
    require(args.from_ledger is None or args.apply, '--from-ledger requires --apply')
    previous = json.loads(local_file(root, args.from_ledger).read_bytes()) if args.from_ledger else None
    originals, expected, events = prepare(root, ledger, args.apply, previous)
    if args.apply:
        current = dict(originals)
        if previous is not None:
            for name, spec in previous['files'].items():
                current[name], _ = substitute(originals[name], spec['renames'])
        for name, data in expected.items():
            path = local_file(root, name)
            require(path.read_bytes() == current[name], 'source changed since preflight: ' + name)
            if data != current[name]:
                path.write_bytes(data)
        prepare(root, ledger)
    report = {'status': 'IDENTIFIER_ONLY_VERIFIED', 'baseline_commit': ledger['baseline_commit'],
              'ledger_sha256': sha(local_file(root, args.ledger).read_bytes()),
              'files': {name: {'before_sha256': sha(originals[name]), 'after_sha256': sha(expected[name]),
                               'substitutions': events[name]} for name in expected},
              'inverse_restores_original_bytes': True,
              'production_inputs_verified': True, 'rom_verified_by_this_tool': False}
    if args.report:
        report_path = args.report.resolve()
        require(report_path.is_relative_to(root / 'analysis/semantic') or report_path.is_relative_to(root / 'work'),
                'report must be in analysis/semantic or work')
        require(report_path not in {root / args.ledger, root / ledger['input_manifest']}, 'report would replace validation input')
        report_path.write_text(json.dumps(report, indent=2) + '\n')
    print('IDENTIFIER ONLY: %d substitutions in %d files; inverse byte match; production inputs intact.' %
          (sum(map(len, events.values())), len(expected)))


if __name__ == '__main__':
    try:
        main()
    except (Invalid, OSError, KeyError, UnicodeError, subprocess.CalledProcessError) as error:
        raise SystemExit('REJECTED: ' + str(error))
