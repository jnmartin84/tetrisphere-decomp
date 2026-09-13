# Building Tetrisphere (USA)

See [README](../README.md) for host packages, reference ROM hash and quick start.

`make tools` selects the official decompals IDO 5.3 v1.2 archive for the detected
OS/architecture, verifies its pinned SHA-256, and builds n64crc from C source.
The compiler is cached by host beneath `tools/ido5.3/v1.2/`. Existing files are
checked against the installation manifest; incomplete/corrupt installations are
replaced only after a replacement archive passes verification. No download occurs
when parsing the Makefile, running `make clean`, or reusing a verified cache.
The full build depends on this setup, including individual C object targets.

`make extract` checks the entire reference ROM hash before producing assets/ipl3.bin
and assets/CD3F0.bin. Normal builds run this check automatically; fixed binary
prerequisites ensure a fresh clone with no assets still links both required blobs.
The retained assembly and linker files are the final generated build inputs.
`make resplit` is an optional research target requiring a separate splat environment;
it is not needed or validated for building this source distribution.

## Build and verification

```sh
make tools
make clean
make -j4
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
python3 -m unittest discover -s tools -p test_setup.py -v
python3 tools/audit_git.py
```

The default make target and matchdiff both check every byte including the header.
matchdiff's optional region-disassembly diagnostics require GNU MIPS objdump.
`CROSS=mips-linux-gnu-` and `HOST_CC=cc` may be overridden on the make command line.
Ensure Homebrew's bin directory is on PATH when building on macOS.

## Matching constraints retained

All C translation units compile directly with unmodified IDO 5.3. No asm-processor,
patched compiler, instruction replacement or GLOBAL_ASM function remains.
The exact per-file optimization/debug/ISA flags are preserved from semantic HEAD
490402d and the original completed decompilation. Physical source layout and erased
symbol-order references in game2.c remain load-bearing.

Existing explicit object metadata adjustments remain:

- game2.o .rodata alignment is four bytes.
- libc/ll.o compiles with -mips3, then its ELF ISA flag is changed to MIPS II for
  the 32-bit GNU link. Instructions are unchanged.
- Selected raw assembly objects preserve section alignments and no-padding flags.

Original compiler audit and Linux build records are retained as historical evidence.
They describe the old portable snapshot. Current host/build results and imported
semantic provenance are in evidence/PUBLICATION.json; neither emulator nor hardware
playtesting is implied by byte matching.
