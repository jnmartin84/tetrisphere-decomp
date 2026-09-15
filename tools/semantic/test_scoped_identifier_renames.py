import unittest
from identifier_renames import Invalid
from scoped_identifier_renames import transform


class ScopedRenames(unittest.TestCase):
    def test_same_spelling_other_scope_and_protected_text_unchanged(self):
        raw = b'int unk0; /* unk0 */ char *s="unk0"; struct A {int unk0;};'
        start = raw.rindex(b'unk0')
        event = {'old': 'unk0', 'new': 'sampleLength', 'offset': start}
        self.assertEqual(transform(raw, [event], 'c'), raw[:start] + b'sampleLength' + raw[start+4:])

    def test_comment_and_partial_identifier_rejected(self):
        for raw, start in [(b'/* unk0 */', 3), (b'int unk01;', 4), (b'"unk0"', 1)]:
            with self.assertRaises(Invalid):
                transform(raw, [{'old': 'unk0', 'new': 'flags', 'offset': start}], 'c')

    def test_assembly_only_label_changes(self):
        raw = b'dlabel D_1234\n    /* D_1234 */ .space 0x20\n'
        event = {'old': 'D_1234', 'new': 'gPlayer', 'offset': 7}
        self.assertEqual(transform(raw, [event], 'asm_dlabel'),
                         b'dlabel gPlayer\n    /* D_1234 */ .space 0x20\n')
        with self.assertRaises(Invalid):
            transform(raw, [dict(event, offset=raw.rindex(b'D_1234'))], 'asm_dlabel')

    def test_multiple_variable_length_changes_and_overlap(self):
        raw = b'int a, b;'
        events = [{'old': 'a', 'new': 'longName', 'offset': 4},
                  {'old': 'b', 'new': 'otherName', 'offset': 7}]
        self.assertEqual(transform(raw, events, 'c'), b'int longName, otherName;')
        with self.assertRaises(Invalid):
            transform(raw, events + events, 'c')

    def test_linker_assignment_preserves_address_and_spacing(self):
        raw = b'/* symbols */\n  D_1234 = 0x1234;\nD_1235=0x1235;\n'
        start = raw.index(b'D_1234')
        event = {'old': 'D_1234', 'new': 'gState', 'offset': start}
        self.assertEqual(transform(raw, [event], 'linker_assignment'),
                         raw[:start] + b'gState' + raw[start+6:])

    def test_linker_comment_is_not_an_assignment(self):
        raw = b'/*\nD_1234 = 0x1234;\n*/\n'
        with self.assertRaises(Invalid):
            transform(raw, [{'old': 'D_1234', 'new': 'gState',
                             'offset': raw.index(b'D_1234')}], 'linker_assignment')

    def test_linker_rhs_and_expressions_are_not_rename_sites(self):
        for raw, old in [(b'D_1234 = 0x1234;\n', '0x1234'),
                         (b'D_1234 = OTHER;\n', 'OTHER'),
                         (b'D_1234 = 0x1234 + 2;\n', 'D_1234')]:
            with self.assertRaises(Invalid):
                transform(raw, [{'old': old, 'new': 'gState',
                                 'offset': raw.index(old.encode())}], 'linker_assignment')


if __name__ == '__main__':
    unittest.main()
