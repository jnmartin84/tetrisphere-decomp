# Versus attack accumulation, cancellation and dispatch

Read-only evidence gathered at b53c494 before batch 018, 2026-09-14. Paths/lines
refer to src/game2.c in /Users/jnmartin/landed_tsphere. The investigation starts
from the negative-counter diagnostic at 24672 and the newly named ThrowBlackLayer.
The names below are descriptive semantic names, not recovered original spellings.

## What the shared counter represents

D_8015FE04 is pending versus attack power; D_8015FE0A is the player who owns that
pending attack (IDs 1 or 2). D_8015FDE8 holds separately queued contributions
for those players. This is more specific than the old comments' "score/combo"
description or "double-buffered accumulator": the array is indexed by player
identity, even though its drain alternates between indices each frame.

Evidence chain:

1. func_800CA554:25067 adds a u8 amount to D_8015FDE8[playerId-1]. Callers at
   24116 and 26757 supply the low byte at player+0x23B3 of the big-endian s16
   player ID at +0x23B2, with amounts derived from +0x2AE6/+0x2AE8. The precise
   names of those earning counters remain outside this batch.
2. func_800CB070:25407, the HUD/effect frame builder, drains one player's queue
   when D_8015FDF8 is zero, passes index+1 and its accumulated amount to
   func_800C96C0, clears that queue, and alternates the drain index. The u16
   queue storage and u8 contribution conversion are preserved.
3. func_800C96C0:24640 adds contributions from the current owning player.
   Opposing contributions subtract; if they exceed the pending amount, the
   remainder becomes owned by the contributing player. Equal contributions
   leave zero with the old owner retained. The pending amount is capped at 360.
   The "What the FUCK" path is a defensive negative-value reset, not a separate
   scoring operation. The cap is applied per drain, so do not replace the exact
   update order with a presumed order-independent net-total calculation.
4. func_800C93D4:24597 rebuilds 16 HUD/effect slots by greedy decomposition into
   powers 72, 24, 8 and 1. Each slot carries the owning player, tier, placement
   coordinate and flags. It is a renderable description of pending attack power.
5. func_800CA584:25081 only proceeds for D_8015D980==2, nonzero pending power,
   owning player equal to the current player, and no active sequence. It arms
   the slots, assigns tier-dependent delays, starts sequence state 3 and consumes
   the pending amount. The frame loop invokes it when player+0x1A3 is set
   (26955). The trigger's wider gameplay semantics are not assigned here.
6. func_800CA404:25018 decrements the sequence/slot delays, invokes
   func_800CA710 for due slots, and clears sequence state on completion.
7. func_800CA710:25200 temporarily selects player `3-slotPlayer` through
   func_800AF09C. That helper explicitly selects the player-1 or player-2 board
   context (14720); func_800AF294 restores the saved context (14761). Thus the
   slot's player is the attacker, and the operation is applied to the opponent.

## Tier and data relationships

| Tier | Power represented | Fired behavior |
|---|---|---|
| 0 | 1 | Selects a board location and invokes func_80093A00 on the opponent |
| 1 | 8 | ThrowBlackLayer with dimensions 4x4 |
| 2 | 24 | ThrowBlackLayer with dimensions 8x8 |
| 3 | 72 | ThrowBlackLayer with dimensions 12x12 |

The power table is four big-endian s16 values at ROM 0xC466C, corresponding to
VA 0x800E92BC..0x800E92C2. D_800E92B4 starts an adjacent four-value spacing table
{10,14,18,22}; the power array has only an existing end label D_800E92C2. Preserve
the current labels and backwards traversal rather than introducing a new array.

For all capped pending amounts 0..360, greedy decomposition needs at most 15
slots, fitting the existing 16-slot array. This is a bounded arithmetic/data
cross-check, not evidence of hardware execution or a complete attack-system test.

The HUD renderer func_800CA148 colors slots by player and selects images by tier.
The highest tier has additional animation through func_800C9B2C. The animation
sequence and presentation helpers remain address-named in this bounded batch.

## Naming batch

| Old | New |
|---|---|
| func_800CA554 | queueVersusAttackPower |
| func_800C96C0 | updateVersusAttackBalance |
| func_800C93D4 | rebuildVersusAttackIndicators |
| func_800CA584 | startPendingVersusAttack |
| func_800CA710 | applyVersusAttackSlot |
| D_8015FDE8 | gQueuedVersusAttackPower |
| D_8015FE04 | gPendingVersusAttackPower |
| D_8015FE0A | gPendingVersusAttackPlayer |

All three globals have existing BSS dlabels. Names change in declarations,
references and those labels only. Record layouts, types, comments and exact
source grouping remain untouched, including the old comments' provisional terms.
Quest helper names and the unrelated effect vector remain future candidates.
