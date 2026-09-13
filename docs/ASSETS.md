# Tetrisphere asset formats

The back **7.2 MB** of the ROM (`0x000CD3F0 .. 0x00800000`, ~90% of the cart) is asset
data. In `tetrisphere.yaml` it is currently a single opaque segment
(`type: bin, start: 0xCD3F0` → `assets/CD3F0.bin`). This document records what that blob
is, how it decodes, and the tooling that can recreate parts of it byte-exactly.

> **Priority:** asset work is *lowest priority*, behind the code decompilation. This is a
> map for when we get there, not an active work front.
>
> **Repo policy:** `assets/` is gitignored — **no ROM-derived bytes are ever committed**.
> `assets/CD3F0.bin` is regenerated from your own ROM by `make extract`. Asset work ships
> as *tools* + regenerate/verify gates, never as committed decoded data.

## Top-level layout

The blob holds **13 top-level assets**, each named by its 6-hex ROM offset (`D_xxxxxx`).
**8 are offset-table archives**; the rest are raw tables. Total sub-assets ≈ 3,100.

```
container @ base:  u16 count;  u32 offset[count];  u8 data[];
  sub-asset k = bytes [base+offset[k], base+offset[k+1])
  offset[0]      == end of the table (2 + count*4)
  offset[count-1]== archive span  (END SENTINEL)  →  num_assets = count-1
  empty slot     : offset[k]==offset[k+1]  → zero-length asset (aliased offset)
```

| Asset | Sub-assets | Filter | Content |
|---|---|---|---|
| `D_CD3F0` | — | — | 0x180 bitmask tables (→ bss `D_80164E60`) |
| `D_CD570` | — | — | 592 B raw |
| `D_CD7C0` | 874 | — | audio archive |
| `D_15F978`/`D_15F9B8` | — | — | small raw tables |
| `D_1DC6C0` | 421 | S,D | (S-gated) |
| `D_490B10` | 307 | S | **skeletal animation** (bone keyframes) |
| `D_5921F0` | 124 | S | **3D meshes** |
| `D_72A5A0` | 108 | — | |
| `D_736C50` | 303 | **J** | **textures** ✅ recreatable byte-exact |
| `D_7B55B0` | 611 | S | |
| `D_7D4A70` | 342 | — | uniform 20-byte records |
| `D_7D6C00` | 48 | S | solid-color / ramp tiles |

## The loader / codec pipeline ("LW engine")

Assets are DMA'd raw (no segmentation — ROM offset + direct KSEG0 pointers) and decoded by
a **filter-pipeline interpreter**:

- `func_8002A430` (boot.c) — raw `osPiStartDma` cart→RAM copy. **No decompression here.**
- `func_8002A8B4` (boot.c) — DMAs a sub-asset to staging `0x80000400`, then calls the
  interpreter `func_80081BE8` (code_5B5D0.c).
- Stream header: `[u8 numOps][numOps opcode LETTERS][u32 payloadSize][payload]`. The
  interpreter loops the letters and dispatches one decode filter per letter:

| Letter | Function | State |
|---|---|---|
| `D` | `func_800802CC` | C |
| `F` | `func_80080424` | C |
| `H` | `func_80080654` | C |
| `J` | `func_80081444` (+ `func_80081264` LZ) | C ✅ |
| `W` | `func_800819E0` (+ copy `func_80080220`) | C |
| `S` | `func_800807E4` | **asm** |
| `R` | `func_80080B00` | **asm** |
| `A` | `func_80080FF4` | **asm** |

Each asset's letters name its decode chain. **Landing `S` unlocks the bulk** of the
remaining archives (most are S-chains).

## The `J` filter (textures) — fully cracked

`J` is **LZ77 over u16 units**. A `J` asset is one `SQSH` block:

```
asset : [01 'J'][u32 blockSize][SQSH][u32 raw][u32 comp][payload(comp)] + pad(comp & 1)
        blockSize = 0xC + comp ; exactly one SQSH block per asset
        raw  = LOGICAL decompressed byte size (may be ODD; the decoder over-produces the
               final u16's low byte, which is input padding baked into the buffer)
        stored block (raw==comp): payload = raw bytes verbatim (no compression)
```

Token stream: a cmd byte, then
- `cmd & 0x80` → back-reference, `len=(cmd&0x7F)+1` u16s copied from absolute u16 index
  `(p[i]<<8)|p[i+1]` (overlap allowed);
- else literal run, `len=cmd+1` u16s, each stored big-endian.

The original **encoder is reproduced byte-for-byte**: greedy longest-match, min-match 2,
cap 128 u16, whole-buffer window, tie-break **FARTHEST** (smallest target among
equal-length matches), no lazy matching. *Tie-break direction is decisive:* nearest gives
2/300 blocks, farthest 300/300.

Decoded texture payload: `[u16 width][u16 height][u16 fmt][u16 pad][pixels]`,
`w*h*bpp + 8 == size` exactly. **fmt 0 = RGBA16, fmt 2 = CI8** (fmt 4 likely CI4). RGBA16
pixel *bytes* are big-endian on the N64; a little-endian host port must byte-swap for display.

## Other archive payloads (decoded, not yet round-trippable)

- **`D_5921F0` meshes:** header `[0x18][offMaterials][offB][offVerts][offPrims][totalSize][count]`.
  **Vertex = 16 B:** `s16 x,y,z | s16 flag | s16 u,v | u8 r,g,b,a`. Faces live at `@offB` as a
  **nibble-packed, vertex-cache-batched triangle list** (per-block `u16` offset table +
  6-byte batch records + 4-bit indices relative to each batch's first vertex). Verified
  in-range on multiple assets; tools in `pending/session23/model_format.py`,
  `tools/facedump*.py`, `tools/faceverify.py`.
- **`D_490B10` skeletal animation:** record
  `[u32 channelFlags(low 9 bits; popcount=#channels)][u16 time][s16 mode][f32[3*popcount]]`,
  stride `8 + 12*popcount`. (This is NOT geometry — an early mesh reading was wrong.)
- Microcode is **F3D vanilla**; Tetrisphere builds GBI at runtime from float geometry, so
  the meshes are not pre-baked display lists.

## Recreation tooling

`tools/asset_recreate/` (see its `README.md`) recreates `D_736C50` byte-exactly:

- `lz736.py` — `J`/SQSH codec (`decode_block`, `compress`) + container helpers
- `extract_736C50.py` — region → per-asset big-endian u16 buffers + `manifest.json`
- `build_736C50.py` — manifest + buffers → byte-identical archive (`--verify`)
- `verify_736C50.py` — self-contained regenerate-and-round-trip gate straight from
  `assets/CD3F0.bin`; wired as **`make verify-assets`** (scratches in `work/`, never `/tmp`)

Only non-derivable committed metadata beyond the decoded buffers: per-asset `{kind, raw}`
and 157 container-pad bytes (stale-buffer leftovers), all captured in the manifest.

## Plan: full extraction is gated on per-part isolation

The eventual goal is to extract *all* asset data as part of `make extract`. That is **gated**:
decode and prove a **byte-exact round-trip for each archive/filter in isolation first**, then
build the unified extractor. Building the whole-blob extractor before the parts are proven is
scaffolding around unknowns. Each part follows the same three steps:

1. decoder in C (understand the bytes),
2. **byte-exact encoder round-trip** (the real gate — a decoder alone can't rebuild),
3. standalone verify from the extracted region.

Only `J`/`D_736C50` clears all three today. The critical-path item is the **`S` filter**
(`func_800807E4`), which unlocks most of the remaining archives.
