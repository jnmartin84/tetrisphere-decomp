#!/usr/bin/env python3
"""Check saved-thread C ownership and the cumulative BSS/ROM invariants."""
import hashlib
import importlib.util
import json
from pathlib import Path
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
spec = importlib.util.spec_from_file_location(
    "event_bss", ROOT / "pending/session_bss_event_table/verify.py")
event_bss = importlib.util.module_from_spec(spec)
spec.loader.exec_module(event_bss)


def main():
    event_bss.main()
    baseline = json.loads((HERE / "BASELINE.json").read_text())
    source = ROOT / "src/libultra/debug/kdebugserver.c"
    assert source.read_bytes() == (ROOT / "tools/ultralib/src/debug/kdebugserver.c").read_bytes()
    assert hashlib.sha256(source.read_bytes()).hexdigest() == baseline["sdk_source_sha256"]
    assert hashlib.sha256((ROOT / "asm/libultra/os/exceptasm.s").read_bytes()).hexdigest() == \
        baseline["exception_assembly_sha256"]
    sections, symbols, text = event_bss.elf_info(ROOT / "build/src/libultra/debug/kdebugserver.o")
    index = next(i for i, s in enumerate(sections) if s["name"] == ".bss")
    bss = sections[index]
    assert bss["type"] == 8 and bss["size"] == 432 and bss["alignment"] == 16
    assert not text and not any(s["flags"] & 4 and s["size"] for s in sections)
    defined = [s for s in symbols if s["info"] >> 4 and s["index"] != 0]
    assert len(defined) == 1
    thread = defined[0]
    assert thread == dict(name="__osThreadSave", address=0, size=432, info=17, index=index)
    linked_sections, linked_symbols, _ = event_bss.elf_info(ROOT / "build/tetrisphere.us.elf")
    thread = next(s for s in linked_symbols if s["name"] == "__osThreadSave")
    assert thread["address"] == 0x80163CB0 and thread["size"] == 432 and thread["info"] == 17
    assert 0 < thread["index"] < len(linked_sections)
    assert linked_sections[thread["index"]]["name"] == ".main_bss"
    assert not (ROOT / "asm/data/os_bss_e.bss.s").exists()
    for name in ["undefined_syms.txt", "undefined_syms_auto.txt", "undefined_funcs_auto.txt"]:
        assert not re.search(r"^\s*__osThreadSave\s*=", (ROOT / name).read_text(), re.M)
    assert "{ type: .bss, vram: 0x80163CB0, name: libultra/debug/kdebugserver }" in \
        (ROOT / "tetrisphere.yaml").read_text()
    assert "__osThreadSave = 0x80163CB0; // size:0x1B0" in (ROOT / "symbol_addrs.txt").read_text()
    print("C OWNERSHIP: 432-byte OSThread at 0x80163CB0, exact allocation, no debugger instructions.")


if __name__ == "__main__":
    main()
