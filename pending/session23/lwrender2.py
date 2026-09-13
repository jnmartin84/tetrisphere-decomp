#!/usr/bin/env python3
"""Full LW-engine decoder: filters J (LZ77-u16), S (LZSS 4KB-ring), D (delta),
chained per the asset's opcode string. Renders textures to PNG.
Ported from src/code_5B5D0.c (J/D) and func_800807E4 asm (S)."""
import struct, zlib, sys, os

BASE = 0xCD3F0
blob = open(sys.argv[1], "rb").read()
def be16(o): return (blob[o] << 8) | blob[o+1]
def be32(o): return struct.unpack_from(">I", blob, o)[0]

# --- 'S' : LZSS with pre-filled 4KB ring (func_800807E4 + func_80080688) ---
def build_dict():
    d = bytearray(0x1000)
    for i in range(0x100): d[i] = i
    for i in range(0x100, 0x200): d[i] = (0x1FF - i) & 0xFF
    for i in range(0x100):
        for j in range(4): d[0x200 + i*4 + j] = i
    for i in range(0x600, 0x1000): d[i] = i & 0xFF
    return d

def filt_S(src):
    win = build_dict(); wp = 0; out = bytearray(); sp = 0; n = len(src)
    while sp < n:
        flag = src[sp]; sp += 1
        if not (flag & 0xF0):                       # literal run (1..16)
            for _ in range(flag + 1):
                b = src[sp]; sp += 1
                win[wp] = b; out.append(b); wp = (wp + 1) & 0xFFF
        else:                                        # back-ref (len 3..17)
            count = (flag >> 4) + 2
            rp = src[sp] + ((flag & 0xF) << 8); sp += 1
            for _ in range(count):
                b = win[rp]; win[wp] = b; out.append(b)
                wp = (wp + 1) & 0xFFF; rp = (rp + 1) & 0xFFF
    return out

# --- 'D' : first-order delta (func_800802CC) ---
def filt_D(src):
    n = len(src); out = bytearray(n)
    if n: out[0] = src[0]
    for i in range(1, n): out[i] = (out[i-1] - src[i]) & 0xFF
    return out

# --- 'J' : LZ77-on-u16 block codec (func_80081444 + func_80081264) ---
def filt_J(src):
    out = bytearray(); o = 0; rem = len(src)
    while rem > 0:
        raw = struct.unpack_from(">I", src, o+4)[0]; comp = struct.unpack_from(">I", src, o+8)[0]
        o += 0xC; rem -= 0xC
        if raw == comp:
            out += src[o:o+comp]; out += b"\x00" * ((((raw+1)//2)*2) - comp)
        else:
            u16s = []; spC = 0
            while spC < comp:
                cmd = src[o+spC]; spC += 1
                if cmd & 0x80:
                    ln = (cmd & 0x7F) + 1; sp4 = (src[o+spC] << 8) | src[o+spC+1]; spC += 2
                    for _ in range(ln): u16s.append(u16s[sp4]); sp4 += 1
                else:
                    ln = cmd + 1
                    for _ in range(ln): u16s.append((src[o+spC] << 8) | src[o+spC+1]); spC += 2
            for v in u16s: out += struct.pack(">H", v)
            out += b"\x00" * max(0, (((raw+1)//2)*2) - len(u16s)*2)
        o += comp; rem -= comp
    return out

FILT = {ord('S'): filt_S, ord('D'): filt_D, ord('J'): filt_J}

def decode_asset(rom, idx):
    a = rom - BASE; d = a + be32(a+2+idx*4)
    nops = blob[d]; ops = bytes(blob[d+1:d+1+nops]); size = be32(d+1+nops)
    data = bytearray(blob[d+1+nops+4 : d+1+nops+4+size])
    for op in ops:
        if op not in FILT: return None, ops
        data = FILT[op](data)
    return data, ops

def write_png(path, w, h, rgba):
    def chunk(t, dd): return struct.pack(">I", len(dd)) + t + dd + struct.pack(">I", zlib.crc32(t+dd) & 0xffffffff)
    raw = bytearray()
    for y in range(h): raw.append(0); raw += rgba[y*w*4:(y+1)*w*4]
    open(path, "wb").write(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
                           + chunk(b"IDAT", zlib.compress(bytes(raw), 9)) + chunk(b"IEND", b""))

def render(rom, idx, outdir, prefix):
    dec, ops = decode_asset(rom, idx)
    if dec is None or len(dec) < 8: return None
    w, h, fmt = struct.unpack_from(">HHH", dec, 0)
    if w == 0 or h == 0 or w > 2048 or h > 2048: return None
    px = dec[8:]; rgba = bytearray(w*h*4)
    bpp = 2 if fmt == 0 else 1
    if w*h*bpp + 8 != len(dec): ok = "MISMATCH"
    else: ok = "ok"
    if fmt == 0:
        for i in range(min(w*h, len(px)//2)):
            v = struct.unpack_from(">H", px, i*2)[0]
            r = (v >> 11) & 0x1F; g = (v >> 6) & 0x1F; b = (v >> 1) & 0x1F; al = v & 1
            ex = lambda c: (c << 3) | (c >> 2)
            rgba[i*4:i*4+4] = bytes((ex(r), ex(g), ex(b), 255 if al else 0))
        kind = "RGBA16"
    elif fmt == 2:
        for i in range(min(w*h, len(px))): g = px[i]; rgba[i*4:i*4+4] = bytes((g, g, g, 255))
        kind = "CI8"
    else: return None
    write_png(os.path.join(outdir, f"{prefix}_{idx:04d}.png"), w, h, rgba)
    return (idx, w, h, kind, ops.decode(), len(dec), ok)

if __name__ == "__main__":
    rom = int(sys.argv[2], 16); outdir = sys.argv[3]; prefix = sys.argv[4]
    os.makedirs(outdir, exist_ok=True)
    cnt = be16(rom-BASE) - 1
    man = []; bad = 0
    for i in range(cnt):
        try:
            r = render(rom, i, outdir, prefix)
            if r:
                man.append(r)
                if r[6] != "ok": bad += 1
        except Exception: bad += 1
    for m in man[:6]: print("%d %dx%d %s ops=%s decoded=%d %s" % m)
    print(f"RENDERED {len(man)}  header-mismatch/err {bad}")
