#include "common.h"

typedef struct {
    u8 pad[0x24];
    s32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 pad30[0x18];
    u8 unk48;
} Obj;

void func_800338B0(Gfx **gdl) {
    gDPPipeSync((*gdl)++);
    gDPSetCombineMode((*gdl)++, G_CC_SHADE, G_CC_SHADE);
    gDPSetTexturePersp((*gdl)++, G_TP_PERSP);
}

typedef struct {
    u16 width;
    u16 height;
    u16 fmt; /* 0=RGBA16, 1=I4, 2=IA8, 3=CI8 */
    u16 pad;
    u8 data[1];
} UnkImg;

extern s32 D_800DFE94;
extern s16 D_800DFE98;
extern u8 D_800DFE9C;
extern u8 D_800DFEA0;
extern u8 D_800DFEA4;
extern u8 D_800DFEA8;

void func_8003396C(Gfx **gdl, UnkImg *img, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a) {
    s32 rows;
    s32 remain;
    s32 w;
    s32 h;
    s32 fmt;

    if ((img == NULL) || (a == 0)) {
        return;
    }
    w = img->width;
    h = img->height;
    fmt = img->fmt;
    if ((w <= 0) || (h <= 0)) {
        return;
    }
    if (D_800DFE98 != fmt) {
        switch (fmt) {
        case 0:
            D_800DFE94 = 0x800;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 2:
            D_800DFE94 = 0x800;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 1:
            D_800DFE94 = 0x1000;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 3:
            D_800DFE94 = 0x800;
            break;
        default:
            return;
        }
    }
    rows = D_800DFE94 / ((w + 3) & 0xFFFC);
    if (rows <= 0) {
        return;
    }
    if ((D_800DFE9C != r) || (D_800DFEA0 != g) || (D_800DFEA4 != b) || (D_800DFEA8 != a) || (D_800DFE98 != fmt)) {
        if ((a == 0xFF) && (r == 0xFF) && (g == 0xFF) && (b == 0xFF)) {
            gDPSetCombineMode((*gdl)++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        } else {
            if (((D_800DFE9C == 0xFF) && (D_800DFEA0 == 0xFF) && (D_800DFEA4 == 0xFF) && (D_800DFEA8 == 0xFF)) || (D_800DFE98 != fmt)) {
                gDPSetCombineMode((*gdl)++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
            }
            gDPSetPrimColor((*gdl)++, 0, 0, r, g, b, a);
        }
        D_800DFE9C = r;
        D_800DFEA0 = g;
        D_800DFEA4 = b;
        D_800DFEA8 = a;
    }
    D_800DFE98 = fmt;
    remain = h;
    while (remain != 0) {
        if (remain > rows) {
            switch (fmt) {
            case 0:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, h, 0, h - remain, w - 1, (h - remain) + rows - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 1:
                gDPLoadTextureTile_4b((*gdl)++, img->data, G_IM_FMT_I, w, h, 0, h - remain, w - 1, (h - remain) + rows - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 2:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, h - remain, w - 1, (h - remain) + rows - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 3:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_CI, G_IM_SIZ_8b, w, h, 0, h - remain, w - 1, (h - remain) + rows - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            }
            gDPSetTileSize((*gdl)++, G_TX_RENDERTILE, 0, 0, (w << 2) - 1, (rows << 2) - 1);
            gSPTextureRectangle((*gdl)++, x << 2, ((y + h) - remain) << 2, ((x + w) << 2) - 1, ((((y + h) - remain) + rows) << 2) - 1, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            remain -= rows;
        } else {
            switch (fmt) {
            case 0:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, h, 0, h - remain, w - 1, h - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 1:
                gDPLoadTextureTile_4b((*gdl)++, img->data, G_IM_FMT_I, w, h, 0, h - remain, w - 1, h - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 2:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, h - remain, w - 1, h - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 3:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_CI, G_IM_SIZ_8b, w, h, 0, h - remain, w - 1, h - 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            }
            gDPSetTileSize((*gdl)++, G_TX_RENDERTILE, 0, 0, (w << 2) - 1, (remain << 2) - 1);
            gSPTextureRectangle((*gdl)++, x << 2, ((y + h) - remain) << 2, ((x + w) << 2) - 1, ((y + h) << 2) - 1, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            remain = 0;
        }
    }
}

void func_800353F4(Gfx **gdl, UnkImg *img, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a) {
    s32 rows;
    s32 remain;
    s32 w;
    s32 h;
    s32 fmt;

    if ((img == NULL) || (a == 0)) {
        return;
    }
    w = img->width;
    h = img->height;
    fmt = img->fmt;
    if ((w <= 0) || (h <= 0) || (lrs < uls) || (lrt < ult)) {
        return;
    }
    if (D_800DFE98 != fmt) {
        switch (fmt) {
        case 0:
            D_800DFE94 = 0x800;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 2:
            D_800DFE94 = 0x800;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 1:
            D_800DFE94 = 0x1000;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 3:
            D_800DFE94 = 0x800;
            break;
        default:
            return;
        }
    }
    rows = D_800DFE94 / (((lrs - uls) + 4) & 0xFFFC);
    if (rows <= 0) {
        return;
    }
    if ((D_800DFE9C != r) || (D_800DFEA0 != g) || (D_800DFEA4 != b) || (D_800DFEA8 != a) || (D_800DFE98 != fmt)) {
        if ((a == 0xFF) && (r == 0xFF) && (g == 0xFF) && (b == 0xFF)) {
            gDPSetCombineMode((*gdl)++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        } else {
            if (((D_800DFE9C == 0xFF) && (D_800DFEA0 == 0xFF) && (D_800DFEA4 == 0xFF) && (D_800DFEA8 == 0xFF)) || (D_800DFE98 != fmt)) {
                gDPSetCombineMode((*gdl)++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
            }
            gDPSetPrimColor((*gdl)++, 0, 0, r, g, b, a);
        }
        D_800DFE9C = r;
        D_800DFEA0 = g;
        D_800DFEA4 = b;
        D_800DFEA8 = a;
    }
    D_800DFE98 = fmt;
    remain = (lrt - ult) + 1;
    while (remain != 0) {
        if (remain > rows) {
            switch (fmt) {
            case 0:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, h, uls, (lrt - remain) + 1, lrs, (lrt - remain) + rows, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 1:
                gDPLoadTextureTile_4b((*gdl)++, img->data, G_IM_FMT_I, w, h, uls, (lrt - remain) + 1, lrs, (lrt - remain) + rows, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 2:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, uls, (lrt - remain) + 1, lrs, (lrt - remain) + rows, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 3:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_CI, G_IM_SIZ_8b, w, h, uls, (lrt - remain) + 1, lrs, (lrt - remain) + rows, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            }
            gDPSetTileSize((*gdl)++, G_TX_RENDERTILE, 0, 0, (((lrs - uls) + 1) << 2) - 1, (rows << 2) - 1);
            gSPTextureRectangle((*gdl)++, x << 2, (y << 2) + 3, (((x + lrs) - uls) << 2) + 3, ((y + rows) << 2) - 1, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            remain -= rows;
            y += rows;
            ult += rows;
        } else {
            switch (fmt) {
            case 0:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, h, uls, (lrt - remain) + 1, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 1:
                gDPLoadTextureTile_4b((*gdl)++, img->data, G_IM_FMT_I, w, h, uls, (lrt - remain) + 1, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 2:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, uls, (lrt - remain) + 1, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            case 3:
                gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_CI, G_IM_SIZ_8b, w, h, uls, (lrt - remain) + 1, lrs, lrt, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                break;
            }
            gDPSetTileSize((*gdl)++, G_TX_RENDERTILE, 0, 0, ((lrs - uls) << 2) + 3, (remain << 2) - 1);
            gSPTextureRectangle((*gdl)++, x << 2, y << 2, (((x + lrs) - uls) << 2) + 3, ((y + remain) << 2) - 1, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            remain = 0;
        }
    }
}

void func_80036FE4(Gfx **gdl, UnkImg *img, s32 uls, s32 ult, s32 lrs, s32 lrt, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a, s32 dsdx, s32 dtdy) {
    s32 w;
    s32 h;
    s32 fmt;
    s32 dw;
    s32 dh;

    if ((img == NULL) || (a == 0)) {
        return;
    }
    w = img->width;
    h = img->height;
    fmt = img->fmt;
    dw = (((((lrs - uls) + 1) << 12) + 0xFFF) / dsdx) - 5;
    dh = (((((lrt - ult) + 2) << 12) + 0xFFF) / dtdy) - 9;
    if ((w <= 0) || (h <= 0) || (lrs < uls) || (lrt < ult)) {
        return;
    }
    if (D_800DFE98 != fmt) {
        switch (fmt) {
        case 0:
            D_800DFE94 = 0x800;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 2:
            D_800DFE94 = 0x800;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 1:
            D_800DFE94 = 0x1000;
            gDPSetTextureLUT((*gdl)++, G_TT_NONE);
            break;
        case 3:
            D_800DFE94 = 0x800;
            break;
        default:
            return;
        }
    }
    if ((D_800DFE9C != r) || (D_800DFEA0 != g) || (D_800DFEA4 != b) || (D_800DFEA8 != a) || (D_800DFE98 != fmt)) {
        if ((a == 0xFF) && (r == 0xFF) && (g == 0xFF) && (b == 0xFF)) {
            gDPSetCombineMode((*gdl)++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        } else {
            if (((D_800DFE9C == 0xFF) && (D_800DFEA0 == 0xFF) && (D_800DFEA4 == 0xFF) && (D_800DFEA8 == 0xFF)) || (D_800DFE98 != fmt)) {
                gDPSetCombineMode((*gdl)++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
            }
            gDPSetPrimColor((*gdl)++, 0, 0, r, g, b, a);
        }
        D_800DFE9C = r;
        D_800DFEA0 = g;
        D_800DFEA4 = b;
        D_800DFEA8 = a;
    }
    D_800DFE98 = fmt;
    switch (fmt) {
        case 0:
            gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, w, h, uls, ult, lrs + 1, lrt + 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 1:
            gDPLoadTextureTile_4b((*gdl)++, img->data, G_IM_FMT_I, w, h, uls, ult, lrs + 1, lrt + 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 2:
            gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, uls, ult, lrs + 1, lrt + 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 3:
            gDPLoadTextureTile((*gdl)++, img->data, G_IM_FMT_CI, G_IM_SIZ_8b, w, h, uls, ult, lrs + 1, lrt + 1, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPSetTileSize((*gdl)++, G_TX_RENDERTILE, 0, 0, (((lrs - uls) + 1) << 2) + 3, (((lrt - ult) + 1) << 2) + 3);
    gSPTextureRectangle((*gdl)++, x, y, x + dw, y + dh, G_TX_RENDERTILE, 0, 0, dsdx, dtdy);
}

typedef struct {
    UnkImg *img;      /* 0x00 */
    s16 widths[0x40]; /* 0x04 per-glyph proportional widths */
    s16 cellW;        /* 0x84 */
    s16 cellH;        /* 0x86 */
} Font; /* 0x88 */

extern Font D_80102D48[5];

void func_80037F9C(UnkImg *img, u8 slot) {
    s32 i;

    if (slot >= 5) {
        return;
    }
    D_80102D48[slot].img = img;
    if (img == NULL) {
        return;
    }
    D_80102D48[slot].cellW = img->width;
    D_80102D48[slot].cellH = img->height / 64;
    for (i = 0; i < 0x40; i++) {
        D_80102D48[slot].widths[i] = D_80102D48[slot].cellW - 1;
        while ((*((u8 *)(((i * D_80102D48[slot].cellW) * D_80102D48[slot].cellH) + D_80102D48[slot].widths[i] + (u8 *)img) + 8) & 0xF0) == 0xF0) {
            D_80102D48[slot].widths[i]--;
        }
        if (D_80102D48[slot].widths[i] < 2) {
            D_80102D48[slot].widths[i] = D_80102D48[slot].cellW - 1;
        }
    }
}

void func_80038254(UnkImg *img) {
    func_80037F9C(img, 0);
}

void func_80038284(UnkImg *img) {
    func_80037F9C(img, 1);
}

void func_800382B4(Gfx **gdl, u8 slot, s32 x, s32 y, u8 *str, s32 r, s32 g, s32 b, s32 a) {
    s32 i;
    s32 startX;

    if (slot >= 5) {
        return;
    }
    if (D_80102D48[slot].img == NULL) {
        return;
    }
    startX = x;
    i = 0;
    while (str[i] != 0) {
        func_800353F4(gdl, D_80102D48[slot].img, 0, D_80102D48[slot].cellH * (str[i] - 0x20),
                      D_80102D48[slot].widths[str[i] - 0x20] - 1,
                      ((D_80102D48[slot].cellH * (str[i] - 0x20)) + D_80102D48[slot].cellH) - 1,
                      x, y, r, g, b, a);
        x += D_80102D48[slot].widths[str[i] - 0x20];
        i++;
    }
}

void func_80038478(Gfx **gdl, s32 x, s32 y, u8 *str, s32 r, s32 g, s32 b, s32 a) {
    func_800382B4(gdl, 0, x, y, str, r, g, b, a);
}

void func_800384E4(Gfx **gdl, s32 x, s32 y, u8 *str, s32 r, s32 g, s32 b, s32 a) {
    func_800382B4(gdl, 1, x, y, str, r, g, b, a);
}

extern s16 D_800DFEAC;

void func_80038550(Gfx **gdl, u8 slot, s32 x, s32 y, u8 *str, s32 r, s32 g, s32 b, s32 a) {
    s32 i;
    s32 startX;

    if (slot >= 5) {
        return;
    }
    if (D_80102D48[slot].img == NULL) {
        return;
    }
    startX = x;
    i = 0;
    while (str[i] != 0) {
        func_80036FE4(gdl, D_80102D48[slot].img, 0, D_80102D48[slot].cellH * (str[i] - 0x20),
                      D_80102D48[slot].widths[str[i] - 0x20] - 1,
                      ((D_80102D48[slot].cellH * (str[i] - 0x20)) + D_80102D48[slot].cellH) - 1,
                      x, y, r, g, b, a, D_800DFEAC, D_800DFEAC);
        x += (D_80102D48[slot].widths[str[i] - 0x20] << 12) / D_800DFEAC;
        i++;
    }
}

void func_80038760(Gfx **gdl, s32 x, s32 y, u8 *str, s32 r, s32 g, s32 b, s32 a) {
    func_80038550(gdl, 0, x, y, str, r, g, b, a);
}

s32 func_800387CC(u8 *str, u8 slot) {
    s32 i;
    s32 total;

    if (slot >= 5) {
        return 0;
    }
    if (D_80102D48[slot].img == NULL) {
        return 0;
    }
    i = 0;
    total = 0;
    while (str[i] != 0) {
        total += D_80102D48[slot].widths[str[i] - 0x20];
        i++;
    }
    return total;
}

s32 func_800388BC(u8 *str) {
    return func_800387CC(str, 0);
}

s32 func_800388F4(u8 *str) {
    return func_800387CC(str, 1);
}

s32 func_8003892C(u8 *str, u8 slot) {
    s32 i;
    s32 total;

    if (slot >= 5) {
        return 0;
    }
    if (D_80102D48[slot].img == NULL) {
        return 0;
    }
    i = 0;
    total = 0;
    while (str[i] != 0) {
        total += (D_80102D48[slot].widths[str[i] - 0x20] << 12) / D_800DFEAC;
        i++;
    }
    return total;
}

s32 func_80038A50(u8 *str) {
    return func_8003892C(str, 0);
}

typedef struct {
    s16 x, y, z;
    u16 flag;
    s16 s, t;
    u8 r, g, b, a;
} BgVtx; /* 0x10 — matches Vtx_t */

typedef struct {
    u8 pad0[0x1000];
    Mtx proj;          /* 0x1000 */
    Mtx mv;            /* 0x1040 */
    u8 pad1080[0x804];
    BgVtx *vtx;        /* 0x1884 */
} UnkFrame;

typedef struct {
    UnkImg *tex[7];    /* 0x00 background texture frames */
    u8 colA[8];        /* 0x1C current color pair (top/bottom RGBA) */
    u8 colB[8];        /* 0x24 displayed color pair */
    u8 pad2C[0x18];
    u8 target[8];      /* 0x44 fade target pair */
} UnkBg;

extern UnkBg D_800DFEB0;
extern u32 D_800DFEDC;
extern u32 D_800DFEE0;
extern s32 D_800DFEE4;
extern s32 D_800DFEE8;
extern s32 D_800DFEEC;
extern s32 D_800DFEF0;
extern f32 D_800EDA9C;
extern Gfx *D_800F22B4;
extern UnkFrame *D_801028D4;

void func_80038A88(void) {
    s32 scrollX;
    s32 scrollY;
    s32 i;
    s32 j;
    s32 k;
    s32 texIdx;
    u16 perspNorm;

    for (i = 0; i < 7; i++) {
        if (D_800DFEB0.tex[i] == NULL) {
            return;
        }
    }
    j = 0;
    for (i = 0; i < 4; i++) {
        if ((D_800DFEB0.target[i] != D_800DFEB0.colA[i]) || (D_800DFEB0.target[i + 4] != D_800DFEB0.colA[i + 4])) {
            j = 1;
        }
    }
    if (j != 0) {
        if (D_800DFEF0 == 0) {
            D_800DFEF0 = 0x28;
        }
    } else {
        D_800DFEF0 = 0;
        D_800DFEB0.target[0] = D_800DFEB0.colA[0];
        D_800DFEB0.target[1] = D_800DFEB0.colA[1];
        D_800DFEB0.target[2] = D_800DFEB0.colA[2];
        D_800DFEB0.target[3] = D_800DFEB0.colA[3];
        D_800DFEB0.target[4] = D_800DFEB0.colA[4];
        D_800DFEB0.target[5] = D_800DFEB0.colA[5];
        D_800DFEB0.target[6] = D_800DFEB0.colA[6];
        D_800DFEB0.target[7] = D_800DFEB0.colA[7];
        D_800DFEB0.colB[0] = D_800DFEB0.colA[0];
        D_800DFEB0.colB[1] = D_800DFEB0.colA[1];
        D_800DFEB0.colB[2] = D_800DFEB0.colA[2];
        D_800DFEB0.colB[3] = D_800DFEB0.colA[3];
        D_800DFEB0.colB[4] = D_800DFEB0.colA[4];
        D_800DFEB0.colB[5] = D_800DFEB0.colA[5];
        D_800DFEB0.colB[6] = D_800DFEB0.colA[6];
        D_800DFEB0.colB[7] = D_800DFEB0.colA[7];
    }
    if ((D_800DFEB0.colA[7] == 0) || (D_800DFEB0.colA[3] == 0)) {
        return;
    }
    scrollX = (u32)D_800DFEDC + (D_800DFEE8 - D_800DFEEC) * -1;
    scrollY = (u32)D_800DFEE0 + (D_800DFEE8 - D_800DFEEC) * -1;
    texIdx = D_800DFEE4;
    while ((scrollY < 0) || (scrollX < 0)) {
        scrollX += 0x540;
        scrollY += 0x140;
        if (scrollX >= 0x17C0) {
            scrollX -= 0x17C0;
        }
        texIdx += 1;
        if (texIdx >= 7) {
            texIdx = 0;
        }
    }
    D_800DFEDC = scrollX;
    D_800DFEE0 = scrollY;
    D_800DFEE4 = texIdx;
    D_800DFEEC = D_800DFEE8;
    for (i = 0; i < 0xE; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                D_801028D4->vtx[(i * 4) + (j * 2) + k + 0xFC].x = ((k * 0x2BF) + scrollX) - 0xC80;
                D_801028D4->vtx[(i * 4) + (j * 2) + k + 0xFC].y = ((j * 0x2BF) - scrollY) + 0x780;
                D_801028D4->vtx[(i * 4) + (j * 2) + k + 0xFC].z = -0xFA0;
                D_801028D4->vtx[(i * 4) + (j * 2) + k + 0xFC].flag = 0;
                D_801028D4->vtx[(i * 4) + (j * 2) + k + 0xFC].s = k * 0xAC0;
                D_801028D4->vtx[(i * 4) + (j * 2) + k + 0xFC].t = (-j * 0xAC0) + 0xAC0;
            }
        }
        D_801028D4->vtx[(i * 4) + 0xFD].r = ((D_800DFEB0.target[4] * scrollX) + (D_800DFEB0.target[0] * (0x17C0 - scrollX))) / 6080;
        D_801028D4->vtx[(i * 4) + 0xFD].g = ((D_800DFEB0.target[5] * scrollX) + (D_800DFEB0.target[1] * (0x17C0 - scrollX))) / 6080;
        D_801028D4->vtx[(i * 4) + 0xFD].b = ((D_800DFEB0.target[6] * scrollX) + (D_800DFEB0.target[2] * (0x17C0 - scrollX))) / 6080;
        D_801028D4->vtx[(i * 4) + 0xFD].a = ((D_800DFEB0.target[7] * scrollX) + (D_800DFEB0.target[3] * (0x17C0 - scrollX))) / 6080;
        scrollX += 0x540;
        scrollY += 0x140;
        if (scrollX >= 0x17C0) {
            scrollX -= 0x17C0;
        }
    }
    guPerspective(&D_801028D4->proj, &perspNorm, 45.0f, 1.3333334f, 1.0f, D_800EDA9C, 1.0f);
    gSPPerspNormalize(D_800F22B4++, perspNorm);
    guTranslate(&D_801028D4->mv, 0.0f, 0.0f, -500.0f);
    gSPMatrix(D_800F22B4++, (u8 *)D_801028D4 + 0x80001000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *)D_801028D4 + 0x80001040, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(D_800F22B4++);
    gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_AVERAGE);
    gDPSetRenderMode(D_800F22B4++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPClearGeometryMode(D_800F22B4++, G_SHADING_SMOOTH | G_CULL_BACK | G_LIGHTING);
    gSPSetGeometryMode(D_800F22B4++, G_SHADE);
    gSPTexture(D_800F22B4++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(D_800F22B4++, G_CC_MODULATERGBA, G_CC_MODULATERGBA);
    gDPSetBlendColor(D_800F22B4++, 0, 0, 0, 0);
    gDPSetTile(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 11, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    for (i = 0; i < 0xE; i++) {
        gSPVertex(D_800F22B4++, (u8 *)D_801028D4->vtx + (((i * 4) + 0xFC) << 4), 4, 0);
        gDPLoadTextureTile(D_800F22B4++, D_800DFEB0.tex[texIdx], G_IM_FMT_RGBA, G_IM_SIZ_16b, 44, 44, 0, 0, 43, 43, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x560, 0x560);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 1);
        gSP1Triangle(D_800F22B4++, 1, 2, 3, 0);
        texIdx += 1;
        if (texIdx >= 7) {
            texIdx = 0;
        }
    }
    gSPTexture(D_800F22B4++, 0, 0, 0, 0, G_OFF);
}

void func_80039854(u8 *img) {
    s32 j;
    s32 i;

    gDPPipeSync(D_800F22B4++);
    gDPSetCycleType(D_800F22B4++, G_CYC_COPY);
    gDPSetCombineMode(D_800F22B4++, G_CC_DECALRGB, G_CC_DECALRGB);
    gDPSetRenderMode(D_800F22B4++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetBlendColor(D_800F22B4++, 0, 0, 0, 0);
    gSPTexture(D_800F22B4++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetAlphaCompare(D_800F22B4++, G_AC_NONE);
    gDPSetTexturePersp(D_800F22B4++, G_TP_NONE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_POINT);
    gDPSetTextureConvert(D_800F22B4++, G_TC_FILT);
    gDPSetTextureDetail(D_800F22B4++, G_TD_CLAMP);
    gDPSetTextureLOD(D_800F22B4++, G_TL_TILE);
    gDPSetTextureLUT(D_800F22B4++, G_TT_NONE);
    gSPClearGeometryMode(D_800F22B4++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gDPSetTile(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 5; j++) {
            gDPLoadTextureTile(D_800F22B4++, img, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 240, j << 6, i * 0x1E, (j << 6) + 0x3F, (i * 0x1E) + 0x1D, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x7E0, 0x3A0);
            gSPTextureRectangle(D_800F22B4++, (j << 6) << 2, (i * 0x1E) << 2, (((j << 6) + 0x40) << 2) - 1, (((i * 0x1E) + 0x1E) << 2) - 1, G_TX_RENDERTILE, 0, 0, 0x1000, 0x400);
        }
    }
    gDPPipeSync(D_800F22B4++);
    gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
    gDPSetCombineMode(D_800F22B4++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(D_800F22B4++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(D_800F22B4++, G_TP_PERSP);
}

extern UnkImg *D_800DFEFC; /* 160x120 IA8 full-screen overlay image */




void func_8003A06C(s32 r, s32 g, s32 b, s32 a) {
    s32 j;
    s32 i;

    if (a == 0) {
        return;
    }
    gDPPipeSync(D_800F22B4++);
    gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
    gDPSetCombineMode(D_800F22B4++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetPrimColor(D_800F22B4++, 0, 0, r, g, b, a);
    if (a == 0xFF) {
        gDPSetRenderMode(D_800F22B4++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    } else {
        gDPSetRenderMode(D_800F22B4++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    gDPSetBlendColor(D_800F22B4++, 0, 0, 0, 0);
    gSPTexture(D_800F22B4++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetAlphaCompare(D_800F22B4++, G_AC_NONE);
    gDPSetTexturePersp(D_800F22B4++, G_TP_NONE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_POINT);
    gDPSetTextureConvert(D_800F22B4++, G_TC_FILT);
    gDPSetTextureDetail(D_800F22B4++, G_TD_CLAMP);
    gDPSetTextureLOD(D_800F22B4++, G_TL_TILE);
    gDPSetTextureLUT(D_800F22B4++, G_TT_NONE);
    gSPClearGeometryMode(D_800F22B4++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            gDPLoadTextureTile(D_800F22B4++, D_800DFEFC, G_IM_FMT_IA, G_IM_SIZ_8b, 160, 120, j << 5, i * 0x3C, (j << 5) + 0x1F, (i * 0x3C) + 0x3B, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x3E0, 0x760);
            gSPTextureRectangle(D_800F22B4++, (j << 6) << 2, (i * 0x78) << 2, (((j << 6) + 0x40) << 2) - 1, (((i * 0x78) + 0x78) << 2) - 1, G_TX_RENDERTILE, 0, 0, 0x200, 0x200);
        }
    }
    gDPPipeSync(D_800F22B4++);
    gDPSetCombineMode(D_800F22B4++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(D_800F22B4++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(D_800F22B4++, G_TP_PERSP);
}

void func_8003A900(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 j;

    if (arg4 == 0) {
        return;
    }
    gDPPipeSync(D_800F22B4++);
    gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
    gDPSetCombineMode(D_800F22B4++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetPrimColor(D_800F22B4++, 0, 0, arg1, arg2, arg3, arg4);
    if (arg4 == 0xFF) {
        gDPSetRenderMode(D_800F22B4++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    } else {
        gDPSetRenderMode(D_800F22B4++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }
    gDPSetBlendColor(D_800F22B4++, 0, 0, 0, 0);
    gSPTexture(D_800F22B4++, 0x8000, 0x8000, 0, 0, G_ON);
    gDPSetAlphaCompare(D_800F22B4++, G_AC_NONE);
    gDPSetTexturePersp(D_800F22B4++, G_TP_NONE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_POINT);
    gDPSetTextureConvert(D_800F22B4++, G_TC_FILT);
    gDPSetTextureDetail(D_800F22B4++, G_TD_CLAMP);
    gDPSetTextureLOD(D_800F22B4++, G_TL_TILE);
    gDPSetTextureLUT(D_800F22B4++, G_TT_NONE);
    gSPClearGeometryMode(D_800F22B4++, 0x1F3205);
    gDPSetTile(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 2, 0, 0, 2, 0, 0);
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 5; i++) {
            gDPSetTextureImage(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, arg0);
            { Gfx *g = D_800F22B4++; g->words.w0 = (((((i * 64 - i * 64) * 2 + 0x87) >> 3) & 0x1FF) << 9) | 0xF5100000; g->words.w1 = 0x07080200; }
            gDPLoadSync(D_800F22B4++);
            { Gfx *g = D_800F22B4++; g->words.w0 = (((i * 64 * 4) & 0xFFF) << 12) | 0xF4000000 | ((j * 30 * 4) & 0xFFF); g->words.w1 = ((((i * 64 + 0x3F) << 2) & 0xFFF) << 12) | 0x07000000 | ((((j * 30 + 0x1D) << 2) & 0xFFF)); }
            gDPPipeSync(D_800F22B4++);
            { Gfx *g = D_800F22B4++; g->words.w0 = (((((i * 64 - i * 64) * 2 + 0x87) >> 3) & 0x1FF) << 9) | 0xF5100000; g->words.w1 = 0x00080200; }
            { Gfx *g = D_800F22B4++; g->words.w0 = (((i * 64 * 4) & 0xFFF) << 12) | 0xF2000000 | ((j * 30 * 4) & 0xFFF); g->words.w1 = ((((i * 64 + 0x3F) << 2) & 0xFFF) << 12) | ((((j * 30 + 0x1D) << 2) & 0xFFF)); }
            gDPSetTileSize(D_800F22B4++, 0, 0, 0, 2016, 928);
            { Gfx *g = D_800F22B4++; g->words.w0 = (((((i * 64 + 0x40) << 2) - 1) & 0xFFF) << 12) | 0xE4000000 | (((((j * 30 + 0x1E) << 2) - 1) & 0xFFF)); g->words.w1 = (((i * 64 * 4) & 0xFFF) << 12) | ((j * 30 * 4) & 0xFFF); }
            { Gfx *g = D_800F22B4++; g->words.w0 = 0xB4000000; g->words.w1 = 0; }
            { Gfx *g = D_800F22B4++; g->words.w0 = 0xB3000000; g->words.w1 = 0x04000400; }
        }
    }
    gDPPipeSync(D_800F22B4++);
    gDPSetCombineMode(D_800F22B4++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(D_800F22B4++, G_RM_OPA_SURF, G_RM_OPA_CI2);
    gDPSetTexturePersp(D_800F22B4++, G_TP_PERSP);
}

typedef struct {
    u8 unk0[0xE];
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
} StructFEFC;



extern UnkImg *D_800DFEFC;
extern u16 *D_800DFF00;
extern u16 D_800DFF08;
extern u16 D_800DFF0E;
extern u16 D_800DFF10;
extern s32 D_800DFF14;
extern s32 D_800DFF18;
extern s32 D_800DFF1C;
extern s32 D_800DFF20;
extern u16 D_800DFF24;
extern u8 D_800E2818[];
extern Gfx *D_800F22B4;
extern UnkFrame *D_801028D4;
extern u8 D_8010B358[];

void func_80039854(u8 *img);
void func_8003A06C(s32 r, s32 g, s32 b, s32 a);
void func_8003DAA4(void);
void func_8003DE98(void);
void func_8003DFAC(void);
void func_8003E1A0(void);
void func_8007D45C(void *, void *, s32);

#define SA ((StructFEFC *)&D_800DFEFC)

void func_8003B1A4(void) {
    s32 pad0;
    s32 i;
    s32 pad1;
    u16 perspNorm;

    if (D_800DFF08 != D_800DFF10) {
        if (D_800DFF10 == 0) {
            D_800DFF1C = 0;
            D_800DFF14 = 1;
            D_800DFF18 = 1;
        }
        D_800DFF20 = D_800DFF14;
        D_800DFF10 = D_800DFF08;
        D_800DFF24 = 0;
        switch (D_800DFF08) {
        case 1:
            func_8003DE98();
            break;
        case 4:
            func_8003DFAC();
            if ((SA->unkE != 0) || (SA->unkF != 0) || (SA->unk10 != 0)) {
                func_8007D45C(D_8010B358, D_800E2818, 0);
            }
            break;
        case 5:
            func_8003E1A0();
            func_8007D45C(D_8010B358, D_800E2818, 1);
            break;
        }
    }
    if ((D_800DFEFC == 0) || (D_800DFF00 == 0)) {
        return;
    }
    D_800DFF1C = D_800DFF14;
    D_800DFF14 = D_800DFF18;
    switch (D_800DFF08) {
    case 4:
        if ((D_800DFF14 - D_800DFF20) >= 0x28) {
            D_800DFF0E = 0xFF;
        } else {
            D_800DFF0E = (D_800DFF14 - D_800DFF20) * 0xFF / 40;
        }
        break;
    case 5:
        if ((D_800DFF14 - D_800DFF20) >= 0x28) {
            D_800DFF0E = 0;
        } else {
            D_800DFF0E = 0xFF - (D_800DFF14 - D_800DFF20) * 0xFF / 40;
        }
        break;
    case 0:
        D_800DFF0E = 0;
        break;
    case 1:
        D_800DFF0E = 0xFF;
        break;
    }
    if (D_800DFF0E < 0xFF) {
        func_80039854((u8 *)D_800DFF00);
    }
    if (D_800DFF0E != 0) {
        func_8003A06C(SA->unkE / 2, SA->unkF / 2, SA->unk10 / 2, D_800DFF0E);
    }
    if (D_800DFF08 == 0) {
        return;
    }
    func_8003DAA4();
    switch (D_800DFF08) {
    case 4:
        if (D_800DFF24 != 0) {
            D_800DFF08 = 1;
        }
        break;
    case 5:
        if (D_800DFF24 != 0) {
            D_800DFF08 = 0;
        }
        break;
    }
    guPerspective((Mtx *)((u8 *)D_801028D4 + 0xF80), &perspNorm, 45.0f, 1.3333334f, 1.0f, 7500.0f, 1.0f);
    { gSPPerspNormalize(D_800F22B4++, perspNorm); }
    guTranslate((Mtx *)((u8 *)D_801028D4 + 0xFC0), 1.0f, 1.0f, -500.0f);
    { gSPMatrix(D_800F22B4++, (u32)((u8 *)D_801028D4 + 0x80000F80), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH); }
    { gSPMatrix(D_800F22B4++, (u32)((u8 *)D_801028D4 + 0x80000FC0), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH); }
    gDPPipeSync(D_800F22B4++);
    gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_AVERAGE);
    { gDPSetRenderMode(D_800F22B4++, G_RM_XLU_SURF, G_RM_XLU_SURF2); }
    gSPClearGeometryMode(D_800F22B4++, 0x23200);
    gSPSetGeometryMode(D_800F22B4++, 0x4);
    gSPTexture(D_800F22B4++, 0x8000, 0x8000, 0, 0, G_ON);
    gDPSetCombineMode(D_800F22B4++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetBlendColor(D_800F22B4++, 0, 0, 0, 0);
    { Gfx *g = D_800F22B4++; g->words.w0 = 0xFA000000; g->words.w1 = (SA->unk11 & 0xFF) | (((SA->unkE & 0xFF) << 24) | ((SA->unkF & 0xFF) << 16) | ((SA->unk10 & 0xFF) << 8)); }
    gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 0, 0, 2, 0, 0, 2, 0, 0);
    for (i = 0; i < 3; i++) {
        { gSPVertex(D_800F22B4++, (u32)&D_801028D4->vtx[i * 9 * 4], 16, 0); }
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4000000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0707C000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2000000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0007C000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 1, 2, 3, 0);
        gSP1Triangle(D_800F22B4++, 4, 5, 6, 0);
        gSP1Triangle(D_800F22B4++, 5, 6, 7, 0);
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4080000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x070FC000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2080000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x000FC000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 8, 9, 10, 0);
        gSP1Triangle(D_800F22B4++, 9, 10, 11, 0);
        gSP1Triangle(D_800F22B4++, 12, 13, 14, 0);
        gSP1Triangle(D_800F22B4++, 13, 14, 15, 0);
        { gSPVertex(D_800F22B4++, (u32)&D_801028D4->vtx[i * 9 * 4 + 0x20], 4, 0); }
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4200000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0723C000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2200000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0023C000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 63, 63);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 1, 2, 3, 0);
        { gSPVertex(D_800F22B4++, (u32)&D_801028D4->vtx[i * 9 * 4 + 0x10], 16, 0); }
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4180000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x071FC000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2180000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x001FC000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 12, 13, 14, 0);
        gSP1Triangle(D_800F22B4++, 13, 14, 15, 0);
        gSP1Triangle(D_800F22B4++, 8, 9, 10, 0);
        gSP1Triangle(D_800F22B4++, 9, 10, 11, 0);
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4100000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0717C000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2100000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0017C000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 4, 5, 6, 0);
        gSP1Triangle(D_800F22B4++, 5, 6, 7, 0);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 1, 2, 3, 0);
    }
    for (i = 6; i >= 3; i--) {
        { gSPVertex(D_800F22B4++, (u32)&D_801028D4->vtx[i * 9 * 4], 16, 0); }
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4000000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0707C000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2000000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0007C000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 1, 2, 3, 0);
        gSP1Triangle(D_800F22B4++, 4, 5, 6, 0);
        gSP1Triangle(D_800F22B4++, 5, 6, 7, 0);
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4080000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x070FC000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2080000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x000FC000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 8, 9, 10, 0);
        gSP1Triangle(D_800F22B4++, 9, 10, 11, 0);
        gSP1Triangle(D_800F22B4++, 12, 13, 14, 0);
        gSP1Triangle(D_800F22B4++, 13, 14, 15, 0);
        { gSPVertex(D_800F22B4++, (u32)&D_801028D4->vtx[i * 9 * 4 + 0x20], 4, 0); }
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4200000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0723C000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2200000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0023C000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 63, 63);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 1, 2, 3, 0);
        { gSPVertex(D_800F22B4++, (u32)&D_801028D4->vtx[i * 9 * 4 + 0x10], 16, 0); }
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4180000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x071FC000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2180000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x001FC000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 12, 13, 14, 0);
        gSP1Triangle(D_800F22B4++, 13, 14, 15, 0);
        gSP1Triangle(D_800F22B4++, 8, 9, 10, 0);
        gSP1Triangle(D_800F22B4++, 9, 10, 11, 0);
        gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 160, (u32)D_800DFEFC);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(D_800F22B4++);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF4100000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0717C000; }
        gDPPipeSync(D_800F22B4++);
        gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        { Gfx *g = D_800F22B4++; g->words.w0 = (((-i * 0x10 + 0x60) << 2) & 0xFFF) | 0xF2100000; g->words.w1 = (((-i * 0x10 + 0x6F) << 2) & 0xFFF) | 0x0017C000; }
        gDPSetTileSize(D_800F22B4++, 0, 0, 0, 127, 63);
        gSP1Triangle(D_800F22B4++, 4, 5, 6, 0);
        gSP1Triangle(D_800F22B4++, 5, 6, 7, 0);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 1);
        gSP1Triangle(D_800F22B4++, 1, 2, 3, 0);
    }
    gSPTexture(D_800F22B4++, 0x0, 0x0, 0, 0, G_OFF);
    gDPPipeSync(D_800F22B4++);
}



void func_8003D838(void) {
    s32 j;
    s32 i;
    s32 k;
    s32 l;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 9; j++) {
            for (k = 0; k < 2; k++) {
                for (l = 0; l < 2; l++) {
                    D_801028D4->vtx[(i * 9 + j) * 4 + k * 2 + l].x = j * 95 + k * 89 - 0x1A9;
                    D_801028D4->vtx[(i * 9 + j) * 4 + k * 2 + l].y = i * 95 + l * 89 - 0x14A;
                    D_801028D4->vtx[(i * 9 + j) * 4 + k * 2 + l].flag = 0;
                    D_801028D4->vtx[(i * 9 + j) * 4 + k * 2 + l].s = ((j & 1) << 10) + k * 959;
                    D_801028D4->vtx[(i * 9 + j) * 4 + k * 2 + l].t = -l * 959 + 0x3BF;
                }
            }
        }
    }
}

extern u16 D_800DFF24;
extern s32 D_800DFF04;
struct S {
    s32 pad[12];
    s32 a[9][7];
    s32 b[9][7];
    s32 c[9][7];
    u16 d[9][7];
    u16 e[9][7];
};
#define SB ((struct S *)&D_800DFEFC)
extern s32 D_800DFF2C[9][7];
extern u16 D_800E0220[9][7];
extern u16 D_800E029E[9][7];
extern s32 D_800DFF14;
void func_8003DAA4(void) {
    s32 j;
    s32 i;
    s32 k;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1c;
    D_800DFF24 = 1;
    func_8003D838();
    D_800DFF04 = D_800DFF14 >> 3;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 9; j++) {
            sp28 = sins((u16)(14000 * j + 9234 * i + 768 * D_800DFF14) * 1) / 0xC00;
            for (k = 0; k < 4; k++) {
                sp20 = D_801028D4->vtx[(i * 9 + j) * 4 + k].x;
                sp1c = D_801028D4->vtx[(i * 9 + j) * 4 + k].y;
                sp24 = sp28 - ((sp20 - 4) * (sp20 - 4) + (sp1c - 3) * (sp1c - 3)) / 0x33E;
                D_801028D4->vtx[(i * 9 + j) * 4 + k].z = (D_800DFF2C[j][i] >> 4) + sp24;
            }
            if (D_800E0220[j][i] <= 0) {
                D_800DFF2C[j][i] = 0;
            } else {
                D_800DFF24 = 0;
                SB->d[j][i] -= 1;
                if (D_800E029E[j][i] > 0) {
                    SB->e[j][i] -= 1;
                } else {
                    SB->a[j][i] += SB->b[j][i];
                    SB->b[j][i] += SB->c[j][i];
                }
            }
        }
    }
}


extern s32 D_800E0028[9][7];
extern s32 D_800E0124[9][7];

void func_8003DE98(void) {
    s32 j;
    s32 i;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 9; j++) {
            D_800DFF2C[j][i] = 0;
            D_800E0028[j][i] = 0;
            D_800E0124[j][i] = 0;
            D_800E0220[j][i] = 0;
            D_800E029E[j][i] = 0;
        }
    }
}


void func_8003DFAC(void) {
    s32 j;
    s32 i;
    s32 c;
    s32 a;
    s32 b;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 9; j++) {
            a = j - 4;
            if (a < 0) {
                a = -a;
            }
            b = i - 3;
            if (b < 0) {
                b = -b;
            }
            c = 40 - ((40 - (a + b) * 40 / 7) >> 1);
            D_800E0028[j][i] = -(c * 59);
            D_800DFF2C[j][i] = ((c * c + c) >> 1) * 59;
            D_800E0124[j][i] = 59;
            D_800E0220[j][i] = c;
            D_800E029E[j][i] = 0;
        }
    }

}


void func_8003E1A0(void) {
    s32 j;
    s32 i;
    s32 c;
    s32 a;
    s32 b;

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 9; j++) {
            a = j - 4;
            if (a < 0) {
                a = -a;
            }
            b = i - 3;
            if (b < 0) {
                b = -b;
            }
            c = (40 - (a + b) * 40 / 7) >> 1;
            D_800DFF2C[j][i] = 0;
            D_800E0028[j][i] = 59;
            D_800E0124[j][i] = 59;
            D_800E0220[j][i] = 40;
            D_800E029E[j][i] = c;
        }
    }
}


extern char D_80102670[];
extern s32 D_8010268C;
extern s32 D_80102694;

char *func_8003E358(s32 arg0) {
    if (arg0 < 0) {
        D_8010268C = -arg0;
    } else {
        D_8010268C = arg0;
    }
    D_80102670[0x17] = 0;
    D_80102694 = 0x17;
    do {
        D_80102694--;
        D_80102670[D_80102694] = D_8010268C % 10 + 0x30;
        D_8010268C = D_8010268C / 10;
    } while (D_8010268C != 0);
    if (arg0 < 0) {
        D_80102694--;
        D_80102670[D_80102694] = 0x2D;
    }
    return D_80102694 + D_80102670;
}


extern s32 D_800E0B10;
extern u8 D_800DF770;
extern s8 D_800E07CC[8];
extern u32 D_800DFDD4[];

void func_8003E460(void) {
    s32 i;

    D_800E0B10 = 0;
    if (D_800DF770 & 8) {
        D_800E07CC[D_800E0B10] = 3;
    }
    if (D_800DF770 & 4) {
        D_800E07CC[D_800E0B10] = 2;
    }
    if (D_800DF770 & 2) {
        D_800E07CC[D_800E0B10] = 1;
    }
    if (D_800DF770 & 1) {
        D_800E07CC[D_800E0B10] = 0;
    }
    for (i = 0; i < 4; i++) {
        if (D_800DFDD4[i] & 0xB000) {
            D_800E07CC[D_800E0B10] = i;
        }
    }
}


s32 func_8003E590(void) {
    if (D_800DF770 == 0 || D_800DF770 == 1 || D_800DF770 == 2 || D_800DF770 == 4 || D_800DF770 == 8) {
        return 1;
    }
    return 0;
}



void func_8003E5F4(void) {
    s32 i;
    s32 j;

    if (func_8003E590() != 0) {
        return;
    }
    j = -1;
    for (i = 0; i < 8; i++) {
        do {
            j = (j + 1) & 3;
        } while (!(D_800DF770 & (1 << j)));
        D_800E07CC[i] = j;
    }
}

extern s32 D_800E0B14;

void func_8003E698(s32 arg0) {
    if (D_800E07CC[D_800E0B10] == D_800E07CC[D_800E0B14]) {
        do {
            D_800E07CC[arg0] = (D_800E07CC[arg0] + 1) & 3;
        } while (!((1 << D_800E07CC[arg0]) & D_800DF770));
    }
}

extern s16 D_800DFD48;
extern u16 D_800DFD68;
extern u16 D_800DFD6C;
extern u16 D_800DFD70;
extern u16 D_800DFD74;
extern s32 D_800DFD8C;
extern s32 D_800DFD90;
extern s32 D_800DFD94;
extern s32 D_800DFD98;
extern s32 D_800DFD9C;
extern u32 D_800DFDA4[];
extern u32 D_800DFDB4[];
extern u32 D_800DFDC4[];
extern u32 D_800DFDD4[];
extern u32 D_800DFDE4[];
extern s16 D_800E1202;
extern s32 D_800E1208;
extern s32 D_800E1300;
extern s32 D_800E1304;
extern s32 D_800E1308;
extern s32 D_800E130C;
extern s32 D_800E1310;
extern s32 D_800E1314;
extern s32 D_800E1318;
extern s32 D_800E131C;
extern s32 D_800E1320[];
extern s32 D_800E1330[];
extern s32 D_800E1340[];
extern s32 D_800E1350[];
extern s32 D_800E1360[];
extern s32 D_800E1370[];
extern s32 D_800E1380[];
extern s32 D_800E1390[];
extern u8 D_800E13A0;
extern u8 D_800E13A4;
extern u8 D_800E13A8;
extern u8 D_800E13AC;
extern u8 D_800E13B0;
extern u8 D_800E13B4;
extern u8 D_800E13B8;
extern u8 D_800E13BC;
extern u8 D_80102698;

void func_8003E724(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_800DFDA4[i] = D_800DFDB4[i];
    }
    D_800DFDB4[0] = D_800DFD68;
    D_800DFDB4[1] = D_800DFD6C;
    D_800DFDB4[2] = D_800DFD70;
    D_800DFDB4[3] = D_800DFD74;
    D_800DFD90 = D_800DFDB4[0] | D_800DFDB4[1] | D_800DFDB4[2] | D_800DFDB4[3];
    D_800DFD9C = D_800DFD8C ^ D_800DFD90;
    D_800DFD94 = D_800DFD8C & D_800DFD9C;
    D_800DFD98 = D_800DFD90 & D_800DFD9C;
    D_800DFD8C = D_800DFD90;
    if (D_800DFD94 & 0x800) {
        D_800E1300 = 0;
    }
    if (D_800DFD94 & 0x400) {
        D_800E1304 = 0;
    }
    if (D_800DFD94 & 0x200) {
        D_800E1308 = 0;
    }
    if (D_800DFD94 & 0x100) {
        D_800E130C = 0;
    }
    if (D_800DFD94 & 2) {
        D_800E1310 = 0;
    }
    if (D_800DFD94 & 4) {
        D_800E1314 = 0;
    }
    if (D_800DFD94 & 8) {
        D_800E1318 = 0;
    }
    if (D_800DFD94 & 1) {
        D_800E131C = 0;
    }
    if (D_800DFD98 & 0x800) {
        D_800E1300 = 1;
    }
    if (D_800DFD98 & 0x400) {
        D_800E1304 = 1;
    }
    if (D_800DFD98 & 0x200) {
        D_800E1308 = 1;
    }
    if (D_800DFD98 & 0x100) {
        D_800E130C = 1;
    }
    if (D_800DFD98 & 2) {
        D_800E1310 = 1;
    }
    if (D_800DFD98 & 4) {
        D_800E1314 = 1;
    }
    if (D_800DFD98 & 8) {
        D_800E1318 = 1;
    }
    if (D_800DFD98 & 1) {
        D_800E131C = 1;
    }
    if (D_800E1300 != 0) {
        D_800E1300 += 1;
        if ((D_800E1300 >= 0xD) && !(D_800E1300 & 1)) {
            D_800DFD98 |= 0x800;
        }
    }
    if (D_800E1304 != 0) {
        D_800E1304 += 1;
        if ((D_800E1304 >= 0xD) && !(D_800E1304 & 1)) {
            D_800DFD98 |= 0x400;
        }
    }
    if (D_800E1308 != 0) {
        D_800E1308 += 1;
        if ((D_800E1308 >= 0xD) && !(D_800E1308 & 1)) {
            D_800DFD98 |= 0x200;
        }
    }
    if (D_800E130C != 0) {
        D_800E130C += 1;
        if ((D_800E130C >= 0xD) && !(D_800E130C & 1)) {
            D_800DFD98 |= 0x100;
        }
    }
    if (D_800E1310 != 0) {
        D_800E1310 += 1;
        if ((D_800E1310 >= 0xD) && !(D_800E1310 & 1)) {
            D_800DFD98 |= 2;
        }
    }
    if (D_800E1314 != 0) {
        D_800E1314 += 1;
        if ((D_800E1314 >= 0xD) && !(D_800E1314 & 1)) {
            D_800DFD98 |= 4;
        }
    }
    if (D_800E1318 != 0) {
        D_800E1318 += 1;
        if ((D_800E1318 >= 0xD) && !(D_800E1318 & 1)) {
            D_800DFD98 |= 8;
        }
    }
    if (D_800E131C != 0) {
        D_800E131C += 1;
        if ((D_800E131C >= 0xD) && !(D_800E131C & 1)) {
            D_800DFD98 |= 1;
        }
    }
    for (i = 0; i < 4; i++) {
        D_800DFDE4[i] = D_800DFDA4[i] ^ D_800DFDB4[i];
        D_800DFDC4[i] = D_800DFDA4[i] & D_800DFDE4[i];
        D_800DFDD4[i] = D_800DFDB4[i] & D_800DFDE4[i];
        if (D_800DFDC4[i] & 0x800) {
            D_800E1320[i] = 0;
        }
        if (D_800DFDC4[i] & 0x400) {
            D_800E1330[i] = 0;
        }
        if (D_800DFDC4[i] & 0x200) {
            D_800E1340[i] = 0;
        }
        if (D_800DFDC4[i] & 0x100) {
            D_800E1350[i] = 0;
        }
        if (D_800DFDC4[i] & 2) {
            D_800E1360[i] = 0;
        }
        if (D_800DFDC4[i] & 4) {
            D_800E1370[i] = 0;
        }
        if (D_800DFDC4[i] & 8) {
            D_800E1380[i] = 0;
        }
        if (D_800DFDC4[i] & 1) {
            D_800E1390[i] = 0;
        }
        if (D_800DFDD4[i] & 0x800) {
            D_800E1320[i] = 1;
        }
        if (D_800DFDD4[i] & 0x400) {
            D_800E1330[i] = 1;
        }
        if (D_800DFDD4[i] & 0x200) {
            D_800E1340[i] = 1;
        }
        if (D_800DFDD4[i] & 0x100) {
            D_800E1350[i] = 1;
        }
        if (D_800DFDD4[i] & 2) {
            D_800E1360[i] = 1;
        }
        if (D_800DFDD4[i] & 4) {
            D_800E1370[i] = 1;
        }
        if (D_800DFDD4[i] & 8) {
            D_800E1380[i] = 1;
        }
        if (D_800DFDD4[i] & 1) {
            D_800E1390[i] = 1;
        }
        if (D_800E1320[i] != 0) {
            D_800E1320[i] += 1;
            if ((D_800E1320[i] >= 0xD) && !(D_800E1320[i] & 1)) {
                D_800DFDD4[i] |= 0x800;
            }
        }
        if (D_800E1330[i] != 0) {
            D_800E1330[i] += 1;
            if ((D_800E1330[i] >= 0xD) && !(D_800E1330[i] & 1)) {
                D_800DFDD4[i] |= 0x400;
            }
        }
        if (D_800E1340[i] != 0) {
            D_800E1340[i] += 1;
            if ((D_800E1340[i] >= 0xD) && !(D_800E1340[i] & 1)) {
                D_800DFDD4[i] |= 0x200;
            }
        }
        if (D_800E1350[i] != 0) {
            D_800E1350[i] += 1;
            if ((D_800E1350[i] >= 0xD) && !(D_800E1350[i] & 1)) {
                D_800DFDD4[i] |= 0x100;
            }
        }
        if (D_800E1360[i] != 0) {
            D_800E1360[i] += 1;
            if ((D_800E1360[i] >= 0xD) && !(D_800E1360[i] & 1)) {
                D_800DFDD4[i] |= 2;
            }
        }
        if (D_800E1370[i] != 0) {
            D_800E1370[i] += 1;
            if ((D_800E1370[i] >= 0xD) && !(D_800E1370[i] & 1)) {
                D_800DFDD4[i] |= 4;
            }
        }
        if (D_800E1380[i] != 0) {
            D_800E1380[i] += 1;
            if ((D_800E1380[i] >= 0xD) && !(D_800E1380[i] & 1)) {
                D_800DFDD4[i] |= 8;
            }
        }
        if (D_800E1390[i] != 0) {
            D_800E1390[i] += 1;
            if ((D_800E1390[i] >= 0xD) && !(D_800E1390[i] & 1)) {
                D_800DFDD4[i] |= 1;
            }
        }
    }
    D_80102698 = (D_800E1208 & 0x10)
        ? (D_800E1202 * (D_800E1208 & 0x1E)) / 30
        : (D_800E1202 * (((0xF - D_800E1208) & 0xF) + 0xF)) / 30;
    if (D_800DFD98 & 0x200) {
        D_800E13B0 = 4;
    }
    if (D_800DFD98 & 0x100) {
        D_800E13B4 = 4;
    }
    if (D_800DFD98 & 0x800) {
        D_800E13B8 = 4;
    }
    if (D_800DFD98 & 0x400) {
        D_800E13BC = 4;
    }
    if (D_800E13B0 != 0) {
        D_800E13A0 = 0x8C;
        D_800E13B0 -= 1;
    } else {
        D_800E13A0 = 0xFF;
    }
    if (D_800E13B4 != 0) {
        D_800E13A4 = 0x8C;
        D_800E13B4 -= 1;
    } else {
        D_800E13A4 = 0xFF;
    }
    if (D_800E13B8 != 0) {
        D_800E13A8 = 0x8C;
        D_800E13B8 -= 1;
    } else {
        D_800E13A8 = 0xFF;
    }
    if (D_800E13BC != 0) {
        D_800E13AC = 0x8C;
        D_800E13BC -= 1;
    } else {
        D_800E13AC = 0xFF;
    }
    if (D_800DFD98 != 0) {
        D_800DFD48 = 0x1518;
    }
}



extern u16 *D_800DFF00;
extern void *D_801028C8;

void func_8003F8D8(void) {
    {
        gDPSetColorImage(
            D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, (u32) D_800DFF00
        );
    }
    {
        gSPTexture(
            D_800F22B4++, 0, 0, 0, G_TX_RENDERTILE, G_OFF
        );
    }
    {
        gDPSetCycleType(
            D_800F22B4++, G_CYC_FILL
        );
    }
    {
        gDPSetFillColor(
            D_800F22B4++, 0x00010001
        );
    }
    {
        gDPSetRenderMode(
            D_800F22B4++, G_RM_NOOP, G_RM_NOOP2
        );
    }
    {
        gDPFillRectangle(
            D_800F22B4++, 0, 0, 319, 239
        );
    }
    {
        gDPPipeSync(
            D_800F22B4++
        );
    }
    {
        gDPSetColorImage(
            D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, *(u32 *)((u8 *) D_801028C8 + 0x1910)
        );
    }
    {
        gDPSetCombineMode(
            D_800F22B4++, G_CC_SHADE, G_CC_SHADE
        );
    }
    {
        gDPSetCycleType(
            D_800F22B4++, G_CYC_1CYCLE
        );
    }

}


typedef struct {
    u8 unk0[0x1C];
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B[0x19];
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
} StructFEB0;


#define SB ((StructFEB0 *)&D_800DFEB0)

void func_8003FB04(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    SA->unkE = arg0;
    SA->unkF = arg1;
    SA->unk10 = arg2;
    SA->unk11 = 0xFF;
    SB->unk1C = arg3;
    SB->unk1D = arg4;
    SB->unk1E = arg5;
    SB->unk20 = arg6;
    SB->unk21 = arg7;
    SB->unk22 = arg8;
    SB->unk44 = arg3;
    SB->unk45 = arg4;
    SB->unk46 = arg5;
    SB->unk48 = arg6;
    SB->unk49 = arg7;
    SB->unk4A = arg8;
    SB->unk24 = arg3;
    SB->unk25 = arg4;
    SB->unk26 = arg5;
    SB->unk28 = arg6;
    SB->unk29 = arg7;
    SB->unk2A = arg8;
}


typedef struct {
    u8 pad00[0x1C];
    u8 unk1C[0x28];
    u8 unk44[0x10];
} UnkDFEB0;

extern u16 D_800DFF08;
extern u16 D_800DFF10;
extern s16 D_800E11FA;
extern s16 D_800E1202;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;

void capturePreviousFramebuffer(void);

void func_8003FC6C(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    capturePreviousFramebuffer();
    D_800DFF08 = 4;
    D_800DFF10 = 0;
    func_8003FB04(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[3] = 0x30;
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[7] = 0x30;
    ((UnkDFEB0 *)&D_800DFEB0)->unk44[3] = 0;
    ((UnkDFEB0 *)&D_800DFEB0)->unk44[7] = 0;
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[0xB] = 0;
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[0xF] = 0;
    D_800E1202 = 0;
    D_800E11FA = 0xFF;
    D_800E1206 = 0;
    D_800E1208 = 1;
    D_800E120C = 1;
}



void func_8003FD78(void) {
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[0] = ((UnkDFEB0 *)&D_800DFEB0)->unk44[0];
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[1] = ((UnkDFEB0 *)&D_800DFEB0)->unk44[1];
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[2] = ((UnkDFEB0 *)&D_800DFEB0)->unk44[2];
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[3] = 0;
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[4] = ((UnkDFEB0 *)&D_800DFEB0)->unk44[4];
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[5] = ((UnkDFEB0 *)&D_800DFEB0)->unk44[5];
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[6] = ((UnkDFEB0 *)&D_800DFEB0)->unk44[6];
    ((UnkDFEB0 *)&D_800DFEB0)->unk1C[7] = 0;
    D_800DFF08 = 5;
    D_800E1206 = D_800E1202;
    D_800E11FA = 0;
}


typedef struct {
    u16 unk0;
    u16 unk2;
} Img4127;

typedef struct {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ void *unkC;
    /* 0x010 */ void *unk10;
    /* 0x014 */ u8 pad14[0xC];
    /* 0x020 */ void *unk20;
    /* 0x024 */ void *unk24;
    /* 0x028 */ void *unk28;
    /* 0x02C */ void *unk2C;
    /* 0x030 */ void *unk30;
    /* 0x034 */ void *unk34;
    /* 0x038 */ void *unk38;
    /* 0x03C */ void *unk3C;
    /* 0x040 */ void *unk40;
    /* 0x044 */ void *unk44;
    /* 0x048 */ void *unk48;
    /* 0x04C */ void *unk4C;
    /* 0x050 */ void *unk50;
    /* 0x054 */ void *unk54;
    /* 0x058 */ void *unk58;
    /* 0x05C */ void *unk5C;
    /* 0x060 */ void *unk60;
    /* 0x064 */ void *unk64;
    /* 0x068 */ void *unk68;
    /* 0x06C */ void *unk6C;
    /* 0x070 */ void *unk70;
    /* 0x074 */ void *unk74;
    /* 0x078 */ void *unk78;
    /* 0x07C */ void *unk7C;
    /* 0x080 */ void *unk80;
    /* 0x084 */ Img4127 *unk84;
    /* 0x088 */ void *unk88;
    /* 0x08C */ u8 pad8C[0x170 - 0x8C];
    /* 0x170 */ u8 *unk170;
    /* 0x174 */ u8 pad174[0x194 - 0x174];
    /* 0x194 */ u8 *unk194;
    /* 0x198 */ u8 pad198[0x250 - 0x198];
    /* 0x250 */ s32 unk250;
} T1010;

#define MENU ((T1010 *)&D_800E1010)

extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern void func_8002A140(void);
extern u8 *loadAsset(u8 *, s32, s32);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern void func_800335F0(void *);
extern void func_800338B0(Gfx **);
extern void func_8003396C(Gfx **, UnkImg *, s32, s32, s32, s32, s32, s32);
extern void func_80038284(UnkImg *);
extern void func_80038478(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern s32 func_800388BC(u8 *);
extern void func_8003B1A4(void);
extern void func_8003F8D8(void);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8003FD78(void);
extern void updateAndDrawAudioMenu(void);
extern void updateAndDrawRecordsMenu(void);
extern s32 insertRankedRecord(u16, u8 *, u32, s32);
extern void func_80071DD8(s32);
extern void func_80074308(void);
extern void func_8007D45C(void *, void *, s32);
extern void func_800ADC98(u8 *);
extern void guScaleF(f32 (*)[4], f32, f32, f32);
extern void guTranslateF(f32 (*)[4], f32, f32, f32);

extern u8 D_736C50[];
extern s32 D_800DF710;
extern s32 D_800DF714;
extern u32 D_800DFDD4[];
extern s16 D_800DFE00;
extern UnkImg *D_800DFEFC;
extern u16 D_800DFF08;
extern s16 D_800E0754[];
extern s32 D_800E0760;
extern s16 D_800E076C;
extern u16 D_800E08D4[];
extern u16 D_800E08F4[];
extern f32 D_800E0D28[];
extern f32 D_800E0D44[];
extern f32 D_800E0D60[];
extern f32 D_800E0D7C[];
extern f32 D_800E0D98[];
extern f32 D_800E0DB4[];
extern f32 D_800E0DD0[];
extern f32 D_800E0DEC[];
extern f32 D_800E0E08[];
extern u8 *D_800E1010;
extern void *D_800E1014;
extern void *D_800E10B0;
extern u8 *D_800E1134[];
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s16 D_800E121C;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E1224;
extern s16 D_800E1228;
extern s16 D_800E122A;
extern s16 D_800E122C;
extern s16 D_800E1240;
extern s32 D_800E1258;
extern s32 D_800E1260;
extern Obj *D_800E1264;
extern Obj *D_800E1268;
extern Obj *D_800E1278;
extern u8 D_800E2818[];
extern s16 D_800E44A0;
extern s16 D_800E44A8;
extern u8 D_800E44FC;
extern u16 D_800ECBEC;
extern u8 D_800ECBF0[];
extern u8 D_800ECBF8[];
extern u8 D_800ECC00[];
extern u8 D_800ECC08[];
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern u8 D_80102698;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern f32 D_80102B28[16];
extern f32 D_80102B68[16];
extern s32 D_80102C84;
extern s16 D_801033A2;
extern s16 D_801033AC;
extern s32 D_80103958;
extern s32 D_8010395C;
extern s32 D_80103960;
extern u8 D_8010B358[];
extern u8 D_80110220[];
extern s16 D_801125F6;
extern s16 D_801126DA;
extern s32 D_80112D18;
extern s8 D_80113321;
extern s8 D_80113322;
extern s32 D_80113328;
extern s16 D_80113454;
extern s8 D_8011658A;
extern s32 D_8013D25C;
extern s16 D_8013FAD2;
extern s16 D_8013FAD4;
extern s16 D_8013FAD8;
extern s16 D_8015D980;


void updateAndDrawPauseMenu(void) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    u16 pad42;
    u16 sp40;
    sp40 = D_800ECBEC;
    if (D_800E122C >= 0) {
        updateAndDrawRecordsMenu();
        if (D_800E122C < 0) {
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1228 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        return;
    }
    if (D_800E122A >= 0) {
        updateAndDrawAudioMenu();
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E1014 = loadAsset(D_736C50, 0xC2, 8);
        func_80038284(D_800E1014);
        MENU->unkC = loadAsset(D_736C50, 0x19, 8);
        MENU->unk10 = loadAsset(D_736C50, 0x47, 8);
        D_800E10B0 = loadAsset(D_736C50, 0x24, 8);
        D_800E11FC = 0;
        D_800E1258 = loadAnim(0x101);
        D_800E1260 = loadMesh(0x6A);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1268->unk28 = 1.0f;
        D_800E1268->unk2C = -0.08f;
        D_800E1268->unk48 = 0;
        D_800E1258 = loadAnim(D_800E08F4[D_80113322]);
        D_800E1260 = loadMesh(D_800E08D4[D_80113322]);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1264->unk28 = 1.0f;
        D_800E1264->unk2C = -0.08f;
        if (D_8015D980 == 2) {
            D_800E1258 = loadAnim(D_800E08F4[((D_800E44A8 == 6) && (D_800E44A0 >= 3)) ? 7 : D_8011658A]);
            D_800E1260 = loadMesh(D_800E08D4[((D_800E44A8 == 6) && (D_800E44A0 >= 3)) ? 7 : D_8011658A]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1278 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            D_800E1278->unk28 = 1.0f;
            D_800E1278->unk2C = -0.08f;
        }
        D_800E1240 = 0x14;
        func_8003FC6C(0x58, 0x32, 0x40, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
        D_80102C84 = (D_800E44A8 != 5) || (D_8013D25C == 0) || (D_800E44FC != 0);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    SA->unkE = (sins((D_800E1208 * 0x39) + 0x31FE) / 1524) + 0x32;
    SA->unkF = (sins((D_800E1208 * 0x1F) - 0x5D59) / 1524) + 0x3C;
    SA->unk10 = (sins(D_800E1208 * 0xA) / 1524) + 0x46;
    func_8003B1A4();
    if (D_800DFF08 == 0) {
        if (D_800E1228 == 3) {
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        if ((D_800E1228 == 2) && (D_800E11FC != 0)) {
            if (D_800E44A8 == 3) {
                D_800E076C = 1;
                D_8013FAD2 = 1;
                D_801125F6 = 1;
                if (D_8013FAD8 != 0) {
                    D_8013FAD4 = 1;
                }
                D_800E1228 = -1;
                D_800E1208 = 0;
                D_800E120C = 0;
            } else {
                D_800E122A = D_800E1228;
                D_800E1228 = 0;
                D_800E1208 = 0;
                D_800E120C = 0;
            }
        } else {
            D_800E1228 = -1;
        }
        return;
    }
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, NULL, NULL) != 0) {
        D_800E1268->unk24 = 0;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, D_800E10B0, 0, 0x55, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unkC, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unk10, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
    sp44 = 0;
    for (sp4C = 0; sp4C < 4; sp4C++) {
        if ((sp4C == 1) && (D_80102C84 != 0)) {
            sp4C += 1;
        }
        sp48 = D_800E1202;
        if (D_800E1228 == sp4C) {
            if ((D_800E44A8 == 3) && (sp4C == 2)) {
                func_80038478(&D_800F22B4, (-(sp44 * 6) - func_800388BC(D_800ECBF0)) + 0x72, (sp44 * 0x12) + 0x5E, D_800ECBF8, 0xFF, 0xFF, 0xFF, D_80102698);
            } else {
                func_80038478(&D_800F22B4, (-(sp44 * 6) - func_800388BC(D_800E1134[sp4C])) + 0x72, (sp44 * 0x12) + 0x5E, D_800E1134[sp4C], 0xFF, 0xFF, 0xFF, D_80102698);
            }
        } else if ((D_800E44A8 == 3) && (sp4C == 2)) {
            func_80038478(&D_800F22B4, (-(sp44 * 6) - func_800388BC(D_800ECC00)) + 0x72, (sp44 * 0x12) + 0x5E, D_800ECC08, 0xE6, 0x61, 0x1E, sp48);
        } else {
            func_80038478(&D_800F22B4, (-(sp44 * 6) - func_800388BC(D_800E1134[sp4C])) + 0x72, (sp44 * 0x12) + 0x5E, D_800E1134[sp4C], 0xE6, 0x61, 0x1E, sp48);
        }
        sp44 += 1;
    }
    func_800338B0(&D_800F22B4);
    if (D_8015D980 == 1) {
        guTranslateF(D_80102B28, D_800E0D28[D_80113322], D_800E0D44[D_80113322], 0);
        guScaleF(D_80102B68, D_800E0D60[D_80113322], D_800E0D60[D_80113322], D_800E0D60[D_80113322]);
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, D_80102B68, D_80102B28) != 0) {
            D_800E1264->unk24 = 0;
        }
    } else if (D_8015D980 == 2) {
        guTranslateF(D_80102B28, D_800E0D7C[D_80113322], D_800E0D98[D_80113322], 0);
        guScaleF(D_80102B68, D_800E0DB4[D_80113322], D_800E0DB4[D_80113322], D_800E0DB4[D_80113322]);
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, D_80102B68, D_80102B28) != 0) {
            D_800E1264->unk24 = 0;
        }
        guTranslateF(D_80102B28, D_800E0DD0[D_8011658A], D_800E0DEC[D_8011658A], 0);
        guScaleF(D_80102B68, D_800E0E08[D_8011658A], D_800E0E08[D_8011658A], D_800E0E08[D_8011658A]);
        if (LWPlayAnimation(D_800E1278, (D_800E1208 - D_800E1210) + D_800E1240, D_80102B68, D_80102B28) != 0) {
            D_800E1278->unk24 = 0;
        }
        D_800E1240 = 0;
    }
    if ((D_800DFDD4[D_800DFE00] & 0x400) && (D_800DFF08 != 5)) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1228 < 3) {
            D_800E1228 += 1;
        } else {
            D_800E1228 = 0;
        }
        if ((D_800E1228 == 1) && (D_80102C84 != 0)) {
            D_800E1228 += 1;
        }
    }
    if ((D_800DFDD4[D_800DFE00] & 0x800) && (D_800DFF08 != 5)) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1228 > 0) {
            D_800E1228 -= 1;
        } else {
            D_800E1228 = 3;
        }
        if ((D_800E1228 == 1) && (D_80102C84 != 0)) {
            D_800E1228 -= 1;
        }
    }
    if ((D_800DFDD4[D_800DFE00] & 0xB000) && (D_800DFF08 != 5)) {
        func_8007D45C(D_8010B358, D_800E2818, 3);
        if ((D_800E1228 == 3) && (D_8015D980 == 1)) {
            switch (D_800E44A8) {
            case 5:
                if (insertRankedRecord(5, D_80113328, D_80112D18, D_80113321) != 0) {
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E122C = 1;
                    D_800E0760 = 0x4B0;
                    return;
                }
                break;
            case 1:
                if (insertRankedRecord(1, D_80113328, D_80112D18, D_80113321) != 0) {
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E122C = 0;
                    D_800E0760 = 0x4B0;
                    return;
                }
                break;
            case 2:
                if (insertRankedRecord(2, D_80113328, D_80112D18, D_80113321) != 0) {
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E122C = 3;
                    D_800E0760 = 0x4B0;
                    return;
                }
                break;
            }
        }
        D_800E1264->unk2C = 0.08f;
        D_800E1268->unk2C = 0.08f;
        if (D_8015D980 == 2) {
            D_800E1278->unk2C = 0.08f;
        }
        func_8003FD78();
        if ((D_800E1228 == 3) || ((D_800E1228 == 2) && (D_800E44A8 == 3))) {
            func_8003F8D8();
        }
        if (D_800E1228 == 1) {
            D_801033A2 = 0xFF;
            D_801033AC = 1;
            D_800E44FC = 1;
            D_80103958 = D_8013D25C;
            func_80074308();
            D_8010395C = 0;
            D_80103960 = 0;
            func_80071DD8(0);
            func_800ADC98(D_80110220);
            D_801126DA = 1;
            D_80113454 = 1;
        }
        D_800E11FC = 1;
    }
    if ((D_800DFDD4[D_800DFE00] & 0x4000) && (D_800DFF08 != 5)) {
        func_8007D45C(D_8010B358, D_800E2818, 4);
        D_800E1264->unk2C = 0.08f;
        D_800E1268->unk2C = 0.08f;
        if (D_8015D980 == 2) {
            D_800E1278->unk2C = 0.08f;
        }
        func_8003FD78();
        D_800E11FC = 0;
        D_800E1228 = 0;
    }
}


extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern void func_8002A140(void);
extern u8 *loadAsset(u8 *, s32, s32);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern void func_800335F0(void *);
extern void func_800338B0(Gfx **);
extern void func_8003396C(Gfx **, UnkImg *, s32, s32, s32, s32, s32, s32);
extern void func_800353F4(Gfx **, UnkImg *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80038478(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern s32 func_800388BC(u8 *);
extern void func_80038A88(void);
extern void func_8003B1A4(void);
extern void func_8003F8D8(void);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8003FD78(void);
extern void func_80050BFC(void);
extern void func_8005EE48(void);
extern void func_8006224C(void);
extern void func_80065660(void);
extern void func_800656C8(void);
extern void func_80065D74(void);
extern s32 func_80066854(void);
extern s32 func_80066CE8(void);
extern void func_8007ACFC(u8 *);
extern void func_8007D45C(void *, void *, s32);
extern void loadsong(s32, u8 *);
extern void func_800905A4(u8 *, s32);
extern void func_800CC6E0(void);
extern void guMtxCatF(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void guRotateRPYF_2(f32 (*)[4], f32, f32, f32);
extern void guScaleF(f32 (*)[4], f32, f32, f32);
extern void guTranslateF(f32 (*)[4], f32, f32, f32);

extern u8 D_736C50[];
extern s32 D_800DF710;
extern s32 D_800DF714;
extern s16 D_800DFD4C;
extern s16 D_800DFD50;
extern s16 D_800DFD54;
extern u32 D_800DFDA4[];
extern u32 D_800DFDB4[];
extern u32 D_800DFDD4[];
extern s16 D_800DFE80;
extern s32 D_800DFE84;
extern u16 D_800DFF08;
extern s16 D_800E0754[];
extern u8 D_800E0784[8][9];
extern s8 D_800E07CC[8];
extern u8 D_800E07D4[];
extern s8 D_800E07E4[];
extern s32 D_800E088C;
extern s16 D_800E08A8;
extern s16 D_800E08AC;
extern s16 D_800E08B0;
extern u16 D_800E08D4[];
extern u16 D_800E08F4[];
extern u16 D_800E0904[];
extern s32 D_800E0B20;
extern s32 D_800E0B24;
extern f32 D_800E0C80[];
extern f32 D_800E0C9C[];
extern f32 D_800E0CB8[];
extern f32 D_800E0CD4[];
extern f32 D_800E0CF0[];
extern f32 D_800E0D0C[];
extern u8 *D_800E1010;
extern s32 D_800E1018;
extern void *D_800E1028;
extern void *D_800E102C;
extern void *D_800E1030[];
extern void *D_800E1058[];
extern void *D_800E1074[];
extern void *D_800E10AC;
extern void *D_800E10CC[];
extern u8 *D_800E1160[];
extern u8 *D_800E11D8[];
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s16 D_800E121C;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E1224;
#define CURSOR D_800E1224
extern s16 D_800E122A;
extern s16 D_800E122E;
extern s16 D_800E1230;
extern s16 D_800E1232;
extern s16 D_800E1234;
extern s16 D_800E123E;
extern s16 D_800E1240;
extern s16 D_800E1242;
extern s32 D_800E1254;
extern s32 D_800E1258;
extern s32 D_800E125C;
extern s32 D_800E1260;
extern Obj *D_800E1264;
extern Obj *D_800E1268;
extern u8 *D_800E12D8;
extern s16 D_800E12DC;
extern u8 *D_800E12E0;
extern s16 D_800E12E4;
extern u8 *D_800E12E8;
extern s16 D_800E12EC;
extern u8 *D_800E12F0;
extern s16 D_800E12F4;
extern u8 *D_800E12F8;
extern s32 D_800E13C0;
extern s16 D_800E13C4;
extern u8 D_800E13C8[];
extern u8 D_800E2818[];
extern s16 D_800E28E4;
extern s16 D_800E4498;
extern s16 D_800E449C;
extern s16 D_800E44A0;
extern s16 D_800E44A4;
extern s16 D_800E44A8;
extern u16 D_800E94B0;
extern u8 D_800ECC10[];
extern u8 D_800ECC14[];
extern u8 D_800ECC24[];
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern s16 D_80102666;
extern u8 D_80102698;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern f32 D_80102B28[16];
extern f32 D_80102B68[16];
extern f32 D_80102BB0[16];
extern f32 D_80102CF0;
extern f32 D_80102CF4;
extern f32 D_80102CF8;
extern f32 D_80102CFC;
extern u8 D_80107290[];
extern u8 D_8010B358[];
extern u8 D_80110220[];
extern s16 D_801125C6;
extern s16 D_801125F6;
extern s16 D_8011268A;
extern s16 D_8011268C;
extern s32 D_80112D18;
extern s8 D_80113320;
extern s8 D_80113322;
extern s8 D_80113323;
extern s32 D_80113328;
extern s16 D_8011585E;
extern s16 D_8015D980;

void func_8004127C(void) {
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    u8 sp4C[10];
    u8 *sp48;

    if (D_800E1234 >= 0) {
        func_8006224C();
        return;
    }
    if (D_800E122A >= 0) {
        func_80050BFC();
        return;
    }
    if (D_800E1232 >= 0) {
        func_8005EE48();
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        MENU->unk170[2] = 0x2F;
        MENU->unk194[2] = 0x2F;
        MENU->unkC = loadAsset(D_736C50, 0x19, 8);
        MENU->unk10 = loadAsset(D_736C50, 0x47, 8);
        D_800E1028 = loadAsset(D_736C50, 0x1A, 8);
        D_800E102C = loadAsset(D_736C50, 0x1B, 8);
        D_800E1018 = loadAsset(D_736C50, 0x3A, 8);
        MENU->unk20 = loadAsset(D_736C50, 0x1C, 8);
        MENU->unk24 = loadAsset(D_736C50, 0x1D, 8);
        MENU->unk28 = loadAsset(D_736C50, 0x77, 8);
        MENU->unk2C = loadAsset(D_736C50, 0x1F, 8);
        MENU->unk30 = loadAsset(D_736C50, 0x20, 8);
        MENU->unk34 = loadAsset(D_736C50, 0x21, 8);
        MENU->unk38 = loadAsset(D_736C50, 0x22, 8);
        MENU->unk3C = loadAsset(D_736C50, 0x11F, 8);
        MENU->unk40 = loadAsset(D_736C50, 0x120, 8);
        MENU->unk44 = loadAsset(D_736C50, 0x4A, 8);
        MENU->unk48 = loadAsset(D_736C50, 0x118, 8);
        MENU->unk4C = loadAsset(D_736C50, 0x119, 8);
        MENU->unk50 = loadAsset(D_736C50, 0x11A, 8);
        MENU->unk54 = loadAsset(D_736C50, 0x11B, 8);
        MENU->unk58 = loadAsset(D_736C50, 0x11C, 8);
        MENU->unk5C = loadAsset(D_736C50, 0x11D, 8);
        MENU->unk60 = loadAsset(D_736C50, 0x11E, 8);
        MENU->unk64 = loadAsset(D_736C50, 0x122, 8);
        MENU->unk68 = loadAsset(D_736C50, 0x123, 8);
        MENU->unk6C = loadAsset(D_736C50, 0x124, 8);
        MENU->unk70 = loadAsset(D_736C50, 0x125, 8);
        MENU->unk74 = loadAsset(D_736C50, 0x126, 8);
        MENU->unk78 = loadAsset(D_736C50, 0x127, 8);
        MENU->unk7C = loadAsset(D_736C50, 0x128, 8);
        MENU->unk80 = loadAsset(D_736C50, 0x78, 8);
        MENU->unk84 = loadAsset(D_736C50, 0x129, 8);
        MENU->unk88 = loadAsset(D_736C50, 0x110, 8);
        D_800E10AC = loadAsset(D_736C50, 0x73, 8);
        if (D_800E0B20 != 2) {
            loadsong(D_800E94B0, D_80107290);
        } else {
            loadsong(D_800E0B24, D_80107290);
        }
        func_8007ACFC(D_80107290);
        D_800E1222 = 0;
        D_800E1254 = D_800F22C0;
        D_800E1242 = -1;
        D_800E1264 = NULL;
        D_800E1268 = NULL;
        D_800E11FC = 0;
        D_800E1224 = -1;
        D_800E123E = D_800E07D4[0];
        D_800E1240 = -1;
        D_80102CF0 = 0.0f;
        D_80102CF4 = 0.0f;
        D_80102CF8 = 0.0f;
        D_80102CFC = 0.0f;
        func_800656C8();
        if (((u8 *)D_800E0784)[0] == 0) {
            ((u8 *)D_800E0784)[0] = 'P';
            ((u8 *)D_800E0784)[1] = 'L';
            ((u8 *)D_800E0784)[2] = 'A';
            ((u8 *)D_800E0784)[3] = 'Y';
            ((u8 *)D_800E0784)[4] = 'E';
            ((u8 *)D_800E0784)[5] = 'R';
            ((u8 *)D_800E0784)[6] = ' ';
            ((u8 *)D_800E0784)[7] = '1';
            ((u8 *)D_800E0784)[8] = 0;
            D_80113328 = ((u8 *)D_800E0784);
        }
        func_80066854();
        for (sp70 = 0; sp70 < 9; sp70++) {
            D_800E13C8[sp70] = ((u8 *)D_800E0784)[sp70];
            ((u8 *)D_800E0784)[sp70] = 0;
        }
        D_800E13C0 = 0;
        func_8003FC6C(0x5A, 0x28, 0x3C, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if (D_80102CF0 < D_80102CF4) {
        for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
            D_80102CF0 += 0.05;
        }
        if (D_80102CF0 > D_80102CF4) {
            D_80102CF0 = D_80102CF4;
        }
    }
    if (D_80102CF0 > D_80102CF4) {
        for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
            D_80102CF0 -= 0.05;
        }
        if (D_80102CF0 < D_80102CF4) {
            D_80102CF0 = D_80102CF4;
        }
    }
    if (((D_800E1222 != 3) || (CURSOR < 0)) && (D_80102CF8 > 0.0)) {
        for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
            D_80102CF8 -= 5.0;
        }
        if (D_80102CF8 < 0.0) {
            D_80102CF8 = 0.0f;
        }
    }
    if (((D_800E1222 != 3) || (CURSOR < 0)) && (D_80102CFC > 0.0)) {
        for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
            D_80102CFC -= 5.0;
        }
        if (D_80102CFC < 0.0) {
            D_80102CFC = 0.0f;
        }
    }
    if (((D_800E1222 != 3) || (CURSOR < 0)) && (D_80102CF8 < 0.0)) {
        for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
            D_80102CF8 += 5.0;
        }
        if (D_80102CF8 > 0.0) {
            D_80102CF8 = 0.0f;
        }
    }
    if (((D_800E1222 != 3) || (CURSOR < 0)) && (D_80102CFC < 0.0)) {
        for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
            D_80102CFC += 5.0;
        }
        if (D_80102CFC > 0.0) {
            D_80102CFC = 0.0f;
        }
    }
    if (D_800E11FC == 3) {
        D_800E11FC = 4;
        func_8003FD78();
        func_8003F8D8();
    }
    sp4C[1] = 0;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        for (sp70 = 0; sp70 < 9; sp70++) {
            ((u8 *)D_800E0784)[sp70] = D_800E13C8[sp70];
        }
        func_80065660();
        if (D_800E11FC != 0) {
            if (D_800E44A8 == 6) {
                D_800E4498 = 0;
                D_800E449C = 0;
            }
            D_801125C6 = 1;
            func_800CC6E0();
            D_80112D18 = 0;
            if (D_800E44A8 == 5) {
                for (sp70 = 0; sp70 < 9; sp70++) {
                    ((u8 *)D_800E0784)[sp70] = D_800E13C8[sp70];
                }
                D_800E1234 = 0;
            } else {
                D_800E121C = -1;
                D_800E1220 = -1;
                D_800E1222 = -1;
                D_800E1224 = -1;
            }
            D_800E1208 = 0;
            D_800E120C = 0;
        } else {
            D_800E1208 = 0;
            D_800E120C = 0;
            if (D_800E12EC != 0) {
                D_800E122E = 0;
                D_800E12EC = 0;
            } else {
                D_800E1222 = -1;
            }
        }
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    if (D_800E1240 >= 0) {
        sp58 = 0x40;
    } else if ((D_800E1222 == 3) && (CURSOR >= 0)) {
        sp58 = 0;
    } else {
        sp58 = 0x100;
    }
    if (D_800E13C4 > sp58) {
        for (sp70 = D_800E1210; sp70 < D_800E1208; sp70++) {
            D_800E13C4 -= 0x10;
        }
        if (D_800E13C4 < sp58) {
            D_800E13C4 = sp58;
        }
    }
    if (D_800E13C4 < sp58) {
        for (sp70 = D_800E1210; sp70 < D_800E1208; sp70++) {
            D_800E13C4 += 0x10;
        }
        if (D_800E13C4 > sp58) {
            D_800E13C4 = sp58;
        }
    }
    func_800335F0(&D_800F22B4);
    if (D_800E1240 < 0) {
        func_8003396C(&D_800F22B4, MENU->unkC, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
        func_8003396C(&D_800F22B4, MENU->unk10, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
    }
    func_8003396C(&D_800F22B4, D_800E102C, 0x16, 0x16, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E13C4) >> 8);
    func_8003396C(&D_800F22B4, D_800E1028, 0x19, 0x1C, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E13C4) >> 8);
    for (sp70 = 0; sp70 < 4; sp70++) {
        if (D_800E1222 == sp70) {
            sp60 = D_800E1202;
        } else {
            sp60 = (D_800E1202 * 0x8C) / 255;
        }
        sp6C = (D_800E1222 == sp70)
            ? ((CURSOR < 0)
                ? ((D_800E1208 & 0x10)
                    ? (D_800E1202 * (D_800E1208 & 0x1E)) / 30
                    : (D_800E1202 * (((0xF - D_800E1208) & 0xF) + 0xF)) / 30)
                : sp60)
            : sp60;
        sp60 = (D_800E13C4 * sp60) >> 8;
        sp6C = (D_800E13C4 * sp6C) >> 8;
        switch (sp70) {
        case 0:
            if (D_800E1222 == sp70) {
                func_8003396C(&D_800F22B4, D_800E1018, 0x94, 0x20, 0xFF, 0xFF, 0xFF, sp6C);
            } else {
                func_8003396C(&D_800F22B4, D_800E1018, 0x94, 0x20, 0xFF, 0xDC, 0x3E, sp60);
            }
            func_80038478(&D_800F22B4, 0xB7 - func_800388BC(D_800E13C8), 0x2D, D_800E13C8, 0xE6, 0x61, 0x1E, sp60);
            break;
        case 2:
            if (D_800E1222 == sp70) {
                func_8003396C(&D_800F22B4, MENU->unk40, 0x66, 0x52, 0xFF, 0xFF, 0xFF, sp6C);
            } else {
                func_8003396C(&D_800F22B4, MENU->unk40, 0x66, 0x52, 0xFF, 0xDC, 0x3E, sp60);
            }
            if ((CURSOR < 0x40) && (CURSOR >= 0) && (D_800E1222 == 2)) {
                if (((u8 *)D_800E0784)[6] == 0) {
                    sp4C[0] = D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7];
                    sp4C[1] = 0;
                    func_80038478(&D_800F22B4, 0xAA - func_800388BC(sp4C), 0x60, sp4C, 0xFF, 0xFF, 0xFF, sp60);
                } else {
                    sp4C[0] = 0;
                }
                func_80038478(&D_800F22B4, 0xAA - func_800388BC(((u8 *)D_800E0784)) - func_800388BC(sp4C), 0x60, ((u8 *)D_800E0784), 0xE6, 0x61, 0x1E, sp60);
            } else if ((D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7] == 0x29) && (((u8 *)D_800E0784)[0] != 0) && (D_800E1222 == 2)) {
                sp48 = ((u8 *)D_800E0784);
                while (*sp48 != 0) {
                    sp48++;
                }
                sp48--;
                sp6C = func_800388BC(((u8 *)D_800E0784));
                sp4C[0] = *sp48;
                sp4C[1] = 0;
                *sp48 = 0;
                func_80038478(&D_800F22B4, 0xAA - sp6C, 0x60, ((u8 *)D_800E0784), 0xE6, 0x61, 0x1E, sp60);
                if (D_800E1208 & 0x10) {
                    func_80038478(&D_800F22B4, 0xAA - func_800388BC(sp4C), 0x60, sp4C, 0xE6, 0x61, 0x1E, (s32)((u32)sp60 * (u32)(D_800E1208 & 0x1E)) / 30);
                } else {
                    func_80038478(&D_800F22B4, 0xAA - func_800388BC(sp4C), 0x60, sp4C, 0xE6, 0x61, 0x1E, (s32)((u32)sp60 * (u32)(((0xF - D_800E1208) & 0xF) + 0xF)) / 30);
                }
                *sp48 = sp4C[0];
            } else {
                func_80038478(&D_800F22B4, 0xAA - func_800388BC(((u8 *)D_800E0784)), 0x60, ((u8 *)D_800E0784), 0xE6, 0x61, 0x1E, sp60);
            }
            break;
        case 3:
            if (D_800E1222 == sp70) {
                func_8003396C(&D_800F22B4, MENU->unk44, 0x8A, 0x74, 0xFF, 0xFF, 0xFF, sp6C);
            } else {
                func_8003396C(&D_800F22B4, MENU->unk44, 0x8A, 0x74, 0xFF, 0xDC, 0x3E, sp60);
            }
            if ((D_800E1222 != 3) || (CURSOR < 0)) {
                D_800E123E = D_800E07D4[0];
            } else {
                D_800E123E = CURSOR;
            }
            break;
        case 1:
            if (D_800E1222 == sp70) {
                func_8003396C(&D_800F22B4, MENU->unk3C, 0x6C, 0x3F, 0xFF, 0xFF, 0xFF, sp6C);
            } else {
                func_8003396C(&D_800F22B4, MENU->unk3C, 0x6C, 0x3F, 0xFF, 0xDC, 0x3E, sp60);
            }
            break;
        }
    }
    if (CURSOR >= 0) {
        sp60 = D_800E1202;
    } else {
        sp60 = (D_800E1202 * 0x8C) / 255;
    }
    switch (D_800E1222) {
    case 2:
        for (sp70 = 0; sp70 < 9; sp70++) {
            sp4C[0] = 0;
            sp48 = D_800E1160[sp70 + D_800E13C0];
            sp74 = 0;
            while (*sp48 != 0) {
                sp48++;
                sp74++;
            }
            sp48 = D_800E1160[sp70 + D_800E13C0];
            sp6C = 0;
            while (*sp48 != 0) {
                sp4C[0] = *sp48;
                if (((CURSOR >> 3) == sp70) && ((CURSOR & 7) == sp6C)) {
                    func_80038478(&D_800F22B4, 0x12E - (sp70 * 6) - (sp74 * 0xE) - (func_800388BC(sp4C) >> 1), (sp70 * 0x12) + 0x25, sp4C, 0xFF, 0xFF, 0xFF, D_80102698);
                } else {
                    func_80038478(&D_800F22B4, 0x12E - (sp70 * 6) - (sp74 * 0xE) - (func_800388BC(sp4C) >> 1), (sp70 * 0x12) + 0x25, sp4C, 0xE6, 0x61, 0x1E, sp60);
                }
                sp48++;
                sp74--;
                sp6C++;
            }
        }
        break;
    case 3:
        if ((D_800E1240 >= 0) || (CURSOR < 0)) {
            sp6C = sp60;
        } else {
            sp6C = D_800E1202;
        }
        for (sp74 = 0; sp74 < 7; sp74++) {
            if ((CURSOR == sp74) || ((CURSOR < 0) && (D_800E07D4[0] == sp74))) {
                if ((D_800E1240 >= 0) || (CURSOR < 0)) {
                    func_8003396C(&D_800F22B4, D_800E1030[sp74], (((sp74 + 1) / 3) * 0x40) - (sp74 * 0x1B) + 0xEA, (sp74 * 0x20) - (((sp74 + 1) / 3) * 0x20) + 0x28, 0xFF, 0xFF, 0xFF, sp6C);
                } else {
                    func_8003396C(&D_800F22B4, D_800E1030[sp74], (((sp74 + 1) / 3) * 0x40) - (sp74 * 0x1B) + 0xEA, (sp74 * 0x20) - (((sp74 + 1) / 3) * 0x20) + 0x28, 0xFF, 0xFF, 0xFF, D_80102698);
                }
            } else {
                func_8003396C(&D_800F22B4, D_800E1030[sp74], (((sp74 + 1) / 3) * 0x40) - (sp74 * 0x1B) + 0xEA, (sp74 * 0x20) - (((sp74 + 1) / 3) * 0x20) + 0x28, 0xE6, 0x61, 0x1E, sp6C);
            }
        }
        break;
    case 0:
        for (sp74 = 0; sp74 < D_800E12E4 + 5; sp74++) {
            if (CURSOR == sp74) {
                func_80038478(&D_800F22B4, 0x124 - (sp74 * 6) - func_800388BC(D_800E10CC[sp74]), (sp74 * 0x12) + 0x46, D_800E10CC[sp74], 0xFF, 0xFF, 0xFF, (D_80102698 * D_800E13C4) >> 8);
            } else {
                func_80038478(&D_800F22B4, 0x124 - (sp74 * 6) - func_800388BC(D_800E10CC[sp74]), (sp74 * 0x12) + 0x46, D_800E10CC[sp74], 0xE6, 0x61, 0x1E, (D_800E13C4 * sp60) >> 8);
            }
        }
        break;
    }
    if (D_800E07E4[0] != 0) {
        func_80038478(&D_800F22B4, 0x50, 0x40, D_800ECC10, 0xFF, 0xDC, 0x3E, (D_800E1202 * D_800E13C4) >> 8);
    }
    if ((D_800E1222 == 3) && (CURSOR >= 0)) {
        func_8003396C(&D_800F22B4, D_800E1074[CURSOR], 0x21, 0xC, 0xFF, 0xFF, 0xFF, sp6C);
        func_8003396C(&D_800F22B4, D_800E1058[CURSOR], 0x21, 0xC, 0xFF, 0xFF, 0xFF, sp6C);
    }
    func_800338B0(&D_800F22B4);
    if (D_800E123E != D_800E1242) {
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800F22C0 = D_800E1254;
        D_800DFE84 = 1;
        D_800E1258 = loadAnim(D_800E08F4[D_800E123E]);
        D_800E125C = loadAnim(D_800E0904[D_800E123E]);
        D_800E1260 = loadMesh(D_800E08D4[D_800E123E]);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E125C, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if (D_800E1242 < 0) {
            D_800E1264->unk28 = 1.0f;
            D_800E1264->unk2C = -0.08f;
        }
        D_800DFE84 = 0;
        D_800E1242 = D_800E123E;
    }
    if ((D_800E1264 != NULL) && (D_800E11FC < 3)) {
        guTranslateF(D_80102B28,
                     D_800E0C80[D_800E123E] * (1.0 - D_80102CF0) + D_800E0CD4[D_800E123E] * D_80102CF0,
                     D_800E0C9C[D_800E123E] * (1.0 - D_80102CF0) + D_800E0CF0[D_800E123E] * D_80102CF0,
                     0.0f);
        guScaleF(D_80102B68,
                 D_800E0CB8[D_800E123E] * (1.0 - D_80102CF0) + D_800E0D0C[D_800E123E] * D_80102CF0,
                 D_800E0CB8[D_800E123E] * (1.0 - D_80102CF0) + D_800E0D0C[D_800E123E] * D_80102CF0,
                 D_800E0CB8[D_800E123E] * (1.0 - D_80102CF0) + D_800E0D0C[D_800E123E] * D_80102CF0);
        guRotateRPYF_2(D_80102BB0, D_80102CFC, D_80102CF8, 0.0f);
        guMtxCatF(D_80102B68, D_80102BB0, D_80102B68);
        if (D_800E11FC == 2) {
            if ((D_800DFDD4[D_800E07CC[0]] & 0xB000) && (D_800E11FA != 0)) {
                D_800E1268->unk2C = 0.08f;
                func_8007D45C(D_8010B358, D_800E2818, 4);
                func_8003FD78();
                func_8003F8D8();
            }
            if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, D_80102B68, D_80102B28) != 0) {
                D_800E11FC = 3;
            }
        } else if (D_800E11FC != 0) {
            if (LWPlayAnimation(D_800E1264, (D_800E1208 - D_800E1210) * 4, D_80102B68, D_80102B28) != 0) {
                D_800E11FC = 2;
                switch (D_800E07D4[0]) {
                case 5:
                    func_8007D45C(D_8010B358, D_800E2818, 7);
                    break;
                default:
                    func_8007D45C(D_8010B358, D_800E2818, 6);
                    break;
                }
            }
        } else if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, D_80102B68, D_80102B28) != 0) {
            D_800E1264->unk24 = 0;
        }
    }
    if ((D_800E1222 == 3) && (CURSOR >= 0)) {
        func_800905A4(D_80110220, CURSOR);
        func_800335F0(&D_800F22B4);
        func_8003396C(&D_800F22B4, MENU->unk80, 0x35, 0xBC, 0xFF, 0xFF, 0xFF, sp6C);
        func_8003396C(&D_800F22B4, MENU->unk88, 0x35, 0xBC, 0xFF, 0xFF, 0xFF, sp6C);
        func_800353F4(&D_800F22B4, MENU->unk84, 0, 0, ((MENU->unk84->unk0 - 1) * (0xF - D_8011268A)) / 15, MENU->unk84->unk2 - 1, 0x61, 0xC3, 0x60, 0xC0, 0xFF, sp6C);
        func_800353F4(&D_800F22B4, MENU->unk84, 0, 0, ((MENU->unk84->unk0 - 1) * (0x12 - D_8011268C)) / 15, MENU->unk84->unk2 - 1, 0x61, 0xC9, 0xFF, 0xDC, 0, sp6C);
        func_800338B0(&D_800F22B4);
    }
    if (D_800E1240 >= 0) {
        func_800335F0(&D_800F22B4);
        func_8003396C(&D_800F22B4, D_800E10AC, 0x14, 0x4E, 0xFF, 0xFF, 0xFF, D_800E1202);
        func_80038478(&D_800F22B4, 0x85, 0x5A, D_800ECC14, 0xE6, 0x61, 0x1E, D_800E1202);
        func_80038478(&D_800F22B4, 0x32, 0x6C, D_800ECC24, 0xE6, 0x61, 0x1E, D_800E1202);
        for (sp74 = 0; sp74 < 2; sp74++) {
            if (D_800E1240 == sp74) {
                func_80038478(&D_800F22B4, 0x104 - func_800388BC(D_800E11D8[sp74]) - (sp74 * 5), (sp74 * 0x12) + 0x82, D_800E11D8[sp74], 0xFF, 0xFF, 0xFF, D_80102698);
            } else {
                func_80038478(&D_800F22B4, 0x104 - func_800388BC(D_800E11D8[sp74]) - (sp74 * 5), (sp74 * 0x12) + 0x82, D_800E11D8[sp74], 0xE6, 0x61, 0x1E, D_800E1202);
            }
        }
        func_8003396C(&D_800F22B4, MENU->unkC, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
        func_8003396C(&D_800F22B4, MENU->unk10, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
        func_800338B0(&D_800F22B4);
    }
    if (D_800E07CC[0] < 0) {
        for (sp74 = 0; sp74 < 4; sp74++) {
            if (D_800DFDD4[sp74] != 0) {
                D_800E07CC[0] = sp74;
            }
        }
    }
    if ((D_800E07CC[0] >= 0) && (D_800DFF08 != 5) && (D_800E11FC == 0)) {
        if (D_800E1240 >= 0) {
            if (D_800DFDD4[D_800E07CC[0]] & 0xC00) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                D_800E1240 ^= 1;
            }
            if (D_800DFDD4[D_800E07CC[0]] & 0xB000) {
                func_8007D45C(D_8010B358, D_800E2818, 3);
                if (D_800E1240 == 0) {
                    D_800E1240 = -1;
                    D_800E11FC = 1;
                } else {
                    D_800E1240 = -1;
                    D_800E1230 = 0;
                    D_800E1208 = 0;
                    D_800E120C = 0;
                }
            }
            if (D_800DFDD4[D_800E07CC[0]] & 0x4000) {
                func_8007D45C(D_8010B358, D_800E2818, 4);
                D_800E1240 = -1;
            }
        } else if (CURSOR < 0) {
            if (D_800DFDD4[D_800E07CC[0]] & 0x800) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                D_800E1222 -= 1;
                if (D_800E1222 < 0) {
                    D_800E1222 = 3;
                }
            }
            if (D_800DFDD4[D_800E07CC[0]] & 0x400) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                D_800E1222 += 1;
                if (D_800E1222 >= 4) {
                    D_800E1222 = 0;
                }
            }
            if (D_800DFDD4[D_800E07CC[0]] & 0x4000) {
                if (D_800E1264 != NULL) {
                    D_800E1264->unk2C = 0.08f;
                }
                func_8007D45C(D_8010B358, D_800E2818, 4);
                func_8003FD78();
                func_8003F8D8();
            }
            switch (D_800E1222) {
            case 2:
                if ((D_800DFDB4[D_800E07CC[0]] == 0x25) && (D_800DFDA4[D_800E07CC[0]] != 0x25)) {
                    D_800E13C0 ^= 9;
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0xA000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1224 = 0x44;
                }
                break;
            case 3:
                if (D_800DFDD4[D_800E07CC[0]] & 0xA000) {
                    D_80102CF4 = 1.0f;
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1224 = D_800E07D4[0];
                }
                break;
            case 1:
                if (D_800DFDD4[D_800E07CC[0]] & 0xA000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_80113328 = D_800E13C8;
                    func_80065660();
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E1230 = 0;
                }
                break;
            case 0:
                if (D_800DFDD4[D_800E07CC[0]] & 0xB000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1224 = D_800E0754[1];
                }
                break;
            }
            if ((D_800DFDD4[D_800E07CC[0]] & 0x1000) && (D_800E1222 != 0)) {
                func_8007D45C(D_8010B358, D_800E2818, 3);
                D_800E1222 = 0;
            }
        } else if ((D_800E1222 != 0) && (D_800DFDD4[D_800E07CC[0]] & 0x1000)) {
            switch (D_800E1222) {
            case 2:
                if ((D_800DFDB4[D_800E07CC[0]] == 0x25) && (D_800DFDA4[D_800E07CC[0]] != 0x25)) {
                    D_800E13C0 ^= 9;
                }
                func_8007D45C(D_8010B358, D_800E2818, 3);
                D_800E1222 = 0;
                D_800E1224 = -1;
                sp70 = 0;
                while ((D_800E12D8[sp70] != 0) && (D_800E12D8[sp70] == ((u8 *)D_800E0784)[sp70])) {
                    sp70++;
                }
                if (D_800E12D8[sp70] == ((u8 *)D_800E0784)[sp70]) {
                    D_800E12DC = 1;
                    func_8007D45C(D_8010B358, D_800E2818, 0xA);
                } else {
                    sp70 = 0;
                    while ((D_800E12E0[sp70] != 0) && (D_800E12E0[sp70] == ((u8 *)D_800E0784)[sp70])) {
                        sp70++;
                    }
                    if (D_800E12E0[sp70] == ((u8 *)D_800E0784)[sp70]) {
                        D_800E12E4 = 1;
                        func_8007D45C(D_8010B358, D_800E2818, 0xA);
                    } else {
                        sp70 = 0;
                        while ((D_800E12E8[sp70] != 0) && (D_800E12E8[sp70] == ((u8 *)D_800E0784)[sp70])) {
                            sp70++;
                        }
                        if (D_800E12E8[sp70] == ((u8 *)D_800E0784)[sp70]) {
                            func_8007D45C(D_8010B358, D_800E2818, 0xA);
                            D_800E12EC = 1;
                            func_8003FD78();
                            func_8003F8D8();
                        } else {
                            sp70 = 0;
                            while ((D_800E12F8[sp70] != 0) && (D_800E12F8[sp70] == ((u8 *)D_800E0784)[sp70])) {
                                sp70++;
                            }
                            if (D_800E12F8[sp70] == ((u8 *)D_800E0784)[sp70]) {
                                D_800E28E4 = 0x16;
                                func_8007D45C(D_8010B358, D_800E2818, 0xA);
                            } else {
                                sp70 = 0;
                                while ((D_800E12F0[sp70] != 0) && (D_800E12F0[sp70] == ((u8 *)D_800E0784)[sp70])) {
                                    sp70++;
                                }
                                if (D_800E12F0[sp70] == ((u8 *)D_800E0784)[sp70]) {
                                    D_800E12F4 = 1;
                                    func_8007D45C(D_8010B358, D_800E2818, 0xA);
                                } else if (((u8 *)D_800E0784)[0] != 0) {
                                    for (sp70 = 0; sp70 < 9; sp70++) {
                                        D_800E13C8[sp70] = ((u8 *)D_800E0784)[sp70];
                                    }
                                }
                            }
                        }
                    }
                }
                for (sp70 = 0; sp70 < 9; sp70++) {
                    ((u8 *)D_800E0784)[sp70] = 0;
                }
                break;
            case 3:
                D_80102CF4 = 0.0f;
                func_8007D45C(D_8010B358, D_800E2818, 3);
                D_800E07D4[0] = CURSOR;
                D_800E1224 = -1;
                D_800E1222 = 0;
                break;
            case 1:
                func_8007D45C(D_8010B358, D_800E2818, 3);
                D_800E1224 = -1;
                D_800E1222 = 0;
                break;
            }
        } else {
            switch (D_800E1222) {
            case 2:
                if ((D_800DFDB4[D_800E07CC[0]] == 0x25) && (D_800DFDA4[D_800E07CC[0]] != 0x25)) {
                    D_800E13C0 ^= 9;
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x400) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    sp48 = D_800E1160[(CURSOR >> 3) + D_800E13C0];
                    sp74 = CURSOR & 7;
                    while (*sp48 != 0) {
                        sp48++;
                        sp74--;
                    }
                    if (CURSOR < 0x40) {
                        D_800E1224 = CURSOR + 8;
                    } else {
                        D_800E1224 = CURSOR - 0x40;
                    }
                    sp48 = D_800E1160[(CURSOR >> 3) + D_800E13C0];
                    while (*sp48 != 0) {
                        sp48++;
                        sp74++;
                    }
                    if (sp74 < 0) {
                        sp74 = 0;
                    }
                    D_800E1224 = (CURSOR & 0xF8) + sp74;
                    while (D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7] == 0x20) {
                        D_800E1224 = CURSOR + 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x800) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    sp48 = D_800E1160[(CURSOR >> 3) + D_800E13C0];
                    sp74 = CURSOR & 7;
                    while (*sp48 != 0) {
                        sp48++;
                        sp74--;
                    }
                    if (CURSOR >= 8) {
                        D_800E1224 = CURSOR - 8;
                    } else {
                        D_800E1224 = CURSOR + 0x40;
                    }
                    sp48 = D_800E1160[(CURSOR >> 3) + D_800E13C0];
                    while (*sp48 != 0) {
                        sp48++;
                        sp74++;
                    }
                    if (sp74 < 0) {
                        sp74 = 0;
                    }
                    D_800E1224 = (CURSOR & 0xF8) + sp74;
                    while (D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7] == 0x20) {
                        D_800E1224 = CURSOR + 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x200) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    if (!(CURSOR & 7)) {
                        while (D_800E1160[(CURSOR >> 3) + D_800E13C0][(CURSOR & 7) + 1] != 0) {
                            D_800E1224 = CURSOR + 1;
                        }
                    } else {
                        D_800E1224 = CURSOR - 1;
                    }
                    while (D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7] == 0x20) {
                        D_800E1224 = CURSOR - 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x100) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 = CURSOR + 1;
                    if (D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7] == 0) {
                        D_800E1224 = CURSOR & 0xF8;
                    }
                    while (D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7] == 0x20) {
                        D_800E1224 = CURSOR + 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0xA000) {
                    sp4C[0] = D_800E1160[(CURSOR >> 3) + D_800E13C0][CURSOR & 7];
                    if (sp4C[0] == 0x22) {
                        sp4C[0] = 0x20;
                    }
                    if (sp4C[0] == 0x2F) {
                        func_8007D45C(D_8010B358, D_800E2818, 4);
                        D_800E1224 = -1;
                        for (sp70 = 0; sp70 < 9; sp70++) {
                            ((u8 *)D_800E0784)[sp70] = 0;
                        }
                    } else if (sp4C[0] == 0x5F) {
                        func_8007D45C(D_8010B358, D_800E2818, 3);
                        D_800E1224 = -1;
                        sp70 = 0;
                        while ((D_800E12D8[sp70] != 0) && (D_800E12D8[sp70] == ((u8 *)D_800E0784)[sp70])) {
                            sp70++;
                        }
                        if (D_800E12D8[sp70] == ((u8 *)D_800E0784)[sp70]) {
                            D_800E12DC = 1;
                            func_8007D45C(D_8010B358, D_800E2818, 0xA);
                        } else {
                            sp70 = 0;
                            while ((D_800E12E0[sp70] != 0) && (D_800E12E0[sp70] == ((u8 *)D_800E0784)[sp70])) {
                                sp70++;
                            }
                            if (D_800E12E0[sp70] == ((u8 *)D_800E0784)[sp70]) {
                                D_800E12E4 = 1;
                                func_8007D45C(D_8010B358, D_800E2818, 0xA);
                            } else {
                                sp70 = 0;
                                while ((D_800E12E8[sp70] != 0) && (D_800E12E8[sp70] == ((u8 *)D_800E0784)[sp70])) {
                                    sp70++;
                                }
                                if (D_800E12E8[sp70] == ((u8 *)D_800E0784)[sp70]) {
                                    func_8007D45C(D_8010B358, D_800E2818, 0xA);
                                    D_800E12EC = 1;
                                    func_8003FD78();
                                    func_8003F8D8();
                                } else {
                                    sp70 = 0;
                                    while ((D_800E12F8[sp70] != 0) && (D_800E12F8[sp70] == ((u8 *)D_800E0784)[sp70])) {
                                        sp70++;
                                    }
                                    if (D_800E12F8[sp70] == ((u8 *)D_800E0784)[sp70]) {
                                        D_800E28E4 = 0x16;
                                        func_8007D45C(D_8010B358, D_800E2818, 0xA);
                                    } else {
                                        sp70 = 0;
                                        while ((D_800E12F0[sp70] != 0) && (D_800E12F0[sp70] == ((u8 *)D_800E0784)[sp70])) {
                                            sp70++;
                                        }
                                        if (D_800E12F0[sp70] == ((u8 *)D_800E0784)[sp70]) {
                                            D_800E12F4 = 1;
                                            func_8007D45C(D_8010B358, D_800E2818, 0xA);
                                        } else if (((u8 *)D_800E0784)[0] != 0) {
                                            for (sp70 = 0; sp70 < 9; sp70++) {
                                                D_800E13C8[sp70] = ((u8 *)D_800E0784)[sp70];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        for (sp70 = 0; sp70 < 9; sp70++) {
                            ((u8 *)D_800E0784)[sp70] = 0;
                        }
                        D_800E1222 = 0;
                    } else if (sp4C[0] == 0x29) {
                        if (((u8 *)D_800E0784)[0] != 0) {
                            sp74 = 1;
                            while (((u8 *)D_800E0784)[sp74] != 0) {
                                sp74++;
                            }
                            ((u8 *)D_800E0784)[sp74 - 1] = 0;
                        }
                        func_8007D45C(D_8010B358, D_800E2818, 4);
                    } else {
                        func_8007D45C(D_8010B358, D_800E2818, 4);
                        if (((u8 *)D_800E0784)[6] == 0) {
                            sp74 = 0;
                            while (((u8 *)D_800E0784)[sp74] != 0) {
                                sp74++;
                            }
                            ((u8 *)D_800E0784)[sp74] = sp4C[0];
                            ((u8 *)D_800E0784)[sp74 + 1] = 0;
                            if (sp74 == 6) {
                                D_800E1224 = 0x44;
                            }
                        }
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    if (((u8 *)D_800E0784)[0] != 0) {
                        if (CURSOR == 0x40) {
                            sp74 = 1;
                            while (((u8 *)D_800E0784)[sp74] != 0) {
                                sp74++;
                            }
                            ((u8 *)D_800E0784)[sp74 - 1] = 0;
                        }
                        D_800E1224 = 0x40;
                    } else {
                        D_800E1224 = -1;
                    }
                }
                break;
            case 3:
                if (D_800DFDD4[D_800E07CC[0]] & 0xA00) {
                    D_80102CF8 = 0.0f;
                    D_80102CFC = 0.0f;
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 = CURSOR - 1;
                    if (CURSOR < 0) {
                        D_800E1224 = 6;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x500) {
                    D_80102CF8 = 0.0f;
                    D_80102CFC = 0.0f;
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 = CURSOR + 1;
                    if (CURSOR >= 7) {
                        D_800E1224 = 0;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0xA000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E07D4[0] = CURSOR;
                    D_800E1224 = -1;
                    D_80102CF4 = 0.0f;
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x4000) {
                    if (D_800E07D4[0] != CURSOR) {
                        D_80102CF8 = 0.0f;
                        D_80102CFC = 0.0f;
                    }
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1224 = -1;
                    D_80102CF4 = 0.0f;
                }
                break;
            case 1:
                if (D_800DFDD4[D_800E07CC[0]] & 0x800) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 = CURSOR - 1;
                    if (CURSOR < 0) {
                        D_800E1224 = 2;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x400) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 = CURSOR + 1;
                    if (CURSOR >= 3) {
                        D_800E1224 = 0;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0xA200) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800DFE80 = CURSOR;
                    D_800E1224 = -1;
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1224 = -1;
                }
                break;
            case 0:
                if (D_800DFDD4[D_800E07CC[0]] & 0x800) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 = CURSOR - 1;
                    if (CURSOR < 0) {
                        D_800E1224 = D_800E12E4 + 4;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x400) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 = CURSOR + 1;
                    if (CURSOR > D_800E12E4 + 4) {
                        D_800E1224 = 0;
                    }
                }
                D_800E0754[1] = CURSOR;
                if (D_800DFDD4[D_800E07CC[0]] & 0xB000) {
                    D_800DFD4C = 1;
                    D_8015D980 = 1;
                    D_800DFD50 = 1;
                    D_800DFD54 = 1;
                    D_800E4498 = 0;
                    D_800E449C = 0;
                    D_80102666 = 0;
                    D_800E44A0 = 0;
                    switch (D_800E1224) {
                    case 0:
                        D_800E44A8 = 1;
                        break;
                    case 1:
                        D_800E44A8 = 5;
                        break;
                    case 5:
                        D_800E44A8 = 9;
                        D_800DFD4C = 2;
                        break;
                    case 2:
                        D_800E44A8 = 4;
                        break;
                    case 3:
                        D_800E44A8 = 2;
                        break;
                    case 4:
                        D_800E44A4 = 1;
                        D_8015D980 = 2;
                        D_800E44A8 = 6;
                        D_801125F6 = 1;
                        D_8011585E = 0;
                        D_800E08A8 = 1;
                        D_800E08AC = 0;
                        D_800E08B0 = 0;
                        D_800E088C = 0;
                        break;
                    }
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E4498 = 0;
                    D_800E449C = 0;
                    D_800E44A0 = 0;
                    D_80113320 = D_800E07CC[0];
                    D_80113322 = D_800E07D4[0];
                    D_80113328 = D_800E13C8;
                    D_80113323 = D_800E07E4[0];
                    func_80065D74();
                    sp5C = func_80066854();
                    func_80065660();
                    if ((sp5C == 0) && (func_80066CE8() == 0)) {
                        D_800E1240 = 0;
                    } else {
                        D_800E11FC = 1;
                    }
                    if (D_800E44A8 == 0xC) {
                        D_800E122A = 0;
                        for (sp70 = 0; sp70 < 9; sp70++) {
                            ((u8 *)D_800E0784)[sp70] = D_800E13C8[sp70];
                        }
                        D_800E1208 = 0;
                        D_800E120C = 0;
                    } else if ((D_800E44A8 != 2) && ((D_800E4498 > 0) || (D_80102666 > 0) || (D_800E12DC != 0))) {
                        D_800E1232 = 0;
                        for (sp70 = 0; sp70 < 9; sp70++) {
                            ((u8 *)D_800E0784)[sp70] = D_800E13C8[sp70];
                        }
                        D_800E1208 = 0;
                        D_800E120C = 0;
                    } else if (D_800E44A8 == 6) {
                        D_800E122A = 0;
                        for (sp70 = 0; sp70 < 9; sp70++) {
                            ((u8 *)D_800E0784)[sp70] = D_800E13C8[sp70];
                        }
                        D_800E1208 = 0;
                        D_800E120C = 0;
                    }
                }
                if (D_800DFDD4[D_800E07CC[0]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1224 = -1;
                }
                break;
            }
        }
    }
    if ((D_800E11FC == 0) && !(D_800DFDB4[D_800E07CC[0]] & 0x30)) {
        if (D_800DFDB4[D_800E07CC[0]] & 2) {
            for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
                D_80102CF8 -= 1.0;
            }
            if (D_80102CF8 < -180.0) {
                D_80102CF8 += 360.0;
            }
        }
        if (D_800DFDB4[D_800E07CC[0]] & 1) {
            for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
                D_80102CF8 += 1.0;
            }
            if (D_80102CF8 > 180.0) {
                D_80102CF8 -= 360.0;
            }
        }
        if (D_800DFDB4[D_800E07CC[0]] & 4) {
            for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
                D_80102CFC -= 1.0;
            }
            if (D_80102CFC < -180.0) {
                D_80102CFC += 360.0;
            }
        }
        if (D_800DFDB4[D_800E07CC[0]] & 8) {
            for (sp74 = D_800E1210; sp74 < D_800E1208; sp74++) {
                D_80102CFC += 1.0;
            }
            if (D_80102CFC > 180.0) {
                D_80102CFC -= 360.0;
            }
        }
    }
}

extern s32 func_80033504(u8 *, u8 *);
extern void func_80065748(void);
extern void func_800657FC(void);
extern u8 D_800E07DC[8];
extern s32 D_800E07EC[];
extern s32 D_800E080C[];
extern s32 D_800E082C[];
extern u8 *D_800E08B4[];
extern s32 D_800E0B0C;
extern f32 D_800E0E24[];
extern f32 D_800E0E40[];
extern f32 D_800E0E5C[];
extern f32 D_800E0E78[];
extern f32 D_800E0E94[];
extern f32 D_800E0EB0[];
extern void *D_800E1024;
extern s32 D_800E10B4;
extern s16 D_800E1226;
extern s16 D_800E123A;
extern s16 D_800E1244;
extern s32 D_800E126C;
extern s32 D_800E1274;
extern Obj *D_800E1278;
extern u8 D_800ECC3C;
extern u8 D_800ECC40;
extern f32 D_80102BF8[16];
extern s32 D_80102D00;
extern u8 D_80113488[];
extern s16 D_801158F2;
extern s16 D_801158F4;

typedef struct {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ u8 *unkC;
    /* 0x010 */ u8 *unk10;
    /* 0x014 */ u8 pad14[0xC];
    /* 0x020 */ void *unk20;
    /* 0x024 */ void *unk24;
    /* 0x028 */ void *unk28;
    /* 0x02C */ void *unk2C;
    /* 0x030 */ void *unk30;
    /* 0x034 */ void *unk34;
    /* 0x038 */ void *unk38;
    /* 0x03C */ void *unk3C;
    /* 0x040 */ void *unk40;
    /* 0x044 */ void *unk44;
    /* 0x048 */ u16 *unk48;
    /* 0x04C */ void *unk4C;
    /* 0x050 */ void *unk50;
    /* 0x054 */ u8 pad54[0x170 - 0x54];
    /* 0x170 */ u8 *unk170;
    /* 0x174 */ u8 pad174[0x194 - 0x174];
    /* 0x194 */ u8 *unk194;
    /* 0x198 */ u8 pad198[0x250 - 0x198];
    /* 0x250 */ s32 unk250;
    /* 0x254 */ u8 pad254[0x264 - 0x254];
    /* 0x264 */ s32 unk264;
} T1010_46;

#define MENU46 ((T1010_46 *)&D_800E1010)

void func_80046A9C(void) {
    s32 i;
    s32 j;
    s32 len;
    s32 pad;
    s32 alpha2;
    s32 alpha;
    u8 buf[9];
    u8 *p;

    if (D_800E122A >= 0) {
        func_80050BFC();
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        func_800657FC();
        MENU46->unk170[2] = 0x20;
        MENU46->unk194[2] = 0x20;
        MENU46->unkC = loadAsset(D_736C50, 0x19, 8);
        MENU46->unk10 = loadAsset(D_736C50, 0x47, 8);
        D_800E1028 = loadAsset(D_736C50, 0x4F, 8);
        D_800E102C = loadAsset(D_736C50, 0x50, 8);
        D_800E1018 = loadAsset(D_736C50, 0x3A, 8);
        D_800E1024 = loadAsset(D_736C50, 0x57, 8);
        D_800E10B4 = loadAsset(D_736C50, 0x98, 8);
        MENU46->unk20 = loadAsset(D_736C50, 0x1C, 8);
        MENU46->unk24 = loadAsset(D_736C50, 0x1D, 8);
        MENU46->unk28 = loadAsset(D_736C50, 0x77, 8);
        MENU46->unk2C = loadAsset(D_736C50, 0x1F, 8);
        MENU46->unk30 = loadAsset(D_736C50, 0x20, 8);
        MENU46->unk34 = loadAsset(D_736C50, 0x21, 8);
        MENU46->unk38 = loadAsset(D_736C50, 0x22, 8);
        MENU46->unk3C = loadAsset(D_736C50, 0x72, 8);
        MENU46->unk40 = loadAsset(D_736C50, 0x49, 8);
        MENU46->unk44 = loadAsset(D_736C50, 0x4A, 8);
        MENU46->unk48 = loadAsset(D_736C50, 0x13, 8);
        MENU46->unk4C = loadAsset(D_736C50, 0x23, 8);
        MENU46->unk50 = loadAsset(D_736C50, 0x25, 8);
        for (i = 0; i < 8; i++) {
            D_800E1074[i] = loadAsset(D_736C50, i + 0x82, 8);
        }
        if (D_800E0B20 != 2) {
            loadsong(D_800E94B0, D_80107290);
        } else {
            loadsong(D_800E0B24, D_80107290);
        }
        func_8007ACFC(D_80107290);
        D_800E1222 = 0;
        D_800E1254 = D_800F22C0;
        D_800E1242 = -1;
        D_800E1244 = -1;
        D_800E123E = ((u8 *) D_800E07D4)[0];
        D_800E1240 = ((u8 *) D_800E07D4)[1];
        D_800E1264 = NULL;
        D_800E1278 = NULL;
        D_800E11FC = 0;
        D_800E1222 = 2;
        D_800E1224 = 0x44;
        D_800E1226 = 0x44;
        for (i = 0; i < 8; i++) {
            D_800E07EC[i] = 0;
            D_800E080C[i] = 0;
            D_800E082C[i] = 0;
            buf[0] = 0x50;
            buf[1] = 0x4C;
            buf[2] = 0x41;
            buf[3] = 0x59;
            buf[4] = 0x45;
            buf[5] = 0x52;
            buf[6] = 0x20;
            buf[7] = i + 0x31;
            buf[8] = 0;
            if (func_80033504(((u8*)D_800E0784) + i * 9, buf) != 0) {
                for (j = 0; j < 9; j++) {
                    ((u8*)D_800E0784)[i * 9 + j] = 0;
                }
            }
        }
        D_80102D00 = 0;
        D_800E088C = 0;
        D_800E123A = 0xA;
        D_800E13C0 = 0;
        func_8003FC6C(0x58, 0x32, 0x40, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if (D_800E11FC == 3) {
        D_800E11FC = 4;
        func_8003FD78();
        func_8003F8D8();
    }
    buf[1] = 0;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E1224 = -1;
        D_800E1222 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        func_80065748();
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, MENU46->unkC, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
    func_8003396C(&D_800F22B4, MENU46->unk10, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E102C, 0x11, 0x17, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E1028, 0x17, 0x1D, 0xFF, 0xFF, 0xFF, D_800E1202);
    if (D_800E0B0C >= D_80102D00 + 2) {
        alpha = D_800E1202;
    } else {
        alpha = D_800E1202 * 0x64 / 255;
    }
    func_8003396C(&D_800F22B4, D_800E102C, 0x11, 0x73, 0xFF, 0xFF, 0xFF, alpha);
    func_8003396C(&D_800F22B4, D_800E1028, 0x17, 0x79, 0xFF, 0xFF, 0xFF, alpha);
    if (D_800E07E4[D_80102D00] != 0) {
        func_80038478(&D_800F22B4, 0x4C, 0x20, &D_800ECC3C, 0xFF, 0xDC, 0x3E, D_800E1202);
    }
    if (D_800E07E4[D_80102D00 + 1] != 0) {
        func_80038478(&D_800F22B4, 0x4C, 0x7D, &D_800ECC40, 0x2A, 0xE6, 0xFF, D_800E1202);
    }
    func_8003396C(&D_800F22B4, D_800E1074[D_80102D00], 0x2A - *(u16*)D_800E1074[D_80102D00], 0x29, 0xFF, 0xFF, 0xFF, D_800E1202);
    if (D_800E0B0C < D_80102D00 + 2) {
        alpha = D_800E1202 * 0x64 / 255;
    } else {
        alpha = D_800E1202;
    }
    func_8003396C(&D_800F22B4, D_800E1074[D_80102D00 + 1], 0x2A - *(u16*)D_800E1074[D_80102D00 + 1], 0x85, 0xFF, 0xFF, 0xFF, alpha);
    j = D_800E1222;
    if (D_800E1224 >= 0) {
        alpha = D_800E1202;
    } else {
        alpha = D_800E1202 * 0x8C / 255;
    }
    alpha2 = (D_800E0B0C < D_80102D00 + 2) ? D_800E1202 * 0x64 / 255
        : ((D_800E1226 >= 0) ? D_800E1202 : D_800E1202 * 0x8C / 255);
    switch (j) {
    case 2:
        func_8003396C(&D_800F22B4, MENU46->unk40, 0x76, 0x39, 0xFF, 0xDC, 0x3E, alpha);
        if ((D_800E1224 < 0x40) && (D_800E1224 >= 0) && (D_800E1222 == 2) && (((u8*)D_800E0784)[D_80102D00 * 9 + 6] == 0)) {
            if (((u8*)D_800E0784)[D_80102D00 * 9 + 6] == 0) {
                buf[0] = D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7];
                buf[1] = 0;
                func_80038478(&D_800F22B4, 0x96 - func_800388BC(buf), 0x43, buf, 0xFF, 0xDC, 0x3E, alpha);
            } else {
                buf[0] = 0;
            }
            func_80038478(&D_800F22B4, 0x96 - func_800388BC(((u8*)D_800E0784) + D_80102D00 * 9) - func_800388BC(buf), 0x43, ((u8*)D_800E0784) + D_80102D00 * 9, 0xE6, 0x61, 0x1E, alpha);
        } else if ((D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7] == 0x29) && (((u8*)D_800E0784)[D_80102D00 * 9] != 0) && (D_800E1222 == 2)) {
            p = ((u8*)D_800E0784) + D_80102D00 * 9;
            while (*p != 0) {
                p++;
            }
            p--;
            len = func_800388BC(((u8*)D_800E0784) + D_80102D00 * 9);
            buf[0] = *p;
            buf[1] = 0;
            *p = 0;
            func_80038478(&D_800F22B4, 0x96 - len, 0x43, ((u8*)D_800E0784) + D_80102D00 * 9, 0xE6, 0x61, 0x1E, alpha);
            func_80038478(&D_800F22B4, 0x96 - func_800388BC(buf), 0x43, buf, 0xE6, 0x61, 0x1E, D_80102698);
            *p = buf[0];
        } else {
            func_80038478(&D_800F22B4, 0x96 - func_800388BC(((u8*)D_800E0784) + D_80102D00 * 9), 0x43, ((u8*)D_800E0784) + D_80102D00 * 9, 0xE6, 0x61, 0x1E, alpha);
        }
        func_8003396C(&D_800F22B4, MENU46->unk40, 0x76, 0x94, 0x2A, 0xE6, 0xFF, alpha2);
        if ((D_800E1226 < 0x40) && (D_800E1226 >= 0) && (D_800E1222 == 2) && (((u8*)D_800E0784)[D_80102D00 * 9 + 0xF] == 0)) {
            if (((u8*)D_800E0784)[D_80102D00 * 9 + 0xF] == 0) {
                buf[0] = D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7];
                func_80038478(&D_800F22B4, 0x96 - func_800388BC(buf), 0x9E, buf, 0x2A, 0xE6, 0xFF, alpha2);
            } else {
                buf[0] = 0;
            }
            func_80038478(&D_800F22B4, 0x96 - func_800388BC(((u8*)D_800E0784) + D_80102D00 * 9 + 9) - func_800388BC(buf), 0x9E, ((u8*)D_800E0784) + D_80102D00 * 9 + 9, 0xE6, 0x61, 0x1E, alpha2);
        } else if ((D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7] == 0x29) && (((u8*)D_800E0784)[D_80102D00 * 9 + 9] != 0) && (D_800E1222 == 2)) {
            p = ((u8*)D_800E0784) + D_80102D00 * 9 + 9;
            while (*p != 0) {
                p++;
            }
            p--;
            len = func_800388BC(((u8*)D_800E0784) + D_80102D00 * 9 + 9);
            buf[0] = *p;
            buf[1] = 0;
            *p = 0;
            func_80038478(&D_800F22B4, 0x96 - len, 0x9E, ((u8*)D_800E0784) + D_80102D00 * 9 + 9, 0xE6, 0x61, 0x1E, alpha2);
            func_80038478(&D_800F22B4, 0x96 - func_800388BC(buf), 0x9E, buf, 0xE6, 0x61, 0x1E, D_80102698);
            *p = buf[0];
        } else {
            func_80038478(&D_800F22B4, 0x96 - func_800388BC(((u8*)D_800E0784) + D_80102D00 * 9 + 9), 0x9E, ((u8*)D_800E0784) + D_80102D00 * 9 + 9, 0xE6, 0x61, 0x1E, alpha2);
        }
        break;
    case 3:
        func_8003396C(&D_800F22B4, MENU46->unk44, 0x88, 0x23, 0xFF, 0xDC, 0x3E, alpha);
        if ((D_800E1222 != 3) || (D_800E1224 < 0)) {
            D_800E123E = D_800E07D4[D_80102D00];
        } else {
            D_800E123E = D_800E1224;
        }
        func_80038478(&D_800F22B4, 0x5D - (func_800388BC(D_800E08B4[D_800E123E]) >> 1), 0x5D, D_800E08B4[D_800E123E], 0xE6, 0x61, 0x1E, alpha);
        func_8003396C(&D_800F22B4, MENU46->unk44, 0x88, 0x7F, 0x2A, 0xE6, 0xFF, alpha2);
        if ((D_800E1222 != 3) || (D_800E1226 < 0)) {
            D_800E1240 = D_800E07D4[D_80102D00 + 1];
        } else {
            D_800E1240 = D_800E1226;
        }
        func_80038478(&D_800F22B4, 0x5D - (func_800388BC(D_800E08B4[D_800E1240]) >> 1), 0xB9, D_800E08B4[D_800E1240], 0xE6, 0x61, 0x1E, alpha2);
        break;
    case 1:
        func_8003396C(&D_800F22B4, MENU46->unk3C, 0x55, 0x32, 0xFF, 0xDC, 0x3E, alpha);
        p = func_8003E358(D_800E07DC[D_80102D00]);
        func_80038478(&D_800F22B4, 0x8F - func_800388BC(p), 0x49, p, 0xE6, 0x61, 0x1E, alpha);
        func_8003396C(&D_800F22B4, MENU46->unk3C, 0x55, 0x8E, 0x2A, 0xE6, 0xFF, alpha2);
        p = func_8003E358(D_800E07DC[D_80102D00 + 1]);
        func_80038478(&D_800F22B4, 0x8F - func_800388BC(p), 0xA5, p, 0xE6, 0x61, 0x1E, alpha2);
        func_8003396C(&D_800F22B4, D_800E1024, 0x64, 0x49, 0xFF, 0xFF, 0xFF, alpha);
        func_8003396C(&D_800F22B4, D_800E10B4, 0x64, 0x49, 0xFF, 0xFF, 0xFF, alpha);
        func_8003396C(&D_800F22B4, D_800E1024, 0x64, 0xA5, 0xFF, 0xFF, 0xFF, alpha2);
        func_8003396C(&D_800F22B4, D_800E10B4, 0x64, 0xA5, 0xFF, 0xFF, 0xFF, alpha2);
        break;
    }
    switch (D_800E1222) {
    case 2:
        for (j = 0; j < 9; j++) {
            buf[0] = 0;
            p = D_800E1160[j + D_800E13C0];
            i = 0;
            while (*p != 0) {
                p++;
                i++;
            }
            p = D_800E1160[j + D_800E13C0];
            len = 0;
            while (*p != 0) {
                buf[0] = *p;
                if (((D_800E1224 >> 3) == j) && ((D_800E1224 & 7) == len)) {
                    if (((D_800E1226 >> 3) == j) && ((D_800E1226 & 7) == len) && (D_800E0B0C >= D_80102D00 + 2)) {
                        func_80038478(&D_800F22B4, 0x12E - (j * 6) - (i * 0xE) - (func_800388BC(buf) >> 1), j * 0x12 + 0x25, buf, 0xFF, 0xFF, 0xFF, D_80102698);
                    } else {
                        func_80038478(&D_800F22B4, 0x12E - (j * 6) - (i * 0xE) - (func_800388BC(buf) >> 1), j * 0x12 + 0x25, buf, 0xFF, 0xDC, 0x3E, D_80102698);
                    }
                } else if (((D_800E1226 >> 3) == j) && ((D_800E1226 & 7) == len) && (D_800E0B0C >= D_80102D00 + 2)) {
                    func_80038478(&D_800F22B4, 0x12E - (j * 6) - (i * 0xE) - (func_800388BC(buf) >> 1), j * 0x12 + 0x25, buf, 0x2A, 0xE6, 0xFF, D_80102698);
                } else {
                    func_80038478(&D_800F22B4, 0x12E - (j * 6) - (i * 0xE) - (func_800388BC(buf) >> 1), j * 0x12 + 0x25, buf, 0xE6, 0x61, 0x1E, D_800E1202);
                }
                p++;
                i--;
                len++;
            }
        }
        break;
    case 3:
        for (i = 0; i < 7; i++) {
            len = D_800E1202;
            if (D_800E1224 == i) {
                if ((D_800E1226 == i) && (D_800E0B0C >= D_80102D00 + 2)) {
                    func_8003396C(&D_800F22B4, D_800E1030[i], ((i + 1) / 3 * 0x40) - (i * 0x1B) + 0xEA, (i * 0x20) - ((i + 1) / 3 * 0x20) + 0x28, 0xFF, 0xFF, 0xFF, len);
                } else {
                    func_8003396C(&D_800F22B4, D_800E1030[i], ((i + 1) / 3 * 0x40) - (i * 0x1B) + 0xEA, (i * 0x20) - ((i + 1) / 3 * 0x20) + 0x28, 0xFF, 0xDC, 0x3E, len);
                }
            } else if ((D_800E1226 == i) && (D_800E0B0C >= D_80102D00 + 2)) {
                func_8003396C(&D_800F22B4, D_800E1030[i], ((i + 1) / 3 * 0x40) - (i * 0x1B) + 0xEA, (i * 0x20) - ((i + 1) / 3 * 0x20) + 0x28, 0x2A, 0xE6, 0xFF, len);
            } else {
                func_8003396C(&D_800F22B4, D_800E1030[i], ((i + 1) / 3 * 0x40) - (i * 0x1B) + 0xEA, (i * 0x20) - ((i + 1) / 3 * 0x20) + 0x28, 0xE6, 0x61, 0x1E, len);
            }
        }
        func_800905A4(D_80110220, (D_800E1224 >= 0) ? D_800E1224 : D_800E07D4[D_80102D00]);
        func_8003396C(&D_800F22B4, MENU46->unk4C, 0x8C, 0x18, 0xFF, 0xFF, 0xFF, len);
        func_8003396C(&D_800F22B4, MENU46->unk50, 0x8C, 0x6B, 0xFF, 0xFF, 0xFF, len);
        i = MENU46->unk48[1] - ((MENU46->unk48[1] - 1) * (0xF - D_8011268A) / 15) - 1;
        func_800353F4(&D_800F22B4, MENU46->unk48, 0, i, MENU46->unk48[0] - 1, MENU46->unk48[1] - 1, 0x9D, i + 0x2E, 0x60, 0xC0, 0xFF, len);
        i = MENU46->unk48[1] - ((MENU46->unk48[1] - 1) * (0x12 - D_8011268C) / 15) - 1;
        func_800353F4(&D_800F22B4, MENU46->unk48, 0, i, MENU46->unk48[0] - 1, MENU46->unk48[1] - 1, 0xA3, i + 0x2E, 0xFF, 0xDC, 0, len);
        func_800905A4(D_80113488, (D_800E1226 >= 0) ? D_800E1226 : D_800E07D4[D_80102D00 + 1]);
        func_8003396C(&D_800F22B4, MENU46->unk4C, 0x8C, 0x76, 0xFF, 0xFF, 0xFF, len);
        func_8003396C(&D_800F22B4, MENU46->unk50, 0x8C, 0xC9, 0xFF, 0xFF, 0xFF, len);
        i = MENU46->unk48[1] - ((MENU46->unk48[1] - 1) * (0xF - D_801158F2) / 15) - 1;
        func_800353F4(&D_800F22B4, MENU46->unk48, 0, i, MENU46->unk48[0] - 1, MENU46->unk48[1] - 1, 0x9D, i + 0x8C, 0x60, 0xC0, 0xFF, len);
        i = MENU46->unk48[1] - ((MENU46->unk48[1] - 1) * (0x12 - D_801158F4) / 15) - 1;
        func_800353F4(&D_800F22B4, MENU46->unk48, 0, i, MENU46->unk48[0] - 1, MENU46->unk48[1] - 1, 0xA3, i + 0x8C, 0xFF, 0xDC, 0, len);
        break;
    case 1:
        break;
    }
    func_800338B0(&D_800F22B4);
    if (D_800E123E != D_800E1242) {
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800F22C0 = D_800E1254;
        D_800DFE84 = 1;
        D_800E1258 = loadAnim(D_800E08F4[D_800E123E]);
        D_800E1260 = loadMesh(D_800E08D4[D_800E123E]);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU46->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if (D_800E1242 < 0) {
            D_800E1264->unk28 = 1.0f;
            D_800E1264->unk2C = -0.08f;
        }
        D_800DFE84 = 0;
        D_800E1242 = D_800E123E;
    }
    if ((D_800E1240 != D_800E1244) && (D_800E0B0C >= D_80102D00 + 2)) {
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800F22C0 = D_800E1254 + 0x222E0;
        D_800DFE84 = 1;
        D_800E126C = loadAnim(D_800E08F4[D_800E1240]);
        D_800E1274 = loadMesh(D_800E08D4[D_800E1240]);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1278 = LWAllocateMemory(D_800F22C0, D_800E126C, &MENU46->unk264, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if (D_800E1244 < 0) {
            D_800E1278->unk28 = 1.0f;
            D_800E1278->unk2C = -0.08f;
        }
        D_800DFE84 = 0;
        D_800E1244 = D_800E1240;
    }
    if ((D_800E1222 == 3) && (D_800E1264 != NULL)) {
        guTranslateF((f32(*)[4])D_80102B28, D_800E0E24[D_800E123E], D_800E0E40[D_800E123E], 0.0f);
        guScaleF((f32(*)[4])D_80102BB0, D_800E0E5C[D_800E123E], D_800E0E5C[D_800E123E], D_800E0E5C[D_800E123E]);
        if (LWPlayAnimation(D_800E1264, (D_800E1208 - D_800E1210) + D_800E123A, D_80102BB0, D_80102B28) != 0) {
            D_800E1264->unk24 = 0;
        }
        D_800E123A = 0;
        if ((D_800E0B0C >= D_80102D00 + 2) && (D_800E1278 != NULL)) {
            guTranslateF((f32(*)[4])D_80102B68, D_800E0E78[D_800E1240], D_800E0E94[D_800E1240], 0.0f);
            guScaleF((f32(*)[4])D_80102BF8, D_800E0EB0[D_800E1240], D_800E0EB0[D_800E1240], D_800E0EB0[D_800E1240]);
            if (LWPlayAnimation(D_800E1278, D_800E1208 - D_800E1210, D_80102BF8, D_80102B68) != 0) {
                D_800E1278->unk24 = 0;
            }
        }
    }
    if (D_800E07CC[D_80102D00] < 0) {
        for (i = 0; i < 4; i++) {
            if (D_800DFDD4[i] != 0) {
                D_800E07CC[D_80102D00] = i;
            }
        }
    } else if (D_800E07CC[D_80102D00 + 1] < 0) {
        for (i = 0; i < 4; i++) {
            if ((D_800E07CC[D_80102D00] != i) && (D_800DFDD4[i] != 0)) {
                D_800E07CC[D_80102D00 + 1] = i;
            }
        }
    }
    if ((D_800E07CC[D_80102D00] >= 0) && (D_800DFF08 != 5)) {
        if (D_800E1224 < 0) {
            switch (D_800E1222) {
            case 2:
                if ((D_800DFDB4[D_800E07CC[D_80102D00]] == 0x25) && (D_800DFDA4[D_800E07CC[D_80102D00]] != 0x25)) {
                    D_800E13C0 ^= 9;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1224 = 0x44;
                    buf[0] = 0x50;
                    buf[1] = 0x4C;
                    buf[2] = 0x41;
                    buf[3] = 0x59;
                    buf[4] = 0x45;
                    buf[5] = 0x52;
                    buf[6] = 0x20;
                    buf[7] = D_80102D00 + 0x31;
                    buf[8] = 0;
                    if (func_80033504(((u8*)D_800E0784) + D_80102D00 * 9, buf) != 0) {
                        for (j = 0; j < 9; j++) {
                            ((u8*)D_800E0784)[D_80102D00 * 9 + j] = 0;
                        }
                    }
                }
                break;
            case 3:
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1224 = D_800E07D4[D_80102D00];
                }
                break;
            case 1:
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1224 = D_800E07DC[D_80102D00];
                }
                break;
            }
        } else {
            switch (D_800E1222) {
            case 2:
                if ((D_800DFDB4[D_800E07CC[D_80102D00]] == 0x25) && (D_800DFDA4[D_800E07CC[D_80102D00]] != 0x25)) {
                    D_800E13C0 ^= 9;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x400) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    p = D_800E1160[(D_800E1224 >> 3) + D_800E13C0];
                    i = D_800E1224 & 7;
                    while (*p != 0) {
                        p++;
                        i--;
                    }
                    if (D_800E1224 < 0x40) {
                        D_800E1224 += 8;
                    } else {
                        D_800E1224 -= 0x40;
                    }
                    p = D_800E1160[(D_800E1224 >> 3) + D_800E13C0];
                    while (*p != 0) {
                        p++;
                        i++;
                    }
                    if (i < 0) {
                        i = 0;
                    }
                    D_800E1224 = (D_800E1224 & 0xF8) + i;
                    while (D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7] == 0x20) {
                        D_800E1224 += 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x800) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    p = D_800E1160[(D_800E1224 >> 3) + D_800E13C0];
                    i = D_800E1224 & 7;
                    while (*p != 0) {
                        p++;
                        i--;
                    }
                    if (D_800E1224 >= 8) {
                        D_800E1224 -= 8;
                    } else {
                        D_800E1224 += 0x40;
                    }
                    p = D_800E1160[(D_800E1224 >> 3) + D_800E13C0];
                    while (*p != 0) {
                        p++;
                        i++;
                    }
                    if (i < 0) {
                        i = 0;
                    }
                    D_800E1224 = (D_800E1224 & 0xF8) + i;
                    while (D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7] == 0x20) {
                        D_800E1224 += 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x200) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    if (!(D_800E1224 & 7)) {
                        while (D_800E1160[(D_800E1224 >> 3) + D_800E13C0][(D_800E1224 & 7) + 1] != 0) {
                            D_800E1224 += 1;
                        }
                    } else {
                        D_800E1224 -= 1;
                    }
                    while (D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7] == 0x20) {
                        D_800E1224 -= 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x100) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 += 1;
                    if (D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7] == 0) {
                        D_800E1224 &= 0xF8;
                    }
                    while (D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7] == 0x20) {
                        D_800E1224 += 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x1000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1224 = -1;
                    if (((u8*)D_800E0784)[D_80102D00 * 9] == 0) {
                        ((u8*)D_800E0784)[D_80102D00 * 9] = 0x50;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 1] = 0x4C;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 2] = 0x41;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 3] = 0x59;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 4] = 0x45;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 5] = 0x52;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 6] = 0x20;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 7] = D_80102D00 + 0x31;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 8] = 0;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0xA000) {
                    buf[0] = D_800E1160[(D_800E1224 >> 3) + D_800E13C0][D_800E1224 & 7];
                    if (buf[0] == 0x22) {
                        buf[0] = 0x20;
                    }
                    if (buf[0] == 0x5F) {
                        func_8007D45C(D_8010B358, D_800E2818, 3);
                        D_800E1224 = -1;
                        if (((u8*)D_800E0784)[D_80102D00 * 9] == 0) {
                            ((u8*)D_800E0784)[D_80102D00 * 9] = 0x50;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 1] = 0x4C;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 2] = 0x41;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 3] = 0x59;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 4] = 0x45;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 5] = 0x52;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 6] = 0x20;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 7] = D_80102D00 + 0x31;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 8] = 0;
                        }
                    } else if (buf[0] == 0x29) {
                        func_8007D45C(D_8010B358, D_800E2818, 4);
                        if (((u8*)D_800E0784)[D_80102D00 * 9] != 0) {
                            i = 1;
                            while (((u8*)D_800E0784)[D_80102D00 * 9 + i] != 0) {
                                i++;
                            }
                            ((u8*)D_800E0784)[D_80102D00 * 9 + i - 1] = 0;
                        }
                    } else {
                        func_8007D45C(D_8010B358, D_800E2818, 3);
                        if (((u8*)D_800E0784)[D_80102D00 * 9 + 6] == 0) {
                            i = 0;
                            while (((u8*)D_800E0784)[D_80102D00 * 9 + i] != 0) {
                                i++;
                            }
                            if (i < 7) {
                                ((u8*)D_800E0784)[D_80102D00 * 9 + i] = buf[0];
                                ((u8*)D_800E0784)[D_80102D00 * 9 + i + 1] = 0;
                            }
                            if (i == 6) {
                                D_800E1224 = -1;
                            }
                        }
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    if (D_80102D00 != 0) {
                        D_80102D00 -= 2;
                        D_800E1222 = 1;
                        D_800E1224 = D_800E07DC[D_80102D00];
                        D_800E1226 = D_800E07DC[D_80102D00 + 1];
                    } else {
                        if (D_800E1264 != NULL) {
                            D_800E1264->unk2C = 0.08f;
                        }
                        if (D_800E1278 != NULL) {
                            D_800E1278->unk2C = 0.08f;
                        }
                        func_8003FD78();
                        func_8003F8D8();
                    }
                }
                break;
            case 3:
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0xA00) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 -= 1;
                    if (D_800E1224 < 0) {
                        D_800E1224 = 6;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x500) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1224 += 1;
                    if (D_800E1224 >= 7) {
                        D_800E1224 = 0;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0xB000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E07D4[D_80102D00] = D_800E1224;
                    D_800E1224 = -1;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1222 = 2;
                    D_800E1224 = 0x44;
                    D_800E1226 = 0x44;
                    buf[0] = 0x50;
                    buf[1] = 0x4C;
                    buf[2] = 0x41;
                    buf[3] = 0x59;
                    buf[4] = 0x45;
                    buf[5] = 0x52;
                    buf[6] = 0x20;
                    buf[7] = D_80102D00 + 0x31;
                    buf[8] = 0;
                    if (func_80033504(((u8*)D_800E0784) + D_80102D00 * 9, buf) != 0) {
                        for (j = 0; j < 9; j++) {
                            ((u8*)D_800E0784)[D_80102D00 * 9 + j] = 0;
                        }
                    }
                    buf[7] = D_80102D00 + 0x32;
                    buf[8] = 0;
                    if (func_80033504(((u8*)D_800E0784) + D_80102D00 * 9 + 9, buf) != 0) {
                        for (j = 0; j < 9; j++) {
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 9 + j] = 0;
                        }
                    }
                }
                break;
            case 1:
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x200) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E07DC[D_80102D00] -= 1;
                    if (D_800E07DC[D_80102D00] < 4) {
                        D_800E07DC[D_80102D00] = 0x63;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x100) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E07DC[D_80102D00] += 1;
                    if (D_800E07DC[D_80102D00] >= 0x64) {
                        D_800E07DC[D_80102D00] = 4;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0xB000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1224 = -1;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1222 = 3;
                    D_800E1224 = D_800E07D4[D_80102D00];
                    D_800E1226 = D_800E07D4[D_80102D00 + 1];
                }
                break;
            }
        }
    }
    if ((D_800E07CC[D_80102D00 + 1] >= 0) && (D_80102D00 + 1 < D_800E0B0C) && (D_800DFF08 != 5)) {
        if (D_800E1226 < 0) {
            switch (D_800E1222) {
            case 2:
                if ((D_800DFDB4[D_800E07CC[D_80102D00 + 1]] == 0x25) && (D_800DFDA4[D_800E07CC[D_80102D00 + 1]] != 0x25)) {
                    D_800E13C0 ^= 9;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1226 = 0x44;
                    buf[0] = 0x50;
                    buf[1] = 0x4C;
                    buf[2] = 0x41;
                    buf[3] = 0x59;
                    buf[4] = 0x45;
                    buf[5] = 0x52;
                    buf[6] = 0x20;
                    buf[7] = D_80102D00 + 0x32;
                    buf[8] = 0;
                    if (func_80033504(((u8*)D_800E0784) + D_80102D00 * 9 + 9, buf) != 0) {
                        for (j = 0; j < 9; j++) {
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 9 + j] = 0;
                        }
                    }
                }
                break;
            case 3:
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1226 = D_800E07D4[D_80102D00 + 1];
                }
                break;
            case 1:
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1226 = D_800E07DC[D_80102D00 + 1];
                }
                break;
            }
        } else {
            switch (D_800E1222) {
            case 2:
                if ((D_800DFDB4[D_800E07CC[D_80102D00 + 1]] == 0x25) && (D_800DFDA4[D_800E07CC[D_80102D00 + 1]] != 0x25)) {
                    D_800E13C0 ^= 9;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x400) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    p = D_800E1160[(D_800E1226 >> 3) + D_800E13C0];
                    i = D_800E1226 & 7;
                    while (*p != 0) {
                        p++;
                        i--;
                    }
                    if (D_800E1226 < 0x40) {
                        D_800E1226 += 8;
                    } else {
                        D_800E1226 -= 0x40;
                    }
                    p = D_800E1160[(D_800E1226 >> 3) + D_800E13C0];
                    while (*p != 0) {
                        p++;
                        i++;
                    }
                    if (i < 0) {
                        i = 0;
                    }
                    D_800E1226 = (D_800E1226 & 0xF8) + i;
                    while (D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7] == 0x20) {
                        D_800E1226 += 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x800) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    p = D_800E1160[(D_800E1226 >> 3) + D_800E13C0];
                    i = D_800E1226 & 7;
                    while (*p != 0) {
                        p++;
                        i--;
                    }
                    if (D_800E1226 >= 8) {
                        D_800E1226 -= 8;
                    } else {
                        D_800E1226 += 0x40;
                    }
                    p = D_800E1160[(D_800E1226 >> 3) + D_800E13C0];
                    while (*p != 0) {
                        p++;
                        i++;
                    }
                    if (i < 0) {
                        i = 0;
                    }
                    D_800E1226 = (D_800E1226 & 0xF8) + i;
                    while (D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7] == 0x20) {
                        D_800E1226 += 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x200) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    if (!(D_800E1226 & 7)) {
                        while (D_800E1160[(D_800E1226 >> 3) + D_800E13C0][(D_800E1226 & 7) + 1] != 0) {
                            D_800E1226 += 1;
                        }
                    } else {
                        D_800E1226 -= 1;
                    }
                    while (D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7] == 0x20) {
                        D_800E1226 -= 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x100) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1226 += 1;
                    if (D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7] == 0) {
                        D_800E1226 &= 0xF8;
                    }
                    while (D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7] == 0x20) {
                        D_800E1226 += 1;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x1000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1226 = -1;
                    if (((u8*)D_800E0784)[D_80102D00 * 9 + 9] == 0) {
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 9] = 0x50;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0xA] = 0x4C;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0xB] = 0x41;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0xC] = 0x59;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0xD] = 0x45;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0xE] = 0x52;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0xF] = 0x20;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0x10] = D_80102D00 + 0x32;
                        ((u8*)D_800E0784)[D_80102D00 * 9 + 0x11] = 0;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0xA000) {
                    buf[0] = D_800E1160[(D_800E1226 >> 3) + D_800E13C0][D_800E1226 & 7];
                    if (buf[0] == 0x22) {
                        buf[0] = 0x20;
                    }
                    if (buf[0] == 0x5F) {
                        func_8007D45C(D_8010B358, D_800E2818, 3);
                        D_800E1226 = -1;
                        if (((u8*)D_800E0784)[D_80102D00 * 9 + 9] == 0) {
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 9] = 0x50;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0xA] = 0x4C;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0xB] = 0x41;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0xC] = 0x59;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0xD] = 0x45;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0xE] = 0x52;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0xF] = 0x20;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0x10] = D_80102D00 + 0x32;
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 0x11] = 0;
                        }
                    } else if (buf[0] == 0x29) {
                        func_8007D45C(D_8010B358, D_800E2818, 4);
                        if (((u8*)D_800E0784)[D_80102D00 * 9 + 9] != 0) {
                            i = 1;
                            while (((u8*)D_800E0784)[D_80102D00 * 9 + 9 + i] != 0) {
                                i++;
                            }
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 9 + i - 1] = 0;
                        }
                    } else {
                        func_8007D45C(D_8010B358, D_800E2818, 3);
                        if (((u8*)D_800E0784)[D_80102D00 * 9 + 0x10] == 0) {
                            i = 0;
                            while (((u8*)D_800E0784)[D_80102D00 * 9 + 9 + i] != 0) {
                                i++;
                            }
                            if (i < 7) {
                                ((u8*)D_800E0784)[D_80102D00 * 9 + 9 + i] = buf[0];
                                ((u8*)D_800E0784)[D_80102D00 * 9 + 9 + i + 1] = 0;
                            }
                            if (i == 6) {
                                D_800E1226 = -1;
                            }
                        }
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    if (D_80102D00 != 0) {
                        D_80102D00 -= 2;
                        D_800E1222 = 1;
                        D_800E1224 = D_800E07DC[D_80102D00];
                        D_800E1226 = D_800E07DC[D_80102D00 + 1];
                    } else {
                        if (D_800E1264 != NULL) {
                            D_800E1264->unk2C = 0.08f;
                        }
                        if (D_800E1278 != NULL) {
                            D_800E1278->unk2C = 0.08f;
                        }
                        func_8003FD78();
                        func_8003F8D8();
                    }
                }
                break;
            case 3:
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0xA00) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1226 -= 1;
                    if (D_800E1226 < 0) {
                        D_800E1226 = 6;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x500) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E1226 += 1;
                    if (D_800E1226 >= 7) {
                        D_800E1226 = 0;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0xB000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E07D4[D_80102D00 + 1] = D_800E1226;
                    D_800E1226 = -1;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1222 = 2;
                    D_800E1224 = 0x44;
                    D_800E1226 = 0x44;
                    buf[0] = 0x50;
                    buf[1] = 0x4C;
                    buf[2] = 0x41;
                    buf[3] = 0x59;
                    buf[4] = 0x45;
                    buf[5] = 0x52;
                    buf[6] = 0x20;
                    buf[7] = D_80102D00 + 0x31;
                    buf[8] = 0;
                    if (func_80033504(((u8*)D_800E0784) + D_80102D00 * 9, buf) != 0) {
                        for (j = 0; j < 9; j++) {
                            ((u8*)D_800E0784)[D_80102D00 * 9 + j] = 0;
                        }
                    }
                    buf[7] = D_80102D00 + 0x32;
                    buf[8] = 0;
                    if (func_80033504(((u8*)D_800E0784) + D_80102D00 * 9 + 9, buf) != 0) {
                        for (j = 0; j < 9; j++) {
                            ((u8*)D_800E0784)[D_80102D00 * 9 + 9 + j] = 0;
                        }
                    }
                }
                break;
            case 1:
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x200) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E07DC[D_80102D00 + 1] -= 1;
                    if (D_800E07DC[D_80102D00 + 1] < 4) {
                        D_800E07DC[D_80102D00 + 1] = 0x63;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x100) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    D_800E07DC[D_80102D00 + 1] += 1;
                    if (D_800E07DC[D_80102D00 + 1] >= 0x64) {
                        D_800E07DC[D_80102D00 + 1] = 4;
                    }
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0xB000) {
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1226 = -1;
                }
                if (D_800DFDD4[D_800E07CC[D_80102D00 + 1]] & 0x4000) {
                    func_8007D45C(D_8010B358, D_800E2818, 4);
                    D_800E1222 = 3;
                    D_800E1224 = D_800E07D4[D_80102D00];
                    D_800E1226 = D_800E07D4[D_80102D00 + 1];
                }
                break;
            }
        }
    }
    if ((D_800E1224 < 0) && ((D_800E1226 < 0) || (D_800E0B0C < D_80102D00 + 2))) {
        switch (D_800E1222) {
        case 2:
            D_800E1224 = D_800E07D4[D_80102D00];
            D_800E1226 = D_800E07D4[D_80102D00 + 1];
            D_800E1222 = 3;
            break;
        case 3:
            D_800E1224 = D_800E07DC[D_80102D00];
            D_800E1226 = D_800E07DC[D_80102D00 + 1];
            D_800E1222 = 1;
            break;
        case 1:
            if (D_80102D00 + 2 < D_800E0B0C) {
                D_80102D00 += 2;
                D_800E1224 = 0x44;
                D_800E1226 = 0x44;
                D_800E1222 = 2;
            } else {
                D_800E122A = 0;
                D_800E1232 = 0;
                D_800E1208 = 0;
                D_800E120C = 0;
                func_80065748();
            }
            break;
        }
    }
}


extern void func_80062C3C(void);
extern void func_80055A80(void);
extern void func_8005D674(void);
extern void func_8004127C(void);
extern void func_80046A9C(void);
extern void updateAndDrawRecordsMenu(void);
extern void updateAndDrawAudioMenu(void);
extern void func_80060630(void);
extern void func_80064BBC(void);
extern void func_8002A140(void);
extern void _bzero(void *, s32);
extern u8 *loadAsset(u8 *, s32, s32);
extern void func_80038284(UnkImg *);
extern void func_80037F9C(UnkImg *, u8);
extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern void loadsong(s32, u8 *);
extern void func_8007ACFC(u8 *);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern s32 func_8003E590(void);
extern void func_8003B1A4(void);
extern s32 func_80081E90(s32);
extern void func_800CC6E0(void);
extern void requestSaveDataWrite(void);
extern void func_80038A88(void);
extern void func_800335F0(void *);
extern void func_8003396C(Gfx **, UnkImg *, s32, s32, s32, s32, s32, s32);
extern void func_800353F4(Gfx **, UnkImg *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_800338B0(Gfx **);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern s32 func_800388BC(u8 *);
extern s32 func_800388F4(u8 *);
extern void func_80038478(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern void func_800384E4(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern void func_800382B4(Gfx **, u8, s32, s32, u8 *, s32, s32, s32, s32);
extern void func_8007D45C(void *, void *, s32);
extern void func_8003E460(void);
extern void func_8003E5F4(void);
extern void func_8003FD78(void);
extern void func_8003F8D8(void);
extern f32 sinf(f32);
extern f32 __cosf(f32);
extern void guRotateRPYF_2(f32 mf[4][4], f32 r, f32 p, f32 h);

extern s32 D_800DF710;
extern s32 D_800DF714;
extern u8 D_800DF770;
extern s16 D_800DFD48;
extern s16 D_800DFD4C;
extern s32 D_800DFD90;
extern s32 D_800DFD98;
extern s16 D_800DFDFC;
extern u16 D_800DFF08;
extern s16 D_800E0754[];
extern s16 D_800E0756[];
extern s32 D_800E0760;
extern s16 D_800E0768;
extern s16 D_800E076C;
extern s8 D_800E07CC[8];
extern s32 D_800E088C;
extern s32 D_800E0B0C;
extern s32 D_800E0B10;
extern s32 D_800E0B20;
extern s32 D_800E0B24;
extern u8 *D_800E1010;
extern void *D_800E1014;
extern s32 D_800E1018;
extern void *D_800E1024;
extern void *D_800E1028;
extern void *D_800E10AC;
extern s32 D_800E10B4;
extern u8 *D_800E10B8[];
extern u16 D_800E10F4[];
extern u16 D_800E110C[];
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s32 D_800E1214;
extern s32 D_800E1218;
extern s16 D_800E121C;
extern s16 D_800E121E;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E1228;
extern s16 D_800E122C;
extern s16 D_800E122E;
extern s16 D_800E1230;
extern s16 D_800E1232;
extern s16 D_800E1236;
extern s16 D_800E1240;
extern s16 D_800E1242;
extern s16 D_800E1244;
extern s32 D_800E1250;
extern s32 D_800E1258;
extern s32 D_800E1260;
extern Obj *D_800E1264;
extern Obj *D_800E1280[];
extern s16 D_800E12E4;
extern s32 D_800E12FC;
extern u8 D_800E13A8;
extern u8 D_800E13AC;
extern s16 D_800E149C;
extern s16 D_800E14A0;
extern s16 D_800E14A4;
extern u8 D_800E2818[];
extern s32 D_800E4480;
extern s16 D_800E4498;
extern s16 D_800E449C;
extern s16 D_800E44A0;
extern s16 D_800E44A4;
extern s16 D_800E44A8;
extern s16 D_800E44AC;
extern u16 D_800E94B0;
extern u8 D_800ECC44[];
extern u8 D_800ECC4C[];
extern u8 D_800ECC50[];
extern u8 D_800ECC5C[];
extern u8 D_800ECC68[];
extern u8 D_800ECC74[];
extern u8 D_800ECC90[];
extern u8 D_800ECCB0[];
extern u8 D_800ECCD0[];
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern s16 D_80102664;
extern u8 D_80102698;
extern f32 D_8010269C;
extern u8 **D_801026A0;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern u8 D_80102918[];
extern f32 D_80102B28[16];
extern f32 D_80102B68[16];
extern f32 D_80102BB0[16];
extern f32 D_80102BF8[16];
extern u8 D_80107290[];
extern u8 D_8010B358[];
extern u8 D_80110220[];
extern s16 D_801125C6;
extern s32 D_80112D18;
extern s8 D_80113320;
extern s8 D_80113322;
extern s8 D_80113323;
extern s32 D_80113328;
extern u8 D_80113488[];
extern s16 D_8015D980;
extern u8 D_736C50[];
extern u16 D_800E121C_u16; /* alias of D_800E121C @ 0x800E121C — jtbl switch needs a bare lhu */
extern u16 D_800E1220_u16; /* alias of D_800E1220 @ 0x800E1220 — jtbl switch needs a bare lhu */

void func_8004C7E8(void) {
    s32 sp6C;
    s32 sp68;
    u8 sp54[0x14];

    if (D_800E1236 >= 0) {
        func_80062C3C();
        return;
    }
    if (D_800E1230 >= 0) {
        func_80055A80();
        return;
    }
    if (D_800E122E >= 0) {
        func_8005D674();
        return;
    }
    if (D_800E1222 >= 0) {
        if ((D_8015D980 == 1) || (D_800E44A8 == 6)) {
            func_8004127C();
        } else {
            func_80046A9C();
        }
        return;
    }
    if (D_800E122C >= 0) {
        updateAndDrawRecordsMenu();
        return;
    }
    if (D_800E1228 >= 0) {
        updateAndDrawAudioMenu();
        return;
    }
    if (D_800E1232 >= 0) {
        func_80060630();
        return;
    }
    if (D_800E121E >= 0) {
        func_80064BBC();
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        _bzero(D_80110220, 0x3268);
        _bzero(D_80113488, 0x3268);
        D_800DFDFC = 1;
        D_800E149C = 0;
        D_800E1018 = loadAsset(D_736C50, 0x17, 8);
        D_800E1024 = loadAsset(D_736C50, 0x18, 8);
        (&D_800E1010)[3] = loadAsset(D_736C50, 0x19, 8);
        (&D_800E1010)[4] = loadAsset(D_736C50, 0x47, 8);
        (&D_800E1010)[8] = loadAsset(D_736C50, 0xD, 8);
        D_800E1028 = loadAsset(D_736C50, 0x4E, 8);
        D_800E10B4 = loadAsset(D_736C50, 0x97, 8);
        D_800E10AC = loadAsset(D_736C50, 0x73, 8);
        D_800E1014 = loadAsset(D_736C50, 0x39, 8);
        func_80038284(D_800E1014);
        D_800E1014 = loadAsset(D_736C50, 0xC2, 8);
        func_80037F9C(D_800E1014, 2);
        if (D_800E1220 >= 0) {
            switch (D_800E121C) {
            case 0:
                D_8015D980 = 1;
                D_800E12FC = 6;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0xBC);
                D_800E1250 = 0;
                break;
            case 1:
                D_8015D980 = 2;
                D_800E12FC = D_800E12E4 + 2;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0x1DC);
                break;
            case 3:
                D_800E12FC = 4;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0xD4);
                D_800E1250 = 0;
                break;
            case 4:
                D_800E12FC = 3;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0x1D0);
                D_800E1250 = 0;
                break;
            }
        } else {
            D_800E1250 = 0;
        }
        for (sp6C = 0; sp6C < 0xC; sp6C++) {
            D_800E1258 = (s32) loadAnim(D_800E110C[sp6C]);
            D_800E1260 = (s32) loadMesh(D_800E10F4[sp6C]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1280[sp6C] = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E1258, (void **)((u8 *)&D_800E1010 + 0x250), 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            D_800E1280[sp6C]->unk48 = 1;
        }
        D_800E1258 = (s32) loadAnim(0x58);
        D_800E1260 = (s32) loadMesh(0x1F);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E1258, (void **)((u8 *)&D_800E1010 + 0x250), 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1264->unk48 = 1;
        D_800E11FC = 0;
        D_8010269C = 360.0f;
        D_800E1242 = 0;
        if (D_800E0B20 != 2) {
            loadsong(D_800E94B0, D_80107290);
        } else {
            loadsong(D_800E0B24, D_80107290);
        }
        func_8007ACFC(D_80107290);
        D_800E1218 = -1;
        D_800E076C = 0;
        D_800E1214 = 0;
        func_8003FC6C(0x29, 0x3C, 0x52, 0xDC, 0xFF, 0, 0xFF, 0, 0xC0);
    }
    if (D_800E121C == 0) {
        D_800E1220 = -1;
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if ((D_800E121C == 1) && (D_800E1220 >= 0) && (func_8003E590() != 0)) {
        D_800E1240 = 0x40;
    } else {
        D_800E1240 = 0xFF;
    }
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        if (D_800E44A8 == 3) {
            if (D_80113323 != 0) {
                D_800E44A0 = 0;
                D_800E449C = D_800E14A4;
                D_800E4498 = D_800E449C;
                D_800E14A4 = (D_800E14A4 + 1) & 3;
                D_800E44AC = 1;
                D_800E076C = 0;
                D_800E14A0 += 1;
            } else {
                D_800E076C = 0;
                D_80102918[0] |= 1;
                requestSaveDataWrite();
            }
        } else {
            D_80113323 = 0;
        }
        D_800E4480 = 0;
        if (D_800E44A8 == 0xA) {
            D_800DFD48 = 0x384;
            D_800E14A0 += 1;
            D_800E44A0 = func_80081E90(3);
            D_800E449C = func_80081E90(4) + 3;
            D_800E4498 = D_800E449C;
            D_80102664 = D_800E1220 >= 0;
            if (D_800DF770 & 1) {
                D_80113320 = 0;
            } else if (D_800DF770 & 2) {
                D_80113320 = 1;
            } else if (D_800DF770 & 4) {
                D_80113320 = 2;
            } else if (D_800DF770 & 8) {
                D_80113320 = 3;
            }
            D_80113323 = 1;
            D_80113328 = (s32) D_800ECC44;
            D_80113322 = func_80081E90(7);
            D_801125C6 = 1;
            func_800CC6E0();
            D_80112D18 = 0;
        } else {
            D_80113320 = D_800E07CC[D_800E0B10];
            D_80113328 = (s32) D_800ECC4C;
            D_80113322 = 4;
            D_801125C6 = 1;
            func_800CC6E0();
            D_80112D18 = 0;
        }
        D_800E121C = -1;
        D_800E1220 = -1;
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, D_800E1024, 0, 0x22, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E1240) / 255);
    func_8003396C(&D_800F22B4, D_800E1018, 0, 0xAA, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E1240) / 255);
    func_800353F4(&D_800F22B4, (UnkImg *)(&D_800E1010)[3], 0, 0, 0x30, ((UnkImg *)(&D_800E1010)[3])->height - 1, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, (D_800E1202 * D_800E1240) / 255);
    func_800353F4(&D_800F22B4, (UnkImg *)(&D_800E1010)[4], 0, 0, 0x30, ((UnkImg *)(&D_800E1010)[4])->height - 1, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, (D_800E1202 * D_800E1240) / 255);
    func_800338B0(&D_800F22B4);
    if ((D_800E1220 < 0) || (D_800E121C == 1)) {
        if (D_800E1218 < 0) {
            D_800E1244 = D_800E121C;
        } else if (D_800E121C == 3) {
            D_800E1244 = D_800E0754[4] + 5;
        } else if (D_800E121C == 4) {
            D_800E1244 = D_800E0754[5] + 9;
        }
    } else if (D_800E121C == 3) {
        D_800E1244 = D_800E1220 + 5;
    } else if (D_800E121C == 4) {
        D_800E1244 = D_800E1220 + 9;
    }
    for (sp6C = D_800E1210; sp6C < D_800E1208; sp6C++) {
        if (D_8010269C > 130.0) {
            D_8010269C += 5.0;
        }
        if ((D_8010269C == 130.0) && (D_800E1244 != D_800E1242)) {
            D_8010269C += 5.0;
        }
        if (D_8010269C < 130.0) {
            D_8010269C += 5.0;
            if (D_8010269C > 130.0) {
                D_8010269C = 130.0f;
            }
        }
        if (D_8010269C >= 180.0) {
            D_800E1242 = D_800E1244;
            D_800E1280[D_800E1242]->unk24 = 0;
            D_8010269C = 0.0f;
        }
    }
    guRotateRPYF_2(D_80102B28, sinf(D_8010269C * 3.1415 / 180.0) * 20.0, D_8010269C, 0.0f);
    guTranslateF(D_80102B68, -180.0f, 30.0f, 0.0f);
    if (D_8010269C < 40.0) {
        guTranslateF(D_80102BF8, 0.0f, 0.0f, (1.0 - __cosf((D_8010269C - 40.0) * 6.283 / 180.0)) * 50.0);
    } else if (D_8010269C <= 130.0) {
        guTranslateF(D_80102BF8, 0.0f, 0.0f, 0.0f);
    } else {
        guTranslateF(D_80102BF8, 0.0f, 0.0f, (1.0 - __cosf((D_8010269C - 130.0) * 6.283 / 180.0)) * 50.0);
    }
    guScaleF(D_80102BB0, 0.7f, 0.7f, 0.7f);
    guMtxCatF(D_80102BB0, D_80102B28, D_80102B28);
    guMtxCatF(D_80102BF8, D_80102B28, D_80102BF8);
    LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, D_80102B28, D_80102B68);
    D_800E1280[D_800E1242]->unk28 = ((D_8010269C > 40.0) && (D_8010269C <= 130.0)) ? 0.0 : 0.01;
    if (LWPlayAnimation(D_800E1280[D_800E1242], D_800E1208 - D_800E1210, D_80102BF8, D_80102B68) != 0) {
        D_800E1280[D_800E1242]->unk24 = 0;
    }
    func_800335F0(&D_800F22B4);
    if (D_800E1220 < 0) {
        for (sp6C = 0; sp6C < 5; sp6C++) {
            sp68 = D_800E1202;
            if (D_800E121C == sp6C) {
                if (D_800E1218 < 0) {
                    func_80038478(&D_800F22B4, (-(sp6C * 7) - func_800388BC(D_800E10B8[sp6C])) + 0x108, (sp6C * 0x13) + 0x3C, D_800E10B8[sp6C], 0xFF, 0xFF, 0xFF, D_80102698);
                } else {
                    func_800384E4(&D_800F22B4, ((-(sp6C * 7) - func_800388F4(D_800E10B8[sp6C])) - ((0xF - D_800E1218) >> 1)) + 0x108, (sp6C * 0x13) + ((0xF - D_800E1218) >> 1) + 0x3C, D_800E10B8[sp6C], 0xFF, 0xFF, 0xFF, (sp68 * D_800E1218) / 15);
                    func_800384E4(&D_800F22B4, (-(sp6C * 7) - func_800388F4(D_800E10B8[sp6C])) + ((0xF - D_800E1218) >> 1) + 0x108, ((sp6C * 0x13) - ((0xF - D_800E1218) >> 1)) + 0x3C, D_800E10B8[sp6C], 0xFF, 0xFF, 0xFF, (sp68 * D_800E1218) / 15);
                    func_80038478(&D_800F22B4, (-(sp6C * 7) - func_800388BC(D_800E10B8[sp6C])) + 0x108, (sp6C * 0x13) + 0x3C, D_800E10B8[sp6C], 0xFF, 0xFF, 0xFF, (D_80102698 * D_800E1218) / 15);
                }
            } else if (D_800E1218 < 0) {
                func_80038478(&D_800F22B4, (-(sp6C * 7) - func_800388BC(D_800E10B8[sp6C])) + 0x108, (sp6C * 0x13) + 0x3C, D_800E10B8[sp6C], 0xE6, 0x61, 0x1E, sp68);
            } else {
                func_80038478(&D_800F22B4, (-(sp6C * 7) - func_800388BC(D_800E10B8[sp6C])) + 0x108, (sp6C * 0x13) + 0x3C, D_800E10B8[sp6C], 0xE6, 0x61, 0x1E, (sp68 * D_800E1218) / 15);
            }
            if (sp6C < 4) {
                func_8003396C(&D_800F22B4, (UnkImg *)(&D_800E1010)[8], 0x98 - (sp6C * 7), (sp6C * 0x13) + 0x4A, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E1218) / 15);
            }
        }
    }
    if ((D_800E1220 >= 0) || (D_800E1218 >= 0)) {
        if (D_800E1218 < 0) {
            func_800353F4(&D_800F22B4, (UnkImg *)(&D_800E1010)[3], 0x31, 0, ((UnkImg *)(&D_800E1010)[3])->width - 1, ((UnkImg *)(&D_800E1010)[3])->height - 1, 0xFF, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
            func_800353F4(&D_800F22B4, (UnkImg *)(&D_800E1010)[4], 0x31, 0, ((UnkImg *)(&D_800E1010)[4])->width - 1, ((UnkImg *)(&D_800E1010)[4])->height - 1, 0xFF, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
        } else {
            func_800353F4(&D_800F22B4, (UnkImg *)(&D_800E1010)[3], 0x31, 0, ((UnkImg *)(&D_800E1010)[3])->width - 1, ((UnkImg *)(&D_800E1010)[3])->height - 1, 0xFF, 0xD2, 0xE6, 0x61, 0x1E, (D_800E1202 * (0xF - D_800E1218)) / 15);
            func_800353F4(&D_800F22B4, (UnkImg *)(&D_800E1010)[4], 0x31, 0, ((UnkImg *)(&D_800E1010)[4])->width - 1, ((UnkImg *)(&D_800E1010)[4])->height - 1, 0xFF, 0xD2, 0xFF, 0xDC, 0x3E, (D_800E1202 * (0xF - D_800E1218)) / 15);
        }
        if ((D_800E121C == 1) && (D_800E1250 != 0)) {
            sp54[0] = D_800E0B0C + 0x30;
            sp54[1] = 0;
            sp6C = func_800388BC(D_800ECC50);
            if (D_800E1218 < 0) {
                func_8003396C(&D_800F22B4, D_800E1028, 0x8E, 0x62, 0xFF, 0xFF, 0xFF, (((D_800E1202 * D_800E13AC) / 255) * D_800E1240) / 255);
                func_8003396C(&D_800F22B4, D_800E10B4, 0x8E, 0x62, 0xFF, 0xFF, 0xFF, (((D_800E1202 * D_800E13A8) / 255) * D_800E1240) / 255);
                func_80038478(&D_800F22B4, (-sp6C - func_800388BC(sp54)) + 0xFA, 0x62, sp54, 0xFF, 0xFF, 0xFF, (D_80102698 * D_800E1240) / 255);
                func_80038478(&D_800F22B4, 0xFA - sp6C, 0x62, D_800ECC5C, 0xE6, 0x61, 0x1E, (D_800E1202 * D_800E1240) / 255);
            } else {
                func_8003396C(&D_800F22B4, D_800E1028, 0x8E, 0x62, 0xFF, 0xFF, 0xFF, (D_800E1202 * (0xF - D_800E1218) * D_800E13AC) / 3825);
                func_8003396C(&D_800F22B4, D_800E10B4, 0x8E, 0x62, 0xFF, 0xFF, 0xFF, (D_800E1202 * (0xF - D_800E1218) * D_800E13A8) / 3825);
                func_80038478(&D_800F22B4, (-sp6C - func_800388BC(sp54)) + 0xFA, 0x62, sp54, 0xFF, 0xFF, 0xFF, (D_80102698 * (0xF - D_800E1218)) / 15);
                func_80038478(&D_800F22B4, 0xFA - sp6C, 0x62, D_800ECC68, 0xE6, 0x61, 0x1E, (D_800E1202 * (0xF - D_800E1218)) / 15);
            }
        } else {
            for (sp6C = 0; sp6C < D_800E12FC; sp6C++) {
                sp68 = D_800E1202;
                if (D_800E1218 < 0) {
                    if (D_800E1220 == sp6C) {
                        func_80038478(&D_800F22B4, ((-(sp6C * 7) - func_800388BC(D_801026A0[sp6C])) - (((-D_800E12FC * 7) + 0x1C) / 2)) + 0x104, ((sp6C * 0x13) - ((D_800E12FC * 0x13) / 2)) + 0x6B, D_801026A0[sp6C], 0xFF, 0xFF, 0xFF, (D_80102698 * D_800E1240) / 255);
                    } else {
                        func_80038478(&D_800F22B4, ((-(sp6C * 7) - func_800388BC(D_801026A0[sp6C])) - (((-D_800E12FC * 7) + 0x1C) / 2)) + 0x104, ((sp6C * 0x13) - ((D_800E12FC * 0x13) / 2)) + 0x6B, D_801026A0[sp6C], 0xE6, 0x61, 0x1E, (D_800E1240 * sp68) / 255);
                    }
                    if (sp6C < (D_800E12FC - 1)) {
                        func_8003396C(&D_800F22B4, (UnkImg *)(&D_800E1010)[8], (-(sp6C * 7) - (((-D_800E12FC * 7) + 0x1C) / 2)) + 0x94, ((sp6C * 0x13) - ((D_800E12FC * 0x13) / 2)) + 0x79, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E1240) / 255);
                    }
                } else {
                    if (D_800E1220 == sp6C) {
                        func_80038478(&D_800F22B4, ((-(sp6C * 7) - func_800388BC(D_801026A0[sp6C])) - (((-D_800E12FC * 7) + 0x1C) / 2)) + 0x104, ((sp6C * 0x13) - ((D_800E12FC * 0x13) / 2)) + 0x6B, D_801026A0[sp6C], 0xFF, 0xFF, 0xFF, (D_80102698 * (0xF - D_800E1218)) / 15);
                    } else {
                        func_80038478(&D_800F22B4, ((-(sp6C * 7) - func_800388BC(D_801026A0[sp6C])) - (((-D_800E12FC * 7) + 0x1C) / 2)) + 0x104, ((sp6C * 0x13) - ((D_800E12FC * 0x13) / 2)) + 0x6B, D_801026A0[sp6C], 0xE6, 0x61, 0x1E, ((s32) sp68 * (0xF - D_800E1218)) / 15);
                    }
                    if (sp6C < (D_800E12FC - 1)) {
                        func_8003396C(&D_800F22B4, (UnkImg *)(&D_800E1010)[8], (-(sp6C * 7) - (((-D_800E12FC * 7) + 0x1C) / 2)) + 0x94, ((sp6C * 0x13) - ((D_800E12FC * 0x13) / 2)) + 0x79, 0xFF, 0xFF, 0xFF, (D_800E1202 * (0xF - D_800E1218)) / 15);
                    }
                }
            }
        }
    }
    if ((D_800E121C == 1) && (D_800E1220 >= 0) && (func_8003E590() != 0)) {
        func_8003396C(&D_800F22B4, D_800E10AC, 0x14, 0x3C, 0xFF, 0xFF, 0xFF, D_800E1202);
        func_800382B4(&D_800F22B4, 2, 0x3E, 0x4B, D_800ECC74, 0xFF, 0xDC, 0x3E, D_800E1202);
        func_800382B4(&D_800F22B4, 2, 0x37, 0x5F, D_800ECC90, 0xE6, 0x61, 0x1E, D_800E1202);
        func_800382B4(&D_800F22B4, 2, 0x32, 0x6D, D_800ECCB0, 0xE6, 0x61, 0x1E, D_800E1202);
        func_800382B4(&D_800F22B4, 2, 0x2D, 0x7B, D_800ECCD0, 0xE6, 0x61, 0x1E, D_800E1202);
    }
    func_800338B0(&D_800F22B4);
    if (D_800E1220 < 0) {
        if (D_800E1218 < 0) {
            if (D_800DFD98 & 0x400) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                if (D_800E121C < 4) {
                    D_800E121C += 1;
                } else {
                    D_800E121C = 0;
                }
                D_800E0754[0] = D_800E121C;
            }
            if (D_800DFD98 & 0x800) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                if (D_800E121C > 0) {
                    D_800E121C -= 1;
                } else {
                    D_800E121C = 4;
                }
                D_800E0754[0] = D_800E121C;
            }
            if (D_800DFD98 & 0xB000) {
                switch (D_800E121C_u16) {
                case 0:
                    D_8015D980 = 1;
                    func_8003E460();
                    D_800E1222 = 0;
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    break;
                case 1:
                    D_800E1218 = 0xF;
                    D_800E12FC = D_800E12E4 + 2;
                    D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0x1DC);
                    break;
                case 2:
                    D_8015D980 = 1;
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E1222 = 0;
                    D_800E4498 = 0;
                    D_800E449C = 0;
                    D_800E44A0 = 0;
                    func_8003E460();
                    D_800E44A8 = 0xC;
                    D_800E1222 = -1;
                    D_800E1232 = 0;
                    break;
                case 3:
                    D_800E1218 = 0xF;
                    D_800E12FC = 4;
                    D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0xD4);
                    break;
                case 4:
                    D_800E1218 = 0xF;
                    D_800E12FC = 3;
                    D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0x1D0);
                    break;
                }
                func_8007D45C(D_8010B358, D_800E2818, 3);
            }
        }
        if (D_800E1218 == 0) {
            D_800E1218 = -1;
            switch (D_800E121C) {
            case 0:
                D_8015D980 = 1;
                D_800E12FC = 6;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0xBC);
                D_800E1220 = D_800E0754[1];
                break;
            case 1:
                D_8015D980 = 2;
                D_800E12FC = D_800E12E4 + 2;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0x1DC);
                D_800E1220 = D_800E0754[2];
                break;
            case 3:
                D_800E12FC = 4;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0xD4);
                D_800E1220 = D_800E0754[4];
                break;
            case 4:
                D_800E12FC = 3;
                D_801026A0 = (u8 **)((u8 *)&D_800E1010 + 0x1D0);
                D_800E1220 = D_800E0754[5];
                break;
            }
        }
    } else if (D_800E1218 < 0) {
        if ((D_800E121C != 1) || (D_800E1220 < 0) || (func_8003E590() == 0)) {
            if ((D_800E121C == 1) && (D_800E1250 != 0)) {
                if (D_800DFD98 & 0x800) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    if (D_800E0B0C < 8) {
                        D_800E0B0C += 1;
                    } else {
                        D_800E0B0C = 2;
                    }
                }
                if (D_800DFD98 & 0x400) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    if (D_800E0B0C >= 3) {
                        D_800E0B0C -= 1;
                    } else {
                        D_800E0B0C = 8;
                    }
                }
            } else {
                if (D_800DFD98 & 0x400) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    if (D_800E1220 < (D_800E12FC - 1)) {
                        D_800E1220 += 1;
                    } else {
                        D_800E1220 = 0;
                    }
                }
                if (D_800DFD98 & 0x800) {
                    func_8007D45C(D_8010B358, D_800E2818, 2);
                    if (D_800E1220 > 0) {
                        D_800E1220 -= 1;
                    } else {
                        D_800E1220 = D_800E12FC - 1;
                    }
                }
                D_800E0756[D_800E121C] = D_800E1220;
            }
            if (D_800DFD98 & 0xB000) {
                switch (D_800E121C) {
                case 0:
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_8015D980 = 1;
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E1222 = 0;
                    D_800E4498 = 0;
                    D_800E449C = 0;
                    D_800E44A0 = 0;
                    D_800DFD4C = 1;
                    switch (D_800E1220_u16) {
                    case 0:
                        D_800E44A8 = 1;
                        break;
                    case 1:
                        D_800E44A8 = 5;
                        break;
                    case 2:
                        D_800E44A8 = 9;
                        D_800DFD4C = 2;
                        break;
                    case 3:
                        D_800E44A8 = 4;
                        break;
                    case 4:
                        D_800E44A8 = 2;
                        break;
                    case 5:
                        D_800E44A4 = 1;
                        D_8015D980 = 2;
                        D_800E44A8 = 6;
                        D_800E088C = 0;
                        break;
                    }
                    break;
                case 1:
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    if (D_800E1220 == 1) {
                        D_800E121E = 0;
                        D_800E1208 = 0;
                        D_800E120C = 0;
                        break;
                    }
                    D_8015D980 = 2;
                    func_8003E5F4();
                    D_800E4498 = 0;
                    D_800E449C = 0;
                    D_800E44A0 = 0;
                    D_800DFD4C = 1;
                    if (D_800E1220 != 0) {
                        D_800DFD4C = 2;
                    }
                    D_800E44A8 = 7;
                    if (D_800E1250 != 0) {
                        D_800E1208 = 0;
                        D_800E120C = 0;
                        D_800E1222 = 0;
                    } else {
                        D_800E1250 = 1;
                    }
                    D_800E088C = 0;
                    break;
                case 3:
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    switch (D_800E1220) {
                    case 0:
                        D_800E1228 = 0;
                        break;
                    case 1:
                        D_800E1230 = 0;
                        break;
                    case 2:
                        D_800E122C = 0;
                        D_800E0760 = 0;
                        break;
                    case 3:
                        D_800E1236 = 0;
                        D_800E1208 = 0;
                        D_800E120C = 0;
                        break;
                    }
                    break;
                case 4:
                    func_8007D45C(D_8010B358, D_800E2818, 3);
                    D_8015D980 = 1;
                    D_800E0B10 = 0;
                    func_8003E460();
                    D_800E44A8 = 3;
                    D_80113323 = 0;
                    switch (D_800E1220) {
                    case 0:
                        D_800E44AC = 1;
                        break;
                    case 1:
                        D_800E44AC = 2;
                        break;
                    case 2:
                        D_800E44AC = 3;
                        break;
                    }
                    D_800E4498 = 0;
                    D_800E449C = 0;
                    D_800E44A0 = 0;
                    func_8003FD78();
                    func_8003F8D8();
                    break;
                }
            }
        }
        if (D_800DFD98 & 0x4000) {
            func_8007D45C(D_8010B358, D_800E2818, 4);
            if (D_800E1250 != 0) {
                D_800E1250 = 0;
            } else {
                D_800E1220 = -1;
            }
        }
    }
    if ((D_800DFD90 != 0) || (D_800DF770 == 0)) {
        D_800E0768 = 0;
        D_800E1214 = D_800E1208;
    }
    if ((D_800E1208 - D_800E1214) >= D_800DFD48) {
        D_8015D980 = 1;
        D_800E0B10 = 0;
        D_80113323 = 1;
        if ((D_800E14A0 % 6) != 0) {
            D_800E44A8 = 0xA;
            D_800DFD4C = 1;
        } else {
            D_800E44A8 = 3;
        }
        func_8003FD78();
        func_8003F8D8();
    }
}


extern void func_800338B0(Gfx **gdl);
extern void func_8003396C(Gfx **gdl, UnkImg *img, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a);
extern void func_80038284(UnkImg *img);
extern void func_80038478(Gfx **gdl, s32 x, s32 y, u8 *str, s32 r, s32 g, s32 b, s32 a);
extern s32 func_800388BC(u8 *str);
extern void func_80038A88(void);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8003FD78(void);
extern void func_8003F8D8(void);
extern void func_8003B1A4(void);
extern void func_8002A140(void);
extern u8 *loadAsset(u8 *, s32, s32);
extern void func_800335F0(void *);
extern void func_8007ACFC(u8 *);
extern void func_8007D45C(void *, void *, s32);
extern void updateAndDrawRecordsMenu(void);
extern s32 insertRankedRecord(u16, u8 *, u32, s32);

extern u8 D_736C50[];
extern s32 D_800DF710;
extern s32 D_800DF714;
extern u32 D_800DFDD4[];
extern u16 D_800DFF08;
extern s32 D_800E0760;
extern s8 D_800E07CC[8];
extern s16 D_800E08A8;
extern s16 D_800E08AC;
extern s16 D_800E08B0;
extern u8 *D_800E0FC8[];
extern u8 *D_800E0FE8[];
extern u8 *D_800E1010;
extern void *D_800E1014;
extern s32 D_800E10A0;
extern s32 D_800E10A4;
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s16 D_800E122A;
extern s16 D_800E122C;
extern s16 D_800E123E;
extern u8 D_800E2818[];
extern s16 D_800E4498;
extern s16 D_800E44A8;
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern s16 D_801026A4;
extern s32 D_801026B8;
extern s32 D_80102D08[];
extern s32 D_80102D28[];
extern u8 D_80107290[];
extern u8 D_8010B358[];
extern s32 D_80112D18;
extern s32 D_80112D2C;
extern s32 D_80112E90;
extern s16 D_80112E98;
extern s32 D_80112E9C;
extern s32 D_80112EA0;
extern s16 D_80112EA4;
extern s16 D_80112EA6;
extern s16 D_80112EA8;
extern s8 D_80113321;
extern s32 D_80113328;
extern s32 D_80115F80;
extern s16 D_80116100;
extern s32 D_80116104;
extern s16 D_8011610C;
extern s16 D_8011610E;
extern s16 D_80116110;
extern s16 D_8015D980;

void func_8004FBF8(void) {
    s32 i;
    s32 pos;
    s32 val;
    s32 pad0;
    s32 digits;
    s32 pad1;
    s32 pad2;
    s32 x;
    s32 y;
    s32 n;
    u8 buf[32];

    if (D_800E122C >= 0) {
        updateAndDrawRecordsMenu();
        if (D_800E122C < 0) {
            D_800E122A = -1;
        }
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E10A0 = loadAsset(D_736C50, 0x32, 8);
        D_800E10A4 = loadAsset(D_736C50, 0x33, 8);
        if (D_8015D980 == 2) {
            (&D_800E1010)[0x10] = loadAsset(D_736C50, 0x40, 8);
        } else {
            (&D_800E1010)[0x10] = loadAsset(D_736C50, 0x6C, 8);
        }
        D_800E1014 = loadAsset(D_736C50, 0xC2, 8);
        func_80038284(D_800E1014);
        func_8007ACFC(D_80107290);
        D_800E11FC = 0;
        if (D_8015D980 == 1) {
            D_80102D08[0] = D_80112D18;
            D_80102D08[1] = D_80112E90;
            D_80102D08[2] = D_80112E98;
            D_80102D08[3] = D_80112EA8;
            D_80102D08[4] = D_80112E9C;
            D_80102D08[5] = D_80112EA0;
            D_80102D08[6] = D_80112EA4;
            D_80102D08[7] = D_800E4498;
        } else {
            D_80102D08[0] = D_80112D2C / 60;
            if (D_80102D08[0] >= 0x1770) {
                D_80102D08[0] = 0x176F;
            }
            D_80102D08[1] = D_80112E98;
            D_80102D08[2] = D_80112EA8;
            D_80102D08[3] = D_80112E9C;
            D_80102D08[4] = D_80112EA6;
            D_80102D08[5] = D_80112EA4;
            D_80102D08[6] = D_80112D18;
            D_80102D28[1] = D_80116100;
            D_80102D28[2] = D_80116110;
            D_80102D28[3] = D_80116104;
            D_80102D28[4] = D_8011610E;
            D_80102D28[5] = D_8011610C;
            D_80102D28[6] = D_80115F80;
        }
        if (D_8015D980 == 1) {
            D_801026A4 = D_800E07CC[0];
        }
        func_8003FC6C(0x17, 0x46, 0x37, 0xDC, 0xFF, 0, 0xFF, 0x28, 0xE1);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E1208 = 0;
        D_800E120C = 0;
        D_800E122A = -1;
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, D_800E10A4, 0, 0x1B, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E10A0, 0x2D, 0x14, 0xFF, 0xFF, 0xFF, D_800E1202);
    D_800E123E = (D_800E1208 - 0x64) / 15;
    if (D_800E123E < 0) {
        D_800E123E = 0;
    }
    y = 0x34;
    x = 0x2D;
    if (D_8015D980 == 1) {
        n = 8;
    } else {
        n = 7;
    }
    for (i = 0; i < n; i++) {
        if ((i < 2 && D_8015D980 == 1) || (D_8015D980 == 2 && i == 6)) {
            digits = 0;
            buf[0x1E] = 0x30;
            buf[0x1F] = 0;
            pos = 0x1E;
        } else {
            digits = -1;
            buf[0x1F] = 0;
            pos = 0x1F;
        }
        val = D_80102D08[i];
        if ((i >= 2 && D_8015D980 == 1) || (D_8015D980 == 2 && i < 6) || val > 0) {
            do {
                digits++;
                if (digits != 0 && digits % 3 == 0) {
                    pos--;
                    buf[pos] = 0x20;
                }
                pos--;
                buf[pos] = val % 10 + 0x30;
                val = val / 10;
            } while (val > 0);
        }
        if (D_8015D980 == 1) {
            func_80038478(&D_800F22B4, x, y, D_800E0FC8[i], 0xE6, 0x61, 0x1E, D_800E1202);
            func_80038478(&D_800F22B4, (x - func_800388BC(pos + buf)) + 0xE6, ((i < 2) ? 0xD : 0) + y, pos + buf, 0xFF, 0xDC, 0x3E, D_800E1202);
        } else if (i == 0) {
            buf[0] = 'T';
            buf[1] = 'I';
            buf[2] = 'M';
            buf[3] = 'E';
            buf[4] = ' ';
            buf[5] = D_80102D08[i] / 600 + 0x30;
            buf[6] = (D_80102D08[i] / 60) % 10 + 0x30;
            buf[7] = ':';
            buf[8] = (D_80102D08[i] / 10) % 6 + 0x30;
            buf[9] = D_80102D08[i] % 10 + 0x30;
            buf[10] = 0;
            pos = func_800388BC(buf) >> 1;
            buf[4] = 0;
            func_80038478(&D_800F22B4, (x - pos) + 0x73, y, buf, 0xE6, 0x61, 0x1E, D_800E1202);
            func_80038478(&D_800F22B4, ((x + pos) - func_800388BC(buf + 5)) + 0x73, y, buf + 5, 0xFF, 0xFF, 0xFF, D_800E1202);
        } else {
            func_80038478(&D_800F22B4, ((0xE6 - func_800388BC(D_800E0FE8[i])) >> 1) + x, y, D_800E0FE8[i], 0xE6, 0x61, 0x1E, D_800E1202);
            func_80038478(&D_800F22B4, x, (i < 6) ? y : y + 0xD, pos + buf, 0xFF, 0xDC, 0x3E, D_800E1202);
            if (i == 6) {
                digits = 0;
                buf[0x1E] = 0x30;
                buf[0x1F] = 0;
                pos = 0x1E;
            } else {
                digits = -1;
                buf[0x1F] = 0;
                pos = 0x1F;
            }
            val = D_80102D28[i];
            if (i < 6 || val > 0) {
                do {
                    digits++;
                    if (digits != 0 && digits % 3 == 0) {
                        pos--;
                        buf[pos] = 0x20;
                    }
                    pos--;
                    buf[pos] = val % 10 + 0x30;
                    val = val / 10;
                } while (val > 0);
            }
            func_80038478(&D_800F22B4, (x - func_800388BC(pos + buf)) + 0xE6, (i < 6) ? y : y + 0xD, pos + buf, 0x2A, 0xE6, 0xFF, D_800E1202);
        }
        if ((i < 2 && D_8015D980 == 1) || (D_8015D980 == 2 && i == 6)) {
            y += 0x1E;
        } else if (D_8015D980 == 1) {
            y += 0x11;
        } else {
            y += 0x14;
        }
        if (i < n - 1 && (D_8015D980 == 1 || i > 0)) {
            func_8003396C(&D_800F22B4, (&D_800E1010)[0x10], x - 5, y - 5, 0xFF, 0xFF, 0xFF, D_800E1202 >> 2);
        }
    }
    func_800338B0(&D_800F22B4);
    if ((D_800DFDD4[D_801026A4] & 0xB000) && D_800E11FC == 0) {
        func_8007D45C(D_8010B358, D_800E2818, 3);
        D_800E11FC = 1;
        if (D_800E44A8 == 2 && insertRankedRecord(2, D_80113328, D_80112D18, D_80113321) != 0) {
            D_800E122C = 3;
            D_800E0760 = 0;
        }
        if (D_8015D980 == 2 && D_800E08AC < D_800E08A8 && D_800E08B0 < D_800E08A8) {
            func_8003F8D8();
            func_8003FD78();
        } else {
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E122A = -1;
        }
    }
}



typedef struct {
    u8 pad[0x24];
    s32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 pad30[0xA];
    u8 unk3A;
} Obj50;



extern void func_8003B1A4(void);
extern void func_80079B80(s32, u8 *);
extern void func_80079BC0(s32, u8 *);
extern void func_8007ADF8(u8 *);
extern void func_8007AEE0(void *);
extern void func_8007B038(u8 *);

extern u8 D_736C50[];
extern s32 D_800DF710;
extern s32 D_800DF714;
extern s32 D_800DFD98;
extern s32 D_800DFE84;
extern u16 D_800DFF08;
extern u8 D_800E0784[8][9];
extern s8 D_800E07CC[8];
extern u8 D_800E07D4[];
extern u8 D_800E07DC[8];
extern s8 D_800E07E4[];
extern s32 D_800E088C;
extern u8 *D_800E08B4[];
extern u16 D_800E08D4[];
extern u16 D_800E08F4[];
extern u16 D_800E0914[];
extern u16 D_800E0A24[];
extern u16 D_800E0A98[];
extern s32 D_800E0B0C;
extern s32 D_800E0B10;
extern s32 D_800E0B14;
extern s32 D_800E0B18;
extern f32 D_800E0F74[];
extern f32 D_800E0F90[];
extern f32 D_800E0FAC[];
extern u8 *D_800E1010;
extern s32 D_800E1018;
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern u16 D_800E11FE;
extern u16 D_800E1200;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s16 D_800E121C;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E1224;
extern s16 D_800E1226;
extern s16 D_800E1228;
extern s16 D_800E122A;
extern s16 D_800E1232;
extern s16 D_800E123E;
extern s16 D_800E1242;
extern s32 D_800E1258;
extern s32 D_800E125C;
extern s32 D_800E1260;
extern Obj *D_800E1264;
extern Obj *D_800E1268;
extern s32 D_800E126C;
extern s32 D_800E1270;
extern s32 D_800E1274;
extern Obj *D_800E1278;
extern s32 D_800E127C;
extern u8 D_800E2818[];
extern s16 D_800E4498;
extern s16 D_800E449C;
extern s16 D_800E44A0;
extern s16 D_800E44A8;
extern u8 D_800ECCEC[];
extern u8 D_800ECCF8[];
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern s8 D_80102688;
extern s8 D_80102690;
extern s32 D_801026A8;
extern s32 D_801026AC;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern f32 D_80102B28[16];
extern f32 D_80102B68[16];
extern f32 D_80102BB0[16];
extern f32 D_80102BF8[16];
extern f32 D_80102CF8;
extern f32 D_80102CFC;
extern u8 D_80108828;
extern u16 D_80109DA4;
extern u8 D_80109DA9;
extern s8 D_80109DB2;
extern u8 D_80109DBC;
extern u8 D_80109DC0[];
extern s16 D_8010B33C;
extern s8 D_8010B341;
extern s8 D_8010B34A;
extern s8 D_8010B354;
extern u8 D_8010B358[];
extern s16 D_801125C6;
extern s16 D_801125F6;
extern s16 D_80112602;
extern s8 D_80113320;
extern s8 D_80113322;
extern s8 D_80113323;
extern s32 D_80113328;
extern s16 D_8011585E;
extern s16 D_8011586A;
extern s8 D_80116588;
extern s8 D_8011658A;
extern s8 D_8011658B;
extern u8 *D_80116590;

void func_80050BFC(void) {
    s32 alpha;
    u8 *p;
    u8 buf[12];
    register s32 w;
    register s16 pan;

    if (D_800E1232 >= 0) {
        func_80060630();
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_80102688 = 0;
        D_80102690 = 0;
        D_80102CF8 = 0.0f;
        D_80102CFC = -0.5f;
        D_800E1018 = 0;
        if (D_800E44A8 == 6) {
            if (D_801125F6 == D_8011585E) {
                D_800E1018 = loadAsset(D_736C50, 0x94, 8);
            }
            D_800E0B10 = 0;
            D_800E0B14 = 1;
            if (D_800E088C == 0) {
                D_800E0B0C = 2;
                D_800E4498 = 0;
                D_800E449C = 0;
                D_800E0B18 = 1;
                D_801026A8 = -1;
                D_801026AC = 1;
            }
            D_80113320 = D_800E07CC[D_800E0B10];
            D_80116588 = -1;
            D_80113322 = D_800E07D4[D_800E0B10];
            D_8011658A = D_800E449C;
            D_80113323 = D_800E07E4[D_800E0B10];
            D_8011658B = 1;
            D_80113328 = (s32)(((u8 *)D_800E0784) + D_800E0B10 * 9);
            if (D_800E44A0 >= 3) {
                w = 7;
            } else {
                w = D_800E449C;
            }
            D_80116590 = D_800E08B4[w];
        } else {
            D_800E4498 = 0;
            D_800E449C = 0;
            if (D_800E088C == 0) {
                D_800E0B10 = 0;
                D_800E0B14 = 1;
                D_800E0B18 = 1;
                D_801026A8 = -1;
                D_801026AC = 1;
            } else if (D_801125F6 == D_8011585E) {
                D_800E1018 = loadAsset(D_736C50, 0x94, 8);
            } else {
                if (D_8011585E != 0) {
                    if (D_800E0B18 == D_800E0B10) {
                        D_800E0B18 += 1;
                        if (D_800E0B18 >= D_800E0B0C) {
                            D_800E0B18 = 0;
                            D_800E4498 += 1;
                        }
                    }
                    if (D_800E0B18 == D_800E0B14) {
                        D_800E0B18 += 1;
                        if (D_800E0B18 >= D_800E0B0C) {
                            D_800E0B18 = 0;
                            D_800E4498 += 1;
                        }
                    }
                    D_800E0B10 = D_800E0B18;
                    func_8003E698(D_800E0B10);
                }
                if (D_801125F6 != 0) {
                    if (D_800E0B18 == D_800E0B14) {
                        D_800E0B18 += 1;
                        if (D_800E0B18 >= D_800E0B0C) {
                            D_800E0B18 = 0;
                            D_800E4498 += 1;
                        }
                    }
                    if (D_800E0B18 == D_800E0B10) {
                        D_800E0B18 += 1;
                        if (D_800E0B18 >= D_800E0B0C) {
                            D_800E0B18 = 0;
                            D_800E4498 += 1;
                        }
                    }
                    D_800E0B14 = D_800E0B18;
                    func_8003E698(D_800E0B14);
                }
            }
            D_80113320 = D_800E07CC[D_800E0B10];
            D_80116588 = D_800E07CC[D_800E0B14];
            D_80113322 = D_800E07D4[D_800E0B10];
            D_8011658A = D_800E07D4[D_800E0B14];
            D_80113323 = D_800E07E4[D_800E0B10];
            D_8011658B = D_800E07E4[D_800E0B14];
            D_80113328 = (s32)(((u8 *)D_800E0784) + D_800E0B10 * 9);
            D_80116590 = ((u8 *)D_800E0784) + D_800E0B14 * 9;
            D_80112602 = D_800E07DC[D_800E0B10];
            D_8011586A = D_800E07DC[D_800E0B14];
        }
        D_800E1210 = 0;
        D_800E11FC = 0;
        if (D_800E0784[D_800E0B10][0] == 0) {
            D_800E0784[D_800E0B10][0] = 'P';
            D_800E0784[D_800E0B10][1] = 'L';
            D_800E0784[D_800E0B10][2] = 'A';
            D_800E0784[D_800E0B10][3] = 'Y';
            D_800E0784[D_800E0B10][4] = 'E';
            D_800E0784[D_800E0B10][5] = 'R';
            D_800E0784[D_800E0B10][6] = ' ';
            D_800E0784[D_800E0B10][7] = D_800E0B10 + 0x31;
            D_800E0784[D_800E0B10][8] = 0;
        }
        if (D_800E0784[D_800E0B14][0] == 0) {
            D_800E0784[D_800E0B14][0] = 'P';
            D_800E0784[D_800E0B14][1] = 'L';
            D_800E0784[D_800E0B14][2] = 'A';
            D_800E0784[D_800E0B14][3] = 'Y';
            D_800E0784[D_800E0B14][4] = 'E';
            D_800E0784[D_800E0B14][5] = 'R';
            D_800E0784[D_800E0B14][6] = ' ';
            D_800E0784[D_800E0B14][7] = D_800E0B14 + 0x31;
            D_800E0784[D_800E0B14][8] = 0;
        }
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800DFE84 = 1;
        if (D_800E1018 != 0) {
            D_800E1258 = loadAnim(D_800E08F4[D_80113322]);
            D_800E125C = loadAnim(D_800E0914[D_80113322]);
            if ((D_800E44A8 == 6) && (D_800E44A0 >= 3)) {
                w = 7;
            } else {
                w = D_8011658A;
            }
            D_800E126C = loadAnim(D_800E08F4[w]);
            if ((D_800E44A8 == 6) && (D_800E44A0 >= 3)) {
                w = 7;
            } else {
                w = D_8011658A;
            }
            D_800E1270 = loadAnim(D_800E0914[w]);
        } else {
            D_800E1258 = loadAnim(D_800E0A24[D_80113322]);
            if ((D_800E44A8 == 6) && (D_800E44A0 >= 3)) {
                w = 7;
            } else {
                w = D_8011658A;
            }
            D_800E126C = loadAnim(D_800E0A24[w]);
            D_800E125C = loadAnim(0x70);
            D_800E1274 = loadMesh(0x5C);
        }
        D_800E1260 = loadMesh(D_800E08D4[D_80113322]);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU46->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if (D_800E1018 != 0) {
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E125C, &MENU46->unk250, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
        } else {
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E125C, &MENU46->unk264, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
        }
        D_800E1264->unk28 = 1.0f;
        D_800E1264->unk2C = -0.08f;
        if ((D_800E44A8 == 6) && (D_800E44A0 >= 3)) {
            w = 7;
        } else {
            w = D_8011658A;
        }
        D_800E1274 = loadMesh(D_800E08D4[w]);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1278 = LWAllocateMemory(D_800F22C0, D_800E126C, &MENU46->unk264, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if (D_800E1018 != 0) {
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E127C = LWAllocateMemory(D_800F22C0, D_800E1270, &MENU46->unk264, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
        }
        D_800E1278->unk28 = 1.0f;
        D_800E1278->unk2C = -0.08f;
        D_800DFE84 = 0;
        D_800E11FC = 0;
        D_800E11FE = 0;
        D_800E1200 = 0;
        if (D_800E1018 != 0) {
            ((Obj50 *)D_800E1278)->unk3A = 1;
            ((Obj50 *)D_800E127C)->unk3A = 1;
            D_800E1242 = 0x14;
        } else {
            D_800E1242 = 0xA;
        }
        func_8003FC6C(0x58, 0x32, 0x40, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        if (D_800E11FC != 0) {
            D_800E1228 = -1;
            D_800E122A = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1226 = -1;
            D_800E1220 = -1;
            D_800E121C = -1;
            D_800E123E = D_800E449C;
            D_801125C6 = 1;
            func_800CC6E0();
            D_800E449C = D_800E123E;
            D_800E4498 = D_800E123E;
        } else {
            if (D_800E44A8 != 6) {
                D_800E1232 = 0;
            } else {
                D_800E122A = -1;
            }
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    if (D_80102CF8 < 20.0) {
        alpha = D_800E1202;
    } else if (D_80102CF8 < 25.0) {
        alpha = (25.0 - D_80102CF8) * 255.0 / 5.0;
    } else {
        alpha = 0;
    }
    if ((alpha != 0) || (D_800E1018 != 0)) {
        func_800335F0(&D_800F22B4);
        if (D_800E1018 != 0) {
            func_8003396C(&D_800F22B4, D_800E1018, 0x7D, 0x30, 0xFF, 0xFF, 0xFF, D_800E1202);
        } else {
            if (D_800E44A8 == 6) {
                sprintf(buf, D_800ECCEC, D_800E449C + 1);
                w = func_800388BC(buf), func_80038478(&D_800F22B4, 0xA0 - (w >> 1), 0x18, buf, 0xE6, 0x61, 0x1E, alpha);
            }
            w = func_800388BC(D_80113328), func_80038478(&D_800F22B4, 0x5A - (w >> 1), 0x2E, D_80113328, 0xE6, 0x61, 0x1E, alpha);
            p = D_800ECCF8;
            w = func_800388BC(p), func_80038478(&D_800F22B4, 0xA0 - (w >> 1), 0x70, p, 0xFF, 0xDC, 0x3E, alpha);
            w = func_800388BC(D_80116590), func_80038478(&D_800F22B4, 0xE6 - (w >> 1), 0x2E, D_80116590, 0xE6, 0x61, 0x1E, alpha);
        }
        func_800338B0(&D_800F22B4);
    }
    if (D_800E1018 != 0) {
        guScaleF((f32(*)[4])D_80102B28, -1.0f, 1.0f, 1.0f);
        guTranslateF((f32(*)[4])D_80102BB0, D_800E0F74[D_800E07D4[D_800E0B10]], D_800E0F90[D_800E07D4[D_800E0B10]], 0.0f);
        guTranslateF((f32(*)[4])D_80102B68, -D_800E0F74[D_800E07D4[D_800E0B14]], D_800E0F90[D_800E07D4[D_800E0B14]], 0.0f);
        guMtxCatF((f32(*)[4])D_80102B28, (f32(*)[4])D_80102B68, (f32(*)[4])D_80102B28);
        guScaleF((f32(*)[4])D_80102B68, D_800E0FAC[D_800E07D4[D_800E0B10]], D_800E0FAC[D_800E07D4[D_800E0B10]], D_800E0FAC[D_800E07D4[D_800E0B10]]);
        guScaleF((f32(*)[4])D_80102BF8, D_800E0FAC[D_800E07D4[D_800E0B14]], D_800E0FAC[D_800E07D4[D_800E0B14]], D_800E0FAC[D_800E07D4[D_800E0B14]]);
    } else {
        guRotateRPYF_2((f32(*)[4])D_80102B68, 0.0f, D_80102CF8, 0.0f);
        guRotateRPYF_2((f32(*)[4])D_80102BF8, 0.0f, D_80102CF8 + 180.0, 0.0f);
        guTranslateF((f32(*)[4])D_80102B28, 0.0f, -270.0f, 0.0f);
        guRotateRPYF_2((f32(*)[4])D_80102BB0, 30.0f, 0.0f, 0.0f);
        guMtxCatF((f32(*)[4])D_80102BB0, (f32(*)[4])D_80102B28, (f32(*)[4])D_80102B28);
        for (alpha = D_800E1210; alpha < D_800E1208; alpha++) {
            if (D_80102CFC < 1.0) {
                D_80102CFC += 0.00390625;
            }
            if (D_80102CFC > 0.0) {
                D_80102CF8 += D_80102CFC;
            }
        }
    }
    if (D_800E1018 != 0) {
        if ((D_800E1264 != NULL) && (D_800E11FE < 3)) {
            if (D_800E11FE == 2) {
                if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, D_80102B68, D_80102BB0) != 0) {
                    D_800E11FE = 3;
                }
            } else if (D_800E11FE != 0) {
                if (LWPlayAnimation(D_800E1264, (D_800E1208 - D_800E1210) * 4, D_80102B68, D_80102BB0) != 0) {
                    D_800E11FE = 2;
                    D_800E1200 = 1;
                }
            } else if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, D_80102B68, D_80102BB0) != 0) {
                D_800E1264->unk24 = 0;
            }
        }
    } else {
        if ((D_800E1264->unk24 == 0) && (D_80102688 == 0)) {
            D_80102688 = 1;
            func_8007ADF8(&D_80108828);
            func_80079B80(0x7FFF, &D_80108828);
            D_80109DA9 = 0;
            D_80109DBC = 0;
            D_80109DA4 = 0;
            D_80109DB2 = 1;
            loadsong(D_800E0A98[D_80113322], &D_80108828);
            if (D_800E44A8 == 6) {
                func_8007ADF8(D_80109DC0);
                func_80079B80(0x7FFF, D_80109DC0);
                D_8010B341 = 0;
                D_8010B354 = 0;
                D_8010B33C = 0;
                D_8010B34A = 1;
                if ((D_800E44A8 == 6) && (D_800E44A0 >= 3)) {
                    w = 7;
                } else {
                    w = D_8011658A;
                }
                loadsong(D_800E0A98[w], D_80109DC0);
            } else {
                func_8007ADF8(D_80109DC0);
                func_80079B80(0x7FFF, D_80109DC0);
                D_8010B341 = 0;
                D_8010B354 = 0;
                D_8010B33C = 0;
                D_8010B34A = 1;
                loadsong(D_800E0A98[D_8011658A], D_80109DC0);
            }
        }
        pan = coss((D_80102CF8 + 180.0) * 182.044444444444451);
        func_80079BC0(pan / 1025 + 0x40, &D_80108828);
        pan = sins(D_80102CF8 * 182.044444444444451);
        func_80079B80(pan / 4 + 0x5FFF, &D_80108828);
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, D_80102B68, D_80102B28) != 0) {
            func_8007B038(&D_80108828);
            D_800E1264->unk24 = 0;
        } else {
            func_8007ACFC(&D_80108828);
        }
    }
    if (D_800E1018 != 0) {
        if ((D_800E1278 != NULL) && (D_800E1200 < 3)) {
            if (D_800E1200 == 2) {
                if (LWPlayAnimation(D_800E127C, D_800E1208 - D_800E1210, D_80102BF8, D_80102B28) != 0) {
                    D_800E1200 = 3;
                }
            } else if (D_800E1200 != 0) {
                if (LWPlayAnimation(D_800E1278, (D_800E1208 - D_800E1210) * 4, D_80102BF8, D_80102B28) != 0) {
                    D_800E1200 = 2;
                }
            } else {
                if (LWPlayAnimation(D_800E1278, (D_800E1208 - D_800E1210) + D_800E1242, D_80102BF8, D_80102B28) != 0) {
                    D_800E1278->unk24 = 0;
                }
                D_800E1242 = 0;
            }
        }
    } else {
        if ((D_800E1242 == 0) && (D_800E1278->unk24 == 0) && (D_80102690 == 0)) {
            D_80102690 = 1;
        }
        pan = coss(D_80102CF8 * 182.044444444444451);
        func_80079BC0(pan / 1025 + 0x40, D_80109DC0);
        pan = sins((D_80102CF8 + 180.0) * 182.044444444444451);
        func_80079B80(pan / 4 + 0x5FFF, D_80109DC0);
        if (D_800E1242 != 0) {
            w = 0;
        } else {
            w = D_800E1208 - D_800E1210;
        }
        if (LWPlayAnimation(D_800E1278, w, D_80102BF8, D_80102B28) != 0) {
            func_8007B038(D_80109DC0);
            D_800E1278->unk24 = 0;
        } else if (D_80102690 != 0) {
            func_8007ACFC(D_80109DC0);
        }
        if (D_800E1242 != 0) {
            D_800E1242 -= 1;
        }
        if (LWPlayAnimation(D_800E1268, (D_800E1208 - D_800E1210) + D_800E1242, NULL, D_80102B28) != 0) {
            D_800E1268->unk24 = 0;
        }
    }
    if (D_800E1208 < 0x5A) {
        return;
    }
    if (((D_800DFD98 & 0xB000) || ((D_80113323 != 0) && (D_8011658B != 0) && (D_800E1208 >= 0xB5))) && (D_800E11FC == 0) && (D_800DFF08 != 5)) {
        func_8007ADF8(&D_80108828);
        func_8007ADF8(D_80109DC0);
        D_8010B34A = 0;
        D_80109DB2 = 0;
        if (D_800E1018 != 0) {
            D_800E11FE = 1;
        } else {
            D_800E11FE = 3;
            D_800E1200 = 3;
            D_800E11FC = 3;
            D_800E1264->unk2C = 0.08f;
            D_800E1278->unk2C = 0.08f;
        }
        func_8007AEE0(D_8010B358);
        func_8007D45C(D_8010B358, D_800E2818, 3);
    }
    if ((D_800DFD98 & 0x4000) && (D_800E11FC == 0) && (D_800E121C >= 0) && (D_800DFF08 != 5)) {
        func_8007ADF8(&D_80108828);
        func_8007ADF8(D_80109DC0);
        D_8010B34A = 0;
        D_80109DB2 = 0;
        D_800E1264->unk2C = 0.08f;
        D_800E1278->unk2C = 0.08f;
        func_8003FD78();
        func_8003F8D8();
        func_8007AEE0(D_8010B358);
        func_8007D45C(D_8010B358, D_800E2818, 4);
    }
    if (D_800E11FE > D_800E1200) {
        D_800E11FC = D_800E1200;
    } else {
        D_800E11FC = D_800E11FE;
    }
    if (D_800E11FC == 3) {
        D_800E11FC = 4;
        func_8003FD78();
        func_8003F8D8();
    }
}

/* ---- func_80052F68: 2P-results/score screen; sibling of the menu family
 * (func_8004127C / func_80055A80 / func_8005D674). Reuses the shared
 * file-scope decls; adds only the missing externs (proven candidate
 * spellings, byte-exact vs ROM). ---- */
extern void func_8004FBF8(void);
extern s16 D_801125FA;
extern s16 D_80115862;
extern s32 D_800E084C[];
extern s32 D_800E086C[];
extern s32 D_800E0780;
extern u8 *D_800E11B4[];

void func_80052F68(void) {
    s32 i;
    s32 j;
    s32 val;
    u8 *name;
    u8 buf[11];

    if (D_800E122A >= 0) {
        func_8004FBF8();
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        buf[0] = D_801125FA;
        buf[1] = D_801125F6;
        _bzero(D_80110220, 0x3268);
        D_801125FA = buf[0];
        D_801125F6 = buf[1];
        buf[0] = D_80115862;
        buf[1] = D_8011585E;
        _bzero(D_80113488, 0x3268);
        D_80115862 = buf[0];
        D_8011585E = buf[1];
        D_800E1018 = loadAsset(D_736C50, 0x51, 8);
        D_800E1024 = loadAsset(D_736C50, 0x52, 8);
        D_800E10AC = loadAsset(D_736C50, 0x53, 8);
        D_800E11FC = 0;
        for (i = 0; i < D_800E0B0C; i++) {
            D_800E084C[i] = D_800E082C[i];
            D_800E086C[i] = i;
        }
        for (i = 0; i < D_800E0B0C - 1; i++) {
            for (j = i + 1; j < D_800E0B0C; j++) {
                if (D_800E084C[i] < D_800E084C[j]) {
                    val = D_800E084C[i];
                    D_800E084C[i] = D_800E084C[j];
                    D_800E084C[j] = val;
                    val = D_800E086C[i];
                    D_800E086C[i] = D_800E086C[j];
                    D_800E086C[j] = val;
                }
            }
        }
        for (i = 0; i < D_800E0B0C; i++) {
            D_800E084C[i] = D_800E080C[D_800E086C[i]];
        }
        for (i = 0; i < D_800E0B0C - 1; i++) {
            for (j = i + 1; j < D_800E0B0C; j++) {
                if (D_800E084C[i] > D_800E084C[j]) {
                    val = D_800E084C[i];
                    D_800E084C[i] = D_800E084C[j];
                    D_800E084C[j] = val;
                    val = D_800E086C[i];
                    D_800E086C[i] = D_800E086C[j];
                    D_800E086C[j] = val;
                }
            }
        }
        for (i = 0; i < D_800E0B0C; i++) {
            D_800E084C[i] = D_800E07EC[D_800E086C[i]];
        }
        for (i = 0; i < D_800E0B0C - 1; i++) {
            for (j = i + 1; j < D_800E0B0C; j++) {
                if (D_800E084C[i] < D_800E084C[j]) {
                    val = D_800E084C[i];
                    D_800E084C[i] = D_800E084C[j];
                    D_800E084C[j] = val;
                    val = D_800E086C[i];
                    D_800E086C[i] = D_800E086C[j];
                    D_800E086C[j] = val;
                }
            }
        }
        D_800E0780 = 0;
        func_8003FC6C(0x17, 0x46, 0x37, 0xDC, 0xFF, 0, 0xFF, 0x28, 0xE1);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, D_800E1024, 5, 0x13, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E1018, 0, 0xBF, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E10AC, 0x9B, 0x1A, 0xFF, 0xDC, 0x3E, D_800E1202);
    for (i = 0; i < D_800E0B0C; i++) {
        if (D_800E0784[D_800E086C[i]][0] == 0) {
            D_800E0784[D_800E086C[i]][0] = 'P';
            D_800E0784[D_800E086C[i]][1] = 'L';
            D_800E0784[D_800E086C[i]][2] = 'A';
            D_800E0784[D_800E086C[i]][3] = 'Y';
            D_800E0784[D_800E086C[i]][4] = 'E';
            D_800E0784[D_800E086C[i]][5] = 'R';
            D_800E0784[D_800E086C[i]][6] = ' ';
            D_800E0784[D_800E086C[i]][7] = D_800E086C[i] + '1';
            D_800E0784[D_800E086C[i]][8] = 0;
        } else {
            name = D_800E0784[D_800E086C[i]];
        }
        func_80038478(&D_800F22B4, -func_800388BC(name) - i * 5 + 0x87, i * 15 + 0x2B, name, 0xE6, 0x61, 0x1E, D_800E1202);
        val = D_800E07EC[D_800E086C[i]];
        buf[10] = 0;
        j = 10;
        do {
            j--;
            buf[j] = val % 10 + '0';
            val = val / 10;
        } while (val > 0);
        func_80038478(&D_800F22B4, -func_800388BC(&buf[j]) - i * 5 + 0xB0, i * 15 + 0x2B, &buf[j], 0xE6, 0x61, 0x1E, D_800E1202);
        val = D_800E080C[D_800E086C[i]];
        buf[10] = 0;
        j = 10;
        do {
            j--;
            buf[j] = val % 10 + '0';
            val = val / 10;
        } while (val > 0);
        func_80038478(&D_800F22B4, -func_800388BC(&buf[j]) - i * 5 + 0xDD, i * 15 + 0x2B, &buf[j], 0xE6, 0x61, 0x1E, D_800E1202);
        val = D_800E082C[D_800E086C[i]];
        buf[10] = 0;
        j = 10;
        do {
            j--;
            buf[j] = val % 10 + '0';
            val = val / 10;
        } while (val > 0);
        func_80038478(&D_800F22B4, -func_800388BC(&buf[j]) - i * 5 + 0x11B, i * 15 + 0x2B, &buf[j], 0xE6, 0x61, 0x1E, D_800E1202);
    }
    for (i = 0; i < 2; i++) {
        if (D_800E1228 == i) {
            func_80038478(&D_800F22B4, i * 93 + 0xA2, 0xAB, D_800E11B4[i], 0xFF, 0xFF, 0xFF, D_80102698);
        } else {
            func_80038478(&D_800F22B4, i * 93 + 0xA2, 0xAB, D_800E11B4[i], 0xE6, 0x61, 0x1E, D_800E1202);
        }
    }
    func_800338B0(&D_800F22B4);
    if (D_800DFD98 & 0xF00) {
        D_800E0780 = 1;
        func_8007D45C(D_8010B358, D_800E2818, 2);
        D_800E1228 ^= 1;
    }
    if ((D_800DFD98 & 0xB000) || (D_800E07E4[D_800E0B10] && D_800E07E4[D_800E0B14] && (D_800E1208 >= 0xB5) && (D_800E0780 == 0))) {
        D_800E0780 = 1;
        func_8007D45C(D_8010B358, D_800E2818, 3);
        switch (D_800E1228) {
        case 1:
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
        case 0:
            D_800E1228 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
            break;
        }
    }
}


/* ---- func_80054098: reuses shared Obj/T1010/MENU; adds only missing externs ----
 * func_80079B80 relies on the file-scope (s32,u8*) decl; func_8003396C on its
 * UnkImg* definition; both codegen-identical to the proven candidate's spellings. */
extern s32 D_800E0B1C;
extern u8 *D_800E0B28[];
extern u8 *D_800E11A8[];
extern void *D_800E10A8;
extern void *D_800E10B0;
extern s32 D_800E14A8;
extern u16 D_800E28E8;
extern u8 D_800E13A0;
extern u8 D_800E13A4;
extern u16 D_8010880C;
extern f32 D_80102C40[16];
extern Obj *D_800E1278;
extern u16 D_800E11FE;
extern void requestSaveDataWrite(void);
extern void func_80079BD4(s32);

void updateAndDrawAudioMenu(void) {
    u32 sp44;
    s32 sp40;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        MENU->unkC = loadAsset(D_736C50, 0x19, 8);
        MENU->unk10 = loadAsset(D_736C50, 0x47, 8);
        D_800E1018 = loadAsset(D_736C50, 0x54, 8);
        D_800E1024 = loadAsset(D_736C50, 0x55, 8);
        MENU->unk20 = loadAsset(D_736C50, 0x5C, 8);
        MENU->unk24 = loadAsset(D_736C50, 0x5D, 8);
        MENU->unk28 = loadAsset(D_736C50, 0x5E, 8);
        MENU->unk2C = loadAsset(D_736C50, 0x65, 8);
        MENU->unk3C = loadAsset(D_736C50, 0x5B, 8);
        MENU->unk40 = loadAsset(D_736C50, 0x5A, 8);
        D_800E102C = loadAsset(D_736C50, 0x56, 8);
        D_800E10B0 = loadAsset(D_736C50, 0x58, 8);
        D_800E10AC = loadAsset(D_736C50, 0x59, 8);
        D_800E10A8 = loadAsset(D_736C50, 0x57, 8);
        D_800E10B4 = loadAsset(D_736C50, 0x98, 8);
        D_800E1258 = loadAnim(0x56);
        D_800E1260 = loadMesh(0x1D);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1264->unk28 = 1.0f;
        D_800E1264->unk2C = -0.08f;
        D_800E1258 = loadAnim(0x57);
        D_800E1260 = loadMesh(0x1E);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1278 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1278->unk28 = 1.0f;
        D_800E1278->unk2C = -0.08f;
        D_800E1258 = loadAnim(0x95);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        guRotateRPYF_2(D_80102C40, 0.0f, 140.0f, 0.0f);
        guScaleF(D_80102B28, 0.4f, 0.4f, 0.4f);
        guMtxCatF(D_80102B28, D_80102C40, D_80102B28);
        guTranslateF(D_80102B68, -168.0f, 100.0f, 0.0f);
        guRotateRPYF_2(D_80102C40, 0.0f, -140.0f, 0.0f);
        guScaleF(D_80102BB0, 0.25f, 0.25f, 0.25f);
        guMtxCatF(D_80102BB0, D_80102C40, D_80102BB0);
        guTranslateF(D_80102BF8, 223.0f, 101.0f, 0.0f);
        D_800E0B24 = D_8010880C;
        D_800E11FE = 1;
        func_8003FC6C(0x3E, 0x30, 0x49, 0xDC, 0xFF, 0, 0xFF, 0, 0xC0);
        D_800E14A8 = 0;
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E1208 = 0;
        D_800E120C = 0;
        if (D_800E122A < 0) {
            D_800E1228 = -1;
        } else {
            D_800E1228 = -1;
            D_800E122A = -1;
        }
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, MENU->unkC, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unk10, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E1024, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E1018, 0xCE, 0x2F, 0xFF, 0xFF, 0xFF, D_800E1202);
    sp40 = D_800E1202 * 0x8C / 255;
    if (D_800E1228 == 0) {
        func_8003396C(&D_800F22B4, MENU->unk20, 0xD9, 0x2A, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, MENU->unk20, 0xD9, 0x2A, 0xFF, 0xDC, 0x3E, sp40);
    }
    if (D_800E1228 == 1) {
        func_8003396C(&D_800F22B4, MENU->unk24, 0xCA, 0x5A, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, MENU->unk24, 0xCA, 0x5A, 0xFF, 0xDC, 0x3E, sp40);
    }
    if (D_800E1228 == 2) {
        func_8003396C(&D_800F22B4, MENU->unk2C, 0xD5, 0x80, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, MENU->unk2C, 0xD5, 0x80, 0xFF, 0xDC, 0x3E, sp40);
    }
    if (D_800E1228 == 2) {
        sp40 = D_800E1202 * D_800E13A4 / 255;
    }
    func_8003396C(&D_800F22B4, D_800E10A8, 0x35, 0x8D, 0xFF, 0xFF, 0xFF, sp40);
    if (D_800E1228 == 2) {
        sp40 = D_800E1202 * D_800E13A0 / 255;
    }
    func_8003396C(&D_800F22B4, D_800E10B4, 0x35, 0x8D, 0xFF, 0xFF, 0xFF, sp40);
    if (D_800E1228 == 2) {
        sp40 = D_800E1202;
    } else {
        sp40 = D_800E1202 * 0x8C / 255;
    }
    func_80038478(&D_800F22B4, 0xF7 - func_800388BC(D_800E0B28[D_800E0B24]), 0x8D, D_800E0B28[D_800E0B24], 0xE6, 0x61, 0x1E, sp40);
    if (D_800E1228 == 0) {
        sp40 = D_800E1202;
    } else {
        sp40 = D_800E1202 * 0x8C / 255;
    }
    func_8003396C(&D_800F22B4, D_800E102C, 0x62, 0x3A, 0xFF, 0xFF, 0xFF, sp40);
    for (sp44 = 0; sp44 < 13; sp44++) {
        if (D_800E0B1C != sp44) {
            func_8003396C(&D_800F22B4, D_800E10B0, sp44 * 0xB + 0x67, 0x45, 0xFF, 0xFF, 0xFF, sp40);
        }
    }
    func_8003396C(&D_800F22B4, D_800E10AC, D_800E0B1C * 0xB + 0x63, 0x41, 0xFF, 0xDC, 0x3E, sp40);
    if (D_800E1228 == 1) {
        sp40 = D_800E1202;
    } else {
        sp40 = D_800E1202 * 0x8C / 255;
    }
    for (sp44 = 0; sp44 < 3; sp44++) {
        if (D_800E0B20 == sp44) {
            func_80038478(&D_800F22B4, sp44 * 0x42 - (func_800388BC(D_800E11A8[sp44]) >> 1) + (sp44 >> 1) * 0xA + 0x55, 0x69, D_800E11A8[sp44], 0xFF, 0xDC, 0x3E, sp40);
        } else {
            func_80038478(&D_800F22B4, sp44 * 0x42 - (func_800388BC(D_800E11A8[sp44]) >> 1) + (sp44 >> 1) * 0xA + 0x55, 0x69, D_800E11A8[sp44], 0xE6, 0x61, 0x1E, sp40);
        }
    }
    func_800338B0(&D_800F22B4);
    if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, D_80102B28, D_80102B68) != 0) {
        D_800E1264->unk24 = 0;
    }
    if (D_800E11FE != 0) {
        if (LWPlayAnimation(D_800E1278, (D_800E1208 - D_800E1210) * D_800E11FE, D_80102BB0, D_80102BF8) != 0) {
            D_800E1278->unk24 = 0;
            if (D_800E11FE >= 2) {
                D_800E11FE = 0;
            }
        }
    } else if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, D_80102BB0, D_80102BF8) != 0) {
        D_800E1268->unk24 = 0;
        D_800E11FE = 1;
    }
    if (D_800E14A8 != 0) {
        D_800E14A8 -= 1;
        return;
    }
    if (D_800DFD98 & 0x400) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1228 < 2) {
            D_800E1228 += 1;
        } else {
            D_800E1228 = 0;
        }
    }
    if (D_800DFD98 & 0x800) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1228 > 0) {
            D_800E1228 -= 1;
        } else {
            D_800E1228 = 2;
        }
    }
    switch (D_800E1228) {
    case 0:
        if ((D_800DFD98 & 0x200) && (D_800E0B1C > 0)) {
            D_800E11FE = 0;
            D_800E1268->unk24 = 0;
            D_800E0B1C -= 1;
            sp44 = D_800E0B1C * 0x1556;
            if (sp44 >= 0x8000) {
                sp44 = 0x7FFF;
            }
            func_80079BD4(sp44);
            sp44 = -D_800E0B1C * 0xD56 + 0xA008;
            if (sp44 >= 0x5000) {
                sp44 = 0x4FFF;
            }
            D_800E28E8 = sp44;
            func_80079B80(sp44, D_80107290);
            func_8007D45C(D_8010B358, D_800E2818, 2);
            D_80102918[0x1F0] = (D_800E0B20 * 0x10) | D_800E0B1C;
            requestSaveDataWrite();
        } else if ((D_800DFD98 & 0x100) && (D_800E0B1C < 0xC)) {
            D_800E11FE = 0;
            D_800E1268->unk24 = 0;
            D_800E0B1C += 1;
            sp44 = D_800E0B1C * 0x1556;
            if (sp44 >= 0x8000) {
                sp44 = 0x7FFF;
            }
            func_80079BD4(sp44);
            sp44 = -D_800E0B1C * 0xD56 + 0xA008;
            if (sp44 >= 0x5000) {
                sp44 = 0x4FFF;
            }
            D_800E28E8 = sp44;
            func_80079B80(sp44, D_80107290);
            func_8007D45C(D_8010B358, D_800E2818, 2);
            D_80102918[0x1F0] = (D_800E0B20 * 0x10) | D_800E0B1C;
            requestSaveDataWrite();
        }
        break;
    case 1:
        if (D_800DFD98 & 0x200) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E0B20 <= 0) {
                D_800E0B20 = 2;
            } else {
                D_800E0B20 -= 1;
            }
            if ((D_800E0B20 == 2) && (D_800E0B24 == 0)) {
                D_800E0B24 = 1;
                D_800DFE84 = 1;
                loadsong(D_800E0B24, D_80107290);
                func_8007ACFC(D_80107290);
                D_800DFE84 = 0;
                D_80102918[0x1F1] = D_800E0B24;
                D_800E14A8 = 0xF;
            }
            D_80102918[0x1F0] = (D_800E0B20 * 0x10) | D_800E0B1C;
            requestSaveDataWrite();
            return;
        } else if (D_800DFD98 & 0x100) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E0B20 >= 2) {
                D_800E0B20 = 0;
            } else {
                D_800E0B20 += 1;
            }
            if ((D_800E0B20 == 2) && (D_800E0B24 == 0)) {
                D_800E0B24 = 1;
                D_800DFE84 = 1;
                loadsong(D_800E0B24, D_80107290);
                func_8007ACFC(D_80107290);
                D_800DFE84 = 0;
                D_80102918[0x1F1] = D_800E0B24;
                D_800E14A8 = 0xF;
            }
            D_80102918[0x1F0] = (D_800E0B20 * 0x10) | D_800E0B1C;
            requestSaveDataWrite();
            return;
        }
        break;
    case 2:
        if (D_800DFD98 & 0x200) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if ((D_800E122A < 0) && (D_800E0B20 != 2)) {
                if (D_800E0B24 <= 0) {
                    D_800E0B24 = D_800E28E4;
                } else {
                    D_800E0B24 -= 1;
                }
            } else if (D_800E0B24 < 2) {
                D_800E0B24 = D_800E28E4;
            } else {
                D_800E0B24 -= 1;
            }
            D_800DFE84 = 1;
            loadsong(D_800E0B24, D_80107290);
            func_8007ACFC(D_80107290);
            D_800DFE84 = 0;
            D_80102918[0x1F1] = D_800E0B24;
            requestSaveDataWrite();
            D_800E14A8 = 0xF;
            return;
        } else if (D_800DFD98 & 0x100) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if ((D_800E122A < 0) && (D_800E0B20 != 2)) {
                if (D_800E0B24 >= D_800E28E4) {
                    D_800E0B24 = 0;
                } else {
                    D_800E0B24 += 1;
                }
            } else if (D_800E0B24 >= D_800E28E4) {
                D_800E0B24 = 1;
            } else {
                D_800E0B24 += 1;
            }
            D_800DFE84 = 1;
            loadsong(D_800E0B24, D_80107290);
            func_8007ACFC(D_80107290);
            D_800DFE84 = 0;
            D_80102918[0x1F1] = D_800E0B24;
            requestSaveDataWrite();
            D_800E14A8 = 0xF;
            return;
        }
        break;
    }
    if (D_800DFD98 & 0xB000) {
        func_8007D45C(D_8010B358, D_800E2818, 3);
        if (D_800E122A < 0) {
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E1228 = -1;
            D_800E1220 = -1;
        } else {
            func_8003FD78();
        }
    }
    if (D_800DFD98 & 0x4000) {
        func_8007D45C(D_8010B358, D_800E2818, 4);
        func_8003FD78();
        if (D_800E122A < 0) {
            func_8003F8D8();
        }
    }
}

/* ---- func_80055A80: saved-game/records menu driver; sibling of the menu
 * family (func_8004127C / func_80055EE48 / func_80054098). Reuses the shared
 * UnkImg / T1010 / MENU definitions and the existing file-scope function and
 * data declarations; adds only the externs not already visible here.
 * D_801029E8 / D_80102AAC and func_800654C8 / func_80066F18 / func_80066D50
 * are all defined/declared only later at file scope, so they are forward-
 * declared here with types matching their later definitions. func_80066D50's
 * (u16) prototype is byte-exact here: the sole argument is the s16 global
 * D_800E1230, loaded with lh and passed straight to $a0 with no truncation,
 * so no andi masking is emitted (verified by matchdiff FULL MATCH). */
extern u8 *D_800E11C8[];
extern u8 *D_800E11D0[];
extern u8 D_800ECCFC[];
extern u8 D_800ECD04[];
extern u8 D_800ECD14[];
extern u8 D_800ECD1C[];
extern u8 D_80102AAC[];
extern u8 D_801029E8[8][20];
extern s16 D_80103204;
extern void unpackPlayerName(u8 *, u8 *);
extern void func_80066F18(void);
extern void func_80066D50(u16);

void func_80055A80(void) {
    u32 i;
    u32 sp58;
    u32 sp54;
    u8 *sp50;
    u8 *sp4C;
    u8 sp40[9];
    register s32 w;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        MENU->unkC = loadAsset(D_736C50, 0x19, 8);
        MENU->unk10 = loadAsset(D_736C50, 0x47, 8);
        D_800E1018 = (s32) loadAsset(D_736C50, 0x66, 8);
        D_800E1024 = loadAsset(D_736C50, 0x55, 8);
        MENU->unk3C = loadAsset(D_736C50, 0x80, 8);
        MENU->unk40 = loadAsset(D_736C50, 0x49, 8);
        MENU->unk44 = loadAsset(D_736C50, 0x4A, 8);
        MENU->unk64 = loadAsset(D_736C50, 0x42, 8);
        MENU->unk68 = loadAsset(D_736C50, 0x30, 8);
        D_800E1028 = loadAsset(D_736C50, 0x81, 8);
        D_800E10AC = loadAsset(D_736C50, 0x4E, 8);
        D_800E10B4 = (s32) loadAsset(D_736C50, 0x97, 8);
        D_800E122A = 0;
        D_800E1242 = -1;
        D_800E123E = -1;
        D_800E1240 = -1;
        D_80103204 = 8;
        if (D_800E0B20 != 2) {
            loadsong(D_800E94B0, D_80107290);
        } else {
            loadsong(D_800E0B24, D_80107290);
        }
        func_8007ACFC(D_80107290);
        func_8003FC6C(0x3E, 0x30, 0x49, 0xDC, 0xFF, 0, 0xFF, 0, 0xC0);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E1208 = 0;
        D_800E120C = 0;
        D_800E1230 = -1;
        D_800E122A = -1;
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    if ((D_800E1242 < 0) && (D_800E123E < 0) && (D_800E1240 < 0)) {
        sp58 = D_800E1202;
    } else {
        sp58 = D_800E1202 / 4;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, MENU->unk3C, 0x56, 0x2C, 0xFF, 0xDC, 0x3E, sp58);
    func_8003396C(&D_800F22B4, MENU->unk40, 0xDC, 0x30, 0xFF, 0xDC, 0x3E, sp58);
    func_8003396C(&D_800F22B4, MENU->unkC, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unk10, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unk64, 0x1E, 0xD2, 0xE6, 0x61, 0x1E, sp58);
    func_8003396C(&D_800F22B4, MENU->unk68, 0x1E, 0xD2, 0xFF, 0xDC, 0x3E, sp58);
    func_8003396C(&D_800F22B4, D_800E1024, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF, sp58);
    func_8003396C(&D_800F22B4, (UnkImg *) D_800E1018, 0xD6, 0x2F, 0xFF, 0xFF, 0xFF, sp58);
    for (i = 0; i < 6; i++) {
        if (D_800E122A + i < D_80103204) {
            sp50 = func_8003E358(D_800E122A + i + 1);
            if ((D_800E122A + i >= 8U) || (D_801029E8[D_800E122A + i][0] == 0xFF)) {
                sp4C = D_800ECCFC;
            } else {
                unpackPlayerName(sp40, &D_80102918[(D_800E122A + i) * 0x14 + 0xD0]);
                sp40[8] = 0;
                sp4C = sp40;
            }
            if (D_800E1230 == (D_800E122A + i)) {
                w = func_800388BC(sp50), func_80038478(&D_800F22B4, -w - (i * 6) + 0x6D, (i * 0x12) + 0x41, sp50, 0xFF, 0xFF, 0xFF, D_80102698 * sp58 / 255);
                w = func_800388BC(sp4C), func_80038478(&D_800F22B4, -w - (i * 6) + 0xFE, (i * 0x12) + 0x41, sp4C, 0xFF, 0xFF, 0xFF, D_80102698 * sp58 / 255);
            } else {
                w = func_800388BC(sp50), func_80038478(&D_800F22B4, -w - (i * 6) + 0x6D, (i * 0x12) + 0x41, sp50, 0xE6, 0x61, 0x1E, sp58);
                w = func_800388BC(sp4C), func_80038478(&D_800F22B4, -w - (i * 6) + 0xFE, (i * 0x12) + 0x41, sp4C, 0xE6, 0x61, 0x1E, sp58);
            }
        }
    }
    if ((D_800E1242 < 0) && (D_800E123E < 0) && (D_800E1240 < 0)) {
        sp54 = D_800E13AC * sp58 / 255;
    } else {
        sp54 = sp58;
    }
    func_8003396C(&D_800F22B4, D_800E10AC, 0x3E, 0xAD, 0xFF, 0xFF, 0xFF, sp54);
    if ((D_800E1242 < 0) && (D_800E123E < 0) && (D_800E1240 < 0)) {
        sp54 = D_800E13A8 * sp58 / 255;
    }
    func_8003396C(&D_800F22B4, (UnkImg *) D_800E10B4, 0x3E, 0xAD, 0xFF, 0xFF, 0xFF, sp54);
    if ((D_800E1242 >= 0) || (D_800E123E >= 0) || (D_800E1240 >= 0)) {
        func_8003396C(&D_800F22B4, D_800E1028, 0x46, 0x4E, 0xFF, 0xFF, 0xFF, D_800E1202);
    }
    if (D_800E123E >= 0) {
        for (i = 0; i < 2; i++) {
            if (D_800E123E == i) {
                w = func_800388BC(D_800E11C8[i]), func_80038478(&D_800F22B4, -(i * 5) - w + 0xCD, (i * 0x12) + 0x63, D_800E11C8[i], 0xFF, 0xFF, 0xFF, D_80102698);
            } else {
                w = func_800388BC(D_800E11C8[i]), func_80038478(&D_800F22B4, -(i * 5) - w + 0xCD, (i * 0x12) + 0x63, D_800E11C8[i], 0xE6, 0x61, 0x1E, D_800E1202);
            }
        }
    }
    if (D_800E1242 >= 0) {
        sp50 = D_800ECD04;
        w = func_800388BC(sp50), func_80038478(&D_800F22B4, 0xDE - w, 0x5A, sp50, 0xE6, 0x61, 0x1E, D_800E1202);
        for (i = 0; i < 2; i++) {
            if (D_800E1242 == i) {
                w = func_800388BC(D_800E11D0[i]), func_80038478(&D_800F22B4, -(i * 5) - w + 0xD7, (i * 0x12) + 0x73, D_800E11D0[i], 0xFF, 0xFF, 0xFF, D_80102698);
            } else {
                w = func_800388BC(D_800E11D0[i]), func_80038478(&D_800F22B4, -(i * 5) - w + 0xD7, (i * 0x12) + 0x73, D_800E11D0[i], 0xE6, 0x61, 0x1E, D_800E1202);
            }
        }
    }
    if (D_800E1240 >= 0) {
        func_80038478(&D_800F22B4, 0x64, 0x55, D_800ECD14, 0xE6, 0x61, 0x1E, D_800E1202);
        func_80038478(&D_800F22B4, 0x5F, 0x64, D_800ECD1C, 0xE6, 0x61, 0x1E, D_800E1202);
        for (i = 0; i < 2; i++) {
            if (D_800E1240 == i) {
                w = func_800388BC(D_800E11D0[i]), func_80038478(&D_800F22B4, -(i * 5) - w + 0xD7, (i * 0x11) + 0x78, D_800E11D0[i], 0xFF, 0xFF, 0xFF, D_80102698);
            } else {
                w = func_800388BC(D_800E11D0[i]), func_80038478(&D_800F22B4, -(i * 5) - w + 0xD7, (i * 0x11) + 0x78, D_800E11D0[i], 0xE6, 0x61, 0x1E, D_800E1202);
            }
        }
    }
    func_800338B0(&D_800F22B4);
    if ((D_800E1242 < 0) && (D_800E123E < 0) && (D_800E1240 < 0)) {
        if (D_800DFD98 & 0x800) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E1230 != 0) {
                D_800E1230 -= 1;
            } else {
                D_800E1230 = D_80103204 - 1;
            }
        }
        if (D_800DFD98 & 0x400) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E1230 < (D_80103204 - 1)) {
                D_800E1230 += 1;
            } else {
                D_800E1230 = 0;
            }
        }
        if (D_800DFD98 & 0xB000) {
            if (D_801029E8[D_800E1230][0] != 0xFF) {
                func_8007D45C(D_8010B358, D_800E2818, 3);
                D_800E123E = 0;
            } else {
                func_8007D45C(D_8010B358, D_800E2818, 5);
            }
        }
        if (D_800DFD98 & 0x4000) {
            func_8007D45C(D_8010B358, D_800E2818, 4);
            func_8003FD78();
            func_8003F8D8();
        }
        if (D_800DFD98 & 4) {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            D_800E1240 = 0;
        }
    } else if (D_800E123E >= 0) {
        if (D_800DFD98 & 0xB000) {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            if (D_800E123E == 1) {
                D_800E1242 = 0;
            } else {
                unpackPlayerName(D_800E0784[0], &D_80102918[D_800E1230 * 0x14 + 0xD0]);
                D_800E0784[0][8] = 0;
                D_80113328 = (s32) D_800E0784;
                D_800E07D4[0] = D_80102AAC[D_800E1230];
                D_80113322 = D_800E07D4[0];
                func_80065660();
                D_8015D980 = 1;
                D_800E1208 = 0;
                D_800E120C = 0;
                D_800E1230 = -1;
                D_800E0754[0] = 0;
                D_800E121C = 0;
                D_800E1220 = -1;
                D_800E1222 = 0;
            }
            D_800E123E = -1;
        }
        if (D_800DFD98 & 0x4000) {
            func_8007D45C(D_8010B358, D_800E2818, 4);
            D_800E123E = -1;
        }
        if (D_800DFD98 & 0xC00) {
            func_8007D45C(D_8010B358, D_800E2818, 4);
            D_800E123E ^= 1;
        }
    } else if (D_800E1240 >= 0) {
        if (D_800DFD98 & 0xB000) {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            if (D_800E1240 == 1) {
                func_80066F18();
            }
            D_800E1240 = -1;
        }
        if (D_800DFD98 & 0x4000) {
            func_8007D45C(D_8010B358, D_800E2818, 4);
            D_800E1240 = -1;
        }
        if (D_800DFD98 & 0xC00) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            D_800E1240 ^= 1;
        }
    } else if (D_800E1242 >= 0) {
        if (D_800DFD98 & 0xB000) {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            if ((D_800E1242 == 1) && (D_800E1230 < 8)) {
                func_80066D50(D_800E1230);
            }
            D_800E1242 = -1;
        }
        if (D_800DFD98 & 0x4000) {
            func_8007D45C(D_8010B358, D_800E2818, 4);
            D_800E1242 = -1;
        }
        if (D_800DFD98 & 0xC00) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            D_800E1242 ^= 1;
        }
    }
    if (D_800E1230 < D_800E122A) {
        D_800E122A = D_800E1230;
    }
    if ((D_800E122A + 5) < D_800E1230) {
        D_800E122A = D_800E1230 - 5;
    }
}


/*
 * func_80057128 @ ROM 0x324D8 -- IDO 5.3 -O1 -g -mips1
 * STATUS: MATCHED (function body byte-perfect 0x0..0xFD4).
 *   Residual: ultracheck reports 2 words at +0xFD8/+0xFDC. These are the
 *   assembler.s 16-byte .text alignment padding (function is 0xFD8 bytes, not
 *   16-aligned) which the tool compares against the NEXT function.s prologue
 *   (27BDFFB8 addiu sp,-0x48). Not fixable from C; the function is a match.
 * FIX LEDGER (from 870):
 *   1. +s32 sp38 homed local (declared after sp3C): frame 0x38->0x40, sp3C
 *      0x34->0x3C. 870->869 (collapsed the addiu-sp word; -g homes the local).
 *   2. switch: break INSIDE each case if-body + trailing break => two separate
 *      "b .L800573C8" (true-path + false-path) per case instead of a merged
 *      tail branch. 4 cases x2 insns. 869->348.
 *   3. the four sp3C +/-0x10 delta loops converted do-while -> for: the
 *      "sp3C = D_800E1210" init store lands in the entry-test.s load-delay slot
 *      (was emitted separately + reloaded). 348->2 (only padding left).
 */
extern void func_8006EC00(void);
extern void func_8005D674(void);
extern s32 func_80089D04(void);
extern s32 func_80089D60(void);
extern s32 insertRankedRecord(u16, u8 *, u32, s32);
extern void updateAndDrawRecordsMenu(void);
extern void func_8002A140(void);
extern s32 func_80089C40(void);
extern s32 func_80065EDC(void);
extern void func_8006EAD8(s32, s32);
extern void loadsong(s32, u8 *);
extern void func_80079B80(s32, u8 *);
extern void func_8007ACFC(u8 *);
extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern s32 func_800334D8(void);
extern void func_80029760();
extern void func_8007AF98(void *);
extern s32 func_800660B8(s32);
extern void func_8007ADF8(u8 *);
extern void func_8007AEE0(void *);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern void func_8006FA28(s16, s16, s16, s16, u8, u8, u8, u8);
extern void func_8006FE64(s16, s16, s16, s16);
extern s32 D_800DF710;
extern s32 D_800DF714;
extern u16 D_800DFD5C;
extern s16 D_800E0754[];
extern s32 D_800E0760;
extern u8 D_800E07D4[];
extern u16 D_800E08D4[];
extern u16 D_800E08E4[];
extern u16 D_800E0974[];
extern u16 D_800E0A04[];
extern u16 D_800E0A14[];
extern u16 D_800E0A78[];
extern u8 *D_800E1010;
extern u16 D_800E11FC;
extern s32 D_800E1210;
extern s16 D_800E121C;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E1224;
extern s16 D_800E1228;
extern s16 D_800E122C;
extern s16 D_800E122E;
extern s16 D_800E1234;
extern s32 D_800E1258;
extern s32 D_800E125C;
extern Obj *D_800E1264;
extern Obj *D_800E1268;
extern s16 D_800E14AC;
extern s16 D_800E44A0;
extern s16 D_800E44A8;
extern u16 D_800E94B8;
extern u8 D_800ECD28[];
extern s32 D_800F22C0;
extern s32 D_800F22C4;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern u8 D_80107290[];
extern u8 D_80108828;
extern u16 D_80109DA4;
extern u8 D_80109DA9;
extern u8 D_80109DBC;
extern u8 D_80109DC0[];
extern u8 D_8010B358[];
extern s32 D_8010B7C4;
extern s32 D_80112D18;
extern s32 D_80112D2C;
extern s8 D_80113321;
extern s32 D_80113328;
extern s16 D_8015D980;
void func_80057128(void) {
    s32 sp3C;
    s32 sp38;
    if (D_800E122E >= 0) {
        func_8006EC00();
        func_8005D674();
        if (D_800E122E < 0) {
            D_800E122E = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
            if (D_8015D980 == 2) {
                if ((D_800E44A8 == 6) && (func_80089D04() == (D_800E44A0 + 1))) {
                    D_800E44A0 += 1;
                }
                D_800E1228 = -1;
                D_800E1234 = -1;
            }
            if (D_800E44A0 >= (func_80089D60() - 1)) {
                switch (D_800E44A8) {
                case 5:
                    if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                        D_800E122C = 1;
                        D_800E0760 = 0x4B0;
                        break;
                    }
                    break;
                case 1:
                    if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                        D_800E122C = 0;
                        D_800E0760 = 0x4B0;
                        break;
                    }
                    break;
                case 4:
                    if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D2C / 60, D_80113321) != 0) {
                        D_800E122C = 2;
                        D_800E0760 = 0x4B0;
                        break;
                    }
                    break;
                case 2:
                    if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                        D_800E122C = 3;
                        D_800E0760 = 0x4B0;
                        break;
                    }
                    break;
                }
            }
            D_800E1228 = -1;
            D_800E1234 = -1;
        }
        return;
    }
    if (D_800E122C >= 0) {
        func_8006EC00();
        updateAndDrawRecordsMenu();
        if (D_800E122C < 0) {
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1228 = -1;
            D_800E1234 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        if (D_800DF710 > D_800DF714) {
            do {
                func_8002A140();
            } while (D_800DF710 > D_800DF714);
        }
        D_800E14AC = (D_800E44A0 >= (func_80089C40() - 1)) || (func_80065EDC() == 0x7F);
        if (D_800E14AC != 0) {
            func_8006EAD8(0x15000, 0);
            D_800F22C0 = D_800F22C4;
            loadsong(D_800E94B8, D_80107290);
            func_80079B80(0x3FFF, D_80107290);
            func_8007ACFC(D_80107290);
            D_800E1258 = (s32) loadAnim(0x105);
            (&D_800E1010)[0xA8] = (u8 *) loadMesh(0x6D);
            (&D_800E1010)[0xA9] = (u8 *) loadMesh(0);
            (&D_800E1010)[0xAA] = (u8 *) loadMesh(1);
            (&D_800E1010)[0xAB] = (u8 *) loadMesh(0x31);
            (&D_800E1010)[0xAC] = (u8 *) loadMesh(3);
            (&D_800E1010)[0xAD] = (u8 *) loadMesh(4);
            (&D_800E1010)[0xAE] = (u8 *) loadMesh(5);
            (&D_800E1010)[0xAF] = (u8 *) loadMesh(6);
            (&D_800E1010)[0xB0] = (u8 *) loadMesh(0x2F);
            (&D_800E1010)[0xB1] = (u8 *) loadMesh(0x3D);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1264 = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E1258, (void **)((u8 *)&D_800E1010 + 0x2A0), 0xA, &D_801026B0);
            D_800F22C0 += D_801026B0;
            func_80029760(D_800ECD28, func_800334D8());
            D_80109DA9 = 1;
            D_80109DBC = 0;
            D_80109DA4 = 0;
            func_8007AF98(D_8010B358);
            loadsong(0x135, &D_80108828);
            func_8007ACFC(&D_80108828);
            if (D_800E44A0 < (func_80089D60() - 1)) {
                D_800E1228 = 1;
            } else {
                D_800E1228 = 0;
            }
        } else {
            func_800660B8(1);
            D_800E1258 = (s32) loadAnim(D_800E0974[D_800E07D4[D_800E0B10]]);
            (&D_800E1010)[0xA8] = (u8 *) loadMesh(D_800E08D4[D_800E07D4[D_800E0B10]]);
            (&D_800E1010)[0xA9] = (u8 *) loadMesh(D_800E08E4[D_800E07D4[D_800E0B10]]);
            (&D_800E1010)[0xAA] = (u8 *) loadMesh(D_800E0A14[D_800E07D4[D_800E0B10]]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1264 = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E1258, (void **)((u8 *)&D_800E1010 + 0x2A0), (D_800E07D4[D_800E0B10] == 1) ? 3 : 2, &D_801026B0);
            D_800F22C0 += D_801026B0;
            if (D_800E07D4[D_800E0B10] == 0) {
                D_800E1264->unk48 = 0;
            }
            if (D_800E07D4[D_800E0B10] != 1) {
                D_800E125C = (s32) loadAnim(D_800E0A04[D_800E07D4[D_800E0B10]]);
                D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                D_800E1268 = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E125C, (void **)((u8 *)&D_800E1010 + 0x2A8), 1, &D_801026B0);
                D_800F22C0 += D_801026B0;
            }
            if (D_800E07D4[D_800E0B10] == 6) {
                loadsong(0x122, D_80107290);
                func_80079B80(0x4FFF, D_80107290);
                func_8007ACFC(D_80107290);
            } else {
                loadsong(D_800E94B8, D_80107290);
                func_80079B80(0x3FFF, D_80107290);
                func_8007ACFC(D_80107290);
            }
            if (D_800E0A78[D_800E07D4[D_800E0B10]] != 0) {
                func_8007ADF8(&D_80108828);
                func_80079B80(0x7FFF, &D_80108828);
                D_80109DA9 = 1;
                D_80109DBC = 0;
                D_80109DA4 = 0;
                loadsong(D_800E0A78[D_800E07D4[D_800E0B10]], &D_80108828);
            }
        }
        D_800E11FA = 0xFF;
        D_800E11FC = 0;
        D_800E1208 = 1;
        D_800E120C = 1;
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, 0xFF);
    if (D_800E14AC != 0) {
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, 0, 0) != 0) {
            if (D_800E1228 != 0) {
                if (D_800E11FA < 0xFF) {
                    for (sp3C = D_800E1210; sp3C < D_800E1208; sp3C++) {
                            D_800E11FA += 0x10;
                            }
                }
                if (D_800E11FA >= 0xFF) {
                    D_800E11FA = 0xFF;
                    D_800DFD5C = 0;
                    D_8010B7C4 = 0;
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E122E = 0;
                }
            } else {
                D_800E1228 = 1;
                if (D_800DF710 > D_800DF714) {
                    do {
                        func_8002A140();
                    } while (D_800DF710 > D_800DF714);
                }
                D_800F22C0 = D_800F22C4;
                D_800E1258 = (s32) loadAnim(0x12F);
                (&D_800E1010)[0xA8] = (u8 *) loadMesh(0x7A);
                D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                D_800E1264 = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E1258, (void **)((u8 *)&D_800E1010 + 0x2A0), 1, &D_801026B0);
                D_800F22C0 += D_801026B0;
                D_80109DA9 = 1;
                D_80109DBC = 0;
                D_80109DA4 = 0;
                func_8007AF98(D_8010B358);
                loadsong(0x141, &D_80108828);
                func_8007ACFC(&D_80108828);
            }
        } else {
            if (D_800E11FA > 0) {
                for (sp3C = D_800E1210; sp3C < D_800E1208; sp3C++) {
                        D_800E11FA -= 0x10;
                        }
            }
            if (D_800E11FA < 0) {
                D_800E11FA = 0;
            }
        }
    } else {
        func_8007ACFC(&D_80108828);
        if (D_800E07D4[D_800E0B10] != 1) {
            LWPlayAnimation(D_800E1268, D_80109DBC ? (D_800E1208 - D_800E1210) : 0, 0, 0);
            func_8006FE64(0, 0, 0x13F, 0xEF);
        }
        if (LWPlayAnimation(D_800E1264, D_80109DBC ? (D_800E1208 - D_800E1210) : 0, 0, 0) != 0) {
            func_8007ADF8(&D_80108828);
            if (D_800E07D4[D_800E0B10] == 6) {
                func_8007ADF8(D_80109DC0);
                func_8007AEE0(D_8010B358);
            }
            if (D_800E11FA < 0xFF) {
                for (sp3C = D_800E1210; sp3C < D_800E1208; sp3C++) {
                        D_800E11FA += 0x10;
                        }
            }
            if (D_800E11FA >= 0xFF) {
                D_800E11FA = 0xFF;
                D_800E1208 = 0;
                D_800E120C = 0;
                D_800E122E = 0;
            }
        } else {
            if (D_800E11FA > 0) {
                for (sp3C = D_800E1210; sp3C < D_800E1208; sp3C++) {
                        D_800E11FA -= 0x10;
                        }
            }
            if (D_800E11FA < 0) {
                D_800E11FA = 0;
            }
        }
    }
    if (D_800E11FA != 0) {
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, D_800E11FA);
    }
}

extern void func_80050BFC(void);
extern u8 *loadAsset(u8 *, s32, s32);
extern void func_800335F0(void *);
extern void func_8007D45C(void *, void *, s32);
extern void func_8003B1A4(void);
extern u8 D_736C50[];
extern s32 D_800DFD98;
extern s16 D_800DFDFC;
extern s32 D_800E0780;
extern s8 D_800E07E4[];
extern u16 D_800E0924[];
extern u16 D_800E0944[];
extern u16 D_800E0964[];
extern u16 D_800E0A58[];
extern u16 D_800E0A68[];
extern f32 D_800E0B84[];
extern f32 D_800E0BA0[];
extern f32 D_800E0BBC[];
extern void *D_800E1014;
extern void *D_800E1144[];
extern u16 D_800E11FE;
extern s16 D_800E1204;
extern s16 D_800E122A;
extern s32 D_800E1260;
extern u8 D_800E2818[];
extern s16 D_800E4498;
extern s16 D_800E449C;
extern s16 D_800E44AC;
extern u8 D_800ECD48[];
extern u8 D_800ECD68[];
extern u8 D_80102698;
extern s16 D_801026C0;
extern s16 D_801026C4;
extern f32 D_80102B28[16];
extern f32 D_80102B68[16];
void func_80058100(void) {
    s32 sp44;
    s32 pad40;
    void *sp3C;
    if (D_800E1208 == 0) {
        switch (D_800E44A8) {
        case 5:
            if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                D_800E122C = 1;
                D_800E0760 = 0x4B0;
            }
            break;
        case 1:
            if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                D_800E122C = 0;
                D_800E0760 = 0x4B0;
            }
            break;
        case 2:
            if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                D_800E122C = 3;
                D_800E0760 = 0x4B0;
            }
            break;
        }
    }
    if (D_800E122C >= 0) {
        updateAndDrawRecordsMenu();
        if (D_800E122C < 0) {
            D_80112D18 = 0;
            D_800E1228 = 0;
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        return;
    }
    if (D_800E122A >= 0) {
        func_80050BFC();
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        if (D_800DF710 > D_800DF714) {
            do {
                func_8002A140();
            } while (D_800DF710 > D_800DF714);
        }
        D_80112D18 = 0;
        D_800DFDFC = 1;
        D_800E1014 = loadAsset(D_736C50, 0xC2, 8);
        func_80038284(D_800E1014);
        D_801026C4 = (D_800E44A8 == 5) && ((D_800E4498 % 5) == 4);
        D_800E125C = 0;
        D_800E1268 = 0;
        if (D_801026C4 != 0) {
            D_800E1258 = (s32) loadAnim(D_800E0924[D_800E07D4[D_800E0B10]]);
        } else {
            D_800E1258 = (s32) loadAnim(D_800E0944[D_800E07D4[D_800E0B10]]);
            if (D_800E0964[D_800E07D4[D_800E0B10]] != 0) {
                D_800E125C = (s32) loadAnim(D_800E0964[D_800E07D4[D_800E0B10]]);
            }
        }
        D_800E1260 = (s32) loadMesh(D_800E08D4[D_800E07D4[D_800E0B10]]);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, (void **)((u8 *)&D_800E1010 + 0x250), 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if (D_800E125C != 0) {
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E125C, (void **)((u8 *)&D_800E1010 + 0x250), 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            D_800E1268->unk24 = 0;
        }
        D_800E1264->unk28 = 1.0f;
        D_800E1264->unk2C = -0.08f;
        if (D_801026C4 != 0) {
            sp44 = D_800E0A68[D_800E07D4[D_800E0B10]];
        } else {
            sp44 = D_800E0A58[D_800E07D4[D_800E0B10]];
        }
        if (sp44 != 0) {
            func_8007ADF8(&D_80108828);
            func_80079B80(0x7FFF, &D_80108828);
            D_80109DA9 = 1;
            D_80109DBC = 0;
            D_80109DA4 = 0;
            loadsong(sp44, &D_80108828);
        }
        D_800E11FE = 0;
        D_800E0780 = 0;
        if (((D_800E44A8 == 1) || (D_800E44A8 == 5) || (D_800E44A8 == 4)) && (D_800E4498 == 0) && (D_800E44A0 == 0)) {
            D_801026C0 = 3;
        } else {
            D_801026C0 = 2;
        }
        func_8003FC6C(0x50, 0xA, 0x1E, 0, 0, 0, 0, 0, 0);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        if (D_800E44A8 != 6) {
            D_800E449C = D_800E4498;
        }
        D_800E1228 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    for (sp44 = 0; sp44 < D_801026C0; sp44++) {
        if (D_800E1228 == sp44) {
            func_80038478(&D_800F22B4, (-func_800388BC(D_800E1144[sp44]) - (sp44 * 5)) + 0x10E, (sp44 * 0x12) + 0x64, D_800E1144[sp44], 0xFF, 0xFF, 0xFF, D_80102698);
        } else {
            func_80038478(&D_800F22B4, (-func_800388BC(D_800E1144[sp44]) - (sp44 * 5)) + 0x10E, (sp44 * 0x12) + 0x64, D_800E1144[sp44], 0xE6, 0x61, 0x1E, D_800E1202);
        }
    }
    if (D_801026C0 == 3) {
        sp3C = D_800ECD48;
        func_800384E4(&D_800F22B4, 0xA0 - (func_800388F4(sp3C) >> 1), 0xBE, sp3C, 0xFF, 0xDC, 0x3E, D_800E1202);
        sp3C = D_800ECD68;
        func_800384E4(&D_800F22B4, 0xA0 - (func_800388F4(sp3C) >> 1), 0xCA, sp3C, 0xFF, 0xDC, 0x3E, D_800E1202);
    }
    func_800338B0(&D_800F22B4);
    guScaleF(D_80102B28, D_800E0B84[D_800E07D4[D_800E0B10]], D_800E0B84[D_800E07D4[D_800E0B10]], D_800E0B84[D_800E07D4[D_800E0B10]]);
    guRotateF(D_80102B68, 7.0f, 0.0f, 1.0f, 0.0f);
    guMtxCatF(D_80102B68, D_80102B28, D_80102B28);
    guTranslateF(D_80102B68, D_800E0BA0[D_800E07D4[D_800E0B10]], D_800E0BBC[D_800E07D4[D_800E0B10]], 0.0f);
    if (D_800E11FE != 0) {
        if (D_800E1268 != 0) {
            if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, D_80102B28, D_80102B68) != 0) {
                D_800E1268->unk24 = 0;
            }
        }
    } else {
        func_8007ACFC(&D_80108828);
        if ((LWPlayAnimation(D_800E1264, D_80109DBC ? (D_800E1208 - D_800E1210) : 0, D_80102B28, D_80102B68) != 0) && (D_800E1268 != 0)) {
            D_800E1268->unk28 = D_800E1264->unk28;
            D_800E11FE = 1;
        }
    }
    if ((D_800DFD98 & 0x800) && (D_800DFF08 != 5)) {
        D_800E0780 = 1;
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1228 > 0) {
            D_800E1228 -= 1;
        } else {
            D_800E1228 = D_801026C0 - 1;
        }
    }
    if ((D_800DFD98 & 0x400) && (D_800DFF08 != 5)) {
        D_800E0780 = 1;
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1228 < (D_801026C0 - 1)) {
            D_800E1228 += 1;
        } else {
            D_800E1228 = 0;
        }
    }
    if (((D_800DFD98 & 0xB000) || ((D_800E07E4[0] != 0) && (D_800E11FE != 0) && (D_800E0780 == 0))) && (D_800DFF08 != 5)) {
        func_8007ADF8(&D_80108828);
        D_800E0780 = 1;
        func_8007D45C(D_8010B358, D_800E2818, 3);
        switch (D_800E1228) {
        case 1:
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1228 = -1;
            break;
        case 0:
            if (D_800E44A8 == 6) {
                D_800E122A = 0;
                D_800E1228 = 0;
                D_800E1208 = 0;
                D_800E120C = 0;
                break;
            }
            D_800E1264->unk2C = 0.08f;
            if (D_800E1268 != 0) {
                D_800E1268->unk2C = 0.08f;
            }
            func_8003FD78();
            func_8003F8D8();
            break;
        case 2:
            D_800E4498 = 0;
            D_800E449C = 0;
            D_800E44A0 = 0;
            if (D_800E44A8 == 4) {
                D_800E44AC = 3;
            } else {
                D_800E44AC = 1;
            }
            D_800E44A8 = 3;
            D_800DFDFC = 1;
            D_800E1264->unk2C = 0.08f;
            if (D_800E1268 != 0) {
                D_800E1268->unk2C = 0.08f;
            }
            func_8003FD78();
            func_8003F8D8();
            break;
        }
    }
}

/* ---- func_8005907C: local view structs (shared Obj lacks unk14/unk3A) ---- */
typedef struct UnkB0 {
    /* 0x00 */ u8 pad0[0xA8];
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ f32 unkB0;
} UnkB0;

typedef struct {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ UnkB0 *unk14;
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 pad30[0xA];
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B[0xD];
    /* 0x48 */ u8 unk48;
} Obj59;

typedef struct {
    /* 0x000 */ u8 pad0[0x250];
    /* 0x250 */ s32 unk250;
    /* 0x254 */ u8 pad254[0x264 - 0x254];
    /* 0x264 */ s32 unk264;
    /* 0x268 */ u8 pad268[0x270 - 0x268];
    /* 0x270 */ s32 unk270;
    /* 0x274 */ u8 pad274[0x28C - 0x274];
    /* 0x28C */ s32 unk28C;
} T59;

#define MENU59 ((T59 *)&D_800E1010)

extern u16 D_800E0934[];
extern u16 D_800E0954[];
extern u16 D_800E0984[];
extern u16 D_800E09B4[];
extern u16 D_800E09C4[];
extern u16 D_800E09D4[];
extern u16 D_800E09E4[];
extern u16 D_800E0A48[];
extern u16 D_800E0A88[];
extern f32 D_800E0BD8[];
extern f32 D_800E0BF4[];
extern f32 D_800E0C10[];
extern u8 *D_800E11B4[];
extern Obj *D_800E129C[];
extern s32 D_800E4478;
extern s16 D_8013FAD8;
/* declared later in main.c; re-declared here so they are in scope for func_8005907C */
extern s16 D_8010B33C;
extern s8 D_8010B341;
extern s8 D_8010B354;
extern s16 D_8013FAD4;
/* prototypes for functions main.c only declares after this point (or not at all) */
extern void func_80063F1C(void);
extern void func_8007B038(u8 *);
extern s32 func_80089C9C(void);

void func_8005907C(void) {
    u32 i;
    u32 j;
    s32 len;

    if (D_800E122C >= 0) {
        updateAndDrawRecordsMenu();
        if (D_800E122C < 0) {
            if (D_800E44A0 >= func_80089C40() - 1) {
                D_800E121C = D_800E0754[0];
            }
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1228 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        return;
    }
    if (D_800E1228 == 0x64) {
        func_80063F1C();
        if ((D_800E1228 < 0) && (D_800E122A >= 0)) {
            D_800E1228 = 0;
        }
        return;
    }
    if (D_800E122A >= 0) {
        func_80050BFC();
        return;
    }
    if ((D_800E1242 != 0) && (D_800E44A8 != 7) && (D_800E4498 >= func_80089C9C() - 1) &&
        ((func_80089D04() == D_800E44A0 + 1) || ((D_800E44A8 != 5) && (func_80089C40() == D_800E44A0 + 1)))) {
        func_80057128();
        if (D_800E1228 < 0) {
            D_800E1228 = 0x64;
            D_800E121C = -1;
            if (D_800E44A8 == 6) {
                D_800E122A = 0;
            }
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        return;
    }
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        if (D_800E44A8 == 5) {
            i = (D_800E4498 - 1) / 5;
            if (i >= D_800E07D4[D_800E0B10]) {
                i += 1;
            }
            i = i % 7;
            D_800E1258 = loadAnim(D_800E0984[i]);
            D_800E1260 = loadMesh(D_800E08D4[i]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU59->unk250, 1, &D_801026B0);
            D_800F22C0 = D_800F22C0 + D_801026B0 + 0x400;
            D_800E1258 = loadAnim(D_800E09B4[D_80113322]);
            D_800E1260 = loadMesh(D_800E08D4[D_80113322]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1278 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU59->unk250, 1, &D_801026B0);
            D_800F22C0 = D_800F22C0 + D_801026B0 + 0x400;
            guTranslateF(D_80102B28, -120.0f, -70.0f, 0.0f);
            D_800E1258 = loadAnim(0x96);
            D_800E1260 = loadMesh(0x30);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU59->unk250, 1, &D_801026B0);
            D_800F22C0 = D_800F22C0 + D_801026B0 + 0x400;
            len = D_800E4498 / 5;
            j = 0;
            for (i = 0; i < len; i++) {
                if (D_80113322 == i) {
                    j += 1;
                }
                D_800E1260 = loadMesh(D_800E09E4[j]);
                D_800E1258 = loadAnim(D_800E09D4[j]);
                D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                D_800E1280[i] = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU59->unk250, 1, &D_801026B0);
                D_800F22C0 += D_801026B0;
                D_800E1280[i]->unk48 = 0;
                if (D_8013FAD4 != 0) {
                    D_800E125C = loadAnim(D_800E09C4[j]);
                    D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                    D_800E129C[i] = LWAllocateMemory(D_800F22C0, D_800E125C, &MENU59->unk250, 1, &D_801026B0);
                    D_800F22C0 += D_801026B0;
                    D_800E1280[i]->unk48 = 0;
                }
                j += 1;
            }
            D_800E1264->unk28 = 0.0f;
            D_800E123E = 0;
            D_800E1228 = 4;
            D_800E11FC = 0;
            i = (D_800E4498 - 1) / 5;
            if (i >= D_800E07D4[D_800E0B10]) {
                i += 1;
            }
            i = i % 7;
            if (D_800E0A88[i] != 0) {
                func_8007ADF8(&D_80108828);
                func_80079B80(0x7FFF, &D_80108828);
                D_80109DA9 = 1;
                D_80109DBC = 0;
                D_80109DA4 = 0;
                loadsong(D_800E0A88[i], &D_80108828);
            }
        } else {
            D_800E125C = 0;
            D_800E1268 = NULL;
            if (D_8013FAD4 != 0) {
                D_800E126C = loadAnim(0xE2);
                D_800E1274 = loadMesh(0x5B);
                D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                D_800E1278 = LWAllocateMemory(D_800F22C0, D_800E126C, &MENU59->unk264, 1, &D_801026B0);
                D_800F22C0 += D_801026B0;
            }
            D_800E1258 = loadAnim(D_800E0934[D_800E07D4[D_800E0B10]]);
            if (D_800E0954[D_800E07D4[D_800E0B10]] != 0) {
                D_800E125C = loadAnim(D_800E0954[D_800E07D4[D_800E0B10]]);
            }
            D_800E1260 = loadMesh(D_800E08D4[D_800E07D4[D_800E0B10]]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU59->unk250, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            ((Obj59 *)D_800E1264)->unk3A = 1;
            if (D_800E125C != 0) {
                D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E125C, &MENU59->unk250, 1, &D_801026B0);
                D_800F22C0 += D_801026B0;
                ((Obj59 *)D_800E1268)->unk3A = 1;
            }
            D_800E1264->unk28 = 1.0f;
            D_800E1264->unk2C = -0.08f;
            if (D_800E0A48[D_800E07D4[D_800E0B10]] != 0) {
                func_8007ADF8(&D_80108828);
                func_80079B80(0x7FFF, &D_80108828);
                D_80109DA9 = 1;
                D_80109DBC = 0;
                D_80109DA4 = 0;
                loadsong(D_800E0A48[D_800E07D4[D_800E0B10]], &D_80108828);
            }
            if (D_8013FAD4 != 0) {
                func_8007ADF8(D_80109DC0);
                func_80079B80(0x7FFF, D_80109DC0);
                D_8010B341 = 1;
                D_8010B354 = 0;
                D_8010B33C = 0;
                loadsong(0x142, D_80109DC0);
            }
        }
        D_800E11FE = 0;
        D_800E0780 = 0;
        if (D_8013FAD4 != 0) {
            func_8003FC6C(0x28, 0x14, 0x3C, 0, 0, 0, 0, 0, 0);
        } else {
            func_8003FC6C(0xA, 0x46, 0x1E, 0, 0, 0, 0, 0, 0);
        }
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if (D_800E44A8 == 5) {
        if (D_800E1208 < 0x96) {
            func_80039854(D_800DFF00);
        }
        LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, 0, 0);
        func_8006FE64(0, 0, 0x13F, 0xEF);
        guTranslateF(D_80102BB0, (((Obj59 *)D_800E1268)->unk14->unkA8 + 40.0) / 43.0, (((Obj59 *)D_800E1268)->unk14->unkAC + 2350.058105) / 43.0,
                     (((Obj59 *)D_800E1268)->unk14->unkB0 + 4614.96582) / 43.0);
        guTranslateF(D_80102BF8, (((Obj59 *)D_800E1268)->unk14->unkA8 + 40.0) / 12.0, (((Obj59 *)D_800E1268)->unk14->unkAC + 2350.058105) / 12.0,
                     (((Obj59 *)D_800E1268)->unk14->unkB0 + 4614.96582) / 12.0);
        len = D_800E4498 / 5;
        if ((len != 0) && (D_800E123E == 0)) {
            D_800E123E = D_800E1208;
            for (i = 0; i < len; i++) {
                if (D_800E1280[i] != NULL) {
                    if (LWPlayAnimation(D_800E1280[i], D_800E1208 - D_800E1210, D_80102BF8, 0) != 0) {
                        if (((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk28C != ((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk270) {
                            D_800E123E = 0;
                            if (D_800E11FC != 0) {
                                ((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk270 = ((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk28C;
                                func_8007D45C(D_8010B358, D_800E2818, 9);
                            }
                            D_800E1280[i]->unk24 = 0;
                        } else {
                            D_800E1280[i] = NULL;
                        }
                    } else {
                        D_800E123E = 0;
                    }
                }
            }
        } else {
            for (i = 0; i < len; i++) {
                if (D_800E1280[i] != NULL) {
                    if (LWPlayAnimation(D_800E1280[i], D_800E1208 - D_800E1210, D_80102BF8, 0) != 0) {
                        if (((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk28C != ((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk270) {
                            if (D_800E11FC != 0) {
                                ((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk270 = ((T59 *)((i * 4) + (u8 *)&D_800E1010))->unk28C;
                            }
                            D_800E1280[i]->unk24 = 0;
                        } else {
                            D_800E1280[i] = NULL;
                        }
                    }
                }
            }
        }
        guTranslateF(D_80102BB0, (((Obj59 *)D_800E1268)->unk14->unkA8 + 40.0) / 43.0, (((Obj59 *)D_800E1268)->unk14->unkAC + 2350.058105) / 43.0,
                     (((Obj59 *)D_800E1268)->unk14->unkB0 + 4614.96582) / 43.0);
        guTranslateF(D_80102BF8, (((Obj59 *)D_800E1268)->unk14->unkA8 + 40.0) / 12.0, (((Obj59 *)D_800E1268)->unk14->unkAC + 2350.058105) / 12.0,
                     (((Obj59 *)D_800E1268)->unk14->unkB0 + 4614.96582) / 12.0);
        if (D_800E123E != 0) {
            if ((D_800E1208 - D_800E123E) < 0x1E) {
                LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, 0, 0);
                func_8006FE64(0, 0, 0x13F, 0xEF);
                if (LWPlayAnimation(D_800E1278, D_800E1208 - D_800E1210, D_80102BB0, D_80102B28) != 0) {
                    D_800E1278->unk24 = 0;
                }
                func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, (D_800E1208 - D_800E123E) * 0xFF / 30);
            } else {
                if (D_800E1228 < 0) {
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E1242 = 1;
                }
                D_800E1228 -= 1;
                func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, 0xFF);
            }
        } else {
            func_8007ACFC(&D_80108828);
            if ((LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, 0, 0) != 0) ||
                ((D_800E1208 >= 0x1F) && (D_8013FAD4 == 0) && (D_800DFD98 & 0xB000)) || (D_800E1264->unk24 >= 0x1C3)) {
                func_8007ADF8(&D_80108828);
                if (D_8013FAD4 != 0) {
                    D_800E11FC = 1;
                } else {
                    D_800E123E = D_800E1208;
                }
            }
            func_8006FE64(0, 0, 0x13F, 0xEF);
            if (LWPlayAnimation(D_800E1278, D_800E1208 - D_800E1210, D_80102BB0, D_80102B28) != 0) {
                D_800E1278->unk24 = 0;
            }
        }
        if ((D_800E1228 < 0) && (D_8013FAD8 != 0) && (D_800E44A0 < func_80089C40() - 1)) {
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E1242 = 1;
            if (func_80089D04() == D_800E44A0 + 1) {
                D_800E1228 = 0;
            } else {
                D_800E1228 = 0x64;
            }
        }
        return;
    }
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        if ((D_8013FAD8 != 0) && (D_800E1228 == 0)) {
            D_800E1228 = 0x64;
        } else {
            D_800E1228 = -1;
        }
        D_800E1208 = 0;
        D_800E120C = 0;
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    if (D_8013FAD4 != 0) {
        if (D_800E1278->unk24 == 0) {
            func_8007ACFC(D_80109DC0);
        }
        if (LWPlayAnimation(D_800E1278, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1278->unk24 = 0;
            func_8007B038(D_80109DC0);
        }
    }
    func_800335F0(&D_800F22B4);
    for (i = 0; i < 2; i++) {
        if (D_800E1228 == i) {
            func_80038478(&D_800F22B4, -func_800388BC(D_800E11B4[i]) - i * 5 + 0x82, i * 0x12 + 0x64, D_800E11B4[i], 0xFF,
                          0xFF, 0xFF, D_80102698);
        } else {
            func_80038478(&D_800F22B4, -func_800388BC(D_800E11B4[i]) - i * 5 + 0x82, i * 0x12 + 0x64, D_800E11B4[i], 0xE6,
                          0x61, 0x1E, D_800E1202);
        }
    }
    func_800338B0(&D_800F22B4);
    guScaleF(D_80102B28, D_800E0BD8[D_800E07D4[D_800E0B10]], D_800E0BD8[D_800E07D4[D_800E0B10]],
             D_800E0BD8[D_800E07D4[D_800E0B10]]);
    guRotateF(D_80102B68, 9.0f, 0.0f, 1.0f, 0.0f);
    guMtxCatF(D_80102B68, D_80102B28, D_80102B28);
    guTranslateF(D_80102B68, D_800E0BF4[D_800E07D4[D_800E0B10]], D_800E0C10[D_800E07D4[D_800E0B10]], 0.0f);
    guScaleF(D_80102BB0, -1.0f, 1.0f, 1.0f);
    guMtxCatF(D_80102B68, D_80102BB0, D_80102B68);
    if (D_800E11FE != 0) {
        if (D_800E1268 != NULL) {
            if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, D_80102B28, D_80102B68) != 0) {
                D_800E1268->unk24 = 0;
            }
        }
    } else {
        func_8007ACFC(&D_80108828);
        if (LWPlayAnimation(D_800E1264, (D_80109DBC != 0) ? D_800E1208 - D_800E1210 : 0, D_80102B28, D_80102B68) != 0) {
            if (D_800E1268 != NULL) {
                D_800E1268->unk28 = D_800E1264->unk28;
            }
            D_800E11FE = 1;
        }
    }
    if (D_800E1208 < 0x4B) {
        return;
    }
    if ((D_800DFD98 & 0xC00) && (D_800DFF08 == 1)) {
        D_800E0780 = 1;
        func_8007D45C(D_8010B358, D_800E2818, 2);
        D_800E1228 ^= 1;
    }
    if (((D_800DFD98 & 0xB000) && (D_800DFF08 == 1)) ||
        ((D_800E07E4[0] != 0) && (D_800E11FE != 0) && (D_800E0780 == 0))) {
        func_8007ADF8(&D_80108828);
        func_8007ADF8(D_80109DC0);
        D_800E0780 = 1;
        func_8007AEE0(D_8010B358);
        func_8007D45C(D_8010B358, D_800E2818, 3);
        switch (D_800E1228) {
        case 1:
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            switch (D_800E44A8) {
            case 5:
                if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                    D_800E122C = 1;
                    D_800E0760 = 0x4B0;
                    return;
                }
                goto reset;
            case 1:
                if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                    D_800E122C = 0;
                    D_800E0760 = 0x4B0;
                    return;
                }
                goto reset;
            case 2:
                if (insertRankedRecord(D_800E44A8, D_80113328, D_80112D18, D_80113321) != 0) {
                    D_800E122C = 3;
                    D_800E0760 = 0x4B0;
                    return;
                }
                goto reset;
            default:
            reset:
                D_800E1228 = -1;
                func_8003FD78();
                func_8003F8D8();
            }
            break;
        case 0:
            if (D_800E44A8 == 6) {
                if (D_8013FAD8 != 0) {
                    D_800E088C = 0;
                    D_800E449C = 0;
                    D_800E4498 = 0;
                    D_800E44A0 += 1;
                    D_800E4480 = 0;
                    D_800E4478 = 0;
                }
                if (D_8013FAD8 != 0) {
                    D_800E1228 = 0x64;
                } else {
                    D_800E1228 = 0;
                }
                D_800E122A = 0;
                D_800E1208 = 0;
                D_800E120C = 0;
                break;
            }
            D_800E1264->unk2C = 0.08f;
            if (D_800E1268 != NULL) {
                D_800E1268->unk2C = 0.08f;
            }
            func_8003FD78();
            func_8003F8D8();
            break;
        }
    }
}



typedef struct {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[6];
    /* 0x3A */ u8 unk3A;
} ObjAFE8;

typedef struct {
    /* 0x000 */ u8 pad0[0x250];
    /* 0x250 */ s32 unk250;
    /* 0x254 */ u8 pad254[0x264 - 0x254];
    /* 0x264 */ s32 unk264;
    /* 0x268 */ u8 pad268[0x270 - 0x268];
    /* 0x270 */ void *unk270;
    /* 0x274 */ void *unk274;
} TAFE8;

#define MENUA ((TAFE8 *)&D_800E1010)

extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern void func_8002A140(void);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern void func_8003B1A4(void);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8006FE64(s16, s16, s16, s16);
extern void func_80079B80(s32, u8 *);
extern void func_8007ACFC(u8 *);
extern void func_8007ADF8(u8 *);
extern void func_8007D45C(void *, void *, s32);
extern void loadsong(s32, u8 *);

extern s32 D_800DF710;
extern s32 D_800DF714;
extern u32 D_800DFDD4[];
extern s16 D_800E0754[];
extern s8 D_800E07CC[8];
extern u8 D_800E07D4[];
extern u8 D_800E07DC[8];
extern s8 D_800E07E4[];
extern u16 D_800E08D4[];
extern u16 D_800E0934[];
extern u16 D_800E0954[];
extern u16 D_800E0964[];
extern u16 D_800E0A48[];
extern s32 D_800E0B10;
extern s32 D_800E0B14;
extern f32 D_800E0ECC[];
extern f32 D_800E0EE8[];
extern f32 D_800E0F04[];
extern f32 D_800E0F20[];
extern f32 D_800E0F3C[];
extern f32 D_800E0F58[];
extern u8 *D_800E1010;
extern s16 D_800E11FA;
extern u16 D_800E11FE;
extern u16 D_800E1200;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s16 D_800E121C;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E1224;
extern s16 D_800E1228;
extern s32 D_800E1258;
extern s32 D_800E125C;
extern s32 D_800E1260;
extern s32 D_800E126C;
extern s32 D_800E1270;
extern s32 D_800E1274;
extern u8 D_800E2818[];
extern s32 D_800F22C0;
extern s16 D_801026A4;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern f32 D_80102B28[16];
extern f32 D_80102B68[16];
extern f32 D_80102BB0[16];
extern f32 D_80102BF8[16];
extern u8 D_80108828;
extern u16 D_80109DA4;
extern u8 D_80109DA9;
extern u8 D_80109DBC;
extern u8 D_80109DC0[];
extern u8 D_8010B358[];
extern s16 D_801125F6;
extern s16 D_80112602;
extern s16 D_8011585E;
extern s16 D_8011586A;

void func_8005AFE8(void) {
    f32 pad44;
    f32 pad40;
    f32 sp3C;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E1264 = 0;
        D_800E1268 = 0;
        D_800E1278 = 0;
        D_800E127C = 0;
        D_800E11FE = 0;
        D_800E1200 = 0;
        D_800E1260 = loadMesh(D_800E08D4[D_800E07D4[D_800E0B10]]);
        if (D_801125F6 != 0) {
            D_801026A4 = D_800E07CC[D_800E0B10];
            D_800E1258 = loadAnim(D_800E0934[D_800E07D4[D_800E0B10]]);
            if (D_800E0954[D_800E07D4[D_800E0B10]] != 0) {
                D_800E125C = loadAnim(D_800E0954[D_800E07D4[D_800E0B10]]);
            } else {
                D_800E125C = 0;
            }
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1264 = (Obj *)LWAllocateMemory(D_800F22C0, D_800E1258, &MENUA->unk250, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
        } else {
            D_800E1258 = 0;
            D_800E11FE = 1;
            if (D_800E0964[D_800E07D4[D_800E0B10]] != 0) {
                D_800E125C = loadAnim(D_800E0964[D_800E07D4[D_800E0B10]]);
            } else {
                D_800E125C = 0;
            }
        }
        if (D_800E125C != 0) {
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1268 = (Obj *)LWAllocateMemory(D_800F22C0, D_800E125C, &MENUA->unk250, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            if (D_801125F6 == 0) {
                ((ObjAFE8 *)D_800E1268)->unk30 = 0.5f;
            }
        } else {
            D_800E1268 = 0;
        }
        D_800E1274 = loadMesh(D_800E08D4[D_800E07D4[D_800E0B14]]);
        if (D_8011585E != 0) {
            D_801026A4 = D_800E07CC[D_800E0B14];
            D_800E126C = loadAnim(D_800E0934[D_800E07D4[D_800E0B14]]);
            if (D_800E0954[D_800E07D4[D_800E0B14]] != 0) {
                D_800E1270 = loadAnim(D_800E0954[D_800E07D4[D_800E0B14]]);
            } else {
                D_800E1270 = 0;
            }
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1278 = (Obj *)LWAllocateMemory(D_800F22C0, D_800E126C, &MENUA->unk264, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            ((ObjAFE8 *)D_800E1278)->unk3A = 1;
        } else {
            D_800E126C = 0;
            D_800E1200 = 1;
            if (D_800E0964[D_800E07D4[D_800E0B14]] != 0) {
                D_800E1270 = loadAnim(D_800E0964[D_800E07D4[D_800E0B14]]);
            } else {
                D_800E1270 = 0;
            }
        }
        if (D_800E1270 != 0) {
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E127C = (s32)LWAllocateMemory(D_800F22C0, D_800E1270, &MENUA->unk264, 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            ((ObjAFE8 *)D_800E127C)->unk3A = 1;
            if (D_8011585E == 0) {
                ((ObjAFE8 *)D_800E127C)->unk30 = 0.5f;
            }
        } else {
            D_800E127C = 0;
        }
        D_800E1258 = loadAnim(0x59);
        D_800E1260 = loadMesh(0x20);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        MENUA->unk270 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENUA->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1258 = loadAnim(0x5A);
        D_800E1260 = loadMesh(0x21);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        MENUA->unk274 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENUA->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if ((D_801125F6 != 0) && (D_800E0A48[D_800E07D4[D_800E0B10]] != 0)) {
            func_8007ADF8(&D_80108828);
            func_80079B80(0x7FFF, &D_80108828);
            D_80109DA9 = 1;
            D_80109DBC = 0;
            D_80109DA4 = 0;
            loadsong(D_800E0A48[D_800E07D4[D_800E0B10]], &D_80108828);
        }
        if ((D_8011585E != 0) && (D_800E0A48[D_800E07D4[D_800E0B14]] != 0)) {
            func_8007ADF8(&D_80108828);
            func_80079B80(0x7FFF, &D_80108828);
            D_80109DA9 = 1;
            D_80109DBC = 0;
            D_80109DA4 = 0;
            loadsong(D_800E0A48[D_800E07D4[D_800E0B14]], &D_80108828);
        }
        D_80112602 = D_800E07DC[D_800E0B10];
        D_8011586A = D_800E07DC[D_800E0B14];
        func_8003FC6C(0x1E, 0x28, 0x32, 0, 0, 0, 0, 0, 0);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    if (D_800E1208 < 0x1F4) {
        sp3C = 1.0f;
    } else if (D_800E1208 >= 0x259) {
        sp3C = 0.0f;
    } else {
        sp3C = 1.0 - (f32)(D_800E1208 - 0x1F4) / 100.0;
    }
    guTranslateF(D_80102BF8, sp3C * -120.0, 0.0f, 0.0f);
    if (D_801125F6 != 0) {
        LWPlayAnimation(MENUA->unk270, D_800E1208 - D_800E1210, 0, D_80102BF8);
        guScaleF(D_80102B28, D_800E0F20[D_800E07D4[D_800E0B10]], D_800E0F20[D_800E07D4[D_800E0B10]],
                 D_800E0F20[D_800E07D4[D_800E0B10]]);
        guTranslateF(D_80102B68, D_800E0F3C[D_800E07D4[D_800E0B10]] * sp3C, D_800E0F58[D_800E07D4[D_800E0B10]] * sp3C,
                     0.0f);
        guRotateF(D_80102BB0, sp3C * 9.0, 0.0f, 1.0f, 0.0f);
    } else {
        guScaleF(D_80102B28, D_800E0ECC[D_800E07D4[D_800E0B10]] * 0.75, D_800E0ECC[D_800E07D4[D_800E0B10]] * 0.75,
                 D_800E0ECC[D_800E07D4[D_800E0B10]] * 0.75);
        guTranslateF(D_80102B68, D_800E0EE8[D_800E07D4[D_800E0B10]], D_800E0F04[D_800E07D4[D_800E0B10]], 0.0f);
        guRotateF(D_80102BB0, 9.0f, 0.0f, 1.0f, 0.0f);
        if (D_800E1264 != 0) {
            ((ObjAFE8 *)D_800E1264)->unk28 = 1.0 - sp3C;
        }
        if (D_800E1268 != 0) {
            ((ObjAFE8 *)D_800E1268)->unk28 = 1.0 - sp3C;
        }
    }
    guMtxCatF(D_80102BB0, D_80102B28, D_80102B28);
    if (D_800E11FE != 0) {
        if (D_800E1268 != 0) {
            if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, D_80102B28, D_80102B68) != 0) {
                ((ObjAFE8 *)D_800E1268)->unk24 = 0;
            }
        }
    } else if (D_800E1264 != 0) {
        func_8007ACFC(&D_80108828);
        if (LWPlayAnimation(D_800E1264, (D_80109DBC != 0) ? D_800E1208 - D_800E1210 : 0, D_80102B28, D_80102B68) != 0) {
            D_800E11FE = 1;
            if (D_800E1268 != 0) {
                ((ObjAFE8 *)D_800E1268)->unk24 = 0;
            }
        }
    }
    guTranslateF(D_80102BF8, sp3C * 120.0, 0.0f, 0.0f);
    if (sp3C >= 0.0) {
        func_8006FE64(0, 0, 0x13F, 0xEF);
    }
    if (D_8011585E != 0) {
        LWPlayAnimation(MENUA->unk270, D_800E1208 - D_800E1210, 0, D_80102BF8);
        guScaleF(D_80102B28, D_800E0F20[D_800E07D4[D_800E0B14]], D_800E0F20[D_800E07D4[D_800E0B14]],
                 D_800E0F20[D_800E07D4[D_800E0B14]]);
        guTranslateF(D_80102B68, D_800E0F3C[D_800E07D4[D_800E0B14]] * sp3C, D_800E0F58[D_800E07D4[D_800E0B14]] * sp3C,
                     0.0f);
        guRotateF(D_80102BB0, sp3C * 9.0, 0.0f, 1.0f, 0.0f);
    } else {
        guScaleF(D_80102B28, D_800E0ECC[D_800E07D4[D_800E0B14]] * 0.75, D_800E0ECC[D_800E07D4[D_800E0B14]] * 0.75,
                 D_800E0ECC[D_800E07D4[D_800E0B14]] * 0.75);
        guTranslateF(D_80102B68, D_800E0EE8[D_800E07D4[D_800E0B14]], D_800E0F04[D_800E07D4[D_800E0B14]], 0.0f);
        guRotateF(D_80102BB0, 9.0f, 0.0f, 1.0f, 0.0f);
        if (D_800E1278 != 0) {
            ((ObjAFE8 *)D_800E1278)->unk28 = 1.0 - sp3C;
        }
        if (D_800E127C != 0) {
            ((ObjAFE8 *)D_800E127C)->unk28 = 1.0 - sp3C;
        }
    }
    guMtxCatF(D_80102BB0, D_80102B28, D_80102B28);
    guScaleF(D_80102BB0, -1.0f, 1.0f, 1.0f);
    guMtxCatF(D_80102B68, D_80102BB0, D_80102B68);
    if (D_800E1200 != 0) {
        if (D_800E127C != 0) {
            if (LWPlayAnimation(D_800E127C, D_800E1208 - D_800E1210, D_80102B28, D_80102B68) != 0) {
                ((ObjAFE8 *)D_800E127C)->unk24 = 0;
            }
        }
    } else if (D_800E1278 != 0) {
        func_8007ACFC(&D_80108828);
        if (LWPlayAnimation(D_800E1278, (D_80109DBC != 0) ? D_800E1208 - D_800E1210 : 0, D_80102B28, D_80102B68) != 0) {
            D_800E1200 = 1;
            if (D_800E127C != 0) {
                ((ObjAFE8 *)D_800E127C)->unk24 = 0;
            }
        }
    }
    if (D_800E1208 < 0x3C) {
        return;
    }
    if ((D_800DFDD4[D_801026A4] & 0xB000) ||
        ((*(D_800E0B10 + D_800E07E4) != 0) && (*(D_800E0B14 + D_800E07E4) != 0) && (D_800E11FE != 0) &&
         (D_800E1200 != 0))) {
        func_8007ADF8(&D_80108828);
        func_8007ADF8(D_80109DC0);
        func_8007D45C(D_8010B358, D_800E2818, 3);
        switch (D_800E1228) {
        case 1:
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1228 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
            break;
        case 0:
            D_800E1228 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
            break;
        }
    }
}




extern s16 D_800E123E;
extern s16 D_800E12F4;
extern s8 D_800E28D0;
extern s8 D_8010B341;
extern s8 D_8010B354;
extern s8 D_8010B34A;
extern s16 D_8010B33C;
extern u8 D_800ECD80[];

void func_8005C410(void) {
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        capturePreviousFramebuffer();
        D_800DFF08 = 4;
        D_800DFF10 = 0;
        SA->unk11 = 0xFF;
        D_800E11FC = 0;
        D_800E123E = 0;
        D_800E1208 = 1;
        D_800E120C = 1;
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if (D_800DFF14 >= 0x29) {
        SA->unkE = 0;
        SA->unkF = 0;
        SA->unk10 = 0;
    } else {
        SA->unkE = (-D_800DFF14 * 78 + 0xC30) / 40;
        SA->unkF = (-D_800DFF14 * 40 + 0x640) / 40;
        SA->unk10 = (-D_800DFF14 * 54 + 0x870) / 40;
    }
    if (D_800DFF08 == 1) {
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, 0xFF);
        D_800E123E += 1;
        if (D_800E123E >= 3) {
            while ((D_800E120C < 0x12C) || (D_800E12F4 == 0)) {
            }
        }
    } else {
        func_8003B1A4();
    }
    if ((D_800E1208 >= 0x12D) && (D_800E12F4 != 0)) {
        D_800E28D0 = 0;
        if (D_800E11FC == 0) {
            D_800E11FC = 1;
            while (D_800DF710 > D_800DF714) {
                func_8002A140();
            }
            D_800F22C0 = D_800F22C4;
            D_800E1258 = (s32) loadAnim(0x130);
            (&D_800E1010)[0xA8] = (u8 *)loadMesh(0x7B);
            (&D_800E1010)[0xA9] = (u8 *)loadMesh(0);
            (&D_800E1010)[0xAA] = (u8 *)loadMesh(1);
            (&D_800E1010)[0xAB] = (u8 *)loadMesh(0x31);
            (&D_800E1010)[0xAC] = (u8 *)loadMesh(3);
            (&D_800E1010)[0xAD] = (u8 *)loadMesh(4);
            (&D_800E1010)[0xAE] = (u8 *)loadMesh(5);
            (&D_800E1010)[0xAF] = (u8 *)loadMesh(6);
            (&D_800E1010)[0xB0] = (u8 *)loadMesh(0x22);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1264 = (Obj *)LWAllocateMemory(D_800F22C0, D_800E1258, (void **)((u8 *)&D_800E1010 + 0x2A0), 9, &D_801026B0);
            D_800F22C0 += D_801026B0;
            func_8007ADF8(D_80109DC0);
            func_80079B80(0x7FFF, D_80109DC0);
            D_8010B341 = 1;
            D_8010B354 = 0;
            D_8010B34A = 1;
            D_8010B33C = 0;
            loadsong(0x143, D_80109DC0);
            func_8007ACFC(D_80109DC0);
            func_80029760(D_800ECD80, func_800334D8());
        }
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1264->unk24 = 0;
        }
    }
}

void unpackPlayerName(u8 *, u8 *);

extern s16 D_800E0764;
extern s32 D_800E0B20;
extern s32 D_800E0B24;
extern s32 D_800E1018;
extern s32 D_800E10A0;
extern s32 D_800E10A4;
extern s32 D_800E10B4;
extern void *D_800E10CC[];
extern u8 D_800E13A0;
extern u8 D_800E13A4;
extern u16 D_800E94B0;
extern u8 D_80102918[];
extern u32 D_80102994[];

void updateAndDrawRecordsMenu(void) {
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 pad68;
    s32 sp64;
    s32 sp60;
    s32 pad5C;
    char sp3C[0x20];

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E10A0 = loadAsset(D_736C50, 0x96, 8);
        D_800E10A4 = loadAsset(D_736C50, 0x95, 8);
        D_800E1018 = loadAsset(D_736C50, 0x57, 8);
        D_800E10B4 = loadAsset(D_736C50, 0x98, 8);
        (&D_800E1010)[0xF] = loadAsset(D_736C50, 0x49, 8);
        (&D_800E1010)[0x10] = loadAsset(D_736C50, 0x4C, 8);
        (&D_800E1010)[0x11] = loadAsset(D_736C50, 0x5E, 8);
        if (D_800E0B20 != 2) {
            loadsong(D_800E94B0, D_80107290);
        } else {
            loadsong(D_800E0B24, D_80107290);
        }
        func_8007ACFC(D_80107290);
        D_800E11FC = 0;
        func_8003FC6C(0x17, 0x46, 0x37, 0xDC, 0xFF, 0, 0xFF, 0x28, 0xE1);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E122C = -1;
        D_800E1228 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        D_800E0764 = -1;
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, D_800E10A4, 0x15, 0x1D, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E10A0, 0x27, 0x17, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E1018, 0x4C, 0x45, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E13A4) / 255);
    func_8003396C(&D_800F22B4, D_800E10B4, 0x4C, 0x45, 0xFF, 0xFF, 0xFF, (D_800E1202 * D_800E13A0) / 255);
    func_8003396C(&D_800F22B4, (s32)(&D_800E1010)[0xF], 0x41, 0x5F, 0xFF, 0xDC, 0x3E, D_800E1202);
    if (D_800E122C == 2) {
        func_8003396C(&D_800F22B4, (s32)(&D_800E1010)[0x11], 0xFB, 0x5C, 0xFF, 0xDC, 0x3E, D_800E1202);
    } else {
        func_8003396C(&D_800F22B4, (s32)(&D_800E1010)[0x10], 0xEE, 0x5F, 0xFF, 0xDC, 0x3E, D_800E1202);
    }
    func_80038478(&D_800F22B4, 0x11F - func_800388BC(D_800E10CC[D_800E122C]), 0x44, D_800E10CC[D_800E122C], 0xFF, 0xDC, 0x3E, D_800E1202);
    sp74 = 0;
    do {
        sp3C[0x1F] = 0;
        sp70 = 0x1F;
        sp60 = -1;
        if (D_800E122C == 2) {
            sp6C = D_80102994[D_800E122C * 5 + sp74] % 60U;
            sp64 = 0;
            do {
                sp70 -= 1;
                sp3C[sp70] = (sp6C % 10) + 0x30;
                sp6C /= 10;
            } while (++sp64 < 2);
            sp70 -= 1;
            sp3C[sp70] = 0x3A;
            sp6C = D_80102994[D_800E122C * 5 + sp74] / 60U;
            do {
                sp70 -= 1;
                sp3C[sp70] = (sp6C % 10) + 0x30;
                sp6C /= 10;
            } while (sp6C > 0);
        } else {
            sp6C = D_80102994[D_800E122C * 5 + sp74];
            sp70 -= 1;
            sp3C[sp70] = 0x30;
            sp60++;
            do {
                sp60++;
                if ((sp60 != 0) && ((sp60 % 3) == 0)) {
                    sp70 -= 1;
                    sp3C[sp70] = 0x20;
                }
                sp70 -= 1;
                sp3C[sp70] = (sp6C % 10) + 0x30;
                sp6C /= 10;
            } while (sp6C > 0);
        }
        if ((D_800E122C * 5 + sp74) == D_800E0764) {
            func_80038478(&D_800F22B4, (-(sp74 * 5) - func_800388BC(&sp3C[sp70])) + 0x113, (sp74 * 0x11) + 0x6C, &sp3C[sp70], 0xFF, 0xFF, 0xFF, D_80102698);
        } else {
            func_80038478(&D_800F22B4, (-(sp74 * 5) - func_800388BC(&sp3C[sp70])) + 0x113, (sp74 * 0x11) + 0x6C, &sp3C[sp70], 0xE6, 0x61, 0x1E, D_800E1202);
        }
        unpackPlayerName(sp3C, &D_80102918[(D_800E122C * 5 + sp74) * 6 + 4]);
        sp3C[8] = 0;
        if ((D_800E122C * 5 + sp74) == D_800E0764) {
            func_80038478(&D_800F22B4, 0x3C - (sp74 * 5), (sp74 * 0x11) + 0x6C, sp3C, 0xFF, 0xFF, 0xFF, D_80102698);
        } else {
            func_80038478(&D_800F22B4, 0x3C - (sp74 * 5), (sp74 * 0x11) + 0x6C, sp3C, 0xE6, 0x61, 0x1E, D_800E1202);
        }
    } while (++sp74 < 5);
    func_800338B0(&D_800F22B4);
    if (D_800DFD98 & 0x200) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E122C > 0) {
            D_800E122C -= 1;
        } else {
            D_800E122C = 3;
        }
        D_800E0760 = 0;
    }
    if (D_800DFD98 & 0x100) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E122C < 3) {
            D_800E122C += 1;
        } else {
            D_800E122C = 0;
        }
        D_800E0760 = 0;
    }
    if ((D_800DFD98 & 0xB000) || ((D_800E0760 > 0) && ((D_800E0760 - (D_800E1208 - D_800E1210)) <= 0))) {
        func_8007D45C(D_8010B358, D_800E2818, 3);
        D_800E122C = -1;
        D_800E1228 = -1;
        D_800E1220 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        D_800E0764 = -1;
        D_800E0760 = 0;
    }
    if (D_800E0760 > 0) {
        D_800E0760 -= D_800E1208 - D_800E1210;
    }
    if (D_800DFD98 & 0x4000) {
        func_8007D45C(D_8010B358, D_800E2818, 4);
        func_8003FD78();
        func_8003F8D8();
        D_800E0760 = 0;
    }
}

extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern void func_8002A140(void);
extern u8 *loadAsset(u8 *, s32, s32);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern void func_800335F0(void *);
extern void func_800338B0(Gfx **);
extern void func_8003396C(Gfx **, UnkImg *, s32, s32, s32, s32, s32, s32);
extern void func_80038478(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern s32 func_800388BC(u8 *);
extern void func_80038A88(void);
extern void func_8003B1A4(void);
extern void func_8003F8D8(void);
extern void func_8003FB04(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8003FD78(void);
extern void func_80079B80(s32, u8 *);
extern void func_8007ACFC(u8 *);
extern void func_8007ADF8(u8 *);
extern void loadsong(s32, u8 *);
extern s32 func_80081E90(s32);

extern u8 D_736C50[];
extern s32 D_800DF710;
extern s32 D_800DF714;
extern s32 D_800DFD98;
extern UnkBg D_800DFEB0;
extern UnkImg *D_800DFEFC;
extern u16 D_800DFF08;
extern u8 *D_800E031C[];
extern u8 *D_800E0320[];
extern s16 D_800E0510[];
extern s16 D_800E0618[];
extern s16 D_800E0714[];
extern s8 D_800E0734[];
extern s16 D_800E0744[];
extern s32 D_800E0B1C;
extern u8 *D_800E1010;
extern void *D_800E1030[];
extern UnkImg *D_800E104C[];
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s32 D_800E1214;
extern s32 D_800E1218;
extern s16 D_800E122E;
extern s16 D_800E123E;
extern s16 D_800E1240;
extern s32 D_800E1258;
extern s32 D_800E1260;
extern Obj *D_800E1264;
extern s16 D_800E149C;
extern u16 D_800E28E8;
extern u16 D_800E94B4;
extern u8 D_800ECD9C[];
extern u8 D_800ECDA0[];
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern s32 D_80102B18;
extern s32 D_80102B1C;
extern Obj *D_80102FF0[];
extern void *D_801031E8[];
extern u8 D_80107290[];
extern u8 D_80108828;
extern u16 D_80109DA4;
extern u8 D_80109DA9;
extern u8 D_80109DBC;

void func_8005D674(void) {
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    register u16 w16;
    register s32 w;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        D_800E149C = 1;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        loadsong(D_800E94B4, D_80107290);
        func_80079B80(0x4FFF, D_80107290);
        func_8007ACFC(D_80107290);
        MENU->unk40 = loadAsset(D_736C50, 0xA7, 8);
        MENU->unk44 = loadAsset(D_736C50, 0xA8, 8);
        MENU->unk48 = loadAsset(D_736C50, 0xA9, 8);
        MENU->unk4C = loadAsset(D_736C50, 0xAA, 8);
        MENU->unk50 = loadAsset(D_736C50, 0xAB, 8);
        MENU->unk54 = loadAsset(D_736C50, 0xAC, 8);
        MENU->unk58 = loadAsset(D_736C50, 0xAD, 8);
        MENU->unk5C = loadAsset(D_736C50, 0xAE, 8);
        MENU->unk60 = loadAsset(D_736C50, 0xAF, 8);
        MENU->unk64 = loadAsset(D_736C50, 0xB0, 8);
        MENU->unk68 = loadAsset(D_736C50, 0xC, 8);
        MENU->unk6C = loadAsset(D_736C50, 0x43, 8);
        MENU->unk70 = loadAsset(D_736C50, 0x8E, 8);
        MENU->unk74 = loadAsset(D_736C50, 0x8F, 8);
        MENU->unk78 = loadAsset(D_736C50, 0xB2, 8);
        MENU->unk7C = loadAsset(D_736C50, 0xB3, 8);
        MENU->unk80 = loadAsset(D_736C50, 0x121, 8);
        MENU->unk84 = loadAsset(D_736C50, 0xC3, 8);
        MENU->unk88 = loadAsset(D_736C50, 0xC4, 8);
        *(void **)((u8 *)MENU + 0x8C) = loadAsset(D_736C50, 0x12E, 8);
        for (sp50 = 0; sp50 < 7; sp50++) {
            D_800E1030[sp50] = D_800DFEB0.tex[sp50];
        }
        ((UnkImg **)&D_800DFEB0)[0] = (UnkImg *) loadAsset(D_736C50, 0xB1, 8);
        for (sp50 = 1; sp50 < 7; sp50++) {
            ((UnkImg **)&D_800DFEB0)[sp50] = ((UnkImg **)&D_800DFEB0)[0];
        }
        for (sp50 = 0; sp50 < 7; sp50++) {
            D_801031E8[sp50] = loadMesh(D_800E0744[sp50]);
        }
        sp50 = 0;
        while (D_800E0714[sp50] >= 0) {
            D_800E1258 = loadAnim(D_800E0714[sp50]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_80102FF0[sp50] = LWAllocateMemory(D_800F22C0, D_800E1258, &D_801031E8[D_800E0734[sp50]], 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            D_80102FF0[sp50]->unk28 = 1.0f;
            D_80102FF0[sp50]->unk2C = -0.08f;
            sp50++;
        }
        D_800E1258 = loadAnim(0xBC);
        D_800E1260 = loadMesh(0x42);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1264->unk28 = 1.0f;
        D_800E1264->unk2C = -0.08f;
        D_800E1264->unk48 = 0;
        D_800E1214 = 0;
        D_800E1218 = 0;
        D_800E122E = 0x2710;
        D_800E123E = -1;
        D_800E1240 = 0;
        D_800E11FC = 0;
        D_80109DA9 = 1;
        D_80109DBC = 0;
        D_80109DA4 = 0;
        loadsong(0x13F, &D_80108828);
        func_8003FC6C(0, 0, 0, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if (D_800E1208 >= 0x3B) {
        if (D_800E1218 != 0) {
            sp50 = 0xC8 - (D_800E1208 - D_800E1218);
            if (sp50 < 0) {
                sp50 = 0;
            }
            func_8003FB04(sp50 * 88 / 200, sp50 * 50 / 200, sp50 * 64 / 200, sp50 * 220 / 200,
                          sp50 * 255 / 200, 0, sp50 * 100 / 200, sp50 * 80 / 200, sp50 * 255 / 200);
            sp50 = sp50 * 0x4FFF / 200;
            if (sp50 < 0) {
                sp50 = 0;
            }
            func_80079B80(sp50, D_80107290);
        } else {
            SA->unkE = 0x58;
            SA->unkF = 0x32;
            SA->unk10 = 0x40;
        }
    }
    func_8003B1A4();
    if (D_800E1208 < 0x32) {
        return;
    }
    if ((D_800DFF08 == 0) || ((D_800E1218 != 0) && (D_800E1208 >= D_800E1218 + 0xC8))) {
        func_8007ADF8(&D_80108828);
        sp50 = -D_800E0B1C * 0xD56 + 0xA008;
        if (sp50 >= 0x5000) {
            sp50 = 0x4FFF;
        }
        D_800E28E8 = sp50;
        D_800E122E = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        for (sp50 = 0; sp50 < 7; sp50++) {
            D_800DFEB0.tex[sp50] = D_800E1030[sp50];
        }
        return;
    }
    if (D_800E1214 == 0) {
        if (D_800E1264->unk24 == 0) {
            func_8007ACFC(&D_80108828);
        }
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1264->unk2C = 0.08f;
            if ((f64) D_800E1264->unk28 == 1.0) {
                D_800E1214 = D_800E1208 + 0x32;
            }
        }
        if ((D_800E11FC == 0) && (D_800DFD98 & 0xB000)) {
            D_800E11FC = 1;
            if (D_800E1264 != NULL) {
                D_800E1264->unk2C = 0.08f;
            }
            func_8003FD78();
            func_8003F8D8();
        }
        return;
    }
    func_80038A88();
    if (D_800E1208 < D_800E1214) {
        if ((D_800E11FC == 0) && (D_800DFD98 & 0xB000)) {
            D_800E11FC = 1;
            func_8003FD78();
            func_8003F8D8();
        }
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if ((D_800E122E == 0x2710) || (D_800E0510[D_800E122E + 1] >= 0)) {
        if ((D_800E123E >= 0) && (D_800E0714[D_800E123E] >= 0)) {
            if (LWPlayAnimation(D_80102FF0[D_800E123E], D_800E1208 - D_800E1210, 0, 0) != 0) {
                D_80102FF0[D_800E123E]->unk2C = 0.08f;
                if ((f64) D_80102FF0[D_800E123E]->unk28 >= 1.0) {
                    D_800E123E = -1;
                }
            }
        }
        func_800335F0(&D_800F22B4);
        if ((D_800E122E == 0x2710) || ((D_800E1210 - D_800E1214) % 200 > (D_800E1208 - D_800E1214) % 200)) {
            if (D_800E122E == 0x2710) {
                D_800E122E = 0;
            } else {
                D_800E122E += D_800E0618[D_800E122E];
            }
            if ((D_800E123E < 0) && (D_80102FF0[D_800E1240] != NULL)) {
                D_800E123E = D_800E1240++;
            }
            if ((D_800E1218 == 0) && (D_800E0510[D_800E122E + 1] < 0)) {
                D_800E1218 = D_800E1208;
                func_800338B0(&D_800F22B4);
                return;
            }
            if ((D_800E0510[D_800E122E + 1] != 0x63) && (D_800E0510[D_800E122E + 1] >= 0) &&
                (D_800E0510[D_800E122E + 1] != D_800E0510[D_800E122E])) {
                sp48 = 0;
                sp50 = D_800E104C[D_800E0510[D_800E122E + 1]]->width;
                for (sp4C = 0; sp4C < 0x7D; sp4C++) {
                    if (D_800E0510[sp4C + 1] == D_800E0510[D_800E122E + 1]) {
                        sp48++;
                        if (sp50 < func_800388BC(D_800E031C[sp4C])) {
                            sp50 = func_800388BC(D_800E031C[sp4C]);
                        }
                    }
                }
                w16 = func_80081E90(-sp50 - D_800E0618[D_800E122E] * 5 + 0xF5),
                D_80102B18 = D_800E0618[D_800E122E] * 5 + (w16 + sp50) + 0x19;
                D_80102B1C = func_80081E90(0xB2 - D_800E0618[D_800E122E] * 0x12) + 0x28;
            }
        }
        sp50 = (D_800E1208 - D_800E1214) % 200;
        if (sp50 < 0x1E) {
            sp54 = sp50 * 255 / 30;
        } else if (sp50 < 0x96) {
            sp54 = 0xFF;
        } else {
            sp54 = (-sp50 * 255 + 0xB34C) / 30;
        }
        sp54 = D_800E1202 * sp54 / 255;
        if (D_800E0510[D_800E122E + 1] != 0x63) {
            if ((sp50 < 0x1E) && (D_800E0510[D_800E122E + 1] != D_800E0510[D_800E122E])) {
                func_8003396C(&D_800F22B4, D_800E104C[D_800E0510[D_800E122E + 1]],
                              D_80102B18 - D_800E104C[D_800E0510[D_800E122E + 1]]->width + 5,
                              D_80102B1C - D_800E104C[D_800E0510[D_800E122E + 1]]->height, 0xFF, 0xDC, 0x3E, sp54);
            } else if ((sp50 >= 0x96) &&
                       ((&MENU->unk3C)[D_800E0510[D_800E122E + 1]] !=
                        (&MENU->unk3C)[D_800E0510[D_800E0618[D_800E122E] + D_800E122E + 1]])) {
                if (sp50 < 0xB4) {
                    func_8003396C(&D_800F22B4, D_800E104C[D_800E0510[D_800E122E + 1]],
                                  D_80102B18 - D_800E104C[D_800E0510[D_800E122E + 1]]->width + 5,
                                  D_80102B1C - D_800E104C[D_800E0510[D_800E122E + 1]]->height, 0xFF, 0xDC, 0x3E, sp54);
                }
            } else {
                func_8003396C(&D_800F22B4, D_800E104C[D_800E0510[D_800E122E + 1]],
                              D_80102B18 - D_800E104C[D_800E0510[D_800E122E + 1]]->width + 5,
                              D_80102B1C - D_800E104C[D_800E0510[D_800E122E + 1]]->height, 0xFF, 0xDC, 0x3E, D_800E1202);
            }
        }
        if (sp50 < 0xB4) {
            if (D_800E0510[D_800E122E + 1] == 0x63) {
                w = func_800388BC(D_800E031C[D_800E122E]),
                func_80038478(&D_800F22B4, 0xA0 - (w >> 1), 0x6A, D_800E031C[D_800E122E], 0xE6, 0x61, 0x1E, sp54);
                w = func_800388BC(D_800E0320[D_800E122E]),
                func_80038478(&D_800F22B4, 0xA0 - (w >> 1), 0x7A, D_800E0320[D_800E122E], 0xE6, 0x61, 0x1E, sp54);
            } else {
                for (sp4C = 0; sp4C < D_800E0618[D_800E122E]; sp4C++) {
                    if (D_800E0510[D_800E122E + sp4C + 1] == D_800E0510[D_800E122E + 1]) {
                        if (D_800E0510[D_800E122E + 1] == 1) {
                            w = func_800388BC(D_800ECD9C),
                            func_80038478(&D_800F22B4, D_80102B18 - w - sp4C * 5 + 2, sp4C * 0x12 + D_80102B1C - 5,
                                          D_800ECDA0, 0xE6, 0x61, 0x1E, sp54);
                        }
                        w = func_800388BC(D_800E031C[D_800E122E + sp4C]),
                        func_80038478(&D_800F22B4, D_80102B18 - w - sp4C * 5, sp4C * 0x12 + D_80102B1C,
                                      D_800E031C[D_800E122E + sp4C], 0xE6, 0x61, 0x1E, sp54);
                    }
                }
            }
        }
        func_800338B0(&D_800F22B4);
    }
    if ((D_800E1218 == 0) && (D_800E0510[D_800E122E + 1] < 0)) {
        D_800E1218 = D_800E1208;
    }
    if ((D_800E11FC == 0) && (D_800DFD98 & 0xB000)) {
        D_800E11FC = 1;
        if (D_80102FF0[D_800E123E] != NULL) {
            D_80102FF0[D_800E123E]->unk2C = 0.08f;
        }
        func_8003FD78();
        func_8003F8D8();
    }
}

/* func_8005EE48 -- 2P versus options/select menu driver (main, IDO 5.3 -O1 -g -mips1) */

extern void func_8002A140(void);
extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern u8 *loadAsset(u8 *, s32, s32);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern void func_800335F0(void *);
extern void func_800338B0(Gfx **);
extern void func_80038478(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern s32 func_800388BC(u8 *);
extern void func_8003B1A4(void);
extern void func_8003F8D8(void);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8003FD78(void);
extern void func_8007D45C(void *, void *, s32);
extern s32 func_80089C9C(void);
extern s32 func_80089D60(void);
extern void func_800CC6E0(void);

extern u8 D_736C50[];
extern s32 D_800DF710;
extern s32 D_800DF714;
extern s16 D_800DFD50;
extern s16 D_800DFD54;
extern u32 D_800DFDD4[];
extern u16 D_800DFF08;
extern s16 D_800E0754[];
extern s8 D_800E07CC[8];
extern s32 D_800E088C;
extern u16 D_800E09E4[];
extern u16 D_800E09F4[];
extern s32 D_800E0B0C;
extern s32 D_800E0B10;
extern s32 D_800E0B18;
extern u8 *D_800E1010;
extern void *D_800E1028;
extern s32 D_800E10B4;
extern void *D_800E10CC[];
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s32 D_800E1214;
extern s16 D_800E121C;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E1224;
extern s16 D_800E122A;
extern s16 D_800E1232;
extern s16 D_800E1234;
extern s32 D_800E1258;
extern s32 D_800E1260;
extern Obj *D_800E1280[];
extern s16 D_800E12DC;
extern u8 D_800E13A0;
extern u8 D_800E13A4;
extern u8 D_800E2818[];
extern s16 D_800E4498;
extern s16 D_800E449C;
extern s16 D_800E44A0;
extern s16 D_800E44A8;
extern u8 D_800ECDA4[];
extern u8 D_800ECDB0[];
extern u8 D_800ECDB4[];
extern u8 D_800ECDC4[];
extern u8 D_800ECDCC[];
extern u8 D_800ECDD4[];
extern u8 D_800ECDDC[];
extern u8 D_800ECDE4[];
extern u8 D_800ECDEC[];
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern s16 D_80102666;
extern char D_80102670[];
extern u8 D_80102698;
extern s32 D_801026A8;
extern s32 D_801026AC;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern s16 D_80102BA8;
extern s16 D_80102BF0;
extern s16 D_80102C38;
extern u8 D_8010B358[];
extern s16 D_801125C6;
extern s32 D_80112D18;
extern s8 D_80113322;
extern s32 D_80113328;

void func_8005EE48(void) {
    u32 i;
    s32 val;
    u8 *str;
    register s32 w;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_80102BA8 = func_80089D60();
        D_80102BF0 = func_80089C9C();
        if (D_800E12DC != 0) {
            D_800E4498 = D_80102BF0 - 1;
            D_80102666 = D_80102BA8 - 1;
        }
        D_80102C38 = D_800E449C;
        MENU->unk3C = loadAsset(D_736C50, 3, 8);
        MENU->unk40 = loadAsset(D_736C50, 0x1E, 8);
        MENU->unk44 = loadAsset(D_736C50, 0x7F, 8);
        MENU->unkC = loadAsset(D_736C50, 0x19, 8);
        MENU->unk10 = loadAsset(D_736C50, 0x47, 8);
        D_800E1028 = loadAsset(D_736C50, 0x57, 8);
        D_800E10B4 = loadAsset(D_736C50, 0x98, 8);
        if (D_800E44A0 >= D_80102BA8) {
            D_800E44A0 = D_80102BA8 - 1;
        }
        D_800E11FC = 0;
        for (i = 0; i < 7; i++) {
            D_800E1260 = loadMesh(D_800E09E4[i]);
            D_800E1258 = loadAnim(D_800E09F4[i]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1280[i] = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E1258, (void **)((u8 *)&D_800E1010 + 0x250), 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
        }
        i = D_80102BF0 - 1;
        if ((i != 0) && (D_800E4498 > i)) {
            D_800E4498 = i;
            D_800E449C = i;
        }
        func_8003FC6C(0x17, 0x46, 0x37, 0xDC, 0xFF, 0, 0xFF, 0x28, 0xE1);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E1232 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        if (D_800E44A8 == 6) {
            D_800E4498 = 0;
            D_800E449C = 0;
        }
        if (D_800E11FC != 0) {
            D_800E4498 = D_800E449C;
            if ((D_800E44A8 == 5) && (D_800E4498 == 0) && (D_800E44A0 == 0)) {
                D_800E1234 = 0;
            } else {
                D_800E121C = -1;
                D_800E1220 = -1;
                D_800E1222 = -1;
                D_800E1224 = -1;
                if (D_800E44A8 == 4) {
                    D_800DFD54 = 1;
                    D_800DFD50 = 1;
                    if (D_800E449C < D_80102C38) {
                        D_800DFD54 = 0;
                    }
                    if (D_800E449C > D_80102C38) {
                        D_800DFD50 = 0;
                    }
                }
            }
            D_801125C6 = 1;
            func_800CC6E0();
            D_80112D18 = 0;
        }
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, MENU->unk3C, 0xB4, 0x78, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unk40, 0xF9, 0x79, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unk44, 0x1F, 0x6B, 0xFF, 0xFF, 0xFF, D_800E1202);
    if (D_800E1232 == 0) {
        val = (D_800E1202 * D_800E13A4) / 255;
    } else {
        val = (D_800E1202 * 0x8C) / 255;
    }
    func_8003396C(&D_800F22B4, D_800E1028, 0xE8, 0x90, 0xFF, 0xFF, 0xFF, val);
    if (D_800E1232 == 0) {
        val = (D_800E1202 * D_800E13A0) / 255;
    }
    func_8003396C(&D_800F22B4, D_800E10B4, 0xE8, 0x90, 0xFF, 0xFF, 0xFF, val);
    if ((D_80102BA8 >= 2) && (D_800E44A8 != 6)) {
        if (D_800E1232 == 1) {
            val = (D_800E1202 * D_800E13A4) / 255;
        } else {
            val = (D_800E1202 * 0x8C) / 255;
        }
        func_8003396C(&D_800F22B4, D_800E1028, 0xE3, 0xA3, 0xFF, 0xFF, 0xFF, val);
        if (D_800E1232 == 1) {
            val = (D_800E1202 * D_800E13A0) / 255;
        }
        func_8003396C(&D_800F22B4, D_800E10B4, 0xE3, 0xA3, 0xFF, 0xFF, 0xFF, val);
    }
    func_80038478(&D_800F22B4, 0x3D, 0x1F, D_800ECDA4, 0xE6, 0x61, 0x1E, D_800E1202);
    func_80038478(&D_800F22B4, 0xA6, 0x1F, D_80113328, 0xFF, 0xDC, 0x3E, D_800E1202);
    w = func_800388BC(D_80113328), func_80038478(&D_800F22B4, w + 0xA6, 0x1F, D_800ECDB0, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_80038478(&D_800F22B4, 0x5C, 0x32, D_800ECDB4, 0xE6, 0x61, 0x1E, D_800E1202);
    if ((D_800E44A8 == 5) || (D_800E44A8 == 2)) {
        func_80038478(&D_800F22B4, 0x3A, 0x7A, D_800E10CC[((s16 *)D_800E0754)[1]], 0xE6, 0x61, 0x1E, D_800E1202);
    } else {
        func_80038478(&D_800F22B4, 0x33, 0x8F, D_800E10CC[((s16 *)D_800E0754)[1]], 0xE6, 0x61, 0x1E, D_800E1202);
    }
    if (D_800E1232 == 0) {
        if (D_800E44A8 == 6) {
            func_80038478(&D_800F22B4, 0x82, 0x8F, D_800ECDC4, 0xFF, 0xFF, 0xFF, D_80102698);
        } else {
            func_80038478(&D_800F22B4, 0x82, 0x8F, D_800ECDCC, 0xFF, 0xFF, 0xFF, D_80102698);
        }
    } else if (D_800E44A8 == 6) {
        func_80038478(&D_800F22B4, 0x82, 0x8F, D_800ECDD4, 0xFF, 0xDC, 0x3E, (D_800E1202 * 0x8C) / 255);
    } else {
        func_80038478(&D_800F22B4, 0x82, 0x8F, D_800ECDDC, 0xFF, 0xDC, 0x3E, (D_800E1202 * 0x8C) / 255);
    }
    if (D_800E44A8 == 5) {
        D_80102670[0] = (D_800E449C / 5) + 0x31;
        D_80102670[1] = 0x3A;
        D_80102670[2] = (D_800E449C % 5) + 0x31;
        str = D_80102670;
    } else if (D_800E44A8 == 6) {
        str = func_8003E358(D_800E44A0 + 1);
    } else {
        str = func_8003E358(D_800E449C + 1);
    }
    if (D_800E1232 == 0) {
        w = func_800388BC(str), func_80038478(&D_800F22B4, 0xE1 - w, 0x8F, str, 0xE6, 0x61, 0x1E, D_800E1202);
    } else {
        w = func_800388BC(str), func_80038478(&D_800F22B4, 0xE1 - w, 0x8F, str, 0xE6, 0x61, 0x1E, (D_800E1202 * 0x8C) / 255);
    }
    if ((D_80102BA8 >= 2) && (D_800E44A8 != 6)) {
        str = func_8003E358(D_800E44A0 + 1);
        if (D_800E1232 == 1) {
            func_80038478(&D_800F22B4, 0x7D, 0xA2, D_800ECDE4, 0xFF, 0xFF, 0xFF, D_80102698);
            w = func_800388BC(str), func_80038478(&D_800F22B4, 0xDC - w, 0xA2, str, 0xE6, 0x61, 0x1E, D_800E1202);
        } else {
            func_80038478(&D_800F22B4, 0x7D, 0xA2, D_800ECDEC, 0xFF, 0xDC, 0x3E, (D_800E1202 * 0x8C) / 255);
            w = func_800388BC(str), func_80038478(&D_800F22B4, 0xDC - w, 0xA2, str, 0xE6, 0x61, 0x1E, (D_800E1202 * 0x8C) / 255);
        }
    }
    func_8003396C(&D_800F22B4, MENU->unkC, 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
    func_8003396C(&D_800F22B4, MENU->unk10, 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_800338B0(&D_800F22B4);
    if (D_800E11FC != 0) {
        if (D_800E11FC < 0x3C) {
            if (D_800E44A8 == 5) {
                i = D_800E449C / 5;
                if (i >= D_80113322) {
                    i++;
                }
            } else {
                i = 0;
            }
            val = 0;
            for (; i < 7; i++) {
                if (D_800E1210 == D_800E1214) {
                    val = ((i * 3) % 7) * 4;
                }
                if (D_80113322 != i) {
                    LWPlayAnimation(D_800E1280[i], (D_800E1208 - D_800E1210) + val, NULL, NULL);
                }
            }
        } else if (D_800E11FC == 0x3C) {
            func_8003FD78();
            func_8003F8D8();
        }
        D_800E11FC++;
    }
    if ((D_800DFDD4[D_800E07CC[D_800E0B10]] & 0x100) && (D_800E11FC == 0)) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if ((D_800E1232 == 0) && (D_800E44A8 != 6)) {
            D_800E449C++;
        } else {
            D_800E44A0++;
        }
    }
    if ((D_800DFDD4[D_800E07CC[D_800E0B10]] & 0x200) && (D_800E11FC == 0)) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if ((D_800E1232 == 0) && (D_800E44A8 != 6)) {
            D_800E449C--;
        } else {
            D_800E44A0--;
        }
    }
    if (D_800E449C >= D_80102BF0) {
        D_800E44A0++;
        D_800E449C = 0;
    }
    if ((D_800E44A0 == D_80102666) && (D_800E449C > D_800E4498)) {
        D_800E44A0++;
        D_800E449C = 0;
    }
    if (D_800E44A0 > D_80102666) {
        D_800E44A0 = 0;
    }
    if (D_800E449C < 0) {
        D_800E44A0--;
        D_800E449C = D_80102BF0 - 1;
    }
    if (D_800E44A0 < 0) {
        D_800E44A0 = D_80102666;
        D_800E449C = D_800E4498;
    }
    if ((D_800E44A8 != 6) && (D_80102BA8 >= 2) && (D_800DFDD4[D_800E07CC[D_800E0B10]] & 0xC00) && (D_800E11FC == 0)) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        D_800E1232 ^= 1;
    }
    if (D_800DFDD4[D_800E07CC[D_800E0B10]] & 0xB000) {
        if (D_800E11FC != 0) {
            func_8003FD78();
            func_8003F8D8();
            if (D_800E44A8 == 5) {
                i = D_800E449C / 5;
                if (i >= D_80113322) {
                    i++;
                }
            } else {
                i = 0;
            }
            for (; i < 7; i++) {
                if (D_80113322 != i) {
                    D_800E1280[i]->unk2C = 0.08f;
                }
            }
        } else {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            D_800E11FC = 1;
            D_800E1214 = D_800E1208;
            if (D_800E44A8 == 6) {
                D_800E4498 = 0;
                D_800E449C = 0;
                D_800E088C = 0;
                D_800E0B0C = 2;
                D_800E0B18 = 1;
                D_801026A8 = -1;
                D_801026AC = 1;
                D_800E122A = 0;
                D_800E1232 = -1;
                D_800E1208 = 0;
                D_800E120C = 0;
            }
        }
    }
    if (D_800DFDD4[D_800E07CC[D_800E0B10]] & 0x4000) {
        if (D_800E11FC == 0) {
            func_8007D45C(D_8010B358, D_800E2818, 4);
            func_8003FD78();
            func_8003F8D8();
        }
    }
}

extern void func_8002A140(void);
extern u8 *loadAsset(u8 *, s32, s32);
extern void func_80038284(UnkImg *);
extern void *loadAnim(s32);
extern void *loadMesh(s32);
extern u8 *LWAllocateMemory(u32, void *, void **, s32, s32 *);
extern void func_8003FC6C(u8, u8, u8, u8, u8, u8, u8, u8, u8);
extern void func_8003B1A4(void);
extern void func_800CC6E0(void);
extern void requestSaveDataWrite(void);
extern void func_80038A88(void);
extern void func_800335F0(void *);
extern void func_8003396C(Gfx **, UnkImg *, s32, s32, s32, s32, s32, s32);
extern void func_800338B0(Gfx **);
extern s32 LWPlayAnimation(void *, s32, void *, void *);
extern char *func_8003E358(s32);
extern void func_80038478(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern void func_800384E4(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern void func_8007D45C(void *, void *, s32);
extern void func_8003FD78(void);
extern void func_8003F8D8(void);
extern void guScaleF(f32 (*)[4], f32, f32, f32);
extern void guTranslateF(f32 (*)[4], f32, f32, f32);

extern u8 D_736C50[];
extern s32 D_800DF710;
extern s32 D_800DF714;
extern s32 D_800DFD98;
extern u16 D_800DFF08;
extern s8 D_800E07CC[8];
extern u8 D_800E0890[];
extern u8 D_800E0898;
extern s16 D_800E089C;
extern s16 D_800E08A4;
extern s16 D_800E08A8;
extern s16 D_800E08AC;
extern s16 D_800E08B0;
extern u16 D_800E0AA8[];
extern u16 D_800E0AB4[];
extern s32 D_800E0B10;
extern u8 *D_800E1010;
extern void *D_800E1014;
extern s32 D_800E1018;
extern void *D_800E1024;
extern void *D_800E1028;
extern void *D_800E102C;
extern void *D_800E10A8;
extern s32 D_800E10B4;
extern s16 D_800E11FA;
extern u16 D_800E11FC;
extern s16 D_800E1202;
extern s16 D_800E1204;
extern s16 D_800E1206;
extern s32 D_800E1208;
extern s32 D_800E120C;
extern s32 D_800E1210;
extern s16 D_800E121C;
extern s16 D_800E1220;
extern s16 D_800E1222;
extern s16 D_800E122A;
extern s16 D_800E1232;
extern u16 D_800E1232_u16; /* alias of D_800E1232 @ 0x800E1232 — jtbl switch needs a bare lhu */
extern s16 D_800E123E;
extern s32 D_800E1258;
extern s32 D_800E1260;
extern Obj *D_800E1280[];
extern u8 D_800E13A0;
extern u8 D_800E13A4;
extern u8 D_800E2818[];
extern u8 D_800ECDF4[];
extern u8 D_800ECDF8[];
extern Gfx *D_800F22B4;
extern s32 D_800F22C0;
extern u8 D_80102698;
extern s32 D_801026B0;
extern s32 D_801026B8;
extern u8 D_80102AC3;
extern u8 D_80102B04;
extern u8 D_80102B05;
extern u8 D_80102B06;
extern f32 D_80102B28[16];
extern f32 D_80102B68[16];
extern u8 D_8010B358[];
extern s16 D_801125C6;
extern s32 D_80112D18;
extern s8 D_80113320;
extern s8 D_80113322;
extern s8 D_80113323;
extern s32 D_80113328;
extern s16 D_8015D980;

void func_80060630(void) {
    u32 i;
    s32 sp50;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        (&D_800E1010)[3] = loadAsset(D_736C50, 0x19, 8);
        (&D_800E1010)[4] = loadAsset(D_736C50, 0x47, 8);
        D_800E1018 = loadAsset(D_736C50, 0x6E, 8);
        D_800E1024 = loadAsset(D_736C50, 0x55, 8);
        (&D_800E1010)[8] = loadAsset(D_736C50, 0x3A, 8);
        (&D_800E1010)[9] = loadAsset(D_736C50, 0x6F, 8);
        (&D_800E1010)[10] = loadAsset(D_736C50, 0x71, 8);
        (&D_800E1010)[12] = loadAsset(D_736C50, 0x12, 8);
        D_800E1014 = loadAsset(D_736C50, 0xC2, 8);
        func_80038284(D_800E1014);
        if (D_8015D980 == 2) {
            (&D_800E1010)[11] = loadAsset(D_736C50, 0xE, 8);
        } else {
            (&D_800E1010)[11] = loadAsset(D_736C50, 0x72, 8);
        }
        D_800E102C = loadAsset(D_736C50, 0x70, 8);
        D_800E1028 = loadAsset(D_736C50, 0xBC, 8);
        D_800E10A8 = loadAsset(D_736C50, 0x57, 8);
        D_800E10B4 = loadAsset(D_736C50, 0x98, 8);
        for (i = 0; i < 6; i++) {
            D_800E1258 = (s32) loadAnim(D_800E0AA8[i]);
            D_800E1260 = (s32) loadMesh(D_800E0AB4[i]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1280[i] = (Obj *) LWAllocateMemory(D_800F22C0, (void *) D_800E1258, (void **)((u8 *)&D_800E1010 + 0x250), 1, &D_801026B0);
            D_800F22C0 += D_801026B0;
            D_800E1280[i]->unk48 = 1;
        }
        D_800E123E = 0;
        D_800E11FC = 0;
        func_8003FC6C(0x17, 0x46, 0x37, 0xDC, 0xFF, 0, 0xFF, 0x28, 0xE1);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E1208 = 0;
        D_800E120C = 0;
        D_800E1232 = -1;
        D_800E122A = -1;
        if (D_8015D980 == 2) {
            D_800E1222 = 0;
        } else if (D_800E11FC != 0) {
            D_800E121C = -1;
            D_800E1220 = -1;
            D_80113320 = D_800E07CC[D_800E0B10];
            D_80113323 = 0;
            D_80113328 = (s32) D_800ECDF4;
            D_80113322 = 4;
            D_801125C6 = 1;
            func_800CC6E0();
            D_80112D18 = 0;
        }
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[3], 0xCE, 0xD2, 0xE6, 0x61, 0x1E, D_800E1202);
    func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[4], 0xCE, 0xD2, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E1024, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, (UnkImg *) D_800E1018, 0xD7, 0x2F, 0xFF, 0xFF, 0xFF, D_800E1202);
    if (D_800E1232 == 0) {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[8], 0xED, 0x2B, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[8], 0xED, 0x2B, 0xFF, 0xDC, 0x3E, D_800E1202 * 0x8C / 255);
    }
    if (D_800E1232 == 1) {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[9], 0xD8, 0x52, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[9], 0xD8, 0x52, 0xFF, 0xDC, 0x3E, D_800E1202 * 0x8C / 255);
    }
    if (D_800E1232 == 2) {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[10], 0xB3, 0x94, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[10], 0xB3, 0x94, 0xFF, 0xDC, 0x3E, D_800E1202 * 0x8C / 255);
    }
    if (D_800E1232 == 2) {
        sp50 = D_800E1202 * D_800E13A4 / 255;
    } else {
        sp50 = D_800E1202 * 0x8C / 255;
    }
    func_8003396C(&D_800F22B4, D_800E10A8, 0x37, 0x91, 0xFF, 0xFF, 0xFF, sp50);
    if (D_800E1232 == 2) {
        sp50 = D_800E1202 * D_800E13A0 / 255;
    }
    func_8003396C(&D_800F22B4, (UnkImg *) D_800E10B4, 0x37, 0x91, 0xFF, 0xFF, 0xFF, sp50);
    if (D_800E1232 == 2) {
        sp50 = D_800E1202;
    } else {
        sp50 = D_800E1202 * 0x8C / 255;
    }
    func_80038478(&D_800F22B4, 0x52, 0x91, (u8 *) func_8003E358(D_800E0898), 0xE6, 0x61, 0x1E, sp50);
    if (D_800E1232 == 3) {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[11], (D_8015D980 == 1) ? 0x93 : 0xA6, 0xA8, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[11], (D_8015D980 == 1) ? 0x93 : 0xA6, 0xA8, 0xFF, 0xDC, 0x3E, D_800E1202 * 0x8C / 255);
    }
    if (D_800E1232 == 4) {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[12], 0xD9, 0x3D, 0xFF, 0xFF, 0xFF, D_80102698);
    } else {
        func_8003396C(&D_800F22B4, (UnkImg *) (&D_800E1010)[12], 0xD9, 0x3D, 0xFF, 0xDC, 0x3E, D_800E1202 * 0x8C / 255);
    }
    if (D_800E1232 == 3) {
        sp50 = D_800E1202 * D_800E13A4 / 255;
    } else {
        sp50 = D_800E1202 * 0x8C / 255;
    }
    func_8003396C(&D_800F22B4, D_800E10A8, 0x30, 0xA7, 0xFF, 0xFF, 0xFF, sp50);
    if (D_800E1232 == 3) {
        sp50 = D_800E1202 * D_800E13A0 / 255;
    }
    func_8003396C(&D_800F22B4, (UnkImg *) D_800E10B4, 0x30, 0xA7, 0xFF, 0xFF, 0xFF, sp50);
    if (D_800E1232 == 3) {
        sp50 = D_800E1202;
    } else {
        sp50 = D_800E1202 * 0x8C / 255;
    }
    if (D_8015D980 == 1) {
        func_80038478(&D_800F22B4, 0x4B, 0xA7, (u8 *) func_8003E358(D_800E089C), 0xE6, 0x61, 0x1E, sp50);
    } else {
        func_800384E4(&D_800F22B4, 0x4B, 0xA7, D_800ECDF8, 0xFF, 0xDC, 0x3E, (u32) (sp50 * 0xC8) / 255U);
        D_800E08A8 = (D_800E08A4 >> 1) + 1;
        D_800E08AC = 0;
        D_800E08B0 = 0;
        func_80038478(&D_800F22B4, 0x6A, 0xA7, (u8 *) func_8003E358(D_800E08A8), 0xE6, 0x61, 0x1E, sp50);
        func_80038478(&D_800F22B4, 0x87, 0xA7, (u8 *) func_8003E358(D_800E08A4), 0xE6, 0x61, 0x1E, sp50);
    }
    if (D_800E1232 == 1) {
        sp50 = D_800E1202;
    } else {
        sp50 = D_800E1202 * 0x8C / 255;
    }
    func_8003396C(&D_800F22B4, D_800E102C, 0x3D, 0x66, 0xFF, 0xFF, 0xFF, sp50);
    if (D_800E1232 == 1) {
        func_8003396C(&D_800F22B4, D_800E1028, D_800E123E * 0x21 + 0x3D, 0x6C, 0xFF, 0xFF, 0xFF, D_800E1202);
    }
    func_800338B0(&D_800F22B4);
    for (i = 0; i < 6; i++) {
        guTranslateF((f32 (*)[4]) D_80102B28, i * 60.0 - 147.0, 0.0f, 0.0f);
        guScaleF((f32 (*)[4]) D_80102B68, 0.25f, 0.25f, 0.25f);
        sp50 = (D_800E0890[i] != 0) ? (D_800E1208 - D_800E1210) : ((D_800E1280[i]->unk24 != 0) ? (D_800E1208 - D_800E1210) * 4 : 0);
        D_800E1280[i]->unk28 = ((D_800E1232 == 1) && (D_800E123E == i)) ? 0.0 : ((sp50 != 0) ? 0.5 : 0.8);
        if (LWPlayAnimation(D_800E1280[i], sp50, D_80102B68, D_80102B28) != 0) {
            D_800E1280[i]->unk24 = 0;
        }
    }
    if (D_800DFD98 & 0x400) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1232 == 0) {
            D_800E1232 = 4;
        } else if (D_800E1232 == 4) {
            D_800E1232 = 1;
        } else if (D_800E1232 < 3) {
            D_800E1232 += 1;
        } else {
            D_800E1232 = 0;
        }
    }
    if (D_800DFD98 & 0x800) {
        func_8007D45C(D_8010B358, D_800E2818, 2);
        if (D_800E1232 == 1) {
            D_800E1232 = 4;
        } else if (D_800E1232 == 4) {
            D_800E1232 = 0;
        } else if (D_800E1232 > 0) {
            D_800E1232 -= 1;
        } else {
            D_800E1232 = 3;
        }
    }
    switch (D_800E1232_u16) {
    case 0:
        break;
    case 1:
        if (D_800DFD98 & 0x200) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E123E > 0) {
                D_800E123E -= 1;
            } else {
                D_800E123E = 5;
            }
        }
        if (D_800DFD98 & 0x100) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E123E < 5) {
                D_800E123E += 1;
            } else {
                D_800E123E = 0;
            }
        }
        break;
    case 2:
        if (D_800DFD98 & 0x200) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E0898 >= 2) {
                D_800E0898 -= 1;
            } else {
                D_800E0898 = 5;
            }
        }
        if (D_800DFD98 & 0x100) {
            func_8007D45C(D_8010B358, D_800E2818, 2);
            if (D_800E0898 < 5) {
                D_800E0898 += 1;
            } else {
                D_800E0898 = 1;
            }
        }
        break;
    case 3:
        if (D_8015D980 == 1) {
            if (D_800DFD98 & 0x200) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                if (D_800E089C >= 4) {
                    D_800E089C -= 1;
                } else {
                    D_800E089C = 0x63;
                }
            }
            if (D_800DFD98 & 0x100) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                if (D_800E089C < 0x63) {
                    D_800E089C += 1;
                } else {
                    D_800E089C = 3;
                }
            }
        } else {
            if (D_800DFD98 & 0x200) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                if (D_800E08A4 >= 4) {
                    D_800E08A4 -= 2;
                } else {
                    D_800E08A4 = 9;
                }
            }
            if (D_800DFD98 & 0x100) {
                func_8007D45C(D_8010B358, D_800E2818, 2);
                if (D_800E08A4 < 9) {
                    D_800E08A4 += 2;
                } else {
                    D_800E08A4 = 3;
                }
            }
        }
        break;
    case 4:
        if (D_800DFD98 & 0xA000) {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            D_800E089C = 5;
            D_800E08A4 = 3;
            D_800E0890[0] = 1;
            D_800E0890[1] = 1;
            D_800E0890[2] = 0;
            D_800E0890[3] = 0;
            D_800E0890[4] = 0;
            D_800E0890[5] = 0;
            D_800E0898 = 4;
        }
    }
    if ((D_800DFD98 & 0xA000) && (D_800E1232 == 1)) {
        if (D_800E0890[D_800E123E] != 0) {
            if (D_800E0890[0] + D_800E0890[1] + D_800E0890[2] + D_800E0890[3] + D_800E0890[4] + D_800E0890[5] >= 3) {
                func_8007D45C(D_8010B358, D_800E2818, 4);
                D_800E0890[D_800E123E] = 0;
            } else {
                func_8007D45C(D_8010B358, D_800E2818, 5);
            }
        } else {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            D_800E0890[D_800E123E] = 1;
        }
    }
    if (D_800E1232 != 0) {
        if (D_800DFD98 & 0x1000) {
            func_8007D45C(D_8010B358, D_800E2818, 3);
            D_800E1232 = 0;
        }
    } else if (D_800DFD98 & 0xB000) {
        func_8007D45C(D_8010B358, D_800E2818, 3);
        if (D_8015D980 == 2) {
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E1232 = -1;
        } else {
            func_8003F8D8();
            func_8003FD78();
        }
        D_800E11FC = 1;
    }
    if (D_800DFD98 & 0x4000) {
        func_8007D45C(D_8010B358, D_800E2818, 4);
        func_8003F8D8();
        func_8003FD78();
    }
    if ((D_800E08A4 != D_80102B05) || (D_800E0898 != D_80102B04) || (D_800E089C != D_80102AC3)
        || ((D_800E0890[0] | (D_800E0890[1] << 1) | (D_800E0890[2] << 2) | (D_800E0890[3] << 3) | (D_800E0890[4] << 4) | (D_800E0890[5] << 5)) != D_80102B06)) {
        D_80102AC3 = D_800E089C;
        D_80102B04 = D_800E0898;
        D_80102B05 = D_800E08A4;
        D_80102B06 = D_800E0890[0] | (D_800E0890[1] << 1) | (D_800E0890[2] << 2) | (D_800E0890[3] << 3) | (D_800E0890[4] << 4) | (D_800E0890[5] << 5);
        requestSaveDataWrite();
    }
}


extern u16 D_800E0994[];
extern u16 D_800E09A4[];
extern u16 D_800E0A34[];
extern s16 D_800E1226;
extern s32 D_800E1270;
extern s32 D_800E127C;
extern u8 *D_800E14B0[];
extern s16 D_800E14CC[];
extern s32 D_801028F0[];
extern u16 func_80081E90_u16(s32);

void func_8006224C(void) {
    s32 i;
    s32 local_50;
    s32 unused4C;
    s32 local_48;
    s32 local_44;
    u8 buf[8];

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E1258 = loadAnim(0xEA);
        D_800E1270 = loadAnim(D_800E09A4[D_80113322]);
        D_801028F0[0] = loadMesh(D_800E08D4[D_80113322]);
        for (i = 1; i < 9; i++) {
            D_801028F0[i] = loadMesh(D_800E0A34[i]);
        }
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &D_801028F0[1], 8, &D_801026B0);
        D_800F22C0 += D_801026B0;
        for (i = 0; i < 4; i++) {
            D_800E125C = loadAnim(D_800E0994[func_80081E90_u16(7) % 7]);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1280[i] = LWAllocateMemory(D_800F22C0, D_800E125C, &D_801028F0[1], 8, &D_801026B0);
            D_800F22C0 += D_801026B0;
        }
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E127C = LWAllocateMemory(D_800F22C0, D_800E1270, &D_801028F0[0], 9, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1258 = loadAnim(0x124);
        D_800E1260 = loadMesh(0x6F);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1268 = (Obj *)LWAllocateMemory(D_800F22C0, D_800E1258, (u8 *)&D_800E1010 + 0x250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1268->unk28 = 1.0f;
        D_800E11FC = 0;
        D_800E123E = 0;
        D_800E1240 = 0;
        D_800E1242 = 0;
        D_800E1244 = 0;
        D_800E1208 = 1;
        D_800E120C = 1;
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    switch (D_800E123E) {
    case 0:
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, 0, 0)) {
            D_800E123E++;
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        if (LWPlayAnimation((&D_800E127C)[D_800E123E], D_800E1208 - D_800E1210, 0, 0)) {
            D_800E123E++;
        }
        break;
    case 5:
        if (LWPlayAnimation(D_800E127C, D_800E1208 - D_800E1210, 0, 0)) {
            if (D_800E11FC == 0) {
                D_800E11FC = 1;
                D_800E1214 = D_800E1208;
            }
        }
        break;
    }
    if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, 0, 0)) {
        D_800E1268->unk24 = 0;
    }
    if (D_800E1240 < 7) {
        if (D_800E14B0[D_800E1240][D_800E1242] != 0) {
            D_800E1242++;
            D_800E1244++;
            if (D_800E1244 % 3 == 0) {
                func_8007D45C(D_8010B358, D_800E2818, 0xB);
            }
            if (D_800E14B0[D_800E1240][D_800E1242] == 0x20) {
                D_800E1242++;
            }
            D_800E1268->unk2C = -0.04f;
        }
        func_800335F0(&D_800F22B4);
        local_48 = 0x20;
        local_44 = 0x20;
        i = 0;
        buf[1] = 0;
        while (i < D_800E1242 && D_800E14B0[D_800E1240][i] != 0) {
            buf[0] = D_800E14B0[D_800E1240][i];
            if (buf[0] == 0xA) {
                local_44 += 0x12;
                local_48 = 0x20;
            } else {
                func_80038478(&D_800F22B4, local_48, local_44, buf, 0xFF, 0xFF, 0xFF, 0xFF);
                local_48 += func_800388BC(buf);
            }
            i++;
        }
        func_800338B0(&D_800F22B4);
        if (D_800E1208 > D_800E14CC[D_800E1240 * 2]) {
            D_800E1242 = 0;
            D_800E1244 = 0;
            D_800E1240++;
        }
    }
    if (D_800DFD98 & 0xB000) {
        if (D_800E11FC == 0) {
            D_800E11FC = 1;
            D_800E1214 = D_800E1208;
        }
    }
    if (D_800E11FC != 0) {
        local_50 = (D_800E1208 - D_800E1214) * 255 / 30;
        if (local_50 >= 0x100) {
            local_50 = 0xFF;
            D_800E1234 = -1;
            D_800E121C = -1;
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1226 = -1;
            D_800E1228 = -1;
            D_800E122A = -1;
            D_800E122C = -1;
            D_800E122E = -1;
            D_800E1230 = -1;
            D_800E1232 = -1;
            D_800E1234 = -1;
            D_800E1236 = -1;
        }
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, local_50);
    }
}


extern f32 D_800E14E8;
extern f32 D_800E14EC;
extern f32 D_800E14F0;
extern f32 D_800E14F4;
extern u16 D_800E14F8;
extern u8 D_800ECEF8[];
extern u8 D_800ECF00[];
extern u8 D_800ECF08[];
extern u8 D_800ECF10[];
extern u8 D_800ECF18[];
extern u8 D_800ECF20[];
extern u8 D_800ECF28[];
extern u8 D_800ECF30[];
extern u8 D_800ECF38[];

void func_80062C3C(void) {
    s32 i;
    s32 pad[8];
    Gfx *g;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E1018 = loadAsset(D_736C50, 0x9A, 8);
        D_800E1024 = loadAsset(D_736C50, 0x9B, 8);
        D_800E102C = loadAsset(D_736C50, 0xCB, 8);
        D_800E1258 = loadAnim(0xAD);
        D_800E1260 = loadMesh(0x41);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &MENU->unk250, 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        if (D_800E0B20 != 2) {
            loadsong(D_800E94B0, D_80107290);
        } else {
            loadsong(D_800E0B24, D_80107290);
        }
        func_8007ACFC(D_80107290);
        D_800E11FC = 0;
        D_800E14E8 = 0.0f;
        D_800E14EC = 0.0f;
        D_800E14F0 = 0.0f;
        D_800E14F4 = 0.0f;
        func_8003FC6C(0x17, 0x46, 0x37, 0xDC, 0xFF, 0, 0xFF, 0x28, 0xE1);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E1236 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        D_800E0764 = -1;
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_8003396C(&D_800F22B4, D_800E1024, 0x4B, 0x1F, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_8003396C(&D_800F22B4, D_800E1018, 0x9D, 0x25, 0xFF, 0xFF, 0xFF, D_800E1202);
    func_800338B0(&D_800F22B4);
    D_800E14E8 += D_800E14F0;
    D_800E14EC += D_800E14F4;
    while (D_800E14E8 < -180.0) {
        D_800E14E8 += 360.0;
    }
    while (D_800E14E8 > 180.0) {
        D_800E14E8 -= 360.0;
    }
    while (D_800E14EC < -180.0) {
        D_800E14EC += 360.0;
    }
    while (D_800E14EC > 180.0) {
        D_800E14EC -= 360.0;
    }
    guRotateRPYF_2(D_80102B28, -D_800E14EC, -D_800E14E8, 0.0f);
    guTranslateF(D_80102B68, 0.0f, -15.0f, 0.0f);
    i = D_800E1208 - D_800E1210;
    if (LWPlayAnimation(D_800E1264, i, D_80102B28, D_80102B68) != 0) {
        D_800E1264->unk24 = 0;
    }
    func_800335F0(&D_800F22B4);
    if (D_800E14E8 * D_800E14E8 > D_800E14EC * D_800E14EC) {
        if (D_800E14E8 < -45.0) {
            i = 0;
        } else if (D_800E14E8 < -20.0) {
            i = ((25.0 - (-20.0 - D_800E14E8)) * 255.0) / 25.0;
        } else if (D_800E14E8 > 45.0) {
            i = 0;
        } else if (D_800E14E8 > 20.0) {
            i = ((45.0 - D_800E14E8) * 255.0) / 25.0;
        } else {
            i = 0xFF;
        }
    } else {
        if (D_800E14EC < -45.0) {
            i = 0;
        } else if (D_800E14EC < -20.0) {
            i = ((25.0 - (-20.0 - D_800E14EC)) * 255.0) / 25.0;
        } else if (D_800E14EC > 45.0) {
            i = 0;
        } else if (D_800E14EC > 20.0) {
            i = ((45.0 - D_800E14EC) * 255.0) / 25.0;
        } else {
            i = 0xFF;
        }
    }
    i = D_800E1202 * i / 255;
    func_80038478(&D_800F22B4, 0x48 - func_800388BC(D_800ECEF8), 0x22, D_800ECF00, 0xE6, 0x61, 0x1E, i);
    func_80038478(&D_800F22B4, 0x48 - func_800388BC(D_800ECF08), 0x37, D_800ECF10, 0xE6, 0x61, 0x1E, i);
    func_80038478(&D_800F22B4, 0x48 - func_800388BC(D_800ECF18), 0xA0, D_800ECF20, 0xE6, 0x61, 0x1E, i);
    func_80038478(&D_800F22B4, 0x48 - func_800388BC(D_800ECF28), 0xB4, D_800ECF30, 0xE6, 0x61, 0x1E, i);
    func_80038478(&D_800F22B4, 0xF2, 0x22, D_800ECF38, 0xE6, 0x61, 0x1E, i);
    g = D_800F22B4++;
    g->words.w0 = 0xB900031D;
    g->words.w1 = 0x00504340;
    func_8003396C(&D_800F22B4, D_800E102C, 0x41, 0x26, 0xFF, 0xDC, 0x3E, i);
    func_800338B0(&D_800F22B4);
    for (i = D_800E1210; i < D_800E1208; i++) {
        if (D_800E14F8 != 0 && D_800E14E8 < 0.0) {
            D_800E14E8 += 2.0;
            if (D_800E14E8 > 0.0) {
                D_800E14E8 = 0.0f;
            }
        }
        if (D_800E14F8 != 0 && D_800E14EC < 0.0) {
            D_800E14EC += 2.0;
            if (D_800E14EC > 0.0) {
                D_800E14EC = 0.0f;
            }
        }
        if (D_800E14F8 != 0 && D_800E14E8 > 0.0) {
            D_800E14E8 -= 2.0;
            if (D_800E14E8 < 0.0) {
                D_800E14E8 = 0.0f;
            }
        }
        if (D_800E14F8 != 0 && D_800E14EC > 0.0) {
            D_800E14EC -= 2.0;
            if (D_800E14EC < 0.0) {
                D_800E14EC = 0.0f;
            }
        }
        if ((D_800DFD90 & 0x200) && D_800E14F0 < 4.0) {
            D_800E14F0 += 0.25;
            D_800E14F8 = 0;
        }
        if ((D_800DFD90 & 0x100) && D_800E14F0 > -4.0) {
            D_800E14F0 -= 0.25;
            D_800E14F8 = 0;
        }
        if ((D_800DFD90 & 0x800) && D_800E14F4 < 4.0) {
            D_800E14F4 += 0.25;
            D_800E14F8 = 0;
        }
        if ((D_800DFD90 & 0x400) && D_800E14F4 > -4.0) {
            D_800E14F4 -= 0.25;
            D_800E14F8 = 0;
        }
        if (!(D_800DFD90 & 0x200) && D_800E14F0 > 0.0) {
            D_800E14F0 -= 0.125;
        }
        if (!(D_800DFD90 & 0x100) && D_800E14F0 < 0.0) {
            D_800E14F0 += 0.125;
        }
        if (!(D_800DFD90 & 0x800) && D_800E14F4 > 0.0) {
            D_800E14F4 -= 0.125;
        }
        if (!(D_800DFD90 & 0x400) && D_800E14F4 < 0.0) {
            D_800E14F4 += 0.125;
        }
    }
    if (D_800DFD98 & 0xB000) {
        func_8007D45C(D_8010B358, D_800E2818, 3);
        D_800E1236 = -1;
        D_800E1220 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
    }
    if (D_800DFD98 & 0x4000) {
        func_8007D45C(D_8010B358, D_800E2818, 4);
        func_8003FD78();
        func_8003F8D8();
    }
    if (D_800DFD98 & 0xF) {
        D_800E14F8 = 1;
    }
}





void func_800743BC(s32, s32, s32, s32, s32);

extern s16 D_800E076C;
extern u16 D_800E0AC0[];
extern u16 D_800E0AD4[];
extern u16 D_800E0AE8[];
extern s32 D_800E126C;
extern Obj *D_800E1278;
extern s16 D_800E149C;
extern s32 D_800E14FC[];
extern s32 D_800E150C[];
extern s32 D_800E1530[];
extern s32 D_800E1540[];
extern s16 D_800E1550[];
extern u16 D_800E28E8;
extern s32 D_80103374;
extern s32 D_80103388;
extern s32 D_80103958;
extern s32 D_8010395C;
extern s32 D_80103960;
extern s8 D_80113323;

void func_80063F1C(void) {
    s32 sp54;
    s32 pad0, pad1, pad2, pad3, pad4, pad5;

    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        if (D_800E149C != 0) {
            if (D_800E0B20 != 2) {
                loadsong(D_800E94B0, D_80107290);
            } else {
                loadsong(D_800E0B24, D_80107290);
            }
            func_8007ACFC(D_80107290);
            D_800E149C = 0;
        }
        func_80079B80(D_800E28E8, D_80107290);
        D_800E11FC = 0;
        D_800E076C = 0;
        D_800E1014 = (s32) loadAsset(D_736C50, 0xC2, 8);
        func_80038284(D_800E1014);
        D_80103374 = (s32) loadAsset(D_736C50, 0xCA, 8);
        D_80103388 = (s32) loadAsset(D_736C50, 0xA6, 8);
        if (D_800E44A8 == 6) {
            sp54 = D_800E44A0 - 1;
        } else {
            sp54 = D_800E44A0;
        }
        D_800E1258 = (s32) loadAnim(D_800E0AC0[sp54]);
        D_800E126C = (s32) loadAnim(D_800E0AE8[sp54]);
        D_800E125C = (s32) loadAnim(D_800E0AD4[sp54]);
        D_800E1260 = (s32) loadMesh(0xC);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1264 = LWAllocateMemory(D_800F22C0, D_800E1258, &((Obj **)&D_800E1010)[0x94], 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1278 = LWAllocateMemory(D_800F22C0, D_800E126C, &((Obj **)&D_800E1010)[0x94], 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1268 = LWAllocateMemory(D_800F22C0, D_800E125C, &((Obj **)&D_800E1010)[0x94], 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E1258 = (s32) loadAnim(0x31);
        D_800E126C = (s32) loadAnim(0x32);
        D_800E125C = (s32) loadAnim(0x121);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        ((Obj **)&D_800E1010)[0x9C] = LWAllocateMemory(D_800F22C0, D_800E1258, &((Obj **)&D_800E1010)[0x94], 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        ((Obj **)&D_800E1010)[0x9D] = LWAllocateMemory(D_800F22C0, D_800E126C, &((Obj **)&D_800E1010)[0x94], 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        ((Obj **)&D_800E1010)[0x9E] = LWAllocateMemory(D_800F22C0, D_800E125C, &((Obj **)&D_800E1010)[0x94], 1, &D_801026B0);
        D_800F22C0 += D_801026B0;
        D_800E123E = 0;
        D_80103958 = 0;
        D_8010395C = 0;
        D_80103960 = 0;
        if (D_800E44A8 == 5) {
            D_80103958 = D_800E14FC[sp54];
        }
        if (D_800E44A8 == 1) {
            D_80103958 = D_800E150C[sp54];
        }
        if (D_800E44A8 == 9) {
            D_80103958 = D_800E1530[sp54];
        }
        if (D_800E44A8 == 6) {
            D_80103958 = D_800E1540[sp54];
        }
        D_80109DA9 = 1;
        D_80109DBC = 0;
        D_80109DA4 = 0;
        loadsong(0x138, &D_80108828);
        D_8010B341 = 1;
        D_8010B354 = 0;
        D_8010B33C = 0;
        loadsong(D_800E1550[sp54], D_80109DC0);
        if (D_800E44A8 == 3) {
            D_800E44A8 = -1;
        }
        func_8003FC6C(0x58, 0x32, 0x40, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800DFF08 == 0) {
        func_8007ADF8(&D_80108828);
        func_8007ADF8(D_80109DC0);
        D_800E1228 = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        func_8007AEE0(D_8010B358);
        return;
    }
    switch (D_800E123E) {
    case 0:
        if (D_800E1264->unk24 == 0) {
            func_8007ACFC(&D_80108828);
            func_8007ACFC(D_80109DC0);
        }
        LWPlayAnimation(((Obj **)&D_800E1010)[0x9C], D_800E1208 - D_800E1210, 0, 0);
        if (LWPlayAnimation(D_800E1264, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E123E = 1;
        }
        break;
    case 1:
        if (LWPlayAnimation(((Obj **)&D_800E1010)[0x9D], D_800E1208 - D_800E1210, 0, 0) != 0) {
            ((Obj **)&D_800E1010)[0x9D]->unk24 = 0;
        }
        if (LWPlayAnimation(D_800E1278, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1278->unk24 = 0;
            if (D_800E11FC != 0) {
                D_800E123E = 2;
                D_800E1268->unk28 = D_800E1278->unk28;
                ((Obj **)&D_800E1010)[0x9E]->unk28 = ((Obj **)&D_800E1010)[0x9D]->unk28;
                D_80109DA9 = 1;
                D_80109DBC = 0;
                D_80109DA4 = 0;
                loadsong(0x137, &D_80108828);
                D_8010B341 = 1;
                D_8010B354 = 0;
                D_8010B33C = 0;
                loadsong(0x139, D_80109DC0);
                func_8007ACFC(&D_80108828);
                func_8007ACFC(D_80109DC0);
            }
        }
        break;
    case 2:
        LWPlayAnimation(((Obj **)&D_800E1010)[0x9E], D_800E1208 - D_800E1210, 0, 0);
        if (LWPlayAnimation(D_800E1268, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E123E = 3;
            if (D_800E11FC != 2) {
                func_8003F8D8();
                func_8003FD78();
                D_800E11FC = 2;
            }
        }
        break;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    if (D_80103958 != 0) {
        func_800335F0(&D_800F22B4);
        func_800743BC(0x20, ((D_800E44A8 == 1) && (D_800E44A0 == 7)) ? 0x64 : 0x78, 0x120, 0xD2, D_800E1202);
        func_800338B0(&D_800F22B4);
    }
    if (D_800E1208 < 0x5A) {
        return;
    }
    if ((D_800E123E != 0) && ((D_800DFD98 & 0xB000) || ((D_80113323 != 0) && (D_800E1208 >= 0x12D) && (D_800E11FC == 0)))) {
        if (D_800E11FC == 1) {
            D_800E1268->unk2C = 0.08f;
            D_800E1278->unk2C = 0.08f;
            ((Obj **)&D_800E1010)[0x9D]->unk2C = 0.08f;
            ((Obj **)&D_800E1010)[0x9E]->unk2C = 0.08f;
            func_8003F8D8();
            func_8003FD78();
            D_800E11FC = 2;
        }
        if (D_800E11FC == 0) {
            D_800E11FC = 1;
        }
    }
}

extern s32 D_800E1564;
extern s16 D_800E121E;


void func_80064BBC(void) {
    s32 pad[6];
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E11FC = 0;
        D_800E076C = 0;
        D_800E1014 = (s32) loadAsset(D_736C50, 0xC2, 8);
        func_80038284(D_800E1014);
        D_80103958 = D_800E1564;
        D_80103960 = D_800E1564 + 0x186A0;
        D_800E44A8 = -1;
        func_8003FC6C(0x58, 0x32, 0x40, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800DFF08 == 0) {
        D_800E121E = -1;
        D_800E1208 = 0;
        D_800E120C = 0;
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_800743BC(0x20, 0x20, 0x120, 0xD2, D_800E1202);
    func_800338B0(&D_800F22B4);
    if (D_800DFD98 & 0xF000) {
        if (D_800E11FC == 0) {
            D_800E11FC = 1;
            func_8007D45C(D_8010B358, D_800E2818, 3);
            func_8003F8D8();
            func_8003FD78();
        }
    }
}

extern u8 D_800ED890[];
extern u8 D_800ED8AC[];
extern u8 D_800ED8B8[];
extern u8 D_800ED8C4[];
extern u8 D_800ED8CC[];
extern u8 D_800ED8E0[];


void func_80064EBC(void) {
    s32 pad[10];
    if (D_800E1208 == 0) {
        D_800F22C0 = D_801026B8;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        func_8003FC6C(0x58, 0x32, 0x40, 0xDC, 0xFF, 0, 0x64, 0x50, 0xFF);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    func_8003B1A4();
    if (D_800E1208 < 0x1E) {
        return;
    }
    func_80038A88();
    if (D_800E1208 < 0x3C) {
        return;
    }
    if (D_800E1202 != D_800E11FA) {
        if (D_800E1204 == 0) {
            D_800E1204 = 0x14;
        }
    } else {
        D_800E1204 = 0;
        D_800E1202 = D_800E11FA;
        D_800E1206 = D_800E11FA;
    }
    if (D_800E1202 == 0) {
        return;
    }
    func_800335F0(&D_800F22B4);
    func_80038478(&D_800F22B4, 0x1A, 0x46, D_800ED890, 0xE6, 0x61, 0x1E, D_800E1202);
    func_80038478(&D_800F22B4, 0x3D, 0x64, D_800ED8AC, 0xE6, 0x61, 0x1E, D_800E1202);
    func_80038478(&D_800F22B4, func_800388BC(D_800ED8B8) + 0x3D, 0x64, D_800ED8C4, 0xFF, 0xDC, 0x3E, D_800E1202);
    func_80038478(&D_800F22B4, 0x48, 0x74, D_800ED8CC, 0xE6, 0x61, 0x1E, D_800E1202);
    func_80038478(&D_800F22B4, 0x30, 0x96, D_800ED8E0, 0xE6, 0x61, 0x1E, D_800E1202);
    func_800338B0(&D_800F22B4);
}

void packPlayerName(u8 *dst, u8 *src) {
    u8 buf[8];
    s32 i;

    if (src[0] != 0) {
        buf[0] = src[0] - 0x20;
    } else {
        buf[0] = 0x3F;
    }
    if (src[1] != 0) {
        buf[1] = src[1] - 0x20;
    } else {
        buf[1] = 0x3F;
    }
    if (src[2] != 0) {
        buf[2] = src[2] - 0x20;
    } else {
        buf[2] = 0x3F;
    }
    if (src[3] != 0) {
        buf[3] = src[3] - 0x20;
    } else {
        buf[3] = 0x3F;
    }
    if (src[4] != 0) {
        buf[4] = src[4] - 0x20;
    } else {
        buf[4] = 0x3F;
    }
    if (src[5] != 0) {
        buf[5] = src[5] - 0x20;
    } else {
        buf[5] = 0x3F;
    }
    if (src[6] != 0) {
        buf[6] = src[6] - 0x20;
    } else {
        buf[6] = 0x3F;
    }
    if (src[7] != 0) {
        buf[7] = src[7] - 0x20;
    } else {
        buf[7] = 0x3F;
    }
    i = 0;
    while (i < 8 && buf[i] != 0x3F) {
        i++;
    }
    for (; i < 8; i++) {
        buf[i] = 0x3F;
    }
    dst[0] = buf[0] | (buf[1] << 6);
    dst[1] = ((buf[1] >> 2) & 0xF) | (buf[2] << 4);
    dst[2] = ((buf[2] >> 4) & 3) | (buf[3] << 2);
    dst[3] = buf[4] | (buf[5] << 6);
    dst[4] = ((buf[5] >> 2) & 0xF) | (buf[6] << 4);
    dst[5] = ((buf[6] >> 4) & 3) | (buf[7] << 2);
}

void unpackPlayerName(u8 *dst, u8 *src) {
    dst[0] = (src[0] & 0x3F) + 0x20;
    dst[1] = ((((src[0] >> 6) & 0x3) | (src[1] << 2)) & 0x3F) + 0x20;
    dst[2] = ((((src[1] >> 4) & 0xF) | (src[2] << 4)) & 0x3F) + 0x20;
    dst[3] = ((src[2] >> 2) & 0x3F) + 0x20;
    dst[4] = (src[3] & 0x3F) + 0x20;
    dst[5] = ((((src[3] >> 6) & 0x3) | (src[4] << 2)) & 0x3F) + 0x20;
    dst[6] = ((((src[4] >> 4) & 0xF) | (src[5] << 4)) & 0x3F) + 0x20;
    dst[7] = ((src[5] >> 2) & 0x3F) + 0x20;
    if (dst[0] == 0x5F) {
        dst[0] = 0;
    }
    if (dst[1] == 0x5F) {
        dst[1] = 0;
    }
    if (dst[2] == 0x5F) {
        dst[2] = 0;
    }
    if (dst[3] == 0x5F) {
        dst[3] = 0;
    }
    if (dst[4] == 0x5F) {
        dst[4] = 0;
    }
    if (dst[5] == 0x5F) {
        dst[5] = 0;
    }
    if (dst[6] == 0x5F) {
        dst[6] = 0;
    }
    if (dst[7] == 0x5F) {
        dst[7] = 0;
    }
}

extern u8 D_80102AC2;
extern u8 D_80102B07;

void requestSaveDataWrite(void);

void func_80065660(void) {
    packPlayerName((u8 *) &D_80102918 + 0x1A4, D_80113328);
    D_80102AC2 = *(u8 *) &D_800E07D4;
    D_80102B07 = *(s16 *) ((u8 *) &D_800E0754 + 2);
    requestSaveDataWrite();
}

extern u8 D_800E0784[8][9];
extern s8 D_80113322;


void func_800656C8(void) {
    D_80113328 = &D_800E0784;
    unpackPlayerName(D_80113328, (u8 *) &D_80102918 + 0x1A4);
    D_80113322 = D_80102AC2;
    *(s8 *) &D_800E07D4 = D_80113322;
    *(s16 *) ((u8 *) &D_800E0754 + 2) = D_80102B07;
}

extern u8 D_800E07DC[8];
extern u8 D_80102AF4[8];
extern u8 D_80102AFC[8];


void func_80065748(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        packPlayerName((u8 *) &D_80102918 + (i * 6 + 0x1AC), D_800E0784[i]);
        D_80102AF4[i] = D_800E07D4[i];
        D_80102AFC[i] = D_800E07DC[i];
    }
    requestSaveDataWrite();
}



void func_800657FC(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        unpackPlayerName(D_800E0784[i], (u8 *) &D_80102918 + (i * 6 + 0x1AC));
        D_800E07D4[i] = D_80102AF4[i];
        D_800E07DC[i] = D_80102AFC[i];
    }
}

extern s16 D_800E1608;
extern u8 D_8010291C[];


s32 insertRankedRecord(u16 mode, u8 *arg1, u32 arg2, s32 arg3) {
    s32 i;
    s32 k;
    s32 j;
    s32 base;
    u8 buf[8];

    D_800E0764 = -1;

    switch (mode) {
    case 1:
        base = 0;
        i = 0;
        while (i < 5 && arg2 < D_80102994[base + i]) {
            i++;
        }
        if (i == 5) return 0;
        break;
    case 5:
        base = 5;
        i = 0;
        while (i < 5 && arg2 < D_80102994[base + i]) {
            i++;
        }
        if (i == 5) return 0;
        break;
    case 4:
        base = 10;
        i = 0;
        while (i < 5 && arg2 > D_80102994[base + i]) {
            i++;
        }
        if (i == 5) return 0;
        break;
    case 2:
        base = 15;
        i = 0;
        while (i < 5 && arg2 < D_80102994[base + i]) {
            i++;
        }
        if (i == 5) return 0;
        break;
    default:
        return 0;
    }

    for (k = 4; k > i; k--) {
        for (j = 0; j < 6; j++) {
            (&D_80102918[(base + k) * 6 + j])[4] = (&D_80102918[(base + k) * 6 + j])[-2];
        }
        ((u32 *)D_80102918 + (base + k))[0x1F] = ((u32 *)D_80102918 + (base + k))[0x1E];
    }

    packPlayerName(&buf[0], arg1);

    for (j = 0; j < 6; j++) {
        D_8010291C[(base + i) * 6 + j] = buf[j];
    }

    D_80102994[base + i] = arg2;
    D_800E0764 = base + i;

    if (D_800E1608 != 0) {
        requestSaveDataWrite();
    }

    return 1;
}

typedef struct {
    u8 unk0;
} Struct07D4;

typedef struct {
    u8 unk0[2];
    s16 unk2;
} Struct0754;




extern u8 D_80102AAC[];
extern u8 D_80102AB4[];




extern u8 D_801029E8[8][20];

void func_80065D74(void) {
    s32 k;
    s32 found;
    s32 j;
    u8 buf[8];

    if (D_800E44A8 == 10) {
        return;
    }
    packPlayerName(buf, D_80113328);
    found = 8;
    for (k = 0; k < 8; k++) {
        j = 0;
        while (j < 6) {
            if (buf[j] != D_801029E8[k][j]) {
                break;
            }
            j++;
        }
        if (j == 6) {
            found = k;
            break;
        }
    }
    if (found == 8) {
        return;
    }
    D_80102AAC[found] = ((Struct07D4 *)D_800E07D4)->unk0;
    D_80102AB4[found] = ((Struct0754 *)D_800E0754)->unk2;
    requestSaveDataWrite();
}

typedef struct { u8 c[5]; } Row5;
extern Row5 D_80102A84[];
s32 func_80065EDC(void) {
    s32 k;
    s32 found;
    s32 j;
    s32 idx;
    u8 buf[8];
    if (D_800E44A8 == 10) {
        return 0;
    }
    packPlayerName(buf, D_80113328);
    found = 8;
    for (k = 0; k < 8; k++) {
        j = 0;
        while (j < 6) {
            if (buf[j] != D_801029E8[k][j]) {
                break;
            }
            j++;
        }
        if (j == 6) {
            found = k;
            break;
        }
    }
    if (found == 8) {
        return 0;
    }
    switch (D_800E44A8) {
    case 5:
        idx = 0;
        break;
    case 1:
        idx = 1;
        break;
    case 4:
        idx = 2;
        break;
    case 6:
        idx = 3;
        break;
    case 9:
        idx = 4;
        break;
    default:
        return 0;
    }
    return D_80102A84[found].c[idx];
}

typedef struct { s16 f0; s16 f2; u8 e8[6]; u8 ee[10]; } Row;
extern s16 D_800DFD54;
extern u8 D_800ED990[];
extern Row D_801029E4[];
typedef struct { u8 pad[0x16C]; u8 arr[8][5]; } BigBuf;
extern s32 func_80089C9C(void);
s32 func_800660B8(s32 arg0) {
    s32 var2C;
    s32 var28;
    s32 var24;
    s32 var20;
    u8 buf[6];
    if (D_800E44A8 == 0xA) {
        return 0;
    }
    packPlayerName(buf, D_80113328);
    var28 = 8;
    for (var2C = 0; var2C < 8; var2C++) {
        var24 = 0;
        while (var24 < 6) {
            if (buf[var24] != D_801029E4[var2C].e8[var24]) {
                break;
            }
            var24++;
        }
        if (var24 == 6) {
            var28 = var2C;
            break;
        }
    }
    if (var28 == 8) {
        for (var2C = 0; var2C < 8; var2C++) {
            if (D_801029E4[var2C].e8[0] == 0xFF) {
                D_801029E4[var2C].f0 = 0;
                D_801029E4[var2C].f2 = 0;
                D_801029E4[var2C].ee[0] = 0;
                D_801029E4[var2C].ee[1] = 0;
                D_801029E4[var2C].ee[2] = 0;
                D_801029E4[var2C].ee[3] = 0;
                D_801029E4[var2C].ee[4] = 0;
                D_801029E4[var2C].ee[5] = 0;
                D_801029E4[var2C].ee[6] = 0;
                D_801029E4[var2C].ee[7] = 0;
                D_801029E4[var2C].ee[8] = 0;
                D_801029E4[var2C].ee[9] = 0;
                D_80102A84[var2C].c[0] = 0;
                D_80102A84[var2C].c[1] = 0;
                D_80102A84[var2C].c[2] = 0;
                D_80102A84[var2C].c[3] = 0;
                D_80102A84[var2C].c[4] = 0;
                var28 = var2C;
                break;
            }
        }
    }
    if (var28 == 8) {
        return 0;
    }
    D_80102AAC[var28] = ((u8 *)&D_800E07D4)[0];
    D_80102AB4[var28] = ((s16 *)&D_800E0754)[1];
    for (var2C = 0; var2C < 6; var2C++) {
        D_801029E4[var28].e8[var2C] = buf[var2C];
    }
    switch (D_800E44A8 - 1) {
    case 4:
        var20 = 0;
        break;
    case 0:
        var20 = 1;
        break;
    case 3:
        var20 = 2;
        break;
    case 5:
        var20 = 3;
        break;
    case 8:
        var20 = 4;
        break;
    default:
        requestSaveDataWrite();
        return 1;
    }
    if (D_800E44A8 == 4) {
        if (D_801029E4[var28].ee[var20] <= D_800E4498) {
            D_800DFD54 = 1;
        }
        if (D_801029E4[var28].ee[var20] + 1 == D_800E4498) {
            func_80029760(D_800ED990);
            D_801029E4[var28].f0 = D_80112D2C;
            D_801029E4[var28].f2 = D_80112D2C >> 16;
            D_801029E4[var28].ee[var20] = D_800E4498;
        }
    } else {
        var2C = func_80089C9C();
        if ((s16)arg0 != 0) {
            ((BigBuf *)D_80102918)->arr[var28][var20] |= 1 << ((u8 *)&D_800E07D4)[0];
            D_801029E4[var28].ee[var20] = (func_80089D04() - 1) * var2C;
        } else {
            if ((D_80102A84[var28].c[var20] & (1 << ((u8 *)&D_800E07D4)[0])) != 0) {
                var2C = (D_800E44A0 - func_80089D04()) * var2C + D_800E4498;
                if (D_801029E4[var28].ee[5 + var20] + 1 == var2C) {
                    D_801029E4[var28].ee[5 + var20] = var2C;
                }
            } else {
                var2C = D_800E4498 + D_800E44A0 * var2C;
                if (D_801029E4[var28].ee[var20] + 1 == var2C) {
                    D_801029E4[var28].ee[var20] = var2C;
                }
            }
        }
    }
    requestSaveDataWrite();
    return 1;
}

extern u8 D_801029EE[];
extern u8 D_801029F3[];
extern s16 D_800E12E4;
extern s16 D_80102666;
s32 func_80066854(void) {
    s32 row;
    s32 match;
    s32 i;
    s32 sel;
    u8 buf[8];
    packPlayerName(buf, D_80113328);
    match = 8;
    for (row = 0; row < 8; row++) {
        i = 0;
        while (i < 6) {
            if (buf[i] != D_801029E8[row][i]) {
                break;
            }
            i++;
        }
        if (i == 6) {
            match = row;
            break;
        }
    }
    if (match == 8) {
        return 0;
    }
    D_800E07D4[0] = D_80102AAC[match];
    D_800E0754[1] = D_80102AB4[match];
    if (D_800E12E4 == 0) {
        if (D_800E0754[1] >= 5) {
            D_800E0754[1] = 0;
        }
    }
    switch (D_800E44A8) {
    case 5:
        sel = 0;
        break;
    case 1:
        sel = 1;
        break;
    case 4:
        D_80112D2C = ((u16 *)&D_80102918[match * 20])[0x66] | (((u16 *)&D_80102918[match * 20])[0x67] << 16);
        sel = 2;
        break;
    case 6:
        sel = 3;
        break;
    case 9:
        sel = 4;
        break;
    case 2:
    case 3:
    case 7:
    case 8:
    default:
        D_800E4498 = 0;
        D_800E449C = 0;
        D_800E44A0 = 0;
        D_80102666 = 0;
        return 1;
    }
    row = func_80089C9C();
    if (*((u8 *)D_80102A84 + match * 5 + sel) & (1 << D_800E07D4[0])) {
        D_800E449C = *(D_801029F3 + match * 20 + sel) % row;
        D_800E44A0 = *(D_801029F3 + match * 20 + sel) / row + func_80089D04();
    } else {
        D_800E449C = *(D_801029EE + match * 20 + sel) % row;
        D_800E44A0 = *(D_801029EE + match * 20 + sel) / row;
    }
    D_800E4498 = D_800E449C;
    D_80102666 = D_800E44A0;
    if (D_800E44A8 == 6) {
        D_800E4498 = 0;
        D_800E449C = 0;
    }
    return 1;
}


s32 func_80066CE8(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_801029E8[i][0] == 0xFF) {
            return 1;
        }
    }
    return 0;
}


void func_80066D50(u16 arg0) {
    if (arg0 >= 8) {
        return;
    }
    D_801029E8[arg0][0] = 0xFF;
    requestSaveDataWrite();
}


s32 computeSaveDataChecksum(void) {
    u32 sum;
    s16 i;
    u32 *ptr;

    sum = 0x25;
    ptr = (u32 *) D_80102918;
    for (i = 0; i < 0x7F; i++) {
        sum = *ptr + ((sum << 3) | (sum >> 29));
        ptr++;
    }
    return sum;
}

void func_800298C4(void *);

void func_80066E40(void) {
    func_800298C4(D_80102918);
}

void requestEepromWrite(void *);
extern s32 D_80102B14;

void requestSaveDataWrite(void) {
    D_80102B14 = computeSaveDataChecksum();
    requestEepromWrite(D_80102918);
}

void func_80066EA8(void) {
    u8 *ptr;
    s32 i;

    ptr = D_80102918;
    for (i = 0; i < 0x200; i++) {
        *ptr = 0xFF;
        ptr++;
    }
    requestEepromWrite(D_80102918);
}

extern void func_80079BD4(s32);

extern s32 D_801029A8[];
extern s32 D_801029BC[];
extern s32 D_801029D0[];
extern u8 D_80102ABC[];
extern u8 D_80102AC3;
extern u8 D_80102AC4[];
extern u8 D_80102B04;
extern u8 D_80102B05;
extern u8 D_80102B06;
extern u8 D_80102B0A[];
extern s32 D_800E1568[];
extern s32 D_800E157C[];
extern s32 D_800E1590[];
extern s32 D_800E15A4[];
extern s32 D_800E15B8[];
extern s32 D_800E15CC[];
extern s32 D_800E15E0[];
extern s32 D_800E15F4[];
extern s32 D_800E0B1C;
extern u8 D_800E0898;
extern u8 D_800E0890[];

extern s16 D_800E08A4;
extern s16 D_800E089C;

void func_80066F18(void) {
    s32 i;
    s32 j;

    D_80102918[0] = 0;
    D_80102918[1] = 0x48;
    D_80102918[2] = 0x32;
    D_80102918[3] = 0x4F;
    for (i = 0; i < 5; i++) {
        D_80102994[i] = 0;
        D_801029A8[i] = 0;
        D_801029BC[i] = 0xF4240;
        D_801029D0[i] = 0;
    }
    D_800E1608 = 0;
    for (i = 0; i < 5; i++) {
        insertRankedRecord(5, D_800E1568[i], D_800E15B8[i], 1);
        insertRankedRecord(1, D_800E157C[i], D_800E15CC[i], 1);
        insertRankedRecord(4, D_800E1590[i], D_800E15E0[i], 1);
        insertRankedRecord(2, D_800E15A4[i], D_800E15F4[i], 1);
    }
    D_800E1608 = 1;
    D_800E0764 = -1;
    for (i = 0; i < 8; i++) {
        D_801029E8[i][0] = 0xFF;
    }
    for (i = 0; i < 6; i++) {
        D_80102ABC[i] = 0xFF;
    }
    D_80102AC2 = 4;
    for (j = 0; j < 8; j++) {
        for (i = 0; i < 6; i++) {
            D_80102AC4[(j * 6) + i] = 0xFF;
        }
        D_80102AF4[j] = 4;
        D_80102AFC[j] = 0xF;
    }
    D_80102AC3 = 0xF;
    D_80102B04 = 4;
    D_80102B05 = 3;
    D_80102B06 = 0x18;
    D_80102918[0x1F0] = 6;
    D_80102918[0x1F1] = 0;
    D_80102B07 = 0;
    for (i = 0; i < 7; i++) {
        D_80102B0A[i] = 0;
    }
    requestSaveDataWrite();
    D_800E0B1C = D_80102918[0x1F0] & 0xF;
    D_800E0B20 = D_80102918[0x1F0] >> 4;
    D_800E0B24 = D_80102918[0x1F1];
    i = D_800E0B1C * 0x1556;
    if (i >= 0x8000) {
        i = 0x7FFF;
    }
    func_80079BD4(i);
    i = -D_800E0B1C * 3414 + 0xA008;
    if (i >= 0x5000) {
        i = 0x4FFF;
    }
    D_800E28E8 = i;
    func_80079B80(i, D_80107290);
    D_800E08A4 = D_80102B05;
    D_800E0898 = D_80102B04;
    D_800E089C = D_80102AC3;
    D_800E0890[0] = D_80102B06 & 1;
    D_800E0890[1] = (D_80102B06 >> 1) & 1;
    D_800E0890[2] = (D_80102B06 >> 2) & 1;
    D_800E0890[3] = (D_80102B06 >> 3) & 1;
    D_800E0890[4] = (D_80102B06 >> 4) & 1;
    D_800E0890[5] = (D_80102B06 >> 5) & 1;
}

extern u8 D_800DFE8C;
extern u8 D_800ED9A4[];
extern u8 D_800ED9C8[];
extern s16 D_800E28E4;


void func_80067434(void) {
    s32 i;
    u8 *ptr;

    if (computeSaveDataChecksum() != D_80102B14 || D_80102918[1] != 0x48 || D_80102918[2] != 0x32 || D_80102918[3] != 0x4F) {
        D_800E121C = 4;
        D_800E0754[0] = 4;
        D_800DFE8C = 4;
        ptr = D_80102918;
        for (i = 0; i < 0x200; i++) {
            if (*ptr != 0xFF) {
                D_800E121C = 4;
                D_800E0754[0] = 4;
                D_800DFE8C = 0;
                break;
            }
        }
        func_80029760(D_800ED9A4);
        func_80029760(D_800ED9C8, 0x200);
        func_80066F18();
    } else {
        D_800DFE8C = 0;
        D_800E121C = 0;
        D_800E0754[0] = 0;
        D_800E0B1C = D_80102918[0x1F0] & 0xF;
        D_800E0B20 = D_80102918[0x1F0] >> 4;
        D_800E0B24 = D_80102918[0x1F1];
        if (D_800E0B20 == 2) {
            if (D_800E0B24 > D_800E28E4) {
                D_800E0B20 = 0;
            }
        }
        i = D_800E0B1C * 0x1556;
        if (i >= 0x8000) {
            i = 0x7FFF;
        }
        func_80079BD4(i);
        i = -D_800E0B1C * 3414 + 0xA008;
        if (i >= 0x5000) {
            i = 0x4FFF;
        }
        D_800E28E8 = i;
        func_80079B80(i, D_80107290);
        D_800E08A4 = D_80102B05;
        D_800E0898 = D_80102B04;
        D_800E089C = D_80102AC3;
        D_800E0890[0] = D_80102B06 & 1;
        D_800E0890[1] = (D_80102B06 >> 1) & 1;
        D_800E0890[2] = (D_80102B06 >> 2) & 1;
        D_800E0890[3] = (D_80102B06 >> 3) & 1;
        D_800E0890[4] = (D_80102B06 >> 4) & 1;
        D_800E0890[5] = (D_80102B06 >> 5) & 1;
    }
}

typedef struct {
    char pad0[0x30C];
    f32 unk30C;
} Big;
typedef struct {
    char pad0[0x14];
    Big *unk14;
    char pad18[0xC];
    s32 unk24;
    f32 unk28;
    f32 unk2C;
    char pad30[9];
    u8 unk39;
    char pad3A[0xE];
    u8 unk48;
} Anim;
extern u8 D_800DF740;
extern s32 D_800E160C;
extern s32 D_800E1610;
extern s32 D_800E1614;
extern s32 D_800E1634;
extern u16 D_800E1648;
extern s32 D_800E1658;
extern s32 D_800E1660;
extern s32 D_800E1668;
extern Anim *D_800E166C;
extern Anim *D_800E1670;
extern Anim *D_800E1674;
extern s16 D_800E16A8[];
extern s32 D_800E2AC0;
extern u8 D_800ED9EC;
extern u8 D_800EDA0C;
extern u8 D_800EDA24;
extern u8 D_800FC5D0;
extern s16 D_801026C8[];
extern s32 D_801028D0;
extern s32 D_801028D8[];
void func_80067798(void) {
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 pad58;
    void *sp54;
    Gfx *sp50;
    Gfx *sp4C;
    Gfx *sp48;
    Gfx *sp44;
    Gfx *sp40;
    Gfx *sp3C;
    Gfx *sp38;
    if (D_800DF770 == 0) {
        if (D_800E1208 == 0) {
            D_801028D0 = D_800F22C0;
            while (D_800DF710 > D_800DF714) {
                func_8002A140();
            }
            D_800E1660 = (s32) loadAnim(0x104);
            D_800E1668 = (s32) loadMesh(0x41);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1674 = LWAllocateMemory(D_800F22C0, D_800E1660, &D_800E1610 + 0x16, 1, &sp6C);
            D_800F22C0 += sp6C;
            D_800E1634 = loadAsset(D_736C50, 0x10, 8);
            D_800E1014 = loadAsset(D_736C50, 0xC2, 8);
            func_80038284(D_800E1014);
            D_800E1208 = 1;
            D_800E120C = 1;
            D_800E11FA = 0xFF;
        }
        D_800E1210 = D_800E1208;
        D_800E1208 = D_800E120C;
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, 0xFF);
        func_800335F0(&D_800F22B4);
        func_8003396C(&D_800F22B4, D_800E1634, 0x3C, 0x1E, 0xFF, 0xFF, 0xFF, 0xFF);
        sp54 = &D_800ED9EC;
        func_800384E4(&D_800F22B4, 0xA0 - (func_800388F4(sp54) >> 1), 0xB4, sp54, 0xE6, 0x61, 0x1E, 0xFF);
        sp54 = &D_800EDA0C;
        func_800384E4(&D_800F22B4, 0xA0 - (func_800388F4(sp54) >> 1), 0xC0, sp54, 0xE6, 0x61, 0x1E, 0xFF);
        sp54 = &D_800EDA24;
        func_800384E4(&D_800F22B4, 0xA0 - (func_800388F4(sp54) >> 1), 0xCC, sp54, 0xE6, 0x61, 0x1E, 0xFF);
        func_800338B0(&D_800F22B4);
        if (LWPlayAnimation(D_800E1674, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1674->unk24 = 0;
        }
        if (D_800E11FA > 0) {
            D_800E11FA -= 0x10;
            if (D_800E11FA < 0) {
                D_800E11FA = 0;
            }
        }
        if (D_800E11FA != 0) {
            func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, D_800E11FA);
        }
        return;
    }
    if (D_800E1208 == 0) {
        func_80066E40();
        D_801028D0 = D_800F22C0;
        while (D_800DF710 > D_800DF714) {
            func_8002A140();
        }
        D_800E1634 = loadAsset(D_736C50, 0x90, 8);
        D_800E1610 = loadAsset(D_736C50, 0x14, 8);
        D_800E1614 = loadAsset(D_736C50, 0x12D, 8);
        D_800E1660 = (s32) loadAnim(0x3A);
        D_800E1668 = (s32) loadMesh(0x15);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E166C = LWAllocateMemory(D_800F22C0, D_800E1660, &D_800E1610 + 0x16, 1, &sp6C);
        D_800F22C0 += sp6C;
        sp5C = 0;
        do {
            D_801028D8[sp5C] = (s32) loadMesh(D_800E16A8[sp5C]);
        } while (++sp5C < 5);
        D_800E1660 = (s32) loadAnim(0xCC);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1670 = LWAllocateMemory(D_800F22C0, D_800E1660, D_801028D8, 5, &sp6C);
        D_800F22C0 += sp6C;
        func_8007ADF8(D_80109DC0);
        func_80079B80(0x7FFF, D_80109DC0);
        D_8010B341 = 1;
        D_8010B354 = 0;
        D_8010B33C = 0;
        loadsong(0x129, D_80109DC0);
        D_800E160C = 0;
        D_800E1208 = 1;
        D_800E120C = 1;
        D_800E1658 = 0;
        sp5C = 0;
        do {
            D_801026C8[sp5C] = ((sp5C >> 3) << 11) + ((sp5C >> 3) << 6) + ((sp5C >> 3) << 1) + 1;
        } while (++sp5C < 0x100);
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if (D_800E1208 < 0x29) {
        sp64 = (D_800E1208 * 0xFF) / 40;
    } else {
        sp64 = 0xFF;
    }
    if (D_800E1208 < 0x29) {
        sp68 = 0;
    } else if (D_800E1208 < 0x51) {
        sp68 = ((D_800E1208 * 0xFF) - 0x27D8) / 40;
    } else {
        sp68 = 0xFF;
    }
    if (D_800E1670->unk24 < 0xB4) {
        sp60 = (D_800E1670->unk24 * 0xFF) / 180;
    } else {
        sp60 = 0xFF;
    }
    if ((sp68 != 0) && (sp60 < 0xFF)) {
        func_800335F0(&D_800F22B4);
        sp50 = D_800F22B4++;
        sp50->words.w0 = 0xBA000E02;
        sp50->words.w1 = 0x8000;
        sp4C = D_800F22B4++;
        sp4C->words.w0 = 0xFD100000;
        sp4C->words.w1 = (u32)D_801026C8;
        sp48 = D_800F22B4++;
        sp48->words.w0 = 0xE8000000;
        sp48->words.w1 = 0;
        sp44 = D_800F22B4++;
        sp44->words.w0 = 0xF5000100;
        sp44->words.w1 = 0x07000000;
        sp40 = D_800F22B4++;
        sp40->words.w0 = 0xE6000000;
        sp40->words.w1 = 0;
        sp3C = D_800F22B4++;
        sp3C->words.w0 = 0xF0000000;
        sp3C->words.w1 = 0x073FC000;
        sp38 = D_800F22B4++;
        sp38->words.w0 = 0xE7000000;
        sp38->words.w1 = 0;
        func_8003396C(&D_800F22B4, D_800E1634, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        func_8003396C(&D_800F22B4, D_800E1614, 0xD6, 0x3A, 0xFF, 0xFF, 0xFF, (s32)(255.0f - (D_800E166C->unk14->unk30C * 255.0f)));
        func_800338B0(&D_800F22B4);
    }
    if (sp60 != 0) {
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, sp60);
    }
    if (D_800E1208 >= 0x29) {
        if (D_800E166C->unk24 < 0x2710) {
            if (LWPlayAnimation(D_800E166C, D_800E1208 - D_800E1210, 0, 0) != 0) {
                D_800E166C->unk24 = 0x2710;
            }
        }
        if (D_800E166C->unk24 >= 0x2B2) {
            if (D_800E1670->unk24 != 0) {
                func_8003A900(*(s32 *)((u8 *)&D_800FC5D0 + ((!D_800E2AC0) * 0x1918)), 0xFF, 0xFF, 0xFF, D_800E1670->unk39);
            } else {
                func_8007ACFC(D_80109DC0);
            }
            if ((LWPlayAnimation(D_800E1670, D_800E1208 - D_800E1210, 0, 0) != 0) && (D_800E160C == 0)) {
                D_800E1658 = D_800E1208;
                D_800E160C = 1;
                func_80067434();
            }
        }
    }
    if (sp68 < 0xFF) {
        if (sp68 < 0) {
            sp68 = 0;
        }
        if (sp68 >= 0x100) {
            sp68 = 0xFF;
        }
        if (sp64 < 0) {
            sp64 = 0;
        }
        if (sp64 >= 0x100) {
            sp64 = 0xFF;
        }
        func_8006FA28(0, 0, 0x13F, 0xEF, sp64, sp64, sp64, 0xFF - sp68);
    }
    func_800335F0(&D_800F22B4);
    func_800338B0(&D_800F22B4);
    if ((D_800DFD98 & 0xB000) && (D_800E160C == 0) && (D_800DF740 == 0) && (D_800E1208 >= 0xFA)) {
        func_8007ADF8(D_80109DC0);
        func_8007AEE0(D_8010B358);
        D_800E160C = 1;
        D_800E1658 = D_800E1208;
        func_80067434();
    }
    if (D_800E160C != 0) {
        sp5C = (u32)((D_800E1208 - D_800E1658) * 0xFF) / 40U;
        if (sp5C >= 0x100) {
            sp5C = 0xFF;
        }
        if (sp5C < 0) {
            sp5C = 0;
        }
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, sp5C);
        if ((u32)(D_800E1208 - D_800E1658) >= 0x28) {
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E1648 = 1;
            D_800F22C0 = D_801028D0;
        }
    }
}

#define NULL 0
extern u8 *D_800E08B4[];
extern s32 D_800E1638;
extern s32 D_800E1654;
extern s16 D_800E165C;
extern s16 D_800E165E;
extern s32 D_800E1678[];
extern s32 D_800E1690[];
extern s16 D_800E16B4;
extern s16 D_800E16B8;
extern f32 D_800EDE80;
extern f32 D_800EDE84;
extern f32 D_800EDE88;
extern s32 D_80102B20;
extern u16 D_800E1644;
extern u16 D_800E1646;
extern u16 D_800E164A;
extern s16 D_800E164C;
extern u16 D_800E164E;
extern s32 D_800E1650;

void func_800685FC(void) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    Gfx *sp34;
    if (D_800E1648 == 0) {
        func_80067798();
        return;
    }
    if (D_800E16B8 == 0xA) {
        if (D_800E1650 == 0) {
            D_800F22C0 = D_801026B8;
            if (D_800DF710 > D_800DF714) {
                do {
                    func_8002A140();
                } while (D_800DF710 > D_800DF714);
            }
            D_800E1660 = loadAnim(0xBC);
            D_800E1668 = loadMesh(0x42);
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            D_800E1670 = LWAllocateMemory(D_800F22C0, D_800E1660, &D_800E1610 + 0x16, 1, &sp44);
            D_800F22C0 += sp44;
            D_800E1670->unk48 = 0;
            D_80109DA9 = 1;
            D_80109DBC = 0;
            D_80109DA4 = 0;
            loadsong(0x13F, &D_80108828);
            func_8007ACFC(&D_80108828);
            D_800E1650 = 1;
            D_800E1654 = 0;
            D_800E1208 = 1;
            D_800E120C = 1;
            D_800E11FC = 0;
        }
        D_800E1210 = D_800E1208;
        D_800E1208 = D_800E120C;
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, 0xFF);
        if (LWPlayAnimation(D_800E1670, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1670->unk2C = 0.08f;
        }
        if (D_800DFD98 & 0xB000) {
            D_800E11FC = 1;
            D_800E1670->unk2C = D_800EDE80;
        }
        if ((f64) D_800E1670->unk28 >= 1.0) {
            func_8007ADF8(&D_80108828);
            D_800E1650 = 0;
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E16B8 = 0;
            if (D_800E11FC != 0) {
                D_800E1646 = 1;
            }
        }
        return;
    }
    if (D_800E1650 == 0) {
        D_800F22C0 = D_801026B8;
        D_800E16B4 = 0;
        D_800E1654 = 0;
        D_801028D0 = D_800F22C0;
        if (D_800DF710 > D_800DF714) {
            do {
                func_8002A140();
            } while (D_800DF710 > D_800DF714);
        }
        capturePreviousFramebuffer();
        D_800E1634 = (s32) loadAsset(D_736C50, 0x14, 8);
        D_800E1614 = (s32) loadAsset(D_736C50, 0x15, 8);
        D_800E1638 = (s32) loadAsset(D_736C50, 0x46, 8);
        D_800E1660 = loadAnim(0x102);
        D_800E1668 = loadMesh(0x6B);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1670 = LWAllocateMemory(D_800F22C0, D_800E1660, &D_800E1610 + 0x16, 1, &sp44);
        D_800F22C0 += sp44;
        D_800E1660 = loadAnim(0x103);
        D_800E1668 = loadMesh(0x6C);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_800E1674 = LWAllocateMemory(D_800F22C0, D_800E1660, &D_800E1610 + 0x16, 1, &sp44);
        D_800F22C0 += sp44;
        D_800E165C = -1;
        D_800E165E = -1;
        for (sp3C = 0; sp3C < 6; sp3C++) {
            sp38 = (sp3C * 6) + 0x1E;
            D_800E1690[sp3C] = -(-sp38);
            D_800E1678[sp3C] += -((sp38 * sp38) + sp38) / 2;
        }
        D_800DFF08 = 4;
        SA->unkE = 0x29;
        SA->unkF = 0x3C;
        SA->unk10 = 0x52;
        SA->unk11 = 0xFF;
        D_800DFEB0.colA[0] = 0xFF;
        D_800DFEB0.colA[1] = 0xF0;
        D_800DFEB0.colA[2] = 0;
        D_800DFEB0.colA[3] = 0x30;
        D_800DFEB0.colA[4] = 0xFF;
        D_800DFEB0.colA[5] = 0x46;
        D_800DFEB0.colA[6] = 0xAA;
        D_800DFEB0.colA[7] = 0x30;
        D_800DFEB0.colB[0] = 0xFF;
        D_800DFEB0.colB[1] = 0xF0;
        D_800DFEB0.colB[2] = 0;
        D_800DFEB0.colB[3] = 0;
        D_800DFEB0.colB[4] = 0xFF;
        D_800DFEB0.colB[5] = 0x46;
        D_800DFEB0.colB[6] = 0xAA;
        D_800DFEB0.colB[7] = 0;
        D_800E1650 = 1;
        D_800E1654 = 0;
        D_800E1208 = 1;
        D_800E120C = 1;
        D_80102B20 = D_800F22C0;
        D_8010B341 = 1;
        D_8010B354 = 0;
        D_8010B33C = 0;
        loadsong(0x134, D_80109DC0);
        D_800E164A = 0;
        D_800E164E = 0;
        D_800E1644 = 0xFF;
    }
    D_800E1210 = D_800E1208;
    D_800E1208 = D_800E120C;
    if (D_800E1208 < 0x82) {
        SA->unkE = 0;
        SA->unkF = 0;
        SA->unk10 = 0;
    } else if (D_800E1208 < 0xB4) {
        SA->unkE = ((D_800E1208 * 0x29) - 0x14D2) / 50;
        SA->unkF = ((D_800E1208 * 0x3C) - 0x1E78) / 50;
        SA->unk10 = ((D_800E1208 * 0x52) - 0x29A4) / 50;
    } else {
        SA->unkE = 0x29;
        SA->unkF = 0x3C;
        SA->unk10 = 0x52;
    }
    func_8003B1A4();
    if (D_800E1208 >= 0x64) {
        func_80038A88();
    }
    if (D_800E1670 != 0) {
        if (D_800E1670->unk24 >= 0x7E) {
            if (D_800E1670->unk24 >= 0xC0) {
                sp40 = 0xFF;
            } else {
                sp40 = ((D_800E1670->unk24 * 0xFF) - 0x7D82) / 66;
            }
        } else {
            sp40 = 0;
        }
    } else {
        sp40 = 0xFF;
    }
    if (D_800E1674 != 0) {
        if (D_800E1674->unk24 == 0) {
            func_8007ACFC(D_80109DC0);
        }
        if (LWPlayAnimation(D_800E1674, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1674 = 0;
        }
        func_8006FE64(0, 0, 0x13F, 0xEF);
    }
    if (D_800DFF08 == 0) {
        D_800E1208 = 0;
        D_800E120C = 0;
        D_800E16B8 += 1;
        D_800E1646 = 1;
        return;
    }
    if (D_800E164A != D_800E1644) {
        if (D_800E164C == 0) {
            D_800E164C = 0x28;
        }
    } else {
        D_800E164C = 0;
        D_800E164A = D_800E1644;
        D_800E164E = D_800E1644;
    }
    func_800335F0(&D_800F22B4);
    sp34 = D_800F22B4++;
    sp34->words.w0 = 0xB900031D;
    sp34->words.w1 = 0x504340;
    func_8003396C(&D_800F22B4, D_800E1638, 0x18, 0x15, 0xFF, 0xFF, 0xFF, (D_800E164A * sp40) / 255);
    if ((D_800E1208 / 48) & 1) {
        sp3C = D_800E1208 % 48;
    } else {
        sp3C = 0x2F - (D_800E1208 % 48);
    }
    if (sp40 > 0) {
        func_8003396C(&D_800F22B4, D_800E1614, 0x18, 0x15, 0xFF, 0xFF, 0xFF, (D_800E164A * sp40) / 255);
    }
    for (sp38 = 0; sp38 < (D_800E1208 - D_800E1210); sp38++) {
        for (sp3C = 5; sp3C >= 0; sp3C--) {
            if (D_800E1690[sp3C] != 0) {
                D_800E1678[sp3C] += D_800E1690[sp3C];
                D_800E1690[sp3C] -= 1;
            }
        }
    }
    if (D_800E165C >= 0) {
        func_80038478(&D_800F22B4, 0x99 - (func_800388BC(D_800E08B4[D_800E165C]) / 2), 0x94, D_800E08B4[D_800E165C], 0xE6, 0x61, 0x1E, (s32) ((f64) (f32) D_800E164A * (1.0 - (f64) D_800E166C->unk28)));
    }
    func_800338B0(&D_800F22B4);
    if (D_800E1670 != 0) {
        if (LWPlayAnimation(D_800E1670, D_800E1208 - D_800E1210, 0, 0) != 0) {
            D_800E1670 = 0;
        }
    }
    if ((D_800E16B4 == 0) && (D_800DF770 != 0) && ((D_800DFD98 & 0xB000) || (D_800E165C >= 7) || (D_800E1208 >= 0x385)) && (D_800E1208 >= 0xF0)) {
        func_8007ADF8(D_80109DC0);
        func_8007AEE0(D_8010B358);
        D_800E16B4 = 1;
        func_8003E460();
        D_800F22C0 = D_801028D0;
        if (D_800DFE8C != 0) {
            func_8003FD78();
            func_8003F8D8();
            D_800E164E = D_800E164A;
            D_800E1644 = 0;
            if (D_800E1670 != 0) {
                D_800E1670->unk2C = D_800EDE84;
            }
            if (D_800E1674 != 0) {
                D_800E1674->unk2C = D_800EDE88;
            }
        } else {
            D_800E1646 = 1;
            D_800E16B8 += 1;
            D_800E1208 = 0;
            D_800E120C = 0;
        }
    }
}

typedef struct {
    /* 0x0000 */ u8 pad0[0x23B2];
    /* 0x23B2 */ s16 unk23B2;
} UnkGameState;

extern UnkGameState *D_8013DD00;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 pad22[0x12];
} Elem34;

extern Elem34 D_80102C64[];
extern f32 D_800EDE8C;
extern f32 D_800EDE90;
extern f32 D_800EDE94;
extern f32 D_800EDE98;
extern u8 D_800EDA40[];


void func_80069620(void) {
    D_80102C64[D_8013DD00->unk23B2].unk00 = D_800EDE8C;
    D_80102C64[D_8013DD00->unk23B2].unk04 = D_800EDE90;
    D_80102C64[D_8013DD00->unk23B2].unk08 = D_800EDE94;
    D_80102C64[D_8013DD00->unk23B2].unk0C = D_800EDE98;
    D_80102C64[D_8013DD00->unk23B2].unk10 = 0;
    D_80102C64[D_8013DD00->unk23B2].unk12 = 0;
    D_80102C64[D_8013DD00->unk23B2].unk14 = 0;
    D_80102C64[D_8013DD00->unk23B2].unk16 = 0;
    D_80102C64[D_8013DD00->unk23B2].unk18 = 0;
    D_80102C64[D_8013DD00->unk23B2].unk20 = 0;
    D_80102C64[D_8013DD00->unk23B2].unk1A = 0;
    D_80102C64[D_8013DD00->unk23B2].unk1C = 0;
    D_80102C64[D_8013DD00->unk23B2].unk1E = 0;
    func_80029760(D_800EDA40);
}

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ u8 pad08[0x08];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x06];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 pad1A[0x1A];
} Unk34;    /* size 0x34 */


extern Unk34 D_80102C6C[];

void func_800698CC(void) {
    D_80102C6C[D_8013DD00->unk23B2].unk10 = 0xFF;
    D_80102C6C[D_8013DD00->unk23B2].unk00 = 2.0f;
}

void func_80069940(void) {
    D_80102C6C[D_8013DD00->unk23B2].unk18 = 0xFF;
    D_80102C6C[D_8013DD00->unk23B2].unk04 = 2.0f;
}

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ u8 pad32[2];
} Unk699;                       /* size 0x34 */

typedef struct {
    u8 pad0[0x23B2];
    s16 unk23B2;
    u8 pad23B4[0x2B14 - 0x23B4];
    s16 unk2B14;
} UnkGS699;

extern Unk699 D_80102C88[];
extern s16 D_80160C64;
extern s16 D_800E23B4;
extern s16 D_800DFEAC;
extern s32 D_800E16BC;
extern s32 D_800E16C0;
extern s32 D_80102C80;
extern u8 D_8014D262;
extern Gfx *D_800F22B4;
typedef struct {
    u8 pad0[0x1080];
    Mtx m[64];
} UnkFrame699;
#define GS ((UnkGS699 *)D_8013DD00)
#define FR ((UnkFrame699 *)D_801028D4)
extern u8 *D_80103358;
extern u8 *D_8010335C;
extern u8 *D_80103360;
extern u8 *D_80103364;
extern Vtx D_800E16C8[];
extern u8 D_800EDA5C[];

extern f32 D_800EDE9C;
extern f32 D_800EDEA0;
extern f32 D_800EDEA4;
extern f32 D_800EDEA8;
extern f32 D_800EDEAC;
extern f32 D_800EDEB0;
extern f32 D_800EDEB4;
extern f32 D_800EDEB8;
extern f32 D_800EDEBC;
extern f32 D_800EDEC0;
extern f32 D_800EDEC4;
extern f32 D_800EDEC8;
extern f32 D_800EDECC;
extern f32 D_800EDED0;
extern f32 D_800EDED4;
extern f32 D_800EDED8;
extern f32 D_800EDEDC;
extern f32 D_800EDEE0;
extern f32 D_800EDEE4;
extern f32 D_800EDEE8;
extern f32 D_800EDEEC;
extern f32 D_800EDEF0;
extern f32 D_800EDEF4;
extern f32 D_800EDEF8;
extern f64 D_800EDF00;
extern f64 D_800EDF08;
extern f64 D_800EDF10;
extern f64 D_800EDF18;
extern f64 D_800EDF20;
extern f64 D_800EDF28;
extern f64 D_800EDF30;
extern f64 D_800EDF38;
extern f64 D_800EDF40;
extern f64 D_800EDF48;
extern f64 D_800EDF50;
extern f64 D_800EDF58;
extern f64 D_800EDF60;

extern void func_800338B0(Gfx **);
extern void func_80038478(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern void func_80038760(Gfx **, s32, s32, u8 *, s32, s32, s32, s32);
extern s32 func_800388BC(u8 *);
extern s32 func_80038A50(u8 *);
extern void guRotateRPY_2(Mtx *, f32, f32, f32);

#define CUR (D_80102C88[GS->unk23B2 - 1])
#define IDX (GS->unk23B2)

void func_800699B4(void) {
    f32 sp254;
    f32 sp250;
    s32 sp24C;
    s32 sp248;
    s32 sp244;
    s32 sp240;
    s32 sp23C;
    s32 sp238;
    s32 sp234;
    s32 sp230;
    s32 sp22C;
    s32 sp228;
    u8 sp218[13];

    sp24C = GS->unk2B14;
    for (sp228 = 0; sp228 < D_80160C64; sp228++) {
        if (CUR.unk28 > 0) {
            CUR.unk28 -= 10;
            if (CUR.unk28 < 0) {
                CUR.unk28 = 0;
            }
        }
        if (CUR.unk30 > 0) {
            CUR.unk30 -= 10;
            if (CUR.unk30 < 0) {
                CUR.unk30 = 0;
            }
        }
    }
    if ((CUR.unk2C > sp24C) && (CUR.unk2C >= 2)) {
        CUR.unk28 = 0xC0;
        CUR.unk18 = D_800EDE9C;
    }
    if ((CUR.unk2C < sp24C) && (CUR.unk2C >= 2)) {
        CUR.unk28 = 0x80;
        CUR.unk18 = 1.0f;
    }
    sp248 = 0;
    sp254 = D_800EDEA0;
    sp244 = 0;
    sp250 = D_800EDEA4;
    sp240 = 0;
    sp23C = 0;
    if (sp24C > 0) {
        if (sp24C < 3) {
            sp248 = 0x8C;
            sp254 = D_800EDEA8;
        } else if (sp24C < 5) {
            sp248 = 0xA0;
            sp254 = D_800EDEAC;
            sp244 = 0x14;
            sp250 = D_800EDEB0;
        } else if (sp24C < 7) {
            sp248 = 0xB4;
            sp254 = D_800EDEB4;
            sp244 = 0x1E;
            sp250 = 0.75f;
            sp240 = 0x40;
        } else if (sp24C < 9) {
            sp248 = 0xC8;
            sp254 = D_800EDEB8;
            sp244 = 0x28;
            sp250 = D_800EDEBC;
            sp240 = 0x80;
        } else if (sp24C < 0xB) {
            sp248 = 0xDC;
            sp254 = D_800EDEC0;
            sp244 = 0x32;
            sp250 = D_800EDEC4;
            sp240 = 0xC0;
        } else if (sp24C < 0xD) {
            sp248 = 0xF0;
            sp254 = D_800EDEC8;
            sp244 = 0x3C;
            sp250 = D_800EDECC;
            sp240 = 0xFF;
        } else if (sp24C < 0xF) {
            sp248 = 0xFA;
            sp254 = D_800EDED0;
            sp244 = 0x46;
            sp250 = D_800EDED4;
            sp240 = 0xFF;
            sp23C = 0x60;
        } else if (sp24C < 0x11) {
            sp248 = 0xFF;
            sp254 = D_800EDED8;
            sp244 = 0x50;
            sp250 = D_800EDEDC;
            sp240 = 0xFF;
            sp23C = 0xC0;
        } else if (sp24C < 0x13) {
            sp248 = 0xFF;
            sp254 = 0.75f;
            sp244 = 0x55;
            sp250 = D_800EDEE0;
            sp240 = 0xFF;
            sp23C = 0xFF;
        } else if (sp24C < 0x15) {
            sp248 = 0xFF;
            sp254 = D_800EDEE4;
            sp244 = 0x5A;
            sp250 = D_800EDEE8;
            sp240 = 0xFF;
            sp23C = 0xFF;
        } else if (sp24C < 0x17) {
            sp248 = 0xFF;
            sp254 = D_800EDEEC;
            sp244 = 0x5F;
            sp250 = D_800EDEF0;
            sp240 = 0xFF;
            sp23C = 0xFF;
        } else {
            sp248 = 0xFF;
            sp254 = D_800EDEF4;
            sp244 = 0x64;
            sp250 = D_800EDEF8;
            sp240 = 0xFF;
            sp23C = 0xFF;
        }
    }
    for (sp228 = 0; sp228 < D_80160C64; sp228++) {
        if (sp248 > CUR.unk20) {
            CUR.unk20 += 2;
            if (CUR.unk20 > sp248) {
                CUR.unk20 = sp248;
            }
        }
        if (sp248 < CUR.unk20) {
            if (sp24C <= 0) {
                CUR.unk20 -= 8;
            } else {
                CUR.unk20 -= 2;
            }
            if (CUR.unk20 < sp248) {
                CUR.unk20 = sp248;
            }
        }
        if (sp254 > CUR.unk10) {
            CUR.unk10 += D_800EDF00;
            if (CUR.unk10 > sp254) {
                CUR.unk10 = sp254;
            }
        }
        if (sp254 < CUR.unk10) {
            CUR.unk10 -= D_800EDF08;
            if (CUR.unk10 < sp254) {
                CUR.unk10 = sp254;
            }
        }
        if (sp244 > CUR.unk22) {
            CUR.unk22 += 0;
            if (CUR.unk22 > sp244) {
                CUR.unk22 = sp244;
            }
        }
        if (sp244 < CUR.unk22) {
            CUR.unk22 -= 0;
            if (CUR.unk22 < sp244) {
                CUR.unk22 = sp244;
            }
        }
        if (sp250 > CUR.unk14) {
            CUR.unk14 += D_800EDF10;
            if (CUR.unk14 > sp250) {
                CUR.unk14 = sp250;
            }
        }
        if (sp250 < CUR.unk14) {
            CUR.unk14 -= D_800EDF18;
            if (CUR.unk14 < sp250) {
                CUR.unk14 = sp250;
            }
        }
        if (sp240 > CUR.unk24) {
            CUR.unk24 += 2;
            if (CUR.unk24 > sp240) {
                CUR.unk24 = sp240;
            }
        }
        if (sp240 < CUR.unk24) {
            CUR.unk24 -= 2;
            if (CUR.unk24 < sp240) {
                CUR.unk24 = sp240;
            }
        }
        if (sp23C > CUR.unk26) {
            CUR.unk26 += 2;
            if (CUR.unk26 > sp23C) {
                CUR.unk26 = sp23C;
            }
        }
        if (sp23C < CUR.unk26) {
            CUR.unk26 -= 2;
            if (CUR.unk26 < sp23C) {
                CUR.unk26 = sp23C;
            }
        }
        CUR.unk00 += D_800EDF20;
        CUR.unk04 += D_800EDF28;
        CUR.unk08 += D_800EDF30;
        CUR.unk0C += D_800EDF38;
        CUR.unk2A += 0x15;
        if (CUR.unk2A >= 0x100) {
            CUR.unk2A = 0xFF;
        }
    }
    if (GS->unk23B2 == 1) {
        guOrtho(&FR->m[0], -160.0f, 160.0f, -120.0f, 120.0f, -1000.0f, 1000.0f, 2.0f);
        guOrtho(&FR->m[23], -160.0f, 160.0f, -120.0f, 120.0f, -1000.0f, 0.0f, 2.0f);
        guOrtho(&FR->m[24], -160.0f, 160.0f, -120.0f, 120.0f, 0.0f, 1000.0f, 2.0f);
    }
    if (D_8014D262 == 1) {
        guTranslate(&FR->m[IDX], 118.0f, 78.0f, 0.0f);
        guTranslate(&FR->m[IDX + 2], 118.0f, -53.0f, 0.0f);
        sp230 = 0x116;
        sp22C = 0x20;
    } else {
        if (GS->unk23B2 == 1) {
            guTranslate(&FR->m[IDX], 62.0f, 90.0f, 0.0f);
            guTranslate(&FR->m[IDX + 2], -27.0f, 90.0f, 0.0f);
            sp230 = 0x8E;
            sp22C = 0x15;
        } else {
            guTranslate(&FR->m[IDX], -62.0f, 90.0f, 0.0f);
            guTranslate(&FR->m[IDX + 2], 30.0f, 90.0f, 0.0f);
            sp230 = 0xB2;
            sp22C = 0x15;
        }
    }
    guRotateRPY_2(&FR->m[IDX + 10], 0.0f, 0.0f, CUR.unk00);
    guRotateRPY_2(&FR->m[IDX + 12], 0.0f, 0.0f, CUR.unk00 * D_800EDF40);
    guRotateRPY_2(&FR->m[IDX + 14], sinf(CUR.unk04 / D_800EDF48) * 10.0 + D_800EDF50, 0.0f, CUR.unk04);
    guRotateRPY_2(&FR->m[IDX + 18], 0.0f, 0.0f, CUR.unk08);
    guRotateRPY_2(&FR->m[IDX + 16], sinf(CUR.unk04 / D_800EDF58) * 10.0 + 120.0, 0.0f, CUR.unk04 + D_800EDF60);
    guRotateRPY_2(&FR->m[IDX + 20], 0.0f, 0.0f, CUR.unk0C);
    guScale(&FR->m[IDX + 4], CUR.unk10, CUR.unk10, CUR.unk10);
    guScale(&FR->m[IDX + 6], CUR.unk14, CUR.unk14, CUR.unk14);
    guScale(&FR->m[IDX + 24], CUR.unk14 * CUR.unk18, CUR.unk14 * CUR.unk18, CUR.unk14 * CUR.unk18);
    guScale(&FR->m[IDX + 26], CUR.unk14 * CUR.unk1C, CUR.unk14 * CUR.unk1C, CUR.unk14 * CUR.unk1C);
    gDPSetTextureLUT(D_800F22B4++, G_TT_NONE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_AVERAGE);
    gDPSetRenderMode(D_800F22B4++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPClearGeometryMode(D_800F22B4++, G_ZBUFFER | G_SHADING_SMOOTH | G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(D_800F22B4++, G_SHADE);
    gSPTexture(D_800F22B4++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(D_800F22B4++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTile(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + 0x80001640, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001080, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001400, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001500, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gDPSetPrimColor(D_800F22B4++, 0, 0, 0, 0xE1, 0xFF, (CUR.unk24 * D_800E23B4) / 255);
    gDPLoadTextureTile(D_800F22B4++, D_80103360, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, 0, 31, 31, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x7F, 0x7F);
    gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
    if (CUR.unk24 != 0) {
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    }
    gDPSetPrimColor(D_800F22B4++, 0, 0, 0, 0xE1, 0xFF, (CUR.unk26 * D_800E23B4) / 255);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001080, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001480, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001580, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
    if (CUR.unk26 != 0) {
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    }
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + 0x80001080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001080, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001200, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gDPSetPrimColor(D_800F22B4++, 0, 0, 0, 0xE1, 0xFF, (CUR.unk22 * D_800E23B4) / 255);
    gDPLoadTextureTile(D_800F22B4++, D_8010335C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, 0, 31, 31, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x7F, 0x7F);
    gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
    if (CUR.unk22 != 0) {
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    }
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001080, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001300, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001180, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gDPSetPrimColor(D_800F22B4++, 0, 0, 0xFF, 0xFF, 0xFF, (CUR.unk20 * D_800E23B4) / 255);
    gDPLoadTextureTile(D_800F22B4++, D_80103358, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, 0, 31, 31, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x7F, 0x7F);
    gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
    if (CUR.unk20 != 0) {
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    }
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001080, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001380, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001680, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gDPSetPrimColor(D_800F22B4++, 0, 0, 0xFF, 0xFF, 0xFF, (CUR.unk28 * D_800E23B4) / 255);
    gDPLoadTextureTile(D_800F22B4++, D_80103364, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, 0, 31, 31, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x7F, 0x7F);
    gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
    if (CUR.unk28 != 0) {
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    }
    if (CUR.unk30 != 0) {
        gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001100, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001380, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001700, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
        gDPSetPrimColor(D_800F22B4++, 0, 0, 0xFF, 0xFF, 0xFF, (CUR.unk30 * D_800E23B4) / 255);
        gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
        gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
        gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    }
    gSPTexture(D_800F22B4++, 0, 0, 0, 0, G_OFF);
    func_800335F0(&D_800F22B4);
    if (sp24C < CUR.unk2C) {
        D_80102C80 = CUR.unk2C;
        D_800E16BC = 0x400;
        D_800E16C0 = 0xFF;
    }
    if (D_800E16C0 > 0) {
        sp218[0xC] = 0;
        sp238 = 0xC;
        sp234 = D_80102C80;
        if (sp234 >= 0x3E8) {
            sp234 = 0x3E7;
        }
        while (sp234 > 0) {
            sp238 -= 1;
            sp218[sp238] = (sp234 % 10) + 0x30;
            sp234 = sp234 / 10;
        }
        D_800DFEAC = D_800E16BC;
        func_80038760(&D_800F22B4, (sp230 * 4) - (func_80038A50(&sp218[sp238]) >> 1), ((sp22C * 4) - func_80038A50(D_800EDA5C)) + 0x18, &sp218[sp238], 0, 0x80, 0x80, (D_800E23B4 * D_800E16C0) / 255);
        D_800DFEAC = 0x400;
        D_800E16BC -= 0x40;
        D_800E16C0 -= 0x18;
    }
    if (CUR.unk2C != sp24C) {
        CUR.unk2A = 0;
        CUR.unk2E = CUR.unk2C;
    }
    if (CUR.unk2E < sp24C) {
        if (CUR.unk2E > 0) {
            sp218[0xC] = 0;
            sp238 = 0xC;
            sp234 = CUR.unk2E;
            if (sp234 >= 0x3E8) {
                sp234 = 0x3E7;
            }
            while (sp234 > 0) {
                sp238 -= 1;
                sp218[sp238] = (sp234 % 10) + 0x30;
                sp234 = sp234 / 10;
            }
            func_80038478(&D_800F22B4, sp230 - (func_800388BC(&sp218[sp238]) >> 1), sp22C, &sp218[sp238], 0, 0x80, 0x80, ((0xFF - CUR.unk2A) * D_800E23B4) / 255);
        }
        if (sp24C > 0) {
            sp218[0xC] = 0;
            sp238 = 0xC;
            sp234 = sp24C;
            if (sp234 >= 0x3E8) {
                sp234 = 0x3E7;
            }
            while (sp234 > 0) {
                sp238 -= 1;
                sp218[sp238] = (sp234 % 10) + 0x30;
                sp234 = sp234 / 10;
            }
            func_80038478(&D_800F22B4, sp230 - (func_800388BC(&sp218[sp238]) >> 1), sp22C, &sp218[sp238], 0, 0x80, 0x80, D_800E23B4);
        }
    } else if (sp24C > 0) {
        sp218[0xC] = 0;
        sp238 = 0xC;
        sp234 = sp24C;
        if (sp234 >= 0x3E8) {
            sp234 = 0x3E7;
        }
        while (sp234 > 0) {
            sp238 -= 1;
            sp218[sp238] = (sp234 % 10) + 0x30;
            sp234 = sp234 / 10;
        }
        func_80038478(&D_800F22B4, sp230 - (func_800388BC(&sp218[sp238]) >> 1), sp22C, &sp218[sp238], 0, 0x80, 0x80, D_800E23B4);
    }
    func_800338B0(&D_800F22B4);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + 0x80001680, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetTextureLUT(D_800F22B4++, G_TT_NONE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_AVERAGE);
    gDPSetRenderMode(D_800F22B4++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPClearGeometryMode(D_800F22B4++, G_ZBUFFER | G_SHADING_SMOOTH | G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(D_800F22B4++, G_SHADE);
    gSPTexture(D_800F22B4++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(D_800F22B4++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTile(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001080, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001400, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001500, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gDPSetPrimColor(D_800F22B4++, 0, 0, 0, 0xE1, 0xFF, (CUR.unk24 * D_800E23B4) / 255);
    gDPLoadTextureTile(D_800F22B4++, D_80103360, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, 0, 31, 31, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(D_800F22B4++, G_TX_RENDERTILE, 0, 0, 0x7F, 0x7F);
    gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
    gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
    gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    gDPSetPrimColor(D_800F22B4++, 0, 0, 0, 0xE1, 0xFF, (CUR.unk26 * D_800E23B4) / 255);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001080, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001480, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u8 *) D_801028D4 + (IDX << 6) + 0x80001580, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPVertex(D_800F22B4++, D_800E16C8, 4, 0);
    gSP1Triangle(D_800F22B4++, 0, 1, 2, 0);
    gSP1Triangle(D_800F22B4++, 0, 2, 3, 0);
    gSPTexture(D_800F22B4++, 0, 0, 0, 0, G_OFF);
    CUR.unk2C = sp24C;
}


extern s16 D_800DFE90;
extern s32 D_800DFE84;
extern s32 D_800E1218;
extern s32 D_800DFF18;

void updateScreenTimersOnRetrace(void) {
    s32 i;
    if (D_800DFE90 > 0) D_800DFE90--;
    if (D_800DFE84 != 0) return;
    if (D_800E120C > 0) D_800E120C++;
    if (D_800E1218 > 0) D_800E1218--;
    if (D_800E1204 > 0) {
        D_800E1204--;
        D_800E1202 = (D_800E1204 * D_800E1206 + (20 - D_800E1204) * D_800E11FA) / 20;
    }
    D_800DFF18++;
    D_800DFEE8++;
    if (D_800DFEF0 > 0) {
        D_800DFEF0--;
        for (i = 0; i < 4; i++) {
            D_800DFEB0.target[i] = (D_800DFEB0.colB[i]*D_800DFEF0 + D_800DFEB0.colA[i]*(40 - D_800DFEF0)) / 40;
            D_800DFEB0.target[i + 4] = (D_800DFEB0.colB[i + 4]*D_800DFEF0 + D_800DFEB0.colA[i + 4]*(40 - D_800DFEF0)) / 40;
        }
    }
    if (D_800E1650 != 0) D_800E1650++;
    if (D_800E164C > 0) {
        D_800E164C--;
        D_800E164A = (D_800E164C * D_800E164E + (40 - D_800E164C) * D_800E1644) / 40;
    }
}

extern s16 D_800E171C;
extern u16 D_800DFD68;
extern u16 D_800DFD6C;
extern u16 D_800DFD70;
extern u16 D_800DFD74;
extern s16 D_800DFD78;
extern s16 D_800DFD7C;
extern s16 D_800DFD80;
extern s16 D_800DFD84;
extern u16 D_800E11F8;
extern s32 D_800DFD40;
extern s16 D_8013FAD2;
extern s16 D_8013FAD0;
extern s16 D_8013FAD4;
extern s8 D_800E2AC4;
extern u16 D_800DFD60;
extern s8 D_80113320;
extern u16 D_801125EC;
extern u16 D_801125EE;
extern s8 D_80116588;
extern u16 D_80115854;
extern u16 D_80115856;
extern u16 D_800E1710;
extern s16 D_800E2260;
extern s16 D_800E170C;
extern u16 D_800E1714;
extern s16 D_800E1718;
extern u16 D_800E1720[180][4];
extern u16 D_800E1CC0[180][4];

void func_8006DF3C(u16 arg0, u16 arg1) {
    s32 sp4;

    if (D_800E171C == -1) {
        D_800E171C = arg1;
    }
    switch (arg1) {
    case 0:
        D_800DFD78 = D_800DFD68;
        sp4 = D_800DFD68;
        D_800DFD68 = arg0;
        break;
    case 1:
        D_800DFD7C = D_800DFD6C;
        sp4 = D_800DFD6C;
        D_800DFD6C = arg0;
        break;
    case 2:
        D_800DFD80 = D_800DFD70;
        sp4 = D_800DFD70;
        D_800DFD70 = arg0;
        break;
    case 3:
        D_800DFD84 = D_800DFD74;
        sp4 = D_800DFD74;
        D_800DFD74 = arg0;
        break;
    }
    if ((D_800E1646 == 0) || (D_800E11F8 != 0) || (D_800DFD40 != 0) || (D_800E121C >= 0) || (D_8013FAD2 != 0) || (D_8013FAD0 != 0) || (D_8013FAD4 != 0) || (D_800E2AC4 != 0) || (D_800DFD60 != 0)) {
        if (arg1 == D_80113320) {
            D_801125EC = arg0;
            D_801125EE = 0xFFFF;
        }
        if (arg1 == D_80116588) {
            D_80115854 = arg0;
            D_80115856 = 0xFFFF;
        }
        D_800E1710 = D_800E1714;
        D_800E2260 = 1;
        D_800E170C = 0xA;
        return;
    }
    if (D_800E170C != 0) {
        if ((D_800E170C != 0) && (D_800E171C == arg1)) {
            D_800E170C -= 1;
        }
        if (arg1 == D_80113320) {
            D_801125EC = arg0;
            D_801125EE = 0xFFFF;
        }
        if (arg1 == D_80116588) {
            D_80115854 = arg0;
            D_80115856 = 0xFFFF;
        }
        D_800E1710 = D_800E1714;
        D_800E2260 = 1;
        return;
    }
    if (D_800E2260 != 0) {
        D_800E2260 = 0;
    }
    if (D_800E1718 == arg1) {
        D_800E1714 = (D_800E1714 + 1) % 180;
        if (D_800E1714 == D_800E1710) {
            D_800E1710 = (D_800E1710 + 1) % 180;
        }
        D_800E1720[D_800E1714][0] = 0;
        D_800E1720[D_800E1714][1] = 0;
        D_800E1720[D_800E1714][2] = 0;
        D_800E1720[D_800E1714][3] = 0;
        D_800E1CC0[D_800E1714][0] = 0;
        D_800E1CC0[D_800E1714][1] = 0;
        D_800E1CC0[D_800E1714][2] = 0;
        D_800E1CC0[D_800E1714][3] = 0;
    }
    D_800E1720[D_800E1714][arg1] = arg0;
    D_800E1CC0[D_800E1714][arg1] = sp4;
    if (D_800E1718 == -1) {
        D_800E1718 = arg1;
    }
}

extern u16 func_800ACB94(u16, u16, void *);
extern void func_800ADCF0(void *);
extern s32 func_800B9134(void);

extern u8 D_800E44FC;
extern s16 D_80102664;
extern s16 D_801125C0;
extern s16 D_80115828;
extern s16 D_801033D0;
extern f32 *D_801033CC;
extern f32 D_800EDF68;
extern s16 D_800DFE00;
extern u8 D_80110220[];
extern u8 D_80113488[];
extern s16 D_801126DA;
extern s16 D_80113454;
extern s16 D_80112634;
extern s16 D_801125F2;
extern s16 D_80115942;
extern s16 D_801166BC;
extern s16 D_8011589C;
extern s16 D_8011585A;

void func_8006E418(u16 arg0, u16 arg1, u16 arg2) {
    if (D_800E170C != 0) {
        if (arg2 == D_80113320) {
            D_801125EC = arg0;
            D_801125EE = 0xFFFF;
        }
        if (arg2 == D_80116588) {
            D_80115854 = arg0;
            D_80115856 = 0xFFFF;
        }
        return;
    }
    if (((D_800E44A8 == 0xA) || ((D_800E44A8 == 3) && (D_80113323 != 0))) && (arg0 != 0)) {
        D_800E121C = D_800E0754[0];
        if (D_80102664 != 0) {
            D_800E1220 = D_800E0754[D_800E0754[0] + 1];
        }
        D_800E1208 = 0;
        D_800E120C = 0;
        if (arg2 == D_80113320) {
            D_801125EC = arg0;
            D_801125EE = 0xFFFF;
        }
        if (arg2 == D_80116588) {
            D_80115854 = arg0;
            D_80115856 = 0xFFFF;
        }
        return;
    }
    if (((D_801125C0 != 0) && (arg2 == D_80113320)) || ((D_8015D980 == 2) && (D_80115828 != 0) && (arg2 == D_80116588))) {
        if ((D_801033D0 >= 0) && (arg0 & 0xB000) && !(arg1 & 0xB000)) {
            if (D_801033CC != 0) {
                D_801033CC[0xB] = D_800EDF68;
            }
            if (arg2 == D_80113320) {
                D_801125EC = arg0;
                D_801125EE = 0xFFFF;
            }
            if (arg2 == D_80116588) {
                D_80115854 = arg0;
                D_80115856 = 0xFFFF;
            }
            return;
        } else {
            if ((arg0 & 0x1000) && !(arg1 & 0x1000)) {
                if (D_800E44FC != 0) {
                    if (arg2 == D_80113320) {
                        func_800ADCF0(D_80110220);
                        D_801126DA = 0;
                        D_80113454 = 0;
                        D_800E44FC = 0;
                        D_80112634 = 0x429A;
                        D_801125F2 = 1;
                    }
                    if (arg2 == D_80116588) {
                        func_800ADCF0(D_80113488);
                        D_80115942 = 0;
                        D_801166BC = 0;
                        D_800E44FC = 0;
                        D_8011589C = 0x429A;
                        D_8011585A = 1;
                    }
                    goto block_47;
                }
                if (func_800B9134() == 0) {
                    D_8013FAD0 = 1;
                    D_800DFE00 = arg2;
                    if (arg2 == D_80113320) {
                        D_801125EC = arg0;
                        D_801125EE = 0xFFFF;
                    }
                    if (arg2 == D_80116588) {
                        D_80115854 = arg0;
                        D_80115856 = 0xFFFF;
                    }
                    return;
                }
            }
        }
    }
block_47:
    if ((D_801125C0 != 0) && (arg2 == D_80113320)) {
        D_801125EC = func_800ACB94(arg0, D_801125EC, D_80110220);
        D_801125EE = 0xFFFF;
        if (D_800E44A8 == 6) {
            D_80115854 = func_800ACB94(0, D_80115854, D_80113488);
            D_80115856 = 0xFFFF;
        }
    }
    if ((D_800E44A8 != 6) && (D_80115828 != 0) && (arg2 == D_80116588)) {
        D_80115854 = func_800ACB94(arg0, D_80115854, D_80113488);
        D_80115856 = 0xFFFF;
    }
}




void processBufferedControllerSamples(void) {
    u16 i;
    u16 cur;
    u16 end;

    end = D_800E1714;
    cur = D_800E1710;
    while (cur != end) {
        for (i = 0; i < 4; i++) {
            if (D_800DF770 & (1 << i)) {
                func_8006E418(D_800E1720[cur][i], D_800E1CC0[cur][i], i);
            }
        }
        cur = (cur + 1) % 180;
        D_800E1710 = (D_800E1710 + 1) % 180;
    }
}

extern u16 D_800DFD58[];

void func_8006EAAC(s16 arg0) {
    D_800DFD58[arg0] = 0xFF;
}


typedef struct {
    u8 pad0[0x18E8];
    u8 *unk18E8[2];
    u8 pad18F0[0x3200 - 0x18F0];
    u8 *unk3200[2];
} UnkFACC0;

extern UnkFACC0 D_800FACC0;
extern u8 D_802A2000[];
extern u8 D_800EDA60[];
extern u8 D_800EDA7C[];

void beginGraphicsFrame(void *, void *);

void func_8006EAD8(s32 arg0, s32 arg1) {
    D_800FACC0.unk18E8[0] = D_802A2000 - arg0 * 2 - 0x8000;
    D_800FACC0.unk3200[0] = D_802A2000 - arg0 - 0x8000;
    D_800FACC0.unk18E8[1] = D_802A2000 - (arg0 * 2 + arg1 * 2) - 0x8000;
    D_800FACC0.unk3200[1] = D_802A2000 - (arg0 * 2 + arg1) - 0x8000;
    beginGraphicsFrame(D_801028C8, D_801028D4);
    func_80029760(D_800EDA60, D_800FACC0.unk18E8[0], D_800FACC0.unk3200[0]);
    func_80029760(D_800EDA7C, D_800FACC0.unk18E8[1], D_800FACC0.unk3200[1]);
}


void func_8007F3D4(u8 *);

extern s32 D_800DFDA0;


void func_8006EC00(void) {
    if (D_800DFD5C != 0) {
        return;
    }
    D_800E170C = 10;
    D_800DFD5C = 1;
    D_800DFD60 = 1;
    D_800DFDA0 = -1;
    while (D_800DF710 > D_800DF714) {
        func_8002A140();
    }
    func_8006EAD8(0x18000, 0x2000);
    D_800F22C0 = D_800F22C4;
    D_800DFF00 = (u16 *) D_800F22C0;
    D_800F22C0 = D_800F22C0 + 0x25800;
    D_800DFEFC = (UnkImg *) loadAsset(D_736C50, 0, 8);
    ((u8 **)&D_800DFEB0)[0] = loadAsset(D_736C50, 1, 8);
    ((u8 **)&D_800DFEB0)[1] = loadAsset(D_736C50, 2, 8);
    ((u8 **)&D_800DFEB0)[2] = loadAsset(D_736C50, 0x76, 8);
    ((u8 **)&D_800DFEB0)[3] = loadAsset(D_736C50, 4, 8);
    ((u8 **)&D_800DFEB0)[4] = loadAsset(D_736C50, 5, 8);
    ((u8 **)&D_800DFEB0)[5] = loadAsset(D_736C50, 6, 8);
    ((u8 **)&D_800DFEB0)[6] = loadAsset(D_736C50, 7, 8);
    D_800E1010 = loadAsset(D_736C50, 0x16, 8);
    func_80038254(D_800E1010);
    D_801026B8 = D_800F22C0;
    if (D_800DF770 != 0) {
        func_8007F3D4(D_800E2818);
    }
    D_800E170C = 10;
    D_800DFD60 = 0;
}

extern u8 D_801026C2;
extern u16 D_801033AA;
extern s16 D_8013D264;
extern u16 D_800E2262[];
extern u16 D_800E2296[];
extern s16 D_800E23BC;
extern u16 D_800E2264[];
extern u16 D_800E2298[];
extern u8 *D_801033BC;
extern s16 D_800DFE04[];
extern s16 D_800DFE06[];
extern s16 D_800DFE08[];
extern s16 D_800E44A4;
extern s16 D_800DFE60[];
extern u8 *D_80103220;
extern u8 D_8015FDF6;
extern u32 D_8013E474;
extern u32 D_8013DD08;
extern s32 D_800E4480;
extern s16 D_800DFE48[];
extern s16 D_80112D06;
extern s16 D_80112D08;
extern s16 D_801039EC;

void *loadAnim(s32 arg0);
void *loadMesh(s32 arg0);
u8 *LWAllocateMemory(u32 arg0, void *arg1, void **arg2, s32 arg3, s32 *arg4);
void func_800BA25C(void);
void func_8007ADF8(u8 *arg0);
void loadsong(s32 arg0, u8 *arg1);
void func_8007ACFC(u8 *arg0);
void func_80071DD8(s32 arg0);

void func_8006EE6C(void) {
    s32 i;
    s32 notfound;
    s32 size;
    void *seq;
    void *bank;

    D_801026C2 = 1;
    while (D_800DF710 > D_800DF714) {
        func_8002A140();
    }
    D_801033CC = 0;
    D_801026C2 = 1;
    D_801033AA = 0;
    if (D_8015D980 != 2) {
        if (D_8013D264 != 0) {
            seq = (s32) loadAnim(D_800E2262[D_8013D264]);
            bank = (s32) loadMesh(D_800E2296[D_8013D264]);
            D_800E23BC = D_8013D264 - 1;
        } else {
            seq = (s32) loadAnim(D_800E2264[D_800E23BC]);
            bank = (s32) loadMesh(D_800E2298[D_800E23BC]);
        }
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        D_801033BC = LWAllocateMemory(D_800F22C0, seq, &bank, 1, &i);
        D_800F22C0 += i;
        D_801033BC[0x49] = 0;
    }
    if (D_800E44A8 == 5) {
        for (i = 0; i < 11; i++) {
            if (D_800DFE04[i * 3] == D_800E44A4) {
                D_80103220 = loadAsset(D_736C50, D_800DFE60[i], 8);
                break;
            }
        }
    }
    D_8015FDF6 = 0;
    if ((D_800E44A4 == 8) || (D_800E44A4 == 3)) {
        if (D_8015D980 == 1) {
            if (D_800E44A8 != 0xC) {
                D_8015FDF6 = 1;
                func_800BA25C();
            }
        }
    }
    D_8013DD08 = D_8013E474 = D_800F22C0;
    if (D_801033D0 >= 0) {
        if (((D_800E44A8 == 2) && (D_800E4498 == 0)) || (D_800E44A8 == 5)) {
            if (D_800E44A8 == 2) {
                seq = (s32) loadAnim(0xCD);
                bank = (s32) loadMesh(0x45);
                D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                D_801033CC = LWAllocateMemory(D_800F22C0, seq, &bank, 1, &size);
                D_800F22C0 += size;
                D_801026C2 = 0;
                func_8007ADF8(&D_80108828);
                func_80079B80(0x7FFF, &D_80108828);
                D_80109DA9 = 1;
                D_80109DBC = 0;
                D_80109DA4 = 0;
                loadsong(0x144, &D_80108828);
                func_8007ACFC(&D_80108828);
            } else {
                notfound = 1;
                for (i = 0; i < 11; i++) {
                    if (D_800DFE04[i * 3] == D_800E44A4) {
                        seq = (s32) loadAnim(D_800DFE06[i * 3]);
                        bank = (s32) loadMesh(D_800DFE08[i * 3]);
                        notfound = 0;
                        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
                        D_801033CC = LWAllocateMemory(D_800F22C0, seq, &bank, 1, &size);
                        D_800F22C0 += size;
                        if (D_800DFE48[i] != 0) {
                            D_801026C2 = 0;
                            func_8007ADF8(&D_80108828);
                            func_80079B80(0x7FFF, &D_80108828);
                            D_80109DA9 = 1;
                            D_80109DBC = 0;
                            D_80109DA4 = 0;
                            loadsong(D_800DFE48[i], &D_80108828);
                            func_8007ACFC(&D_80108828);
                        }
                        break;
                    }
                }
            }
            if (D_800E4480 == 0) {
                D_801033D0 = 0;
            }
            func_80071DD8(0);
        } else {
            D_801033D0 = -1;
        }
    }
    if (D_801033CC == 0) {
        D_801033D0 = -1;
    }
    if ((D_801033D0 < 0) && (D_8015D980 == 1) && (D_800E44A8 != 4) && (D_800E44A8 != 0xA) && (D_800E44A8 != 3)) {
        func_8007ADF8(&D_80108828);
        func_80079B80(0x7FFF, &D_80108828);
        D_80109DA9 = 1;
        D_80109DBC = 0;
        D_80109DA4 = 0;
        loadsong(0x140, &D_80108828);
    }
    D_801039EC = D_80112D06 + D_80112D08;

}

/* SOLVED (session 10): the outer construct is NOT if/else. It is
 * "if (cond) { ...; return; }" followed by the old else-body as plain
 * fallthrough code. Mechanism, proven with /tmp/probe4.c vs /tmp/probe5.c
 * under IDO 5.3 cfe -O1 -g -mips1 (non-leaf function):
 *   if/else:    then-exit is the skip-else UJP, bound to the JOIN label,
 *               which lands ON the trailing "b .+1" artifact.
 *   if+return:  the return\047s UJP replaces the skip branch 1-for-1 and is
 *               bound to the EPILOGUE label; the fallthrough tail still ends
 *               with the implicit end-of-body "b .+1" to the return label.
 * Identical instruction count, identical dispatch (bnez), only the branch
 * displacement at +0x1dc changes: 0x5C (join) -> 0x5E (epilogue). */
extern u16 D_800DFD64;
extern s32 D_801026BC;
extern u8 D_800E2838[];
extern u8 D_800E2828[];
void InitPlayScreen(void);
void func_8007F3D4();
void func_8006F52C(void) {
    if (D_800DFD5C == 0) {
        if (D_800DFD64 != D_800E44A8) {
            D_800E170C = 0xA;
            D_800DFD60 = 1;
            D_800DFD64 = D_800E44A8;
            while (D_800DF710 > D_800DF714) {
                func_8002A140();
            }
            if (D_800E44A8 == 3) {
                func_8006EAD8(0x18000, 0xE000);
            } else if (D_8015D980 == 2) {
                func_8006EAD8(0x3E000, 0x24000);
            } else {
                func_8006EAD8(0x1C000, 0xE000);
            }
            D_800F22C0 = D_800F22C4;
            InitPlayScreen();
            D_801026BC = D_800F22C0;
            func_8006EE6C();
            D_800DFDA0 = D_800E4498;
            D_800E170C = 0xA;
            D_800DFD60 = 0;
        } else if (D_800E4498 != D_800DFDA0) {
            D_800E170C = 0xA;
            D_800DFD60 = 1;
            D_800F22C0 = D_801026BC;
            func_8006EE6C();
            D_800DFDA0 = D_800E4498;
            D_800E170C = 0xA;
            D_800DFD60 = 0;
        }
        return;
    }
    D_800E170C = 0xA;
    D_800DFD60 = 1;
    while (D_800DF710 > D_800DF714) {
        func_8002A140();
    }
    if (D_800E44A8 == 3) {
        func_8006EAD8(0x18000, 0xE000);
    } else if (D_8015D980 == 2) {
        func_8006EAD8(0x3E000, 0x24000);
    } else {
        func_8006EAD8(0x1C000, 0xE000);
    }
    D_800DFD64 = D_800E44A8;
    D_800F22C0 = D_800F22C4;
    InitPlayScreen();
    if (D_8015D980 == 2) {
        func_8007F3D4(D_800E2838);
    } else {
        func_8007F3D4(D_800E2828);
    }
    D_801026BC = D_800F22C0;
    func_8006EE6C();
    D_800DFDA0 = D_800E4498;
    D_800E170C = 0xA;
    D_800DFD5C = 0;
    D_800DFD60 = 0;
}

extern u8 *D_801028CC;

void capturePreviousFramebuffer(void) {
    s32 i;
    u16 *dst;
    u16 *src;

    dst = D_800DFF00;
    src = *(u16 **)(D_801028CC + 0x1910);
    for (i = 0; i < 0x12C00; i++) {
        *dst++ = *src++;
    }
}

void func_8006F91C(void) {
    s32 i;
    u16 *p;

    p = D_800DFF00;
    for (i = 0; i < 0x12C00; i++) {
        *p = 0;
        p++;
    }
}

void func_8006F97C(void) {
    s32 y;
    s32 x;
    u16 *dst;

    dst = D_800DFF00;
    for (y = 0; y < 240; y++) {
        for (x = 0; x < 320; x++) {
            *dst = ((u16 *)D_800DFEFC)[(y >> 1) * 160 + (x >> 1)];
            dst++;
        }
    }
}

extern u8 D_800E0770[];

void func_8006FA28(s16 a0, s16 a1, s16 a2, s16 a3, u8 r, u8 g, u8 b, u8 a) {
    if (a == 0) {
        return;
    }
    { gDPPipeSync(D_800F22B4++); }
    { gSPViewport(D_800F22B4++, (u32)(u8 *)D_800E0770); }
    { gDPSetScissor(D_800F22B4++, G_SC_NON_INTERLACE, 0, 0, 320, 240); }
    { gSPClearGeometryMode(D_800F22B4++, G_SHADE | G_SHADING_SMOOTH | G_CULL_FRONT | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD); }
    { gSPTexture(D_800F22B4++, 0, 0, 0, G_TX_RENDERTILE, G_OFF); }
    if (a == 0xFF) {
        { gDPSetCycleType(D_800F22B4++, G_CYC_FILL); }
        { gDPSetRenderMode(D_800F22B4++, G_RM_NOOP, G_RM_NOOP2); }
    } else {
        { gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE); }
        { gDPSetRenderMode(D_800F22B4++, G_RM_CLD_SURF, G_RM_CLD_SURF2); }
        { gDPSetCombineMode(D_800F22B4++, G_CC_PRIMITIVE, G_CC_PRIMITIVE); }
        { Gfx *gp = D_800F22B4++; gp->words.w0 = 0xFA000000;
          gp->words.w1 = (((u32)r & 0xFF) << 24) | (((u32)g & 0xFF) << 16) | (((u32)b & 0xFF) << 8) | ((u32)a & 0xFF); }
    }
    { gDPSetFillColor(D_800F22B4++,
        ((((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1) << 16) | (((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1)); }
    { Gfx *gp = D_800F22B4++;
      gp->words.w0 = ((a2 & 0x3FF) << 14) | 0xF6000000 | ((a3 & 0x3FF) << 2);
      gp->words.w1 = ((a0 & 0x3FF) << 14) | ((a1 & 0x3FF) << 2); }
    { gDPPipeSync(D_800F22B4++); }
    { gDPSetCombineMode(D_800F22B4++, G_CC_SHADE, G_CC_SHADE); }
    if (a == 0xFF) {
        { gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE); }
    }
}



void func_8006FE64(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    {
        gDPPipeSync(
            D_800F22B4++
        );
    }
    {
        gDPSetCycleType(
            D_800F22B4++, G_CYC_FILL
        );
    }
    {
        gDPSetRenderMode(
            D_800F22B4++, G_RM_NOOP, G_RM_NOOP2
        );
    }
    {
        gDPSetColorImage(
            D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical((void *)0x80000400)
        );
    }
    {
        gDPSetFillColor(
            D_800F22B4++, 0xFFFCFFFC
        );
    }
    {
        Gfx *g = D_800F22B4++;
        g->words.w0 = (((arg2 & 0x3FF) << 14) | 0xF6000000) | ((arg3 & 0x3FF) << 2);
        g->words.w1 = ((arg0 & 0x3FF) << 14) | ((arg1 & 0x3FF) << 2);
    }
    {
        gDPPipeSync(
            D_800F22B4++
        );
    }
    {
        gDPSetColorImage(
            D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(*(void **)((u8 *) D_801028C8 + 0x1910))
        );
    }
    {
        gDPPipeSync(
            D_800F22B4++
        );
    }
    {
        gDPSetCycleType(
            D_800F22B4++, G_CYC_1CYCLE
        );
    }
}

extern s32 D_800DF728;

void func_800700E8(void) {
    D_800DF728 = 1;
}

void func_80070104(s32 arg0) {
}

typedef struct {
    u8 pad[0x24];
    s32 unk24;
} UnkStruct33BC;

extern s32 D_800DFD44;
extern u16 D_800DFD88;
extern u8 D_800E9468[];
extern s8 D_800EDA98[];
extern s16 D_80113482;
extern s16 D_8013D260;
extern s16 D_8013FAC0;
extern s16 D_8013FAC2;
extern s16 D_8013FAC4;
extern s16 D_8013FAC6;
extern s16 D_8013FAC8;
extern s16 D_8013FACA;
extern s16 D_8013FACC;
extern s16 D_8013FACE;
extern s32 leomecha_bss_0004;

void updateAndBuildFrame(s32 arg0, s32 arg1) {
    s32 i;

    processBufferedControllerSamples();
    func_80081E90(0x10);
    D_801028CC = D_801028C8;
    D_801028C8 = arg1;
    D_801028D4 = arg0;
    beginGraphicsFrame(arg1, D_801028D4);
    func_8003E724();
    if ((leomecha_bss_0004 != 0) && (D_800E11F8 == 0) && (D_800DF770 != 0)) {
        D_800E11F8 = 1;
        D_800E1208 = 0;
        D_800E120C = 0;
    }
    if (D_800E11F8 != 0) {
        func_8006EC00();
        func_8005C410();
        return;
    }
    if (D_800DFD40 != 0) {
        if (D_800DFD44 != 0) {
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800DFD44 = 0;
        }
        func_8006EC00();
        func_80064EBC();
        return;
    }
    if (D_800E1646 == 0) {
        func_8006EC00();
        func_800685FC();
        return;
    }
    if (D_800DFE8C != 0) {
        D_800DFE8C = 0;
        D_800E121C = -1;
        D_8015D980 = 1;
        D_800E0B10 = 0;
        D_800DFDFC = 1;
        D_800E44A8 = 3;
        D_800E44AC = 1;
        D_800E4498 = 0;
        D_800E449C = 0;
        D_800E44A0 = 0;
        D_80113320 = D_800E07CC[D_800E0B10];
        D_80113323 = 0;
        D_80113328 = D_800EDA98;
        D_80113322 = 4;
        D_801125C6 = 1;
        func_800CC6E0();
        D_80112D18 = 0;
    }
    if (D_800E121C >= 0) {
        func_8006EC00();
        func_8004C7E8();
        return;
    }
    if (D_8013FAD0 != 0) {
        if (D_800E1228 < 0) {
            D_800E1228 = 0;
            D_800E122A = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
        }
        func_8006EC00();
        updateAndDrawPauseMenu();
        if (D_800E1228 < 0) {
            D_8013FAD0 = 0;
        }
        return;
    }
    if (D_8013FAD4 != 0) {
        D_80115862 = !D_801125FA;
        if (D_800E44A8 == 0xC) {
            D_800E121C = D_800E0754[0];
            D_800E1208 = 0;
            D_800E120C = 0;
            return;
        }
        if ((D_800E44A8 == 0xA) || ((D_800E44A8 == 3) && (D_80113323 != 0))) {
            D_800E1646 = 0;
            D_800E1650 = 0;
            D_800E121C = D_800E0754[0];
            if (D_80102664 != 0) {
                D_800E1220 = D_800E0754[D_800E0754[0] + 1];
            }
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E0768 = 0;
            return;
        }
        if ((D_800E44A8 == 6) || (D_8015D980 == 2)) {
            D_801125F6 = 0;
            D_8011585E = 0;
            if ((D_801125FA != 0) && (D_80115862 == 0)) {
                D_8011585E = 1;
            }
            if ((D_80115862 != 0) && (D_801125FA == 0)) {
                D_801125F6 = 1;
            }
        }
        if (((D_800E44A8 != 2) && ((D_801125FA != 0) || (D_8013FAD8 == 0))) || ((D_800E44A8 == 6) && (D_801125F6 == D_8011585E)) || ((D_800E44A8 == 4) && (D_80113482 != 0))) {
            D_8013FAD4 = 0;
            D_8013FAD2 = 1;
            D_8013FAC0 = 0;
            D_8013FAC4 = 0;
            D_8013FAC8 = 0;
            D_8013FACC = 0;
            D_8013FAC2 = 0;
            D_8013FAC6 = 0;
            D_8013FACA = 0;
            D_8013FACE = 0;
        } else {
            switch (D_8013FAD4) {
            case 1:
                if (D_8015D980 == 2) {
                    D_800DFDFC = 1;
                }
                if (D_800E44A0 < func_80089D60() - 1) {
                    D_800E44A0 += 1;
                    i = D_800E4498;
                    D_800E4498 = 0;
                    func_800660B8(0);
                    D_800E44A0 -= 1;
                    D_800E4498 = i;
                    D_800E449C = 0;
                }
                if ((D_8015D980 == 1) || (D_800E44A8 == 6)) {
                    D_800E1228 = 0;
                    D_800E1208 = 0;
                    D_800E120C = 0;
                    D_800E122A = -1;
                    if ((D_800E44A8 == 5) && (func_80089C40() == D_800E44A0 + 1)) {
                        D_800E122A = -3;
                    }
                    if ((D_800E44A8 == 5) && (func_80089D04() == D_800E44A0 + 1)) {
                        D_800E1242 = 0;
                    } else {
                        D_800E1242 = 1;
                    }
                }
                D_8013FAD4 = 2;
            case 2:
                if ((D_800E44A8 == 3) || (D_800E44A8 == 2)) {
                    D_800E1228 = -1;
                }
                if (D_800E1228 >= 0) {
                    if (D_800E122A == -1) {
                        if (func_80089D60() != D_800E44A0 + 1) {
                            func_8006EC00();
                            func_8005907C();
                            if ((D_800E1228 < 0) && (D_800E44A8 != 6)) {
                                if (D_800E121C < 0) {
                                    D_800E088C = 0;
                                    D_800E449C = 0;
                                    D_800E4498 = 0;
                                    D_800E44A0 += 1;
                                    D_800E4480 = 0;
                                    D_800E4478 = 0;
                                    D_801125C6 = 1;
                                    func_800CC6E0();
                                }
                                D_801125FA = 0;
                                D_80115862 = 0;
                                D_801125F6 = 0;
                                D_8011585E = 0;
                                D_8013FAD4 = 0;
                                D_8013FAD2 = 0;
                                D_8013FAD0 = 0;
                                D_8013FAC0 = 0;
                                D_8013FAC4 = 0;
                                D_8013FAC8 = 0;
                                D_8013FACC = 0;
                                D_8013FAC2 = 0;
                                D_8013FAC6 = 0;
                                D_8013FACA = 0;
                                D_8013FACE = 0;
                            }
                            if (D_800E1228 < 0) {
                                return;
                            }
                        } else {
                            func_80057128();
                        }
                    } else {
                        func_8006EC00();
                        func_8005907C();
                        if (D_800E1228 < 0) {
                            D_800E122A = -1;
                            D_800E1228 = 0;
                            D_800E1208 = 0;
                            D_800E120C = 0;
                        }
                    }
                    if (D_800E1228 >= 0) {
                        return;
                    }
                }
                D_8013FAD4 = 3;
            case 3:
                switch (D_800E44A8) {
                case 2:
                    if (D_800E122A < 0) {
                        D_800E122A = 0;
                        D_800E1208 = 0;
                        D_800E120C = 0;
                    }
                    func_8006EC00();
                    func_8004FBF8();
                    if (D_800E122A >= 0) {
                        return;
                    }
                    break;
                case 4:
                    if (D_801125FA != 0) {
                        if (D_800E1228 < 0) {
                            D_800E1228 = 0;
                            D_800E1208 = 0;
                            D_800E120C = 0;
                        }
                        func_8006EC00();
                        func_80058100();
                        if (D_800E1228 >= 0) {
                            return;
                        }
                    }
                    break;
                case 3:
                    D_800E0754[0] = 0;
                    break;
                }
            }
            D_8013FAD4 = 0;
            D_8013FAD2 = 0;
            D_8013FAD0 = 0;
            D_8013FAC0 = 0;
            D_8013FAC4 = 0;
            D_8013FAC8 = 0;
            D_8013FACC = 0;
            D_8013FAC2 = 0;
            D_8013FAC6 = 0;
            D_8013FACA = 0;
            D_8013FACE = 0;
            D_800E449C = 0;
            D_800E4498 = 0;
            D_800E44A0 = 0;
            D_800E121C = D_800E0754[0];
            D_800E1220 = -1;
            D_800E1222 = -1;
            D_800E1224 = -1;
            D_800E1208 = 0;
            D_800E120C = 0;
            return;
        }
    }
    if (D_8013FAD2 != 0) {
        D_80115862 = !D_801125FA;
        if (D_800E44A8 == 0xC) {
            D_800E121C = D_800E0754[0];
            D_800E1208 = 0;
            D_800E120C = 0;
            return;
        }
        if ((D_800E44A8 == 0xA) || ((D_800E44A8 == 3) && (D_80113323 != 0))) {
            D_800E1646 = 0;
            D_800E1650 = 0;
            D_800E121C = D_800E0754[0];
            if (D_80102664 != 0) {
                D_800E1220 = D_800E0754[D_800E0754[0] + 1];
            }
            D_800E1208 = 0;
            D_800E120C = 0;
            D_800E0768 = 1;
            return;
        }
        if (D_8013FAD2 == 1) {
            if (D_8015D980 == 2) {
                D_800DFDFC = 1;
            }
            D_800E088C += 1;
            D_800E1228 = 0;
            D_800E1208 = 0;
            D_800E120C = 0;
            D_8013FAD2 = 2;
            D_801125F6 = 0;
            D_8011585E = 0;
            if ((D_801125FA != 0) && (D_80115862 == 0)) {
                D_8011585E = 1;
            }
            if ((D_80115862 != 0) && (D_801125FA == 0)) {
                D_801125F6 = 1;
            }
            if (D_8015D980 == 2) {
                if (D_801125F6 != 0) {
                    D_800E08AC += 1;
                }
                if (D_8011585E != 0) {
                    D_800E08B0 += 1;
                }
            }
            if ((D_8015D980 == 1) || (D_800E44A8 == 6)) {
                if (D_800E44A8 == 6) {
                    if ((D_801125FA == 0) && (D_80115862 != 0)) {
                        D_800E4498 += 1;
                        D_800E449C = D_800E4498;
                        func_800660B8(0);
                        D_800E4498 -= 1;
                    } else {
                        D_800E449C = D_800E4498;
                    }
                } else if (D_801125FA == 0) {
                    D_800E4498 += 1;
                    func_800660B8(0);
                    D_800E4498 -= 1;
                }
            }
            if ((D_8015D980 == 2) && (D_800E44A8 != 6)) {
                if ((D_800E08AC < D_800E08A8) && (D_800E08B0 < D_800E08A8)) {
                    if (D_801125F6 == D_8011585E) {
                        D_8013FAD2 = 4;
                    } else {
                        D_8013FAD2 = 0x64;
                    }
                } else if (D_801125F6 == D_8011585E) {
                    D_8013FAD2 = 4;
                } else {
                    D_800E08AC = 0;
                    D_800E08B0 = 0;
                    D_800E0B18 += 1;
                    if (D_800E0B18 >= D_800E0B0C) {
                        D_800E0B18 = 0;
                        D_800E4498 += 1;
                    }
                    if (D_801125F6 != 0) {
                        D_800E07EC[D_800E0B10]++;
                        D_800E080C[D_800E0B14]++;
                        if (D_801026A8 == D_800E0B10) {
                            D_801026AC = D_801026AC + 1;
                            if (D_801026AC > D_800E082C[D_800E0B10]) D_800E082C[D_800E0B10] = D_801026AC;
                        } else {
                            D_801026AC = 1;
                            if (D_801026AC > D_800E082C[D_800E0B10]) D_800E082C[D_800E0B10] = D_801026AC;
                        }
                        D_801026A8 = D_800E0B10;
                    }
                    if (D_8011585E != 0) {
                        D_800E07EC[D_800E0B14]++;
                        D_800E080C[D_800E0B10]++;
                        if (D_801026A8 == D_800E0B14) {
                            D_801026AC = D_801026AC + 1;
                            if (D_801026AC > D_800E082C[D_800E0B14]) D_800E082C[D_800E0B14] = D_801026AC;
                        } else {
                            D_801026AC = 1;
                            if (D_801026AC > D_800E082C[D_800E0B14]) D_800E082C[D_800E0B14] = D_801026AC;
                        }
                        D_801026A8 = D_800E0B14;
                    }
                }
            }
        }
        if ((D_800E44A8 == 6) && (D_801125F6 == D_8011585E)) {
            func_8006EC00();
            func_80050BFC();
            if (D_800E1228 < 0) {
                D_800E4480 = 0;
                D_800E4478 = 0;
                if (D_8015D980 == 1) {
                    D_801125C6 = 1;
                    func_800CC6E0();
                }
                D_8013FAD2 = 0;
            }
        } else if ((D_8015D980 == 1) || (D_800E44A8 == 6)) {
            if (D_801125FA != 0) {
                func_8006EC00();
                func_80058100();
            } else if ((D_8013D260 != 0) || (D_800E44A8 == 6)) {
                func_8006EC00();
                func_8005907C();
            } else {
                D_800E1228 = -1;
                D_800E1208 = 0;
                D_800E120C = 0;
                func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, 0xFF);
            }
            if ((D_800E1228 < 0) && (D_800E121C < 0)) {
                D_800E076C = 0;
                D_800E4480 = 0;
                D_800E4478 = 0;
                if (D_800E44A8 != 6) {
                    D_801125C6 = 1;
                    func_800CC6E0();
                }
                D_801125FA = 0;
                D_80115862 = 0;
                D_801125F6 = 0;
                D_8011585E = 0;
                D_8013FAD4 = 0;
                D_8013FAD2 = 0;
                D_8013FAD0 = 0;
                D_8013FAC0 = 0;
                D_8013FAC4 = 0;
                D_8013FAC8 = 0;
                D_8013FACC = 0;
                D_8013FAC2 = 0;
                D_8013FAC6 = 0;
                D_8013FACA = 0;
                D_8013FACE = 0;
            }
        } else if (D_8013FAD2 == 2) {
            func_8006EC00();
            func_8005AFE8();
            if ((D_800E1228 < 0) && (D_800E121C < 0)) {
                D_800E1228 = 0;
                D_800E1208 = 0;
                D_800E120C = 0;
                D_800E122A = 0;
                D_8013FAD2 = 3;
            }
        } else if (D_8013FAD2 == 3) {
            func_8006EC00();
            func_80052F68();
            if ((D_800E1228 < 0) && (D_800E121C < 0)) {
                D_800E1228 = 0;
                D_800E1208 = 0;
                D_800E120C = 0;
                D_8013FAD2 = 4;
            }
        } else if (D_8013FAD2 == 4) {
            func_8006EC00();
            func_80050BFC();
            if (D_800E1228 < 0) {
                D_800E4480 = 0;
                D_800E4478 = 0;
                if (D_8015D980 == 1) {
                    D_801125C6 = 1;
                    func_800CC6E0();
                }
                D_8013FAD2 = 0;
            }
        } else if (D_8013FAD2 == 0x64) {
            func_8006EC00();
            func_8005AFE8();
            if ((D_800E1228 < 0) && (D_800E121C < 0)) {
                D_800E1208 = 0;
                D_800E120C = 0;
                D_800E122A = 0;
                D_8013FAD2 = 0x65;
            }
        } else if (D_8013FAD2 == 0x65) {
            func_8006EC00();
            func_8004FBF8();
            if (D_800E122A < 0) {
                D_800E4480 = 0;
                D_800E4478 = 0;
                D_801125C6 = 1;
                func_800CC6E0();
                D_8013FAD2 = 0;
            }
        }
        return;
    }
    func_8006F52C();
        if (D_800E4480 == 0) {
            D_800E4478 = 0;
        }
        if (D_8015D980 == 2) {
            func_8006FA28(0, 0, 0x9F, 0xEF,
                ((D_800E9468[0] >> 2) * (0xFF - ((s16 *)D_800DFD58)[0])) / 255 + (((s16 *)D_800DFD58)[0] >> 1),
                ((D_800E9468[1] >> 2) * (0xFF - ((s16 *)D_800DFD58)[0])) / 255,
                ((D_800E9468[2] >> 2) * (0xFF - ((s16 *)D_800DFD58)[0])) / 255,
                0xFF);
            func_8006FA28(0xA0, 0, 0x13F, 0xEF,
                ((D_800E9468[3] >> 2) * (0xFF - ((s16 *)D_800DFD58)[1])) / 255 + (((s16 *)D_800DFD58)[1] >> 1),
                ((D_800E9468[4] >> 2) * (0xFF - ((s16 *)D_800DFD58)[1])) / 255,
                ((D_800E9468[5] >> 2) * (0xFF - ((s16 *)D_800DFD58)[1])) / 255,
                0xFF);
            for (i = 0; i < D_80160C64; i++) {
                if (((s16 *)D_800DFD58)[0] > 0) {
                    ((s16 *)D_800DFD58)[0] -= 8;
                    if (((s16 *)D_800DFD58)[0] < 0) {
                        ((s16 *)D_800DFD58)[0] = 0;
                    }
                }
                if (((s16 *)D_800DFD58)[1] > 0) {
                    ((s16 *)D_800DFD58)[1] -= 8;
                    if (((s16 *)D_800DFD58)[1] < 0) {
                        ((s16 *)D_800DFD58)[1] = 0;
                    }
                }
            }
        } else {
            if (D_800E23BC == 0x10) {
                func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, 0xFF);
            }
            if ((D_800E23BC != 1) && (D_800E23BC != 5)) {
                func_800B7E3C();
                if (LWPlayAnimation(D_801033BC, (D_800DFD88 + D_80160C64) - ((UnkStruct33BC *)D_801033BC)->unk24, (void *)(arg0 + 0x17C0), (void *)(arg0 + 0x1800)) != 0) {
                    ((UnkStruct33BC *)D_801033BC)->unk24 = 0;
                }
                D_800DFD88 = ((UnkStruct33BC *)D_801033BC)->unk24;
            } else {
                if (LWPlayAnimation(D_801033BC, (D_800DFD88 + D_80160C64) - ((UnkStruct33BC *)D_801033BC)->unk24, 0, 0) != 0) {
                    ((UnkStruct33BC *)D_801033BC)->unk24 = 0;
                }
                D_800DFD88 = ((UnkStruct33BC *)D_801033BC)->unk24;
            }
        }
        func_800CD3B8(arg0, arg1);
        if ((D_800E44A8 == 0xA) && (D_800E4478 >= 0x709)) {
            i = D_800E4478 * 8 - 0x3840;
            if (i >= 0x100) {
                i = 0xFF;
                D_800E121C = D_800E0754[0];
                if (D_80102664 != 0) {
                    D_800E1220 = D_800E0754[D_800E0754[0] + 1];
                }
                D_800E1208 = 0;
                D_800E120C = 0;
                D_800E1646 = 0;
                D_800E1650 = 0;
            }
            func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, i);
        }
        if (D_800E4478 < 0x1E) {
            func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, (-D_800E4478 * 0xFF + 0x1DE2) / 30);
        }
}

