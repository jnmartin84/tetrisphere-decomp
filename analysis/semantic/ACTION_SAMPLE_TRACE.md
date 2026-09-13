# A/Z sample to a timed piece operation

Recorded 2026-09-13 against original baseline
`823ca10873a7eafde7d68951087cdaf9d3095dfd` and semantic branch batch 001.
Source pointers below use `src/game2.c` unless stated otherwise. Identifier
renames preserve physical line numbers. This is static source evidence;
numeric modes, flags and player-state fields remain unrenamed.

## From the controller to action arming

The previously traced route is controller/Eeprom worker ->
`readAndDispatchControllerData` -> button ring ->
`processBufferedControllerSamples` -> `func_8006E418` -> `func_800ACB94`.
The last function sees effective current buttons after its input guards and
stream overrides; its second argument is the previous processed button mask
retained by the caller (`src/main.c:12194-12286`). See INPUT_SAMPLE_TRACE.md.

`include/PR/os_cont.h:122-143` defines A=0x8000 and Z=0x2000. In the
normal enabled route, `game2.c:13722-13760` tests
`(buttons & 0xA000) && !(arg1 & 0xA000)`. This is one grouped edge: either
button is down now and neither was down previously. Holding Z while newly
pressing A does not meet this fresh-edge condition.

The route additionally requires +23A4 nonzero, +23AE zero and +24B6 zero,
within the earlier movement/input gates. The +2416 >= 30690.0 path can
also request an action without a fresh edge. D_800DFD4C==2 takes a distinct
path; do not generalize the normal action to every game mode.

On the ordinary fresh edge (D_800DFD4C!=2), the function writes:

| Player offset | Observed assignment / bounded meaning |
|---|---|
| +24B2 | 0x5595, pending operation flags |
| +24B4 | 0 for the fresh button path; 1 for the threshold path |
| +24AA | Selected entry from +2374 |
| +24AC, +24AE | `(targetX + 7) & 31`, `(targetY + 7) & 31` |
| +24B0 | 8, initial layer value |
| +2B5C | 1 |
| +23A4 | 0, closes this arming gate |
| +1E6 | 0 |
| +24A6 | 1 when this action is newly armed |

The targets are +2B28/+2B2C, not the smoothed +2B40/+2B44 values or their
later display latch. The smoothing update follows this block. An action
therefore captures discrete target coordinates even while the view is moving.

## Converting pending state into an operation

At function entry, ACB94 increments +24A6 if it is nonzero (13436-13438).
The consumer in `func_800CD3B8` requires +24A6 >= 2 **or an already active
operation**, and +24BA == 0 (26470). It also has mode/resource gates.
This is not a fixed one-frame latency: the counter advances with processed
input calls, several of which can be drained during one update. Existing
operations can satisfy the alternate gate even with a newly armed counter.

When pending flags have either low bit set, the consumer allocates a slot
(26478-26480), copies the pending entry/flags/coordinates/layer into it,
ORs flags with 0x20, clears the pending flags, and sets delay to 10
(26496-26505). Thus the ordinary 0x5595 request initially becomes 0x55B5.

There is a branch when +3232 == +2374 that queries the board at pending
coordinates plus one. `func_8008A9C4` reads the low nibble of the wrapped
32x32 column table (3251). `func_80093214` decodes the cell's piece entry
and recovers its wrapped origin from its 3x3 template (5843-5880).
The consumer can replace the pending entry and origin with those values;
an empty/invalid result takes a distinct failure route. Therefore the
selected pending entry is not invariably the entry stored in the operation.

Entries whose template ID is 0x20..0x26 additionally decrement +25C6,
increment +2C80 and call `func_800C0308` (26523-26529). That helper
initializes an animated object at state +668..+67C (20850-20889).
Its full visual meaning is not established here. Other valid template IDs
1..7 take another route. Exact game-mode and template-category names remain
open.

## The operation table and its driver

The current player context is D_8013DD00. Its +25CC table consists of 64
normal slots, each 0x14 bytes. +25CA counts active operations.

| Slot offset | Evidence-supported role |
|---|---|
| +0 | Active marker |
| +2 | Slot index |
| +4 | Piece/template entry index |
| +6 | Operation flags |
| +8 | Remaining delay |
| +A, +C | Wrapped board origin |
| +E | Layer |
| +10, +12 | Additional state; flags/context need a wider audit |

`func_800920E4` (5437-5448) activates a chosen slot, records its index,
and clears the payload. `func_800921A8` (5455-5466) searches indices
0..63 for the first inactive slot, increments the count, initializes it
and returns its index. Exhaustion logs and returns 64. The A/Z consumer
does not explicitly check that return, whereas the callers at 6118 and
14869 do. Preserve this behavior; the table's overflow contract is not
being repaired or inferred from the allocator alone.

This is an indexed operation pool, not a FIFO. Other producers include
`func_80093C08` (6118-6134), which fills a record and can reject a duplicate,
and `func_800AF424` (14825-14898), which discovers affected pieces and
schedules records with flags 0x408. The pool extends beyond fresh input.

The consumer visits slots in index order (26548-26579). For each active
slot it subtracts D_80160C64 from the delay. When delay <= 0 and flags are
nonzero, it calls `func_8009423C`; the return becomes the next delay.
Do not call this delay milliseconds or render frames without tracing that
delta's source and scheduling.

The driver (6288-6546) interprets the flags, changes operation and board
state, and can schedule subsequent steps. Examples: bit 1 recomputes layer
from the piece footprint; bit 0x4000 reopens +23A4 and clears +2B5C;
the bit-8 path can move a piece down one layer and return 10. Other routes
return 15 or a computed delay, or clear the flags and return zero.
The action gate can therefore reopen before all operations are finished.
The exact meanings of the full flag word are deliberately left unresolved.

When flags are zero and delay <= 0, the consumer releases the slot through
`func_80092238_p`. The underlying `func_80092238` (5469-5481) deactivates
it and decrements the count; when releasing the final active slot it also
clears +24A6/+2B5C and reopens +23A4. The fixed-address `_p` alias is left
unchanged along with its target name in this batch.

## Batch 002 naming decisions

| Original | Applied name | Confidence |
|---|---|---|
| func_800920E4 | initPieceOperationSlot | High |
| func_800921A8 | allocatePieceOperationSlot | High |
| func_8009423C | advancePieceOperation | High |

These names describe the observed shared lifecycle without assigning a
single game-mode meaning to it. Inventory of all 997 production inputs
finds the names only in game2.c, including historical comments; none of the
proposed names preexists. Nine C identifier tokens change: 2 + 5 + 2.
Comments retain original spellings. See batch_002.json and its validation
and build evidence for acceptance; this research note alone is not a gate.

Next bounded trace: follow the initial 0x55B5 operation through its bit-4
branch into `func_800C84C8` / `func_800C2848` to identify the board mutation
and connected-piece tests, or trace the separate B-held operation route.
