# Game-side math: vector rotations

Recorded 2026-09-13. Baseline commit
`823ca10873a7eafde7d68951087cdaf9d3095dfd`; batch 003 extends the accepted
semantic branch at `a8bf617`. Only two function identifiers are renamed.

## Ownership boundary

The selected functions are in `src/code_8170.c`, a game-side translation
unit with object/animation/light processing. Both have one caller in that
same file, `func_80030EB4`. Neither is an SDK entry point or a fixed-address
linker alias. They use `sinf` and `__cosf`, which remain SDK functions.

The supplied `src/libultra/gu/rotaterpy.c` implements the separate
`guRotateRPYF_2` / `guRotateRPY_2` matrix builders, with SGI source provenance;
it does not implement these vector-pointer wrappers. The Makefile lists
code_8170 and libultra as distinct compilation inputs. The older GU copy,
libultra source, n_audio, compiler runtime, trigonometric functions and all
SDK symbols are outside this batch. This establishes the repository's
game/SDK boundary, not the historical authorship of every mathematical idea.

## Exact transformations

Both signatures take three float angles followed by three float pointers.
Those pointers supply and receive vector components x, y, z in place.
Angles use the existing degree conversion literal `0.017453293`, evaluated
via double multiplication and then stored as float. Preserve that literal,
precision, evaluation order and all stores exactly.

The angle parameters have a non-obvious order:

| Existing argument | Role |
|---|---|
| arg0 | Rotation about Y, in degrees |
| arg1 | Rotation about X, in degrees |
| arg2 | Rotation about Z, in degrees |
| arg3 / arg4 / arg5 | Pointers to x / y / z |

Using column-vector notation and distinct component storage, the elementary
operations are the standard signed axis rotations:

- Z: `(x*c - y*s, x*s + y*c, z)`
- X: `(x, y*c - z*s, y*s + z*c)`
- Y: `(x*c + z*s, y, -x*s + z*c)`

`func_8002FD9C`, code_8170.c:1030-1058, applies Z, then X, then Y:
`v_out = Ry(arg0) Rx(arg1) Rz(arg2) v_in`.
Its name is **rotateVectorZXYDegrees**. The suffix denotes the order applied
to the vector, not the written matrix-product order or argument order.

`func_8002FF08`, code_8170.c:1064-1092, applies Y, then X, then Z:
`v_out = Rz(arg2) Rx(arg1) Ry(arg0) v_in`.
Its name is **rotateVectorYXZDegrees**.

The second reverses the first when all three angles are negated, within
floating-point rounding. It is not intrinsically an inverse operation for
the same input angles. Neither translates or normalizes the vector.
No aliasing guarantees for overlapping component pointers are inferred.

## Concrete caller: light direction

`func_80030EB4`, code_8170.c:1362-1394, initializes `(x,y,z)=(0,0,120)`
for each light record. It applies the first helper with that record's
three angles, then the second with object angles `(-a,-b,+c)` from
+204/+208/+20C. It stores `(x,y,-z)` at bytes 8/9/A of each 16-byte light
record. Nearby lighting code uses the libultra Light layout and `gSPLight`
(1325-1343). Thus these are useful game-side lighting transformations.
The caller's mixed signs and final Z negation are retained, not folded into
an assumed generic inverse/view transform.

## Checks and unresolved math

`math_rotation_probe.py` extracts just the two baseline function bodies,
compiles a temporary host library and compares them with independently
composed axis matrices. It checks zero rotation, 90-degree basis vectors
and 100 deterministic mixed-angle/vector cases: 220 order checks and 110
inverse-composition checks passed. The maximum order error divided by
`max(1, vector length)` was about 1.22e-7, below the 2e-6 bound.
This checks the naming interpretation; it is not target floating-point
validation. The independent identifier and linked whole-ROM gates remain
the acceptance authority for the source edits.

An additional candidate is `func_8002CDC0` at code_8170.c:8-48. It divides
the 3x3 by the squared length of its first row, transposes it and computes
the inverse translation. This gives an affine inverse for an orthogonal,
uniformly scaled basis, not an arbitrary affine matrix. It also mutates
the input matrix and declares an integer result without returning one;
its caller at 1706 tests that result. Leave it unrenamed pending a focused
caller/precondition audit. No corrective edits are authorized by this note.

There is also game-specific normalization and geometric interpolation in
game2.c (for example 7450-7523 and 13964-14063). These remain candidates
for a later bounded pass; the current batch makes no exhaustive math claim.

## Rename inventory and acceptance

Inventory spans all 997 manifested production inputs. Each chosen name has
one definition and one call in code_8170.c: four identifier substitutions.
The old names also occur in tetrisphere.yaml comments (253-254); those
comments are preserved. No proposed new name preexists. There are no other
production references or fixed-address aliases requiring edits.

See cumulative `batch_003.json`, `batch_003_inventory.json`,
`batch_003_math_probe.json`, `batch_003_validation.json`, and
`batch_003_verification.json` in the semantic worktree's analysis directory.
The research note itself does not substitute for acceptance evidence.
