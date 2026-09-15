# Game EEPROM BSS restored to C

Baseline: `fe841555e731ea75ef5f14aa0547b6756a981bf9`.

`src/boot.c` now defines the EEPROM comparison mirror and dirty-block flags:

```c
u8 D_800F2050[0x200];
u8 D_800F2250[0x40];
```

These replace the two existing `extern u8 []` declarations in place. The names,
function bodies, physical line grouping, compiler flags, and every other byte
of `boot.c` are unchanged. The array bounds come from the comparison/copy loops
in `requestEepromWrite`, the worker's 64 eight-byte transfers, and initialization
loops in `mainproc`.

Stock IDO allocates exactly 576 bytes in a 16-aligned BSS section: the 512-byte
mirror at offset zero and the 64 flags at offset `0x200`, without added padding.
The linker places that section at `0x800F2050..0x800F2290`.

The original game reservation is split into a 16-byte assembly prefix,
`boot.o`'s 576-byte C allocation, and the unchanged assembly tail beginning at
`0x800F2290`. Only the two array reservations are removed. The prefix retains
the four existing labels at `0x800F2040..0x800F2050`; every other original raw
label and reserved span is preserved. YAML records the same three intervals.
No new translation unit or fixed-address alias was needed.

## Verification

- Pristine isolated and candidate builds passed `./matchdiff.sh`.
- Complete 8,388,608-byte ROM comparison passed, including the header.
- `boot.o`'s complete `.text` bytes are identical to the pristine object.
- All allocated ELF section layouts and all existing BSS symbol addresses
  remain unchanged. This migration adds no symbols.
- Both arrays are real, correctly sized C-owned objects in `.main_bss`.
- Reversing the two declaration substitutions restores the original `boot.c`
  hash; reconstructing the original assembly block restores its original hash.
- The cumulative verifier continues to check all three SDK BSS migrations.

After building, run without Python's `-O` option:

```sh
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
python3 pending/session_bss_game_eeprom/verify.py
```

`BASELINE.json` records pristine source, object-text, and ELF hashes, plus the
exact removed assembly text for reversible reconstruction. Binary artifacts
are untracked. Complete splat regeneration remains an untested research
operation, as before this change.

Other boot state still occupies nonadjacent raw intervals. This accepted
placement is for the two EEPROM arrays only; it does not establish original
TU boundaries or permit adding further `boot.c` BSS without planning its
allocation and rechecking the whole layout.
