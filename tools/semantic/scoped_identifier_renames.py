#!/usr/bin/env python3
"""Check/apply C token, assembly dlabel or linker assignment identifier renames.

Unlike the file-wide guard, this supports selected members without renaming
unrelated members sharing an unk spelling. It does not infer C type bindings.
The reviewed ledger selects exact tokens; every other byte must stay unchanged.
"""
import argparse
import json
from pathlib import Path
import re

from identifier_renames import IDENT, KEYWORDS, git, identifiers, local_file, require, sha


def token_spans(raw, kind):
    if kind == 'c':
        return {(a, b): word for word, a, b in identifiers(raw)}
    if kind == 'linker_assignment':
        tokens = {(a, b): word for word, a, b in identifiers(raw)}
        return {m.span(1): m[1] for m in re.finditer(
            rb'^[ \t]*([A-Za-z_][A-Za-z_0-9]*)[ \t]*=[ \t]*0x[0-9A-Fa-f]+[ \t]*;[ \t]*$',
            raw, re.M) if tokens.get(m.span(1)) == m[1]}
    require(kind == 'asm_dlabel', 'unsupported token kind')
    return {m.span(1): m[1] for m in re.finditer(
        rb'^dlabel ([A-Za-z_][A-Za-z_0-9]*)[ \t]*$', raw, re.M)}


def transform(raw, events, kind):
    require(events, 'empty event set')
    spans = token_spans(raw, kind)
    result, last, inverse, shift = [], 0, [], 0
    for event in events:
        old, new = event['old'].encode('ascii'), event['new'].encode('ascii')
        require(IDENT.fullmatch(new) and new not in KEYWORDS and old != new,
                'invalid replacement identifier')
        start, end = event['offset'], event['offset'] + len(old)
        require(start >= last and spans.get((start, end)) == old,
                'event is overlapping, unordered, or not an approved token')
        require(raw[start:end] == old, 'baseline spelling mismatch')
        result.extend((raw[last:start], new))
        inverse.append((start + shift, new, old))
        shift += len(new) - len(old)
        last = end
    result.append(raw[last:])
    after = b''.join(result)
    after_spans = token_spans(after, kind)
    restored = after
    for start, new, old in reversed(inverse):
        require(after_spans.get((start, start + len(new))) == new,
                'replacement does not form an identifier token')
        restored = restored[:start] + old + restored[start + len(new):]
    require(restored == raw, 'inverse did not restore original bytes')
    return after


def check(root, ledger, applying=False):
    base = ledger['baseline_commit']
    require(re.fullmatch('[0-9a-f]{40}', base), 'full baseline hash required')
    require(git(root, 'rev-parse', base + '^{commit}').decode().strip() == base,
            'invalid baseline')
    outputs = {}
    for name, spec in ledger['files'].items():
        require((spec['kind'] == 'c' and Path(name).suffix in ('.c', '.h')) or
                (spec['kind'] == 'asm_dlabel' and name.startswith('asm/data/')
                 and Path(name).suffix == '.s') or
                (spec['kind'] == 'linker_assignment' and name == 'undefined_syms.txt'),
                'invalid production path/kind')
        before = git(root, 'show', base + ':' + name)
        require(sha(before) == spec['baseline_sha256'], 'baseline hash mismatch: ' + name)
        after = transform(before, spec['events'], spec['kind'])
        require(local_file(root, name).read_bytes() == (before if applying else after),
                'unexpected bytes: ' + name)
        outputs[name] = after
    manifest_raw = local_file(root, ledger['input_manifest']).read_bytes()
    require(sha(manifest_raw) == ledger['input_manifest_sha256'], 'manifest hash mismatch')
    manifest = json.loads(manifest_raw)
    require(set(outputs) <= set(manifest), 'rename input absent from manifest')
    for name, spec in manifest.items():
        path = local_file(root, name)
        expected = sha(outputs[name]) if name in outputs and not applying else spec['sha256']
        require(sha(path.read_bytes()) == expected, 'input changed: ' + name)
        require(path.stat().st_mode & 0o111 == int(spec['mode'], 8) & 0o111,
                'executable mode changed: ' + name)
    for directory in ('src', 'include', 'asm', 'assets', 'tools/ido5.3', 'tools/ultralib'):
        for path in (root / directory).rglob('*'):
            if path.is_file() or path.is_symlink():
                require(path.relative_to(root).as_posix() in manifest, 'extra input: ' + str(path))
    baseline_files = set(git(root, 'ls-tree', '-r', '--name-only', base).decode().splitlines())
    for name in git(root, 'diff', '--name-only', base, '--').decode().splitlines():
        if name not in outputs:
            require(name not in baseline_files and name.startswith(('analysis/semantic/', 'tools/semantic/')),
                    'out of scope change: ' + name)
    for name in git(root, 'diff', '--cached', '--name-only').decode().splitlines():
        require(git(root, 'show', ':' + name) == local_file(root, name).read_bytes(),
                'index/worktree differ: ' + name)
    return outputs


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--ledger', required=True)
    parser.add_argument('--apply', action='store_true')
    parser.add_argument('--report')
    args = parser.parse_args()
    root = Path.cwd().resolve()
    ledger_raw = local_file(root, args.ledger).read_bytes()
    ledger = json.loads(ledger_raw)
    outputs = check(root, ledger, args.apply)
    if args.apply:
        for name, data in outputs.items():
            require(sha(local_file(root, name).read_bytes()) == ledger['files'][name]['baseline_sha256'],
                    'input changed after preflight')
            local_file(root, name).write_bytes(data)
        check(root, ledger)
    count = sum(len(spec['events']) for spec in ledger['files'].values())
    report = {'status': 'SCOPED_IDENTIFIER_ONLY_VERIFIED', 'baseline_commit': ledger['baseline_commit'],
              'ledger_sha256': sha(ledger_raw), 'substitutions': count,
              'inverse_restores_original_bytes': True, 'production_inputs_verified': True,
              'rom_verified_by_this_tool': False,
              'files': {name: {'before_sha256': ledger['files'][name]['baseline_sha256'],
                               'after_sha256': sha(data)} for name, data in outputs.items()}}
    if args.report:
        path = local_file(root, args.report)
        require(args.report.startswith(('analysis/semantic/', 'work/')) and
                args.report not in (args.ledger, ledger['input_manifest']), 'unsafe report path')
        require(not path.exists(), 'report exists; select a new output path')
        path.write_text(json.dumps(report, indent=2) + '\n')
    print(f'SCOPED IDENTIFIER ONLY: {count} substitutions in {len(outputs)} files; inverse byte match; inputs intact.')


if __name__ == '__main__':
    main()
