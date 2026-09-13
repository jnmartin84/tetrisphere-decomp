#!/usr/bin/env python3
"""Catalog the Tetrisphere asset blob: walk each archive's [u16 count][u32 off[]][data]
table, enumerate sub-assets, and sample each head to guess a type."""
import struct, collections

BLOB = "/home/jnmartin84/claude_tetrisphere/assets/CD3F0.bin"
BASE = 0xCD3F0
blob = open(BLOB, "rb").read()

# 13 top-level assets (rom addr, next rom addr) from the D_ symbols
tops = [0xCD3F0,0xCD570,0xCD7C0,0x15F978,0x15F9B8,0x1DC6C0,0x490B10,0x5921F0,
        0x72A5A0,0x736C50,0x7B55B0,0x7D4A70,0x7D6C00,0x800000]

def u16(o): return struct.unpack_from(">H", blob, o)[0]
def u32(o): return struct.unpack_from(">I", blob, o)[0]

def is_archive(rom, nxt):
    """Archive layout: u16 count; u32 off[count] (last = end sentinel); data.
    num_assets = count-1, asset k = [off[k], off[k+1]). Returns off[] or None."""
    o = rom - BASE; span = nxt - rom
    if span < 6: return None
    c = u16(o)
    tbl = 2 + c*4
    if c < 2 or tbl > span: return None
    try:
        offs = [u32(o + 2 + i*4) for i in range(c)]
    except struct.error:
        return None
    if offs[0] != tbl: return None                      # offset[0] must == table end
    if any(offs[i] > offs[i+1] for i in range(c-1)): return None  # monotonic
    if not (span - 0x20 <= offs[-1] <= span): return None  # last off = end sentinel
    return offs

def classify(data):
    if not data: return "empty"
    b = data[:16]
    if len(set(data[:64])) == 1: return "fill(%02x)" % data[0]
    # RSP/RDP display list? first byte a GBI opcode in the DL range, many 8-byte cmds
    if b[0] in (0x01,0x03,0x04,0x05,0x06,0xB8,0xBB,0xBA,0xB9,0xE7,0xDF,0xFD,0xFF):
        return "dlist?"
    # printable ascii run
    if all(32 <= x < 127 or x in (9,10,13) for x in data[:8]): return "ascii?"
    # texture-ish: first word plausible small dims (w,h <= 512) as u16 pair
    w, h = struct.unpack_from(">HH", data, 0)
    if 1 <= w <= 640 and 1 <= h <= 480: return "dims %dx%d?" % (w, h)
    return "bin"

print("== TETRISPHERE ASSET CATALOG ==")
total_sub = 0
for i in range(len(tops)-1):
    rom, nxt = tops[i], tops[i+1]
    span = nxt - rom
    offs = is_archive(rom, nxt)
    if offs is None:
        print("\nD_%06X  RAW  size=0x%X (%d B)  head=%s" %
              (rom, span, span, blob[rom-BASE:rom-BASE+8].hex()))
        continue
    c = len(offs) - 1        # num assets = count-1 (last offset is end sentinel)
    total_sub += c
    kinds = collections.Counter()
    sizes = []
    samples = []
    for k in range(c):
        s, e = offs[k], offs[k+1]
        d = blob[rom-BASE+s: rom-BASE+e]
        sizes.append(e-s)
        cl = classify(d)
        kinds[cl.split()[0].rstrip("?")] += 1
        if k < 5: samples.append("[%d]0x%X:%s" % (k, e-s, cl))
    print("\nD_%06X  ARCHIVE  %d sub-assets  span=0x%X" % (rom, c, span))
    print("   sizes: min=%d max=%d avg=%d" % (min(sizes), max(sizes), sum(sizes)//len(sizes)))
    print("   kinds: %s" % dict(kinds.most_common()))
    print("   first5: %s" % "  ".join(samples))
print("\nTOTAL sub-assets across archives: %d" % total_sub)
