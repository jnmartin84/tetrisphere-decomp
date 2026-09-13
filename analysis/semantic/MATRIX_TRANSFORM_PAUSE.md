# Four-component transform and the affine-inverse pause point

Recorded 2026-09-13, original baseline
`823ca10873a7eafde7d68951087cdaf9d3095dfd`, pre-batch semantic HEAD
`d408c8c9c56743662914b7cc2f58c87a623f6147`.
The user authorized continued work until a situation deserves a pause and
greater thought. The inverse routine below is that boundary.

## Bounded accepted name

`func_80031EB8` -> **transformVector4InPlace**.
At src/code_8170.c:1618-1636 it computes, for i=0..3:

`d[i] = sum(arg0[j][i] * arg1[j], j=0..3)`

It accumulates in float and computes all four results in a local array
before writing back to the vector. With the source matrix indexed by rows,
this is the row-vector product `v_out = v_in * M`. The fourth component is
also transformed; there is no perspective division or implicit w value.
The matrix and input vector need no new types or layout changes to express
the supported name. Only the function identifier changes.

The sole calling function, `func_80031FEC`, initializes at and eye with w=1,
and up with w=0 (1713-1723), then applies the transform four times
(1725-1729) before calling guLookAtReflect. That distinguishes positions
from directions: translation affects w=1 inputs and not w=0 inputs for an
affine matrix. The optional arg3 transform acts on at, as does a converted
node matrix; the inverse stored at +178 acts on up and eye.

This is game-side code. The separate vendored guMtxXFMF implementation in
src/libultra/gu/mtxcatf.c:57-62 takes three scalar components and writes
three outputs with an implicit translation contribution. No SDK code or
symbol changes in this batch. Inventory of all 997 production inputs found
only the definition, declaration and four calls in code_8170.c: six tokens.
There is no target-name collision or fixed-address alias.

## Pause: source return type does not describe a real status result

`func_8002CDC0`, code_8170.c:8-48, has an s32 declaration but no return
statement. Its caller tests the result against zero at line 1706.
The byte-identical linked ELF confirms this is not just a missing source
annotation:

- 0x8003202C calls guMtxL2F.
- guMtxL2F at 0x800D3FC4 sets integer v0 to its input Mtx pointer, and
  increments it by 4 on each of eight iterations (0x800D4034).
  On return, v0 is the input Mtx pointer plus 0x20. This is an incidental
  register value from a void SDK function, not an SDK return contract.
- 0x80032044 calls func_8002CDC0. There is no intervening write to v0.
- The complete [0x8002CDC0, 0x8002CF70) function writes no integer v0.
  Its floating-point f0 is a different register and does not supply the
  caller's integer status. The function returns at 0x8002CF68.
- 0x8003204C branches on integer v0. For a valid ordinary Mtx pointer,
  the inherited pointer+0x20 is nonzero, bypassing the diagnostic and
  identity fallback at 0x80032054-0x80032068.

Thus the apparent success/failure check is not a determinant or singularity
test in the shipped instruction stream. A name or documentation implying a
reliable status result would be misleading. Do not change the return type,
add a return, or repair the caller within this identifier-only pass.

## Pause: matrix preconditions and mutation need a wider audit

The inverse candidate divides the entire 3x3 basis by the squared length
of its first row, transposes it into a second matrix, and computes inverse
translation. This is the inverse for a nonzero uniformly scaled orthogonal
basis; it is not a general affine inverse. It modifies the input basis.

The producer `func_8003031C` (1222-1245) initializes that input at object
+1B8, applies translation and rotations, then permits three separate scale
components (+210/+214/+218) and an optional caller-supplied matrix.
It does not locally require equal scales or an orthogonal basis. Whether
the actual asset/call paths restrict those inputs remains unestablished.
There is also no zero-length guard in the inverse candidate.

The reflection caller only sets its +3B gate on the apparent failure route,
which the inherited valid pointer normally bypasses. Therefore a repeated
call with +3B still zero can revisit and modify the same input basis.
For scale magnitude s, one application changes the input basis scale to
1/s; another application without rebuilding would change it back. This
is a conditional mathematical consequence, not a claim that gameplay
actually reaches such repeated non-unit-scale calls.

## Resume with deliberate investigation

Pause further naming here after the independently verified vector-helper
batch. Preserve the current inverse spelling and all existing bytes.
The next investigation should establish:

1. Actual scale values and optional matrices supplied to func_8003031C.
2. When that matrix is rebuilt relative to repeated reflection setup and
   how +3B is reset or set on all relevant paths.
3. How to describe the destructive specialized inverse accurately while
   keeping the shipped register behavior separate from any intended API.

No corrective implementation or broad type reconstruction is part of that
investigation. The linked ROM remains the preservation gate. Supporting
disassembly is retained in analysis/semantic/batch_004_inverse_disassembly.txt;
current rename acceptance is in batch_004_validation.json and
batch_004_verification.json.
