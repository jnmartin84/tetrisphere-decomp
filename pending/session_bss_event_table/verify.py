#!/usr/bin/env python3
"""Verify the event-table C allocation against the recorded pristine BSS layout."""
import hashlib
import json
from pathlib import Path
import re
import struct

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]


def digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True).encode()).hexdigest()


def elf_info(path):
    data = path.read_bytes()
    assert data[:6] == b"\x7fELF\x01\x02", "Expected ELF32 big endian"
    h = struct.unpack_from(">HHIIIIIHHHHHH", data, 16)
    raw = [struct.unpack_from(">IIIIIIIIII", data, h[5] + i * h[10])
           for i in range(h[11])]

    def payload(s):
        return data[s[4]:s[4] + s[5]]

    def string(strings, offset):
        return strings[offset:strings.index(b"\0", offset)].decode()

    names = payload(raw[h[12]])
    sections = [dict(name=string(names, s[0]), type=s[1], flags=s[2],
                     address=s[3], size=s[5], alignment=s[8]) for s in raw]
    symbols = []
    for s in raw:
        if s[1] != 2:
            continue
        strings = payload(raw[s[6]])
        for offset in range(s[4], s[4] + s[5], s[9]):
            name, value, size, info, other, index = struct.unpack_from(">IIIBBH", data, offset)
            if name:
                symbols.append(dict(name=string(strings, name), address=value,
                                    size=size, info=info, index=index))
    text = payload(raw[next(i for i, s in enumerate(sections) if s['name'] == '.text')]) \
        if any(s['name'] == '.text' for s in sections) else b''
    return sections, symbols, text


def layout(root):
    sections, symbols, _ = elf_info(root / "build/tetrisphere.us.elf")
    bss = next(s for s in sections if s["name"] == ".main_bss")
    pairs = sorted((s["name"], s["address"]) for s in symbols
                   if bss["address"] <= s["address"] <= bss["address"] + bss["size"])
    contributions = []
    for addr, size, owner in re.findall(
            r"^ \.bss\s+(0x\w+)\s+(0x\w+)\s+(\S+)",
            (root / "build/tetrisphere.us.map").read_text(), re.M):
        addr, size = int(addr, 16), int(size, 16)
        if size and bss["address"] <= addr < bss["address"] + bss["size"]:
            contributions.append([addr, size, owner])
    return dict(allocated_sections=[s for s in sections if s["flags"] & 2],
                bss_symbol_count=len(pairs), bss_symbol_addresses_sha256=digest(pairs),
                contributions=contributions)


def main():
    baseline = json.loads((HERE / "BASELINE.json").read_text())
    actual = layout(ROOT)
    expected = baseline["layout"]
    expected["contributions"] = [
        [addr, size, "build/src/libultra/os/seteventmesg.o" if owner ==
         "build/asm/data/os_bss_a.bss.o" else owner]
        for addr, size, owner in expected["contributions"]]
    assert actual == expected, "Allocated section, BSS symbol address, or ownership drift"

    sections, symbols, text = elf_info(ROOT / "build/src/libultra/os/seteventmesg.o")
    index = next(i for i, s in enumerate(sections) if s["name"] == ".bss")
    bss = sections[index]
    assert bss["type"] == 8 and bss["size"] == 128 and bss["alignment"] == 16
    event = next(s for s in symbols if s["name"] == "__osEventStateTab")
    assert (event["address"], event["size"], event["info"], event["index"]) == (0, 120, 17, index)
    assert hashlib.sha256(text).hexdigest() == baseline["object_text_sha256"]
    linked_sections, linked_symbols, _ = elf_info(ROOT / "build/tetrisphere.us.elf")
    event = next(s for s in linked_symbols if s["name"] == "__osEventStateTab")
    assert event["address"] == 0x801627A0 and event["size"] == 120
    assert linked_sections[event["index"]]["name"] == ".main_bss", "Event table is not section owned"
    assert not (ROOT / "asm/data/os_bss_a.bss.s").exists()
    for name in ["undefined_syms.txt", "undefined_syms_auto.txt", "undefined_funcs_auto.txt"]:
        assert not re.search(r"^\s*__osEventStateTab\s*=", (ROOT / name).read_text(), re.M)
    assert hashlib.sha256((ROOT / "asm/1000.s").read_bytes()).hexdigest() == baseline["entry_sha256"]
    assert "{ type: .bss, vram: 0x801627A0, name: libultra/os/seteventmesg }" in \
        (ROOT / "tetrisphere.yaml").read_text()
    rom = (ROOT / "tetrisphere.z64").read_bytes()
    assert hashlib.sha256(rom).hexdigest() == baseline["rom_sha256"]
    assert rom == (ROOT / "build/tetrisphere.us.z64").read_bytes(), "Whole ROM mismatch"
    print("BSS MATCH: all allocated section layouts and 1,369 named BSS addresses preserved.")
    print("C OWNERSHIP: 120-byte event table + 8-byte section padding at 0x801627A0.")
    print("FULL ROM MATCH; osSetEventMesg object text unchanged.")


if __name__ == "__main__":
    main()
