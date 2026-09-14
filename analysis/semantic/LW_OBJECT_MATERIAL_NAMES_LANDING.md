# LW object and material function names — batch 016

The object-state and material-light paths previously used address-based function
names. This batch names their demonstrated roles in transparency, transforms,
hierarchy traversal and light loading, making the LW playback chain readable.
These are descriptive semantic names, not recovered original spellings.

| Previous name | New name |
|---|---|
| func_8002E0D4 | updateAnimationObjectAlpha |
| func_800301FC | resetAnimationObjectTransparency |
| func_8003024C | resetAnimationObjectTransform |
| func_800312C4 | buildAnimationObjectHierarchyMatrices |
| func_80031964 | buildAnimationObjectMatrices |
| func_800305B0 | loadAnimationLights |
| func_80030964 | loadMaterialTintedAnimationLights |
| func_8002DFA0 | findMaterialLightColor |

There are 22 identifier substitutions in `src/code_8170.c`, including declarations,
definitions and calls. No other source bytes change. Types, field names, comments,
strings, whitespace, expressions and compiler-sensitive line grouping are preserved.
The field candidates in the research notes remain deferred.

Evidence: [LW_OBJECT_MATERIAL_TRACE.md](LW_OBJECT_MATERIAL_TRACE.md) connects the
runtime writers to matrix/alpha/light consumers. In particular, the compact RGB
table used during allocation and the later material light groups occupy the same
reserved storage at different times; no indexing correction is introduced.

Baseline: `9840f7226709243cf8adbd0700d5cfb079124c25`.
The isolated pristine build and renamed build both returned FULL MATCH. Independent
`cmp tetrisphere.z64 build/tetrisphere.us.z64` passed including the 64-byte header.
All eight linked addresses remain unchanged. The full 8,388,608-byte ROM SHA-256 is
`f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.

The identifier guard verifies exact inverse restoration and 995 production inputs.
The existing guard implementation is unchanged. Evidence is in `batch_016.json`,
`batch_016_inputs.json`, `batch_016_validation.json`, and
`batch_016_verification.json`.

Recheck this batch with:

```sh
python3 tools/semantic/identifier_renames.py --ledger analysis/semantic/batch_016.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

Only the source and named text evidence files belong in this commit. GitHub pushes
remain user-managed. The final published-checkout rebuild is recorded separately
in the research restart notes after integration.
