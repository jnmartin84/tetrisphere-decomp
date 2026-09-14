#include "common.h"

/* func_8002CDC0 -- inverts an affine 4x4.  Normalises rows 0-2 by the squared
 * length of row 0, transposes the 3x3 into arg1, then writes the inverse
 * translation and the constant 4th column.  Declared s32 because the sole
 * caller (func_80031FEC) tests the result against 0; the body never sets $v0
 * (K&R implicit int, no return statement). */
s32 func_8002CDC0(arg0, arg1)
f32 arg0[4][4];
f32 arg1[4][4];
{
    f32 *m;
    f32 *o;
    f32 d;
    f32 e;

    m = arg0[0];
    o = arg1[0];
    d = (m[2] * m[2]) + ((m[1] * m[1]) + (m[0] * m[0]));
    e = 0.0f;
    m[0] = m[0] / d;
    m[1] = m[1] / d;
    m[2] = m[2] / d;
    m[4] = m[4] / d;
    m[5] = m[5] / d;
    m[6] = m[6] / d;
    m[8] = m[8] / d;
    m[9] = m[9] / d;
    m[10] = m[10] / d;
    o[0] = m[0];
    o[4] = m[1];
    o[8] = m[2];
    o[1] = m[4];
    o[5] = m[5];
    o[9] = m[6];
    o[2] = m[8];
    o[6] = m[9];
    o[10] = m[10];
    o[12] = ((-o[0] * m[12]) - (o[4] * m[13])) - (m[14] * o[8]);
    o[13] = ((-o[1] * m[12]) - (o[5] * m[13])) - (m[14] * o[9]);
    o[14] = ((-o[2] * m[12]) - (o[6] * m[13])) - (m[14] * o[10]);
    o[3] = e;
    o[7] = e;
    o[11] = e;
    o[15] = 1.0f;
}

/*
 * Pool setup and block-entry indexing. Preserve declaration order, erased
 * arithmetic, and intentional same-line statements: they reproduce IDO 5.3
 * register allocation and spill placement. Re-run the ROM gate after formatting.
 */
extern void func_8002AF20(char *, char *);
extern void func_80025CA0();
extern s32 findMaterialLightColor();
extern s16 eqpower[];
extern char D_800EBA80[], D_800EBAA0[], D_800EBAC0[], D_800EBAE0[];
extern char D_800EBB00[], D_800EBB18[], D_800EBB38[], D_800EBB50[];
extern char D_800EBB70[], D_800EBB88[], D_800EBBA8[], D_800EBBC0[];
extern char D_800EBBE0[], D_800EBBF4[], D_800EBC14[], D_800EBC34[];
extern char D_800EBC54[], D_800EBC74[];

#define BADPTR(p) \
    (((u32)func_80025CA0 < (u32)(p) && (u32)(p) < (u32)eqpower) \
      || (u32)(p) < 0x80000400 || (u32)(p) >= 0x80400001)

typedef struct {
    /*0x00*/ s16 *indexList;
    /*0x04*/ void *geomStream;
} LWGeometryInfo;

typedef struct {
    /*0x00*/ u8 *lights0;
    /*0x04*/ u8 *lights1;
    /*0x08*/ u8 *materialLights0;
    /*0x0C*/ u8 *materialLights1;
    /*0x10*/ u8 *lightInfo;
    /*0x14*/ u8 *objectInfo;
    /*0x18*/ LWGeometryInfo *geometryInfo;
    /*0x1C*/ void *animStream;
    /*0x20*/ s32 geomStreamCount;
    /*0x24*/ s32 unk24;
    /*0x28*/ f32 unk28;
    /*0x2C*/ f32 unk2C;
    /*0x30*/ f32 unk30;
    /*0x34*/ f32 unk34;
    /*0x38*/ u8 unk38;
    /*0x39*/ u8 unk39;
    /*0x3A*/ u8 unk3A;
    /*0x3B*/ u8 pad3B;
    /*0x3C*/ u8 unk3C;
    /*0x3D*/ u8 unk3D;
    /*0x3E*/ u8 pad3E[2];
    /*0x40*/ f32 unk40;
    /*0x44*/ f32 unk44;
    /*0x48*/ u8 unk48;
    /*0x49*/ u8 unk49;
    /*0x4A*/ u8 unk4A;
    /*0x4B*/ u8 pad4B[0x270 - 0x4B];
    /*0x270*/ f32 unk270;
} LWInfo;

typedef struct {
    /*0x00*/ s32 pad0;
    /*0x04*/ s32 lightBlockOffset;
    /*0x08*/ s32 objectBlockOffset;
    /*0x0C*/ s32 padC;
    /*0x10*/ s32 streamSize;
} LWAnimStreamHeader;

typedef struct {
    /*0x00*/ s32 pad0;
    /*0x04*/ s32 unk4;
    /*0x08*/ s32 pad8[3];
    /*0x14*/ s32 streamSize;
} LWGeomStreamHeader;

typedef struct {
    /*0x00*/ s32 count;
    /*0x04*/ s32 off[1];
} Sub;

typedef struct {
    /*0x00*/ u8 unk0;
    /*0x01*/ u8 unk1;
    /*0x02*/ u8 unk2;
    /*0x03*/ u8 pad3;
    /*0x04*/ u8 unk4;
} Entry;

u8 *LWAllocateMemory(memory, animStream, geomStreams, geomStreamCount, allocatedSize)
s32 memory;
s32 animStream;
void **geomStreams;
s32 geomStreamCount;
s32 *allocatedSize;
{
    /* Local homes are part of the matching frame layout. */
    LWInfo *lwInfo;
    s32 lightCount;
    s32 objectCount;
    u8 *blk;
    s32 base;
    s32 heapSize;
    s32 blkSize;
    Sub *sub;
    s32 bcount;
    s32 *entryOffsets;
    s32 idx;
    s32 i;
    s32 j;
    s32 cursor;
    s32 header;
    Entry *e;
    u8 c0;
    u8 c1;
    u8 c2;
    s32 v;
    u8 *src;
    void **entryCursor;

    blk = (u8 *)(((LWAnimStreamHeader *)animStream)->lightBlockOffset + animStream);
    lightCount = *(s32 *)blk;
    blk = (u8 *)(((LWAnimStreamHeader *)animStream)->objectBlockOffset + animStream);
    objectCount = *(s32 *)blk;
    header = ((LWAnimStreamHeader *)animStream)->streamSize;
    if (memory >= animStream && memory < animStream + header) {
        func_8002AF20(D_800EBA80, D_800EBAA0);
    }

    i = 0;
    if (geomStreamCount > 0) {
        do {
            /* Dead stores mint the size and address spill items in this order. */
            idx = lightCount * 16;
            j = (u32)func_80025CA0;
            blk = (u8 *)geomStreams[i];
            blkSize = ((LWGeomStreamHeader *)blk)->streamSize;
            if (memory >= (s32)blk) {
                if (memory < (s32)blk + blkSize) {
                    func_8002AF20(D_800EBAC0, D_800EBAE0);
                }
            }
            blk = (u8 *)geomStreams[i];
            if ((s32)blk % 16) {
                func_8002AF20(D_800EBB00, D_800EBB18);
            }
            if (BADPTR(geomStreams[i])) {
                func_8002AF20(D_800EBB38, D_800EBB50);
            }
            i++;
        } while (i != geomStreamCount);
        memory = memory + i * 0;
    }
    i = 0;

    if (memory % 16) {
        func_8002AF20(D_800EBB70, D_800EBB88);
    }
    if (animStream % 16) {
        func_8002AF20(D_800EBBA8, D_800EBBC0);
    }
    if (BADPTR(memory)) {
        func_8002AF20(D_800EBBE0, D_800EBBF4);
    }
    if (BADPTR(animStream)) {
        func_8002AF20(D_800EBC14, D_800EBC34);
    }

    base = memory;
    lwInfo = (LWInfo *)memory;
    heapSize = lightCount * 16;
    /* Keep a zero-valued 32-bit identity through the size-copy passes. */
    idx = animStream;
    idx *= 0;
    memory += 0x278;
    while ((memory - base) % 16) memory++;
    lwInfo->lights0 = (u8 *)memory;
    memory += heapSize;
    while ((memory - base) % 16) memory++;
    lwInfo->lights1 = (u8 *)memory;
    memory += heapSize;
    while ((memory - base) % 16) memory++;
    lwInfo->lightInfo = (u8 *)memory; memory += lightCount * 0x34;
    while ((memory - base) % 16) memory++;
    lwInfo->objectInfo = (u8 *)memory;
    memory += objectCount * 0x120;
    while ((memory - base) % 16) memory++;
    lwInfo->geometryInfo = (LWGeometryInfo *)memory;
    memory += geomStreamCount * 8;

    memory = memory;
    i = 0;
    if (geomStreamCount > 0) {
        cursor = (s32)geomStreams;
        do {
            header = *(s32 *)cursor;
            sub = (Sub *)(((LWGeomStreamHeader *)header)->unk4 + header);
            bcount = sub->count + (((u32)header & 1) * 0) + (((u32)header & 2) * 0) + (((u32)header & 4) * 0) + (((u32)header & 8) * 0);
            while ((memory - base) % 16) memory++;
            lwInfo->geometryInfo[i].indexList = (s16 *)memory;
            i++;
            memory += bcount * 2;
            cursor += 4;
        } while (i != geomStreamCount);
        memory = memory + i * 0;
        i = 0;
    }
    memory = memory;
    while ((memory - base) % 16) memory++;
    lwInfo->materialLights0 = (u8 *)memory;
    memory = memory;

    _bzero(lwInfo->lights0, heapSize | idx);
    _bzero(lwInfo->lights1, heapSize | idx);
    _bzero(lwInfo->lightInfo, lightCount * 0x34);
    _bzero(lwInfo->objectInfo, objectCount * 0x120);

    lwInfo->unk3D = 0;
    /* End these cold lifetimes after the clear calls, before the entry loop. */
    do { j = objectCount * 0x120; blkSize = objectCount; } while (0);
    memory += j * 0 + blkSize * 0;
    idx = 0;
    j = 0;
    if (geomStreamCount > 0) {
        entryCursor = geomStreams;
        do {
            blk = (u8 *)*entryCursor;
            sub = (Sub *)(((LWGeomStreamHeader *)blk)->unk4 + (s32)blk);
            bcount = sub->count;
            entryOffsets = sub->off;
            if (bcount > 0) {
                do {
                    e = (Entry *)(*entryOffsets + (s32)sub);
                    cursor = e->unk0;
                    c1 = e->unk1;
                    c2 = e->unk2;
                    e = (Entry *)((u8 *)e + 4);
                    if (e->unk0 & 8) {
                        v = findMaterialLightColor(lwInfo, idx, cursor & 0xFF, c1 & 0xFF, (s32)c2);
                        if (v == -1) {
                            memory += heapSize + (((u32)cursor & 1) * 0);
                            lwInfo->materialLights0[idx * 16 + 0] = cursor;
                            lwInfo->materialLights0[idx * 16 + 1 + (((u32)cursor & 2) * 0)] = c1;
                            lwInfo->materialLights0[idx * 16 + 2 + (((u32)cursor & 4) * 0)] = c2;
                            v = idx + (((u32)cursor & 8) * 0);
                            idx += 1 + (((u32)cursor & 16) * 0);
                        }
                        *(s16 *)((u8 *)lwInfo->geometryInfo[j].indexList + i * 2) = v + (((u32)cursor & 32) * 0);
                    }
                    i++;
                    entryOffsets++;
                } while (i != bcount);
                i = 0;
            }
            /* Same-line updates retain the counter store in the delay slot. */
            j++; entryCursor++;
        } while (j != geomStreamCount);
        j = 0;
    }

    {
        blk = (u8 *)memory;
        src = lwInfo->materialLights0;
        lwInfo->materialLights1 = (u8 *)memory;
        if ((s32)((u8 *)memory - lwInfo->materialLights0) > 0) {
            do {
                *blk++ = *src++;
                j++;
            } while (j < (s32)(lwInfo->materialLights1 - lwInfo->materialLights0));
        }
    }

    lwInfo->unk48 = 1;
    lwInfo->unk49 = 1;
    lwInfo->unk4A = 1;
    lwInfo->unk3C = 0;
    lwInfo->unk24 = 0;
    lwInfo->unk3A = 0;
    lwInfo->unk39 = 0;
    memory = (s32)((u8 *)memory + (s32)lwInfo->materialLights1) - (s32)lwInfo->materialLights0;
    lwInfo->animStream = animStream;
    lwInfo->geomStreamCount = geomStreamCount;
    if (geomStreamCount > 0) {
        do {
            lwInfo->geometryInfo[i].geomStream = geomStreams[i];
            i++;
        } while (i != geomStreamCount);
    }

    lwInfo->unk3D = 0;
    lwInfo->unk38 = 2;
    lwInfo->unk30 = 1.0f;
    lwInfo->unk270 = 40.0f;
    lwInfo->unk28 = 0.0f;
    lwInfo->unk2C = 0.0f;
    lwInfo->unk34 = 0.0f;
    lwInfo->unk40 = 16.0f;
    lwInfo->unk44 = 16384.0f;

    if (BADPTR(memory)) {
        func_8002AF20(D_800EBC54, D_800EBC74);
    }
    *allocatedSize = memory - base;
    return (u8 *)lwInfo;
}

/* LWPlayAnimation. Ten LWInfo pointer-validity asserts, then the per-frame
 * advance and the sub-builder chain. The bounds are (u32)&func_80025CA0 and
 * (u32)eqpower -- whatever the original names were, those two symbols resolve
 * to the addresses the ROM's relocations carry. */
extern void func_8002AF20(char *, char *);
extern void func_8002F55C();
extern void func_8003031C();
extern void buildAnimationLightDirections();
extern void buildAnimationObjectMatrices();
extern void updateAnimationObjectAlpha();
extern void func_8002DEA8();
extern void func_80031A98();
extern void func_80025CA0();
extern s16 eqpower[];
extern f64 D_800EBEE8;
extern char D_800EBC94[];
extern char D_800EBCAC[];
extern char D_800EBCC8[];
extern char D_800EBCE4[];
extern char D_800EBD00[];
extern char D_800EBD20[];
extern char D_800EBD3C[];
extern char D_800EBD58[];
extern char D_800EBD74[];
extern char D_800EBD90[];
extern char D_800EBDAC[];
extern char D_800EBDC8[];
extern char D_800EBDE4[];
extern char D_800EBE00[];
extern char D_800EBE1C[];
extern char D_800EBE38[];
extern char D_800EBE54[];
extern char D_800EBE78[];
extern char D_800EBE94[];
extern char D_800EBEB8[];

typedef struct { s32 indexList; u32 geomStream; } LWGeometryInfoCheckView;

#define BADPTR(p) \
    (((u32)func_80025CA0 < (u32)(p) && (u32)(p) < (u32)eqpower) \
      || (u32)(p) < 0x80000400 || (u32)(p) >= 0x80400001)

s32 LWPlayAnimation(arg0, arg1, arg2, arg3)
u8 *arg0;
s32 arg1;
void *arg2;
void *arg3;
{
    s32 i;

    if (BADPTR(arg0)) {
        func_8002AF20(D_800EBC94, D_800EBCAC);
    }
    if (BADPTR(*(u32 *)(arg0 + 0x18))) {
        func_8002AF20(D_800EBCC8, D_800EBCE4);
    }
    for (i = 0; i < *(s32 *)(arg0 + 0x20); i++) {
        if (BADPTR(((LWGeometryInfoCheckView *)*(u8 **)(arg0 + 0x18))[i].geomStream)) {
            func_8002AF20(D_800EBD00, D_800EBD20);
        }
    }
    if (BADPTR(*(u32 *)(arg0 + 0x1C))) {
        func_8002AF20(D_800EBD3C, D_800EBD58);
    }
    if (BADPTR(*(u32 *)(arg0 + 0x0))) {
        func_8002AF20(D_800EBD74, D_800EBD90);
    }
    if (BADPTR(*(u32 *)(arg0 + 0x4))) {
        func_8002AF20(D_800EBDAC, D_800EBDC8);
    }
    if (BADPTR(*(u32 *)(arg0 + 0x10))) {
        func_8002AF20(D_800EBDE4, D_800EBE00);
    }
    if (BADPTR(*(u32 *)(arg0 + 0x14))) {
        func_8002AF20(D_800EBE1C, D_800EBE38);
    }
    if (BADPTR(*(u32 *)(arg0 + 0x8))) {
        func_8002AF20(D_800EBE54, D_800EBE78);
    }
    if (BADPTR(*(u32 *)(arg0 + 0xC))) {
        func_8002AF20(D_800EBE94, D_800EBEB8);
    }
    arg0[0x3D] = arg0[0x3D] ^ 1;
    if (*(s32 *)(arg0 + 0x24) == 0 && arg1 == 0) {
        func_8002F55C(arg0);
    }
    while (arg1 > 0) {
        func_8002F55C(arg0);
        *(s32 *)(arg0 + 0x24) = *(s32 *)(arg0 + 0x24) + 1;
        arg1--;
    }
    arg0[0x39] = *(f32 *)(arg0 + 0x21C) * D_800EBEE8;
    if (arg0[0x3C] == 0) {
        func_8003031C(arg0, arg2, arg3);
        buildAnimationLightDirections(arg0);
        buildAnimationObjectMatrices(arg0);
        updateAnimationObjectAlpha(arg0);
        *(s16 *)(arg0 + 0x3E) = -2;
        arg0[0x3B] = 0;
        func_8002DEA8(arg0);
        func_80031A98(arg0, arg2);
    }
    if (*(s32 *)(arg0 + 0x24) >= *(s32 *)(*(u8 **)(arg0 + 0x1C) + 0xC)) {
        return 1;
    }
    return 0;
}

void func_8002DEA8(void *arg0) {
    u8 *p = arg0;
    if (*(u8 *)(p + 0x49) != 0) {
        if (*(u8 *)(p + 0x48) != 0) {
            *(u32 *)(p + 0x4C) = 0x4049F8;
            *(u32 *)(p + 0x50) = 0x1049F8;
        } else {
            *(u32 *)(p + 0x4C) = 0x4049D8;
            *(u32 *)(p + 0x50) = 0x1049D8;
        }
        *(u32 *)(p + 0x64) = 0x443078;
        *(u32 *)(p + 0x68) = 0x113078;
        *(u32 *)(p + 0x6C) = 0x442078;
        *(u32 *)(p + 0x70) = 0x112078;
        *(u32 *)(p + 0x54) = 0x404B50;
        *(u32 *)(p + 0x58) = 0x104B50;
        return;
    }
    *(u32 *)(p + 0x4C) = 0x4041C8;
    *(u32 *)(p + 0x50) = 0x1041C8;
    *(u32 *)(p + 0x64) = 0x443048;
    *(u32 *)(p + 0x68) = 0x113048;
    *(u32 *)(p + 0x6C) = 0x442048;
    *(u32 *)(p + 0x70) = 0x112048;
    *(u32 *)(p + 0x54) = 0x404340;
    *(u32 *)(p + 0x58) = 0x104340;
}

s32 findMaterialLightColor(arg0, arg1, arg2, arg3, arg4)
u8 *arg0;
s32 arg1;
u8 arg2;
u8 arg3;
u8 arg4;
{
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (arg2 == ((u8 **)(arg0 + 8))[arg0[0x3D]][i * 0x10 + 0] &&
            arg3 == ((u8 **)(arg0 + 8))[arg0[0x3D]][i * 0x10 + 1] &&
            arg4 == ((u8 **)(arg0 + 8))[arg0[0x3D]][i * 0x10 + 2]) {
            return i;
        }
    }
    return -1;
}

typedef struct {
    /* 0x000 */ u8 pad0[0x80];
    /* 0x080 */ u8 u80;
    /* 0x081 */ u8 pad81[0xCC - 0x81];
    /* 0x0CC */ f32 fCC;
    /* 0x0D0 */ u8 padD0[0x120 - 0xD0];
} V120;

void updateAnimationObjectAlpha(arg0)
u8 *arg0;
{
    s32 n;
    s32 i;
    s32 c;

    n = *(s32 *)(*(u8 **)(arg0 + 0x1C) + *(s32 *)(*(u8 **)(arg0 + 0x1C) + 8));
    for (i = 0; i < n; i++) {
        if (((V120 *)*(u8 **)(arg0 + 0x14))[i].fCC < *(f32 *)(arg0 + 0x28)) {
            c = (1.0 - *(f32 *)(arg0 + 0x28)) * 255.0 + 0.5;
        } else {
            c = (1.0 - ((V120 *)*(u8 **)(arg0 + 0x14))[i].fCC) * 255.0 + 0.5;
        }
        if (c > 255) {
            c = 255;
        }
        if (c < 0) {
            c = 0;
        }
        ((V120 *)*(u8 **)(arg0 + 0x14))[i].u80 = c;
    }
}

s32 func_8002E3B0(s32 arg0) {
    s32 count;
    count = 0;
    if (arg0 & 1) count = 1;
    if (arg0 & 2) count++;
    if (arg0 & 4) count++;
    if (arg0 & 8) count++;
    if (arg0 & 0x10) count++;
    if (arg0 & 0x20) count++;
    if (arg0 & 0x40) count++;
    if (arg0 & 0x80) count++;
    if (arg0 & 0x100) count++;
    return count;
}

void func_8002E42C(u8 *arg0, f32 *arg1) {
    s32 flags = *(s32 *)arg1;
    if (*(s16 *)((u8 *)arg1 + 6) == 0) {
        arg1 += 2;
        if (flags & 0x1)   { *(f32 *)(arg0 + 0x220) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x248) = arg1[-2]; }
        if (flags & 0x2)   { *(f32 *)(arg0 + 0x224) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x24C) = arg1[-2]; }
        if (flags & 0x4)   { *(f32 *)(arg0 + 0x228) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x250) = arg1[-2]; }
        if (flags & 0x8)   { *(f32 *)(arg0 + 0x22C) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x254) = arg1[-2]; }
        if (flags & 0x10)  { *(f32 *)(arg0 + 0x230) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x258) = arg1[-2]; }
        if (flags & 0x20)  { *(f32 *)(arg0 + 0x234) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x25C) = arg1[-2]; }
        if (flags & 0x40)  { *(f32 *)(arg0 + 0x238) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x260) = arg1[-2]; }
        if (flags & 0x80)  { *(f32 *)(arg0 + 0x23C) = arg1[0]; arg1 += 3; *(f32 *)(arg0 + 0x264) = arg1[-2]; }
        if (flags & 0x100) { *(f32 *)(arg0 + 0x240) = arg1[0]; arg1 += 1; *(f32 *)(arg0 + 0x268) = arg1[0]; }
    }
}

void func_8002E568(u8 *arg0, u8 *arg1) {
    if (*(s16*)(arg1 + 2) == 0) {
        *(f32*)(arg0 + 0x244) = *(f32*)(arg1 + 4);
        arg1 += 8;
        *(f32*)(arg0 + 0x26C) = *(f32*)arg1;
    }
}

void func_8002E598(u8 *arg0, u8 *arg1, s32 arg2) {
    if (*(s16*)(arg1 + 2) == 0) {
        *(f32*)(*(u8**)(arg0 + 0x10) + arg2 * 0x34 + 0x8) = *(f32*)(arg1 + 4);
        arg1 += 8;
        *(f32*)(*(u8**)(arg0 + 0x10) + arg2 * 0x34 + 0xC) = *(f32*)arg1;
    }
}

void func_8002E5E0(u8 *arg0, u8 *arg1, s32 arg2) {
    if (*(s16*)(arg1 + 2) == 0) {
        *(f32*)(*(u8**)(arg0 + 0x14) + arg2 * 0x120 + 0xF4) = *(f32*)(arg1 + 4);
        arg1 += 8;
        *(f32*)(*(u8**)(arg0 + 0x14) + arg2 * 0x120 + 0x11C) = *(f32*)arg1;
    }
}

typedef struct S120 {
    char pad[0xD0];
    f32 fD0, fD4, fD8, fDC, fE0, fE4, fE8, fEC, fF0;
    char pad1[4];
    f32 fF8, fFC, f100, f104, f108, f10C, f110, f114, f118;
    char pad2[4];
} S120;

#define ENT120 (((S120 *)(*(u8 **)(arg0 + 0x14)))[arg2])

void func_8002E620(u8 *arg0, f32 *arg1, s32 arg2) {
    s32 flags = *(s32 *)arg1;
    if (*(s16 *)((u8 *)arg1 + 6) == 0) {
        arg1 += 2;
        if (flags & 0x1)   { ENT120.fD0 = arg1[0]; arg1 += 3; ENT120.fF8  = arg1[-2]; }
        if (flags & 0x2)   { ENT120.fD4 = arg1[0]; arg1 += 3; ENT120.fFC  = arg1[-2]; }
        if (flags & 0x4)   { ENT120.fD8 = arg1[0]; arg1 += 3; ENT120.f100 = arg1[-2]; }
        if (flags & 0x8)   { ENT120.fDC = arg1[0]; arg1 += 3; ENT120.f104 = arg1[-2]; }
        if (flags & 0x10)  { ENT120.fE0 = arg1[0]; arg1 += 3; ENT120.f108 = arg1[-2]; }
        if (flags & 0x20)  { ENT120.fE4 = arg1[0]; arg1 += 3; ENT120.f10C = arg1[-2]; }
        if (flags & 0x40)  { ENT120.fE8 = arg1[0]; arg1 += 3; ENT120.f110 = arg1[-2]; }
        if (flags & 0x80)  { ENT120.fEC = arg1[0]; arg1 += 3; ENT120.f114 = arg1[-2]; }
        if (flags & 0x100) { ENT120.fF0 = arg1[0]; arg1 += 1; ENT120.f118 = arg1[0]; }
    }
}
#undef ENT120

typedef struct S34 {
    char pad[0x1C];
    f32 f1C, f20, f24, f28, f2C, f30;
} S34;

#define ENT (((S34 *)(*(u8 **)(arg0 + 0x10)))[arg2])

void func_8002E818(u8 *arg0, f32 *arg1, s32 arg2) {
    s32 flags = *(s32 *)arg1;
    if (*(s16 *)((u8 *)arg1 + 6) == 0) {
        arg1 += 2;
        if (flags & 0x8)  { ENT.f1C = arg1[0]; arg1 += 3; ENT.f28 = arg1[-2]; }
        if (flags & 0x10) { ENT.f20 = arg1[0]; arg1 += 3; ENT.f2C = arg1[-2]; }
        if (flags & 0x20) { ENT.f24 = arg1[0]; arg1 += 1; ENT.f30 = arg1[0]; }
    }
}
#undef ENT

void func_8002E8D8(u8 *arg0, f32 *arg1) {
    s32 flags = *(s32 *)arg1;
    if (*(s16 *)((u8 *)arg1 + 6) != 0) {
        arg1 += 2;
        if (flags & 0x1)   { *(f32 *)(arg0 + 0x1F8) += arg1[0]; arg1 += 1; }
        if (flags & 0x2)   { *(f32 *)(arg0 + 0x1FC) += arg1[0]; arg1 += 1; }
        if (flags & 0x4)   { *(f32 *)(arg0 + 0x200) += arg1[0]; arg1 += 1; }
        if (flags & 0x8)   { *(f32 *)(arg0 + 0x204) += arg1[0]; arg1 += 1; }
        if (flags & 0x10)  { *(f32 *)(arg0 + 0x208) += arg1[0]; arg1 += 1; }
        if (flags & 0x20)  { *(f32 *)(arg0 + 0x20C) += arg1[0]; arg1 += 1; }
        if (flags & 0x40)  { *(f32 *)(arg0 + 0x210) += arg1[0]; arg1 += 1; }
        if (flags & 0x80)  { *(f32 *)(arg0 + 0x214) += arg1[0]; arg1 += 1; }
        if (flags & 0x100) { *(f32 *)(arg0 + 0x218) += arg1[0]; }
    } else {
        arg1 += 2;
        if (flags & 0x1)   { *(f32 *)(arg0 + 0x1F8) += *(f32 *)(arg0 + 0x220); *(f32 *)(arg0 + 0x220) += *(f32 *)(arg0 + 0x248); arg1 += 3; *(f32 *)(arg0 + 0x248) += arg1[-1]; }
        if (flags & 0x2)   { *(f32 *)(arg0 + 0x1FC) += *(f32 *)(arg0 + 0x224); *(f32 *)(arg0 + 0x224) += *(f32 *)(arg0 + 0x24C); arg1 += 3; *(f32 *)(arg0 + 0x24C) += arg1[-1]; }
        if (flags & 0x4)   { *(f32 *)(arg0 + 0x200) += *(f32 *)(arg0 + 0x228); *(f32 *)(arg0 + 0x228) += *(f32 *)(arg0 + 0x250); arg1 += 3; *(f32 *)(arg0 + 0x250) += arg1[-1]; }
        if (flags & 0x8)   { *(f32 *)(arg0 + 0x204) += *(f32 *)(arg0 + 0x22C); *(f32 *)(arg0 + 0x22C) += *(f32 *)(arg0 + 0x254); arg1 += 3; *(f32 *)(arg0 + 0x254) += arg1[-1]; }
        if (flags & 0x10)  { *(f32 *)(arg0 + 0x208) += *(f32 *)(arg0 + 0x230); *(f32 *)(arg0 + 0x230) += *(f32 *)(arg0 + 0x258); arg1 += 3; *(f32 *)(arg0 + 0x258) += arg1[-1]; }
        if (flags & 0x20)  { *(f32 *)(arg0 + 0x20C) += *(f32 *)(arg0 + 0x234); *(f32 *)(arg0 + 0x234) += *(f32 *)(arg0 + 0x25C); arg1 += 3; *(f32 *)(arg0 + 0x25C) += arg1[-1]; }
        if (flags & 0x40)  { *(f32 *)(arg0 + 0x210) += *(f32 *)(arg0 + 0x238); *(f32 *)(arg0 + 0x238) += *(f32 *)(arg0 + 0x260); arg1 += 3; *(f32 *)(arg0 + 0x260) += arg1[-1]; }
        if (flags & 0x80)  { *(f32 *)(arg0 + 0x214) += *(f32 *)(arg0 + 0x23C); *(f32 *)(arg0 + 0x23C) += *(f32 *)(arg0 + 0x264); arg1 += 3; *(f32 *)(arg0 + 0x264) += arg1[-1]; }
        if (flags & 0x100) { *(f32 *)(arg0 + 0x218) += *(f32 *)(arg0 + 0x240); *(f32 *)(arg0 + 0x240) += *(f32 *)(arg0 + 0x268); arg1 += 2; *(f32 *)(arg0 + 0x268) += arg1[0]; }
    }
}

typedef struct { u8 pad0[4]; f32 unk4, unk8, unkC; u8 pad1[0x34 - 0x10]; } Elem2EBF4;
typedef struct { u8 pad0[0x10]; Elem2EBF4 *lightInfo; } LWInfoLightView;
typedef struct { u8 pad0[2]; s16 unk2; f32 unk4; u8 pad1[4]; f32 unkC; } Cur2EBF4;

void func_8002EBF4(LWInfoLightView *arg0, Cur2EBF4 *arg1, s32 arg2) {
    if (arg1->unk2 != 0) {
        arg1 = (Cur2EBF4 *)((u8 *)arg1 + 4);
        arg0->lightInfo[arg2].unk4 += *(f32 *)arg1;
        return;
    }
    arg0->lightInfo[arg2].unk4 += arg0->lightInfo[arg2].unk8;
    arg1 = (Cur2EBF4 *)((u8 *)arg1 + 0xC);
    arg0->lightInfo[arg2].unk8 += arg0->lightInfo[arg2].unkC;
    arg0->lightInfo[arg2].unkC += *(f32 *)arg1;
}

void func_8002ECA4(u8 *a0, f32 *a1)
{
    if (*(s16 *)((u8 *)a1 + 2)) {
        a1 += 1;
        *(f32 *)(a0 + 0x21C) += *a1;
    } else {
        *(f32 *)(a0 + 0x21C) += *(f32 *)(a0 + 0x244);
        *(f32 *)(a0 + 0x244) += *(f32 *)(a0 + 0x26C);
        a1 += 3;
        *(f32 *)(a0 + 0x26C) += a1[0];
    }
}

void func_8002ED04(void *arg0, f32 *arg1, s32 arg2) {
    if (*(s16 *)((u8 *)arg1 + 2) != 0) {
        *(f32 *)(*(u8 **)((u8 *)arg0 + 0x14) + arg2 * 0x120 + 0xCC) += *++arg1;
        return;
    }
    *(f32 *)(*(u8 **)((u8 *)arg0 + 0x14) + arg2 * 0x120 + 0xCC) += *(f32 *)(*(u8 **)((u8 *)arg0 + 0x14) + arg2 * 0x120 + 0xF4);
    *(f32 *)(*(u8 **)((u8 *)arg0 + 0x14) + arg2 * 0x120 + 0xF4) += *(f32 *)(*(u8 **)((u8 *)arg0 + 0x14) + arg2 * 0x120 + 0x11C);
    arg1 += 3;
    *(f32 *)(*(u8 **)((u8 *)arg0 + 0x14) + arg2 * 0x120 + 0x11C) += arg1[0];
}

typedef struct S120B {
    char pad[0xA8];
    f32 fA8, fAC, fB0, fB4, fB8, fBC, fC0, fC4, fC8;
    char pad1[4];
    f32 fD0, fD4, fD8, fDC, fE0, fE4, fE8, fEC, fF0;
    char pad2[4];
    f32 fF8, fFC, f100, f104, f108, f10C, f110, f114, f118;
    char pad3[4];
} S120B;

#define E120 (((S120B *)(*(u8 **)(arg0 + 0x14)))[arg2])

void func_8002EDA4(u8 *arg0, f32 *arg1, s32 arg2) {
    s32 flags = *(s32 *)arg1;
    if (*(s16 *)((u8 *)arg1 + 6) != 0) {
        arg1 += 2;
        if (flags & 0x1)     { E120.fA8 += arg1[0]; arg1 += 1; }
        if (flags & 0x2)     { E120.fAC += arg1[0]; arg1 += 1; }
        if (flags & 0x4)     { E120.fB0 += arg1[0]; arg1 += 1; }
        if (flags & 0x8)     { E120.fB4 += arg1[0]; arg1 += 1; }
        if (flags & 0x10)    { E120.fB8 += arg1[0]; arg1 += 1; }
        if (flags & 0x20)    { E120.fBC += arg1[0]; arg1 += 1; }
        if (flags & 0x40)    { E120.fC0 += arg1[0]; arg1 += 1; }
        if (flags & 0x80)    { E120.fC4 += arg1[0]; arg1 += 1; }
        if (flags & 0x100)   { E120.fC8 += arg1[0]; }
    } else {
        arg1 += 2;
        if (flags & 0x1)     { E120.fA8 += E120.fD0; E120.fD0 += E120.fF8; arg1 += 3; E120.fF8 += arg1[-1]; }
        if (flags & 0x2)     { E120.fAC += E120.fD4; E120.fD4 += E120.fFC; arg1 += 3; E120.fFC += arg1[-1]; }
        if (flags & 0x4)     { E120.fB0 += E120.fD8; E120.fD8 += E120.f100; arg1 += 3; E120.f100 += arg1[-1]; }
        if (flags & 0x8)     { E120.fB4 += E120.fDC; E120.fDC += E120.f104; arg1 += 3; E120.f104 += arg1[-1]; }
        if (flags & 0x10)    { E120.fB8 += E120.fE0; E120.fE0 += E120.f108; arg1 += 3; E120.f108 += arg1[-1]; }
        if (flags & 0x20)    { E120.fBC += E120.fE4; E120.fE4 += E120.f10C; arg1 += 3; E120.f10C += arg1[-1]; }
        if (flags & 0x40)    { E120.fC0 += E120.fE8; E120.fE8 += E120.f110; arg1 += 3; E120.f110 += arg1[-1]; }
        if (flags & 0x80)    { E120.fC4 += E120.fEC; E120.fEC += E120.f114; arg1 += 3; E120.f114 += arg1[-1]; }
        if (flags & 0x100)   { E120.fC8 += E120.fF0; E120.fF0 += E120.f118; arg1 += 2; E120.f118 += arg1[0]; }
    }
}
#undef E120

typedef struct S34B {
    char pad[0x10];
    f32 f10, f14, f18;
    f32 f1C, f20, f24;
    f32 f28, f2C, f30;
} S34B;

#define E34 (((S34B *)(*(u8 **)(arg0 + 0x10)))[arg2])

void func_8002F354(u8 *arg0, f32 *arg1, s32 arg2) {
    s32 flags = *(s32 *)arg1;
    if (*(s16 *)((u8 *)arg1 + 6) != 0) {
        arg1 += 2;
        if (flags & 0x8)  { E34.f10 += arg1[0]; arg1 += 1; }
        if (flags & 0x10) { E34.f14 += arg1[0]; arg1 += 1; }
        if (flags & 0x20) { E34.f18 += arg1[0]; }
    } else {
        arg1 += 2;
        if (flags & 0x8)  { E34.f10 += E34.f1C; E34.f1C += E34.f28; arg1 += 3; E34.f28 += arg1[-1]; }
        if (flags & 0x10) { E34.f14 += E34.f20; E34.f20 += E34.f2C; arg1 += 3; E34.f2C += arg1[-1]; }
        if (flags & 0x20) { E34.f18 += E34.f24; E34.f24 += E34.f30; arg1 += 2; E34.f30 += arg1[0]; }
    }
}
#undef E34

extern void func_80030078();
extern u8 *func_800300F8();
extern void func_80030140();
extern u8 *func_80030164();
extern u8 *resetAnimationObjectTransparency();
extern void resetAnimationObjectTransform();

void func_8002F55C(u8 *arg0) {
    u8 *base;
    u8 *p;
    s32 t;
    s32 per;
    s32 cnt;
    s32 prev;
    s32 n;
    s32 j;
    s32 i;
    s32 *list;

    *(f32 *)(arg0 + 0x28) += *(f32 *)(arg0 + 0x2C);
    if (*(f32 *)(arg0 + 0x28) > 1.0) {
        *(f32 *)(arg0 + 0x28) = 1.0f;
    } else if (*(f32 *)(arg0 + 0x28) < 0.0) {
        *(f32 *)(arg0 + 0x28) = 0.0f;
    }
    *(f32 *)(arg0 + 0x30) += *(f32 *)(arg0 + 0x34);
    if (*(f32 *)(arg0 + 0x30) > 1.0) {
        *(f32 *)(arg0 + 0x30) = 1.0f;
    } else if (*(f32 *)(arg0 + 0x30) < 0.0) {
        *(f32 *)(arg0 + 0x30) = 0.0f;
    }

    /* ---- A ---- */
    base = *(u8 **)(arg0 + 0x1C) + *(s32 *)*(u8 **)(arg0 + 0x1C);
    t = *(s32 *)(arg0 + 0x24);
    per = *(s16 *)(base + 0x30);
    cnt = *(s16 *)(base + 0x32);
    p = base + 0x2C;
    if (*(s32 *)(base + 0x2C) == 2) {
        while (t >= per && per != 0) {
            t -= per;
        }
    }
    if (t == 0) {
        func_80030140(arg0);
    } else if (per >= t) {
        p += 8;
        prev = 0;
        j = 0;
        while (*(s16 *)p < t && j < cnt) {
            prev = *(s16 *)p;
            if (*(s16 *)(p + 2) != 0) {
                p += 8;
            } else {
                p += 0x10;
            }
            j++;
        }
        if (prev + 1 == t && j < cnt) {
            func_8002E568(arg0, p);
        }
        if (cnt != 0) {
            func_8002ECA4(arg0, (f32 *)p);
        }
    }

    /* ---- B ---- */
    t = *(s32 *)(arg0 + 0x24);
    p = base + *(s32 *)(base + 0x28);
    p += 0x28;
    per = *(s16 *)(p + 4);
    cnt = *(s16 *)(p + 6);
    if (*(s32 *)(base + 0x24) == 2) {
        while (t >= per && per != 0) {
            t -= per;
        }
    }
    if (t == 0) {
        func_80030078(arg0);
    } else if (per >= t) {
        p += 8;
        prev = 0;
        j = 0;
        while (*(s16 *)(p + 4) < t && j < cnt) {
            prev = *(s16 *)(p + 4);
            if (*(s16 *)(p + 6) != 0) {
                p += func_8002E3B0(*(s32 *)p) * 4;
                p += 8;
            } else {
                p += func_8002E3B0(*(s32 *)p) * 0xC;
                p += 8;
            }
            j++;
        }
        if (prev + 1 == t && j < cnt) {
            func_8002E42C(arg0, (f32 *)p);
        }
        if (cnt != 0) {
            func_8002E8D8(arg0, (f32 *)p);
        }
    }

    base = *(u8 **)(arg0 + 0x1C) + *(s32 *)(*(u8 **)(arg0 + 0x1C) + 4);
    n = *(s32 *)base;
    list = (s32 *)(base + 4);
    for (i = 0; i < n; i++) {
        /* ---- C ---- */
        t = *(s32 *)(arg0 + 0x24);
        p = base + list[i];
        p += 0x18;
        per = *(s16 *)(p + 4);
        cnt = *(s16 *)(p + 6);
        if (*(s32 *)p == 2) {
            while (t >= per && per != 0) {
                t -= per;
            }
        }
        if (t == 0) {
            func_800300F8(arg0, i);
        } else if (per >= t) {
            p += 8;
            prev = 0;
            j = 0;
            while (*(s16 *)p < t && j < cnt) {
                prev = *(s16 *)p;
                if (*(s16 *)(p + 2) != 0) {
                    p += 8;
                } else {
                    p += 0x10;
                }
                j++;
            }
            if (prev + 1 == t && j < cnt) {
                func_8002E598(arg0, p, i);
            }
            if (cnt != 0) {
                func_8002EBF4((LWInfoLightView *)arg0, (Cur2EBF4 *)p, i);
            }
        }

        /* ---- D ---- */
        t = *(s32 *)(arg0 + 0x24);
        p = base + list[i];
        p += 0x14;
        p += *(s32 *)p;
        per = *(s16 *)(p + 4);
        cnt = *(s16 *)(p + 6);
        if (*(s32 *)p == 2) {
            while (t >= per && per != 0) {
                t -= per;
            }
        }
        if (t == 0) {
            func_80030164(arg0, i);
        } else if (per >= t) {
            p += 8;
            prev = 0;
            j = 0;
            while (*(s16 *)(p + 4) < t && j < cnt) {
                prev = *(s16 *)(p + 4);
                if (*(s16 *)(p + 6) != 0) {
                    p += func_8002E3B0(*(s32 *)p) * 4;
                    p += 8;
                } else {
                    p += func_8002E3B0(*(s32 *)p) * 0xC;
                    p += 8;
                }
                j++;
            }
            if (prev + 1 == t && j < cnt) {
                func_8002E818(arg0, (f32 *)p, i);
            }
            if (cnt != 0) {
                func_8002F354(arg0, (f32 *)p, i);
            }
        }
    }

    base = *(u8 **)(arg0 + 0x1C) + *(s32 *)(*(u8 **)(arg0 + 0x1C) + 8);
    n = *(s32 *)base;
    list = (s32 *)(base + 4);
    for (i = 0; i < n; i++) {
        /* ---- E ---- */
        t = *(s32 *)(arg0 + 0x24);
        p = base + list[i];
        p += 4;
        p += *(s32 *)p * 4;
        p += 0x3C;
        per = *(s16 *)(p + 4);
        cnt = *(s16 *)(p + 6);
        if (*(s32 *)p == 2) {
            while (t >= per && per != 0) {
                t -= per;
            }
        }
        if (t == 0) {
            resetAnimationObjectTransparency(arg0, i);
        } else if (per >= t) {
            p += 8;
            prev = 0;
            j = 0;
            while (*(s16 *)p < t && j < cnt) {
                prev = *(s16 *)p;
                if (*(s16 *)(p + 2) != 0) {
                    p += 8;
                } else {
                    p += 0x10;
                }
                j++;
            }
            if (prev + 1 == t && j < cnt) {
                func_8002E5E0(arg0, p, i);
            }
            if (cnt != 0) {
                func_8002ED04(arg0, (f32 *)p, i);
            }
        }

        /* ---- F ---- */
        t = *(s32 *)(arg0 + 0x24);
        p = base + list[i];
        p += 4;
        p += *(s32 *)p * 4;
        p += 0x38;
        p += *(s32 *)p;
        per = *(s16 *)(p + 4);
        cnt = *(s16 *)(p + 6);
        if ((*(s32 *)p & 7) == 2) {
            while (t >= per && per != 0) {
                t -= per;
            }
        }
        if (t == 0) {
            resetAnimationObjectTransform(arg0, i);
        } else if (per >= t) {
            p += 8;
            prev = 0;
            j = 0;
            while (*(s16 *)(p + 4) < t && j < cnt) {
                prev = *(s16 *)(p + 4);
                if (*(s16 *)(p + 6) != 0) {
                    p += func_8002E3B0(*(s32 *)p) * 4;
                    p += 8;
                } else {
                    p += func_8002E3B0(*(s32 *)p) * 0xC;
                    p += 8;
                }
                j++;
            }
            if (prev + 1 == t && j < cnt) {
                func_8002E620(arg0, (f32 *)p, i);
            }
            if (cnt != 0) {
                func_8002EDA4(arg0, (f32 *)p, i);
            }
        }
    }
}


extern f32 __cosf(f32);
extern f32 sinf(f32);

void rotateVectorZXYDegrees(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 cx, cy, cz;
    f32 sx, sy, sz;
    f32 ax, ay, az;

    ax = (f64)arg0 * 0.017453293;
    cx = __cosf(ax);
    ay = (f64)arg1 * 0.017453293;
    cy = __cosf(ay);
    az = (f64)arg2 * 0.017453293;
    cz = __cosf(az);
    sx = sinf(ax);
    sy = sinf(ay);
    sz = sinf(az);

    ax = (cz * *arg3) - (*arg4 * sz);
    ay = (sz * *arg3) + (*arg4 * cz);
    az = *arg5;
    *arg3 = ax;
    *arg4 = (cy * ay) - (sy * az);
    *arg5 = (sy * ay) + (cy * az);

    ax = (cx * *arg3) + (*arg5 * sx);
    ay = *arg4;
    az = (-sx * *arg3) + (*arg5 * cx);
    *arg3 = ax;
    *arg4 = ay;
    *arg5 = az;
}


extern f32 __cosf(f32);
extern f32 sinf(f32);

void rotateVectorYXZDegrees(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 cx, cy, cz;
    f32 sx, sy, sz;
    f32 ax, ay, az;

    ax = (f64)arg0 * 0.017453293;
    cx = __cosf(ax);
    ay = (f64)arg1 * 0.017453293;
    cy = __cosf(ay);
    az = (f64)arg2 * 0.017453293;
    cz = __cosf(az);
    sx = sinf(ax);
    sy = sinf(ay);
    sz = sinf(az);

    ax = (cx * *arg3) + (*arg5 * sx);
    ay = *arg4;
    az = (-sx * *arg3) + (*arg5 * cx);
    *arg3 = ax;
    *arg4 = (cy * ay) - (sy * az);
    *arg5 = (sy * ay) + (cy * az);

    ax = (cz * *arg3) - (*arg4 * sz);
    ay = (sz * *arg3) + (*arg4 * cz);
    az = *arg5;
    *arg3 = ax;
    *arg4 = ay;
    *arg5 = az;
}

void func_80030078(void *arg0) {
    f32 *q = (f32 *)((u8 *)*(s32 **)((u8 *)arg0 + 0x1C) + *(s32 *)(*(s32 **)((u8 *)arg0 + 0x1C)));
    *(f32 *)((u8 *)arg0 + 0x1F8) = *q;
    *(f32 *)((u8 *)arg0 + 0x1FC) = *++q;
    *(f32 *)((u8 *)arg0 + 0x200) = *++q;
    *(f32 *)((u8 *)arg0 + 0x204) = *++q;
    *(f32 *)((u8 *)arg0 + 0x208) = *++q;
    *(f32 *)((u8 *)arg0 + 0x20C) = *++q;
    *(f32 *)((u8 *)arg0 + 0x210) = *++q;
    *(f32 *)((u8 *)arg0 + 0x214) = *++q;
    *(f32 *)((u8 *)arg0 + 0x218) = *++q;
}

u8 *func_800300F8(u8 *a0, s32 a1)
{
    u8 *base = *(u8 **)(a0 + 0x1C);
    f32 *p;

    base = *(s32 *)(base + 4) + base;
    p = (f32 *)(((s32 *)base)[a1 + 1] + base);
    p += 3;
    *(f32 *)(*(s32 *)(a0 + 0x10) + a1 * 52 + 4) = *p;
    return base;
}

void func_80030140(u8 *a0)
{
    f32 *p;

    p = (f32 *)(*(u8 **)(a0 + 0x1C) + *(s32 *)*(u8 **)(a0 + 0x1C));
    p += 9;
    *(f32 *)(a0 + 0x21C) = *p;
}

u8 *func_80030164(u8 *a0, s32 a1)
{
    u8 *base = *(u8 **)(a0 + 0x1C);
    u8 *p;

    base = *(s32 *)(base + 4) + base;
    p = (u8 *)(((s32 *)base)[a1 + 1] + base);
    *(f32 *)(*(s32 *)(a0 + 0x10) + a1 * 52 + 0x10) = *(f32 *)(p + 0);
    *(f32 *)(*(s32 *)(a0 + 0x10) + a1 * 52 + 0x14) = *(f32 *)(p + 4);
    *(f32 *)(*(s32 *)(a0 + 0x10) + a1 * 52 + 0x18) = *(f32 *)(p + 8);
    *(u8 *)(*(s32 *)(a0 + 0x10) + a1 * 52 + 0) = p[0x10];
    *(u8 *)(*(s32 *)(a0 + 0x10) + a1 * 52 + 1) = p[0x11];
    p += 0x12;
    *(u8 *)(*(s32 *)(a0 + 0x10) + a1 * 52 + 2) = *p;
    return base;
}

u8 *resetAnimationObjectTransparency(u8 *a0, s32 a1)
{
    u8 *base = *(u8 **)(a0 + 0x1C);
    s32 *p;

    base = *(s32 *)(base + 8) + base;
    p = (s32 *)(((s32 *)base)[a1 + 1] + base);
    p += 1;
    p += *p;
    p += 10;
    *(f32 *)(*(s32 *)(a0 + 0x14) + a1 * 288 + 0xCC) = *(f32 *)p;
    return base;
}

typedef struct {
    u8 pad0[0xA8];
    f32 unkA8, unkAC, unkB0, unkB4, unkB8, unkBC, unkC0, unkC4, unkC8;
    u8 padCC[0x120 - 0xCC];
} T24C_Item;

typedef struct {
    u8 pad0[8];
    s32 objectBlockOffset;
} LWAnimStreamObjectView;

typedef struct {
    u8 pad0[0x14];
    u8 *objectInfo;
    u8 pad18[4];
    LWAnimStreamObjectView *animStream;
} LWInfoObjectView;

void resetAnimationObjectTransform(LWInfoObjectView *arg0, s32 arg1) {
    u8 *base;
    f32 *q;

    base = arg0->animStream->objectBlockOffset + (u8 *) arg0->animStream;
    q = (f32 *) (base + ((s32 *) base)[arg1 + 1]);
    q += 1;
    q += *(s32 *) q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkA8 = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkAC = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkB0 = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkB4 = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkB8 = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkBC = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkC0 = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkC4 = *++q;
    ((T24C_Item *) arg0->objectInfo)[arg1].unkC8 = *++q;
}

typedef struct {
    /* 0x000 */ u8 pad0[0x3D];
    /* 0x03D */ u8 unk3D;
    /* 0x03E */ u8 pad3E[0xF8 - 0x3E];
    /* 0x0F8 */ Mtx mtx[2];
    /* 0x178 */ u8 pad178[0x1B8 - 0x178];
    /* 0x1B8 */ f32 mf1B8[4][4];
    /* 0x1F8 */ f32 f1F8;
    /* 0x1FC */ f32 f1FC;
    /* 0x200 */ f32 f200;
    /* 0x204 */ f32 f204;
    /* 0x208 */ f32 f208;
    /* 0x20C */ f32 f20C;
    /* 0x210 */ f32 f210;
    /* 0x214 */ f32 f214;
    /* 0x218 */ f32 f218;
} LWInfoTransformView;

void func_8003031C(arg0, arg1, arg2)
LWInfoTransformView *arg0;
f32 (*arg1)[4];
f32 (*arg2)[4];
{
    f32 tmp[4][4];
    f32 out[4][4];

    guMtxIdentF(arg0->mf1B8);
    guMtxIdentF(out);
    if (arg0->f1F8 != 0.0 || arg0->f1FC != 0.0 || arg0->f200 != 0.0) {
        guTranslateF(tmp, -arg0->f1F8, -arg0->f1FC, -arg0->f200);
        guMtxCatF(arg0->mf1B8, tmp, arg0->mf1B8);
    }
    if (arg0->f204 != 0.0) {
        guRotateF(tmp, arg0->f204, 0.0f, 1.0f, 0.0f);
        guMtxCatF(arg0->mf1B8, tmp, arg0->mf1B8);
    }
    if (arg0->f208 != 0.0) {
        guRotateF(tmp, arg0->f208, 1.0f, 0.0f, 0.0f);
        guMtxCatF(arg0->mf1B8, tmp, arg0->mf1B8);
    }
    if (arg0->f20C != 0.0) {
        guRotateF(tmp, arg0->f20C, 0.0f, 0.0f, 1.0f);
        guMtxCatF(arg0->mf1B8, tmp, arg0->mf1B8);
    }
    if (arg0->f210 != 1.0 || arg0->f214 != 1.0 || arg0->f218 != 1.0) {
        guScaleF(tmp, arg0->f210, arg0->f214, arg0->f218);
        guMtxCatF(arg0->mf1B8, tmp, arg0->mf1B8);
    }
    if (arg2 != 0) {
        guMtxCatF(arg0->mf1B8, arg2, arg0->mf1B8);
    }
    if (arg1 != 0) {
        guMtxCatF(arg1, arg0->mf1B8, out);
    } else {
        guMtxCatF(out, arg0->mf1B8, out);
    }
    guMtxF2L(out, &arg0->mtx[arg0->unk3D]);
}

extern Gfx *D_800F22B4;

typedef struct {
    u8 c0, c1, c2, c3;
    f32 f4;
    char pad8[0x34 - 8];
} C34;

void loadAnimationLights(arg0)
u8 *arg0;
{
    u8 *base;
    s32 i;
    s32 n;
    f32 m;

    base = *(u8 **)(arg0 + 0x1C) + *(s32 *)(*(u8 **)(arg0 + 0x1C) + 4);
    n = *(s32 *)base;
    for (i = 0; i < n; i++) {
        m = *(f32 *)(arg0 + 0x30) < ((C34 *)*(s32 *)(arg0 + 0x10))[i].f4
              ? *(f32 *)(arg0 + 0x30)
              : ((C34 *)*(s32 *)(arg0 + 0x10))[i].f4;
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 0] = (u32)((C34 *)*(s32 *)(arg0 + 0x10))[i].c0 * m;
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 1] = (u32)((C34 *)*(s32 *)(arg0 + 0x10))[i].c1 * m;
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 2] = (u32)((C34 *)*(s32 *)(arg0 + 0x10))[i].c2 * m;
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 4] = ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 0];
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 5] = ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 1];
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 6] = ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 2];
        gSPLight(D_800F22B4++, &((Light *)((u8 **)arg0)[arg0[0x3D]])[i], i + 1);
    }
    gSPNumLights(D_800F22B4++, n - 1);
}

extern Gfx *D_800F22B4;

typedef struct {
    u8 c0, c1, c2, c3;
    f32 f4;
    char pad8[0x34 - 8];
} C34B;

typedef struct {
    s16 *p0;
    u8 *p4;
} T8B;

#define SRC (((C34B *)*(s32 *)(arg0 + 0x10))[j])
#define LT  (&((u8 **)arg0)[arg0[0x3D]])

void loadMaterialTintedAnimationLights(arg0, arg1, arg2, arg3, arg4, arg5)
u8 *arg0;
s32 arg1;
s32 arg2;
u8 arg3;
u8 arg4;
u8 arg5;
{
    u8 *base;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 s;
    s32 q;
    f32 m;

    base = *(u8 **)(arg0 + 0x1C) + *(s32 *)(*(u8 **)(arg0 + 0x1C) + 4);
    n = *(s32 *)base;
    for (i = 0; i < *(s32 *)(arg0 + 0x20); i++) {
        s = ((T8B *)*(u8 **)(arg0 + 0x18))[arg1].p0[arg2];
        for (j = 0; j < n; j++) {
            m = *(f32 *)(arg0 + 0x30) < SRC.f4 ? *(f32 *)(arg0 + 0x30) : SRC.f4;
            q = s * n + j;
            for (k = 0; k < 3; k++) {
                ((Light *)LT[2])[q].l.dir[k] = ((Light *)LT[0])[j].l.dir[k];
            }
            LT[2][q * 0x10 + 0] = (u32)SRC.c0 * m * (u32)arg3 / 255.0;
            LT[2][q * 0x10 + 1] = (u32)SRC.c1 * m * (u32)arg4 / 255.0;
            LT[2][q * 0x10 + 2] = (u32)SRC.c2 * m * (u32)arg5 / 255.0;
            LT[2][q * 0x10 + 4] = LT[2][q * 0x10 + 0];
            LT[2][q * 0x10 + 5] = LT[2][q * 0x10 + 1];
            LT[2][q * 0x10 + 6] = LT[2][q * 0x10 + 2];
            gSPLight(D_800F22B4++, &((Light *)LT[2])[q], j + 1);
        }
    }
    gSPNumLights(D_800F22B4++, n - 1);
}

#undef SRC
#undef LT

extern Gfx *D_800F22B4;

#define gCmd(pkt, W0, W1) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
    _g->words.w0 = (W0); \
    _g->words.w1 = (W1); \
}

/* Wider view of the same 0x34-stride array S34 views from 0x1C; both are TU-local
 * view structs over one object, which is the established idiom in this file. */
typedef struct {
    u8 pad0[0x10];
    f32 f10, f14, f18, f1C, f20, f24, f28, f2C, f30;
} T52;

void buildAnimationLightDirections(arg0)
u8 *arg0;
{
    u8 *base;
    s32 i;
    s32 n;
    f32 x;
    f32 y;
    f32 z;

    base = *(u8 **)(arg0 + 0x1C) + *(s32 *)(*(u8 **)(arg0 + 0x1C) + 4);
    n = *(s32 *)base;
    for (i = 0; i < n; i++) {
        x = 0.0f;
        y = 0.0f;
        z = 120.0f;
        rotateVectorZXYDegrees(((T52 *)*(s32 *)(arg0 + 0x10))[i].f10,
                      ((T52 *)*(s32 *)(arg0 + 0x10))[i].f14,
                      ((T52 *)*(s32 *)(arg0 + 0x10))[i].f18, &x, &y, &z);
        rotateVectorYXZDegrees(-*(f32 *)(arg0 + 0x204), -*(f32 *)(arg0 + 0x208),
                      *(f32 *)(arg0 + 0x20C), &x, &y, &z);
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 8] = (s32)x;
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 9] = (s32)y;
        ((u8 **)arg0)[arg0[0x3D]][i * 0x10 + 0xA] = (s32)-z;
    }
    if (n != 0) {
        gSPSetGeometryMode(D_800F22B4++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(D_800F22B4++, G_LIGHTING);
    }
}

typedef struct { s32 indexList; u8 *geomStream; } LWGeometryInfoStreamView;

u8 *func_800310C4(a0, a1, a2)
u8 *a0;
s32 a1;
s16 *a2;
{
    u8 *base;
    u8 *q;
    s32 i;
    s16 n;
    s16 v;

    base = *(u8 **)(a0 + 0x1C) + *(s32 *)(*(u8 **)(a0 + 0x1C) + 8);
    base += ((s32 *)base)[a1 + 1];
    *a2 = *(s16 *)base;
    base += 2;
    n = *(s16 *)base;
    q = ((LWGeometryInfoStreamView *)*(u8 **)(a0 + 0x18))[*a2].geomStream + *(s32 *)((LWGeometryInfoStreamView *)*(u8 **)(a0 + 0x18))[*a2].geomStream;
    q += 4;
    for (i = 0; i < n; i++) {
        if (*q) {
            v = *(s16 *)(q + 0x10);
            q += v * 2;
            q += 0x12;
        } else {
            v = *(s16 *)(q + 4);
            q += v * 2;
            q += 6;
        }
        if (!(v & 1)) {
            q += 2;
        }
    }
    return q;
}

typedef struct { Mtx mtx[2]; u8 pad80[0x120 - 0x80]; } T24C_Mtx;
#define ITEM ((T24C_Item *) ((u8 *) arg0->objectInfo + idx * 0x120))

void buildAnimationObjectHierarchyMatrices(LWInfoObjectView *arg0, s32 *base, s32 *tbl, s32 idx, f32 *mf) {
    f32 ntx, nty, ntz;
    f32 wx, wy, wz;
    f32 scx, scy, scz;
    f32 m33, t2, t1, t0;
    f32 m23, r22, r12, r02;
    f32 m13, r21, r11, r01;
    f32 m03, r20, r10, r00;
    f32 out[4][4];
    u8 *p;
    s32 n;
    s32 *kids;
    s32 i;
    f32 sy, cy, sx, cx, sz, cz;

    p = (u8 *) base + tbl[idx];
    n = *(s32 *) (p + 4);
    p += 4;
    kids = (s32 *) (p + 4);
    p += n * 4;
    p += 4;
    ntx = *(f32 *) (p + 0x28);
    nty = *(f32 *) (p + 0x2C);
    ntz = *(f32 *) (p + 0x30);
    sy = sinf((f32) ((f64) ITEM->unkB8 * 0.017453293));
    cy = __cosf((f32) ((f64) ITEM->unkB8 * 0.017453293));
    sx = sinf((f32) ((f64) ITEM->unkB4 * 0.017453293));
    cx = __cosf((f32) ((f64) ITEM->unkB4 * 0.017453293));
    sz = sinf((f32) ((f64) ITEM->unkBC * 0.017453293));
    cz = __cosf((f32) ((f64) ITEM->unkBC * 0.017453293));
    scx = ITEM->unkC0;
    scy = ITEM->unkC4;
    scz = ITEM->unkC8;
    wx = ITEM->unkA8;
    wy = ITEM->unkAC;
    wz = ITEM->unkB0;
    r00 = ((cx * cz) + (sx * sy * sz)) * scx;
    r01 = ((-cx * sz) + (sx * sy * cz)) * scy;
    r02 = sx * cy * scz;
    r10 = cy * sz * scx;
    r11 = cy * cz * scy;
    r12 = -sy * scz;
    r20 = ((-sx * cz) + (cx * sy * sz)) * scx;
    r21 = ((sx * sz) + (cx * sy * cz)) * scy;
    r22 = cx * cy * scz;
    t0 = ((wx - r00 * ntx) - r01 * nty) - r02 * ntz;
    t1 = ((wy - r10 * ntx) - r11 * nty) - r12 * ntz;
    t2 = ((wz - r20 * ntx) - r21 * nty) - r22 * ntz;
    out[0][0] = mf[8] * r20 + (mf[4] * r10 + (mf[0] * r00));
    out[1][0] = mf[8] * r21 + (mf[4] * r11 + (mf[0] * r01));
    out[2][0] = mf[8] * r22 + (mf[4] * r12 + (mf[0] * r02));
    out[3][0] = mf[12] + (mf[8] * t2 + (mf[4] * t1 + (mf[0] * t0)));
    out[0][1] = mf[9] * r20 + (mf[5] * r10 + (mf[1] * r00));
    out[1][1] = mf[9] * r21 + (mf[5] * r11 + (mf[1] * r01));
    out[2][1] = mf[9] * r22 + (mf[5] * r12 + (mf[1] * r02));
    out[3][1] = mf[13] + (mf[9] * t2 + (mf[5] * t1 + (mf[1] * t0)));
    out[0][2] = mf[10] * r20 + (mf[6] * r10 + (mf[2] * r00));
    out[1][2] = mf[10] * r21 + (mf[6] * r11 + (mf[2] * r01));
    out[2][2] = mf[10] * r22 + (mf[6] * r12 + (mf[2] * r02));
    out[3][2] = mf[14] + (mf[10] * t2 + (mf[6] * t1 + (mf[2] * t0)));
    out[0][3] = 0.0f;
    out[1][3] = 0.0f;
    out[2][3] = 0.0f;
    out[3][3] = 1.0f;
    guMtxF2L(out, &((T24C_Mtx *) arg0->objectInfo)[idx].mtx[*((u8 *) arg0 + 0x3D)]);
    i = 0;
    if (n > 0) {
        do {
            buildAnimationObjectHierarchyMatrices(arg0, base, tbl, *kids, (f32 *) out);
            i += 1;
            kids += 1;
        } while (i != n);
    }
}


void buildAnimationObjectMatrices(LWInfoObjectView *arg0) {
    s32 *base;
    s32 i;
    s32 n;
    u8 *p;
    s32 *tbl;
    f32 m[4][4];

    base = (s32 *) (arg0->animStream->objectBlockOffset + (u8 *) arg0->animStream);
    n = *base;
    tbl = base + 1;
    for (i = 0; i < n; i++) {
        p = tbl[i] + (u8 *) base;
        p += 4;
        p += *(s32 *) p * 4;
        p += 0x38;
        p += *(s32 *) p;
        m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
        m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f; m[3][1] = 0.0f;
        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f; m[3][2] = 0.0f;
        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3] = 1.0f;
        if (*(s32 *) p & 0x10) {
            buildAnimationObjectHierarchyMatrices(arg0, base, tbl, i, &m[0][0]);
        }
    }
}


extern Gfx *D_800F22B4;

#define gCmd(pkt, W0, W1) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
    _g->words.w0 = (W0); \
    _g->words.w1 = (W1); \
}

typedef struct {
    /* 0x000 */ Mtx mtx[2];
} M1A98;

typedef struct {
    /* 0x000 */ u8 pad0[0x78];
    /* 0x078 */ Mtx proj[2];
} P1A98;

typedef struct {
    /* 0x000 */ u8 pad0[0x80];
    /* 0x080 */ u8 unk80;
    /* 0x081 */ u8 pad81[0x120 - 0x81];
} E1A98;

extern void func_800321D4();

void func_80031A98(arg0, arg1)
u8 *arg0;
s32 arg1;
{
    u8 *base;
    s32 i;
    s32 n;

    u16 pn;
    s16 v;

    base = *(u8 **)(arg0 + 0x1C) + *(s32 *)(*(u8 **)(arg0 + 0x1C) + 8);
    n = *(s32 *)base;
    gSPClearGeometryMode(D_800F22B4++, G_SHADE | G_SHADING_SMOOTH | G_CULL_FRONT | G_CULL_BACK | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gSPSetGeometryMode(D_800F22B4++, G_ZBUFFER | G_SHADE | G_LIGHTING);
    guPerspective(&((P1A98 *)arg0)->proj[arg0[0x3D]], &pn, *(f32 *)(arg0 + 0x270),
                  1.3333334f, *(f32 *)(arg0 + 0x40), *(f32 *)(arg0 + 0x44), 1.0f);
    gSPPerspNormalize(D_800F22B4++, pn);
    gSPMatrix(D_800F22B4++, (u32)&((M1A98 *)arg0)->mtx[arg0[0x3D]] + 0x80000078, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(D_800F22B4++);
    gDPSetCycleType(D_800F22B4++, G_CYC_2CYCLE);
    gDPPipelineMode(D_800F22B4++, G_PM_1PRIMITIVE);
    gDPSetColorDither(D_800F22B4++, G_CD_MAGICSQ);
    gDPSetAlphaDither(D_800F22B4++, G_AD_DISABLE);
    gDPSetPrimColor(D_800F22B4++, 0, 0, 255, 255, 255, 255);
    gDPSetBlendColor(D_800F22B4++, 0, 0, 0, 0);
    gDPSetTexturePersp(D_800F22B4++, G_TP_PERSP);
    gDPSetTextureDetail(D_800F22B4++, G_TD_CLAMP);
    gDPSetTextureLOD(D_800F22B4++, G_TL_LOD);
    gDPSetTextureLUT(D_800F22B4++, G_TT_NONE);
    gDPSetTextureFilter(D_800F22B4++, G_TF_BILERP);
    gDPSetCombineLERP(D_800F22B4++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIMITIVE, 0);
    gDPSetAlphaCompare(D_800F22B4++, G_AC_THRESHOLD);
    gDPSetRenderMode(D_800F22B4++, *(s32 *)(arg0 + 0x68), G_RM_PASS);
    arg0[0x38] = 1;
    for (i = 0; i < n; i++) {
        base = func_800310C4(arg0, i, &v);
        base += 2;
        if (((E1A98 *)*(u8 **)(arg0 + 0x14))[i].unk80 == 0xFF && *(s16 *)base == 0) {
            base -= 2;
            func_800321D4(arg0, v, base, i, 1, arg1);
        }
    }
    for (i = 0; i < n; i++) {
        base = func_800310C4(arg0, i, &v);
        base += 1;
        if ((*base == 0 || ((E1A98 *)*(u8 **)(arg0 + 0x14))[i].unk80 != 0xFF)
                && ((E1A98 *)*(u8 **)(arg0 + 0x14))[i].unk80 != 0) {
            base -= 1;
            func_800321D4(arg0, v, base, i, 2, arg1);
        }
    }
}

void transformVector4InPlace(arg0, arg1)
f32 arg0[4][4];
f32 *arg1;
{
    s32 i;
    s32 j;
    f32 d[4];

    for (i = 0; i < 4; i++) {
        d[i] = 0.0f;
        for (j = 0; j < 4; j++) {
            d[i] += arg0[j][i] * arg1[j];
        }
    }
    for (i = 0; i < 4; i++) {
        arg1[i] = d[i];
    }
}

#define gCmd(pkt, W0, W1) \
{ \
    Gfx *_g = (Gfx *)(pkt); \
    _g->words.w0 = (W0); \
    _g->words.w1 = (W1); \
}

typedef struct {
    /* 0x000 */ Mtx mtx[2];
    /* 0x080 */ u8 unk80;
    /* 0x081 */ u8 pad81[0x88 - 0x81];
    /* 0x088 */ LookAt lookat;
    /* 0x0A8 */ u8 padA8[0x120 - 0xA8];
} E321;

typedef struct {
    /* 0x000 */ u8 pad0[0x14];
    /* 0x014 */ E321 *objectInfo;
    /* 0x018 */ s32 geometryInfo;
    /* 0x01C */ u8 pad1C[0x24 - 0x1C];
    /* 0x024 */ s32 unk24;
    /* 0x028 */ u8 pad28[0x38 - 0x28];
    /* 0x038 */ u8 unk38;
    /* 0x039 */ u8 pad39[0x3A - 0x39];
    /* 0x03A */ u8 unk3A;
    /* 0x03B */ u8 unk3B;
    /* 0x03C */ u8 pad3C[0x3D - 0x3C];
    /* 0x03D */ u8 unk3D;
    /* 0x03E */ s16 unk3E;
    /* 0x040 */ u8 pad40[0x4A - 0x40];
    /* 0x04A */ u8 unk4A;
    /* 0x04B */ u8 pad4B[0x4C - 0x4B];
    /* 0x04C */ s32 unk4C;
    /* 0x050 */ s32 unk50;
    /* 0x054 */ s32 unk54;
    /* 0x058 */ s32 unk58;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ s32 unk60;
    /* 0x064 */ s32 unk64;
    /* 0x068 */ s32 unk68;
    /* 0x06C */ s32 unk6C;
    /* 0x070 */ s32 unk70;
    /* 0x074 */ u8 pad74[0xF8 - 0x74];
    /* 0x0F8 */ Mtx mtx[2];
    /* 0x178 */ f32 mf178[4][4];
    /* 0x1B8 */ f32 mf1B8[4][4];
} LWInfoRenderView;

extern Gfx *D_800F22B4;
extern void func_80031FEC(LWInfoRenderView *, s32, u8 *, s32);
extern void func_80032320();
extern s32 func_8002CDC0(f32 [4][4], f32 [4][4]);
extern void transformVector4InPlace(f32 [4][4], f32 *);
extern char D_800EBED4[];

void func_80031FEC(arg0, arg1, arg2, arg3)
LWInfoRenderView *arg0;
s32 arg1;
u8 *arg2;
s32 arg3;
{
    Mtx mtx;
    f32 mf[4][4];
    f32 at[4];
    f32 up[4];
    f32 eye[4];

    guMtxL2F(mf, &arg0->objectInfo[arg1].mtx[arg0->unk3D]);
    if (arg0->unk3B == 0) {
        if (func_8002CDC0(arg0->mf1B8, arg0->mf178) == 0) {
            arg0->unk3B = 1;
            rmonPrintf(D_800EBED4);
            guMtxIdentF(arg0->mf178);
        }
    }
    at[0] = *(f32 *)(arg2 + 4);
    at[1] = *(f32 *)(arg2 + 8);
    at[2] = *(f32 *)(arg2 + 0xC);
    at[3] = 1.0f;
    eye[0] = 0.0f;
    eye[1] = 0.0f;
    eye[2] = 0.0f;
    eye[3] = 1.0f;
    up[0] = 0.0f;
    up[1] = -1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    if (arg3 != 0) {
        transformVector4InPlace((f32 (*)[4]) arg3, at);
    }
    transformVector4InPlace(mf, at);
    transformVector4InPlace(arg0->mf178, up);
    transformVector4InPlace(arg0->mf178, eye);
    guLookAtReflect(&mtx, &arg0->objectInfo[arg1].lookat, eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1],
                    up[2]);
    gSPLookAtX(D_800F22B4++, (u32) &arg0->objectInfo[arg1].lookat);
    gSPLookAtY(D_800F22B4++, (u32) &arg0->objectInfo[arg1].lookat.l[1]);
}

void func_800321D4(arg0, arg1, arg2, arg3, arg4, arg5)
LWInfoRenderView *arg0;
s32 arg1;
u8 *arg2;
s32 arg3;
s32 arg4;
s32 arg5;
{
    s16 n;
    s32 j;

    /* The Mtx bank lives at +0xF8, but IDO defers a member's constant offset to the
     * OUTERMOST add, so `&arg0->mtx[i] + 0x80000000` emits addu+addiu 0xF8 and lets the
     * duplicated 0x80000000 be CSE'd into a temp. Folding 0xF8 into the literal keeps the
     * two constants distinct, so each stays an immediate (as1 $at) as the ROM has it. */
    gSPMatrix(D_800F22B4++, (u32)&((Mtx *)arg0)[arg0->unk3D] + 0x800000F8, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(D_800F22B4++, (u32)&arg0->objectInfo[arg3].mtx[arg0->unk3D] + 0x80000000, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    if (*arg2 != 0) {
        func_80031FEC(arg0, arg3, arg2, arg5);
        arg2 += 0x10;
    } else {
        arg2 += 4;
    }
    n = *(s16 *)arg2;
    arg2 += 2;
    for (j = 0; j < n; j++) {
        func_80032320(arg0, arg1, *(s16 *)arg2, arg0->objectInfo[arg3].unk80, arg4);
        arg2 += 2;
    }
}

/*
 * func_80032320  ROM 0xD6D0  (932 insns, frame 0x138) -- MATCHED 2026-09-03.
 * Texture/animation display-list builder: walks one record through a single advancing byte
 * cursor `p` (r,g,b,a, flags, pal, s16 count, s16 div, s16 frames[]), then emits the
 * combine/texture/tile/load commands for the mip levels. The gbi.h macros (gSPTexture,
 * gDPSetTile, gDPSetTileSize, gDPLoadBlock) are load-bearing: their _SHIFTL term order and
 * casts fix the ugen scratch-register draw order; the house gCmd form was 30 rows short.
 * `hh`/`ww` double as the mip-size loop copies and (hh) as the clamped-alpha temp; `x` is the
 * promoted K&R byte argument (its v0 web must be a plain variable so alpha keeps pool slot 0x3C).
 * Owns jtbl_800EBF48 (pal2 switch) and jtbl_800EBF68 (fmt switch) in the code_8170 .rodata.
 */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8  pad8[0x10 - 0x08];
    /* 0x10 */ s32 unk10;
} T321;

extern void func_800331B0();

#define NODE ((T321 *)((T321 *)((u8 *)arg0->geometryInfo + arg1 * 8))->unk4)

void func_80032320(arg0, arg1, arg2, arg3, arg4)
LWInfoRenderView *arg0;
s32 arg1;
s32 arg2;
s32 arg3;
s32 arg4;
{
    s16 count;
    s16 dv;
    s32 n;
    s32 size;
    s32 hh;
    s32 ww;
    u8 *timg;
    u8 pal2;
    u8 fmt;
    u8 alpha;
    u8 sh;
    s32 x;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    s32 lw2;
    s32 lh2;
    s32 levels;
    s32 clamp;
    s32 w;
    s32 h;
    s32 i;
    u8 *p;
    u8 *q;

    p = (u8 *)(*(s32 *)((NODE->unk4 + (u8 *)NODE) + arg2 * 4 + 4) + (NODE->unk4 + (u8 *)NODE));
    count = *(s16 *)(p + 6);
    dv = *(s16 *)(p + 8);
    if (count != 0) {
        q = NODE->unk10 + (u8 *)NODE;
        timg = q;
        i = (arg0->unk24 / dv) % count;
        q += *(s16 *)(p + i * 2 + 0xA) * 8;
        fmt = *q;
        levels = *++q;
        w = *++q;
        h = *++q;
        timg += *(s32 *)++q;
    } else {
        fmt = 8;
    }
    if (arg4 == 2 && p[3] == 0xFF && p[5] == 0 && fmt != 1 && (u8) arg3 == 0xFF) {
        return;
    }
    if (arg4 == 1 && (p[3] < 0xFF || (p[4] & 0x10) || fmt == 1)) {
        return;
    }
    {
        r = *p++;
        g = *p++;
        b = *p++;
        a = *p++;
        x = *((u8 *)&arg3 + 3);
        hh = x;
        if (hh < a) {
            a = hh;
        }
        alpha = a;
        if (p[0] & 8) {
            if (arg2 != arg0->unk3E) {
                loadMaterialTintedAnimationLights(arg0, arg1, arg2, *(u8 *)&r, *(u8 *)&g, *(u8 *)&b);
            }
            arg0->unk3E = arg2;
        } else {
            if (arg0->unk3E != -1) {
                loadAnimationLights(arg0);
            }
            arg0->unk3E = -1;
        }
        if (p[0] & 4) {
            gSPSetGeometryMode(D_800F22B4++, G_SHADING_SMOOTH);
        } else {
            gSPClearGeometryMode(D_800F22B4++, G_SHADING_SMOOTH);
        }
        if (p[0] & 1) {
            if (arg0->unk3A != 0) {
                gSPSetGeometryMode(D_800F22B4++, G_CULL_FRONT);
            } else {
                gSPSetGeometryMode(D_800F22B4++, G_CULL_BACK);
            }
        } else {
            if (arg0->unk3A != 0) {
                gSPClearGeometryMode(D_800F22B4++, G_CULL_FRONT);
            } else {
                gSPClearGeometryMode(D_800F22B4++, G_CULL_BACK);
            }
        }
        if (p[0] & 2) {
            gSPClearGeometryMode(D_800F22B4++, G_LIGHTING);
        } else {
            gSPSetGeometryMode(D_800F22B4++, G_LIGHTING);
        }
        if (arg0->unk4A != 0) {
            if (p[0] & 0x20) {
                n = 1;
            } else {
                n = 0;
            }
        } else {
            n = 0;
        }
        sh = 0;
        if (p[0] & 0x80) {
            sh = 1;
            gSPSetGeometryMode(D_800F22B4++, G_TEXTURE_GEN);
        } else if (p[0] & 0x40) {
            sh = 1;
            gSPSetGeometryMode(D_800F22B4++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
        } else {
            gSPClearGeometryMode(D_800F22B4++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
        }
        if (n != 0) {
            arg0->unk5C = arg0->unk4C;
            arg0->unk60 = arg0->unk50;
            arg0->unk64 = arg0->unk64 | 8;
            arg0->unk68 = arg0->unk68 | 8;
            arg0->unk6C = arg0->unk6C | 8;
            arg0->unk70 = arg0->unk70 | 8;
        } else {
            arg0->unk5C = arg0->unk54;
            arg0->unk60 = arg0->unk58;
            arg0->unk64 = arg0->unk64 & ~8;
            arg0->unk68 = arg0->unk68 & ~8;
            arg0->unk6C = arg0->unk6C & ~8;
            arg0->unk70 = arg0->unk70 & ~8;
        }
        gDPPipeSync(D_800F22B4++);
        gDPSetPrimColor(D_800F22B4++, 0, 0, r, g, b, (u32)a);
        if (alpha < 0xFF || fmt == 1) {
            if (count != 0) {
                if (arg0->unk38 != 5) {
                    gDPSetCycleType(D_800F22B4++, G_CYC_2CYCLE);
                    gDPSetRenderMode(D_800F22B4++, arg0->unk60, G_RM_PASS);
                    arg0->unk38 = 5;
                }
            } else if (arg0->unk38 != 4) {
                gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
                gDPSetRenderMode(D_800F22B4++, arg0->unk5C, arg0->unk60);
                arg0->unk38 = 4;
            }
        } else if (count != 0) {
            if (p[0] & 0x10) {
                if (arg0->unk38 != 1) {
                    gDPSetCycleType(D_800F22B4++, G_CYC_2CYCLE);
                    gDPSetRenderMode(D_800F22B4++, arg0->unk68, G_RM_PASS);
                    arg0->unk38 = 1;
                }
            } else if (arg0->unk38 != 3) {
                gDPSetCycleType(D_800F22B4++, G_CYC_2CYCLE);
                gDPSetRenderMode(D_800F22B4++, arg0->unk70, G_RM_PASS);
                arg0->unk38 = 3;
            }
        } else if (p[0] & 0x10) {
            if (arg0->unk38 != 0) {
                gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
                gDPSetRenderMode(D_800F22B4++, arg0->unk64, arg0->unk68);
                arg0->unk38 = 0;
            }
        } else if (arg0->unk38 != 2) {
            gDPSetCycleType(D_800F22B4++, G_CYC_1CYCLE);
            gDPSetRenderMode(D_800F22B4++, arg0->unk6C, arg0->unk70);
            arg0->unk38 = 2;
        }
        pal2 = p[1];
        p += 1;
        clamp = 0;
        switch (pal2) {
        case 0:
            clamp = 2;
            break;
        case 1:
            break;
        case 2:
            clamp = 1;
            break;
        default:
            clamp = 2;
            break;
        }
        p += count * 2;
        p += 5;
        if (count != 0) {
            gDPSetCombineLERP(D_800F22B4++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIMITIVE, 0);
            if (sh != 0) {
                gSPTexture(D_800F22B4++, w << 6, h << 6, levels, 2, 1);
            } else {
                gSPTexture(D_800F22B4++, 0x8000, 0x8000, levels, 2, 1);
            }
            size = 0;
            ww = w;
            hh = h;
            for (i = 0; i <= levels; i++) {
                size += ww * hh;
                ww >>= 1;
                hh >>= 1;
            }
            gDPPipeSync(D_800F22B4++);
            gDPTileSync(D_800F22B4++);
            switch (fmt) {
            case 0:
                gDPSetTextureImage(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, timg);
                gDPSetTile(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 2, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
                break;
            case 1:
                gDPSetTextureImage(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, timg);
                gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, 2, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
                break;
            case 4:
                gDPSetTextureImage(D_800F22B4++, G_IM_FMT_I, G_IM_SIZ_8b, 1, timg);
                gDPSetTile(D_800F22B4++, G_IM_FMT_I, G_IM_SIZ_8b, 0, 0, 2, 0, G_TX_WRAP, 0, 0, G_TX_WRAP, 0, 0);
                break;
            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
                break;
            }
            gDPLoadBlock(D_800F22B4++, 2, 0, 0, size, 0);
            size = 0;
            i = w;
            lw2 = 0;
            while (i >= 2) {
                lw2++;
                i >>= 1;
            }
            i = h;
            lh2 = 0;
            while (i >= 2) {
                lh2++;
                i >>= 1;
            }
            for (i = 0; i <= levels; i++) {
                switch (fmt) {
                case 0:
                    gDPSetTile(D_800F22B4++, G_IM_FMT_RGBA, G_IM_SIZ_16b, w >> 2, size, i + 2, 0, clamp, lw2 - i, i, clamp, lh2 - i, i);
                    break;
                case 1:
                    gDPSetTile(D_800F22B4++, G_IM_FMT_IA, G_IM_SIZ_16b, w >> 2, size, i + 2, 0, clamp, lw2 - i, i, clamp, lh2 - i, i);
                    break;
                case 2:
                    break;
                case 4:
                    gDPSetTile(D_800F22B4++, G_IM_FMT_I, G_IM_SIZ_8b, (w >> 2) / 2, size, i + 2, 0, clamp, lw2 - i, i, clamp, lh2 - i, i);
                    break;
                case 3:
                    break;
                case 5:
                    break;
                case 7:
                    break;
                case 6:
                    break;
                default:
                    break;
                }
                gDPSetTileSize(D_800F22B4++, i + 2, 0, 0, (w - 1) << 2, (h - 1) << 2);
                w >>= 1;
                h >>= 1;
                if (fmt == 4) {
                    size += w * (h >> 1);
                } else {
                    size += w * h;
                }
            }
        } else {
            gDPSetCombineLERP(D_800F22B4++, PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0);
        }
        n = *(s16 *)p;
        p += 2;
        for (i = 0; i < n; i++) {
            func_800331B0(arg0, arg1, *(s16 *)(p + i * 2));
        }
    }
}
#undef NODE

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
} R6;

typedef struct {
    /* 0x0 */ s16 cnt;
    /* 0x2 */ s16 off;
    /* 0x4 */ R6 rec[1];
} H6;

void func_800331B0(arg0, arg1, arg2)
u8 *arg0;
s32 arg1;
s32 arg2;
{
    u8 *base;
    u8 *base2;
    u8 *p;
    u8 *e;
    u8 *np;
    s32 i;
    s16 n;
    s32 j;
    s32 k;
    s32 cur;
    s32 cell;
    s32 b;
    u8 *vp;
    u32 val;
    s32 vidx;

    base = ((LWGeometryInfoStreamView *)*(u8 **)(arg0 + 0x18))[arg1].geomStream
         + *(s32 *)(((LWGeometryInfoStreamView *)*(u8 **)(arg0 + 0x18))[arg1].geomStream + 8);
    p = base;
    for (i = 0; i < arg2; i++) {
        p += 2;
    }
    cur = 0;
    p = *(s16 *)p + base;
    base2 = ((LWGeometryInfoStreamView *)*(u8 **)(arg0 + 0x18))[arg1].geomStream
          + *(s32 *)(((LWGeometryInfoStreamView *)*(u8 **)(arg0 + 0x18))[arg1].geomStream + 0xC);
    n = ((H6 *)p)->cnt;
    e = (u8 *)&((H6 *)p)->rec[n];
    np = ((H6 *)p)->off + p;
    p += 4;
    cell = 0;
    for (i = 0; i < n; i++) {
        vp = base2 + *(s16 *)p * 0x10;
        gSPVertex(D_800F22B4++, vp, p[3], p[2]);
        j = 0;
        for (k = 0; k < p[4]; k++) {
            if (j < p[5]) {
                while (e[1] == (u8)k) {
                    val = *(u32 *)(e + 2);
                    vidx = e[0];
                    gSPModifyVertex(D_800F22B4++, vidx, G_MWO_POINT_ST, val);
                    e += 6;
                    j++;
                }
            }
            if (cell & 1) {
                b = *np++;
                gSP1Triangle(D_800F22B4++, cur & 0xF, b >> 4, b & 0xF, 0);
            } else {
                b = *np++;
                cur = *np++;
                gSP1Triangle(D_800F22B4++, b >> 4, b & 0xF, cur >> 4, 0);
            }
            cell++;
        }
        p += 6;
    }
}
