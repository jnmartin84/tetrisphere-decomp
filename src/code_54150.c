#include "common.h"

/* ROM 0x54150 (func_80078DA0) -- its own translation unit: plain -O2 (loop unrolling ON).
 *
 * code_4D170 is compiled with -Wo,-loopunroll,1 because func_800750C8 needs unrolling OFF,
 * and that flag is byte-neutral for every other matched function in that unit. This function
 * needs the opposite: its middle palette loop is compiler-unrolled 4x in the ROM (the
 * `((t0 - t1) + 5) & 3` remainder loop, the pointer-compared 4-store body, the `t0 + 5`
 * temporaries are all uopt's own unroller output). Under -loopunroll,1 the loop cannot be
 * reproduced from a clean `for`, and a hand-unrolled transcription carries variable copies
 * the ROM lacks. Under -O2 a clean `for` is byte-exact. Two functions in one segment that
 * need opposite unroll settings were two source files; the same reasoning split rand.c out
 * of game2 (commit 73f4d80). */

typedef struct {
    u8 pad0[0x2B10];
    s16 unk2B10;
    u8 pad1[0x2D90 - 0x2B12];
    u8 unk2D90;
    u8 unk2D91;
    u8 unk2D92;
    u8 unk2D93;
    u8 unk2D94;
    u8 unk2D95;
    u8 unk2D96[9];
    u8 unk2D9F[9];
    u8 unk2DA8;
    u8 unk2DA9;
    s16 unk2DAA;
    u8 unk2DAC;
    u8 unk2DAD;
    u16 pal[256];
} PalView78;
#define PS ((PalView78 *) arg0)

extern Gfx *D_800F22B4;
extern void *D_80103224;
extern s16 D_800E23B4;
extern void func_8003396C(void *, void *, s32, s32, s32, s32, s32, s32);

/* RGBA5551 palette fade: fills pal[] in three bands (bright / 3/4 bright / base colour),
 * then steps the current colour components toward the stage target by 5, then emits the
 * TLUT load. The `& 0xFF` on each step is load-bearing: it keeps the byte narrowing as a
 * real conversion, which costs one ugen scratch draw per arm exactly as the ROM spends. */
void func_80078DA0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 t0;
    s32 t1;

    if (arg0[0x2DAC]) {
        arg0[0x2D90] += (0xFF - arg0[0x2D90]) / 2;
        arg0[0x2D91] += (0xFF - arg0[0x2D91]) / 2;
        arg0[0x2DAC] = 0;
        arg0[0x2D92] += (0xFF - arg0[0x2D92]) / 2;
        arg0[0x2D90] -= arg0[0x2D90] % 5;
        arg0[0x2D91] -= arg0[0x2D91] % 5;
        arg0[0x2D92] -= arg0[0x2D92] % 5;
    }
    if (*(s16 *) &arg0[0x2B10] < *(s16 *) &arg0[0x2DAA]) {
        if (*(s16 *) &arg0[0x2DAA] < 9) {
            *(s16 *) &arg0[0x2DAA] -= *(s16 *) &arg0[0x2DAA] / 2;
        }
        if (*(s16 *) &arg0[0x2DAA] == 600) {
            *(s16 *) &arg0[0x2DAA] = 201;
        } else {
            *(s16 *) &arg0[0x2DAA] -= *(s16 *) &arg0[0x2DAA] / 8;
        }
        t0 = *(s16 *) &arg0[0x2DAA] % 202;
    } else {
        *(s16 *) &arg0[0x2DAA] = *(s16 *) &arg0[0x2B10];
        t0 = *(s16 *) &arg0[0x2B10] % 201;
    }
    t1 = t0 + 1;

    for (i = 1; i <= t0 + 1; i++) {
        ((u16 *) &arg0[0x2DAE])[i] = GPACK_RGBA5551(PS->unk2D93, PS->unk2D94, PS->unk2D95, 1);
    }
    if (t0 >= 5 && t0 < 0x5F) {
        for (i = t1; i < t0 + 5; i++) {
            ((u16 *) &arg0[0x2DAE])[i] = GPACK_RGBA5551(PS->unk2D93 - PS->unk2D93 / 4, PS->unk2D94 - PS->unk2D94 / 4, PS->unk2D95 - PS->unk2D95 / 4, 1);
        }
    }
    if (t0 >= 5 && t0 < 0x5F) {
        i = t0 + 5;
    } else {
        i = t1;
    }
    for (; i < 202; i++) {
        ((u16 *) &arg0[0x2DAE])[i] = GPACK_RGBA5551(PS->unk2D90, PS->unk2D91, PS->unk2D92, 1);
    }

    if (*(s16 *) &arg0[0x2B10] > 0 && *(s16 *) &arg0[0x2B10] < 200) {
        arg0[0x2DA8] = 0;
    }
    if (*(s16 *) &arg0[0x2B10] > 200 && *(s16 *) &arg0[0x2B10] < 400) {
        arg0[0x2DA8] = 1;
    }
    if (*(s16 *) &arg0[0x2B10] > 400 && *(s16 *) &arg0[0x2B10] < 600) {
        arg0[0x2DA8] = 2;
    }

    if (arg0[arg0[0x2DA8] * 3 + 0x2D96] < arg0[0x2D93]) {
        arg0[0x2D93] = (arg0[0x2D93] - 5) & 0xFF;
    }
    if (arg0[0x2D93] < arg0[arg0[0x2DA8] * 3 + 0x2D96]) {
        arg0[0x2D93] = (arg0[0x2D93] + 5) & 0xFF;
    }
    if (arg0[arg0[0x2DA8] * 3 + 0x2D97] < arg0[0x2D94]) {
        arg0[0x2D94] = (arg0[0x2D94] - 5) & 0xFF;
    }
    if (arg0[0x2D94] < arg0[arg0[0x2DA8] * 3 + 0x2D97]) {
        arg0[0x2D94] = (arg0[0x2D94] + 5) & 0xFF;
    }
    if (arg0[arg0[0x2DA8] * 3 + 0x2D98] < arg0[0x2D95]) {
        arg0[0x2D95] = (arg0[0x2D95] - 5) & 0xFF;
    }
    if (arg0[0x2D95] < arg0[arg0[0x2DA8] * 3 + 0x2D98]) {
        arg0[0x2D95] = (arg0[0x2D95] + 5) & 0xFF;
    }
    if (arg0[arg0[0x2DA8] * 3 + 0x2D9F] < arg0[0x2D90]) {
        arg0[0x2D90] = (arg0[0x2D90] - 5) & 0xFF;
    }
    if (arg0[0x2D90] < arg0[arg0[0x2DA8] * 3 + 0x2D9F]) {
        arg0[0x2D90] = (arg0[0x2D90] + 5) & 0xFF;
    }
    if (arg0[arg0[0x2DA8] * 3 + 0x2DA0] < arg0[0x2D91]) {
        arg0[0x2D91] = (arg0[0x2D91] - 5) & 0xFF;
    }
    if (arg0[0x2D91] < arg0[arg0[0x2DA8] * 3 + 0x2DA0]) {
        arg0[0x2D91] = (arg0[0x2D91] + 5) & 0xFF;
    }
    if (arg0[arg0[0x2DA8] * 3 + 0x2DA1] < arg0[0x2D92]) {
        arg0[0x2D92] = (arg0[0x2D92] - 5) & 0xFF;
    }
    if (arg0[0x2D92] < arg0[arg0[0x2DA8] * 3 + 0x2DA1]) {
        arg0[0x2D92] = (arg0[0x2D92] + 5) & 0xFF;
    }

    gDPSetTextureLUT(D_800F22B4++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(D_800F22B4++, &arg0[0x2DAE]);
    func_8003396C(&D_800F22B4, D_80103224, arg1, arg2, 0xFF, 0xFF, 0xFF, D_800E23B4);
    gDPSetTextureLUT(D_800F22B4++, G_TT_NONE);
}
