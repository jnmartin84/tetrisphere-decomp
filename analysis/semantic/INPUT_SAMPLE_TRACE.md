# One input sample: D-pad Left to board geometry

Recorded 2026-09-13. Read-only source investigation; no source substitutions.
References are relative to `/Users/jnmartin/landed_tsphere` at preserved
commit `823ca10873a7eafde7d68951087cdaf9d3095dfd`.
Canonical HEAD and tracked status were checked live and match the startup
pass. Package verification passed for all 1,032 files before this trace.

## Concrete path and assumptions

Follow a healthy connected controller assigned to the first active player,
pressing **D-pad Left alone**, after ordinary gameplay input buffering is
enabled. Assume no transition/pause/interruption gate, scripted-input override,
or alternate input provider, and initially clear directional repeat state.
These are explicit branch conditions for an example, not a captured runtime
session. `CONT_LEFT == 0x0200` and `CONT_B == 0x4000` are defined in
`include/PR/os_cont.h:123-129`.

```text
SI completion: boot.c func_80029938, message type 3
  controller.c func_8002AE0C
    osContGetReadData -> pad.button
    main.c func_8006DF3C(buttons, port)
      publish raw current/previous buttons into input-history row

main thread: func_800CCE7C -> func_80070118
  func_8006E98C drains completed history rows
    func_8006E418(currentRaw, previousRaw, port)
      func_800ACB94(currentRaw, previousProcessed, playerState)
        increment horizontal target; arm repeat countdown
        smooth target into fixed-point coordinate
        return effective buttons for next processed comparison

ordinary frame path: func_800CD3B8
  select player context -> func_800AF09C_p / func_800AF09C
  func_800ADD6C(previouslyLatchedFractionX, previouslyLatchedFractionY)
    generate per-player geometry-coordinate table
  later latch the newly smoothed input coordinates
  func_800A348C -> func_800A0ED8
    select wrapped board cells; copy table coordinates into Vtx
    emit vertex-load and triangle commands
```

## 1. Collection: raw input and a row still being filled

`boot.c:225-232` starts controller reads on retrace and handles their later
SI completions. `controller.c:38-50` retrieves `OSContPad` data and forwards
the `button` field for connected ports when `D_800DF778 != 0`. This traced
path does not forward analog-stick axes. Read-error substitutes are 0 or
`0x1000`; the example assumes no error.

`main.c:12095-12115` updates each port's raw current/previous globals.
For port 0, `D_800DFD68` becomes `0x0200`, and its old value is retained as
the previous raw sample. Port assignment is separate from player number:
`D_80113320` selects the first player's controller port.

When ordinary buffering is active (`main.c:12117-12168`), the worker stores:

- `D_800E1720[row][port]`: current raw buttons.
- `D_800E1CC0[row][port]`: previous raw buttons.

There are 180 rows and four ports. `D_800E1718` is the port whose arrival
advances the fill-row index `D_800E1714`; it is initialized from the first
port seen. At that advance, the new row is cleared. If it catches the
consumer, `D_800E1710` advances too, dropping the oldest row.

**The row currently being filled is excluded from consumption.**
`func_8006E98C` snapshots `end = D_800E1714` and loops while `cur != end`
(`main.c:12297-12306`). Thus a row becomes eligible when a subsequent
producer advance leaves it behind. The consumer may process multiple rows
per call, but stops at the captured end even if more input arrives meanwhile.
This establishes source ordering, not a fixed millisecond latency.

Transition guards and the `D_800E170C` countdown can instead publish direct
player button state and discard buffered history (`main.c:12117-12145`).

## 2. Routing: raw history and processed history are different

`func_8006E418(currentRaw, previousRaw, port)` first evaluates global and
player gates (`main.c:12194-12273`). Examples include a fresh Start press
and input that exits certain application states. Do not bypass these when
describing the ordinary path.

For the first active player, the actual call is (`main.c:12275-12277`):

```c
D_801125EC = func_800ACB94(arg0, D_801125EC, D_80110220);
D_801125EE = 0xFFFF;
```

So ACB94 receives the current raw sample, **the previous return value from
ACB94**, and the player's state object. It does not receive the previous raw
history word as its second argument. The latter was used by the routing
layer's edge tests. For our initial press, both previous values are zero.

The second player uses `D_80115854` and `D_80113488`. Mode value 6 also calls
the second player's handler with zero current buttons when processing the
first player (`main.c:12278-12284`); do not generalize to exactly one handler
call per physical port sample in every mode.

## 3. ACB94 is a control update, not merely a button decoder

Full function: `game2.c:13416-13868`. The example reaches the directional
branch with `unk1680 == 0`, `unk23A2 != 0`, `D_800E44FC == 0`, and
`D_801033D0 < 0`.

Before direction handling, the function can suppress input until release
(`+0x23D2`), mask A/Z or B (`+0x23AE/+0x23B0`), substitute a duration/button
stream (`+0x23BC..+0x23C8`), or obtain buttons from `func_800B2E94`
(`13439-13575`). The stream includes command sentinel words, so it is more
than raw pad playback. Those alternate paths are excluded from the worked
example and remain separate investigations.

For context number 1 (`+0x23B2 == 1`), each call increments `D_800E4484` and
`D_800E4478` (`13577-13579`). This happens before later early returns and is
not conditional on movement or any pressed button. The function also calls
`func_80081E90_u16(1)` (`13581`). No gameplay role for that call is assigned
by this bounded trace.

Directional handling (`13622-13718`):

| Button | Target change | Countdown / repeat-started fields |
|---|---|---|
| Left `0x0200` | `+0x2B28 += 1` | `+0x2458`, `+0x245A` |
| Right `0x0100` | `+0x2B28 -= 1` | `+0x245C`, `+0x245E` |
| Up `0x0800` | `+0x2B2C += 1` | `+0x2460`, `+0x2462` |
| Down `0x0400` | `+0x2B2C -= 1` | `+0x2464`, `+0x2466` |

Each direction steps only when its countdown is zero, then loads its delay.
The countdown decrements when that direction is present in both current and
previous processed buttons. Release clears both countdown and repeat-started
state. Direction tests are independent; do not assume opposite directions
are normalized before these branches.

`func_800905A4` supplies seven delay profiles (`game2.c:4755-4766`):

| Profile index | Initial delay `+0x2468` | Repeated delay `+0x246A` | B-held delay `+0x246C` |
|---|---:|---:|---:|
| 0 | 7 | 4 | 13 |
| 1 | 9 | 5 | 12 |
| 2 | 15 | 8 | 8 |
| 3 | 16 | 9 | 7 |
| 4 | 13 | 7 | 10 |
| 5 | 11 | 6 | 11 |
| 6 | 14 | 8 | 9 |

The profile argument is reduced modulo 7. Menu and state initialization
callers exist (`main.c:2715,3638,3645`, `game2.c:14675`), but their character
labels are not established here. B selects a distinct delay, not universally
a faster one.

For profile 0, consecutive processed Left samples starting at zero repeat
state behave as follows. This is arithmetic derived from the source, not
an emulator or hardware trace:

| Processed sample | Step this call? | Net target change | Countdown after call |
|---|---|---:|---:|
| 1 | Yes | +1 | 7 |
| 2 | No | +1 | 6 |
| 7 | No | +1 | 1 |
| 8 | No | +1 | 0 |
| 9 | Yes | +2 | 3 |
| 12 | No | +2 | 0 |
| 13 | Yes | +3 | 3 |

On sample 9 the repeat delay loads as 4 and decrements to 3 in the same
call. The first press does not decrement because the previous buttons did
not include Left.

An accepted movement calls the audio request wrapper `func_8007D45C` with
ID `0x2C`, or `0x1B` while B is held (`game2.c:13825-13835`). The wrapper is
gated by `D_8010B7C4` (`audio_engine.c:1595-1599`), so this is an attempted
audio request, not proof that a sound plays. Exact audible identities remain
unassigned.

ACB94 also advances other persistent control values and damped motion state
(`13769-13867`) before returning effective buttons. The no-movement case can
still perform these updates.

## 4. Target steps become smooth fixed-point movement

At `game2.c:13765-13768`, each axis applies the following integer expression
(semantic notation only):

```text
smooth += ((target << 8) - smooth + 0x80) / 16
coarse = (latchedSmooth >> 8) & 31
```

Horizontal target/smooth/latchedSmooth/coarse are respectively
`+0x2B28`, `+0x2B40`, `+0x2B48`, `+0x2B18`; vertical counterparts are
`+0x2B2C`, `+0x2B44`, `+0x2B4C`, `+0x2B1C`.
Integer division truncates as in the C source; retain the `+0x80` bias.
The coarse index comes from the older latched value, not this call's updated
smooth value.

One initialization path uses target `0x400000` and smooth
`(target << 8) + 0x80` (`game2.c:5406-5423`). Using that baseline for the
example, the first Left step changes target to `0x400001` and smooth from
`0x40000080` to `0x40000090`: a change of 16 in a scale where 256 is one
target unit. The next held sample, without another target step, changes
smooth to `0x4000009F`. This is gradual movement on each processed control
update, rather than an immediate geometry jump to the next whole coordinate.

## 5. Where those values reach rendered geometry

`func_800CD3B8` selects a player context at `game2.c:26395-26397`.
`func_800AF09C_p` aliases `func_800AF09C`
(`undefined_syms.txt:332`), which selects both `D_8013DD00` and the player's
geometry-table pointer `D_800E44E4` (`game2.c:14720-14753`).

The relevant order within a player's frame processing is:

1. At `26428`, pass the fractional parts of the **previously latched**
   coordinates to `func_800ADD6C`: horizontal is complemented within its
   low byte, vertical uses its low byte directly.
2. `func_800ADD6C` (`13964-14063`) interpolates table-driven 3D coordinates
   into `D_800E44E4`: a 16-by-16 grid, six signed halfwords per grid point.
   It also applies conditional scale and two-player offsets. Fractional
   movement therefore changes the actual coordinates later used for vertices.
3. At `26661-26666`, copy smooth coordinates to their latched fields, coarse
   indices to `+0x2B20/+0x2B24`, and targets to `+0x2B30/+0x2B34`.
4. At `26881-26883`, `func_800A348C` builds board graphics. Among its passes
   it calls `func_800A0ED8` (`10363-10400`).
5. `func_800A0ED8` walks a 15-by-15 window, using the coarse indices to look
   up wrapped 32-by-32 board positions (`9747-9754`). For eligible occupied
   cells, it reads the geometry table (`9758-9770`), writes `Vtx.v.ob`
   coordinates (`9817-9845`), and emits vertex-load and triangle commands
   (`9807-9815`).

This closes one concrete chain from D-pad bits to vertex positions and board
cell selection. The fractional geometry for a given build precedes the
new latch, so it uses earlier state. The coarse index also has its own
capture order. Do not flatten these into one immediate coordinate update,
or infer a universal one-frame/end-to-end latency: input row completion,
sample batching, frame-slot availability, other render passes and VI swapping
are additional boundaries.

## Semantic conclusions and remaining boundaries

- High confidence: raw per-port state, fill/consume history indices, previous
  processed buttons, four directional repeat pairs, delay profile roles,
  target/smoothed/latched coordinate stages, and board-geometry data flow.
- Strong inference: `+0x2B28/+0x2B2C` are horizontal/vertical board-view
  targets. Their directional signs, wrapping, and rendering uses establish
  this more narrowly than generic camera-angle or cursor-screen-position
  names. No source field names have been changed.
- `func_800CD3B8` combines gameplay-state progression and rendering. Calling
  it only a renderer would miss the state changes visible in this trace.
- The A/Z action branch at `game2.c:13722-13760` arms action state, and
  `func_800CD3B8:26470-26579` consumes that state into operation records.
  This is a useful next concrete sample to trace; exact action names and
  record semantics are deliberately not assigned from masks alone.
- B also sets state consumed by `func_800954FC` (`13825-13842`,
  `26711-26724`). Its complete board-operation semantics are outside this
  Left-only sample.

No rename batch or build was performed. This note refines the startup map:
the input ring excludes its current fill row, and raw-previous input is
distinct from the previous processed buttons passed to ACB94.
