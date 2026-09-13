# GBI restoration: beginGraphicsFrame

Accepted 2026-09-13 against published source commit
`a4c3cbe0012567925c7bb9a491283bad9694e9eb`.

The user explicitly requested one function with moderate raw `gCmd` use to be
restored to SDK GBI macros while preserving the ROM match. This is a separate,
authorized expression change, outside the earlier identifier-only rename batches.

## Scope and command meanings

`src/game2.c:26171`, `beginGraphicsFrame` (formerly `func_800CCB78`), occupies
linked addresses `[0x800CCB78, 0x800CCE6C)`, 0x2F4 bytes. All 18 raw calls were
replaced on their original physical lines, 26181 through 26198. Every other byte
of the source file remains unchanged. Existing SDK headers, build flags, argument
evaluation order, pointer advancement and command ordering are retained. The
now-unused local `gCmd` definition/undef remain to preserve surrounding layout.

Mappings use the actual `include/PR/gbi.h` compiled by this project:

| Calls | Original words (W0 / W1) | Restored operation |
| --- | --- | --- |
| 1 | `BC000006 / 0` | `gSPSegment`, segment 0, base 0 |
| 2 | `BC000406 / physical(D_800DF75C)` | `gSPSegment`, segment 1 |
| 3 | `BC000806 / physical(arg1)` | `gSPSegment`, segment 2 |
| 4, 18 | `06000000 / D_1000010` | `gSPDisplayList` |
| 5, 17 | `06000000 / D_1000030` | `gSPDisplayList` |
| 6 | `FE000000 / physical(D_80000400)` | `gDPSetDepthImage` |
| 7, 13, 15 | `E7000000 / 0` | `gDPPipeSync` |
| 8 | `BA001402 / 00300000` | `gDPSetCycleType`, `G_CYC_FILL` |
| 9 | `B900031D / 0` | `gDPSetRenderMode`, `G_RM_NOOP`, `G_RM_NOOP2` |
| 10 | `FF10013F / physical(D_80000400)` | `gDPSetColorImage`, RGBA, 16-bit, width 320 |
| 11 | `F7000000 / FFFCFFFC` | `gDPSetFillColor` |
| 12 | `F64FC3BC / 0` | `gDPFillRectangle`, `(0, 0)` through `(319, 239)` |
| 14 | `FF10013F / physical(*(arg0 + 0x1910))` | `gDPSetColorImage`, RGBA, 16-bit, width 320 |
| 16 | `BA001402 / 0` | `gDPSetCycleType`, `G_CYC_1CYCLE` |

Here `physical(...)` abbreviates the unchanged `osVirtualToPhysical` calls;
the table's offset notation abbreviates the actual typed source expression.

The sequence clears the depth buffer by temporarily selecting it as the color
image and issuing a full-screen fill, then selects the frame's color buffer.
Each 16-bit half of `0xFFFCFFFC` is `GPACK_ZDZ(G_MAXFBZ, 0)`; the fill value stays
literal in source. `G_MAXFBZ` (0x3FFF) is distinct from viewport `G_MAXZ` (0x03FF).
The two nested display lists were not decoded in this experiment.

These are matching SDK spellings for the commands, not proof of the exact macro
aliases or source spelling used by the original developers.

## Verification

Fresh isolated checkout, native macOS ARM64, official IDO 5.3 v1.2, GNU MIPS
binutils 2.47, unchanged production flags (`game2.c`: `-O2 -g0 -mips1 -32`).

1. Before editing: fresh `PATH=/opt/homebrew/bin:$PATH make -j4` and full `cmp`
   passed against the reference ROM.
2. All 18 replacements passed on the first build with
   `PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh`: `FULL MATCH`.
3. `cmp tetrisphere.z64 build/tetrisphere.us.z64` passed, including the header.
4. The entire `build/src/game2.o` is byte-identical to its fresh baseline object.
5. A byte comparison against Git verified that only the 18 command lines changed;
   the source prefix, suffix, all other lines and total line count are identical.

Reference and restored ROM: 8,388,608 bytes, SHA-256
`f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.

Both baseline and restored `game2.o` SHA-256:
`b8a7c46805ea00a348d2e32468343b95cc3fee839e14f40259f819a10ee8a631`.

Baseline `src/game2.c` SHA-256:
`38c9959a9aa4e2e969b8e5ee71cf482220bc93fac12369273967e1380e29262c`.

Restored `src/game2.c` SHA-256:
`87c55703955efd29655b928d57c06ade2bc6735b795c3950c5a56170b7a62108`.

No compiler, header, linker, object patch or instruction repair was introduced.
This result validates this function; variable-field and multi-command macros in
other functions still require their own matching experiments. The baseline
distribution manifest and historical rename ledgers remain unchanged.
