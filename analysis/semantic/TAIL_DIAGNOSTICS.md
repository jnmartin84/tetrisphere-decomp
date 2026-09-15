# Late diagnostic strings — 2026-09-14

Read-only follow-up to the user's ROM-string observation. Published source is
clean at ddfaf805462777676186a6a04cb5122fe557add0. Eight selected strings were
checked against original ROM bytes including their NUL terminators; see
TAIL_DIAGNOSTIC_EVIDENCE.json. No source changes or new build.

The final strings in asm/data/C9AFC.data.s run through ROM 0xCC1CC. They mix
error checks, routine progress messages and informal debugging; neighboring
strings do not automatically belong to one subsystem or original TU.

## The three profane messages

- ROM 0xCB920 / D_800F0570: "*** THIS IS MAJOR FUCKING EVIL AND WILL CRASH THE GAME!!!!! TELL SOMEONE!!\n".
  PlacePieceGame, src/game2.c:6309, rejects a piece descriptor whose second s16
  is outside both 1..7 and 0x20..0x26. The branch prints more diagnostics and
  ultimately calls func_8002AF20 with an error description. This is an actual
  invalid-piece branch, not just an emphatic informational message.
- ROM 0xCC12C / D_800F0D7C: "FUCK YOU  %d\n".
  func_800C5254, game2.c:23102, prints D_8014D264 immediately after computing
  sqrt(D_80160C78^2 + D_80160C7C^2 + D_80160C80^2) and converting/storing it.
  This is during effect initialization, after setting player+0x1274 active.
  The string itself does not guard a failure or identify the vector's meaning.
- ROM 0xCC184 / D_800F0DD4: "What the FUCK\n".
  func_800C96C0, game2.c:24672, handles a negative D_8015FE04 after updating a
  shared quantity based on arg0 and D_8015FE0A. It resets the quantity to zero
  and the selector to one. Meaning of this quantity/selector needs more tracing;
  do not call it a score merely because a scoring string is nearby.

All three call func_80029760, whose body in src/boot.c:75 is empty. The strings
survive, but that sink does not display them in this build. The invalid-piece
branch additionally reaches func_8002AF20 (src/code_62D0.c:28), which formats an
error buffer, sets a flag, invokes rmonPrintf, flushes caches and writes through
D_800DFD34. Distinguish the retained diagnostic sink from the error path itself.

## Nearby naming leads

| Literal | Current direct caller | Evidence / limit |
|---|---|---|
| ScoreTheLevel Player: %d .. Score: %d | func_800C7C90, game2.c:23992 | Computes a gated level award and passes a scaled score to the diagnostic; strong original-name lead |
| ThrowBlackLayer Called. | func_800CB7E8, game2.c:25618 | Unconditional entry diagnostic followed by a rectangular layer/piece operation; strong original-name lead |
| Saying PlayTowerAnim DONE! | func_800CBB1C, game2.c:25662 | Timer player+0x3244 >= 0x10F clears D_801309EE; strong animation-role/name lead |
| BLOWPIECEGONNER!! | func_800CBEE8, game2.c:25727 | Fires effect at timer 72; at 180 invokes cleanup and clears D_801309EE |
| Inializing heart skull animation thing | func_800C3CAC, game2.c:22418 | Small player-index-gated reset of D_8014D266; wording alone does not prove this function initializes the whole animation |

The tower and blow-piece messages add direct consumers to the earlier
QuestAnimActive candidate D_801309EE. This connects the global to multiple
quest-animation completion paths, not just end-sequence startup. These are
notes-only leads; inspect remaining calls/types before a naming batch.
