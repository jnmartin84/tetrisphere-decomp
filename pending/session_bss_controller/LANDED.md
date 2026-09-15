# Controller and EEPROM BSS restored to C

Baseline: `c3c212da4281a3d982ea34cfa46dde5269039111`.

Restored the storage declarations retained in the bundled SDK's `controller.c`
and `conteepread.c`. Existing function bodies and compiler flags are unchanged.
The complete 208-byte `os_bss_c` reservation is now supplied by two C objects:
64 bytes from `conteepread.o` and 144 bytes from `controller.o`.

| Address | Object | Bytes |
| --- | --- | ---: |
| `0x80163A40` | `OSPifRam __osEepPifRam` | 64 |
| `0x80163A80` | `OSPifRam __osContPifRam` | 64 |
| `0x80163AC0` | `u8 __osContLastCmd` | 1 |
| `0x80163AC1` | `u8 __osMaxControllers` | 1 |
| `0x80163AC2` | Compiler alignment padding | 6 |
| `0x80163AC8` | `OSTimer __osEepromTimer` | 32 |
| `0x80163AE8` | `OSMesgQueue __osEepromTimerQ` | 24 |
| `0x80163B00` | `OSMesg __osEepromTimerMsg` | 4 |
| `0x80163B04` | Compiler section padding | 12 |

The timer declaration explains the unlabeled storage inside the old `0x27`
span after `__osMaxControllers`. The SDK declares it here even though the
linked game has no direct reference to that symbol. Its original SDK type,
declaration order, and the resulting exact allocation provide the evidence;
zero-filled ROM data alone could not establish this interpretation.

Each PIF buffer includes its four-byte status word at offset `0x3C`.
`D_80163A7C` and `D_80163ABC` remain as relative linker aliases to those members.
The owning buffers have real C definitions; none of the seven recovered
objects is supplied by a fixed-address linker assignment. Symbol metadata now
records object sizes instead of stale function annotations, including the
new timer name. Linker and YAML entries record both C contributions. Complete
splat regeneration remains untested and outside the normal build procedure.

## Verification

Pristine isolated and candidate builds passed `./matchdiff.sh`. The entire
8,388,608-byte ROM matches, including its header. Both changed C objects retain
their pristine `.text` bytes. All allocated ELF section layouts and all 1,369
preexisting BSS name/address entries are unchanged. The single added entry is
`__osEepromTimer` at `0x80163AC8`, naming storage that was already reserved.
Only the 208-byte input contribution splits into the two C owners above.

After building, run without Python's `-O` option:

```sh
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
python3 pending/session_bss_controller/verify.py
```

The cumulative verifier checks all three SDK migrations, every typed object's
input and linked size/address/ownership, both interior aliases, the unchanged
object text, and whole-ROM identity. It permits precisely the added timer
name/address pair when comparing against the original BSS symbol baseline.
A negative check reporting a 60-byte controller PIF object was rejected while
leaving the ROM and addresses untouched. Baseline object-text and ELF hashes
are recorded in `BASELINE.json`; no binaries are tracked.

All nonempty raw SDK BSS reservations have now been migrated to C. The empty
`os_bss_f.bss.s` placeholder remains, along with both large game BSS blocks.
