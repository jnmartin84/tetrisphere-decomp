# ROM strings: animation memory and subsystem names

Read-only study, 2026-09-13. Source inspected in
`/Users/jnmartin/landed_tsphere`, clean at `fc38500`. No production source
changes or new matching claims. The previous progress/profile candidates remain
notes-only in `PROGRESS_PROFILE_TRACE.md`.

The user recalled an allocator-related string from an earlier ROM extraction.
The strongest candidate found here is **`detected by LWAllocateMemory`**.
This is a plausible match to the recollection, not proof of which string the
user saw previously.

## Evidence and confidence

`ROM_STRING_LW_EVIDENCE.json` records all 38 diagnostic strings in this cluster,
their symbols, ROM offsets, assembler lines and unique diagnostic call sites in
`src/code_8170.c`. Every string, including its NUL terminator, was checked against
the local original ROM, not just the assembler text.

- ROM size: 8,388,608 bytes.
- SHA256: `f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.
- String region: ROM `0xC6E30` through the literal starting at `0xC7268`;
  assembler `asm/data/C6370.data.s:1025` onward.
- This is a selected diagnostic cluster, not a complete ROM string census.

| Current function | Original routine name supported by diagnostics | Confidence |
| --- | --- | --- |
| `func_8002CF70` | `LWAllocateMemory` | High: nine problem/detector pairs within the function |
| `func_8002D93C` | `LWPlayAnimation` | High: ten problem/detector pairs within the function |

`LWPlayAnimation` was already hinted in an existing source comment. The ROM
strings and direct call sites independently corroborate it. The expansion or
vendor provenance of `LW` remains unknown; do not infer it from the prefix.

## What LWAllocateMemory actually allocates

`src/code_8170.c:131` takes a destination address, an animation stream, an array
of geometry-stream pointers, the geometry-stream count, and an output byte-count
pointer. These parameter roles follow from the operations and caller behavior.

It partitions caller-provided contiguous memory into an animation runtime
instance. It reserves a `0x278`-byte header, aligns successive regions to 16 bytes,
and installs pointers to light arrays, light information, object information,
geometry descriptors, per-geometry index lists, and material-light arrays. It
initializes the instance, retains the stream pointers, returns the instance
address, and writes the consumed byte count through its fifth argument.

The stream contents determine allocation sizes. Animation-header offsets `+4`
and `+8` locate blocks whose first words supply counts. The corresponding runtime
regions include two `countA * 16` light arrays, `countA * 0x34` light information,
and `countB * 0x120` object information. Geometry descriptors occupy eight bytes
per stream. Exact element types and the complete runtime structure remain to be
recovered; current `Pool`, `Heap`, `Blk` and similar typedef names are provisional.

The checks explicitly complain about overwriting `animStream` or `geomStream`,
unaligned stream/destination addresses, invalid pointers, and a bad address after
allocation. They do not establish general bounds safety: no destination capacity
is passed, and the overlap checks inspect the starting destination address.

Concrete ownership evidence: `src/game2.c:18489`, `func_800B8DF0`, aligns the game
arena cursor `D_8013E474`, checks a `0x4000` margin against `D_800FC5AC`, calls
`func_8002CF70`, then advances the cursor by the returned byte count. It sets
animation flags and stores the resulting instance in a gameplay record.

Thus the useful call-flow model is:

```text
gameplay animation setup: func_800B8DF0
    align/check game-owned arena cursor
    LWAllocateMemory: func_8002CF70
        lay out and initialize animation instance in supplied storage
        report bytes consumed
    advance game-owned arena cursor and retain instance

animation playback: func_8002D93C / LWPlayAnimation
    validate that instance and its internal pointers
    advance animation state and invoke transform/display-building helpers
```

Other allocation call sites include menu/character preview setup in
`src/main.c:2665`, pause-related instances at `src/main.c:1888`, and results setup
at `src/main.c:6918`. This subsystem is used beyond one gameplay effect.

## Field vocabulary recovered from LWPlayAnimation

At `src/code_8170.c:390`, each pointer check supplies a literal naming the thing
being checked. These establish vocabulary and offsets, without requiring guesses
from arithmetic alone. They do not prove exact original C member spellings/types.

| Offset within runtime instance | Diagnostic vocabulary | String symbol |
| --- | --- | --- |
| Instance itself | `LWInfo` | `D_800EBC94` |
| `+0x00` | `lights[0]` | `D_800EBD74` |
| `+0x04` | `lights[1]` | `D_800EBDAC` |
| `+0x08` | `materiallights[0]` | `D_800EBE54` |
| `+0x0C` | `materiallights[1]` | `D_800EBE94` |
| `+0x10` | `lightinfo` | `D_800EBDE4` |
| `+0x14` | `objectinfo` | `D_800EBE1C` |
| `+0x18` | `geom info` | `D_800EBCC8` |
| `+0x1C` | `animStream` | `D_800EBD3C` |
| Geometry descriptor `+4` | `geomstream` | `D_800EBD00` |

The geometry descriptor count is read at instance `+0x20`. Playback toggles byte
`+0x3D`; advances via `func_8002F55C` according to its integer second argument;
updates the counter at `+0x24`; and compares that counter against animation-header
`+0x0C` to return completion. A first call with counter zero and advancement zero
still invokes the advancement helper once. The paired storage and toggle suggest
alternating buffers, but full producer/consumer tracing is needed to assign the
toggle's exact meaning. The third and fourth playback parameters feed downstream
transform helpers; keep their exact types/names unresolved for now.

## Diagnostic calls versus visible output

The LW checks call `func_8002AF20` (`src/code_62D0.c:28`). It truncates diagnostic
strings, lowercases the problem text, formats a global error buffer, sets an
error flag, calls `rmonPrintf`, flushes the data cache, and writes through
`D_800DFD34`. That pointer is initialized to zero in the data section, and no
assignment to it was found in the source search. This is consistent with a fatal
error path; actual on-screen handling has not been traced here.

By contrast, the ordinary formatted diagnostic sink `func_80029760`
(`src/boot.c:75`) has an empty body. Its caller strings still provide naming
evidence, but do not imply visible logging in the shipped game. Count actual call
sites separately from declarations, comments, and matching-only address anchors.

## Other promising original-name anchors

These were located during the initial string scan and are candidates for the next
bounded trace. They are separate from the ROM-byte-verified LW evidence ledger.

| String vocabulary | Current function / location |
| --- | --- |
| Memory available/used by `InitPlayScreen` | `func_80073290`, `src/code_4D170.c:515`; `D_800EDF70`, `D_800EE010` |
| `generatelevel.c -> CopyLevelPuzzle` | `func_8008E94C`, `src/game2.c:4296`; `D_800F02BC` |
| `piececontrol.c .. AllocDropPiece` | Already named `allocatePieceOperationSlot`, `src/game2.c:5455`; `D_800F04CC` |

The last example can refine the vocabulary of an earlier semantic name. Do not
automatically overwrite accepted names without a deliberate naming decision.
Audio heap diagnostics also exist; allocation-related strings need their callers
traced before assigning them to this graphics-animation subsystem.

## Restart / next step

No renames have been applied. The two LW function names are strong candidates for
a later identifier-only, whole-ROM-verified batch. Before broader field naming,
trace the light/object/material consumers starting from `LWPlayAnimation`, keeping
the original diagnostic vocabulary distinct from inferred C layouts and names.
