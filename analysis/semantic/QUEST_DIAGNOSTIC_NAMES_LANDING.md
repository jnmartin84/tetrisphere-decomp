# Quest and scoring vocabulary — batch 017

Late ROM diagnostics identify three routines and a quest-animation flag. This
batch makes those connections readable in source with identifier substitutions
only, preserving all declarations, expressions, formatting and string literals.

| Previous identifier | Landed name | Evidence |
|---|---|---|
| func_800C7C90 | ScoreTheLevel | D_800F0DAC prints this spelling while reporting player and score |
| func_800CB7E8 | ThrowBlackLayer | D_800F0DE4 announces entry by this name |
| func_800CBB1C | PlayTowerAnim | D_800F0E00 reports completion under this name |
| D_801309EE | gQuestAnimActive | D_800F0C1C announces QuestAnimActive immediately before setting this byte to 1 |

The function spellings come from retained diagnostics; the global uses the
project's g prefix with the diagnostic vocabulary. See TAIL_DIAGNOSTICS.md,
TAIL_DIAGNOSTIC_EVIDENCE.json and batch_017_string_evidence.json for the original
ROM-verified literals. The tail study retains its pre-rename snapshot.

## Call and state connections

ScoreTheLevel is reached from PlayerWon, Begin_WinAnim, func_800AA4B0 and the
phase-5 completion helper func_800C2E34. Its mode/count checks and player+0x323A
marker prevent repeat awards for the current level. It updates player+0x2AF8,
submits another score quantity through func_800B363C, and reports player identity
and a scaled score. This batch does not assign new names or units to those raw
fields or change the load-bearing comma expression.

ThrowBlackLayer is called from func_800CA710 with 4x4, 8x8 or 12x12 dimensions.
Its body selects board pieces, attempts placements at layer 7, and submits the
associated piece operations. This supports the diagnostic's identity without
inferring undocumented visual details from the word "black".

Begin_WinAnim can select func_800C37A4, which sets phase 5, gQuestAnimActive=1,
and the timer at player+0x3244 to zero. The phase-5 helper calls func_800CBFF4:

- Mode value 0xA calls PlayTowerAnim(1).
- Mode value 0xB calls PlayTowerAnim(2).
- Mode value 7 calls the blow-piece updater func_800CBEE8.
- Other values clear gQuestAnimActive.

PlayTowerAnim advances that timer, triggers work at 30-unit thresholds, and
clears the flag at >=0x10F. The blow-piece path clears it at the 180 threshold.
Once the flag is zero, func_800C2E34 invokes ScoreTheLevel and begins the next
end-sequence phase. Timer units and the mode display names are not newly claimed.

## Storage and validation

gQuestAnimActive retains the existing u8 declaration and absolute linker alias
at 0x801309EE in undefined_syms.txt. The alias points inside the storage interval
of the existing s32 D_801309EC at 0x801309EC; guPerspective uses its address for
the perspective normalization output. No allocation, splitting or storage/type
reconstruction is performed. All neighboring aliases and addresses remain intact.

The scoped identifier guard now accepts only the identifier on the left side of
a constant hexadecimal assignment in undefined_syms.txt. Comments, RHS values
and expressions cannot be selected as rename sites. The guard extension was
committed separately, and all 31 guard tests pass.

Production baseline is ddfaf805462777676186a6a04cb5122fe557add0. The batch ledger
uses the subsequent guard-only commit as its exact Git baseline; production
inputs are identical. Pristine and renamed isolated builds returned FULL MATCH,
and independent cmp verifies all 8,388,608 bytes including the header. There are
23 substitutions: 22 in game2.c and one linker symbol. Inverse restoration and
all 995 production inputs pass; all four linked addresses are unchanged.

ROM SHA-256:
`f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.
See batch_017.json, batch_017_inputs.json, batch_017_validation.json and
batch_017_verification.json. Recheck with:

```sh
python3 tools/semantic/scoped_identifier_renames.py --ledger analysis/semantic/batch_017.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

The informal vector diagnostic, negative-counter semantics and remaining
heart/skull/blow-piece names remain research leads. No binaries are staged;
GitHub pushes remain user-managed. Final integration verification is recorded
in the research SESSION_RESTART.md after the published checkout is rebuilt.
