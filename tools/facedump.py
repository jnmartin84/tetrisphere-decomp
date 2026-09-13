#!/usr/bin/env python3
import sys, struct
sys.argv = ["x", "assets/CD3F0.bin"]
exec(open("pending/session23/lwrender2.py").read().split("if __name__")[0])

def u32(d, o): return struct.unpack_from(">I", d, o)[0]
def u16(d, o): return struct.unpack_from(">H", d, o)[0]
def s16(d, o): return struct.unpack_from(">h", d, o)[0]

def hdr(d):
    return dict(tag=u32(d,0), offMat=u32(d,4), offB=u32(d,8),
               offV=u32(d,0xC), offP=u32(d,0x10), total=u32(d,0x14),
               count=u32(d,0x18))

def hexdump(d, start, length, label):
    print(f"--- {label} @0x{start:X} len 0x{length:X} ---")
    o = start
    end = min(start+length, len(d))
    while o < end:
        row = d[o:o+16]
        hexs = " ".join(f"{b:02X}" for b in row)
        print(f"0x{o:05X}: {hexs}")
        o += 16

for idx in (12,):
    dec, ops = decode_asset(0x5921F0, idx)
    h = hdr(dec)
    print(f"=== asset {idx} ops={ops} len=0x{len(dec):X} ===")
    print("header:", {k:hex(v) for k,v in h.items()})
    nverts = (h['offP']-h['offV'])//16
    print("nverts =", nverts)
    # dump region between header end (0x1C) and offMat
    hexdump(dec, 0x1C, min(h['offMat']-0x1C, 0x80), "pre-materials 0x1C..offMat")
    # materials
    hexdump(dec, h['offMat'], min(h['offB']-h['offMat'], 0x80), "materials")
    # offB start
    hexdump(dec, h['offB'], 0x100, "offB start")
    # offP full-ish
    hexdump(dec, h['offP'], min(h['total']-h['offP'], 0x200), "offPrims start")
    # tail of offP
    print("offPrims total bytes =", h['total']-h['offP'], "=", (h['total']-h['offP'])//8, "recs of 8")
