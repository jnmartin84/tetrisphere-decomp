#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[0x156C];
    s32 unk1570;
    u32 unk1574;
    s16 unk1578;
    u16 unk157A;
    u16 unk157C;
    u16 unk157E;
    u8 unk1580;
    u8 pad1581;
    u16 pad1582;
    u16 unk1584;
    u16 unk1586;
    u8 pad1588[4];
    u8 *unk158C;
    u8 pad1590[4];
    u8 unk1594;
} AudioMgr;

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    void *unk10;
    void *unk14;
    s32 unk18;
    u8 unk1C;
    s32 unk20;
} Cfg1;
typedef struct {
    u32 unk00;
    s32 unk04;
    s32 unk08;
} Cfg2;
extern s16 D_800E28E4;
extern u16 D_800E28E8;
extern u32 D_800E28E0;
extern u8 D_800DF770;
extern char D_800EE490[];
extern u8 D_802A2000[];
extern AudioMgr D_80107290;
extern AudioMgr D_80108828;
extern AudioMgr D_80109DC0;
extern u8 D_80108810;
extern u8 *D_8010881C;
extern u8 *D_80108820;
extern u8 *D_80109DB4;
extern u8 *D_80109DB8;
extern u8 *D_8010B7BC;
extern void *D_8010B7C4;
extern u8 D_8010B7C8[];
extern u8 D_8010C6C8[];
extern u8 D_8010DB48[];
extern u8 D_8010EA48[];
extern u8 D_8010ED08[];
extern u8 D_8010D888[];
extern u8 D_8010B358[];
extern void func_80079BD4(s32);
extern void func_8007E800(Cfg1 *, s32, Cfg2 *);
extern void func_80029760(char *, ...);
extern void func_80079D3C(AudioMgr *, void *, void *, s32, s32, s32);
extern void func_80033470(void);
extern u8 *func_80079E68(AudioMgr *, void *, u8 *, s32);
extern void func_8008012C(void *, s32);
extern void func_8007FE4C(AudioMgr *);
extern void func_8007BDCC(u8 *, s32, s32);
void func_8007F0D0(void *arg0) {
    Cfg1 cfg1;
    Cfg2 cfg2;
    s32 sp24 = 1;
    s32 heapSize;
    D_800E28E4 = 0xD;
    D_80107290.unk0 = 0;
    D_800E28E8 = 0x4FFF;
    func_80079BD4(0x7FFF);
    alHeapInit(arg0, D_802A2000, 0x113000);
    cfg1.unk00 = 0x30;
    cfg1.unk04 = 0x30;
    cfg1.unk08 = 0x60;
    cfg1.unk10 = 0;
    cfg1.unk1C = 1;
    cfg1.unk18 = 0;
    cfg1.unk14 = arg0;
    cfg2.unk00 = D_800E28E0;
    cfg2.unk04 = 1;
    cfg2.unk08 = 0x1800;
    func_8007E800(&cfg1, 0xC, &cfg2);
    heapSize = 0x113000;
    D_8010B7BC = alHeapDBAlloc(0, 0, arg0, 1, heapSize);
    while (D_8010B7BC == 0) {
        heapSize = heapSize - 0x10;
        D_8010B7BC = alHeapDBAlloc(0, 0, arg0, 1, heapSize);
    }
    func_80029760(D_800EE490, heapSize, D_8010B7BC);
    func_80079D3C(&D_80107290, D_8010B7C8, D_8010C6C8, 0x10, D_800E28E8, 1);
    func_80079D3C(&D_80108828, D_8010DB48, D_8010EA48, 0x10, 0x7FFF, 0);
    func_80079D3C(&D_80109DC0, D_8010ED08, D_8010D888, 0, 0x7FFF, 0);
    D_8010881C = D_8010B7BC;
    D_80109DB4 = (u8 *) 0x80352000;
    func_80033470();
    D_80108820 = (u8 *) 0x80000400;
    D_80109DB8 = (u8 *) 0x80000400;
    if (D_800DF770 != 0) {
        func_8008012C((void *) 0x80000400, 0);
    } else {
        func_8008012C((void *) 0x80000400, 0x145);
    }
    D_8010B7BC = func_80079E68(&D_80107290, (void *) 0x80000400, D_8010B7BC, 1);
    D_80108810 = 0;
    while (D_80108810 == 0) {
        func_8007FE4C(&D_80107290);
    }
    func_8007BDCC(D_8010B358, 0, 0x10);
    D_8010B7C4 = 0;
}

typedef struct {
    u8 pad0[4];
    u16 unk4;
    u16 unk6;
    u8 *unk8;
    u16 unkC;
} AudioArg;

extern s8 D_800E28AC;
extern s16 D_800E44A8;
extern u8 D_800E2828[];
extern u8 D_800E2838[];
extern u16 D_800E2868;
extern u8 *D_800F22C0;
extern char D_800EE4AC[];
extern char D_800EE4D0[];
extern char D_800EE4E8[];
extern char D_800EE51C[];
extern char D_800EE538[];
extern char D_800EE560[];
extern char D_800EE578[];
extern u16 D_80109DA4;
extern u8 D_8010A210;
extern u8 *D_8010B6A8;
extern void func_8002AF20(char *, char *);
extern void func_8007ACE8(AudioMgr *);
extern void func_8007ADF8(AudioMgr *);
extern void func_8007AEE0(u8 *);
extern void func_8007AF98(void *);
extern u8 *func_8007C1BC(u8 *, void *, u8 *, s32);
extern void func_8007CD44(u8 *);
extern void osWritebackDCacheAll(void);

void func_8007F3D4(AudioArg *arg0) {
    s32 sp34;
    s32 sp30;
    s32 pad1;
    s32 pad2;

    D_800E28AC = 0;
    if ((D_800E44A8 == 0xA) && (D_800E2828 == (u8 *) arg0)) {
        return;
    }
    func_80029760(D_800EE4AC, arg0, (arg0->unk8 == 0) ? D_800F22C0 : arg0->unk8);
    if ((D_8010B7C4 == arg0) && (D_80109DA4 != 0x135)) {
        func_80029760(D_800EE4D0);
        return;
    }
    if ((D_800E2828 == (u8 *) arg0) && (D_8010A210 != 3)) {
        func_80029760(D_800EE4E8);
        func_8007ACE8(&D_80109DC0);
        func_8007ADF8(&D_80109DC0);
    }
    D_8010B7C4 = 0;
    func_8007CD44(D_8010B358);
    func_8007AF98(D_8010B358);
    func_80029760(D_800EE51C, arg0, arg0->unk8);
    D_800E2868 = arg0->unkC;
    sp30 = (s32) arg0->unk6;
    if (arg0->unk8 == 0) {
        D_8010B7BC = D_800F22C0;
    } else {
        D_8010B7BC = arg0->unk8;
    }
    func_8007BDCC(D_8010B358, 1, 0x10);
    D_8010B6A8 = D_8010B7BC;
    D_8010B7BC += arg0->unk4 * 0x18;
    func_80033470();
    for (sp34 = 0; sp34 < (s32) arg0->unk4; ++sp34) {
        func_8008012C((void *) 0x80000400, sp30++);
        D_8010B7BC = func_8007C1BC(D_8010B358, (void *) 0x80000400, D_8010B7BC, 3);
    }
    func_80029760(D_800EE538, D_8010B7BC, D_8010B7BC - arg0->unk8);
    if ((u32) D_8010B7BC >= 0x803B5001U) {
        func_8002AF20(D_800EE560, D_800EE578);
    }
    D_8010B7C4 = arg0;
    if (D_800E2838 == (u8 *) arg0) {
        D_8010B7C4 = D_800E2828;
    }
    func_8007AEE0(D_8010B358);
    D_800E28AC = 0;
    osWritebackDCacheAll();
}

extern s32 D_800DFE84;
extern s32 D_800DF778;
extern s32 D_800E28C0;
extern s8 D_800E2AC4;
extern s16 D_8013FAD0;
extern s16 D_8015D980;
extern char D_800EE584[];
extern char D_800EE598[];
extern char D_800EE5AC[];
extern char D_800EE5C0[];
extern char D_800EE5D0[];
extern char D_800EE60C[];
extern char D_800EE620[];
extern void func_8002AF20(char *, char *);
extern void func_800335A8(s32);
extern void func_8007EAD0(s32);
extern void func_80079B80(s32, AudioMgr *);
extern void func_8007ACF4(AudioMgr *);
void loadsong(u32 arg0, AudioMgr *arg1) {
    s32 sp34;
    s16 sp32;
    u16 sp30;
    u8 sp2F;
    s32 sp28;

    sp2F = 0;
    if ((arg0 < 0x100) && (arg1->unk157C == arg0)) {
        arg1->unk1580 = 1;
        return;
    }
    if (arg0 >= 0x201) {
        func_8002AF20(D_800EE584, D_800EE598);
    }
    if ((D_800E44A8 == 0xA) && (D_800E2828 == D_8010B7C4)) {
        arg1->unk1580 = 1;
        func_80029760(D_800EE5AC);
        return;
    }
    if ((arg0 > D_800E28E4) && (arg0 < 0x100)) {
        func_80029760(D_800EE5C0);
        arg1->unk1580 = 1;
        return;
    }
    if ((arg0 >= 0x100) && (D_800E2828 == D_8010B7C4)) {
        func_80029760(D_800EE5D0);
        arg1->unk1580 = 1;
    }
    func_80029760(D_800EE60C, arg0);
    D_800DFE84 = 1;
    D_800DF778 = 0;
    if (&D_80107290 == arg1) {
        sp28 = 0;
        sp32 = arg1->unk1578;
        sp30 = (u16) sp32 / 10;
        do {
            arg1->unk1578 -= sp30;
            sp2F += 1;
            func_80079B80((arg1->unk157C >= 0xE && arg1->unk157C < 0x64) ? (arg1->unk1578 - 0x2000) : arg1->unk1578, arg1);
            sp34 = D_800E28C0 + 2;
            sp28 = 0x14;
            if (sp2F == 0) {
                while (sp28--) {
                }
            }
        } while ((s32) sp2F < 0xA);
        arg1->unk1578 = 0;
    }
    arg1->unk157C = arg0;
    arg1->unk157E = arg0;
    func_8007ADF8(arg1);
    if (&D_80109DC0 == arg1) {
        func_8007AF98(D_8010B358);
    }
    arg1->unk1594 = 0;
    func_80033470();
    func_8008012C((void *) 0x80000400, arg0);
    if ((arg1 == &D_80108828) || (arg1 == &D_80109DC0)) {
        if (arg1 == &D_80108828) {
            arg1->unk158C = (u8 *) 0x80349910;
        } else {
            arg1->unk158C = D_800F22C0;
        }
        func_80079B80(0x7FFF, arg1);
        func_80079E68(arg1, (void *) 0x80000400, arg1->unk158C, 2);
    } else {
        func_80079B80(D_800E28E8 & 0x7FFF, arg1);
        D_8010B7BC = func_80079E68(arg1, (void *) 0x80000400, arg1->unk158C, 2);
    }
    if ((D_8013FAD0 == 0) && (arg1 == &D_80107290)) {
        if ((D_8015D980 == 1) || (D_800E2AC4 == 0)) {
            func_8007EAD0(0x9C40);
        } else {
            func_8007EAD0(0x7530);
        }
    }
    arg1->unk1574 = 0x4E20;
    arg1->unk157A = 0;
    arg1->unk1580 = 0;
    while (arg1->unk1580 == 0) {
        func_8007FE4C(arg1);
    }
    func_8007ACF4(arg1);
    func_80029760(D_800EE620, arg1->unk1570 - (s32) arg1->unk158C, (s32) arg1->unk158C, arg1->unk1570);
    func_800335A8(0xA);
    D_800DFE84 = 0;
    D_800DF778 = 1;
}

extern s16 D_800E44A8;
extern u8 D_800E2828[];
extern char D_800EE640[];
extern char D_800EE654[];
extern char D_800EE670[];
extern char D_800EE680[];
extern char D_800EE6B8[];
extern void func_80029760(char *fmt, ...);
extern void func_8007ACF4(AudioMgr *);
void func_8007FC3C(u32 arg0, AudioMgr *arg1) {
    if ((D_800E44A8 == 10) && (D_8010B7C4 == D_800E2828)) {
        func_80029760(D_800EE640);
        return;
    }
    func_80029760(D_800EE654, arg0);
    if ((arg0 > D_800E28E4) && (arg0 < 0x100)) {
        func_80029760(D_800EE670);
        arg1->unk1580 = 1;
        return;
    }
    if ((arg0 >= 0x100) && (D_8010B7C4 == D_800E2828)) {
        func_80029760(D_800EE680);
        arg1->unk1580 = 1;
    }
    if (arg0 < 0x100) {
        if (arg1->unk157C != arg0) {
            arg1->unk157E = arg0;
            if (arg1->unk157A == 0) {
                arg1->unk157A = 1;
            }
        } else {
            return;
        }
    } else {
        arg1->unk157E = arg0;
        if (arg1->unk157A == 0) {
            arg1->unk157A = 1;
        }
    }
    arg1->unk1580 = 0;
    while (arg1->unk1580 == 0) {
        func_8007FE4C(arg1);
    }
    func_8007ACF4(arg1);
    func_80029760(D_800EE6B8);
}

extern s32 D_800DFE84;
extern u8 *D_800F22C0;
extern void func_8007A088(AudioMgr *);
extern void func_80079B80(s32, AudioMgr *);
extern void func_8007ADF8(AudioMgr *);
extern void func_8007AF98(void *);
extern u8 *func_80079E68(AudioMgr *, void *, u8 *, s32);
void func_8007FE4C(AudioMgr *arg0) {
    s32 sp24 = 0;
    func_8007A088(arg0);
    switch (arg0->unk157A) {
    case 1:
        arg0->unk157A = 0;
        arg0->unk1584 = D_800E28E8 / 20;
        arg0->unk1586 = D_800E28E8;
        arg0->unk157A = 2;
        break;
    case 2:
        arg0->unk1586 -= arg0->unk1584;
        if (arg0->unk1586 == 0) {
            arg0->unk157A = 3;
        }
        if (arg0->unk1586 >= 0x7FFF) {
            arg0->unk157A = 3;
        } else {
            func_80079B80(arg0->unk1586 & 0x7FFF, arg0);
        }
        break;
    case 3:
        arg0->unk157C = arg0->unk157E;
        func_8007ADF8(arg0);
        arg0->unk1594 = 0;
        D_800DFE84 = 1;
        func_80033470();
        if ((arg0 == &D_80108828) || (arg0 == &D_80109DC0)) {
            if (arg0 == &D_80109DC0) {
                func_8007AF98(D_8010B358);
            }
            func_80079B80(0x7FFF, arg0);
            func_8008012C((void *) 0x80000400, arg0->unk157C);
            if (arg0 == &D_80108828) {
                arg0->unk158C = D_800F22C0;
            } else {
                arg0->unk158C = D_800F22C0 + 0x29000;
            }
            func_80079E68(arg0, (void *) 0x80000400, arg0->unk158C, 2);
        } else {
            func_80079B80(D_800E28E8 & 0x7FFF, arg0);
            func_8008012C((void *) 0x80000400, arg0->unk157C);
            D_8010B7BC = func_80079E68(arg0, (void *) 0x80000400, arg0->unk158C, 2);
        }
        arg0->unk1574 = 0x4E20;
        D_800DFE84 = 0;
        arg0->unk157A = 0;
        break;
    default:
        break;
    }
}

extern u8 D_CD7C0[];
extern void *D_80107284;
extern s32 D_80107288;
extern void osWritebackDCacheAll(void);
extern void dmaRomToRam(void *src, void *dst, s32 size);
void func_8008012C(void *arg0, s32 arg1) {
    u16 hdr[4];
    u32 buf[4];
    s16 pad;
    pad = 0;
    osWritebackDCacheAll();
    dmaRomToRam(D_CD7C0, hdr, 2);
    dmaRomToRam(&D_CD7C0[arg1 * 4 + 2], buf, 4);
    dmaRomToRam(&D_CD7C0[((arg1 + 1) << 2) + 2], buf + 2, 4);
    D_80107284 = arg0;
    D_80107288 = buf[2] - buf[0];
    dmaRomToRam(&D_CD7C0[buf[0]], D_80107284, D_80107288);
    osWritebackDCacheAll();
}
