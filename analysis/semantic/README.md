# Semantic names branch

This directory preserves research from the original semantic branch. The
source-only publication imports its final source at 490402d. Original VM
paths, Git baseline and build-input checks below are historical; use the
root README and evidence/PUBLICATION.json for this repository.

Worktree: `wr64vm:~/wt/semantic_names`.
Branch: `codex/semantic-names`.
Original baseline: `823ca10873a7eafde7d68951087cdaf9d3095dfd`.
The canonical `main` checkout and `/Users/jnmartin/landed_tsphere` remain
unchanged. This branch is the editable semantic version.

## Source rule

> I would not dare change anything other than names. no whitespace, no line spacing, no nothing

Existing source may change only through reviewed identifier spelling
substitutions. Preserve all other bytes, including comments, strings,
whitespace, line endings, physical grouping, types and expressions. Keep
semantic explanations and uncertainties here. Do not rename SDK ABI names
or source fields whose other uses remain unresolved.

`STARTUP_THREAD_MAP.md` and `INPUT_SAMPLE_TRACE.md` retain baseline identifiers
and baseline source pointers deliberately. The line numbers survive the first
batch. `batch_001.json` records meanings, evidence, scoped mappings, expected
token counts and original source hashes. `batch_001_validation.json` records
the applied substitutions, new hashes and inverse check. `verification.json`
records the independent build/ROM evidence.

Current cumulative ledger: `batch_009.json`. Batch 002 added three
piece-operation functions; batch 003 adds two game-side vector rotations
(four tokens in code_8170.c); batch 004 adds the four-component matrix
transform (six tokens); batch 005 adds the interpolated board grid and its
normal tables (four tokens); batch 006 adds three frame-orchestration names
(twelve tokens); batch 007 adds pause handling, framebuffer capture and the
game's screen-timer hook (ten tokens); batch 008 adds the audio settings
menu and save checksum/write request path (33 tokens); batch 009 adds the
records menu, ranked insertion and player-name packing pair (49 tokens),
for twenty-six function names and 138 substitutions across six source files. `ACTION_SAMPLE_TRACE.md` records the A/Z route;
`MATH_HELPERS.md` records rotation order, the light-direction caller and the
game/SDK boundary. `MATRIX_TRANSFORM_PAUSE.md` records the latest helper and
the earlier inverse-routine investigation. The user subsequently deferred
that routine and authorized other research; it is not an active blocker.
`BOARD_GRID_MATH.md` documents the base-position/layer-step grid and lighting
normal tables. `MAIN_FRAME_DISPATCH.md` follows the main-queue cycle, timing,
priority state dispatch and graphics/resource handoffs. `PAUSE_RESUME_TRACE.md`
follows Start, saved-frame transitions, menu ownership, resume input suppression
and independent screen timing. `AUDIO_SETTINGS_TRACE.md` follows live
audio adjustments, combined-controller input, direct resume from pause and
checksum/EEPROM persistence requests. `EXIT_RECORDS_TRACE.md` corrects the
save-prompt hypothesis: EXIT can insert a ranked record and display the
records menu before returning to the front menu. Current acceptance is in `batch_009_validation.json`
and `batch_009_verification.json`. The tool's
historical default remains batch 001; always pass the current ledger below.

## Build inputs and reproduction

Git does not contain every production build input. This worktree was populated
from the verified portable snapshot, adding only missing files and requiring
every existing selected file to match. `baseline_inputs.json` records all 997
selected inputs and executable modes, including generated assembly, assets,
linker inputs, stock IDO 5.3 and the SDK header subset. No build objects or
compiler patches were copied. The original portable directory is untouched.

A new checkout needs those missing inputs provisioned before verification.
Do not copy the portable README over the repository README. Do not run
`make extract` or `make distclean` against the supplied input snapshot.
Use the existing production Makefile, `docs/BUILD.md`, Linux ARM64 compiler
and GNU MIPS tools without flag changes.

The first clean build used `make -j4` in an empty build directory, then
`cmp tetrisphere.z64 build/tetrisphere.us.z64`. The unchanged baseline also
passed `./matchdiff.sh` plus header-inclusive `cmp` before any renames.
Build logs live in `work/semantic_*`; the retained summary is in this directory.

## Verify the semantic source

From the worktree root:

```sh
python3 -m unittest discover -s tools/semantic -p 'test_*.py' -v
python3 tools/semantic/identifier_renames.py --ledger analysis/semantic/batch_009.json
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
sha256sum tetrisphere.z64 build/tetrisphere.us.z64
```

Both ROM hashes must be
`f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.
The lexical validator does not claim to verify ROM behavior.

`--apply` without `--from-ledger` is only for the corresponding unrenamed
baseline, after the ledger has been reviewed. For an incremental batch, use
`--apply --from-ledger analysis/semantic/batch_001.json` with the next
cumulative `--ledger`. This verifies the previous tree, requires unchanged
baseline/input-manifest identity and retention of every prior mapping/count,
then verifies the next substitutions against the original baseline. Only
files receiving additional substitutions are written. It rechecks the
result after application. Without `--apply`, the tool is read-only (unless
an explicit `--report` path is supplied).

The checker preserves C comments, character/string literals, include header
names, preprocessing numbers, line splices, CRLF and every intervening byte.
It requires an injective rename mapping and no target-name token collision;
reverse substitutions must restore the baseline exactly. It rejects
unreviewed changes to production inputs or existing tracked files, unexpected
files under production input directories, symlinks, changed executable modes,
and staged content differing from the working files.

Limits: this is an ASCII C identifier scanner and byte guard, not a compiler
or binding resolver. It renames every matching identifier token in each
approved file, including macro tokens; manually inventory declarations,
references, macros, aliases and configuration first. It fails closed on
trigraphs, universal-character identifiers, split renamed identifiers and
some unusual directive syntax. Assembly/linker renames need a separately
reviewed lexical implementation; this first batch changes only C functions.

## Continuing

Keep batches small, with evidence and all affected source/configuration files
listed before editing. The current ledger is cumulative from the immutable
original baseline: extend it in a new version for future names, retaining all
earlier approved mappings. Use the verified previous ledger with
`--from-ledger` for incremental application; never restore source to the
original spelling as an intermediate step. The cumulative verifier checks
the final tree against the original.
Do not silently regenerate the original input manifest to accept drift.

Commit tooling/evidence separately from source-name batches. Stage only the
listed files, inspect the staged diff, and rerun the lexical check after
staging. A source change is accepted only with both `matchdiff.sh` and a full
ROM `cmp`, including the header. Do not merge this branch into canonical
`main` as part of routine research continuation.
