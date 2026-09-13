#!/usr/bin/env python3
"""EXTRACT the D_736C50 texture archive into committable source.

  extract_736C50.py <D_736C50.bin> <outdir>

Writes:
  <outdir>/manifest.json           per-asset {index, kind, raw, pad(hex)}
  <outdir>/asset_NNN.bin           decoded big-endian u16 buffer (kind=comp)
                                   or stored payload verbatim (kind=stored)
                                   (kind=empty writes no file)

The buffers are the real decompressed texture data (big-endian, N64 order);
build_736C50.py re-compresses them into a byte-identical archive.
"""
import sys, os, json, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lz736

def main():
    region = open(sys.argv[1], "rb").read()
    outdir = sys.argv[2]
    os.makedirs(outdir, exist_ok=True)
    count, offs = lz736.parse_container(region)
    nassets = count - 1
    assert offs[0] == 2 + count*4, "table_end mismatch"
    manifest = {"archive": "D_736C50", "count": count, "assets": []}
    for k in range(nassets):
        s, e = offs[k], offs[k+1]
        if s == e:
            manifest["assets"].append({"i": k, "kind": "empty"})
            continue
        assert region[s:s+2] == lz736.MAGIC_J, f"asset {k} not 'J'"
        assert region[s+6:s+10] == lz736.MAGIC_SQSH, f"asset {k} not SQSH"
        raw = struct.unpack_from(">I", region, s+0xA)[0]
        comp = struct.unpack_from(">I", region, s+0xE)[0]
        payload = region[s+0x12 : s+0x12+comp]
        used = 6 + 0xC + comp
        pad = region[s+used : e]
        assert len(pad) == (comp & 1), f"asset {k} pad size"
        ent = {"i": k, "raw": raw, "pad": pad.hex()}
        if raw == comp:
            ent["kind"] = "stored"
            buf = payload                       # verbatim
        else:
            ent["kind"] = "comp"
            data = lz736.decode_block(payload)  # list[u16]
            assert len(data) == (raw + 1)//2, f"asset {k} decode len"
            buf = b"".join(struct.pack(">H", v) for v in data)  # BE u16 stream
        open(os.path.join(outdir, f"asset_{k:03d}.bin"), "wb").write(buf)
        manifest["assets"].append(ent)
    with open(os.path.join(outdir, "manifest.json"), "w") as f:
        json.dump(manifest, f, indent=1)
    n_e = sum(a["kind"]=="empty" for a in manifest["assets"])
    n_s = sum(a["kind"]=="stored" for a in manifest["assets"])
    n_c = sum(a["kind"]=="comp" for a in manifest["assets"])
    print(f"extracted {nassets} assets -> {outdir}  (comp={n_c} stored={n_s} empty={n_e})")

if __name__ == "__main__":
    main()
