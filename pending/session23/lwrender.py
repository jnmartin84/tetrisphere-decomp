#!/usr/bin/env python3
"""Decode Tetrisphere 'J'-filter (LZ77-on-u16) sub-assets and render the
textures to PNG. Ported from src/code_5B5D0.c func_80081444/func_80081264.
Header of decoded asset: [u16 w][u16 h][u16 fmt][u16 pad][pixels] (big-endian).
fmt = N64 G_IM_FMT: 0=RGBA(16b/5551), 2=CI(8b, grayscale here — palette is separate)."""
import struct, zlib, sys, os

BASE = 0xCD3F0
blob = open(sys.argv[1], "rb").read()
def be16(o): return (blob[o] << 8) | blob[o+1]
def be32(o): return (blob[o] << 24) | (blob[o+1] << 16) | (blob[o+2] << 8) | blob[o+3]

def lz_block(off, complen):
    """func_80081264: returns list of u16."""
    out = []
    spC = 0
    while spC < complen:
        cmd = blob[off+spC]; spC += 1
        if cmd & 0x80:                                  # back-reference
            n = (cmd & 0x7F) + 1
            sp4 = (blob[off+spC] << 8) | blob[off+spC+1]; spC += 2
            for _ in range(n):
                out.append(out[sp4]); sp4 += 1
        else:                                           # literal run
            n = cmd + 1
            for _ in range(n):
                out.append((blob[off+spC] << 8) | blob[off+spC+1]); spC += 2
    return out

def decode_J(payload_off, srclen):
    """func_80081444: block loop. Returns decoded bytes (big-endian)."""
    out = bytearray()
    o = payload_off; rem = srclen
    while rem != 0:
        raw = be32(o+4); comp = be32(o+8)
        o += 0xC; rem -= 0xC
        if raw == comp:                                 # stored
            blk = blob[o:o+comp]
            out += blk
            out += b"\x00" * ((((raw+1)//2)*2) - len(blk))
        else:                                           # LZ
            u16s = lz_block(o, comp)
            for v in u16s: out += struct.pack(">H", v)  # emit big-endian (N64 order)
            pad = (((raw+1)//2)*2) - len(u16s)*2
            out += b"\x00" * max(0, pad)
        o += comp; rem -= comp
    return bytes(out)

def sub_asset(rom, idx):
    a = rom - BASE
    off0 = be32(a+2+idx*4)
    d = a + off0
    nops = blob[d]
    ops = bytes(blob[d+1:d+1+nops])
    size = be32(d+1+nops)
    return ops, d+1+nops+4, size

def rgba5551_to_rgba8(v):
    r = (v >> 11) & 0x1F; g = (v >> 6) & 0x1F; b = (v >> 1) & 0x1F; a = v & 1
    ex = lambda c: (c << 3) | (c >> 2)
    return ex(r), ex(g), ex(b), 255 if a else 0

def write_png(path, w, h, rgba):
    def chunk(t, d): return struct.pack(">I", len(d)) + t + d + struct.pack(">I", zlib.crc32(t+d) & 0xffffffff)
    raw = bytearray()
    for y in range(h):
        raw.append(0)
        raw += rgba[y*w*4:(y+1)*w*4]
    open(path, "wb").write(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
                           + chunk(b"IDAT", zlib.compress(bytes(raw), 9)) + chunk(b"IEND", b""))

def render(rom, idx, outdir):
    ops, poff, size = sub_asset(rom, idx)
    if ops != b"J": return None
    dec = decode_J(poff, size)
    w = struct.unpack_from(">H", dec, 0)[0]
    h = struct.unpack_from(">H", dec, 2)[0]
    fmt = struct.unpack_from(">H", dec, 4)[0]
    px = dec[8:]
    if w == 0 or h == 0 or w > 2048 or h > 2048: return None
    rgba = bytearray(w*h*4)
    if fmt == 0:                                        # RGBA16 / 5551
        for i in range(min(w*h, len(px)//2)):
            v = struct.unpack_from(">H", px, i*2)[0]
            r, g, b, a = rgba5551_to_rgba8(v)
            rgba[i*4:i*4+4] = bytes((r, g, b, a))       # real 1-bit alpha
        kind = "RGBA16"
    elif fmt == 2:                                      # CI8 -> grayscale (no palette)
        for i in range(min(w*h, len(px))):
            g = px[i]
            rgba[i*4:i*4+4] = bytes((g, g, g, 255))
        kind = "CI8(gray)"
    else:
        return None
    path = os.path.join(outdir, f"tex_{idx:03d}.png")
    write_png(path, w, h, rgba)
    return (idx, w, h, kind, len(dec))

if __name__ == "__main__":
    rom = int(sys.argv[2], 16)
    outdir = sys.argv[3]; os.makedirs(outdir, exist_ok=True)
    idxs = [int(x) for x in sys.argv[4:]] if len(sys.argv) > 4 else range(int.from_bytes(b'','big') or 0, 0)
    if not sys.argv[4:]:
        a = rom - BASE; cnt = be16(a) - 1; idxs = range(cnt)
    manifest = []
    for i in idxs:
        try:
            r = render(rom, i, outdir)
            if r: manifest.append(r)
        except Exception as e:
            pass
    for m in manifest: print("%d %dx%d %s decoded=%d" % m)
    print("RENDERED", len(manifest))
