#include "common.h"

typedef struct {
    u8 pad0[0xC];
    void *unkC;
    void *unk10;
    u8 pad14[0x18 - 0x14];
    void *unk18;
    void *unk1C;
    void *unk20;
    void *unk24;
    void *unk28;
    void *unk2C;
    void *unk30;
    void *unk34;
    void *unk38;
    u8 pad3C[0x44 - 0x3C];
    void *unk44;
    void *unk48;
    void *unk4C;
    void *unk50;
    void *unk54;
    void *unk58;
    void *unk5C;
    void *unk60;
    void *unk64;
    u8 pad68[0xCC - 0x68];
    void *unkCC;
    void *unkD0;
    void *unkD4;
    void *unkD8;
    void *unkDC;
    void *unkE0;
    u8 padE4[0x13C - 0xE4];
    void *unk13C;
    void *unk140;
    u8 pad144[0x160 - 0x144];
    void *unk160;
    u8 pad164[0x190 - 0x164];
    s16 unk190;
    s16 unk192;
    u16 unk194;
    u8 pad196[0x19A - 0x196];
    s16 unk19A;
    u16 unk19C;
} S103210;

extern S103210 D_80103210;

extern s16 D_800E23B4;
extern s16 D_800E23B8;

void func_80071DC0(void) {
    D_800E23B4 = 0;
    D_800E23B8 = 0xFF;
}

void func_80071DD8(arg0)
short arg0;
{
    D_800E23B8 = arg0;
}

extern s16 D_800E23B4;
extern void *D_800F22B4;

int func_80071DE8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
union { s32 w; u8 b[4]; u16 h[2]; s16 s[2]; s8 c[4]; } arg1;
{
    int i;
    int width;
    int k;
    u8 buf[0x1F];
    u8 str[2];
    int xpos;
    int x;
    int count;
    u8 *p;
    int t;

    buf[0x1E] = 0;
    str[1] = 0;
    if (arg4 & 1) {
        buf[0x1D] = 0x30;
        i = 0x1D;
    } else {
        buf[0x1D] = 0x30;
        i = 0x1E;
        arg0 += 1;
    }
    if (arg0 > 0) {
        while (arg0 > 0) {
            i -= 1;
            buf[i] = (arg0 % 10) + 0x30;
            arg0 = arg0 / 10;
        }
    } else if (!(arg4 & 1)) {
        i -= 1;
        buf[i] = 0x30;
    }
    if ((u8)arg1.h[1] == 0) {
        count = 0x1E - i;
        width = (count * 0xC) + ((count - 1) / 3) * 5 + ((*(s16 *)&count & 1) * 0);
    } else {
        count = 0x1E - (i ^ 0);
        width = (count * 0xB) + ((count - 1) / 3) * 5 + ((*(s16 *)&count & 1) * 0);
    }
    x = width + arg2 + 0xC + ((*(s16 *)&t & 1) * 0);
    if (arg4 & 4) {
        width = 0;
        if (count > 0) { arg9 = 0; p = buf + 0x1E; xpos = arg2; do {
                str[0] = p[-1];
                t = arg9 + 1;
                if (t % 3) {
                    arg9 = arg1.b[3];
                    if (arg9 == 0) {
                        func_80038478(&D_800F22B4, xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        width += 9;
                        xpos -= 9;
                    } else {
                        func_800382B4(&D_800F22B4, arg9 & 0xFF, xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        width += 8;
                        xpos -= 8;
                    }
                } else {
                    if ((u8)arg1.h[1] == 0) {
                        func_80038478(&D_800F22B4, xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        width += 0xE;
                        xpos -= 0xE;
                    } else {
                        func_800382B4(&D_800F22B4, arg1.b[3], xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        width += 0xA;
                        xpos -= 0xA;
                    }
                }
                arg9 = t;
                p -= 1;
            } while (arg9 != count);
        }
    }
    if (arg4 & 8) {
        arg9 = count + ((*(s16 *)&count & 1) * 0);
        k = 1;
        if (count > 0) {
            xpos = width + arg2;
            p = i + arg9 + buf;
            do {
                str[0] = p[-1];
                if (k % 3) {
                    width = arg1.b[3];
                    if (width == 0) {
                        func_80038478(&D_800F22B4, xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        xpos -= 0xA;
                    } else {
                        func_800382B4(&D_800F22B4, width & 0xFF, xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        xpos -= 9;
                    }
                } else {
                    if (arg1.b[3] == 0) {
                        func_80038478(&D_800F22B4, xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        xpos -= 0xF;
                    } else {
                        func_800382B4(&D_800F22B4, (u8)arg1.s[1], xpos, arg3, str, arg5, arg6, arg7, (int) (D_800E23B4 * arg8) / 255);
                        xpos -= 0xB;
                    }
                }
                p -= 1;
            } while (k += 1, --arg9 != 0);
        }
    }
    return x;
}

extern s16 D_800E44A8;
extern u8 *D_8013DD00;
extern void *D_800F22B4;

void func_8007240C(arg0, arg1, arg2, arg3, arg4, arg5, arg6)
s32 arg0;
s32 arg1;
s32 arg2;
s32 arg3;
s32 arg4;
s32 arg5;
s32 arg6;
{
    s32 secs;
    s32 t;
    s32 a;
    u8 buf[9];
    s32 mins;
    s32 hr;

    if ((D_800E44A8 == 2) && (*(s32 *) (D_8013DD00 + 0x2B0C) == 5184000)) {
        secs = 0;
    } else {
        secs = *(s32 *) (D_8013DD00 + 0x2B0C) / 60;
    }
    t = secs - 5184000;
    if (t >= 0) {
        a = t;
    } else {
        a = 5184000 - secs;
    }
    if (a < 216000) {
        secs = 0;
    }
    if (arg0 == 2) {
        mins = secs / 60;
        buf[0] = ((mins / 60) % 10) + 0x30;
        buf[1] = 0x3A;
        buf[7] = 0;
        buf[2] = ((mins % 60) / 10) + 0x30;
        buf[3] = ((mins % 60) % 10) + 0x30;
        buf[4] = 0x3A;
        buf[5] = ((secs % 60) / 10) + 0x30;
        buf[6] = ((secs % 60) % 10) + 0x30;
    }
    if (arg0 == 1) {
        buf[0] = (secs / 60) + 0x30;
        buf[1] = 0x3A;
        buf[4] = 0;
        buf[2] = ((secs % 60) / 10) + 0x30;
        buf[3] = (secs % 10) + 0x30;
    }
    if (arg0 == 0) {
        mins = secs / 60;
        hr = mins / 60;
        buf[0] = (hr / 10) + 0x30;
        buf[1] = (hr % 10) + 0x30;
        buf[2] = 0x3A;
        buf[8] = 0;
        buf[3] = ((mins % 60) / 10) + 0x30;
        buf[4] = ((mins % 60) % 10) + 0x30;
        buf[5] = 0x3A;
        buf[6] = ((secs % 60) / 10) + 0x30;
        buf[7] = ((secs % 60) % 10) + 0x30;
    }
    func_80038478(&D_800F22B4, arg1, arg2, buf, arg3, arg4, arg5, (s32) (D_800E23B4 * arg6) / 255);
}


void func_80072964(arg0, arg1, arg2, arg3, arg4, arg5, arg6)
s16 arg0;
s32 arg1;
s32 arg2;
s32 arg3;
s32 arg4;
s32 arg5;
s32 arg6;
{
    s32 n;
    s32 i;
    u8 buf[12];

    buf[12] = 0;
    n = 12;
    if (!(arg0 < 100) || (arg0 < 0)) {
        arg0 = 99;
    }
    for (i = 0; i < 2; i++) {
        n -= 1;
        buf[n] = (arg0 % 10) + 0x30;
        arg0 = arg0 / 10;
    }
    func_80038478(&D_800F22B4, arg1 - (func_800388BC(buf + n) >> 1), arg2, buf + n, arg3, arg4, arg5, (s32) (D_800E23B4 * arg6) / 255);
}

extern s32 loadAsset(void *, s32, s32);
extern u8 D_7D6C00[];
extern s32 D_801326DC;
extern s32 D_80132E48;
extern s32 D_801335B8;
extern s32 D_80133D24;
extern s32 D_8013448C;
extern s32 D_80134BF4;
extern s32 D_8013178C;
extern s32 D_8013535C;
extern s32 D_80135360;
extern s32 D_80137900;
extern s32 D_80138824;
extern s32 D_80138F8C;
extern s32 D_801396F4;
extern s32 D_80139E5C;
extern s16 D_8015D980;

typedef struct {
    s32 unk0, *unk4, *unk8, *unkC, *unk10, *unk14, *unk18, *unk1C, *unk20, *unk24,
         *unk28, *unk2C, *unk30, *unk34, *unk38, *unk3C, *unk40, *unk44, *unk48, *unk4C;
} S131F28;
extern S131F28 D_80131F28;

typedef struct {
    s32 unk0, *unk4, *unk8, *unkC;
} S1380B0;
extern S1380B0 D_801380B0;

void func_80072A94(void) {
    D_801326DC = loadAsset(D_7D6C00, 0, 0);
    D_80132E48 = loadAsset(D_7D6C00, 1, 0);
    D_801335B8 = loadAsset(D_7D6C00, 2, 0);
    D_80133D24 = loadAsset(D_7D6C00, 3, 0);
    D_8013448C = loadAsset(D_7D6C00, 4, 0);
    D_80134BF4 = loadAsset(D_7D6C00, 5, 0);
    D_8013178C = loadAsset(D_7D6C00, 6, 0);
    D_8013535C = loadAsset(D_7D6C00, 7, 0);
    D_80135360 = loadAsset(D_7D6C00, 8, 0);
    D_80131F28.unk0 = loadAsset(D_7D6C00, 0x11, 0);
    D_80131F28.unk4 = loadAsset(D_7D6C00, 0x12, 0);
    D_80131F28.unk8 = loadAsset(D_7D6C00, 0x13, 0);
    D_80131F28.unkC = loadAsset(D_7D6C00, 0x14, 0);
    D_80131F28.unk10 = loadAsset(D_7D6C00, 0x15, 0);
    D_80131F28.unk14 = loadAsset(D_7D6C00, 0x16, 0);
    D_80131F28.unk18 = loadAsset(D_7D6C00, 0x17, 0);
    D_80131F28.unk1C = loadAsset(D_7D6C00, 0x18, 0);
    D_80131F28.unk20 = loadAsset(D_7D6C00, 0x19, 0);
    D_80131F28.unk24 = loadAsset(D_7D6C00, 0x1A, 0);
    D_80131F28.unk28 = loadAsset(D_7D6C00, 0x1B, 0);
    D_80131F28.unk2C = loadAsset(D_7D6C00, 0x1C, 0);
    D_80131F28.unk30 = loadAsset(D_7D6C00, 0x1D, 0);
    D_80131F28.unk34 = loadAsset(D_7D6C00, 0x1E, 0);
    D_80131F28.unk38 = loadAsset(D_7D6C00, 0x1F, 0);
    D_80131F28.unk3C = loadAsset(D_7D6C00, 0x20, 0);
    D_80131F28.unk40 = loadAsset(D_7D6C00, 0x21, 0);
    D_80131F28.unk44 = loadAsset(D_7D6C00, 0x22, 0);
    D_80131F28.unk48 = loadAsset(D_7D6C00, 0x23, 0);
    D_80131F28.unk4C = loadAsset(D_7D6C00, 0x24, 0);
    D_80137900 = loadAsset(D_7D6C00, 0x25, 0);
    if (D_8015D980 == 2) {
        D_801380B0.unk0 = loadAsset(D_7D6C00, 0x26, 0);
        D_801380B0.unk4 = loadAsset(D_7D6C00, 0x27, 0);
        D_801380B0.unk8 = loadAsset(D_7D6C00, 0x28, 0);
        D_801380B0.unkC = loadAsset(D_7D6C00, 0x29, 0);
        D_80138824 = loadAsset(D_7D6C00, 0x2A, 0);
    }
    D_80138F8C = loadAsset(D_7D6C00, 0x2B, 0);
    D_801396F4 = loadAsset(D_7D6C00, 0x2C, 0);
    D_80139E5C = loadAsset(D_7D6C00, 0x2D, 0);
}

extern u8 *D_8013DD00;
extern u8 D_801033B8[];
extern s16 D_8015D980;
extern s32 D_8013EBDC, D_801317A0;
extern u8 D_7D6C00[];
extern void func_800AF09C(s16);
extern void func_800AE5EC(void);
extern void func_800B903C(void);
extern s32 loadMesh(s32);
extern s32 loadAnim(s32);
extern s32 loadAsset(void *, s32, s32);
void func_80072E10(void) {
    s32 a, b;
    u8 i;
    for (i = 0; i < D_8015D980; i++) {
        func_800AF09C(i);
        func_800AE5EC();
        *(s16 *)(D_8013DD00 + 0x23A8) = 1;
        *(s16 *)(D_8013DD00 + 0x23B0) = 0;
        *(s16 *)(D_8013DD00 + 0x23AE) = 0;
        func_800B903C();
    }
    D_8013EBDC = loadMesh(0x5E);
    a = loadAnim(0x72);
    *(s32 *)(D_801033B8 + 0x1C) = a;
    *(s32 *)(D_801033B8 + 0x20) = a;
    *(s32 *)(D_801033B8 + 0x24) = a;
    b = loadAnim(0x73);
    *(s32 *)(D_801033B8 + 0x28) = b;
    *(s32 *)(D_801033B8 + 0x2C) = b;
    *(s32 *)(D_801033B8 + 0x30) = b;
    D_801317A0 = loadAsset(D_7D6C00, 0x2E, 0);
}

typedef struct Obj2F {
    u8 pad00[0x24];
    s32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 pad30[0x10];
    f32 unk40;
    f32 unk44;
    u8 unk48;
    u8 unk49;
    u8 pad4A[0x226];
    f32 unk270;
} Obj2F;

typedef struct AnimTable2F {
    u8 pad00[0x20];
    s32 unk20, unk24, unk28, unk2C, unk30, unk34, unk38, unk3C;
    s32 unk40, unk44, unk48, unk4C, unk50;
    s32 unk54[6];
    Obj2F *unk6C[6];
    s32 unk84, unk88, unk8C, unk90, unk94, unk98;
} AnimTable2F;

#define TB2F ((AnimTable2F *)D_801033B8)

extern s32 D_800F22C0;
extern s16 D_800E44A8;
extern s32 D_8013FADC;
extern s32 D_8013FAE0;
extern Obj2F *D_8013FAE4;
extern Obj2F *func_8002CF70(s32, s32, s32 *, s32, s32 *);

void func_80072F18(void) {
    s32 sizeA[2];
    s32 sizeB[2];
    Obj2F *obj;
    u8 i;
    u8 j;

    if (D_8015D980 == 2) {
        func_80072E10();
    } else {
        D_8013FADC = loadMesh(0x43);
        D_8013FAE0 = loadAnim(0xC4);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        obj = func_8002CF70(D_800F22C0, D_8013FAE0, &D_8013FADC, 1, sizeA);
        D_8013FAE4 = obj;
        D_800F22C0 += sizeA[0];
        obj->unk48 = 0;
        obj->unk49 = 1;
        obj->unk24 = 0;
        obj->unk2C = 0.0f;
        obj->unk28 = 0.0f;
        obj->unk270 = 33.0f;
        for (i = 0; i < D_8015D980; i++) {
            func_800AF09C(i);
            func_800AE5EC();
            *(s16 *)(D_8013DD00 + 0x23A8) = 1;
            *(s16 *)(D_8013DD00 + 0x23B0) = 0;
            *(s16 *)(D_8013DD00 + 0x23AE) = 0;
            func_800B903C();
        }
        D_8013EBDC = loadMesh(0x14);
        if (D_800E44A8 == 3) {
            TB2F->unk20 = loadAnim(0x132);
        } else {
            TB2F->unk20 = loadAnim(0x82);
        }
        TB2F->unk24 = loadAnim(0x91);
        TB2F->unk28 = loadAnim(0x49);
        TB2F->unk2C = loadAnim(0x4A);
        TB2F->unk30 = loadAnim(0x4B);
        TB2F->unk34 = loadAnim(0x92);
        TB2F->unk38 = loadAnim(0x62);
        TB2F->unk3C = loadAnim(0x49);
        TB2F->unk40 = loadAnim(0x4C);
        TB2F->unk44 = TB2F->unk40;
        TB2F->unk48 = loadAnim(0x55);
        TB2F->unk4C = loadAnim(0x93);
        TB2F->unk50 = loadAnim(0x39);
        if (D_800E44A8 == 3) {
            TB2F->unk54[0] = loadAnim(0x131);
        } else {
            TB2F->unk54[0] = loadAnim(0xD2);
        }
        TB2F->unk54[1] = loadAnim(0xD3);
        TB2F->unk54[2] = loadAnim(0xD4);
        TB2F->unk54[3] = loadAnim(0xD5);
        TB2F->unk54[4] = loadAnim(0xD6);
        TB2F->unk54[5] = loadAnim(0xD7);
        for (j = 0; j < 6; j++) {
            D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
            obj = func_8002CF70(D_800F22C0, TB2F->unk54[j], &D_8013EBDC, 1, sizeB);
            TB2F->unk6C[j] = obj;
            D_800F22C0 += sizeB[0];
            obj->unk40 = 256.0f;
            obj->unk44 = 2048.0f;
        }
        TB2F->unk94 = loadMesh(0x5D);
        TB2F->unk98 = loadAnim(0x71);
        if (D_800E44A8 != 4) {
            TB2F->unk88 = loadMesh(0x49);
            TB2F->unk84 = loadAnim(0xD1);
            TB2F->unk90 = loadMesh(0x47);
            TB2F->unk8C = loadAnim(0xCF);
        }
    }
}

extern u8 D_736C50[];
extern u8 D_80103458[];
extern u8 D_80110220[];
extern u8 D_80103210_s1[];
extern u8 D_80103210_s2[];
extern u8 D_80113488[];
extern u8 D_8010345B[];
extern u8 D_80110222[];
extern u8 D_800EDF70[];
extern u8 D_800EDFBC[];
extern u8 D_800EDFE4[];
extern u8 D_800EE010[];
extern s32 D_800FC5AC;
extern s16 D_80112FCE;
extern s8 D_80113322;
extern s16 D_800E23C0[];
extern u8 *D_80113328;
extern u8 *D_80116590;
extern s16 D_80116236;
extern s32 D_8013DD08;
extern s32 D_8013E474;
extern s16 D_800E44AC;
extern s16 D_800E44A4;
extern void func_80037F9C(void *, s32);
extern void func_80038254(void *);
extern void func_80038284(void *);
extern void func_80029760();

#define GET(off)  (*(s32 *)((u8 *)&D_80103210 + (off)))
#define GETP(off) (*(u8 **)((u8 *)&D_80103210 + (off)))

void func_80073290(void) {
    s32 i;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    u8 *pv0;
    s32 old;

    sp40 = D_800F22C0;
    func_80029760(&D_800EDF70, D_800FC5AC - D_800F22C0, D_800F22C0);
    do { } while (0);
    {
    do { } while (0);
    for (i = 1; i < 0xC9; i++) {
        D_80103458[i * 3] = 0x1E;
        D_80103458[i * 3 + 1] = 0x5F;
        D_80103458[i * 3 + 2] = 0x57;
        sp48 = ((D_80103458[i * 3] << 8) & 0xF800) | ((D_80103458[i * 3 + 1] << 3) & 0x7C0) | ((D_80103458[i * 3 + 2] >> 2) & 0x3E) | 1;
        *(s16 *)(D_80110220 + i * 2 + 0x2DAE) = sp48;
        if (D_8015D980 >= 2) {
            *(s16 *)((u8 *)D_80113488 + i * 2 + 0x2DAE) = sp48;
        }
    }
    D_80112FCE = 0;
    do { } while (0);
    if (D_8015D980 >= 2) {
        *(s16 *)((u8 *)D_80113488 + 0x2DAE) = 0;
    }
    }
    GET(0x144) = D_800F22C0;
    GET(0x0) = loadAsset(D_736C50, 0x16, 8);
    if (D_800E44A8 == 3) {
        GET(0x4) = loadAsset(D_736C50, 0xC2, 8);
    } else {
        GET(0x4) = loadAsset(D_736C50, 0x16, 8);
        {
        sp48 = loadAsset(D_736C50, 0xC2, 8);
        GET(0x8) = sp48;
        func_80037F9C((void *)sp48, 2);
        }
    }
    if ((D_800E44A8 != 4) && (D_800E44A8 != 3) && (D_8015D980 == 1)) {
        GET(0x14) = loadAsset(D_736C50, 0x2A, 8);
        ((s16 *)&D_80112FCE)[*(u8 *)(GETP(0x14) + 9)] = 0;
        GET(0x18) = loadAsset(D_736C50, 0x2C, 8);
        GET(0x1C) = loadAsset(D_736C50, 0x2B, 8);
        GET(0xE0) = loadAsset(D_736C50, 0xC0, 8);
        GET(0xDC) = loadAsset(D_736C50, 0xBF, 8);
        GET(0xC) = loadAsset(D_736C50, 0x27, 8);
        GET(0x40) = loadAsset(D_736C50, 0x31, 8);
        GET(0x4C) = loadAsset(D_736C50, 0xC1, 8);
        GET(0x13C) = loadAsset(D_736C50, 0x28, 8);
        GET(0x44) = loadAsset(D_736C50, 0x67, 8);
        GET(0x8C) = loadAsset(D_736C50, 0xCF, 8);
        GET(0x88) = loadAsset(D_736C50, 0xD0, 8);
        GET(0x84) = loadAsset(D_736C50, 0xD1, 8);
        GET(0x80) = loadAsset(D_736C50, 0xD2, 8);
        GET(0x7C) = loadAsset(D_736C50, 0xD3, 8);
        GET(0x78) = loadAsset(D_736C50, 0xD4, 8);
        GET(0x74) = loadAsset(D_736C50, 0xD5, 8);
        GET(0x70) = loadAsset(D_736C50, 0xD6, 8);
        GET(0x6C) = loadAsset(D_736C50, 0xD7, 8);
        GET(0x68) = loadAsset(D_736C50, 0xD8, 8);
        GET(0x64) = loadAsset(D_736C50, 0xD9, 8);
        GET(0x60) = loadAsset(D_736C50, 0xDA, 8);
        GET(0x5C) = loadAsset(D_736C50, 0xDB, 8);
        GET(0x58) = loadAsset(D_736C50, 0xDC, 8);
        GET(0x54) = loadAsset(D_736C50, 0xDD, 8);
        GET(0xCC) = loadAsset(D_736C50, 0x74, 8);
        for (i = 0; i < 0x14; i++) {
            GET(i * 4 + 0xE4) = loadAsset(D_736C50, i + 0xFC, 8);
        }
        GET(0x134) = loadAsset(D_736C50, 0x62, 8);
        GET(0x138) = loadAsset(D_736C50, 0x11, 8);
        switch (D_800E44A8) {
        case 5:
            if (D_800E44A4 == 3) {
                GET(0xD8) = loadAsset(D_736C50, 0x8A, 8);
            } else {
                GET(0xD8) = loadAsset(D_736C50, 0xBE, 8);
            }
            GET(0xD0) = loadAsset(D_736C50, 0xCC, 8);
            GET(0xD4) = loadAsset(D_736C50, 0xCE, 8);
            break;
        case 10:
            GET(0x10) = loadAsset(D_736C50, D_800E23C0[D_80113322], 8);
            GET(0xD8) = loadAsset(D_736C50, 0xC5, 8);
            break;
        case 1:
            GET(0x10) = loadAsset(D_736C50, 0x64, 8);
            GET(0xD8) = loadAsset(D_736C50, 0x35, 8);
            break;
        case 12:
            GET(0x10) = loadAsset(D_736C50, 0xA1, 8);
            GET(0xD8) = loadAsset(D_736C50, 0xA2, 8);
            break;
        case 2:
            GET(0x10) = loadAsset(D_736C50, 0x38, 8);
            GET(0xD8) = loadAsset(D_736C50, 0x37, 8);
            break;
        default:
            GET(0x10) = loadAsset(D_736C50, 0x26, 8);
            GET(0xD8) = loadAsset(D_736C50, 0x35, 8);
            break;
        }
    }
    if (D_800E44A8 == 3) {
        GET(0x20) = loadAsset(D_736C50, 0x91, 8);
        GET(0x24) = loadAsset(D_736C50, 0x93, 8);
        GET(0x28) = loadAsset(D_736C50, 8, 8);
        GET(0x2C) = loadAsset(D_736C50, 9, 8);
        GET(0x30) = loadAsset(D_736C50, 0xA, 8);
        GET(0x34) = loadAsset(D_736C50, 0xB, 8);
        GET(0x38) = loadAsset(D_736C50, 0x92, 8);
        GET(0x160) = loadAsset(D_736C50, 0xA4, 8);
        GET(0x164) = loadAsset(D_736C50, 0xCA, 8);
        GET(0x170) = loadAsset(D_736C50, 0xA5, 8);
        GET(0x174) = loadAsset(D_736C50, 0xC6, 8);
        GET(0x168) = loadAsset(D_736C50, 0xC7, 8);
        GET(0x16C) = loadAsset(D_736C50, 0xC8, 8);
        GET(0x178) = loadAsset(D_736C50, 0xA6, 8);
        sp48 = loadAnim(0x38);
        sp44 = loadMesh(0x13);
        D_800F22C0 = (D_800F22C0 + 0xF) & ~0xF;
        *(s32 *)((u8 *)&D_801033B8 + 8) = (s32) func_8002CF70(D_800F22C0, sp48, &sp44, 1, &i);
        *(s16 *)((u8 *)&D_801033B8 + 0xC) = 0;
        D_800F22C0 += i;
    }
    if ((D_8015D980 >= 2) || (D_800E44A8 == 3)) {
        for (i = 0; i < 0x14; i++) {
            GET(i * 4 + 0xE4) = loadAsset(D_736C50, i + 0xFC, 8);
        }
        GET(0x134) = loadAsset(D_736C50, 0x62, 8);
        GET(0x138) = loadAsset(D_736C50, 0x11, 8);
        GET(0x44) = loadAsset(D_736C50, 0x7A, 8);
        GET(0x4C) = loadAsset(D_736C50, 0x60, 8);
        GET(0x14) = loadAsset(D_736C50, 0x7C, 8);
        GET(0x18) = loadAsset(D_736C50, 0x7D, 8);
        GET(0xCC) = loadAsset(D_736C50, 0x7E, 8);
        if ((D_800E44A8 == 3) && (D_800E44AC == 3)) {
            GET(0x1C) = loadAsset(D_736C50, 0x3E, 8);
            GET(0xE0) = loadAsset(D_736C50, 0x29, 8);
            GET(0xD8) = loadAsset(D_736C50, 0x3F, 8);
        } else {
            GET(0x1C) = loadAsset(D_736C50, 0x2B, 8);
            GET(0xE0) = loadAsset(D_736C50, 0xC0, 8);
        }
        if (D_800E44A8 != 3) {
            GET(0x10) = loadAsset(D_736C50, 0x2D, 8);
            GET(0xD8) = loadAsset(D_736C50, 0x2E, 8);
            GET(0x13C) = loadAsset(D_736C50, 0x117, 8);
            GET(0x48) = loadAsset(D_736C50, 0x5F, 8);
            GET(0x50) = loadAsset(D_736C50, 0x61, 8);
        }
        GET(0x78) = loadAsset(D_736C50, 0xDE, 8);
        GET(0x74) = loadAsset(D_736C50, 0xDF, 8);
        GET(0x70) = loadAsset(D_736C50, 0xE0, 8);
        GET(0x6C) = loadAsset(D_736C50, 0xE1, 8);
        GET(0x68) = loadAsset(D_736C50, 0xE2, 8);
        GET(0x64) = loadAsset(D_736C50, 0xE3, 8);
        GET(0x60) = loadAsset(D_736C50, 0xE4, 8);
        GET(0x5C) = loadAsset(D_736C50, 0xE5, 8);
        GET(0x58) = loadAsset(D_736C50, 0xE6, 8);
        GET(0x54) = loadAsset(D_736C50, 0xE7, 8);
        GET(0xA0) = loadAsset(D_736C50, 0xED, 8);
        GET(0x9C) = loadAsset(D_736C50, 0xEE, 8);
        GET(0x98) = loadAsset(D_736C50, 0xEF, 8);
        GET(0x94) = loadAsset(D_736C50, 0xF0, 8);
        GET(0x90) = loadAsset(D_736C50, 0xF1, 8);
        GET(0x8C) = loadAsset(D_736C50, 0xF2, 8);
        GET(0x88) = loadAsset(D_736C50, 0xF3, 8);
        GET(0x84) = loadAsset(D_736C50, 0xF4, 8);
        GET(0x80) = loadAsset(D_736C50, 0xF5, 8);
        GET(0x7C) = loadAsset(D_736C50, 0xF6, 8);
        ((s16 *)&D_80112FCE)[*(u8 *)(GETP(0x14) + 9)] = 0;
        if (D_8015D980 >= 2) {
            GET(0x140) = loadAsset(D_736C50, 0xF, 8);
            {
            old = 0;
            *(s16 *)((u8 *)&D_80116236 + *(u8 *)(GETP(0x14) + 9) * 2) = 0;
            sp48 = 0;
            for (i = 0; i < 9; i++) {
                sp48 += 1;
                D_80103210_s1[sp48 + 0x17B] = D_80113328[old];
                if (D_80103210_s1[sp48 + 0x17B] == 0) {
                    *(s8 *)((u8 *)&D_80103210 + 0x185) = (s8) i;
                    break;
                }
                old += 1;
            }
            i = 0;
            pv0 = D_80116590;
            sp48 = 0;
            do {
                sp48 += 1;
                D_80103210_s2[sp48 + 0x185] = *pv0;
                if (D_80103210_s2[sp48 + 0x185] == 0) {
                    *(s8 *)((u8 *)&D_80103210 + 0x18F) = (s8) i;
                    break;
                }
                pv0 += 1;
                i += 1 + ((s32) pv0 * 0);
            } while (i < 9);
            }
        }
    } else {
        GET(0x160) = loadAsset(D_736C50, 0x79, 8);
        GET(0x164) = loadAsset(D_736C50, 0xCA, 8);
    }
    if (D_800E44A8 == 4) {
        GET(0x10) = loadAsset(D_736C50, 0x75, 8);
        GET(0xD8) = loadAsset(D_736C50, 0x36, 8);
        GET(0xC) = loadAsset(D_736C50, 0x27, 8);
        GET(0x54) = loadAsset(D_736C50, 0x68, 8);
        GET(0x58) = loadAsset(D_736C50, 0x69, 8);
        GET(0x5C) = loadAsset(D_736C50, 0x63, 8);
        GET(0x60) = loadAsset(D_736C50, 0x6A, 8);
        GET(0x64) = loadAsset(D_736C50, 0x6B, 8);
        for (i = 0; i < 0x14; i++) {
            GET(i * 4 + 0xE4) = loadAsset(D_736C50, i + 0xFC, 8);
        }
        GET(0x134) = loadAsset(D_736C50, 0x62, 8);
        GET(0x138) = loadAsset(D_736C50, 0x11, 8);
    } else {
        GET(0x148) = loadAsset(D_736C50, 0x3B, 8);
        GET(0x14C) = loadAsset(D_736C50, 0x3C, 8);
        GET(0x150) = loadAsset(D_736C50, 0x3D, 8);
        GET(0x154) = loadAsset(D_736C50, 0x41, 8);
        GET(0x158) = loadAsset(D_736C50, 0x44, 8);
    }
    func_80038254((void *) GET(0x0));
    func_80038284((void *) GET(0x4));
    func_80029760(&D_800EDFBC, D_800F22C0 - sp40);
    {
    old = D_800F22C0;
    func_80072A94();
    func_80072F18();
    sp48 = D_800F22C0;
    D_8013E474 = sp48;
    D_8013DD08 = D_8013E474;
    func_80029760(&D_800EDFE4, sp48 - old);
    }
    func_80029760(&D_800EE010, D_800F22C0 - sp40, D_800F22C0);
}

extern void *D_800F22B4;
extern void func_8003396C(void *, void *, s32, s32, s32, s32, s32, s32);
extern s32 D_800E23D0;
extern s16 D_800E23D4;
extern u16 D_800E23D8;
extern u16 D_800E23DC;

void func_800740C4(void) {
    s32 var_s0;
    void *temp_v1;

    if (D_800E23DC-- == 0) {
        D_800E23D8 ^= 0x7F;
        D_800E23DC = 2;
    }
    if ((s32) *(u16 *) &D_800E23D4 > 0) {
        var_s0 = 0; do {
            temp_v1 = (void *) (D_800E23D0 + var_s0);
            switch (*(u16 *) ((u8 *) temp_v1 + 4)) {
            case 0:
                func_8003396C(&D_800F22B4, *(void **) ((u8 *) &D_80103210 + 0x170), *(u16 *) temp_v1, *(u16 *) ((u8 *) temp_v1 + 2), (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23B4);
                break;
            case 1:
                func_8003396C(&D_800F22B4, *(void **) ((u8 *) &D_80103210 + 0x168), *(u16 *) temp_v1, *(u16 *) ((u8 *) temp_v1 + 2), (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23B4);
                break;
            case 2:
                func_8003396C(&D_800F22B4, *(void **) ((u8 *) &D_80103210 + 0x174), *(u16 *) temp_v1, *(u16 *) ((u8 *) temp_v1 + 2), (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23B4);
                break;
            case 3:
                func_8003396C(&D_800F22B4, *(void **) ((u8 *) &D_80103210 + 0x16C), *(u16 *) temp_v1, *(u16 *) ((u8 *) temp_v1 + 2), (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23D8, (s32) D_800E23B4);
                break;
            }
            var_s0 += 6;
        } while (var_s0 < *(u16 *) &D_800E23D4 * 6);
    }
}

extern u16 D_800E23E4;
extern u16 D_800E23E8;

void func_80074308(void) {
    D_800E23E8 = D_800E23E4;
}

extern s32 D_80103958;
extern s32 D_80103968[];

void func_8007431C(void) {
    D_80103968[D_800E23E4] = D_80103958;
    D_800E23E4 = (D_800E23E4 + 1) & 0xF;
    if (D_800E23E8 == D_800E23E4) {
        D_800E23E8 = (D_800E23E8 + 1) & 0xF;
    }
}

void func_80074374(void) {
    if (D_800E23E4 != D_800E23E8) {
        D_800E23E4 = (D_800E23E4 - 1) & 0xF;
        D_80103958 = D_80103968[D_800E23E4];
    }
}

typedef struct { u8 bytes[0]; } E743;
extern void func_800384E4();
extern s32 func_800388F4(u8 *);
extern void func_80074308();
extern s32 D_80103958;
extern u8 *D_8010395C;
extern u8 *D_80103960;
extern u16 D_801039A8;
extern s32 D_800E23D0;
extern s16 D_800E23D4;
extern u16 D_800E23EC;
extern u16 D_800E23F0;
extern s16 D_800E44A8;
extern s32 D_8013D25C;
extern s32 D_80103374;
extern s32 D_80103388;

void func_800743BC(arg0, arg1, arg2, arg3, arg4)
s32 arg0;
s32 arg1;
s32 arg2;
volatile s32 arg3;
s32 arg4;
{
    s32 x;
    s32 y;
    s32 r;
    s32 g;
    s32 b;
    s32 ch;
    s32 a1;
    s32 a2;
    s32 ynext;
    s32 xw;
    u8 *base;
    u8 buf1[0x100];
    u8 buf2[0x100];
    u8 *p;
    s32 ymax;

    D_801039A8 = 0;
    D_800E23F0 = 0;
    x = arg0;
    y = arg1;
    ynext = arg1;
    xw = arg0;
    arg1 = *(u16 *)&D_80103958 * 0;
    if ((u8 *)D_80103958 == NULL) {
        D_80103958 = D_8013D25C;
        func_80074308();
    }
    if ((u8 *)D_80103958 != NULL) {
        p = &((u8 *)D_80103958)[arg1];
        if ((u8 *)D_80103960 == NULL) {
            D_80103960 = (u8 *)D_80103958;
        }
        base = (u8 *)D_80103958;
        if (*base != 0) {
            *(volatile E743 *)0 = *(volatile E743 *)base;
            do {
                r = 0xE6;
                g = 0x61;
                b = 0x1E;
                a1 = 0;
                a2 = 0;
                if ((*p != 0) && (*p != 0x20)) {
                    ch = *p;
loop_9:
                    if (ch == 0x2D) {
                        ch = p[1];
                        ch = (u16)ch;
                        arg1 += 1;
                        p += 1;
                        if ((0x30 - ch) == 0) {
                            buf1[a1] = 0;
                            buf2[a1] = 0;
                            xw = (arg0 - func_800388F4(buf2)) - 6;
                            if (D_800E44A8 == 3) {
                                ynext = y + 0x12;
                            } else {
                                ynext = y + 0x13;
                            }
                            goto block_38;
                        }
                        if ((s32)(u64)(u32)(0x31 - ch) == 0) {
                            arg1 += 1;
                            p += 1;
                            r = 0xFF;
                            g = 0xDC;
                            b = 0x3E;
                            goto block_36;
                        }
                        if ((s32)(u64)(u32)(0x32 - ch) == 0) {
                            p = p + 1;
                            D_801039A8 = 1;
                            goto tail;
                        } else {
                            if ((0x33 - (s32)(u64)(u32)ch) == 0) {
                                arg1 += 1;
                                p += 1;
                                if ((arg4 == 0) && (D_800E23D0 != 0)) {
                                    D_800E23D4 = *(u16 *)&D_800E23D4 + 1;
                                }
                                goto block_36;
                            }
                            if ((s32)(u64)(u32)(0x34 - ch) == 0) {
                                arg1 += 1;
                                p += 1;
                                if ((arg4 == 0) && (D_800E23D0 != 0) && (*(u16 *)&D_800E23D4 != 0)) {
                                    D_800E23D4 = *(u16 *)&D_800E23D4 - 1;
                                    D_800E23D0 += 6;
                                }
                                goto block_36;
                            }
                            arg1 -= 1;
                            ch = ch + (s32)p * 0;
                            if (ch == 0x35) {
                                D_800E23F0 = 1;
                                p = p + 1;
                                D_801039A8 = 1;
                                goto tail;
                            } else {
                                p -= 1;
                                goto block_31;
                            }
                        }
                    } else {
block_31:
                        arg1 += 1;
                        if ((u32)D_80103960 >= (u32)p) {
                            buf1[a1] = *p;
                            a1 += 1;
                        }
                        if (a1 != 0) {
                            buf2[a2] = *p;
                            a2 += 1;
                        }
                        p += 1;
block_36:
                        if (*p != 0) {
                            ch = *p;
                            if ((s32)(u64)(u32)(0x20 - ch) != 0) {
                                goto loop_9;
                            }
                        }
                        goto block_38;
                    }
                }
block_38:
                ((volatile u8 *)buf1)[a1] = 0;
block_39:
                ((volatile u8 *)buf2)[a2] = 0;
                ymax = arg3 - 8;
                if (*p != 0) {
                    arg1 += 1;
                    p += 1;
                } else {
                    D_801039A8 = 1;
                }
                a1 = func_800388F4(buf2);
                xw = xw + a1;
                if (arg2 < xw) {
                    x = arg0;
                    if (*p == 0x20) {
                        do {
                            arg1 += 1;
                            p += 1;
                        } while (*p == 0x20);
                    }
                    xw = func_800388F4(buf2) + arg0;
                    if (D_800E44A8 == 3) {
                        y += 0xC;
                    } else {
                        y += 0xF;
                    }
                    ynext = y;
                    if (ymax < y) {
                        arg1 -= 1;
                        p -= 1;
                        if (p[-1] != 0x20) {
                            do {
                                arg1 -= 1;
                                p -= 1;
                            } while (p[-1] != 0x20);
                        }
                        break;
                    }
                }
                if (arg4 != 0) {
                    func_800384E4(&D_800F22B4, x, y, buf1, r, g, b, arg4);
                }
                xw = xw + 6;
                x = xw;
                y = ynext;
                if (ymax < ynext) {
                    break;
                }
            } while (*p != 0);
        }
block_59:
        p = &base[arg1];
tail:
        D_8010395C = p;
        if ((arg4 != 0) && (*(u8 *)D_8010395C != 0) && (D_800E23EC != 0)) {
            if (D_800E23F0 != 0) {
                func_8003396C(&D_800F22B4, (void *)D_80103388, ((s32)(arg0 + arg2) / 2) - 0x1C, arg3 + 6, 0xFF, 0xFF, 0xFF, arg4);
            } else {
                if (D_800E44A8 == 3) {
                    func_8003396C(&D_800F22B4, (void *)D_80103374, ((s32)(arg0 + arg2) / 2) - 0x1B, arg3 + 5, 0xFF, 0xFF, 0xFF, arg4);
                } else {
                    func_8003396C(&D_800F22B4, (void *)D_80103374, ((s32)(arg0 + arg2) / 2) - 0x19, arg3 + 0x10, 0xFF, 0xFF, 0xFF, arg4);
                }
            }
        }
        if (D_80103960 < D_8010395C) {
            D_80103960 += 1;
            while (((*(u8 *)D_80103960) == 0x20) || ((*(u8 *)D_80103960) == 0x2D)) {
                if ((*(u8 *)D_80103960) == 0x2D) {
                    D_80103960 = D_80103960 + 2 + (s32)D_80103960 * 0;
                } else {
                    D_80103960 = D_80103960 + 1 + (s32)D_80103960 * 0;
                }
            }
        }
        if (D_8010395C < D_80103960) {
            D_80103960 = D_8010395C;
        }

    }
}

extern void func_800743BC(s32, s32, s32, s32, s32);
extern s16 D_800E23D4;

void func_80074AC8(void) {
    D_800E23D4 = 0;
    func_800743BC(0xA0, 0x13, 0x128, 0x6E, 0);
}

extern u8 *D_8010395C;
extern u8 *D_80103960;
extern u16 D_801039A8;

u16 func_80074B00(void) {
    D_80103958 = (s32)D_8010395C;
    D_80103960 = (u8 *)D_80103958;
    func_800743BC(0xA0, 0x13, 0x128, 0x6E, 0);
    return D_801039A8;
}


extern u8 D_800E44FC;
extern s16 D_80160C64;
extern void *D_800F22B4;

extern void func_800338B0(void *);
extern void func_800335F0(void *);
extern void func_8006FA28(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_8003396C(void *, void *, s32, s32, s32, s32, s32, s32);
extern void func_800743BC(s32, s32, s32, s32, s32);
extern void func_80071DD8(s32);

void func_80074B50(void) {
    s32 speed;

    if (D_800E44FC == 0) {
        D_80103210.unk192 = 0;
    }
    if (D_80160C64 != 0) {
        speed = D_80160C64;
    } else {
        speed = 1;
    }
    if (D_80103210.unk192 < D_80103210.unk190) {
        D_80103210.unk190 = D_80103210.unk190 - speed * 8;
        if (D_80103210.unk190 < D_80103210.unk192) {
            D_80103210.unk190 = D_80103210.unk192;
        }
    }
    if (D_80103210.unk190 < D_80103210.unk192) {
        D_80103210.unk190 = D_80103210.unk190 + speed * 8;
        if (D_80103210.unk192 < D_80103210.unk190) {
            D_80103210.unk190 = D_80103210.unk192;
        }
    }
    if (D_80103210.unk190 > 0) {
        func_800338B0(&D_800F22B4);
        func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, D_80103210.unk190 / 2);
        func_800335F0(&D_800F22B4);
        func_8003396C(&D_800F22B4, D_80103210.unk160, 0x3A, 0x2B, 0xFF, 0xFF, 0xFF, D_80103210.unk190);
        func_800743BC(0x46, 0x32, 0xED, 0xAA, D_80103210.unk190);
    } else {
        D_80103210.unk19C = 0;
        func_80071DD8(0xFF);
    }
}

extern u8 D_800E22E0[];
void func_80074CD0(u16 arg0) {
    s32 v = arg0;
    if (v & 0x8000) *(u16 *)(D_800E22E0 + 0x46) = 0xFF;
    if (v & 0x4000) *(u16 *)(D_800E22E0 + 0x3A) = 0xFF;
    if (v & 0x200)  *(u16 *)(D_800E22E0 + 0xA)  = 0xFF;
    if (v & 0x100)  *(u16 *)(D_800E22E0 + 0x22) = 0xFF;
    if (v & 0x800)  *(u16 *)(D_800E22E0 + 0x2E) = 0xFF;
    if (v & 0x400)  *(u16 *)(D_800E22E0 + 0x16) = 0xFF;
    if (*(u16 *)(D_800E22E0 + 0x46) > 0) *(u16 *)(D_800E22E0 + 0x46) -= 0xF;
    if (*(u16 *)(D_800E22E0 + 0x3A) > 0) *(u16 *)(D_800E22E0 + 0x3A) -= 0xF;
    if (*(u16 *)(D_800E22E0 + 0xA)  > 0) *(u16 *)(D_800E22E0 + 0xA)  -= 0xF;
    if (*(u16 *)(D_800E22E0 + 0x22) > 0) *(u16 *)(D_800E22E0 + 0x22) -= 0xF;
    if (*(u16 *)(D_800E22E0 + 0x2E) > 0) *(u16 *)(D_800E22E0 + 0x2E) -= 0xF;
    if (*(u16 *)(D_800E22E0 + 0x16) > 0) *(u16 *)(D_800E22E0 + 0x16) -= 0xF;
}

extern u8 D_800E23E0;
extern u16 D_801033AC;
extern s16 D_801039AA;
extern s16 D_801039AC;
extern s16 D_801039AE;
extern s16 D_801039B0;
extern s32 D_801039B4;
extern s32 D_801039B8;
extern s32 D_801039BC;
extern s32 D_801039C0;

void func_80074DBC(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
s32 arg0;
s32 arg1;
s32 arg2;
u8 arg3;
s32 arg4;
s32 arg5;
s32 arg6;
s32 arg7;
s32 arg8;
s32 arg9;
s32 arg10;
s32 arg11;
{
    s32 t;

    if (D_800E23E0 == 1) {
        D_801039AA = arg8;
        D_801039AC = arg9;
        D_801039B0 = arg11;
        D_801039AE = arg10;
        D_801039B4 = (arg4 - arg8) / 10;
        D_801039B8 = (arg5 - arg9) / 10;
        D_801039BC = (arg6 - arg10) / 10;
        D_801039C0 = (arg7 - arg11) / 10;
        D_800E23E0 = 2;
    }
    if (D_800E23E0 == 2) {
        t = D_801039AE + D_801039BC;
        if (t < arg6) {
            D_801039AA += D_801039B4;
            D_801039AC += D_801039B8;
            D_801039AE = t;
            D_801039B0 += D_801039C0;
        } else if ((D_801033AC == 0) && (arg3 & 1)) {
            D_800E23E0 = 0;
        } else {
            D_800E23E0 = 3;
        }
    }
    if (D_800E23E0 == 3) {
        t = D_801039AE - D_801039BC;
        if (arg10 < t) {
            D_801039AA -= D_801039B4;
            D_801039AC -= D_801039B8;
            D_801039AE = t;
            D_801039B0 -= D_801039C0;
        } else if ((D_801033AC == 0) && (arg3 & 2)) {
            D_800E23E0 = 0;
        } else {
            D_800E23E0 = 2;
        }
    }
    func_80038478(&D_800F22B4, arg1, arg2, (u8 *) arg0, D_801039AA, D_801039AC, D_801039AE, D_801039B0);
}

/* func_800750C8 @ ROM 0x50478 -- FULL MATCH 2026-07-30.
 * Mechanism notes: pending/session_c750_reopen/ (REOPEN_S2.md, ORACLE_S3.md, S4 addendum).
 * Needs Makefile OPT_FLAGS += -Wo,-loopunroll,1 for this TU and linker alias
 * D_80110220_2 = 0x80110220 (undefined_syms.txt). The four (u64)/(s64) cast hops
 * are zero-emission ugen pool-FIFO advances (as1 deletes the move/li records);
 * each must stay expression-DISTINCT or CSE mints a colored web. */
/* candA: byte-run 0x9B/0x6B delivered through an s32 local so uopt copy-prop
 * substitutes an (Idt,155)/(Idt,107) constant into the byte store.
 * constinreg: Idt/Kdt under 32-bit -> false at ANY optype -> no liveunit -> remat,
 * positive materialisation, and un-merged from loop2's (Ldt,155). */
extern u8 D_80110220[];
extern u8 D_80110220_2[];
extern u8 D_8011025C[];
extern u8 D_80113488[];
extern u8 D_80113494[];
extern u8 D_801134C4[];
extern u8 D_8011643A, D_8011643B, D_8011643C, D_8011643D, D_8011643E, D_8011643F;
extern u8 D_80116440, D_80116441, D_80116442, D_80116443, D_80116444, D_80116445;
extern s16 D_8015D980;

void func_800750C8(void) {
    u8 *p;
    s32 n;
    s32 m;
    u32 g;

    g = (u32)D_8011025C;
    D_80110220[0x2DA8] = 0;
    D_80110220[0x2D9F] = 0;
    D_80110220[0x2DA0] = 0x96;
    D_80110220[0x2DA1] = 0xC8;
    D_80110220[0x2DA2] = 0xFF;
    D_80110220[0x2DA3] = 0xF0;
    D_80110220[0x2DA4] = 0;
    ((u8*)(unsigned long long)(u32)D_80110220)[0x2DA5] = 0xC8;
    D_80110220[0x2DA6] = 0x28;
    D_80110220[0x2DA7] = 0;
    D_80110220[0x2D96] = 0;
    D_80110220[0x2D97] = 0x4B;
    D_80110220[0x2D98] = 0x64;
    D_80110220[0x2D99] = 0x64;
    D_80110220[0x2D9A] = 0x5F;
    D_80110220[0x2D9B] = 0;
    D_80110220[0x2D9C] = 0x64;
    D_80110220[0x2D9D] = 0x14;
    D_80110220[0x2D9E] = 0;
    D_80110220[0x2D93] = 0;
    D_80110220[0x2D94] = 0x4B;
    D_80110220[0x2D95] = 0x64;
    D_80110220[0x2D90] = 0;
    D_80110220[0x2D91] = 0x96;
    D_80110220[0x2D92] = 0xC8;
    D_80110220[0x2DAC] = 0;
    *(u32 *)&D_80110220[0x2FF0] = 0;
    *(u32 *)&D_80110220[0x2FF4] = 0;
    D_80110220[0x2FAE] = 0;
    D_80110220[0x2FF8] = 0x2F;
    D_80110220[0x2FF9] = 0x78;
    D_80110220[0x2FFA] = 0x86;
    D_80110220[0x2FFB] = 0x64;

    p = (u8 *)D_80110220_2; do {
        p += 4;
        p[0x2FAE] = 0x2F;
        p[0x2FAF] = 0x78;
        p[0x2FB0] = 0x86;
        p[0x2FB1] = 0x64;
    } while ((u32)(unsigned long long)(u32)p < (u32)D_8011025C);

    n = 0x9B;
    m = 0x6B;
    if (D_8015D980 >= 2) {
        D_80113488[0x2DA8] = 0;
        D_80113488[0x2D9F] = 0;
        D_80113488[0x2DA0] = 0x96;
        D_80113488[0x2DA1] = 0xC8;
        D_80113488[0x2DA2] = 0xFF;
        D_80113488[0x2DA3] = 0xF0;
        D_80113488[0x2DA4] = 0;
        ((u8*)(unsigned long long)(u32)D_80113488)[0x2DA5] = 0xC8;
        D_80113488[0x2DA6] = 0x28;
        D_80113488[0x2DA7] = 0;
        D_80113488[0x2D96] = 0;
        D_80113488[0x2D97] = 0x4B;
        D_80113488[0x2D98] = 0x64;
        D_80113488[0x2D99] = 0x64;
        D_80113488[0x2D9A] = 0x5F;
        D_80113488[0x2D9B] = 0;
        D_80113488[0x2D9C] = 0x64;
        D_80113488[0x2D9D] = 0x14;
        D_80113488[0x2D9E] = 0;
        D_80113488[0x2D93] = 0;
        D_80113488[0x2D94] = 0x4B;
        D_80113488[0x2D95] = 0x64;
        D_80113488[0x2D90] = 0;
        D_80113488[0x2D91] = 0x96;
        D_80113488[0x2D92] = 0xC8;
        D_80113488[0x2DAC] = 0;
        *(u32 *)&D_80113488[0x2FF0] = 0;
        *(u32 *)&((u8*)(long long)(s32)D_80113488)[0x2FF4] = 0;
        D_80113488[0x2FAE] = 0;
        D_80113488[0x2FF8] = 0x2F;
        D_80113488[0x2FF9] = 0x78;
        D_80113488[0x2FFA] = 0x86;
        D_80113488[0x2FFB] = 0x64;

        do {
        D_8011643A = n;
        D_8011643B = m;
        D_8011643C = n;
        D_8011643D = 0x64;
        D_8011643E = n;
        D_8011643F = m;
        D_80116440 = n;
        D_80116441 = 0x64;
        D_80116442 = n;
        D_80116443 = m;
        D_80116444 = n;
        } while (0);

        do {
        p = (u8 *)D_80113494; D_80116445 = 0x64; do {
            p += 0x10;
            p[0x2FA6] = 0x9B;
            p[0x2FA7] = 0x6B;
            p[0x2FA8] = 0x9B;
            p[0x2FA9] = 0x64;
            p[0x2FAA] = 0x9B;
            p[0x2FAB] = 0x6B;
            p[0x2FAC] = 0x9B;
            p[0x2FAD] = 0x64;
            p[0x2FAE] = 0x9B;
            p[0x2FAF] = 0x6B;
            p[0x2FB0] = 0x9B;
            p[0x2FB1] = 0x64;
            p[0x2FA2] = 0x9B;
            p[0x2FA3] = 0x6B;
            p[0x2FA4] = 0x9B;
            p[0x2FA5] = 0x64;
        } while (p != (u8 *)D_801134C4);
        } while (0);
    }
}


extern u8 D_800E23F8[];
extern u8 D_800E2418[];
extern u32 D_800E241C;
extern s32 D_800E2420;
extern u16 D_800E2424;
extern u16 D_800E2428;
extern s16 D_800E44A8;
extern u8 D_801039C8[];
extern u8 D_80110220[];
extern u8 D_80113488[];

void func_80075350(void) {
    u8 *d;
    u8 *s;
    s32 i;

    i = 0;
    d = D_801039C8; s = D_800E23F8; do {
        *d++ = *s++;
    } while (s < D_800E2418);

    if (D_8015D980 >= 2 || D_800E44A8 == 3) {
        if (D_800E44A8 == 3) {
            *(u32 *)&D_80110220[0x3000] = 0x8C;
            *(u32 *)&D_80110220[0x3020] = 0x8C;
            *(u32 *)&D_80110220[0x3040] = 0x8C;
            *(u32 *)&D_80110220[0x3004] = 0xCD;
            *(u32 *)&D_80110220[0x3024] = 0xBE;
            *(u32 *)&D_80110220[0x3044] = 0xAF;
        } else {
            *(u32 *)&D_80110220[0x3000] = 0x78;
            *(u32 *)&D_80110220[0x3004] = 0xCD;
            *(u32 *)&D_80110220[0x3020] = 0x78;
            *(u32 *)&D_80110220[0x3024] = 0xBE;
            *(u32 *)&D_80110220[0x3040] = 0x78;
            *(u32 *)&D_80110220[0x3044] = 0xAF;
            *(u32 *)&D_80110220[0x3080] = 0x72;
            *(u32 *)&D_80110220[0x3084] = 0xCD;
            *(u32 *)&D_80110220[0x30A0] = 0x61;
            *(u32 *)&D_80110220[0x30A4] = 0xCD;
            *(u32 *)&D_80110220[0x30C0] = 0x50;
            *(u32 *)&D_80110220[0x30C4] = 0xCD;
            *(u32 *)&D_80113488[0x3000] = 0xBE;
            *(u32 *)&D_80113488[0x3004] = 0xCD;
            *(u32 *)&D_80113488[0x3020] = 0xBE;
            *(u32 *)&D_80113488[0x3024] = 0xBE;
            *(u32 *)&D_80113488[0x3040] = 0xBE;
            *(u32 *)&D_80113488[0x3044] = 0xAF;
            *(u32 *)&D_80113488[0x3080] = 0xFC;
            *(u32 *)&D_80113488[0x3084] = 0xCD;
            *(u32 *)&D_80113488[0x30A0] = 0xEB;
            *(u32 *)&D_80113488[0x30A4] = 0xCD;
            *(u32 *)&D_80113488[0x30C0] = 0xDA;
            *(u32 *)&D_80113488[0x30C4] = 0xCD;
        }
    } else {
        if (D_800E44A8 == 2) {
            *(u32 *)&D_80110220[0x3000] = 0x23;
            *(u32 *)&D_80110220[0x3004] = 0x59;
            *(u32 *)&D_80110220[0x3020] = 0x32;
            *(u32 *)&D_80110220[0x3024] = 0x59;
            *(u32 *)&D_80110220[0x3040] = 0x41;
            *(u32 *)&D_80110220[0x3044] = 0x59;
        } else {
            *(u32 *)&D_80110220[0x3000] = 0x23;
            *(u32 *)&D_80110220[0x3004] = 0x4F;
            *(u32 *)&D_80110220[0x3020] = 0x32;
            *(u32 *)&D_80110220[0x3024] = 0x4F;
            *(u32 *)&D_80110220[0x3040] = 0x41;
            *(u32 *)&D_80110220[0x3044] = 0x4F;
        }
        *(u32 *)&D_80110220[0x3080] = 0x11B;
        *(u32 *)&D_80110220[0x30A0] = 0x11B;
        *(u32 *)&D_80110220[0x30C0] = 0x11B;
        *(u32 *)&D_80110220[0x30E0] = 0x11B;
        *(u32 *)&D_80110220[0x3084] = 0x42;
        *(u32 *)&D_80110220[0x30A4] = 0x58;
        *(u32 *)&D_80110220[0x30C4] = 0x6E;
        *(u32 *)&D_80110220[0x30E4] = 0x84;
    }

    if (*(s16 *)&D_80110220[0x2D7E] > 0) {
        i = 0;
        if (*(s16 *)&D_80110220[0x2D7E] < 5) {
        *(s16 *)&D_80110220[0x30FC] = *(s16 *)&D_80110220[0x2D7E];
        if (i < *(s16 *)&D_80110220[0x2D7E]) {
            i = 0;
            do {
                *(u32 *)&D_80110220[i * 0x20 + 0x3018] = 0;
                D_80110220[i * 0x20 + 0x2FFC] = 0;
                D_80110220[i * 0x20 + 0x307C] = 0;
                *(u32 *)&D_80110220[i * 0x20 + 0x3008] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x300C] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x3010] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x3014] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x3088] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x308C] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x3090] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x3094] = 0xFF;
                *(u32 *)&D_80110220[i * 0x20 + 0x3098] = 0x600;
                i++;
            } while (i < *(s16 *)&D_80110220[0x2D7E]);
        }
        if (*(s16 *)&D_80110220[0x2D7E] < 4) {
            *(u32 *)&D_80110220[i * 0x20 + 0x3018] = 0;
            D_80110220[i * 0x20 + 0x2FFC] = 0;
            *(u32 *)&D_80110220[i * 0x20 + 0x3008] = 0;
            *(u32 *)&D_80110220[i * 0x20 + 0x300C] = 0;
            *(u32 *)&D_80110220[i * 0x20 + 0x3010] = 0;
            *(u32 *)&D_80110220[i * 0x20 + 0x3014] = 0;
        }
        }
    }

    if (*(s16 *)&D_80113488[0x2D7E] > 0) {
        i = 0;
        if (*(s16 *)&D_80113488[0x2D7E] < 5) {
        *(s16 *)&D_80113488[0x30FC] = *(s16 *)&D_80113488[0x2D7E];
        if (i < *(s16 *)&D_80113488[0x2D7E]) {
            i = 0;
            do {
                *(u32 *)&D_80113488[i * 0x20 + 0x3018] = 0;
                D_80113488[i * 0x20 + 0x2FFC] = 0;
                D_80113488[i * 0x20 + 0x307C] = 0;
                *(u32 *)&D_80113488[i * 0x20 + 0x3008] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x300C] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x3010] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x3014] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x3088] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x308C] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x3090] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x3094] = 0xFF;
                *(u32 *)&D_80113488[i * 0x20 + 0x3098] = 0x600;
                i++;
            } while (i < *(s16 *)&D_80113488[0x2D7E]);
        }
        if (*(s16 *)&D_80113488[0x2D7E] < 4) {
            *(u32 *)&D_80113488[i * 0x20 + 0x3018] = 0;
            D_80113488[i * 0x20 + 0x2FFC] = 0;
            *(u32 *)&D_80113488[i * 0x20 + 0x3008] = 0;
            *(u32 *)&D_80113488[i * 0x20 + 0x300C] = 0;
            *(u32 *)&D_80113488[i * 0x20 + 0x3010] = 0;
            *(u32 *)&D_80113488[i * 0x20 + 0x3014] = 0;
        }
        }
    }

    D_800E241C = *(s32 *)&D_80110220[0x2AF8];
    D_800E2428 = 0;
    D_800E2424 = 0;
    D_800E2420 = 0;
    *(s16 *)&D_80110220[0x2AEC] = 0;
    *(s16 *)&D_80113488[0x2AEC] = 0;
}

void func_80075698(u8 *arg0, s32 arg1) {
    arg0[0x2FAE] = arg1;
    if (arg1 < 0xA) {
        arg0[0x2FAF] = 0x89;
        arg0[0x2FB0] = 0xA0;
        arg0[0x2FB1] = 0xD6;
        return;
    }
    if (arg1 < 0x14) {
        arg0[0x2FAF] = 0xD2;
        arg0[0x2FB0] = 0x64;
        arg0[0x2FB1] = 0xA0;
        return;
    }
    if (arg1 < 0x1E) {
        arg0[0x2FAF] = 0x96;
        arg0[0x2FB0] = 0xFF;
        arg0[0x2FB1] = 0xC8;
    }
}

typedef struct {
    u8 pad0[0xE4];
    void *imgs[0x14];
    void *unk134;
    void *unk138;
} S570C;

extern u8 D_800E243C[];
extern u8 D_800E2445;
extern s16 D_800E2454[];
extern s16 D_800E2458[];
extern s16 D_800E245C[];
extern s16 D_800E2460[];
extern u8 D_800E90DC[];
void func_80036FE4(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_8007570C(arg0, arg1, arg2, arg3)
s16 arg0, arg1, arg2, arg3;
{
    s32 xp;
    s32 yp;

    if (arg2 >= 0x13) {
        arg2 = 0x13;
        if (D_800E245C[arg3] < 0x14) {
            D_800E245C[arg3] = 0x14;
        }
        if (D_800E2460[arg3] < 0x14) {
            D_800E2460[arg3] = 0x14;
        }
    }
    xp = ((s32) (*(u16 *) ((S570C *) &D_80103210)->imgs[arg2] * D_800E2454[arg3]) >> 9) - *(u16 *) ((S570C *) &D_80103210)->imgs[arg2] * 2;
    yp = ((s32) (*(u16 *) ((u8 *) ((S570C *) &D_80103210)->imgs[arg2] + 2) * D_800E2458[arg3]) >> 9) - *(u16 *) ((u8 *) ((S570C *) &D_80103210)->imgs[arg2] + 2) * 2;
    func_80036FE4(&D_800F22B4, ((S570C *) &D_80103210)->imgs[arg2], 0, 0, *(u16 *) ((S570C *) &D_80103210)->imgs[arg2] - 2, *(u16 *) ((u8 *) ((S570C *) &D_80103210)->imgs[arg2] + 2) - 2, (arg0 * 4) + xp, (arg1 * 4) + yp, D_800E90DC[(&D_800E243C[arg2])[1] * 3], D_800E90DC[(&D_800E243C[arg2])[1] * 3 + 1], D_800E90DC[(&D_800E243C[arg2])[1] * 3 + 2], (s32) D_800E23B4, D_800E2454[arg3], D_800E2458[arg3]);
    if (&D_800E243C[arg2] < &D_800E2445) {
        func_80036FE4(&D_800F22B4, ((S570C *) &D_80103210)->unk134, 0, 0, *(u16 *) ((S570C *) &D_80103210)->unk134 - 2, *(u16 *) ((u8 *) ((S570C *) &D_80103210)->unk134 + 2) - 2, (arg0 * 4) + xp, (arg1 * 4) + yp, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255, D_800E2454[arg3], D_800E2458[arg3]);
        return;
    }
    func_80036FE4(&D_800F22B4, ((S570C *) &D_80103210)->unk138, 0, 0, *(u16 *) ((S570C *) &D_80103210)->unk138 - 2, *(u16 *) ((u8 *) ((S570C *) &D_80103210)->unk138 + 2) - 2, (arg0 * 4) + xp, (arg1 * 4) + yp, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255, D_800E2454[arg3], D_800E2458[arg3]);
}

extern s16 D_8015D980;
extern s16 D_80160C64;
extern s32 D_800E4478;
extern s16 D_800E2454[];
extern s16 D_800E2458[];
extern s16 D_800E245C[];
extern s16 D_800E2460[];
extern s16 D_801039F0[];
extern s16 D_801039F4[];

void func_80075A0C(void) {
    s32 i;
    s32 j;

    for (j = 0; j < D_8015D980; j++) {
        for (i = 0; i < D_80160C64; i++) {
            if (D_800E245C[j] != 0) {
                D_800E245C[j]--;
            }
            if (D_800E2460[j] != 0) {
                D_800E2460[j]--;
            }
        }
        D_801039F0[j] = ((s32)((u32)sins(D_800E4478 << 11) * D_800E245C[j]) >> 13) + 0x400;
        D_801039F4[j] = ((s32)((u32)coss(D_800E4478 << 11) * D_800E2460[j]) >> 13) + 0x400;
        for (i = 0; i < D_80160C64; i++) {
            if (D_800E2454[j] > D_801039F0[j]) {
                D_800E2454[j] -= 0x40;
                if (D_800E2454[j] < D_801039F0[j]) {
                    D_800E2454[j] = D_801039F0[j];
                }
            }
            if (D_800E2454[j] < D_801039F0[j]) {
                D_800E2454[j] += 0x40;
                if (D_800E2454[j] > D_801039F0[j]) {
                    D_800E2454[j] = D_801039F0[j];
                }
            }
            if (D_800E2458[j] > D_801039F4[j]) {
                D_800E2458[j] -= 0x40;
                if (D_800E2458[j] < D_801039F4[j]) {
                    D_800E2458[j] = D_801039F4[j];
                }
            }
            if (D_800E2458[j] < D_801039F4[j]) {
                D_800E2458[j] += 0x40;
                if (D_800E2458[j] > D_801039F4[j]) {
                    D_800E2458[j] = D_801039F4[j];
                }
            }
        }
    }
}

extern s16 D_800E245C[];
extern s16 D_800E2460[];

void func_80075C60(arg0)
short arg0;
{
    D_800E245C[arg0] = 0x64;
    D_800E2460[arg0] = 0x64;
}

extern s16 D_800E2454[];
extern s16 D_800E2458[];

void func_80075C90(void) {
    D_800E245C[0] = 0;
    D_800E245C[1] = 0;
    D_800E2460[0] = 0;
    D_800E2460[1] = 0;
    D_800E2454[0] = 0x400;
    D_800E2454[1] = 0x400;
    D_800E2458[0] = 0x400;
    D_800E2458[1] = 0x400;
}

extern void func_80078514(u8 *, s32, s32, s32, u8 *, s32);
extern void func_80078BA8(void *);
extern void func_80078DA0(void *, s32, s32);
extern void func_80079B80(s32, void *);
extern void func_8007ADF8(void *);
extern void func_8007D45C(void *, void *, s32);
extern void func_8007F720(s32, void *);
extern void func_800ADD50(void *);
extern s32 func_8002D93C(void *, s32, void *, void *);
extern void guRotateRPYF_2(f32 mf[4][4], f32 r, f32 p, f32 h);

typedef struct {
    u8 pad0[0x8];
    Obj2F *unk8;
    u16 unkC;
    u8 padE[0x10 - 0xE];
    f32 unk10;
    Obj2F *unk14;
    s16 unk18;
    s16 unk1A;
} S33B8;

extern s16 D_800DFD50;
extern s16 D_800E08A8;
extern s16 D_800E08AC;
extern s16 D_800E08B0;
extern u8 D_800E2328[];
extern u8 D_800E2364[];
extern u8 D_800E238C[];
extern u16 D_800E23EC;
extern u8 D_800E2434;
extern s16 D_800E2464[];
extern u8 D_800E2828[];
extern s16 D_800E44A0;
extern s16 D_800E44A4;
extern s16 D_800E44AC;
extern u8 D_800E44F4;
extern u8 D_800E44F8;
extern s32 D_800E4478;
extern u8 D_800EE060[];
extern u8 D_800EE064[];
extern u8 D_800EE068[];
extern u8 D_800EE06C[];
extern f64 D_800EE0A0;
extern f64 D_800EE0A8;
extern f64 D_800EE0B0;
extern f64 D_800EE0B8;
extern f32 D_800EE0C0;
extern f32 D_80102B28[4][4];
extern f32 D_80102B68[4][4];
extern f32 D_80102BB0[4][4];
extern u8 D_801026C2;
extern s16 D_801039EC;
extern u8 D_80108828[];
extern u8 D_80110220_2[];
extern u8 D_80110220_4[];
extern u8 D_80110220_5[];
extern u8 D_80113488_2[];
extern u8 D_80113488_3[];
extern u8 D_80113488_4[];
extern u8 D_80113488_5[];
extern u8 D_8010B358[];
extern u8 D_801118A0;
extern s16 D_801125DA;
extern s16 D_80112602;
extern s16 D_801127E6;
extern s16 D_801127E8;
extern s16 D_80112D06;
extern s16 D_80112D08;
extern s32 D_80112D2C;
extern u8 D_801131D2;
extern u8 D_801131D3;
extern u8 D_801131D4;
extern u8 D_801131D5;
extern u8 D_80114B08;
extern s16 D_8011586A;

#define TB3B8 ((S33B8 *)D_801033B8)

void func_80075CD8(s32 arg0) {
    u8 buf[36];
    s32 i;
    s32 w;
    s32 n;
    s32 a1v;
    u32 cur;
    s32 v;
    f32 ang;
    f32 b;
    f32 g;
    f32 r;

    func_80075A0C();
    for (i = 0; i < D_80160C64; i++) {
        if (D_800E23B4 < D_800E23B8) {
            D_800E23B4 += 0x10;
            if (D_800E23B8 < D_800E23B4) {
                D_800E23B4 = D_800E23B8;
            }
        }
        if (D_800E23B8 < D_800E23B4) {
            D_800E23B4 -= 0x10;
            if (D_800E23B4 < D_800E23B8) {
                D_800E23B4 = D_800E23B8;
            }
        }
    }
    if (TB3B8->unk18 >= 0) {
        D_80103210.unk19A = D_80103210.unk194 + 0xF;
    }
    func_800335F0(&D_800F22B4);
    if (D_800E44A8 == 4) {
        if (*(s16 *)(D_80110220 + 0x25C8) >= 0x5A) {
            *(s16 *)(D_80110220 + 0x25C8) = 0x63;
        }
        func_8003396C(&D_800F22B4, D_80103210.unk5C, 0xFE, 0x80, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
        func_8003396C(&D_800F22B4, D_80103210.unk60, 0xFE, 0xAD, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
        func_8003396C(&D_800F22B4, D_80103210.unk54, 0xFE, 0xAD, 0xFF, 0xFF, 0xFF, D_800E23B4);
        func_8003396C(&D_800F22B4, D_80103210.unk58, 0xFE, 0x80, 0xFF, 0xFF, 0xFF, D_800E23B4);
        func_80071DE8(D_801127E6 - 1, 0, 0x100, 0x93, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
        if (D_801127E8 == 0x63) {
            func_8003396C(&D_800F22B4, D_80103210.unk64, 0x108, 0xC3, 0xFF, 0xFF, 0xFF, D_800E23B4);
        } else if (D_801127E8 >= 0xA) {
            func_80071DE8(D_801127E8 - 1, 0, 0xF7, 0xBF, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
        } else {
            func_80071DE8(D_801127E8 - 1, 0, 0xFF, 0xBF, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
        }
        if (D_800DFD50 != 0) {
            func_8003396C(&D_800F22B4, D_80103210.unkC, 0x7C, 0xCB, 0xFE, 0xBE, 0x3F, D_800E23B4);
            func_8007240C(2, 0x89, 0xC8, 0xFE, 0xBE, 0x3F, D_800E23B4);
        }
    }
    if (D_800E44A8 == 2) {
        func_8003396C(&D_800F22B4, D_80103210.unkC, 0x7C, 0xCB, 0xFE, 0xBE, 0x3F, D_800E23B4);
        if (D_80112D2C / 60 < 0xA) {
            if (*(s32 *) (D_8013DD00 + 0x2B0C) / 60 != D_800E2464[0]) {
                func_8007D45C(D_8010B358, D_800E2828, 0x30);
            }
            r = sinf((f32) (((D_800E2434 + 0xFE) & 0xFF) * 0x12 * D_800EE0A0));
            g = sinf((f32) (((D_800E2434 + 0xC8) & 0xFF) * 0x12 * D_800EE0A8));
            b = sinf((f32) (((D_800E2434 + 0x3F) & 0xFF) * 0x12 * D_800EE0B0));
            func_8007240C(2, 0x89, 0xC8, (s32) (r * 255.0f * 255.0f) / 255, (s32) (g * 255.0f * 255.0f) / 255, (s32) (b * 255.0f * 255.0f) / 255, (s32) (sinf((f32) (((D_800E2434 + 0xFF) & 0xFF) * 0x12 * D_800EE0B8)) * 255.0f * 255.0f) / 255);
            D_800E2434 = D_800E2434 + 1;
            D_800E2434 = D_800E2434 % 10;
        } else {
            func_8007240C(2, 0x89, 0xC8, 0xFE, 0xBE, 0x3F, 0xFF);
        }
        D_800E2464[0] = *(s32 *) (D_8013DD00 + 0x2B0C) / 60;
    }
    if (D_8015D980 == 1) {
        if ((D_800E44A8 != 3) && (D_800E44A8 != 4)) {
            if (D_800E44A8 == 2) {
                func_8003396C(&D_800F22B4, D_80103210.unkDC, 0x1B, 0x58, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xC8) / 255);
            } else {
                func_8003396C(&D_800F22B4, D_80103210.unkDC, 0x1B, 0x4E, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xC8) / 255);
            }
        }
        if (D_800E44A8 != 3) {
            func_8003396C(&D_800F22B4, D_80103210.unkD8, 0x1B, 0x12, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk10, 0x1B, 0x12, 0xFF, 0xFF, 0xFF, D_800E23B4);
        }
        if (D_800E44A8 == 4) {
            if (D_801125DA < 9) {
                func_80071DE8(D_801125DA, 0, 0x26, 0x2B, 8, 0xFF, 0xFF, 0xFF, 0xFF);
            } else if (D_801125DA < 0x63) {
                func_80071DE8(D_801125DA, 0, 0x1F, 0x2B, 8, 0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                func_80071DE8(D_801125DA, 0, 0x18, 0x2B, 8, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
        if (D_800E44A8 == 0xC) {
            if (D_80112602 >= 0xA) {
                func_80071DE8(D_80112602 - 1, 0, 0x1F, 0x2B, 8, 0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                func_80071DE8(D_80112602 - 1, 0, 0x25, 0x2B, 8, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
        if (D_800E44A8 == 2) {
            if (D_801125DA < 9) {
                func_80071DE8(D_801125DA, 0, 0x25, 0x35, 8, 0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                func_80071DE8(D_801125DA, 0, 0x1F, 0x35, 8, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
        if ((D_800E44A8 == 1) || (D_800E44A8 == 9)) {
            if (D_800E44A0 < 9) {
                if (D_801125DA >= 9) {
                    w = func_80071DE8(D_800E44A0, 0, 0x1B, 0x2B, 8, 0xFF, 0xFF, 0xFF, D_800E23B4) + 0x42;
                    sprintf(buf, D_800EE060);
                    func_80038478(&D_800F22B4, w - 0x47, 0x2A, buf, 0xFF, 0xFF, 0xFF, D_800E23B4);
                    func_80071DE8(D_801125DA, 0, w - 0x4F, 0x2B, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
                } else {
                    w = func_80071DE8(D_800E44A0, 0, 0x1E, 0x2B, 8, 0xFF, 0xFF, 0xFF, D_800E23B4) + 0x42;
                    sprintf(buf, D_800EE064);
                    func_80038478(&D_800F22B4, w - 0x45, 0x2A, buf, 0xFF, 0xFF, 0xFF, D_800E23B4);
                    func_80071DE8(D_801125DA, 0, w - 0x4B, 0x2B, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
                }
            } else {
                w = func_80071DE8(D_800E44A0, 0, 0x16, 0x2B, 8, 0xFF, 0xFF, 0xFF, D_800E23B4) + 0x42;
                sprintf(buf, D_800EE068);
                func_80038478(&D_800F22B4, w - 0x46, 0x2A, buf, 0xFF, 0xFF, 0xFF, D_800E23B4);
                if (D_801125DA >= 9) {
                    func_80071DE8(D_801125DA, 0, w - 0x50, 0x2B, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
                } else {
                    func_80071DE8(D_801125DA, 0, w - 0x4D, 0x2B, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
                }
            }
        }
        if (D_800E44A8 == 3) {
            func_8003396C(&D_800F22B4, D_80103210.unk20, 0xA2, 0x7F, 0xC8, 0xC8, 0xC8, D_800E23B4);
            func_8003396C(&D_800F22B4, D_80103210.unk24, 0xA8, 0x87, 0xFF, 0xFF, 0xFF, D_800E23B4);
            func_8003396C(&D_800F22B4, D_80103210.unk28, *(u16 *)(D_800E22E0 + 0x0), *(u16 *)(D_800E22E0 + 0x2), *(u16 *)(D_800E22E0 + 0x4), *(u16 *)(D_800E22E0 + 0x6), *(u16 *)(D_800E22E0 + 0x8), (s32) (*(u16 *)(D_800E22E0 + 0xA) * D_800E23B4) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk2C, *(u16 *)(D_800E22E0 + 0xC), *(u16 *)(D_800E22E0 + 0xE), *(u16 *)(D_800E22E0 + 0x10), *(u16 *)(D_800E22E0 + 0x12), *(u16 *)(D_800E22E0 + 0x14), (s32) (*(u16 *)(D_800E22E0 + 0x16) * D_800E23B4) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk30, *(u16 *)(D_800E22E0 + 0x18), *(u16 *)(D_800E22E0 + 0x1A), *(u16 *)(D_800E22E0 + 0x1C), *(u16 *)(D_800E22E0 + 0x1E), *(u16 *)(D_800E22E0 + 0x20), (s32) (*(u16 *)(D_800E22E0 + 0x22) * D_800E23B4) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk34, *(u16 *)(D_800E22E0 + 0x24), *(u16 *)(D_800E22E0 + 0x26), *(u16 *)(D_800E22E0 + 0x28), *(u16 *)(D_800E22E0 + 0x2A), *(u16 *)(D_800E22E0 + 0x2C), (s32) (*(u16 *)(D_800E22E0 + 0x2E) * D_800E23B4) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk38, *(u16 *)(D_800E22E0 + 0x30), *(u16 *)(D_800E22E0 + 0x32), *(u16 *)(D_800E22E0 + 0x34), *(u16 *)(D_800E22E0 + 0x36), *(u16 *)(D_800E22E0 + 0x38), (s32) (*(u16 *)(D_800E22E0 + 0x3A) * D_800E23B4) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk38, *(u16 *)(D_800E22E0 + 0x3C), *(u16 *)(D_800E22E0 + 0x3E), *(u16 *)(D_800E22E0 + 0x40), *(u16 *)(D_800E22E0 + 0x42), *(u16 *)(D_800E22E0 + 0x44), (s32) (*(u16 *)(D_800E22E0 + 0x46) * D_800E23B4) / 255);
        }
        if (D_800E44A8 != 3) {
            if (D_800E44A8 != 4) {
                func_80078BA8(D_80110220);
            }
            if (D_800E44A8 != 4) {
                func_8003396C(&D_800F22B4, D_80103210.unk4C, 0xEA, 0x9A, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
                func_8003396C(&D_800F22B4, D_80103210.unk44, 0xEA, 0x9A, 0xFF, 0xFF, 0xFF, D_800E23B4);
                func_80078DA0(D_80110220, 0x105, 0x9D);
                func_8003396C(&D_800F22B4, D_80103210.unk18, 0x107, 0x9F, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
                func_80078514(D_80110220 + (s32) D_80110220_5 * 0, 0x100, 0, 0xF, D_800E2328, 2);
                func_8003396C(&D_800F22B4, D_80103210.unkCC, 0x107, 0x1B, *(u8 *)(D_80110220 + 0x2FB2), *(u8 *)(D_80110220 + 0x2FB3), *(u8 *)(D_80110220 + 0x2FB4), (s32) (*(u8 *)(D_80110220 + 0x2FB5) * D_800E23B4) / 255);
            }
        }
        if (D_800E44A8 == 5) {
            if (D_800E44A4 == 8) {
                func_8003396C(&D_800F22B4, D_80103210.unkD4, 0x8C, 0xB4, 0xFF, 0xFF, 0xFF, D_800E23B4);
                func_8003396C(&D_800F22B4, D_80103210.unkD0, 0x8C, 0xB4, 0xFF, 0xFF, 0xFF, D_800E23B4);
                func_80071DE8(D_80112602, 0, 0x96, 0xC3, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
                func_8003396C(&D_800F22B4, D_80103210.unk13C, 0x8C, 0xB4, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
            }
            w = func_80071DE8(D_800E44F4, 0, 0x1E, 0x2C, 8, 0xFF, 0xFF, 0xFF, D_800E23B4) + 0x42;
            sprintf(buf, D_800EE06C);
            func_80038478(&D_800F22B4, w - 0x45, 0x2B, buf, 0xFF, 0xFF, 0xFF, D_800E23B4);
            func_80071DE8(D_800E44F8, 0, w - 0x4B, 0x2C, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
        }
        if ((D_800E44A8 == 1) || (D_800E44A8 == 0xC) || (D_800E44A8 == 0xA) || (D_800E44A8 == 2) || (D_800E44A8 == 5) || (D_800E44A8 == 9) || (D_800E44A8 == 4)) {
            cur = D_800E241C;
            if (*(u32 *)(D_80110220 + 0x2AF8) < cur) {
                D_800E241C = *(u32 *)(D_80110220 + 0x2AF8);
                cur = *(u32 *)(D_80110220 + 0x2AF8);
            }
            if ((((s32) *(u32 *)(D_80110220 + 0x2AF8) - (s32) cur) > 0) || (*(s16 *)(D_80110220 + 0x2B08) != 0)) {
                D_800E241C = ((*(u32 *)(D_80110220 + 0x2AF8) - cur) >> 3) + (cur + *(s32 *)(D_80110220 + 0x2B00) * 0);
                if ((*(u32 *)(D_80110220 + 0x2AF8) - D_800E241C) < 0xA) {
                    D_800E241C = *(u32 *)(D_80110220 + 0x2AF8);
                }
                D_800E2424 = 0x32;
            }
            n = D_800E2424;
            if (n >= 0xB) {
                if (D_800E44A8 != 2) {
                    D_800E2424 -= 1;
                }
                if (D_800E44A8 == 4) {
                    func_80071DE8(D_800E241C, 0, 0x113, 0x19, 5, 0xFE, 0xBE, 0x3F, 0xFF);
                } else {
                    func_80071DE8(D_800E241C, 0, 0xF5, 0x19, 5, 0xFE, 0xBE, 0x3F, 0xFF);
                }
            } else if (n > 0) {
                D_800E2424 -= 1;
                if (D_800E44A8 == 4) {
                    func_80071DE8(D_800E241C, 0, 0x113, 0x19, 5, 0xFE, 0xBE, 0x3F, D_800E2424 * 0x19);
                } else {
                    func_80071DE8(D_800E241C, 0, 0xF5, 0x19, 5, 0xFE, 0xBE, 0x3F, D_800E2424 * 0x19);
                }
            }
            if (*(s32 *)(D_80110220 + 0x2B00) + (s32) D_80110220 * 0 != 0) {
                D_800E2420 = *(s32 *)(D_80110220 + 0x2B00);
                D_800E2428 = 0x78 + (s32) D_80110220_5 * 0;
                if (*(s32 *)(D_80110220_5 + 0x2AFC) == 0) {
                    *(s32 *)(D_80110220_5 + 0x2B00) = 0;
                }
            }
            if (D_800E44A8 == 4) {
                func_8007570C(0x107, 0x2A, (s16) (*(s16 *)(D_80110220_5 + 0x2AE8) + *(s16 *)(D_80110220_5 + 0x2AE6)), 0);
            } else {
                arg0 = *(s16 *)(D_80110220_5 + 0x2AE6) + *(s16 *)(D_80110220_5 + 0x2AE8) + *(s32 *)(D_80110220 + 0x2B00) * 0;
                if (arg0 != D_801039EC) {
                    func_8007D45C(D_8010B358, D_800E2828, 0x2D);
                    arg0 = D_80112D06 + D_80112D08;
                }
                func_8007570C(0xE9, 0x2A, (s16) arg0, 0);
                D_801039EC = D_80112D06 + D_80112D08;
            }
            n = D_800E2428;
            if (n >= 0xB) {
                D_800E2428 -= 1;
                if (D_800E44A8 == 4) {
                    func_80071DE8(D_800E2420, 2, 0xFA, 0x28, 5, 0xFF, 0xFF, 0xFF, 0xFF);
                } else {
                    func_80071DE8(D_800E2420, 2, 0xDC, 0x28, 5, 0xFF, 0xFF, 0xFF, 0xFF);
                }
            } else if (n > 0) {
                D_800E2428 -= 1;
                if (D_800E44A8 == 4) {
                    func_80071DE8(D_800E2420, 2, 0xFA, 0x28, 5, 0xFF, 0xFF, 0xFF, D_800E2428 * 0x19);
                } else {
                    func_80071DE8(D_800E2420, 2, 0xDC, 0x28, 5, 0xFF, 0xFF, 0xFF, D_800E2428 * 0x19);
                }
            }
        }
    }
    if (D_800E44A8 == 3) {
        func_8003396C(&D_800F22B4, D_80103210.unk160, 0x9A, 0xF, 0xFF, 0xFF, 0xFF, 0xFF);
        func_800743BC(0xA0, 0x13, 0x128, 0x6E, 0xFF);
    } else if ((D_80103210.unk19C != 0) && (TB3B8->unk18 < 0)) {
        func_80074B50();
    }
    if ((D_8015D980 >= 2) || (D_800E44A8 == 3)) {
        if (D_800E44A8 != 3) {
            func_8003396C(&D_800F22B4, D_80103210.unk13C, 0x97, 0, 0x28, 0x28, 0x28, 0xFF);
        }
        func_8007570C(0x81, 0x2B, (s16) (D_80112D06 + D_80112D08), 0);
        if ((D_800E44A8 != 3) || (D_800E44AC != 3)) {
            func_80078BA8(D_80110220);
        } else {
            func_8003396C(&D_800F22B4, D_80103210.unkD8, 0x80, 0xA0, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xE1) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unkD8, 0x80, 0xBE, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xE1) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk1C, 0x80, 0xA0, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xE1) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unkE0, 0x80, 0xBE, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xE1) / 255);
            func_80071DE8(D_801127E6 - 1, 1, 0x7E, 0xAA, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
            func_80071DE8(D_801127E8 - 1, 1, 0x7E, 0xC7, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
        }
        func_8003396C(&D_800F22B4, D_80103210.unk4C, 0x1A, 0x10, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xE1) / 255);
        func_8003396C(&D_800F22B4, D_80103210.unk44, 0x1A, 0x10, 0xFF, 0xFF, 0xFF, D_800E23B4);
        func_80078DA0(D_80110220, 0x2B, 0x15);
        func_80078514(D_80110220, 0x7D, 0x15, 0xA, D_800E2364, 1);
        func_8003396C(&D_800F22B4, D_80103210.unkCC, 0x84, 0x15, D_801131D2, D_801131D3, D_801131D4, (s32) (D_801131D5 * D_800E23B4) / 255);
        func_8003396C(&D_800F22B4, D_80103210.unk18, 0x2B, 0x15, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
        if (D_800E44A8 != 3) {
            func_8007570C(0xA5, 0x2B, (s16) (*(s16 *)(D_80113488 + 0x2AE8) + *(s16 *)(D_80113488 + 0x2AE6)), 1);
            func_8003396C(&D_800F22B4, D_80103210.unkD8, 0x8A, 0xA2, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk10, 0x8A, 0xA2, 0xFF, 0xFF, 0xFF, D_800E23B4);
            func_80078BA8(D_80113488_2);
            func_8003396C(&D_800F22B4, D_80103210.unk50, 0x101, 0x10, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0xE1) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk48, 0xFF, 0x10, 0xFF, 0xFF, 0xFF, D_800E23B4);
            func_80078DA0(D_80113488_3, 0x104, 0x15);
            func_80078514(D_80113488_4, 0x104, 0x15, 0xA, D_800E238C, 1);
            func_8003396C(&D_800F22B4, D_80103210.unkCC, 0xA8, 0x15, *(u8 *)(D_80113488_5 + 0x2FB2), *(u8 *)(D_80113488_5 + 0x2FB3), *(u8 *)(D_80113488_5 + 0x2FB4), (s32) (*(u8 *)(D_80113488_5 + 0x2FB5) * D_800E23B4) / 255);
            func_8003396C(&D_800F22B4, D_80103210.unk18, 0x104, 0x15, 0xFF, 0xFF, 0xFF, (s32) (D_800E23B4 * 0x96) / 255);
            if (D_8011586A >= 0xA) {
                func_80071DE8(D_8011586A - 1, 2, 0x97, 0xBC, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
            } else {
                func_80071DE8(D_8011586A - 1, 2, 0x9C, 0xBC, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
            }
            if (D_80112602 >= 0xA) {
                func_80071DE8(D_80112602 - 1, 2, 0x83, 0xBC, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
            } else {
                func_80071DE8(D_80112602 - 1, 2, 0x8B, 0xBC, 8, 0xFF, 0xFF, 0xFF, D_800E23B4);
            }
            if (D_800E08A8 >= 2) {
                for (n = 0; n < D_800E08A8; n++) {
                        if (D_80114B08 == 1) {
                            coss(D_800E4478 << 0xB);
                            if (sins(D_800E4478 << 0xA) >= 0) {
                                sins(D_800E4478 << 0xA);
                            } else {
                                sins(D_800E4478 << 0xA);
                            }
                        }
                        if (n < D_800E08AC) {
                            func_8003396C(&D_800F22B4, D_80103210.unk140, 0x5F - (n * 0xF), 0xD0, 0xFF, 0xFF, 0, D_800E23B4);
                        } else {
                            func_8003396C(&D_800F22B4, D_80103210.unk140, 0x5F - (n * 0xF), 0xD0, 0, 0, 0, D_800E23B4 >> 1);
                        }
                        if (D_801118A0 == 1) {
                            coss(D_800E4478 << 0xB);
                            if (sins(D_800E4478 << 0xA) >= 0) {
                                sins(D_800E4478 << 0xA);
                            } else {
                                sins(D_800E4478 << 0xA);
                            }
                        }
                        if (n < D_800E08B0) {
                            func_8003396C(&D_800F22B4, D_80103210.unk140, (n * 0xF) + 0xD7, 0xD0, 0xFF, 0xFF, 0, D_800E23B4);
                        } else {
                            func_8003396C(&D_800F22B4, D_80103210.unk140, (n * 0xF) + 0xD7, 0xD0, 0, 0, 0, D_800E23B4 >> 1);
                        }
                }
            }
        }
    }
    if ((D_8015D980 == 1) && (D_800E44A8 == 3)) {
        func_800740C4();
    }
    func_800338B0(&D_800F22B4);
    if ((D_8015D980 == 1) && (D_800E44A8 == 3)) {
        if (D_800E23EC != 0) {
            ang = -18.0f;
        } else {
            ang = -70.0f;
        }
        for (i = 0; i < D_80160C64; i++) {
            if (TB3B8->unk10 < ang) {
                TB3B8->unk10 = TB3B8->unk10 + 2.0;
            }
            if (ang < TB3B8->unk10) {
                TB3B8->unk10 = TB3B8->unk10 - 2.0;
            }
        }
        guScaleF(D_80102B28, D_800EE0C0, D_800EE0C0, D_800EE0C0);
        guTranslateF(D_80102B68, 120.0f, -35.0f, 0.0f);
        guRotateRPYF_2(D_80102BB0, 0.0f, TB3B8->unk10, 0.0f);
        guMtxCatF(D_80102B28, D_80102BB0, D_80102B28);
        if (func_8002D93C(TB3B8->unk8, (TB3B8->unkC + D_80160C64) - TB3B8->unk8->unk24, D_80102B28, D_80102B68) != 0) {
            TB3B8->unk8->unk24 = 0;
        }
        TB3B8->unkC = TB3B8->unk8->unk24;
    }
    if (D_8015D980 == 1) {
        if ((D_800E44A8 == 2) || (D_800E44A8 == 5)) {
            if (TB3B8->unk14 == NULL) {
                TB3B8->unk18 = -1;
            }
            if (TB3B8->unk18 >= 0) {
                TB3B8->unk1A = 0xC0;
                func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, TB3B8->unk1A);
                if ((*(u8 *)(D_80108828 + 0x1594) != 0) || (D_801026C2 != 0)) { a1v = (TB3B8->unk18 + D_80160C64) - TB3B8->unk14->unk24; } else { a1v = 0; } if (func_8002D93C(TB3B8->unk14, a1v, NULL, NULL) != 0) {
                    func_800ADD50(D_80110220);
                    TB3B8->unk18 = -1;
                    if (D_800E44FC == 0) {
                        func_80071DD8(0xFF);
                    }
                    func_8007ADF8(D_80108828);
                    func_80079B80(0x7FFF, D_80108828);
                    *(u8 *)(D_80108828 + 0x1581) = 1;
                    *(u8 *)(D_80108828 + 0x1594) = 0;
                    *(s16 *)(D_80108828 + 0x157C) = 0;
                    func_8007F720(0x140, D_80108828);
                } else {
                    TB3B8->unk18 = TB3B8->unk14->unk24;
                    if (TB3B8->unk14->unk28 >= 1.0) {
                        func_800ADD50(D_80110220);
                        TB3B8->unk18 = -1;
                        if (D_800E44FC == 0) {
                            func_80071DD8(0xFF);
                        }
                        func_8007ADF8(D_80108828);
                        func_80079B80(0x7FFF, D_80108828);
                        *(u8 *)(D_80108828 + 0x1581) = 1;
                        *(u8 *)(D_80108828 + 0x1594) = 0;
                        *(s16 *)(D_80108828 + 0x157C) = 0;
                        func_8007F720(0x140, D_80108828);
                    }
                }
            } else if (TB3B8->unk1A > 0) {
                for (v = 0; v < D_80160C64; v++) {
                    TB3B8->unk1A = TB3B8->unk1A - 8;
                    if (TB3B8->unk1A <= 0) {
                        TB3B8->unk1A = 0;
                        break;
                    }
                }
                if (TB3B8->unk1A > 0) {
                    func_8006FA28(0, 0, 0x13F, 0xEF, 0, 0, 0, TB3B8->unk1A);
                }
            }
        }
    }
}


extern void func_8003396C(void *, void *, s32, s32, s32, s32, s32, s32);
extern u8 D_800E2468[];
extern u8 D_800E2328[];
extern u8 D_800E2364[];

void func_80078514(arg0, arg1, arg2, arg3, arg4, arg5)
u8 *arg0;
s32 arg1;
s32 arg2;
s32 arg3;
u8 *arg4;
s32 arg5;
{
    s32 i;
    s32 d;
    u8 *p;
    u8 *t;
    s32 c;
    s32 cv;
    s32 cv2;
    s32 cv3;
    s32 cv4;
    void *h;

    *(s32 *)&arg0[0x2FF0] = *(s32 *)&arg0[0x2FF0] * 2;
    if (arg3 < *(u16 *)&arg0[0x2AEC]) {
        *(u16 *)&arg0[0x2AEC] = arg3;
    }
    *(s32 *)&arg0[0x2FF0] &= *(s32 *)(D_800E2468 + ((arg3 << 2) + ((*(u16 *)&arg0[0x2AEC] << 2) * -1)));
    if (arg0[0x2FAE] != 0) {
        *(s32 *)&arg0[0x2FF0] = *(s32 *)&arg0[0x2FF0] | 1;
        arg0[0x2FAE] = arg0[0x2FAE] - 1;
    }
    if (*(s32 *)&arg0[0x2FF0] & 1) {
        *(f32 *)&arg0[0x2408] = *(f32 *)&arg0[0x2408] - *(s16 *)&arg0[0x3250];
        if (*(f32 *)&arg0[0x2408] < 0.0f) {
            *(f32 *)&arg0[0x2408] = 0.0f;
        }
    }
    d = arg3 - *(u16 *)&arg0[0x2AEC];
    if ((*(s32 *)&arg0[0x2FF0] & (1 << (d + 0x1F))) && !(*(s32 *)&arg0[0x2FF0] & (1 << (d + 0x1E)))) {
        arg0[0x2DAC] = 1;
    }
    d = arg3 - *(u16 *)&arg0[0x2AEC];
    i = d;
    if (d < arg3) {
        d = arg3 - *(u16 *)&arg0[0x2AEC];
        t = (u8 *)&D_80103210 + i * 4; p = &arg0[0] + i * 4; do {
            p[0x2FB2] = 0x7D;
            p[0x2FB3] = 0xAF;
            p[0x2FB4] = 0xFF;
            p[0x2FB5] = 0xFF;
            if (!(*(s32 *)&arg0[0x2FF0] & (1 << i)) && (*(s32 *)&arg0[0x2FF4] & (1 << i))) {
                p[0x2FB2] = arg0[0x2FAF];
                p[0x2FB3] = arg0[0x2FB0];
                p[0x2FB4] = arg0[0x2FB1];
                p[0x2FB5] = 0xFF;
                if ((arg4 == D_800E2364) || ((arg4 - D_800E2328) == 0)) {
                    h = *(void **)(t + 0x54);
                } else {
                    h = *(void **)(t + 0x7C);
                }
                func_8003396C(&D_800F22B4, h, *(u16 *)(&arg4[0] + (i << 2)), *(u16 *)(&arg4[0] + (i << 2) + 2), p[0x2FB2], p[0x2FB3], p[0x2FB4], (s32)(p[0x2FB5] * D_800E23B4) / 255);
            } else if (*(s32 *)&arg0[0x2FF0] & (1 << i)) {
                if ((arg4 == D_800E2364) || ((arg4 - D_800E2328) == 0)) {
                    h = *(void **)(t + 0x54);
                } else {
                    h = *(void **)(t + 0x7C);
                }
                func_8003396C(&D_800F22B4, h, *(u16 *)(&arg4[0] + (i << 2)), *(u16 *)(&arg4[0] + (i << 2) + 2), 0xFF, 0xFF, 0xFF, D_800E23B4);
            } else {
                if ((arg4 == D_800E2364) || ((arg4 - D_800E2328) == 0)) {
                    h = *(void **)(t + 0x54);
                } else {
                    h = *(void **)(t + 0x7C);
                }
                func_8003396C(&D_800F22B4, h, *(u16 *)(&arg4[0] + (i << 2)), *(u16 *)(&arg4[0] + (i << 2) + 2), p[0x2FB2], p[0x2FB3], p[0x2FB4], (s32)(p[0x2FB5] * D_800E23B4) / 255);
            }
            i += 1;
            p += 4;
            t += 4;
        } while (i < arg3);
        d = arg3 - *(u16 *)&arg0[0x2AEC];
    }
    i = 0;
    if (d > 0) {
        t = (u8 *)&D_80103210;
        p = arg0;
        do {
            cv = p[0x2FB2];
            if (arg0[0x2FF8] < p[0x2FB2]) {
                p[0x2FB2] = cv - 5;
                cv = p[0x2FB2];
            }
            if (cv < arg0[0x2FF8]) {
                p[0x2FB2] = p[0x2FB2] + 1;
            }
            c = arg0[0x2FF9];
            cv2 = p[0x2FB3];
            if (c < p[0x2FB3]) {
                p[0x2FB3] = cv2 - 5;
                cv2 = p[0x2FB3];
                c = arg0[0x2FF9];
            }
            if (cv2 < c) {
                p[0x2FB3] = p[0x2FB3] + 1;
            }
            cv3 = p[0x2FB4];
            if (arg0[0x2FFA] < p[0x2FB4]) {
                p[0x2FB4] = cv3 - 5;
                cv3 = p[0x2FB4];
            }
            if (cv3 < arg0[0x2FFA]) {
                p[0x2FB4] = p[0x2FB4] + 1;
            }
            cv4 = p[0x2FB5];
            if (arg0[0x2FFB] < p[0x2FB5]) {
                p[0x2FB5] = cv4 - 5;
                cv4 = p[0x2FB5];
            }
            if (cv4 < arg0[0x2FFB]) {
                p[0x2FB5] = p[0x2FB5] + 1;
            }
            if (!(*(s32 *)&arg0[0x2FF0] & (1 << i)) && (*(s32 *)&arg0[0x2FF4] & (1 << i))) {
                p[0x2FB2] = arg0[0x2FAF];
                p[0x2FB3] = arg0[0x2FB0];
                p[0x2FB4] = arg0[0x2FB1];
                p[0x2FB5] = 0xFF;
                if ((arg4 == D_800E2364) || ((arg4 - D_800E2328) == 0)) {
                    h = *(void **)(t + 0x54);
                } else {
                    h = *(void **)(t + 0x7C);
                }
                func_8003396C(&D_800F22B4, h, *(u16 *)(&arg4[0] + (i << 2)), *(u16 *)(&arg4[0] + (i << 2) + 2), p[0x2FB2], p[0x2FB3], p[0x2FB4], (s32)(p[0x2FB5] * D_800E23B4) / 255);
            } else if (*(s32 *)&arg0[0x2FF0] & (1 << i)) {
                if ((arg4 == D_800E2364) || ((arg4 - D_800E2328) == 0)) {
                    h = *(void **)(t + 0x54);
                } else {
                    h = *(void **)(t + 0x7C);
                }
                func_8003396C(&D_800F22B4, h, *(u16 *)(&arg4[0] + (i << 2)), *(u16 *)(&arg4[0] + (i << 2) + 2), 0xFF, 0xFF, 0xFF, D_800E23B4);
            } else {
                if ((arg4 == D_800E2364) || ((arg4 - D_800E2328) == 0)) {
                    h = *(void **)(t + 0x54);
                } else {
                    h = *(void **)(t + 0x7C);
                }
                cv = p[0x2FB2];
                cv2 = p[0x2FB3];
                cv3 = p[0x2FB4];
                cv4 = p[0x2FB5];
                func_8003396C(&D_800F22B4, h, *(u16 *)(&arg4[0] + (i << 2)), *(u16 *)(&arg4[0] + (i << 2) + 2), cv, cv2, cv3, (s32)((cv4 * 1) * D_800E23B4) / 255);
            }
            i += 1;
            p += 4;
            t += 4;
        } while (i < arg3 - *(u16 *)&arg0[0x2AEC]);
    }
    *(s32 *)&arg0[0x2FF4] = *(s32 *)&arg0[0x2FF0];
}

extern void func_800C3DE4(u8);
extern void *D_80103454;
extern u8 D_8014D266;

void func_80078BA8(void *arg0) {
    s32 var_s1;
    u8 *var_s0;

    if (*(s16 *) ((u8 *) arg0 + 0x2D7E) != *(s16 *) ((u8 *) arg0 + 0x30FC)) {
        *(u8 *) ((u8 *) arg0 + (*(s16 *) ((u8 *) arg0 + 0x30FC) << 5) + 0x2FDC) = 1;
        func_800C3DE4(*(u8 *) ((u8 *) arg0 + 0x30FD));
    }
    var_s0 = arg0;
    for (var_s1 = 0; var_s1 != 0x60;) {
        if (*(u8 *) (var_s0 + 0x2FFC) == 2) {
            func_8003396C(&D_800F22B4, *(void **) ((u8 *) &D_80103210 + 0xE0), *(s32 *) (var_s0 + 0x3000), *(s32 *) (var_s0 + 0x3004), 0xFF, 0xFF, 0xFF, (s32) D_800E23B4);
        } else if (*(u8 *) (var_s0 + 0x2FFC) == 1) {
            if ((D_8014D266 == 0) || ((D_8014D266 != 0) && (*(s32 *) ((u8 *) D_80103454 + 0x24) >= 0x1F))) {
                *(u8 *) (var_s0 + 0x2FFC) = 2;
            func_8003396C(&D_800F22B4, *(void **) ((u8 *) &D_80103210 + 0xE0), *(s32 *) (var_s0 + 0x3000), *(s32 *) (var_s0 + 0x3004), 0xFF, 0xFF, 0xFF, (s32) D_800E23B4);
            }
        } else {
            func_8003396C(&D_800F22B4, *(void **) ((u8 *) &D_80103210 + 0x1C), *(s32 *) (var_s0 + 0x3000), *(s32 *) (var_s0 + 0x3004), *(s32 *) (var_s0 + 0x3008), *(s32 *) (var_s0 + 0x300C), *(s32 *) (var_s0 + 0x3010), (s32) (*(s32 *) (var_s0 + 0x3014) * D_800E23B4) / 255);
        }
        var_s1 += 0x20;
        var_s0 += 0x20;
    }
    *(s16 *) ((u8 *) arg0 + 0x30FC) = *(s16 *) ((u8 *) arg0 + 0x2D7E);
}
