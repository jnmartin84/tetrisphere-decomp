#!/usr/bin/env python3
"""Self-contained round-trip gate for the D_736C50 texture-archive recreation.

Carves the D_736C50 region straight out of the committed assets/CD3F0.bin, runs
extract -> build in a temp dir, and asserts the rebuilt archive is byte-identical
to the original region.  No committed decoded source required; exits nonzero on
any mismatch.  Wired as `make verify-assets`.
"""
import sys, os, tempfile, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lz736, extract_736C50, build_736C50

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.normpath(os.path.join(HERE, "..", ".."))
BLOB = os.path.join(REPO, "assets", "CD3F0.bin")
SCRATCH = os.path.join(REPO, "work")          # gitignored; never /tmp (reboot-wiped here)
BASE = 0xCD3F0
ROM = 0x736C50
NXT = 0x7B55B0

def main():
    blob = open(BLOB, "rb").read()
    region = blob[ROM-BASE : NXT-BASE]
    os.makedirs(SCRATCH, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=SCRATCH) as td:
        ref = os.path.join(td, "ref.bin")
        open(ref, "wb").write(region)
        srcdir = os.path.join(td, "src")
        sys.argv = ["extract", ref, srcdir]; extract_736C50.main()
        out = build_736C50.build(srcdir)
    if out == region:
        print(f"D_736C50 recreation: BYTE-EXACT round-trip ({len(region)} bytes) OK")
        return 0
    fd = next((i for i in range(min(len(out),len(region))) if out[i]!=region[i]), min(len(out),len(region)))
    print(f"D_736C50 recreation: MISMATCH @0x{fd:X} out={out[fd:fd+12].hex()} ref={region[fd:fd+12].hex()}")
    return 1

if __name__ == "__main__":
    sys.exit(main())
