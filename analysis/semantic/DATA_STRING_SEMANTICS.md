# Data vocabulary from diagnostics

Read-only study, 2026-09-13; current source `/Users/jnmartin/landed_tsphere`
at e56cdd8, clean. No source changes. `DATA_STRING_EVIDENCE.json` records 14
selected named literals verified against original ROM bytes. User handles GitHub
pushes; do not infer remote state from earlier local landing notes.

## Direct field labels: audio sample metadata

`src/audio_engine.c:2146` defines a provisional 16-byte `StructE784`.
`func_8007E784` at line 2158 prints its members through five labelled formats:

| Offset/member | Type | Literal vocabulary | Symbol |
| --- | --- | --- | --- |
| +0x00 / unk0 | u32 | smplen (decimal and hex) | D_800EE41C |
| +0x04 / unk4 | u32 | loopBegin | D_800EE3FC |
| +0x08 / unk8 | u32 | loopEnd | D_800EE40C |
| +0x0C / unkC | u16 | flags | D_800EE3F0 |
| +0x0E / unkE | u16 | Sample ID | D_800EE42C |

These are strong scoped member-name candidates. Sample-length and loop-position
units and individual flag bits remain unverified. No incoming production C call
to func_8007E784 was found; this is retained diagnostic code, not evidence of
visible runtime output. The formatted sink func_80029760 is empty. Do not claim
the complete data format or identify a matching record elsewhere merely by size.
`StructE784` could receive a descriptive sample-metadata name, but the literal
does not preserve an original type name. Other structs' unk0 etc. are unrelated.

## Direct player-state counter labels

`src/game2.c:5291` passes two s16 fields under D_8013DD00 to
`DropPieces: %d PiecesLeft: %d` (D_800F0434). Line 5305 prints a third field under
`Number of Display Pieces: %d` (D_800F0454):

| Player-state offset | Diagnostic vocabulary |
| --- | --- |
| +0x25C6 | DropPieces |
| +0x25C4 | PiecesLeft |
| +0x321A | Number of Display Pieces |

The first two are unpacked from the low/high 16 bits of a loaded puzzle value;
the third is initialized from +0x25C6. This makes them stronger naming evidence
than proximity alone. Counter meanings across all modes still warrant use-site
review. Numeric offset accesses cannot become named fields under an
identifier-only policy without an existing scoped member declaration to rename.

## Named audio-player instances

`src/audio_engine.c:424` and the STOP path at line 454 choose diagnostic strings
by comparing the supplied manager address:

- D_80108828: ANIMPLAYER.
- D_80109DC0: ANIMPLAYER2.
- Remaining branch: DCMPLAYER. D_80107290 is a confirmed caller reaching this
  branch (e.g. src/boot.c:294 and :310), and audio.c:99 initializes it alongside
  the two animation-audio managers.

These are audio manager instances, distinct from the LW geometry animation
runtime. The fallback alone does not prove every other pointer denotes DCMPLAYER.
The message packet D_80104BF0 has an s16 command at +0 (1 PLAY, 0 STOP) and a
manager pointer at +4, corroborated by the queue submission immediately afterward.

## Blank-piece record

In `src/game2.c:17289`, a cube lookup is compared with the first s16 at
D_8013F348; the rejection message says
`Alloc_DelayedPopCubes: _BlankPiece.CubeName... returning` (D_800F0AA4).
D_8013F348 is also inserted into a piece-pointer table at lines 2503 and 2528.
This strongly supports a blank-piece record at that address with CubeName at +0.
Its complete layout and all aliases remain to be checked before a global rename.

## Useful but less direct clues

- `Setting GravDropPiece to TRUE` at game2.c:14884 accompanies both player-state
  +0x24A6 and +0x24B4 being set to 1. +0x24A6 is tested before this transition;
  other code tests it >=2 (line 26470), so it is not safely described as a simple
  Boolean. Do not assign the string to both fields or assume which spelling wins.
- `Setting QuestAnimActive.` at game2.c:22272 sits between setting phase +0x1680
  to 5 and D_801309EE to 1. The global is a strong candidate: the phase-5 helper
  func_800C2E34 gates its transition on this global being zero. Still distinguish
  the global active flag from the phase selector.
- `Make XCount 21!!` precedes setting player-state +0x321C to 21 in the AI
  strategy routine (game2.c:16477). The same field is initialized to 6, and a
  computed count is compared with half of it. This indicates an AI X-count
  target, not necessarily the player's current X-count.
- `Setting AI_MaxCores for: %d` prints the player identity at +0x23B2; it does
  not directly print AI_MaxCores. Nearby +0x3224 copies a core-related value,
  but that assignment needs separate tracing. Avoid naming the printf argument
  AI_MaxCores from the message prefix.

## Suggested next bounded batch

The sample-metadata members and the two explicit animation-audio manager globals
offer strong identifier-only candidates after declaration/alias checks. The
counter offsets and blank-piece record are useful structure notes; do not turn
raw offsets into new expressions or reconstruct structs in a naming-only batch.
