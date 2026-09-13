#include "common.h"

/* ROM 0x5D240 -- its own translation unit, and the first thing in this region.
 *
 * This file exists because func_80081E90 CANNOT be matched with game2's flags. It needs
 * the project DEFAULT flags (-O1 -g -mips1), under which IDO SKIPS uopt ENTIRELY
 * (cfe -> ugen -> as1) while as1 still schedules -- which is exactly ROM's signature here:
 * every local stack-homed, redundant reloads, dead stores kept, delay slots filled.
 * Under game2's -O2 -g0 it is 51 words off and unreachable. -O1/-O2/-O3 x -g/-g1/-g2 are
 * all byte-identical, since uopt is off either way.
 * Corroboration: it is the ONLY function in this region with stack-slot churn (45 vs 0-10
 * for every function in game2), and it sits at the exact first address of the old segment.
 *
 * D_800E2AA0 is u32, not s32: ROM has divu/srl where s32 gives div/sra. */

extern u32 D_800E2AA0;

/* A bounded multiply-shift RNG. Advances a 32-bit LCG state as state = state * K + 1,
 * hand-computed in 16-bit limbs (low multiplier 0x20D5 = 8405, with a % 65535 reduction on
 * the low half), then returns floor(state * arg / 2^32) -- the classic multiply-high
 * bounded reduction, giving a value in [0, arg). Callers use it as
 * func_80081E90(0x64) < 0x32 for a coin flip and func_80081E90(6) + 4 for a range.
 *
 * Honest note: the cross-terms below (the (x & 0xF) << 8 nibble-shifts on lo*8 and hi*4)
 * are mathematically incoherent as a true 32-bit multiply -- they reconstruct no carry. The
 * UPDATE step is a buggy or deliberately-hashed transcription of a 16-bit-era generator and
 * cannot be named; the REDUCTION step is textbook. The dead store "lo = p & 0xFFFF;" in the
 * reduction survives only because uopt is off, which is itself corroboration of the flags. */
s32 func_80081E90(s32 arg0) {
    u16 lo;
    u16 hi;
    u16 t1;
    u16 t2;
    u32 p;

    lo = D_800E2AA0 % 0xFFFF;
    hi = D_800E2AA0 >> 16;
    t1 = lo;
    p = lo * 0x20D5;
    lo = p & 0xFFFF;
    t2 = p >> 16;
    t1 = t1 * 8;
    t1 = t1 + ((t1 & 0xF) << 8);
    t2 = t2 + t1;
    t2 = t2 + hi;
    hi = hi * 4;
    t2 = t2 + hi;
    t2 = t2 + ((hi & 0xF) << 8);
    hi = hi << 5;
    t2 = t2 + ((hi & 0xF) << 8);
    D_800E2AA0 = lo + (t2 << 16) + 1;
    lo = D_800E2AA0 & 0xFFFF;
    t2 = D_800E2AA0 >> 16;
    t1 = t2;
    p = lo * arg0;
    lo = p & 0xFFFF;
    t2 = p >> 16;
    lo = t1;
    t1 = t2;
    p = lo * arg0;
    p += t1;
    return (p >> 16) & 0xFFFF;
}
