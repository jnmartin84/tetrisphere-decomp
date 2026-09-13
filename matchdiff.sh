#!/bin/bash
# usage: matchdiff.sh [hex_start hex_size]  — rebuild, verify, and on mismatch diff the region
# Gate the tree this script LIVES IN, not a hardcoded path. The old "cd
# ~/claude_tetrisphere" meant that running matchdiff.sh from a git worktree
# silently built and gated the LIVE tree and printed ITS verdict -- it handed an
# agent a FULL MATCH for an experiment that had never been built. A gate that
# answers a question you did not ask is worse than no gate.
cd "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)" || exit 1
mkdir -p work
find build/src -name "*.o" -delete 2>/dev/null
# never let a stale ROM survive a failed build and get checksummed
rm -f build/tetrisphere.us.z64 build/tetrisphere.us.bin build/tetrisphere.us.elf 2>/dev/null
make build/tetrisphere.us.z64 >/dev/null 2>&1 || { echo "BUILD FAILED"; make build/tetrisphere.us.z64 2>&1 | grep -iv "assembler\|blob" | tail -5; exit 1; }
if python3 tools/rom.py verify >/dev/null; then echo "FULL MATCH"; exit 0; fi
# -z IS LOAD-BEARING: objdump elides runs of zero words as `...`, and `nop` is
# 0x00000000. Both sides elide, so a region where the ROM has 5 nops and the build has 6
# shows `...` on BOTH and the diff reports NOTHING -- a real difference goes INVISIBLE.
# (The whole-ROM gate above is `cmp -s` on raw bytes and was never affected; this is the
# DIAGNOSTIC path only. It still lied to whoever read it.)
if [ -n "$1" ]; then
  S=$((16#${1#0x})); Z=$((16#${2#0x}))
  for f in build/tetrisphere.us.z64 tetrisphere.z64; do
    dd if=$f bs=1 skip=$S count=$Z of=work/$(basename $f .z64).bin 2>/dev/null; mips-linux-gnu-objdump -z -D -b binary -m mips:4300 -EB work/$(basename $f .z64).bin | tail -n +8 | awk "{\$1=\"\"; print}" > work/$(basename $f .z64).dis
  done
  echo "diff lines: $(diff work/tetrisphere.us.dis work/tetrisphere.dis | wc -l)"
else
  bs=$(wc -c < build/tetrisphere.us.z64); rs=$(wc -c < tetrisphere.z64)
  n=$(cmp -l build/tetrisphere.us.z64 tetrisphere.z64 2>/dev/null | awk '$1>64' | wc -l)
  echo "MISMATCH: built=$bs ref=$rs delta=$((bs-rs)) bytes; differing(excl hdr)=$n"
  echo "first diffs (pos_dec v1_oct v2_oct):"
  cmp -l build/tetrisphere.us.z64 tetrisphere.z64 2>/dev/null | awk '$1>64' | head -6
fi

exit 1
