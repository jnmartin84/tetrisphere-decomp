# GBI audit — first accepted pass

2026-09-13. Baseline: published commit
`a4c3cbe0012567925c7bb9a491283bad9694e9eb`.

The user requested systematic restoration of raw graphics commands to the
project's SDK GBI macros, accepting changes only when the full ROM still matches.
This explicitly expands the earlier identifier-only semantic work. Findings,
reversible replacement ledgers and rejected attempts are recorded separately.

## Current result

**1,137 command sites restored; full ROM match retained.**

| Source form | Initially found | Restored | Remaining |
| --- | ---: | ---: | ---: |
| Actual `gCmd` calls | 1,102 | 1,091 | 11 |
| Direct `Gfx.words` command pairs | 86 | 46 | 40 |
| Total | 1,188 | 1,137 | 51 |

The inventory excludes comments, preprocessor macro definitions, SDK internals
and already symbolic GBI calls. It covers raw `gCmd` calls and explicit
`pointer->words.w0/w1` stores in game C sources; it is not a claim that every
possible command encoded in assembly, data arrays or assets has been decoded.

Of the 51 remaining sites, 20 have tested macro forms that fail matching and
31 have variable or compound direct-store forms not attempted in this pass.
All remain in their original form. Every remaining site has a file, physical
line, containing function and status in [gbi_remaining.json](gbi_remaining.json).

## Accepted batches

Each row passed `./matchdiff.sh` and a comparison of every ROM byte. Batch
ledgers contain exact old/new text and offsets relative to the parent commit.

| Batch | Commit | Sites | Scope / record |
| --- | --- | ---: | --- |
| 001 | `f796959` | 18 | [beginGraphicsFrame](GBI_BEGIN_GRAPHICS_FRAME.md) |
| 002 | `4829e3f` | 576 | [State, synchronization, image setup](gbi_batch_002.json) |
| 003 | `1082a79` | 407 | [Texture, vertex, triangle, matrix, lighting](gbi_batch_003.json) |
| 004 | `04c5ac0` | 69 | [Combiner and render-mode presets](gbi_batch_004.json) |
| 005 | `9cca327` | 11 | [Custom combiners and variable fields](gbi_batch_005.json) |
| 006 | `cf4277a` | 10 | [Individually checked variable triangles](gbi_batch_006.json) |
| 007 | `7434b2d` | 46 | [Direct word stores](gbi_batch_007.json) |

Only `src/code_8170.c`, `src/game2.c` and `src/main.c` change among production
sources. Headers, compiler, flags, linker rules and object adjustments are
unchanged. Every replacement preserves its physical line count; unrelated
source bytes are untouched. The exact patch for each batch was reproduced from
its ledger against the parent commit: [validation](gbi_ledger_validation.json).
Batch 001 has its separate source-scope and byte-identical object checks.

The original local `gCmd` definitions/undefs and surrounding braces remain to
preserve source layout. Some restored direct-store calls span the original
three physical lines for the same reason. In `func_800BB3D0`, the local `g`
pointer is also passed to `func_8009C330`; its declaration and lifetime are
retained when restoring the tile-sync command.

## Semantic findings

- The project uses the original GBI encodings for these game commands, including
  vertex indices multiplied by ten. No switch to F3DEX/F3DEX2 was made.
- Numerous long blocks are texture/palette transfers. Their individual SDK
  commands now expose image format, texel size, tile, palette, wrapping and
  transfer dimensions. Multi-command convenience macros were not substituted
  for these sequences in this pass.
- Common combiner and render-mode words decode to existing SDK presets. Exact
  words, including both cycle fields, were preserved; preset aliases are not
  evidence of the original developers' exact source spelling.
- Three custom combiner calls in `code_8170.c` require explicit
  `gDPSetCombineLERP` operands rather than the available preset pairs.
- Ten second-triangle calls match with variable vertex and flag arguments.
  The corresponding first-triangle calls do not match in the tested form.
  Original flag expressions were preserved, not replaced with guessed constants.

## Rejected and deferred work

The initial 32-site custom/variable batch increased ROM size by 16 bytes.
Family isolation retained 11 sites; individual triangle isolation retained ten
more. The variable vertex call in `func_800A742C` produced a same-size ROM with
57 differing payload bytes in its isolated trial.

Nine direct-store replacements retaining existing command-pointer locals also
failed individually. Seven are the palette setup in `func_80067798`; the others
are render-mode writes in `func_80062C3C` and `func_800685FC`. The straightforward
macro expansions introduce another SDK temporary; the precise source-shape
correction remains unresolved. This rejects the tested source forms, not the possibility of a
matching restoration after further investigation.

Exact [rejected forms](gbi_rejected_forms.json) and trial output are retained:
[family trials](gbi_variable_trials.json),
[triangle trials](gbi_triangle_trials.json),
[retained-pointer trials](gbi_retained_pointer_trials.json).

The 31 unattempted direct-store sites are concentrated in `func_8003A900`
(seven), `func_8003B1A4` (21), `func_8006FA28` (two), and `func_8006FE64` (one).
They include variable tile coordinates, primitive colors, fill rectangles and
the three-word texture-rectangle sequence. Continue with one of these functions
or the retained-pointer palette setup as a bounded matching experiment. Do not
bulk-accept these remaining sites based only on equivalent command words.

## Acceptance and reproduction

Fresh isolated native macOS ARM64 build, official IDO 5.3 v1.2, GNU MIPS
binutils 2.47. The clean baseline passed `make -j4` and full `cmp`. The final
accepted source passed:

```sh
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

Final output: `FULL MATCH`. ROM size: **8,388,608 bytes**, including the header.
Reference and rebuilt SHA-256:
`f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.

Only text sources, documentation and JSON evidence belong in these commits.
The baseline distribution manifest and historical rename evidence remain
unchanged; `check-package.py` is expected to flag intentional source edits.
