# Start -> pause menu -> gameplay

2026-09-13. Original baseline 823ca10873a7eafde7d68951087cdaf9d3095dfd;
batch 007 extends semantic HEAD f7611e5. Source line numbers are unchanged.

## Entering pause

func_8006E418 (main.c:12194-12286) recognizes a fresh Start edge for an
active player's assigned controller, after its transition, demo and
special-state guards. When func_800B9134 permits it, the handler sets
D_8013FAD0=1 and records the controller port in D_800DFE00. It stores the
current processed button mask and returns without the usual ACB94 call.

updateAndBuildFrame tests D_8013FAD0 ahead of normal gameplay
(12817-12829). It initializes selection D_800E1228 to zero if needed,
clears the subordinate-screen index/timing, runs shared screen setup and
calls the pause handler. It clears D_8013FAD0 when selection becomes
negative. This branch always returns; gameplay starts on a subsequent
frame dispatch, not by falling through immediately after closing pause.

Shared setup func_8006EC00 (12347-12381) waits for prior graphics task
completions, repartitions graphics storage and resets the asset allocator.
It reserves 0x25800 bytes for D_800DFF00, loads common screen resources and
records their end at D_801026B8. The pause handler resets allocation to that
retained endpoint and loads its own images, meshes and animations.

## Snapshot and transition

`func_8006F894` -> **capturePreviousFramebuffer** (12603-12614).
It copies 0x12C00 u16 pixels, exactly 320x240, from the framebuffer pointer
at D_801028CC+0x1910 into D_800DFF00. D_801028CC is the previous frame
record saved by updateAndBuildFrame; this helper does not query VI's current
displayed buffer and does not wait or synchronize by itself. Its reviewed
callers perform graphics-completion waits before capture. It is shared by
other screens, so its name is not pause-specific.

Pause initialization calls func_8003FC6C (1657-1673), which captures that
image, installs transition colors, sets D_800DFF08=4 and initializes screen
counters. The transition handler func_8003B1A4 (760 onward) displays the
saved image when its transition blend is below full opacity and draws the
animated screen overlay. It moves opening state 4 to steady state 1 and
closing state 5 to state 0 when the transition-completion flag is set.
Closing helper func_8003FD78 sets state 5 and target opacity zero.

## Pause menu and controller ownership

`func_8003FE3C` -> **updateAndDrawPauseMenu** (1850-2101).
Menu strings are verified from D_800E1134's pointer table in
asm/data/BAAB0.data.s:3147-3151 and the pointed-to strings in
asm/data/C7340.data.s:1166-1185:

| Selection | Label / branch |
|---|---|
| 0 | CONTINUE |
| 1 | GOAL; hidden unless mode/state allows it |
| 2 | AUDIO; displayed as SKIP in mode 3 |
| 3 | EXIT |

The hidden-GOAL predicate is computed at main.c:1911; drawing and navigation
both skip it. Mode-3 SKIP text is explicitly stored at D_800ECBF0/CBF8/CC00/
CC08. Numeric modes stay numeric; the labels do not establish every mode's
full game meaning.

Navigation reads D_800DFDD4[D_800DFE00], the per-port press/repeat mask from
the controller that opened pause. Down/up wrap the selection and skip the
hidden entry. A/Z/Start (0xB000) confirm; B (0x4000) cancels to selection 0.
These actions are disabled during closing state 5. Input is processed only
after the opening screen counter reaches 30 and opacity is nonzero, which
also separates the opening Start press from immediate confirmation.

CONTINUE and B request the closing animation. Once the transition state is
zero the menu makes selection negative, and the outer dispatcher clears
the pause flag. GOAL also sets up the existing goal-display state before
closing. AUDIO dispatches func_80054098 through D_800E122A; EXIT may first
invoke func_8005C978 through D_800E122C in certain single-player modes.
Those subordinate screens and their persistence behavior remain a next
trace. Mode-3 SKIP sets outcome/progression flags instead of AUDIO.

## Input while paused and immediately after resume

Controller dispatch func_8006DF3C always updates raw per-port button words
first (12089-12118). Its pause/transition gate then synchronizes the ring
consumer to the producer, updates processed masks for the assigned players,
sets D_800E170C=10 and returns before enqueuing gameplay samples
(12119-12136). UI edge/repeat processing can therefore continue from the
raw words while newly sampled gameplay inputs are discarded during pause.
This describes incoming samples, not a retroactive claim about every
sample already being drained at the moment Start was recognized.

After all routing gates clear, D_800E170C counts down only on samples from
the designated port D_800E171C. Each of those callbacks still returns via
the suppression path, even the decrement to zero; normal buffering follows
on later callbacks. This is ten qualifying sample callbacks, not ten
rendered frames. The behavior avoids replaying pause-menu input as queued
gameplay actions. Existing processed-mask updates are preserved.

The next gameplay dispatch runs func_8006F52C's shared-screen-to-gameplay
resource path because D_800DFD5C is still set. It waits for old graphics,
repartitions buffers, reloads gameplay resources and clears the screen/
transition gates. This path does not call the board initialization entry
func_800CC6E0. Existing board state is not replaced by a new-game reset
in this dispatcher path; exact resource-loader internals remain separate.

## Screen timers keep running independently

`func_8006DC48` -> **updateScreenTimersOnRetrace** (12033-12060).
The scheduler calls this game-defined helper for VIDEO_MSG before
__scHandleRetrace (sched.c:138-140). It increments positive screen time
D_800E120C, advances transition time D_800DFF18, and handles opacity/color
interpolation and other shared screen counters. D_800DFE84 freezes most of
the work, but the D_800DFE90 decrement precedes that gate. Preserve the
ordering. These updates are per processed video-retrace message, separate
from the input-derived gameplay delta captured by the graphics task builder.

The main thread samples these counters while drawing, so pause animation
continues without the normal board update/render path. The timer helper is
game-owned; only its identifier declaration/call changes in the existing
scheduler source. No SDK function is renamed or scheduling logic altered.

## Batch and continuation

Three function names, ten identifier tokens: eight in main.c and two in
sched.c. All 997 production inputs were inventoried; no new-name collisions
or additional aliases were found. See batch_007.json and its lexical/ROM
reports for acceptance. No emulator/hardware timing or visual test is claimed.

Next main-loop branch: pause's AUDIO selection -> func_80054098 -> return
to pause. Establish how it gates input, updates sound settings and persists
changes before naming its helper or any shared state fields.
