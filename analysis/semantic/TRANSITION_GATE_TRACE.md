# Brief transition-gate trace

2026-09-14; read-only source study at local landed_tsphere 0a913fa, clean.
No production changes or remote operations. This follows the renamed drop pool,
Begin_WinAnim and end-sequence animation helpers rather than expanding scope.

## Separate drop work, visual effects, and pause blocking

func_800B9090 (src/game2.c:18556) is a pure predicate over the current player:
u8 fields +0x701, +0x1268, +0x1267, +0x1269, +0x1274, and u16 +0x1272.
It does not read the active drop count +0x25CA. The frame driver's deferred-win
timer at line 26417 separately requires pending action +0x24A6 == 0 and this
predicate == 0. Begin_WinAnim separately guards +0x25CA. These are distinct
barriers: pending actions, active drop records, and animation/effect state.

Some constituents now have concrete producers:

- +0x701 is set by updateAndDrawEndSequenceAnimation and participates in the
  decision to retain the game animation arena at game2.c:27085. Other producers
  exist, so do not name it exclusively after end sequences.
- +0x1269 is set from func_800C5CFC's argument (23249), whose diagnostic says
  'Beginning tornado of size %d'. The field also selects one of the animation
  assets. It is a tornado size/variant with zero inactive, not just a Boolean.
- +0x1272 is armed with 0x28 by func_800C51F0 (23008). The frame driver counts
  it down and invokes func_800C5254 on expiry (26913–26920). That helper sets
  +0x1274 to 1 and creates an animation record. +0x1274 subsequently gates
  func_800C4EBC. This establishes a delayed-start/active-effect pair; the exact
  effect identity remains unresolved here.
- func_800C6B74 (23578) sets +0x1267 from its argument and +0x1268 to 0x4B.
  The frame driver decrements the latter and either calls func_800C67E4 or clears
  the selector. The timer's unusual subtraction/comparison order is preserved.

func_800B9134 (18587) is the broader predicate: it checks the same six fields for
player 1, adds +0x1680 and +0x168C, checks player 2 when two players are active,
and includes D_8014D266 in the single-player case. Its sole located C caller is
the Start-edge path in src/main.c:12258, where a zero result permits arming pause.
This gives a strong semantic role as checking player effects/transitions that
block pause. It is not the complete pause policy; other mode/input gates surround
the call. The two predicates should not be given interchangeable names.

## End-sequence progression is distinct from visual completion

func_800C2EF4 (game2.c:22045), called from the main gameplay frame path (26937),
updates the active end-sequence state. It services func_800ADC44 for both player
contexts. The exact domain of that helper was not re-established here.

For phase +0x1680 == 5, it delegates to func_800C2E34. Otherwise it counts down
D_80139E68 using D_80160C64. Once the delay elapses and D_80130A26 is nonzero,
it increments the accumulator at +0x1684 by delta times rate byte +0x1688,
then dispatches handlers for phases 2, 1, 4, and 6. These are separate ifs that
re-read the phase, not a switch over a captured initial value. Phase 3 has no
handler in this function; do not assume all active phases dispatch here.

D_80130A26 is not a playback-completed flag. startEndSequenceAnimation clears it
after allocating the instance; updateAndDrawEndSequenceAnimation sets it before
calling LWPlayAnimation. A two-player early exit and non-LW transitions also set
it. Strong bounded interpretation: permission/readiness to advance the end
sequence. Exact frame-order/handshake semantics need a further pass before a
global rename. D_80139E68 is clearly the end-sequence progression delay, though
its time units should not be called milliseconds or frames without tracing delta.

func_800C3058 (22105) provides the related per-player fade-overlay drawing pass:
select player/viewport, check active phase, derive alpha from +0x1684, configure
primitive-color rendering and draw. It also changes result/visibility fields at
fade thresholds, so a future name should allow update side effects. The existing
source comment hinted this; the named end-sequence helpers now provide context.

## Naming candidates, not applied

- func_800C2EF4 -> updateEndSequenceState (high confidence).
- func_800C3058 -> updateAndDrawEndSequenceFade (high confidence; includes state writes).
- func_800C5CFC -> startTornadoEffect (high confidence from diagnostic and setup).
- D_80139E68 -> gEndSequenceDelay (high confidence; preserve shared/global scope).
- func_800B9134 -> hasPauseBlockingPlayerEffects (strong caller-based descriptive
  candidate; does not claim to implement all pause gates).
- func_800B9090: retain notes until the remaining effect identities are traced;
  avoid hasActiveDrops or isEndSequenceActive, both narrower than the checks.

The useful stopping point is the distinction between these gates. No flags were
retyped, counter expressions changed, or names applied during this brief session.
