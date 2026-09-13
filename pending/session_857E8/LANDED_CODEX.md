# func_800857E8: FULL MATCH

The final GLOBAL_ASM function is now C. Integrated on canonical baseline
`1012c9a` in `wr64vm:~/claude_tetrisphere` on 2026-09-12. There are no remaining
GLOBAL_ASM pragmas in `src`.

- VA: `0x800857E8..0x80088914` (exclusive end).
- ROM: `0x60B98..0x63CC4`; 12,588 bytes / 3,147 instructions.
- Source: `src/game2.c`; final experiment H2G93 followed by reviewed source,
  comment, declaration, and alias cleanup in `~/wt/codex_857e8/work/landing857`.

## Verification

The stock production compiler and flags produce an 8,388,608-byte ROM identical
to the original, including the header. The isolated linked gate was repeated
after final comments and formatting; canonical integration is gated separately.

- ROM SHA-256: `f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.
- Target SHA-256: `d1f543090c83e965b5a83179514c57b6a005254927f5675f73c07da5005bcff6`.
- Independent ELF program-header extraction matches all 12,588 reference bytes.
  Splicing them into the reference ROM reproduces the complete generated ROM.
- Final stock/probe uopt outputs are byte-identical. The observer was revalidated
  after source cleanup; its inputs and outputs remain in the isolated worktree
  at `work/trace_landing857_final`.
- The already landed 906E8 retains its original function bounds and local-static
  placement. The whole-ROM comparison covers every other function and all data.

Evidence: `CODEX_VERIFICATION.json`, `CODEX_ISOLATED_MATCH.txt`, and
`CODEX_CANONICAL_MATCH.txt`. Reproduce the production gate with `./matchdiff.sh`,
then run `python3 pending/session_857E8/verify_landing.py pending/session_857E8`
for independent extraction, exact whole-ROM comparison, source hashes, and
storage/bound checks. The optional third argument is a stock-validated trace
directory; it records the matching observer output and input hashes.

## Source and storage constraints

The function initializes descriptor templates and a 48-entry pointer table.
Preserve the shipped by-value copies: `func_80082A94(Foo84)` changes a private
copy, and converting those calls to pointer calls would change behavior.
The common outer counter, stack-array representation, signed tail-byte stores,
and direct-versus-cursor stores recover the original allocation and addressing.

The erased `do {} while (0)` boundary in the second loop preserves constant
coloring. The first loop computes the descriptor number before the source
assignment of `f4`; as1 schedules the latter store ahead of the multiply result.
The deliberately interleaved final table assignments preserve address-load and
saved-register store scheduling. Keep the clang-format guard and statement order.

The existing `D_801317C0` storage is now a Foo84 plus its original four-byte
padding; Foo84 remains 0x764 bytes. Its use in 906E8 gains the required address-of
operator when converting from an array to this object representation.

The following original contiguous BSS bytes move from `game_bss_b.bss.s` into
the C translation unit; there is no added or duplicate storage:

| C storage | Address | Size |
| --- | --- | --- |
| `storage857_prefix` | `0x8013D270` | `0xAA0` |
| `storage857_DD10` | `0x8013DD10` | `0x768` |
| `storage857_middle` | `0x8013E478` | `0xED0` |
| `storage857_F348` | `0x8013F348` | `0x768` |

DD10 and F348 must be defined in this TU for as1 to share their store-address
LUI instructions. Linker aliases preserve all original field labels in the
carved range and provide ten by-value descriptor views into actual storage.
The inherited diagnostic alias inventory is excluded from the landing.

The tracked `tetrisphere.yaml` records game2's complete C BSS range as
`0x80127CF0..0x8013FAB0`. Isolated splat regeneration with that configuration
produced identical BSS declarations: `game_bss_b.bss.s` is byte-identical, and
`game_bss.bss.s` differs only by a trailing blank line. These generated assembly
files remain ignored; the configuration carries the change
through subsequent extraction without committing ROM-derived assembly.

The 79 explicit `(void)&symbol` expressions at the start of 857E8 are erased
symbol-order anchors, not recovered gameplay operations. They allocate no
storage and emit no instructions or memory accesses. Their first references
preserve the stock compiler's BSS ordering without moving the 906E8 local static
or modifying its guarded statement layout. In the final CFE symbol table,
D170/D268 have dense IDs 248/249 and `local_state906` has ID 760; its 32 bytes
occupy the original `0x8013D248..0x8013D268` interval. Omitting the anchors moves
that object into earlier BSS records and breaks the linked ROM match.

Keep the anchor list and storage declarations in order. Any cleanup of these
source constraints must pass the linked whole-ROM gate again. The 8EEA4 guard
and the existing 906E8 split state definitions remain intact.

## Scope

No compiler behavior changes, flag changes, instruction patches, generated
candidate searches, or subagents were used. The unreferenced assembly source
remains available as reference. Experiment candidates and observer binaries are
not part of the commit. Unrelated canonical changes to
`pending/session_8EEA4/.cm.txt` and `pending/session_97e3c/probe97.sh` are preserved
and excluded from the landing.
