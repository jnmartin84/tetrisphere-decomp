#!/usr/bin/env python3
"""Check C ownership of the boot prefix and all earlier BSS migrations."""
import importlib.util
from pathlib import Path
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
spec = importlib.util.spec_from_file_location(
    "game_eeprom", ROOT / "pending/session_bss_game_eeprom/verify.py")
game_eeprom = importlib.util.module_from_spec(spec)
spec.loader.exec_module(game_eeprom)


def main():
    game_eeprom.main()
    read = game_eeprom.controller_bss.thread_bss.event_bss.elf_info
    sections, symbols, text = read(ROOT / "build/src/boot_state.o")
    index = next(i for i, s in enumerate(sections) if s["name"] == ".bss")
    bss = sections[index]
    assert (bss["type"], bss["size"], bss["alignment"]) == (8, 16, 16)
    assert not text and not any(s["flags"] & 4 and s["size"] for s in sections)
    expected = {"D_800F2040": (0, 4), "D_800F2044": (4, 4),
                "D_800F2048": (8, 2), "D_800F204C": (12, 4)}
    owned = {s["name"]: (s["address"], s["size"]) for s in symbols
             if s["index"] == index and s["info"] == 17}
    assert owned == expected, "Wrong boot-prefix object layout"
    assert len([s for s in symbols if s["info"] >> 4 and s["index"] != 0]) == 4
    linked_sections, linked_symbols, _ = read(ROOT / "build/tetrisphere.us.elf")
    for name, (offset, size) in expected.items():
        symbol = next(s for s in linked_symbols if s["name"] == name)
        assert (symbol["address"], symbol["size"], symbol["info"]) == (0x800F2040 + offset, size, 17)
        assert 0 < symbol["index"] < len(linked_sections)
        assert linked_sections[symbol["index"]]["name"] == ".main_bss"
        for aliases in ["undefined_syms.txt", "undefined_syms_auto.txt", "undefined_funcs_auto.txt"]:
            assert not re.search(r"^\s*" + name + r"\s*=", (ROOT / aliases).read_text(), re.M)
    print("C OWNERSHIP: four boot globals at 0x800F2040, with two bytes of alignment padding.")
    print("Storage-only C object; no new instructions or BSS symbols.")


if __name__ == "__main__":
    main()
