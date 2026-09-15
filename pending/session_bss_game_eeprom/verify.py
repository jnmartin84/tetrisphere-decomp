#!/usr/bin/env python3
"""Verify the game EEPROM arrays, unchanged surrounding source, and BSS/ROM layout."""
import hashlib
import importlib.util
import json
from pathlib import Path
import re

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
spec = importlib.util.spec_from_file_location(
    "controller_bss", ROOT / "pending/session_bss_controller/verify.py")
controller_bss = importlib.util.module_from_spec(spec)
spec.loader.exec_module(controller_bss)


def main():
    controller_bss.main()
    baseline = json.loads((HERE / "BASELINE.json").read_text())
    read = controller_bss.thread_bss.event_bss.elf_info
    sections, symbols, text = read(ROOT / "build/src/boot.o")
    index = next(i for i, s in enumerate(sections) if s["name"] == ".bss")
    bss = sections[index]
    assert (bss["type"], bss["size"], bss["alignment"]) == (8, 576, 16)
    expected = {"D_800F2050": (0, 512), "D_800F2250": (512, 64)}
    owned = {s["name"]: (s["address"], s["size"]) for s in symbols
             if s["index"] == index and s["info"] == 17}
    assert owned == expected, "Wrong EEPROM array allocation"
    assert hashlib.sha256(text).hexdigest() == baseline["boot_text_sha256"]
    linked_sections, linked_symbols, _ = read(ROOT / "build/tetrisphere.us.elf")
    for name, (offset, size) in expected.items():
        symbol = next(s for s in linked_symbols if s["name"] == name)
        assert (symbol["address"], symbol["size"], symbol["info"]) == (0x800F2050 + offset, size, 17)
        assert 0 < symbol["index"] < len(linked_sections)
        assert linked_sections[symbol["index"]]["name"] == ".main_bss"
        for aliases in ["undefined_syms.txt", "undefined_syms_auto.txt", "undefined_funcs_auto.txt"]:
            assert not re.search(r"^\s*" + name + r"\s*=", (ROOT / aliases).read_text(), re.M)

    # Reverse precisely the two declaration changes to check every other source byte.
    boot = (ROOT / "src/boot.c").read_bytes()
    for name, size in [("D_800F2050", "0x200"), ("D_800F2250", "0x40")]:
        definition = f"u8 {name}[{size}];".encode()
        assert boot.count(definition) == 1
        boot = boot.replace(definition, f"extern u8 {name}[];".encode())
    assert hashlib.sha256(boot).hexdigest() == baseline["boot_source_sha256"]
    assert not (ROOT / "asm/data/game_bss_prefix.bss.s").exists()
    prefix = baseline["migrated_prefix_assembly"].encode()
    tail = (ROOT / "asm/data/game_bss_before_pi.bss.s").read_bytes()
    header = prefix[:prefix.index(b"dlabel ")]
    assert tail.startswith(header)
    after_pi = (ROOT / "asm/data/game_bss.bss.s").read_bytes()
    assert after_pi.startswith(header)
    tail = tail + b"\n" + baseline["migrated_pi_assembly"].encode() + after_pi[len(header):]
    restored = prefix + b"\n" + baseline["migrated_assembly"].encode() + tail[len(header):]
    assert hashlib.sha256(restored).hexdigest() == baseline["game_bss_source_sha256"]
    yaml = (ROOT / "tetrisphere.yaml").read_text()
    for entry in ["{ type: .bss, vram: 0x800F2040, name: boot_state }",
                  "{ type: .bss, vram: 0x800F2050, name: boot }",
                  "{ type: bss, vram: 0x800F2290, name: game_bss_before_pi }"]:
        assert entry in yaml
    print("C OWNERSHIP: 512-byte EEPROM mirror + 64-byte dirty flags at 0x800F2050.")
    print("boot.o text and all surrounding source/storage preserved; no added BSS symbols.")


if __name__ == "__main__":
    main()
