# Boot prefix restored to C

Baseline: `9c94f8625acdab962839022a0cdab4b697ebc481`.

The 16-byte assembly prefix at `0x800F2040..0x800F2050` is now supplied by
`src/boot_state.c`, using the types already declared by its consumers:

| Address | Definition | Use |
| --- | --- | --- |
| `0x800F2040` | `OSThread *D_800F2040` | Faulted-thread pointer |
| `0x800F2044` | `s32 D_800F2044` | Cleared by the fault handler; broader purpose unresolved |
| `0x800F2048` | `s16 D_800F2048` | EEPROM write/read request type |
| `0x800F204C` | `void *D_800F204C` | EEPROM request buffer |

Stock IDO naturally supplies two alignment bytes at `0x800F204A`. The input
object has exactly 16 bytes of BSS, alignment 16, and no instructions.
`boot.c`, including its existing EEPROM array definitions, is unchanged.
The raw prefix file and the absolute `D_800F2040` assignment in
`undefined_syms_auto.txt` are removed. All four variables are real C-owned
objects in the linked BSS. Linker and YAML entries select the new storage file
at the old address.

## Why a separate storage file

The first experiment defined all four scalars directly in `boot.c`. IDO
allocated them after the EEPROM arrays, at offsets `0x240..0x24C`, despite
their earlier source declarations. The object still occupied 592 bytes and its
instruction bytes were unchanged, but the moved symbol addresses caused 34
non-header ROM bytes to differ. That candidate was rejected and reverted.

Keeping the scalar prefix in its own storage-only C file preserves normal
typed global definitions and the original layout without compiler changes,
invented aggregate wrappers, or address aliases. This is a practical recovery
boundary, not a claim about the original translation-unit organization.

## Verification

Pristine isolated and final candidate builds passed `./matchdiff.sh`. The
entire ROM, including the header, matches. All allocated ELF section layouts
and existing BSS symbol addresses are preserved; this batch adds no symbols.
The only allocation-provider change is the 16-byte prefix, now `boot_state.o`.

After building, run without Python's `-O` option:

```sh
./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
python3 pending/session_bss_boot_prefix/verify.py
```

This runs the earlier SDK and EEPROM checks, validates all four scalar sizes,
offsets, and actual section ownership, rejects fixed-address substitutes, and
checks the lack of instructions. The EEPROM baseline now retains the deleted
prefix's exact assembly text, so the existing reconstruction check still
restores the original pre-migration game-BSS source hash. No baseline hashes
were replaced. Binary artifacts remain untracked.

Complete splat regeneration remains untested, as in the earlier migrations.
No other game BSS interval or identifier was changed.
