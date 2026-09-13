#!/usr/bin/env python3
"""
Tetrisphere (N64) asset-format spec + extractors, recovered by reading the
LW-engine model parser (func_8002CF70 / func_8002DFA0) and the code_8170
animation appliers, then verifying against decoded assets.

TWO distinct asset families live in the ROM, both loaded through the same
archive loader func_8002A8B4(archive, index, 8):

  * D_490B10  (func_8002A0C0)  -> SKELETAL ANIMATION assets   (header word0 == 0x14)
  * D_5921F0  (func_8002A100)  -> STATIC MESH assets          (header word0 == 0x18)

--------------------------------------------------------------------------------
D_5921F0 STATIC MESH HEADER   (big-endian u32, byte offsets into decoded blob)
    +0x00  u32  0x00000018            format tag
    +0x04  u32  offMaterials          -> [u32 offsets...] material list
    +0x08  u32  offB                  -> FACE / triangle data  (see below)
    +0x0C  u32  offVerts              -> vertex table (16-byte records)
    +0x10  u32  offPrims              -> per-batch aux descriptor table (8-byte)
    +0x14  u32  totalSize             == len(decoded)
    +0x18  u32  count                 (material groups)

  VERTEX RECORD (16 bytes), section @offVerts:
      +0x00 s16 x, +0x02 s16 y, +0x04 s16 z   <- POSITION (signed 16-bit units)
      +0x06 s16 flag/aux
      +0x08 s16 u, +0x0A s16 v                <- texcoords
      +0x0C u8  r,g,b,a                        <- per-vertex Gouraud colour
      vertexCount = (offPrims - offVerts) / 16

--------------------------------------------------------------------------------
FACE FORMAT  (section @offB) -- fully decoded & verified
--------------------------------------------------------------------------------
The @offB section is a nibble-packed, vertex-cache-batched triangle-list format,
i.e. the N64 "load a batch of vertices, then draw triangles with small cache-
relative indices" model, stored compactly.  Layout:

  offB SECTION
    +0x00  u16[T]  block offset table.  Entry i = byte offset (relative to offB)
                   of block i.  The table length T is implicit: entry[0] points
                   just past the table, so T = entry[0] / 2.

  BLOCK  (one per hardware mesh chunk; there are T of them)
    +0x00  u16  numBatches
    +0x02  u16  nibDataOffset   (byte offset, relative to block start, of the
                                 packed triangle-index nibble stream)
    +0x04  numBatches x 6-byte BATCH RECORD:
               +0x00 u16  firstVtx    global base vertex index for this batch
                                       (cumulative: batch0.firstVtx of block0 is
                                        0, and each following firstVtx == the
                                        running sum of all previous vtxCounts)
               +0x02 u8   0           (reserved / always 0)
               +0x03 u8   vtxCount    number of vertices this batch "loads"
                                       (<= 16, the nibble range)
               +0x04 u8   triCount    number of triangles drawn from this batch
               +0x05 u8   0           (reserved / always 0)
    @nibDataOffset  packed nibble stream:
               For each batch in order, triCount triangles are emitted; each
               triangle is 3 consecutive 4-bit nibbles (high nibble of a byte
               first, then low nibble).  A nibble value n (0..vtxCount-1) is a
               vertex index RELATIVE to that batch: global index = firstVtx + n.
               The nibble stream is packed CONTINUOUSLY across batches within a
               block (a batch with an odd 3*triCount can leave the next batch
               starting mid-byte); it restarts byte-aligned at each block.

  The blocks/batches together partition the whole offVerts array: the sum of all
  vtxCount equals vertexCount, and every emitted index is < vertexCount.  Because
  each batch owns a disjoint vertex range (no sharing across batches), the
  triangle/vertex ratio is ~0.6-0.8 rather than the ~2.0 of a fully-shared mesh.

  offPrims (@offP) is an auxiliary table of 8-byte records ("00 02 08 08 .. off")
  plus 0xBDEF padding; it is a per-group index/material map and is NOT needed to
  recover geometry -- all connectivity lives in @offB.

Verified against decoded D_5921F0 assets 12 (controller, 4705v -> 3558 tris),
19 (2621v -> 1808 tris) and 84 (5713v -> 3269 tris): 100% of indices in range,
zero degenerate triangles, sum(vtxCount)==vertexCount exactly, and average
triangle edge length ~2.5-7% of the model bounding-box diagonal (spatially
coherent real triangles).
"""
import struct


def _u32(d, o): return struct.unpack_from(">I", d, o)[0]
def _u16(d, o): return struct.unpack_from(">H", d, o)[0]
def _s16(d, o): return struct.unpack_from(">h", d, o)[0]


def _popcount9(x): return bin(x & 0x1FF).count("1")


# ----------------------------------------------------------------------------
# D_490B10 skeletal-animation asset  (word0 == 0x14)
# ----------------------------------------------------------------------------
def parse_animation(decoded):
    d = decoded
    assert _u32(d, 0) == 0x14, "not a 0x14 animation asset"
    off_skel = _u32(d, 4); off_trk = _u32(d, 8); total = _u32(d, 0x10)
    bone_count = _u32(d, off_skel); track_count = _u32(d, off_trk)
    trk_offs = [_u32(d, off_trk + 4 + 4 * i) for i in range(track_count)]
    trk_bounds = trk_offs + [total - off_trk]
    tracks = []
    for i in range(track_count):
        base = off_trk + trk_offs[i]; end = off_trk + trk_bounds[i + 1]
        tracks.append({"offset": base, "keyframes": _scan_keyframes(d, base, end)})
    return {"boneCount": bone_count, "trackCount": track_count,
            "totalSize": total, "tracks": tracks}


def _scan_keyframes(d, base, end):
    o = base
    while o + 8 <= end:
        fl = _u32(d, o)
        if 1 <= fl <= 0x1FF:
            nch = _popcount9(fl); stride = 8 + 12 * nch
            nxt = _u32(d, o + stride) if o + stride + 4 <= end else None
            if nxt is not None and 1 <= nxt <= 0x1FF:
                break
        o += 4
    kfs = []
    while o + 8 <= end:
        fl = _u32(d, o)
        if not (1 <= fl <= 0x1FF):
            break
        nch = _popcount9(fl); stride = 8 + 12 * nch
        if o + stride > end:
            break
        vals = [struct.unpack_from(">f", d, o + 8 + 4 * k)[0] for k in range(3 * nch)]
        kfs.append({"flags": fl, "time": _u16(d, o + 4), "mode": _s16(d, o + 6),
                    "channels": vals})
        o += stride
    return kfs


# ----------------------------------------------------------------------------
# D_5921F0 static mesh asset  (word0 == 0x18)
# ----------------------------------------------------------------------------
def extract_faces(decoded):
    """Return the triangle list of a D_5921F0 mesh as [[i,j,k], ...] where i/j/k
    index the positions list produced by extract_mesh().  See module docstring
    for the @offB nibble-packed, vertex-cache-batched format."""
    d = decoded
    assert _u32(d, 0) == 0x18, "not a 0x18 mesh asset"
    off_b = _u32(d, 0x08)
    ntab = _u16(d, off_b) // 2
    table = [_u16(d, off_b + 2 * i) for i in range(ntab)]
    faces = []
    for rel in table:
        base = off_b + rel
        num_batch = _u16(d, base)
        nib_off = _u16(d, base + 2)
        recs = []
        for j in range(num_batch):
            r = base + 4 + j * 6
            recs.append((_u16(d, r), d[r + 3], d[r + 4]))  # firstVtx, vtxCount, triCount
        # continuous nibble reader (hi nibble first), shared across batches in block
        pos = [base + nib_off]
        half = [0]

        def next_nib():
            b = d[pos[0]]
            if half[0] == 0:
                half[0] = 1
                return (b >> 4) & 0xF
            half[0] = 0
            pos[0] += 1
            return b & 0xF

        for first_vtx, _vtx_count, tri_count in recs:
            for _ in range(tri_count):
                a = first_vtx + next_nib()
                b = first_vtx + next_nib()
                c = first_vtx + next_nib()
                faces.append([a, b, c])
    return faces


def extract_mesh(decoded):
    """Extract vertex positions, colours and triangle faces from a D_5921F0 mesh.
    Returns {"positions":[[x,y,z],...], "colors":[[r,g,b,a],...],
             "faces":[[i,j,k],...]}."""
    d = decoded
    assert _u32(d, 0) == 0x18, "not a 0x18 mesh asset"
    off_verts = _u32(d, 0x0C)
    off_prims = _u32(d, 0x10)
    nverts = (off_prims - off_verts) // 16
    positions, colors = [], []
    for i in range(nverts):
        o = off_verts + i * 16
        positions.append([_s16(d, o), _s16(d, o + 2), _s16(d, o + 4)])
        colors.append(list(d[o + 12:o + 16]))
    return {"positions": positions, "colors": colors, "faces": extract_faces(d)}


def extract_model(decoded):
    tag = _u32(decoded, 0)
    if tag == 0x18:
        return extract_mesh(decoded)
    if tag == 0x14:
        raise ValueError("this is a D_490B10 skeletal-animation asset "
                         "(no static mesh); use parse_animation()")
    raise ValueError("unknown asset tag 0x%X" % tag)


if __name__ == "__main__":
    import sys, math
    sys.argv = ["x", "assets/CD3F0.bin"]
    exec(open("pending/session23/lwrender2.py").read().split("if __name__")[0])
    print("=== D_5921F0 mesh assets (positions + faces) ===")
    for idx in (12, 19, 84):
        dec, ops = decode_asset(0x5921F0, idx)
        m = extract_model(dec)
        P, F = m["positions"], m["faces"]
        n = len(P)
        allmax = max(max(t) for t in F)
        oor = sum(1 for t in F if max(t) >= n or min(t) < 0)
        degen = sum(1 for t in F if len(set(t)) < 3)
        print(f"asset {idx}: verts={n} tris={len(F)} maxidx={allmax} "
              f"out_of_range={oor} degenerate={degen} sample={F[:4]}")
