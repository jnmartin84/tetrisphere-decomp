#!/usr/bin/env python3
"""ORACLE EXPERIMENT: greedy 'J'-filter LZ encoder vs the ROM's real bytes.
For every compressed block in D_736C50: decode it, re-compress with a greedy
longest-match (min-2, whole-block window) encoder, and compare our compressed
bytes to the original. Reports exact-match rate + where we diverge."""
import struct, sys, collections

BASE = 0xCD3F0
blob = open(sys.argv[1], "rb").read()
TIE = sys.argv[3] if len(sys.argv) > 3 else "near"   # 'near' (largest tgt) or 'far' (smallest)
LAZY = "lazy" in sys.argv
def be16(o): return (blob[o] << 8) | blob[o+1]
def be32(o): return (blob[o] << 24) | (blob[o+1] << 16) | (blob[o+2] << 8) | blob[o+3]

def decode_block(off, complen):
    """func_80081264 -> list of u16."""
    out = []; spC = 0
    while spC < complen:
        cmd = blob[off+spC]; spC += 1
        if cmd & 0x80:
            n = (cmd & 0x7F) + 1
            sp4 = (blob[off+spC] << 8) | blob[off+spC+1]; spC += 2
            for _ in range(n): out.append(out[sp4]); sp4 += 1
        else:
            n = cmd + 1
            for _ in range(n): out.append((blob[off+spC] << 8) | blob[off+spC+1]); spC += 2
    return out

def longest_match(data, pos, cand):
    """best (len,tgt) over candidate start positions, min 2, cap 128, overlap ok."""
    n = len(data); maxlen = min(128, n - pos)
    if maxlen < 2: return (0, -1)
    best_len, best_tgt = 0, -1
    order = cand if TIE == "far" else reversed(cand)   # 'near' prefers larger tgt
    for tgt in order:
        if data[tgt] != data[pos]: continue
        k = 1
        while k < maxlen and data[tgt+k] == data[pos+k]: k += 1
        if k > best_len:
            best_len, best_tgt = k, tgt
            if k == maxlen: break
    return (best_len, best_tgt)

def compress(data):
    n = len(data); out = bytearray(); lits = []
    def flush():
        i = 0
        while i < len(lits):
            run = lits[i:i+128]; out.append(len(run)-1)
            for v in run: out.extend(struct.pack(">H", v))
            i += 128
        lits.clear()
    # hash of 2-u16 prefixes -> positions (chronological)
    table = collections.defaultdict(list)
    pos = 0
    while pos < n:
        key = (data[pos], data[pos+1]) if pos+1 < n else None
        cand = table.get(key, []) if key is not None else []
        blen, btgt = longest_match(data, pos, cand) if cand else (0, -1)
        if blen >= 2 and LAZY and pos+1 < n:            # lazy: is next pos better?
            k2 = (data[pos+1], data[pos+2]) if pos+2 < n else None
            c2 = table.get(k2, [])
            # include pos itself as a candidate for pos+1
            nlen, _ = longest_match(data, pos+1, c2 + [pos]) if (c2 or True) else (0, -1)
            if nlen > blen:                             # defer: emit 1 literal
                lits.append(data[pos]); table[key].append(pos) if key else None; pos += 1
                continue
        if blen >= 2:
            flush()
            out.append(0x80 | (blen-1)); out += struct.pack(">H", btgt)
            for p in range(pos, pos+blen):
                if p+1 < n: table[(data[p], data[p+1])].append(p)
            pos += blen
        else:
            lits.append(data[pos])
            if key: table[key].append(pos)
            pos += 1
    flush()
    return bytes(out)

rom = int(sys.argv[2], 16); cnt = be16(rom-BASE) - 1
exact = 0; total = 0; firstdiffs = collections.Counter(); tokdiff = 0
for idx in range(cnt):
    a = rom - BASE; d = a + be32(a+2+idx*4)
    if blob[d] != 1 or blob[d+1] != ord('J'): continue
    size = be32(d+2); o = d+6; rem = size
    while rem != 0:
        raw = be32(o+4); comp = be32(o+8); o += 0xC; rem -= 0xC
        if raw != comp:
            orig = blob[o:o+comp]
            data = decode_block(o-0xC+0xC, comp)  # o already advanced past header
            mine = compress(data)
            total += 1
            if mine == orig: exact += 1
            else:
                fd = next((i for i in range(min(len(mine), len(orig))) if mine[i] != orig[i]), min(len(mine), len(orig)))
                firstdiffs[fd//64 * 64] += 1
                if len(mine) != len(orig): tokdiff += 1
        o += comp; rem -= comp

print(f"tie={TIE} lazy={LAZY}")
print(f"blocks: {total}   EXACT byte-match: {exact}  ({100*exact/max(total,1):.1f}%)")
print(f"of the misses: {tokdiff} had a different COMPRESSED LENGTH (structural), {total-exact-tokdiff} same length (tie-break/choice)")
print(f"first-diff offset histogram (bucketed): {dict(sorted(firstdiffs.items())[:8])}")
