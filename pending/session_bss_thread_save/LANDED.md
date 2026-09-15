# Saved-thread BSS restored to C

Baseline: `bf2a0cbd838b237d16ebcc5dadafc12e5e8774a3`.

Imported `src/libultra/debug/kdebugserver.c` byte-for-byte from the bundled
`tools/ultralib/src/debug/kdebugserver.c`. Its `OSThread __osThreadSave`
definition replaces the complete `os_bss_e` assembly reservation at
`0x80163CB0..0x80163E60`. No other game or SDK storage was migrated.

The SDK places this variable outside `#ifndef _FINALROM`; its debugger
functions are inside that guard. The production flags therefore produce a
BSS-only object with one 432-byte global, 16-byte section alignment, and no
instructions. The object exactly fills the old reservation, without padding
declarations or compiler/object modifications.

The exception handler saves registers into this temporary `OSThread` before
loading `__osRunningThread` and transferring saved values into that thread's
context. The exception assembly is unchanged. This is scratch storage for
exception entry, not another runnable thread.

The linker now selects the C object's BSS at the same position. YAML records
the C ownership, and `symbol_addrs.txt` records size `0x1B0` instead of the stale
`type:func` annotation. Complete splat regeneration remains untested, as in the
existing distribution; it is not part of the normal build.

## Verification

The pristine isolated and candidate builds passed `./matchdiff.sh`. The full
8,388,608-byte ROM, including its header, remains identical to the reference.
All allocated ELF section layouts and all 1,369 named BSS symbol addresses
are preserved. Every nonempty BSS contribution keeps its address and size;
the only provider change in this batch is `os_bss_e.bss.o` to `kdebugserver.o`.
The new symbol has a measured size of 432 bytes and real `.main_bss` ownership.

Run after building, without Python's `-O` option:

```sh
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
python3 pending/session_bss_thread_save/verify.py
```

The verifier reuses the event-table layout baseline, with an explicit mapping
for both accepted ownership transfers. It checks the event-table migration
as well as this one, unchanged exception assembly, exact SDK source identity,
and absence of debugger instructions. A negative check substituting the
pristine assembly-owned ELF was rejected despite unchanged addresses and ROM
bytes. `BASELINE.json` records source/exception hashes and the pristine ELF
identity for this experiment; binaries remain untracked.
