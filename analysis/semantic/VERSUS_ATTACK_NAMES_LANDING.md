# Versus attack names — batch 018

The negative-counter diagnostic and ThrowBlackLayer callers reveal a shared
versus attack balance: per-player contributions cancel, remaining power is
represented by tiered indicators, and armed slots act on the other player.
See VERSUS_ATTACK_TRACE.md for producers, consumers and remaining uncertainty.

This batch names five routines (queueVersusAttackPower, updateVersusAttackBalance,
rebuildVersusAttackIndicators, startPendingVersusAttack, applyVersusAttackSlot)
and three globals (gQueuedVersusAttackPower, gPendingVersusAttackPower,
gPendingVersusAttackPlayer). These are descriptive semantic names.

All 60 substitutions are reviewed identifier tokens: 57 in src/game2.c and three
BSS dlabels in asm/data/game_bss_b.bss.s. Every other production byte is preserved,
including types, storage sizes, comments, formatting and expressions. In
particular, the existing u8 declaration for the owner and its two-byte BSS
reservation remain exactly as before; no type/layout consolidation is performed.

Baseline: b53c494762644fb7fc10c7588b36585b6c584334. Pristine and renamed isolated
builds returned FULL MATCH; independent full-ROM cmp passed including the header.
All eight linked addresses are unchanged. The scoped guard verifies inverse byte
restoration and 995 production inputs. No guard implementation changes or new
production tests were needed for this batch.

batch_018_data_evidence.json independently reads the ROM's four s16 power values
and checks the maximum slot requirement for every integer amount 0..360. This is
a static data/arithmetic check, not hardware gameplay validation. The full ROM
SHA-256 remains f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87.

Ledger and validation: batch_018.json, batch_018_inputs.json,
batch_018_validation.json and batch_018_verification.json. Recheck with:

```sh
python3 tools/semantic/scoped_identifier_renames.py --ledger analysis/semantic/batch_018.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

Only task-owned source and text evidence are staged. User manages GitHub pushes.
Final published-checkout integration is verified separately and recorded in the
research SESSION_RESTART.md.
