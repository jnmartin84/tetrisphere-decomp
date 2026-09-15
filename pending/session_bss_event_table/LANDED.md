# Event table: C-owned BSS

Baseline: `453e7efb93e15e64490aef5c3da149a4dc10a8db`.

Restored `__osEventStateTab` in `src/libultra/os/seteventmesg.c` using the
definition retained in `tools/ultralib/src/os/seteventmesg.c`. The two C files
are now byte-identical. Removed the assembly reservation and absolute linker
assignment, placed the C object's BSS at the original address, and updated the
splat configuration to record C ownership.

Stock IDO 5.3 emits a 120-byte array (15 eight-byte entries) in a 128-byte,
16-aligned `.bss` section. The trailing eight bytes are compiler section padding;
no explicit padding object, invented extra entry, or object patch is required.
The SDK's `ALIGNED(0x8)` spelling is retained; its attribute macro is erased
under this compiler. The measured object alignment is 16.

## Verified

- Pristine isolated checkout: `./matchdiff.sh` returned `FULL MATCH`.
- Candidate: `./matchdiff.sh` returned `FULL MATCH`; header-inclusive `cmp`
  passed. The complete ROM SHA-256 remains
  `f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.
- All allocated ELF section layouts are unchanged, including the complete
  `0x800F2040..0x80164E60` BSS interval and its `0x72E20` size.
- All 1,369 named ELF symbol entries in the inclusive BSS boundary range keep
  their addresses. This is a symbol-entry count, not a distinct-object count.
- Every nonempty input BSS contribution retains its address and size. The
  sole provider change is `os_bss_a.bss.o` to `seteventmesg.o` for
  `0x801627A0..0x80162820`.
- The event-table ELF symbol is now a 120-byte object in `.main_bss`, rather
  than an absolute linker alias. The input C object owns it at BSS offset zero.
- `osSetEventMesg` object `.text` bytes are unchanged. Entry assembly and its
  BSS-clear length are unchanged.
- The layout verifier rejects the pristine assembly-owned ELF even though its
  addresses and ROM bytes match, exercising the C-ownership check.

After building, run:

```sh
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
python3 pending/session_bss_event_table/verify.py
```

`BASELINE.json` records the pristine section/contribution layout and hashes of
the full BSS name/address multiset, original object text, entry source, ELF, and
ROM. The verifier checks the actual linked section and input object, so retaining
an absolute alias cannot hide a wrongly placed allocation. Run without Python's
`-O` option; verification uses assertions. Binary build artifacts are not tracked.

The YAML ownership entry has been updated, but a complete splat regeneration
was not run; it remains an optional, separately validated research operation.
This pilot migrates 128 bytes. The other raw BSS blocks remain for later work.
