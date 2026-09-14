# Original diagnostic vocabulary: batch 011

Nine routine names recovered from direct diagnostic references. The user
authorized using the original vocabulary, including replacing two earlier
inferred semantic names. This is an identifier-only batch against 0520fe6;
no source organization, types, expressions, comments or whitespace changed.

| Previous identifier | Diagnostic-based identifier | Linked address |
| --- | --- | --- |
| `func_8008B830` | `PlacePieceAlways` | `0x8008B830` |
| `func_8008BB24` | `PlacePiece` | `0x8008BB24` |
| `func_8008E94C` | `CopyLevelPuzzle` | `0x8008E94C` |
| `allocatePieceOperationSlot` | `AllocDropPiece` | `0x800921A8` |
| `advancePieceOperation` | `PlacePieceGame` | `0x8009423C` |
| `func_800AC62C` | `PlayerWon` | `0x800AC62C` |
| `func_800C38F4` | `Begin_WinAnim` | `0x800C38F4` |
| `func_80073290` | `InitPlayScreen` | `0x80073290` |
| `func_8007F720` | `loadsong` | `0x8007F720` |

The string spelling is retained, including lowercase `loadsong` and the
underscore in `Begin_WinAnim`. These diagnostics strongly identify routine
roles and names; exact historical C capitalization is not independently proven.
`batch_011_string_evidence.json` records 13 literals checked against the original
ROM, their assembly locations, and their unique diagnostic call sites.

Behavior corroboration: `InitPlayScreen` loads HUD and animation resources;
the two placement routines plot occupied cells with different guards;
`CopyLevelPuzzle` copies board and player state; `PlayerWon` calls
`Begin_WinAnim`; `loadsong` validates a song ID and loads/prepares playback.
`AllocDropPiece` reserves one of 64 operation slots; `PlacePieceGame` advances
an operation, with the diagnostic naming it in its invalid-piece branch.

All definitions, declarations and production C callers were renamed. No old
identifiers remain in src. Remaining names in historical ledgers, archived
nonmatching assembly, YAML comments and evidence preserve their original context.
No active linker or generated symbol input required renaming.

Validation: 142 identifier substitutions in four files; lexical byte guard
passes and inverse substitutions restore all original source bytes. Both the
pristine and candidate builds report FULL MATCH; independent cmp includes the
64-byte header, and all nine linked symbol addresses are unchanged. See
`batch_011_verification.json`. No new tests were needed for the unchanged guard.

The input manifest includes 995 local files, including the existing ignored
asm_differ documentation screenshot, so the isolated and landing checkouts can
use the same strict census. The screenshot remains ignored and is not staged.
Compiler hashes describe this macOS host. No binaries belong in the commit.

Recheck:

```sh
python3 tools/semantic/identifier_renames.py --ledger analysis/semantic/batch_011.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```
