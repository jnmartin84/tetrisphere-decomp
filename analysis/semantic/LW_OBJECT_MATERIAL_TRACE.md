# LW step 2: object state and material lights

Research snapshot preceding batch 016. The probe and full data JSON mentioned
below are retained in `/Users/jnmartin/CodexTetrisphere/pending/semantic_pass/`.
See `LW_OBJECT_MATERIAL_NAMES_LANDING.md` for the subsequent function-name landing.

Read-only source study, 2026-09-14. Both the published checkout and the isolated
`lw_names` checkout were clean at `9840f7226709243cf8adbd0700d5cfb079124c25`.
Source pointers below refer to `src/code_8170.c` at that commit unless stated
otherwise. No production identifiers, types, layout, expressions or other source
bytes changed. These are semantic findings and candidates, not a rename landing.

## Result

`objectInfo` is an array of per-object animation/rendering state. Its `0x120`-byte
records contain alternating fixed matrices, final alpha, reflection LookAt data,
current transform/transparency channels and two banks of animation differences.
The stream supplies a hierarchy, initial values, pivots and animation tracks.

`materialLights` contains alternating buffers of N64 light records, grouped by
deduplicated material RGB. Allocation first uses part of the space as a compact
color lookup table. Rendering reuses it as full groups of tinted lights. The
geometry descriptor's `indexList` maps material records to these groups.

## Object runtime layout

| Offset within a 0x120 record | Meaning | Producer / consumer |
|---|---|---|
| 0x00, 0x40 | Two fixed `Mtx` objects, selected by LWInfo+0x3D | 312C4:1434 builds; 321D4:1736 multiplies into modelview |
| 0x80 | Final object alpha, 0..255 | 2E0D4:511 computes; 31A98:1564 selects draw pass; 32320:1789 limits material primitive alpha |
| 0x81..0x87 | Unassigned bytes | Existing views pad over these; no new meaning claimed |
| 0x88..0xA7 | `LookAt` reflection data | 31FEC:1692 passes this to guLookAtReflect and gSPLookAtX/Y |
| 0xA8, 0xAC, 0xB0 | Translation X, Y, Z | 3024C:1177 initializes; 2EDA4:714 advances; 312C4 consumes |
| 0xB4, 0xB8, 0xBC | Rotation about Y, X, Z respectively, in degrees | Same chain; axes established by matrix equations |
| 0xC0, 0xC4, 0xC8 | Scale X, Y, Z | Same chain; scales the three matrix columns |
| 0xCC | Animated object transparency | 301FC:1145 initializes; 2ED04:691 advances; 2E0D4 converts to alpha |
| 0xD0..0xF4 | First differences for the ten channels above, same order | 2E620:600 / 2E5E0:582 seed; 2EDA4 / 2ED04 consume and update |
| 0xF8..0x11C | Second differences for those ten channels | Same routines; updated by stream-supplied third differences |

The two matrix banks are explicit. The existing LookAt field is a single field;
do not assume that every piece of object rendering state is double buffered.

The axis distinction matters: in 312C4 the variable named `sx` is computed from
object+0xB4, but isolating that angle yields a Y-axis rotation. Object+0xB8 yields
an X-axis rotation. With the conceptual column-vector matrix represented by
`r00..r22`, the rotation/scale is `Ry(B4) * Rx(B8) * Rz(BC) * Scale`.
The libultra output array follows the source's storage convention; do not rewrite
the equations or infer that the old local variable names denote physical axes.

The local translation is `position - rotationScale * pivot`. The routine composes
this with the parent matrix, stores the result in the selected fixed matrix, and
recurses into children using the floating result. The resulting matrix therefore
includes ancestry within the animation. Camera/base modelview is applied later
by 321D4. Avoid naming it merely `localMatrix` or claiming a game-world space.

## Object stream layout and traversal

Animation header+8 points to a block containing a u32 object count and block-relative
u32 offsets. For object entry `E` with child count `N`:

| Location | Meaning established by current consumers |
|---|---|
| E+0 | s16 geometry-stream index; 310C4 selects geometryInfo |
| E+2 | s16 geometry-group index within that stream |
| E+4 | u32 child count |
| E+8 | N u32 child object indices |
| B = E+8+4*N | Nine initial transform floats, matching runtime A8..C8 |
| B+0x24 | Initial transparency float |
| B+0x28..0x30 | Pivot X/Y/Z |
| B+0x34 | Offset relative to this word, leading to transform-track header |
| B+0x38 | Transparency-track header |

31964:1510 walks all objects, follows the transform-track offset, and starts
312C4 recursion when that track's flags contain 0x10. Each start uses identity.
310C4:1396 separately resolves the geometry-group descriptor; 321D4 uses its
material list to call 32320. Objects and materials are therefore different
levels of the hierarchy, with explicit indices connecting them.

2F55C:774 chooses the current track record from the animation counter. For the
object transform path, channel flags 1 through 0x100 select the nine floats.
A nonzero record mode uses direct additive differences from the stream. A zero
mode uses this recurrence, with coefficient initialization at the segment boundary:

    value += firstDifference
    firstDifference += secondDifference
    secondDifference += streamThirdDifference

The separate transparency path follows the same recurrence for its scalar.
This establishes finite-difference animation evaluation. It does not recover the
original authoring spline terminology, exporter or interpolation UI. Keep the
special source pointer advances and record-boundary behavior intact.

## Transparency becomes a rendering value

2E0D4 computes approximately:

    alpha = clamp(round(255 * (1 - max(objectTransparency, globalTransparency))), 0, 255)

Here globalTransparency is LWInfo+0x28. The exact C uses +0.5 followed by integer
conversion and double constants; this formula is explanatory, not replacement C.
2F55C advances/clamps the global value using LWInfo+0x2C.

31A98 uses alpha 255 in its first pass and skips alpha 0 in its second pass.
32320 chooses the minimum of object alpha and the material record's alpha and
passes it to gDPSetPrimColor. Texture format and material flags also affect the
passes. Thus +0xCC is transparency, whereas +0x80 is alpha; naming both opacity
would hide their opposite direction.

## Material records, color deduplication and light emission

Geometry-stream header+4 leads to a count + block-relative offset table of
material records. This gives stronger meaning to LWGeomStreamHeader.unk4 and
LWGeometryInfo.indexList, without changing T321's ambiguous two-role usage.
32320 and allocation agree on this material prefix:

| Material offset | Meaning |
|---|---|
| 0..3 | Red, green, blue, alpha bytes |
| 4 | Rendering flags; bit 0x08 selects material-tinted lights |
| 5 | Texture address-mode selector (0 maps to clamp, 1 wrap, 2 mirror in this consumer) |
| 6 | s16 texture-frame count |
| 8 | s16 frame divisor |
| 0xA | s16 texture-frame indices, followed by geometry-batch references |

Allocation: for every material with flag 0x08, 2DFA0:484 searches RGB bytes at
`colorIndex * 16` in materialLights0. New colors are stored at that same compact
stride, but reserve `lightCount * 16` bytes each. The geometry material's s16
indexList entry receives the color index. Afterward the reserved region is
copied into materialLights1. No assumption that all reserved bytes were cleared.

Rendering: 32320 passes the material's own RGB directly to 30964:1304. That
routine gets `s = geometryInfo[geometryIndex].indexList[materialIndex]`, and for
each light j writes slot `s * lightCount + j` in the active materialLights bank.
Directions are copied from the active lights bank. Each channel is:

    sourceLightRGB * min(globalIntensity, animatedLightIntensity) * materialRGB / 255

It writes both N64 light color copies, then emits gSPLight for the resulting
record. Thus the compact RGB table is needed only during allocation, and its
subsequent overwrite is consistent with the inspected lifetime. This is not
evidence of a stride bug or a reason to change source layout.

305B0:1263 handles the untinted path, computing lightRGB * min(intensities) in
the ordinary lights bank. Both routines load slots 1..n and emit
gSPNumLights(n-1). The bundled `include/PR/gbi.h:1339`, `:2440`, `:2478`
establish the 16-byte Light layout, duplicate color fields and final ambient
slot. Light count in these arrays includes that ambient slot; calling all n
records directional lights would be misleading.

30964 retains an outer loop over geomStreamCount even though its selected
geometry/material indices do not change with that loop. 32320 caches the last
material index at LWInfo+0x3E (initial sentinel -2, untinted sentinel -1).
The exact cache behavior across multiple geometry streams remains a separate
runtime question; no cleanup or stronger cache-correctness claim here.

## Data cross-check

`lw_step2_probe.py` reads the original ROM and uses the existing S decoder.
All decoded hashes are compared with the earlier asset inventory; the current
script does not rerun that earlier survey's independent native decoder check.
The ROM SHA-256 is checked, and the asset blob must equal its ROM slice.
Results are in `LW_STEP2_DATA_EVIDENCE.json`, including source/decoder hashes,
per-object offsets/initial values/hierarchy and per-material prefixes.

- 293 standard animation streams: 3,389 objects. All referenced child indices
  are in range; traversal from root flags reaches every object exactly once,
  with no cycles. 1,603 objects have a nonzero pivot.
- Initial object transparency ranges from 0.0 to 1.0.
- 118 geometry streams: 3,100 material records, 631 with flag 0x08.
- Example: mesh 0 has six such material records but only three distinct RGB
  values, providing real data for the allocation deduplication path. This does
  not assign a visual identity to mesh 0 or bind it to an animation.
- Light counts vary from 2 to 9. The temporary compact-color table therefore
  cannot be explained by an assumption of one light per animation.
- Animation slots 16 and 17 have an alternate header and are explicitly
  deferred. Empty archive slots are not parsed.

These are static decoded-data checks, not N64 execution. Full keyframe record
validation, animation-to-mesh bindings, hardware light-limit behavior for the
count-9 entry, and alternate formats are outside this bounded pass.

## Supported next names (not applied)

| Current identifier | Candidate | Confidence / scope |
|---|---|---|
| func_8002E0D4 | updateAnimationObjectAlpha | High: calculation and final GBI alpha consumer |
| func_800301FC | resetAnimationObjectTransparency | High: initial stream value to CC |
| func_8003024C | resetAnimationObjectTransform | High: initial nine channels |
| func_800312C4 | buildAnimationObjectHierarchyMatrices | High: parent composition and child recursion |
| func_80031964 | buildAnimationObjectMatrices | High: root traversal wrapper |
| func_800305B0 | loadAnimationLights | High: updates records and emits GBI loads |
| func_80030964 | loadMaterialTintedAnimationLights | High: material RGB multiplication and GBI loads |
| func_8002DFA0 | findMaterialLightColor | High: allocation-time RGB search |

Field candidates: object alpha/transparency, translation XYZ, rotation Y/X/Z in
degrees, scale XYZ; LWInfo globalTransparency/globalTransparencyStep,
globalLightIntensity/globalLightIntensityStep, activeBufferIndex; geometry
materialBlockOffset and materialLightIndices. Existing partial views require
scoped substitutions. The proposed spellings are descriptive, not recovered
original identifiers. Do not convert padding/raw accesses into fields or merge
struct views as part of a future naming batch.

Next bounded work can land the strongest names under the normal lexical and
full-ROM gates, or trace one concrete animation/mesh pair through its keyframes
and material cache. No rename or source rebuild was performed by this study.
