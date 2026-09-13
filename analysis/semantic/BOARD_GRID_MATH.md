# Interpolated board grid and normal tables

2026-09-13. Original baseline `823ca10873a7eafde7d68951087cdaf9d3095dfd`.
Batch 005 follows accepted semantic HEAD `21b41c8`. The user explicitly
redirected research away from the affine inverse; that routine stays
documented and deferred, and does not block other semantic work.

## Grid construction

`func_800ADD6C` -> **buildInterpolatedBoardGrid** (game2.c:13964-14070).
The function reads the signed coordinate table D_800E3CD8, whose source is
asm/data/BAAB0.data.s:7370 onward. Each table row has 18 triples (54 s16).
For each of 16 output rows it reads adjacent input rows; for each of 16
output columns it interpolates adjacent triples in those rows.

Its two s16 arguments are shifted left by eight for 16-bit fractional
weights. The only caller (26428) passes the complemented low byte of the
latched horizontal view coordinate and the low byte of the vertical one.
Ignoring the explicit fixed-point rounding/narrowing solely to explain the
weights, for input coordinate T and fractions a=arg0/256, b=arg1/256:

`H(j) = T(i,j) + a * (T(i+1,j) - T(i,j))`

`result = H(j+1) + b * (H(j) - H(j+1))`

Thus the second interpolation runs from the next column toward the current
column. Actual code performs signed shifts, s16 intermediate narrowing,
and a final shift by five. Do not replace its expression with an algebraic
bilinear formula or change evaluation order.

The output D_800E44E4 contains 16x16 records, six s16 per point:

| Record fields | Role |
|---|---|
| [0..2] | Base position: interpolated/scaled coordinate divided by 3 |
| [3..5] | Radial layer step: same coordinate divided by 10 |

Optional per-axis scaling comes from player offsets +247A/+247C/+247E,
divided by 0x4000 when +2478 is nonzero. Each scale is capped above at
0x4000 before the loop; there is no lower clamp here. Multiplayer offsets
only base field [0] by +64 for context 1 or -32 otherwise. The step is not
translated. The renderer consumes components in [1], [0], [2] order, so
these storage fields should not be globally renamed x/y without that audit.

The base/step interpretation is directly supported by layer-7 rendering at
9552-9572: it forms base + 7*step and base + 6*step for upper/lower corners.
The base-only rendering path at 9757-9773 reads the first triple. This is
geometry for the visible 15x15 cells, bounded by a 16x16 point grid; it is
not the full wrapped 32x32 logical board storage.

## Lighting tables

`func_800A2374` -> **buildBoardNormalTables** (10141-10221).
It reads the grid and produces three signed-vector tables:

| Destination | Calculation |
|---|---|
| D_8015EED0 | 256 inward radial vectors, using each point's step triple |
| D_8015EE20 | 15 adjacent-point differences across output row 7 |
| D_8015EDC0 | 15 adjacent-row differences down output column 7 |

For the radial table it uses the reordered vector (step[1],step[0],step[2])
and multiplies by -120/length. The two directional tables use reordered
base-position differences and multiply by +120/length. Results truncate to
s16, so their stored lengths need not be exactly 120. When squared length
is <=0 the existing code substitutes length=1; all arithmetic stays intact.

The row-7 starting s16 offset is 0x2A0 = 7*16*6, advanced by six per point.
The column-7 offset is 0x2A = 7*6, advanced by 0x60 per row. These are
specific sampled rows/columns, not per-cell cross products.

Consumers at 8899-8934 and 9573-9611 copy the radial table into the four
corner normal triples and the directional tables into opposing side-normal
triples, negating the opposite side as written. Those scratch vectors feed
the renderer's Vtx normal fields (for example 9817-9825). The render setup
func_800A348C builds the tables at 10390 before dispatching cell renderers.

Both functions are game-specific table/renderer processing in game2.c.
The normal builder calls SDK sqrtf but does not rename or replace it.
No libultra, n_audio or assembly input changes in this batch.

## Scope and continuation

All 997 production inputs were inventoried. Each chosen name has only a
definition and one call in game2.c; A2374 also occurs in an unchanged
historical comment. Four identifier substitutions, with no collisions or
linker aliases. See batch_005.json and the independent lexical and ROM
verification reports for acceptance. No runtime performance or visual
improvement is claimed.

The game also has a separate per-cell normal recomputation path,
func_8009849C (7465-7523), used by specialized rendering/effects. Its exact
caller-specific geometry is a next research target. Field/type names and
the entire render driver remain outside the current batch.
