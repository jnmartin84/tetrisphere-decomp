#include <ultra64.h>

/* Sliding-window LZ decompressor (4KB ring dictionary, 12-bit backrefs).
 * The window is pre-seeded with fixed patterns so short matches work
 * before any output has been produced. */

typedef struct {
    u8 *src;           /* 0x0000 compressed stream */
    u8 window[0x1000]; /* 0x0004 ring dictionary */
    s32 srcPos;        /* 0x1004 */
    s32 winPos;        /* 0x1008 */
    u8 state;          /* 0x100C 0=command, 1=literal run, 2=backref */
    u8 count;          /* 0x100D remaining bytes in run */
    u16 backPos;       /* 0x100E backref read position */
} UnkLz;

void func_80079660(u8 *src, UnkLz *lz) {
    s16 i;
    s16 j;

    lz->src = src;
    lz->srcPos = 0;
    lz->winPos = lz->srcPos;
    for (i = 0; i < 0x100; i++) {
        lz->window[i] = i;
    }
    for (i = 0x100; i < 0x200; i++) {
        lz->window[i] = 0x1FF - i;
    }
    for (i = 0; i < 0x100; i++) {
        for (j = 0; j < 4; j++) {
            lz->window[(i * 4) + j + 0x200] = i;
        }
    }
    for (i = 0x600; i < 0x1000; i++) {
        lz->window[i] = i & 0xFF;
    }
    lz->state = 0;
    lz->backPos = 0;
}

u8 func_8007979C(UnkLz *lz) {
    u8 out;

    if (lz->state == 0) {
        lz->count = lz->src[lz->srcPos++];
        if (!(lz->count & 0xF0)) {
            lz->state = 1;
            lz->count = lz->count + 1;
        } else {
            lz->state = 2;
            lz->backPos = lz->src[lz->srcPos++] + ((lz->count & 0xF) << 8);
            lz->count = (lz->count >> 4) + 2;
        }
    }
    if (lz->state == 1) {
        out = lz->src[lz->srcPos++];
        lz->window[lz->winPos++] = out;
        lz->winPos = lz->winPos & 0xFFF;
    }
    if (lz->state == 2) {
        out = lz->window[lz->backPos++];
        lz->backPos = lz->backPos & 0xFFF;
        lz->window[lz->winPos++] = out;
        lz->winPos = lz->winPos & 0xFFF;
    }
    lz->count--;
    if (lz->count == 0) {
        lz->state = 0;
    }
    return out;
}
