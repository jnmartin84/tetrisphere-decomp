# LW runtime data vocabulary: batch 015

Step 1 of the user-requested LW data audit: apply established vocabulary to
existing views and members, keeping layouts/access expressions unchanged.
This batch makes 284 identifier substitutions in src/code_8170.c against ef6da68.
No object/material-light format decoding is claimed by this naming batch.

## Runtime and input views

| Previous typedef | New typedef |
| --- | --- |
| Pool | LWInfo |
| PoolEnt | LWGeometryInfo |
| Heap | LWAnimStreamHeader |
| Blk | LWGeomStreamHeader |
| TG8 | LWGeometryInfoCheckView |
| T8Ent | LWGeometryInfoStreamView |
| Obj2EBF4 | LWInfoLightView |
| T24C_Hdr | LWAnimStreamObjectView |
| T24C_A0 | LWInfoObjectView |
| O321 | LWInfoRenderView |
| V31C | LWInfoTransformView |

LWInfo uses the original diagnostic vocabulary for the runtime identity. The
other view names and member casing are descriptive, not claimed original C
spellings. The structs remain separate partial views; this does not construct a
new complete header or merge existing representations.

## Runtime member names

| Offset | New member |
| --- | --- |
| +0x00 | lights0 |
| +0x04 | lights1 |
| +0x08 | materialLights0 |
| +0x0C | materialLights1 |
| +0x10 | lightInfo |
| +0x14 | objectInfo |
| +0x18 | geometryInfo |
| +0x1C | animStream |
| +0x20 | geomStreamCount |

The paired pointers remain separate members. No lights[2] or materialLights[2]
array declaration was introduced, since that would change more than names.
The geometry descriptor views name +0 indexList and +4 geomStream, retaining
their original s16-pointer/s32 and void-pointer/u32/u8-pointer declarations.

The constructor now calls its parameters memory, animStream, geomStreams,
geomStreamCount, and allocatedSize; locals pool/countA/countB become
lwInfo/lightCount/objectCount. Animation header +4/+8 are lightBlockOffset and
objectBlockOffset; +0x10 is streamSize. Geometry header +0x14 is streamSize.
These are relative input-block offsets and stream lengths, not runtime pointers.

Evidence: ROM_STRING_SEMANTICS.md and ROM_STRING_LW_EVIDENCE.json establish
all eight labelled runtime pointers. The allocator provides descriptor count,
index-list allocation, stream offsets/sizes, and constructor parameter roles.
The partial light, object, and render receivers were individually traced to the
same runtime offsets. The previously named buildAnimationLightDirections and
the object transform/render helpers corroborate their uses.

Scope was checked at each declaration and member access. Other unk fields,
entry records, stream commands, raw offset accesses, and arithmetic remain
unchanged. T321 is deliberately retained: it is reused as a view of both an
eight-byte geometry descriptor and a geometry-stream header, so its unk4 is not
one universally nameable field. Preserving that representation avoids an
unjustified rename or type/layout rewrite. The actual light/object record
internals remain candidates for step 2.

Validation: pristine and renamed FULL MATCH, independent cmp of all 8,388,608
ROM bytes including the header, scoped inverse restoration, independent complete
C-identifier stream comparison, and 995 production input hashes. The guard was
not modified; no new tests were necessary. See batch_015_verification.json.

```sh
python3 tools/semantic/scoped_identifier_renames.py --ledger analysis/semantic/batch_015.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

No binaries are staged. User manages GitHub pushes; remote state was not queried
or modified for this local landing.
