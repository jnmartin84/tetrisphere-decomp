# Main thread: frame dispatch, timing and resource transitions

2026-09-13. Original baseline 823ca10873a7eafde7d68951087cdaf9d3095dfd;
batch 006 extends semantic HEAD 5042d43. This follows the main-thread
backbone rather than an isolated leaf. All line numbers survive renaming.

## Frame sequence

```text
mainproc: wait for a main-queue message
  if tracked pending tasks < 2:
    buildAndSubmitGraphicsTasks(frame records)
      choose slot; capture accumulated gameplay count; reset accumulator
      updateAndBuildFrame(matrix workspace, frame record)
        processBufferedControllerSamples()
        advance RNG; remember current/previous frame-record pointers
        beginGraphicsFrame(frame record, matrix workspace)
        func_8003E724(): button edges, directional repeat, UI feedback
        priority screen / transition dispatch, or:
          func_8006F52C(): ensure gameplay resources
          background / animation
          func_800CD3B8(): per-player gameplay and render processing
          overlays / fades
      append full-sync/end commands; fill graphics task and account it
    send newly built tasks to scheduler
  account received completion or PRENMI
```

The main-queue receive and refill precede message dispatch
(boot.c:295-310). A completion received when the pending count is two is
therefore accounted only after the refill check; that iteration does not
immediately refill the just-completed slot. Another receive permits a build.
The separate func_8002A218 loop has the same ordering (355-379); it is
called from code_62D0.c:197. It is not a second newly created thread.

## Task building and ownership

`func_800CCE7C` -> **buildAndSubmitGraphicsTasks**, game2.c:26251-26321.
It snapshots the initial pending count and slot selector into locals and
uses that initial count to decide how many records to build. In ordinary
steady operation this replenishes the two-slot pipeline. Nested resource
waits can consume completion messages during a build, so do not assume the
global pending count stays equal to the local loop counter throughout.

Records have stride 0x1918. The workspace passed to the frame dispatcher is
record+0x68; the actual display-list start comes from record+0x18E8. After
the dispatcher returns, the builder optionally appends an overlay, appends
RDP full-sync and display-list end commands, sets up Fast3D task metadata,
completion queue/message, framebuffer and cache writeback. It toggles the
slot and increments both built-task and pending-completion counts.

Only after all locally scheduled builds does it send their task pointers
to D_800FE178. osSendMesg uses literal 0 (nonblocking) and its result is
ignored. Preserve this exact contract; the semantic name does not assert
successful submission under every hypothetical queue state. The pending
count includes completions not yet consumed, not just hardware work.

`func_800CCB78` -> **beginGraphicsFrame**, game2.c:26171-26199.
It selects display-list and vertex cursors, sets segment commands, clears
the depth-buffer storage and selects the record's framebuffer as color
output. It is also called by func_8006EAD8 after repartitioning graphics
storage (main.c:12331-12338). Thus initialization can restart during a
resource transition; it is not proof of a separate presented frame.

## Timing is coupled to input processing

Before invoking the dispatcher, the builder copies D_800E4484 into
D_80160C64 and D_80160C60, with a mode-4 cap of five when the captured value
is at least six, then clears D_800E4484 (26267-26275).

The dispatcher then drains input. func_800ACB94 increments D_800E4484 and
D_800E4478 for player context +23B2==1 (13577-13580). This happens regardless
of whether a button is pressed when that processing path is reached;
earlier routing gates can bypass ACB94. It is not a button-press count.

Consequently the captured count is not a count of the input samples about
to be consumed by this same build. New samples can update controls now and
accumulate timing for a later build. If the builder creates two tasks, the
second capture may see the count produced during the first dispatch. A
capture of zero is possible; no minimum clamp occurs here. Initialization
seeds all three counters to one (26100-26102). Avoid labeling this delta
milliseconds, VI retraces, or a universal one-tick-per-render-frame clock.

The UI path is different: func_8003E724 snapshots four current button words,
computes aggregate and per-port presses/releases, and generates directional
repeat from counters advanced on each call (main.c:1269-1523). D-pad and
C-direction repeat pulses occur when the counter is >=13 and even. The
fresh press sets it to one and the same call increments it. It also updates
arrow-highlight state, a pulse value and an inactivity counter. Its complete
role deserves a broader name than just a button-edge calculator; it remains
unrenamed. This is separate from gameplay's buffered per-sample repeat logic.

## Priority state dispatch

`func_80070118` -> **updateAndBuildFrame**, main.c:12758-13303.
It drains input and performs graphics/button setup before testing these
branches, in source order:

| Gate | Route / observed consequence |
|---|---|
| D_800E11F8 | Shared screen setup, then func_8005C410; PRENMI can activate this gate |
| D_800DFD40 | Shared screen setup, then func_80064EBC |
| D_800E1646 == 0 | Shared screen setup, then func_800685FC |
| D_800DFE8C | Initializes a specific mode-3 state and clears D_800E121C; this branch itself does not return |
| D_800E121C >= 0 | Shared screen setup, then func_8004C7E8 |
| D_8013FAD0 | Start/pause path, shared setup then func_8003FE3C; returns |
| D_8013FAD4 | Multi-stage completion/progression flow, mode-dependent screens and resets |
| D_8013FAD2 | Multi-stage outcome/rematch flow, per-player results and counters |
| none of the above | Gameplay resource setup, background, gameplay/render driver, fades |

The numeric gates and screen names remain unresolved unless independently
supported. The pause connection is explicit: func_8006E418 sets D_8013FAD0
on a fresh Start press when its earlier guards permit it (12194-12286).
Do not infer that every early-return branch is a pause or that every build
executes the normal board update. The main function's two large outcome
state machines are mapped structurally here, not fully semantically named.

## Resources and normal gameplay

func_8006EC00 (12347-12381) is guarded setup for the shared screen
environment. It returns if D_800DFD5C is already nonzero. Otherwise it sets
transition/input gates, waits while built graphics tasks exceed consumed
completions, repartitions buffers, resets the asset cursor, reserves image
storage and loads a common asset set. This is not a generic per-frame tick.

func_8006F52C (12539-12599) prepares gameplay resources. It distinguishes
changing game mode, changing the stage/index within a mode, and entering
from the shared screen environment. Buffer budgets depend on mode 3 versus
two-player versus other gameplay. It resets allocation cursors at the
appropriate boundary and invokes the resource loaders. The nested wait
helper func_8002A140 consumes a main-queue message without building a frame.

The normal tail (main.c:13224 onward) draws split-player background/fade
rectangles or advances/draws the background animation. It then calls
func_800CD3B8, followed by mode-specific exit and entry fades.
CD3B8 selects player contexts, builds the interpolated board grid, consumes
piece operations, latches view coordinates, handles held/released actions,
advances state/effects and invokes rendering. It is a mixed update/render
driver; the existing source does not separate pure simulation from drawing.

## Scope and next trace

The three new function names require twelve identifier substitutions across
boot.c, main.c and game2.c. Complete production-input inventory found no
target-name collisions or external fixed-address aliases. Existing mixed
pointer/integer declarations are preserved. SDK scheduler code, global
fields, screen IDs, comments and formatting do not change.

Next useful main-loop trace: follow the Start-set D_8013FAD0 into
func_8003FE3C and back to gameplay, including screen-asset setup and buffer
repartitioning. This should establish the pause/resume lifecycle without
descending into unrelated mathematical leaves.
