#include <ultra64.h>

/* Small utility functions (head of the former E820 mega-file) */

extern s32 D_800DF710;
extern s32 D_800DF714;
extern s16 D_800DFE90; /* frame-wait countdown, decremented by interrupt */
extern s32 D_800F22C0;

typedef struct {
    u8 pad[0x18EC];
    s32 unk18EC;
} UnkACC0;
extern u8 D_800FACC0[];

void func_8002A140(void);

void func_80033470(void) {
    while (D_800DF710 > D_800DF714) {
        func_8002A140();
    }
}

s32 func_800334D8(void) {
    return ((UnkACC0 *)D_800FACC0)->unk18EC - D_800F22C0;
}

s32 func_80033504(u8 *a, u8 *b) {
    if ((*a != 0) && (*b != 0) && (*a == *b)) {
        do {
            a++;
            b++;
        } while ((*a != 0) && (*b != 0) && (*a == *b));
    }
    if (*a != *b) {
        return 0;
    }
    return 1;
}

void func_800335A8(s16 n) {
    D_800DFE90 = n;
    while (D_800DFE90 > 0) {
    }
}
