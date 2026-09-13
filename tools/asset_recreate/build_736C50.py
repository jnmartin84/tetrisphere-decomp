#!/usr/bin/env python3
"""BUILD the D_736C50 texture archive byte-exactly from committed source.

  build_736C50.py <indir> <out.bin> [--verify <reference.bin>]

Reads <indir>/manifest.json + asset_NNN.bin, re-compresses each 'comp' asset with
the ROM's greedy 'J' encoder, reassembles the SQSH wrappers, offset table, and
padding, and writes <out.bin>.  With --verify, asserts byte-equality vs a reference
region and exits nonzero on any mismatch.
"""
import sys, os, json, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lz736

def build(indir):
    manifest = json.load(open(os.path.join(indir, "manifest.json")))
    count = manifest["count"]
    nassets = count - 1
    table_end = 2 + count*4
    offs = []
    data_area = bytearray()
    cur = table_end
    for ent in manifest["assets"]:
        offs.append(cur)
        kind = ent["kind"]
        if kind == "empty":
            continue
        buf = open(os.path.join(indir, f"asset_{ent['i']:03d}.bin"), "rb").read()
        raw = ent["raw"]
        pad = bytes.fromhex(ent["pad"])
        if kind == "stored":
            payload = buf                        # verbatim
            assert len(payload) == raw
        else:                                    # comp
            data = list(struct.unpack(f">{len(buf)//2}H", buf))
            payload = lz736.compress(data)
        asset = lz736.build_asset(kind, raw, payload, pad)
        data_area += asset
        cur += len(asset)
    offs.append(cur)                             # end sentinel
    out = bytearray(struct.pack(">H", count))
    for o in offs:
        out += struct.pack(">I", o)
    out += data_area
    return bytes(out)

def main():
    indir, outpath = sys.argv[1], sys.argv[2]
    out = build(indir)
    open(outpath, "wb").write(out)
    print(f"built {outpath}  ({len(out)} bytes)")
    if "--verify" in sys.argv:
        ref = open(sys.argv[sys.argv.index("--verify")+1], "rb").read()
        if out == ref:
            print(f"*** VERIFY: BYTE-EXACT vs reference ({len(ref)} bytes) ***")
        else:
            fd = next((i for i in range(min(len(out),len(ref))) if out[i]!=ref[i]), min(len(out),len(ref)))
            print(f"!!! VERIFY MISMATCH @0x{fd:X}  out={out[fd:fd+12].hex()} ref={ref[fd:fd+12].hex()}  (len out={len(out)} ref={len(ref)})")
            sys.exit(1)

if __name__ == "__main__":
    main()
