import copy
import json
from pathlib import Path
import subprocess
import tempfile
import unittest

from identifier_renames import Invalid, prepare, sha, substitute, verify_bytes


class LexicalTests(unittest.TestCase):
    def check(self, before, expected, count=1):
        mapping = {'old_name': 'descriptiveName'}
        after, events = substitute(before, mapping)
        self.assertEqual(after, expected)
        self.assertEqual(len(events), count)
        verify_bytes(before, after, mapping, {'old_name': count})

    def test_protected_text_and_exact_identifiers(self):
        self.check(b'old_name(); /* old_name */ // old_name\n"old_name"; old_name_suffix;\n',
                   b'descriptiveName(); /* old_name */ // old_name\n"old_name"; old_name_suffix;\n')

    def test_literals_escapes_and_prefixes(self):
        self.check(b'old_name; L"old_name"; u8"old_name"; U\'o\'; "\\\"old_name";',
                   b'descriptiveName; L"old_name"; u8"old_name"; U\'o\'; "\\\"old_name";')

    def test_spliced_comment_stays_protected(self):
        self.check(b'// comment \\\n old_name\nold_name;',
                   b'// comment \\\n old_name\ndescriptiveName;')

    def test_comment_delimiter_formed_by_splice(self):
        self.check(b'/\\\n* old_name */ old_name;', b'/\\\n* old_name */ descriptiveName;')

    def test_crlf_and_splicing_preserved(self):
        self.check(b'old_name( \\\r\n );\r\n', b'descriptiveName( \\\r\n );\r\n')

    def test_include_paths_protected(self):
        self.check(b'# include /* old_name */ <old_name.h>\n#include "old_name.h"\nold_name;',
                   b'# include /* old_name */ <old_name.h>\n#include "old_name.h"\ndescriptiveName;')

    def test_preprocessing_numbers_and_macro_tokens(self):
        self.check(b'#define X old_name\n0xold_name; 1e+old_name; .1old_name;',
                   b'#define X descriptiveName\n0xold_name; 1e+old_name; .1old_name;')

    def test_refuse_split_identifier(self):
        with self.assertRaises(Invalid):
            substitute(b'old_\\\nname();', {'old_name': 'descriptiveName'})

    def test_refuse_ambiguous_mapping(self):
        for mapping in ({'a': 'b', 'c': 'b'}, {'a': 'b', 'b': 'c'}, {'a': 'int'}):
            with self.subTest(mapping=mapping), self.assertRaises(Invalid):
                substitute(b'a b c;', mapping)

    def test_refuse_collision(self):
        with self.assertRaises(Invalid):
            substitute(b'old_name; descriptiveName;', {'old_name': 'descriptiveName'})

    def test_fail_closed_on_unsupported_or_malformed_input(self):
        for text in (b'old_name; /*', b'old_name; "unfinished', b'??/\nold_name;',
                     b'old_name; \\u1234;', b'old_name;\0', b'old_name; $foo;'):
            with self.subTest(text=text), self.assertRaises(Invalid):
                substitute(text, {'old_name': 'descriptiveName'})

    def test_reject_non_identifier_changes(self):
        before = b'old_name(); // old_name\r\n"old_name";'
        correct = b'descriptiveName(); // old_name\r\n"old_name";'
        for bad in (correct + b' ', correct.replace(b'\r\n', b'\n'),
                    correct.replace(b'// old_name', b'// descriptiveName'),
                    correct.replace(b'"old_name"', b'"descriptiveName"'),
                    correct.replace(b'();', b'(1);')):
            with self.subTest(bad=bad), self.assertRaises(Invalid):
                verify_bytes(before, bad, {'old_name': 'descriptiveName'}, {'old_name': 1})

    def test_count_guard(self):
        with self.assertRaises(Invalid):
            verify_bytes(b'old_name;', b'descriptiveName;', {'old_name': 'descriptiveName'}, {'old_name': 2})


class TreeTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        for directory in ('src', 'include', 'asm', 'assets', 'tools/ido5.3', 'tools/ultralib', 'work'):
            (self.root / directory).mkdir(parents=True, exist_ok=True)
        self.source = self.root / 'src/sample.c'
        self.source.write_bytes(b'void old_name(void) {}\n')
        (self.root / 'Makefile').write_bytes(b'all:\n\ttrue\n')
        self.git('init', '-q')
        self.git('add', 'src/sample.c', 'Makefile')
        self.git('-c', 'user.name=Validator Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'baseline')
        manifest = {name: {'sha256': sha((self.root/name).read_bytes()),
                           'mode': oct((self.root/name).stat().st_mode & 0o777)}
                    for name in ('src/sample.c', 'Makefile')}
        manifest_path = self.root / 'work/inputs.json'
        manifest_path.write_text(json.dumps(manifest))
        self.ledger = {'baseline_commit': self.git('rev-parse', 'HEAD').decode().strip(),
                       'input_manifest': 'work/inputs.json',
                       'input_manifest_sha256': sha(manifest_path.read_bytes()),
                       'files': {'src/sample.c': {'baseline_sha256': manifest['src/sample.c']['sha256'],
                                 'renames': {'old_name': 'descriptiveName'}, 'counts': {'old_name': 1}}}}

    def git(self, *args):
        return subprocess.check_output(['git', '-C', str(self.root), *args], stderr=subprocess.DEVNULL)

    def test_baseline_preflight_and_changed_tree(self):
        _, expected, _ = prepare(self.root, self.ledger, True)
        self.source.write_bytes(expected['src/sample.c'])
        prepare(self.root, self.ledger)

    def test_foreign_tracked_edit_rejected(self):
        (self.root / 'Makefile').write_bytes(b'all:\n\tfalse\n')
        with self.assertRaises(Invalid):
            prepare(self.root, self.ledger, True)

    def test_new_ignored_production_input_rejected(self):
        (self.root / 'src/sneaky.c').write_bytes(b'int other;')
        with self.assertRaises(Invalid):
            prepare(self.root, self.ledger, True)

    def test_manifest_tamper_rejected(self):
        (self.root / 'work/inputs.json').write_text('{}')
        with self.assertRaises(Invalid):
            prepare(self.root, self.ledger, True)

    def test_file_mode_change_rejected(self):
        self.source.chmod(self.source.stat().st_mode | 0o100)
        with self.assertRaises(Invalid):
            prepare(self.root, self.ledger, True)

    def test_symlink_rejected(self):
        self.source.rename(self.root / 'original.c')
        self.source.symlink_to(self.root / 'original.c')
        with self.assertRaises(Invalid):
            prepare(self.root, self.ledger, True)

    def test_staged_different_content_rejected(self):
        before = self.source.read_bytes()
        self.source.write_bytes(b'void changed(void) {}\n')
        self.git('add', 'src/sample.c')
        self.source.write_bytes(before)
        with self.assertRaises(Invalid):
            prepare(self.root, self.ledger, True)

    def incremental_fixture(self):
        before = b'void old_name(void) {}\nvoid next_name(void) {}\n'
        self.source.write_bytes(before)
        self.git('add', 'src/sample.c')
        self.git('-c', 'user.name=Validator Test', '-c', 'user.email=test@example.invalid',
                 'commit', '-qm', 'two function baseline')
        self.ledger['baseline_commit'] = self.git('rev-parse', 'HEAD').decode().strip()
        self.ledger['files']['src/sample.c']['baseline_sha256'] = sha(before)
        manifest_path = self.root / 'work/inputs.json'
        manifest = json.loads(manifest_path.read_bytes())
        manifest['src/sample.c']['sha256'] = sha(before)
        manifest_path.write_text(json.dumps(manifest))
        self.ledger['input_manifest_sha256'] = sha(manifest_path.read_bytes())
        self.source.write_bytes(substitute(before, {'old_name': 'descriptiveName'})[0])
        next_ledger = copy.deepcopy(self.ledger)
        next_ledger['files']['src/sample.c']['renames']['next_name'] = 'nextDescriptiveName'
        next_ledger['files']['src/sample.c']['counts']['next_name'] = 1
        return next_ledger

    def test_incremental_cli_preserves_previous_batch_and_baseline(self):
        next_ledger = self.incremental_fixture()
        for name, ledger in (('previous', self.ledger), ('next', next_ledger)):
            (self.root / ('work/' + name + '.json')).write_text(json.dumps(ledger))
        subprocess.check_output(['python3', str(Path(__file__).with_name('identifier_renames.py')),
                                 '--root', str(self.root), '--ledger', 'work/next.json',
                                 '--apply', '--from-ledger', 'work/previous.json'])
        self.assertEqual(self.source.read_bytes(),
                         b'void descriptiveName(void) {}\nvoid nextDescriptiveName(void) {}\n')
        prepare(self.root, next_ledger)

    def test_incremental_rejects_source_drift_without_writes(self):
        next_ledger = self.incremental_fixture()
        self.source.write_bytes(self.source.read_bytes() + b' ')
        before = self.source.read_bytes()
        with self.assertRaises(Invalid):
            prepare(self.root, next_ledger, True, self.ledger)
        self.assertEqual(self.source.read_bytes(), before)

    def test_incremental_rejects_rewriting_previous_decisions(self):
        next_ledger = self.incremental_fixture()
        for key, value in (('renames', 'differentName'), ('counts', 2)):
            bad = copy.deepcopy(next_ledger)
            bad['files']['src/sample.c'][key]['old_name'] = value
            with self.subTest(key=key), self.assertRaises(Invalid):
                prepare(self.root, bad, True, self.ledger)
        for key in ('baseline_commit', 'input_manifest', 'input_manifest_sha256'):
            bad = copy.deepcopy(next_ledger)
            bad[key] = 'changed'
            with self.subTest(key=key), self.assertRaises(Invalid):
                prepare(self.root, bad, True, self.ledger)

    def test_incremental_rejects_dropped_file_and_wrong_mode(self):
        next_ledger = self.incremental_fixture()
        with self.assertRaises(Invalid):
            prepare(self.root, next_ledger, False, self.ledger)
        next_ledger['files'].clear()
        with self.assertRaises(Invalid):
            prepare(self.root, next_ledger, True, self.ledger)


if __name__ == '__main__':
    unittest.main()
