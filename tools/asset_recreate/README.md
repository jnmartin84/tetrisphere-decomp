# D_736C50 texture-archive recreation

Build-time recreation of the `D_736C50` texture archive (ROM `0x736C50..0x7B55B0`,
518,496 bytes) from decoded texture sources. Proven **byte-exact** round-trip.

## Format

Offset-table container of `SQSH`-wrapped LZ77-on-u16 assets:

```
container : [u16 count][u32 off[count]]        off[0]=table_end; asset k=[off[k],off[k+1])
empty slot: off[k]==off[k+1]                   -> 0 bytes (5 of them; duplicate offsets)
asset     : [01 'J'][u32 size][SQSH][u32 raw][u32 comp][payload(comp)] + pad(comp&1)
            size = 0xC+comp ; exactly one SQSH block/asset
            raw  = LOGICAL decompressed byte size (may be ODD; decoder over-produces
                   the final u16's low byte, which is baked into the decoded buffer)
            stored block (raw==comp): payload = raw bytes verbatim (3 of them)
```

LZ token stream: a cmd byte, then `cmd&0x80` = back-reference
`len=(cmd&0x7F)+1` u16s from absolute u16 index `(p[i]<<8)|p[i+1]` (overlap ok),
else literal run `len=cmd+1` u16s stored big-endian.

The encoder reproduces the ROM byte-for-byte: greedy longest-match, min-match 2,
cap 128 u16, whole-buffer window, tie-break **FARTHEST** (smallest target among
equal-length matches), no lazy matching. Tie-break direction is decisive:
nearest = 2/300 blocks, farthest = 300/300.

## Tools

- `lz736.py`          — codec (`decode_block`, `compress`) + container helpers
- `extract_736C50.py` — `<D_736C50.bin> <outdir>` -> `asset_NNN.bin` (BE u16 buffers)
                        + `manifest.json` (per-asset kind/raw/pad)
- `build_736C50.py`   — `<indir> <out.bin> [--verify <ref.bin>]` -> byte-exact archive
- `verify_736C50.py`  — self-contained round-trip gate straight from `assets/CD3F0.bin`
                        (`make verify-assets`)

Only non-derivable committed metadata beyond the decoded buffers: per-asset
`{kind, raw}` and 157 container-pad bytes (stale-buffer leftovers), all in the
manifest.
