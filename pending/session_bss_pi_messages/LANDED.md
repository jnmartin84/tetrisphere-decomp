# PI and DMA message storage restored to C

Baseline: `bd7eac3738d4a3bfad4d876a9e932443e745d731`.

`src/pi_state.c` supplies four typed objects spanning exactly
`0x800FA848..0x800FABB8` (880 bytes):

| Address | Definition | Purpose |
| --- | --- | --- |
| `0x800FA848` | `OSMesg D_800FA848[200]` | PI manager command-message buffer |
| `0x800FAB68` | `OSMesgQueue D_800FAB68` | PI manager command queue |
| `0x800FAB80` | `OSMesgQueue D_800FAB80` | DMA completion queue |
| `0x800FAB98` | `OSMesg D_800FAB98[8]` | DMA completion-message buffer |

`idle` passes the first buffer/queue and capacity `0xC8` to `osCreatePiManager`.
`initScheduler` configures the completion queue with capacity eight.
`dmaRomToRam`, `dmaRomToRamAsync`, and `dmaReady` use that queue for completion
notification. These consumers already declare the same SDK types. Names and
all function-source bytes are unchanged.

The new storage-only C object emits no instructions and reserves exactly 880
bytes, with object offsets `0`, `0x320`, `0x338`, and `0x350`. This grouping is
a recovery convenience, not a claim about original translation-unit boundaries.

## Exact split boundaries

The recovered interval starts and ends eight bytes off a 16-byte boundary.
The surrounding raw reservations therefore need exact lengths:

- `game_bss_before_pi`: `0x800F2290..0x800FA848`, size `0x85B8`.
- `game_bss`: `0x800FABB8..0x80127CF0`, size `0x2D138`.

Their selected assembler rules use `-no-pad-sections`, an existing build
mechanism, so splitting the original assembly does not round either fragment
up to a multiple of sixteen. IDO flags and output are untouched. The existing
linker's `SUBALIGN(4)` preserves the C allocation's linked start at
`0x800FA848` even though the input object requests alignment sixteen; the
actual addresses satisfy the SDK types' alignment requirements.

## Verification

Pristine isolated and candidate builds passed `./matchdiff.sh`. All ROM bytes,
including the header, match. All allocated ELF section layouts and existing
BSS symbol addresses remain unchanged. No symbols or instructions were added.
Each object has the exact expected size and actual C-owned linked storage.
The compiler emits no extra padding within the 880-byte interval.

After building, run without Python's `-O` option:

```sh
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
python3 pending/session_bss_pi_messages/verify.py
```

This runs all prior BSS checks and checks the typed objects, absence of address
aliases, lack of instructions, and both raw fragment lengths. The EEPROM
baseline now also retains the exact removed PI assembly text; reconstructing
the original game block still matches its original hash. Existing baseline
hashes were not replaced. Binary artifacts remain untracked.

Linker and YAML ownership entries have been updated. Complete splat
regeneration remains an untested research operation, as before this change.
Other game BSS remains for future recovery.
