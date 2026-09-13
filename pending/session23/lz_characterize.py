#!/usr/bin/env python3
"""Read the ORIGINAL 'J'-filter compressor's parse straight out of the ROM bytes.
For every block in D_736C50, log each token (literal-run vs back-reference) and
its parameters, so we can infer the exact algorithm the 1997 tool used."""
import struct, sys, collections

BASE = 0xCD3F0
blob = open(sys.argv[1], "rb").read()
def be16(o): return (blob[o] << 8) | blob[o+1]
def be32(o): return (blob[o] << 24) | (blob[o+1] << 16) | (blob[o+2] << 8) | blob[o+3]

matchlen = collections.Counter()   # back-ref lengths
litlen   = collections.Counter()   # literal-run lengths
dist     = collections.Counter()   # back-ref distance buckets (pos - target)
n_lit = n_ref = 0
min_match = 999
short_matches = 0                  # matches of length 1 or 2 (textbook LZ avoids these)

def parse_block(off, complen):
    global n_lit, n_ref, min_match, short_matches
    pos = 0   # output position, in u16 units
    spC = 0
    while spC < complen:
        cmd = blob[off+spC]; spC += 1
        if cmd & 0x80:                                  # back-reference
            n = (cmd & 0x7F) + 1
            tgt = (blob[off+spC] << 8) | blob[off+spC+1]; spC += 2
            matchlen[n] += 1; n_ref += 1
            d = pos - tgt
            dist[1 << (d.bit_length())] += 1            # power-of-two bucket
            min_match = min(min_match, n)
            if n <= 2: short_matches += 1
            pos += n
        else:                                           # literal run
            n = cmd + 1
            litlen[n] += 1; n_lit += 1
            spC += 2*n
            pos += n

def walk_asset(rom, idx):
    a = rom - BASE
    off0 = be32(a+2+idx*4)
    d = a + off0
    nops = blob[d]
    if nops != 1 or blob[d+1] != ord('J'): return
    size = be32(d+2); o = d+6; rem = size
    while rem != 0:
        raw = be32(o+4); comp = be32(o+8); o += 0xC; rem -= 0xC
        if raw != comp: parse_block(o, comp)
        o += comp; rem -= comp

rom = int(sys.argv[2], 16)
cnt = be16(rom-BASE) - 1
for i in range(cnt):
    try: walk_asset(rom, i)
    except: pass

print(f"tokens: {n_lit} literal-runs, {n_ref} back-references")
print(f"min match length actually emitted: {min_match} u16  (matches of len<=2: {short_matches})")
print(f"match-length distribution (top): {dict(matchlen.most_common(8))}")
print(f"  ... max match len emitted: {max(matchlen) if matchlen else 0} (format cap = 128)")
print(f"literal-run length (top): {dict(litlen.most_common(6))}  max={max(litlen) if litlen else 0}")
print(f"back-ref distance, power-of-2 buckets (u16 units): {dict(sorted(dist.items()))}")
