#!/usr/bin/env python3
"""Check PI/DMA queue storage and all preceding BSS recoveries."""
import importlib.util
from pathlib import Path
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
spec = importlib.util.spec_from_file_location(
    "boot_prefix", ROOT / "pending/session_bss_boot_prefix/verify.py")
boot_prefix = importlib.util.module_from_spec(spec)
spec.loader.exec_module(boot_prefix)


def main():
    boot_prefix.main()
    read = boot_prefix.game_eeprom.controller_bss.thread_bss.event_bss.elf_info
    sections, symbols, text = read(ROOT / "build/src/pi_state.o")
    index = next(i for i, s in enumerate(sections) if s["name"] == ".bss")
    bss = sections[index]
    assert (bss["type"], bss["size"], bss["alignment"]) == (8, 880, 16)
    assert not text and not any(s["flags"] & 4 and s["size"] for s in sections)
    expected = {"D_800FA848": (0, 800), "D_800FAB68": (0x320, 24),
                "D_800FAB80": (0x338, 24), "D_800FAB98": (0x350, 32)}
    owned = {s["name"]: (s["address"], s["size"]) for s in symbols
             if s["index"] == index and s["info"] == 17}
    assert owned == expected, "Wrong PI/DMA storage layout"
    assert len([s for s in symbols if s["info"] >> 4 and s["index"] != 0]) == 4
    linked_sections, linked_symbols, _ = read(ROOT / "build/tetrisphere.us.elf")
    for name, (offset, size) in expected.items():
        symbol = next(s for s in linked_symbols if s["name"] == name)
        assert (symbol["address"], symbol["size"], symbol["info"]) == (0x800FA848 + offset, size, 17)
        assert 0 < symbol["index"] < len(linked_sections)
        assert linked_sections[symbol["index"]]["name"] == ".main_bss"
        for aliases in ["undefined_syms.txt", "undefined_syms_auto.txt", "undefined_funcs_auto.txt"]:
            assert not re.search(r"^\s*" + name + r"\s*=", (ROOT / aliases).read_text(), re.M)
    for name, size in [("game_bss_before_pi", 0x85B8), ("game_bss", 0x2D138)]:
        sections, _, _ = read(ROOT / f"build/asm/data/{name}.bss.o")
        section = next(s for s in sections if s["name"] == ".bss")
        assert section["type"] == 8 and section["size"] == size, "Raw BSS fragment acquired padding"
    yaml = (ROOT / "tetrisphere.yaml").read_text()
    assert "{ type: .bss, vram: 0x800FA848, name: pi_state }" in yaml
    assert "{ type: bss, vram: 0x800FABB8, name: game_bss }" in yaml
    print("C OWNERSHIP: 880 bytes of PI/DMA message buffers and queues at 0x800FA848.")
    print("Both raw fragment lengths are exact; no new instructions or BSS symbols.")


if __name__ == "__main__":
    main()
