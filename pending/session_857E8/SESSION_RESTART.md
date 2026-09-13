# 857E8 is landed: FULL MATCH

Completed 2026-09-12 on canonical baseline `1012c9a` in
`wr64vm:~/claude_tetrisphere`. The final GLOBAL_ASM function is C; no pragmas
remain in `src`. This supersedes the earlier 857E8 matching handoffs.

Read `pending/session_857E8/LANDED_CODEX.md` for the source/storage constraints,
verification evidence, and reproduction commands. `CODEX_VERIFICATION.json`
records the exact whole-ROM and target hashes. Both isolated and canonical
linked gates pass after final formatting; independent ELF extraction and
whole-ROM splice checks also pass.

ROM SHA-256:
`f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87`.

The final source includes load-bearing erased symbol references and contiguous
BSS ownership. Preserve those, the 8EEA4/906E8 guards, and the 906E8 local-static
position. Re-run the complete linked gate after source or formatting changes.

The isolated worktree remains `~/wt/codex_857e8`; its Git HEAD is intentionally
older than its verified working source. Do not reset it to HEAD. H2G93 is the
last experimental FULL MATCH; `work/landing857` holds the cleaned final files,
and `work/trace_landing857_final` holds the stock-validated observer evidence.

Unrelated canonical changes to `pending/session_8EEA4/.cm.txt` and
`pending/session_97e3c/probe97.sh`, plus existing untracked work, remain untouched.
