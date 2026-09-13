#!/usr/bin/env python3
"""Codec + container helpers for the Tetrisphere D_736C50 texture archive ('J'/SQSH).

The archive is an offset-table container of SQSH-wrapped LZ77-on-u16 assets:

  container : [u16 count][u32 off[count]]            off[0]=table_end; asset k=[off[k],off[k+1])
  empty slot: off[k]==off[k+1]  -> 0 bytes
  asset     : [01 'J'][u32 size][SQSH][u32 raw][u32 comp][payload(comp)] + pad(comp&1)
              size = 0xC + comp ; ONE SQSH block per asset.
              raw  = LOGICAL decompressed byte size (may be ODD).
              stored block: raw==comp, payload = raw bytes verbatim.

LZ token stream (per payload): a cmd byte, then
  cmd & 0x80 : back-reference, len=(cmd&0x7F)+1 u16s copied from absolute u16 index
               (payload[i]<<8 | payload[i+1]); overlap allowed.
  else       : literal run, len=cmd+1 u16s, each stored big-endian.

Encoder reproduces the ROM byte-for-byte: greedy longest-match, min-match 2, cap 128 u16,
whole-buffer absolute window, tie-break = FARTHEST (smallest target among equal-length matches),
no lazy matching.  (Verified: 300/300 D_736C50 compressed blocks, full-region byte-exact rebuild.)
"""
import struct, collections

MAGIC_J = b'\x01J'
MAGIC_SQSH = b'SQSH'


def decode_block(payload):
    """SQSH 'J' payload -> list[int] of u16 values (len = ceil(raw/2))."""
    out = []; i = 0; n = len(payload)
    while i < n:
        cmd = payload[i]; i += 1
        if cmd & 0x80:
            cnt = (cmd & 0x7F) + 1
            sp = (payload[i] << 8) | payload[i+1]; i += 2
            for _ in range(cnt):
                out.append(out[sp]); sp += 1
        else:
            cnt = cmd + 1
            for _ in range(cnt):
                out.append((payload[i] << 8) | payload[i+1]); i += 2
    return out


def _longest_match(data, pos, cand):
    n = len(data); maxlen = min(128, n - pos)
    if maxlen < 2:
        return (0, -1)
    best_len, best_tgt = 0, -1
    for tgt in cand:                       # ascending == FARTHEST tie-break (first max wins)
        if data[tgt] != data[pos]:
            continue
        k = 1
        while k < maxlen and data[tgt+k] == data[pos+k]:
            k += 1
        if k > best_len:
            best_len, best_tgt = k, tgt
            if k == maxlen:
                break
    return (best_len, best_tgt)


def compress(data):
    """list[int] of u16 values -> SQSH 'J' payload bytes, byte-identical to the ROM encoder."""
    n = len(data); out = bytearray(); lits = []

    def flush():
        i = 0
        while i < len(lits):
            run = lits[i:i+128]; out.append(len(run) - 1)
            for v in run:
                out.extend(struct.pack(">H", v))
            i += 128
        lits.clear()

    table = collections.defaultdict(list); pos = 0
    while pos < n:
        key = (data[pos], data[pos+1]) if pos+1 < n else None
        cand = table.get(key, []) if key is not None else []
        blen, btgt = _longest_match(data, pos, cand) if cand else (0, -1)
        if blen >= 2:
            flush()
            out.append(0x80 | (blen - 1)); out += struct.pack(">H", btgt)
            for p in range(pos, pos + blen):
                if p+1 < n:
                    table[(data[p], data[p+1])].append(p)
            pos += blen
        else:
            lits.append(data[pos])
            if key:
                table[key].append(pos)
            pos += 1
    flush()
    return bytes(out)


# ---- container ----

def parse_container(region):
    """region bytes -> (count, offs list). offs has count entries; nassets=count-1."""
    count = struct.unpack_from(">H", region, 0)[0]
    offs = [struct.unpack_from(">I", region, 2 + i*4)[0] for i in range(count)]
    return count, offs


def build_asset(kind, raw, payload, pad):
    """Assemble one asset's bytes. payload = compressed-or-stored bytes; pad = trailing pad bytes."""
    comp = len(payload)
    size = 0xC + comp
    return (MAGIC_J + struct.pack(">I", size) + MAGIC_SQSH
            + struct.pack(">I", raw) + struct.pack(">I", comp) + payload + pad)
