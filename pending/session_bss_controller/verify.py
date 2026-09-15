#!/usr/bin/env python3
"""Verify the controller/EEPROM C storage and all earlier SDK BSS migrations."""
import hashlib
import importlib.util
import json
from pathlib import Path
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
spec = importlib.util.spec_from_file_location(
    "thread_bss", ROOT / "pending/session_bss_thread_save/verify.py")
thread_bss = importlib.util.module_from_spec(spec)
spec.loader.exec_module(thread_bss)

OBJECTS = {
    "conteepread": (0x80163A40, 0x40, {"__osEepPifRam": (0, 64)}),
    "controller": (0x80163A80, 0x90, {
        "__osContPifRam": (0, 64), "__osContLastCmd": (0x40, 1),
        "__osMaxControllers": (0x41, 1), "__osEepromTimer": (0x48, 32),
        "__osEepromTimerQ": (0x68, 24), "__osEepromTimerMsg": (0x80, 4),
    }),
}


def main():
    thread_bss.main()
    baseline = json.loads((HERE / "BASELINE.json").read_text())
    read = thread_bss.event_bss.elf_info
    linked_sections, linked_symbols, _ = read(ROOT / "build/tetrisphere.us.elf")
    for owner, (address, size, expected) in OBJECTS.items():
        sections, symbols, text = read(ROOT / f"build/src/libultra/io/{owner}.o")
        index = next(i for i, s in enumerate(sections) if s["name"] == ".bss")
        bss = sections[index]
        assert (bss["type"], bss["size"], bss["alignment"]) == (8, size, 16)
        owned = {s["name"]: (s["address"], s["size"]) for s in symbols
                 if s["index"] == index and s["info"] == 17}
        assert owned == expected, f"{owner}: wrong C object layout"
        assert hashlib.sha256(text).hexdigest() == baseline["object_text_sha256"][owner]
        for name, (offset, length) in expected.items():
            symbol = next(s for s in linked_symbols if s["name"] == name)
            assert (symbol["address"], symbol["size"], symbol["info"]) == (address + offset, length, 17)
            assert 0 < symbol["index"] < len(linked_sections)
            assert linked_sections[symbol["index"]]["name"] == ".main_bss"
            for aliases in ["undefined_syms.txt", "undefined_syms_auto.txt", "undefined_funcs_auto.txt"]:
                assert not re.search(r"^\s*" + re.escape(name) + r"\s*=",
                                     (ROOT / aliases).read_text(), re.M)
        assert f"{{ type: .bss, vram: 0x{address:X}, name: libultra/io/{owner} }}" in \
            (ROOT / "tetrisphere.yaml").read_text()
    for name, base, address in [("D_80163A7C", "__osEepPifRam", 0x80163A7C),
                                ("D_80163ABC", "__osContPifRam", 0x80163ABC)]:
        assert f"{name} = {base} + 0x3C;" in (ROOT / "undefined_syms.txt").read_text()
        assert next(s for s in linked_symbols if s["name"] == name)["address"] == address
    assert not (ROOT / "asm/data/os_bss_c.bss.s").exists()
    print("C OWNERSHIP: 208-byte controller/EEPROM interval; seven typed objects and two interior aliases.")
    print("Recovered __osEepromTimer at 0x80163AC8; controller and EEPROM-read object text unchanged.")


if __name__ == "__main__":
    main()
