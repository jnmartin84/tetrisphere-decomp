#define AE_KR_STARTVOICEPARAMS
#include "common.h"
void alSynStartVoiceParams(void *s, void *voice, void *w, f32 pitch, s16 vol, s32 pan, u8 fxmix, s32 t);

typedef struct { s32 unk0; s32 unk4; u8 unk8; s16 unkA; } Entry;

extern s32 func_8007979C(u8 *p);
void func_80079A80(u8 *m) {
    *(u16 *)(m + 0x1564) = *(u16 *)(m + 0x1564) & 0xFF;
    *(u16 *)(m + 0x1566) = *(u16 *)(m + 0x1566) & 0xFF;
    if (*(u8 *)(m + 0x1565) != *(u8 *)(m + 0x1567)) {
        do {
            *(u8 *)(m + 0x1464 + *(u8 *)(m + 0x1567)) = func_8007979C(m + 0x454);
            *(u16 *)(m + 0x1566) = (*(u16 *)(m + 0x1566) + 1) & 0xFF;
        } while (*(u8 *)(m + 0x1565) != *(u8 *)(m + 0x1567));
    }
}

void func_80079B0C(u8 *m) {
    s32 i;
    *(u16 *)(m + 0x1564) = 0;
    *(u16 *)(m + 0x1566) = 0;
    *(u32 *)(m + 0x1568) = 0;
    for (i = 0; i != 0x100; i++) {
        *(u8 *)(m + 0x1464 + (u8)i) = func_8007979C(m + 0x454);
    }
}

/* first param is a 4-byte struct passed by value -> IDO homes a0 (dead store); body empty */
typedef struct { s32 x; } S;
void func_80079B78(S a) {
}

void func_80079B80(S a, u8 *mgr)
{
  u16 song = *((u16 *) (mgr + 0x157C));
  u16 v = (&a)->x ^ ((*((u16 *) (mgr + 0x157C))) * 0);
  if ((song >= 14) && (song < 100))
  {
    v = v + 0x2000;
  }
  *((u16 *) (mgr + 0x1578)) = v;
  *((u8 *) (mgr + 0x1583)) = 1;
}

void func_80079BC0(S a, u8 *mgr)
{
  *((u8 *) (mgr + ((unsigned long long) 0x1589))) = a.x & 0xFFu;
  *((u8 *) (mgr + 0x1588)) = 1;
}

extern u16 D_800E28EC;
extern u16 D_80104910[];

void func_80079BD4(arg0)
u16 arg0;
{
    u16 i;

    if (arg0 >= 0x8000) {
        arg0 = 0x7FFF;
    }
    D_800E28EC = arg0;
    for (i = 0; i < 0x100; i++) {
        D_80104910[i] = (sqrtf(i) * arg0) / (f32)16;
    }
}

extern s32 func_8007B124();

void func_80079D3C(arg0, arg1, arg2, arg3, arg4, arg5)
void *arg0;
void *arg1;
void *arg2;
u8 arg3;
s16 arg4;
u8 arg5;
{
    s32 var_s1;
    ALVoiceConfig cfg;
    s32 var_s2;
    s32 bound;

    ((u8 *) arg0)[0x450] = 0;
    *(void **) ((u8 *) arg0 + 0x14) = alGlobals;
    *(u32 *) ((u8 *) arg0 + 0x1574) = 0x4E20;
    ((u8 *) arg0)[0x156C] = 0;
    ((u8 *) arg0)[0x156D] = 1;
    ((u8 *) arg0)[0x1583] = 0;
    ((u8 *) arg0)[0x1588] = 0;
    ((u8 *) arg0)[0x1580] = 0;
    ((u8 *) arg0)[0x156E] = 0;
    *(u16 *) ((u8 *) arg0 + 0x157A) = 0;
    *(u16 *) ((u8 *) arg0 + 0x157C) = 0;
    ((u8 *) arg0)[0x1581] = 0;
    *(u16 *) ((u8 *) arg0 + 0x157E) = 0;
    ((u8 *) arg0)[0x1582] = 0;
    *(s16 *) ((u8 *) arg0 + 0x1578) = arg4;
    *(u16 *) ((u8 *) arg0 + 0x1586) = 0x7FFF;
    *(u16 *) ((u8 *) arg0 + 0x1584) = 0;
    ((u8 *) arg0)[0x1594] = 0;
    ((u8 *) arg0)[0x1595] = 0;
    *(void **) ((u8 *) arg0 + 0x438) = arg1;
    *(void **) ((u8 *) arg0 + 0x43C) = arg2;
    ((u8 *) arg0)[0x158A] = arg5;
    *(s32 *) ((u8 *) arg0 + 0x0) = 0;
    *(void **) ((u8 *) arg0 + 0x8) = &func_8007B124;
    *(void **) ((u8 *) arg0 + 0x4) = arg0;
    *(s32 *) ((u8 *) arg0 + 0xC) = 0;
    alSynAddPlayer(alGlobals, arg0);
    cfg.priority = 0xA;
    cfg.fxBus = 0;
    cfg.unityPitch = 0;
    if (arg3 != 0) {
        var_s1 = 0;
        bound = arg3;
        if (arg3 > 0) {
            var_s2 = 0;
            do {
                alSynAllocVoice(*(void **) ((u8 *) arg0 + 0x14), *(u8 **) ((u8 *) arg0 + 0x43C) + var_s2, &cfg);
                var_s1 += 1;
                var_s2 += 0x2C;
            } while (var_s1 != bound);
        }
    }
}

extern OSMesgQueue D_80104B10, D_80104B48, D_80104B80, D_80104BB8;
extern OSMesg D_80104B28[8], D_80104B60[8];
extern void func_80079660();
extern void func_8007E63C();
extern void func_8007E6A0();

u8 *func_80079E68(mgr, src, dst, cmd)
u8 *mgr;
u8 *src;
u8 *dst;
u8 cmd;
{
    s32 n;
    s32 i;
    u8 *voice;
    u8 *hdr;
    u8 *q;
    u8 *p;
    s32 len;
    s8 c;
    s32 m;
    s32 w;

    if (cmd == 2) {
        i = 0;
        n = 0x2C0;
        do {
            voice = *(u8 **)(mgr + 0x43C) + i;
            if (voice[0x27] == 0) {
            } else {
                voice[0x27] = 0;
                alSynStopVoice(*(void **)(mgr + 0x14), voice);
            }
            i += 0x2C;
        } while (i != n);
    }
    if (cmd == 1) {
        osCreateMesgQueue(&D_80104B10, D_80104B28, 8);
        osCreateMesgQueue(&D_80104B48, D_80104B60, 8);
        osCreateMesgQueue(&D_80104B80, D_80104B28, 8);
        osCreateMesgQueue(&D_80104BB8, D_80104B60, 8);
    }
    func_8007E63C(src, mgr + 0x418);
    src += 0xE;
    *(u8 **)(mgr + 0x444) = dst;
    *(u8 **)(mgr + 0x448) = dst;
    *(s32 *)(mgr + 0x440) = *(u8 *)(mgr + 0x41C);
    *(s32 *)(mgr + 0x420) = *(s32 *)(mgr + 0x420) - 4;
    dst += *(s32 *)(mgr + 0x420);
    dst += 0x3F;
    dst = (u8 *)((s32)dst & ~0x3F);
    hdr = *(u8 *)(mgr + 0x41D) * 0x10 + src;
    *(s32 *)(mgr + 0x44C) = hdr[3] + (hdr[2] << 8) + (hdr[1] << 16) + (hdr[0] << 24);
    hdr += 4;
    p = *(u8 **)(mgr + 0x444);
    n = *(s32 *)(mgr + 0x420);
    while (n--) {
        *p++ = *(s8 *)hdr;
        hdr++;
    }
    func_80079660(*(u8 **)(mgr + 0x444), mgr + 0x454);
    func_80079B0C(mgr);
    n = 0;
    q = mgr + 0x18;
    while (n < *(u8 *)(mgr + 0x41D)) {
        func_8007E6A0(src, q);
        n++;
        q += 0x10;
        src += 0x10;
    }
    *(u8 **)(mgr + 0x1570) = dst;
    *(u8 *)(mgr + 0x156E) = 0;
    *(u8 *)(mgr + 0x156C) = 1;
    *(u8 *)(mgr + 0x156D) = 1;
    return dst;
}

/* func_8007A088 -- FULL MATCH (2026-09-05 round 2, matchdiff FULL MATCH on clone ~/wt/ch1 @ 3cdbabe).
   Built on the landed sibling func_8007C1BC idioms (while (k--) counts, single-statement 16-trip loops for the
   x4 unroller, u32 record fields, no n local: unk18 re-read and PRE-reloaded after the loops).
   Round 2 levers: per-arm step-loop locals (acc/step vs acc2/step2: one shared var was one web spanning both
   arms with doubled adjsave), d2 before sp, typed-pointer index for rec, member-array view of sp in the copy
   loops, member-form unk18 reads (leaf weight). Signature: void f(AudioMgr *) (K&R u8 *m, TU byte-offset idiom). */

typedef struct { u8 pad[0x18]; u32 unk18; u32 unk1C; u32 unk20; u16 unk24; u16 unk26; } Rec7A;
extern u32 lwDecode();
extern void func_8007AC44();
extern s16 func_8007E710(u8 *p);

void func_8007A088(m)
u8 *m;
{
    s32 idx;
    u8 *rec;
    u8 *PP;
    u8 *QQ;
    u8 *d2;
    s32 i;
    u8 acc;
    u8 step;
    u8 acc2;
    u8 step2;
    s32 k;
    u8 *sp;

    if (*(u8 *)(m + 0x156C) != 0) {
        if (*(u8 *)(m + 0x156D) != 1) {
            *(u8 *)(m + 0x156D) = *(u8 *)(m + 0x156D) - 1;
        } else {
            *(u8 *)(m + 0x156D) = 1;
            func_80033470();
            idx = *(u8 *)(m + 0x156E);
            rec = (u8 *)&((struct { u8 b[0x10]; } *)m)[idx];
            if (*(u16 *)(rec + 0x24) & 1) {
                func_8007AC44(0x80000400, *(u16 *)(rec + 0x26));
                lwDecode((void *)0x80000400, *(s32 *)(m + 0x1570));
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14)) = *(s32 *)(m + 0x1570);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0x640) = *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                if (*(u16 *)(rec + 0x24) & 4) {
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 4) = ((Rec7A *)rec)->unk18 * 2;
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0x780) = ((Rec7A *)rec)->unk18 * 2;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 8) = 1;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 9) = 0xFF;
                    PP = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    d2 = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    k = ((Rec7A *)rec)->unk18;
                    while (k--) {
                        *(s16 *)d2 = (u16)(*(s8 *)(PP + 1) << 8) + (*(s8 *)PP & 0xFF);
                        d2 += 2;
                        PP += 2;
                    }
                    *(s32 *)(m + 0x1570) = *(s32 *)(m + 0x1570) + (((Rec7A *)rec)->unk18 * 2);
                    *(s32 *)(m + 0x1570) = (*(s32 *)(m + 0x1570) + 0x1F) & ~0xF;
                    if (*(u16 *)(rec + 0x24) & 4) {
                        d2 = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                        sp = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                        if (*(u16 *)(rec + 0x24) & 8) {
                            for (i = 0; i < 0x10; i++) {
                                ((s16 *)(d2 + (*(u32 *)(rec + 0x20) * 2)))[i] = ((struct { s16 v[1]; } *)sp)->v[*(u32 *)(rec + 0x1C) - i - 1];
                            }
                        } else {
                            for (i = 0; i < 0x10; i++) {
                                ((s16 *)(d2 + (*(u32 *)(rec + 0x20) * 2)))[i] = ((struct { s16 v[1]; } *)sp)->v[*(u32 *)(rec + 0x1C) + i];
                            }
                        }
                    }
                } else {
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 4) = ((Rec7A *)rec)->unk18;
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0x780) = ((Rec7A *)rec)->unk18;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 8) = 2;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 9) = 0xFF;
                    QQ = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    PP = QQ;
                    k = ((Rec7A *)rec)->unk18;
                    while (k--) {
                        *(s8 *)QQ = func_8007E710(PP) >> 8;
                        PP += 2;
                        QQ += 1;
                    }
                    *(s32 *)(m + 0x1570) = *(s32 *)(m + 0x1570) + ((Rec7A *)rec)->unk18;
                    *(s32 *)(m + 0x1570) = (*(s32 *)(m + 0x1570) + 0x1F) & ~0xF;
                    QQ = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    acc = 0;
                    step = *(s8 *)(QQ + ((Rec7A *)rec)->unk18) >> 4;
                    for (i = 0; i < 0x10; i++) {
                        *(s8 *)(QQ + i + ((Rec7A *)rec)->unk18) = *(s8 *)(QQ + ((Rec7A *)rec)->unk18) - acc;
                        acc += step;
                    }
                }
            } else {
                func_8007AC44(*(s32 *)(m + 0x1570), *(u16 *)(rec + 0x26));
                lwDecode(*(s32 *)(m + 0x1570), (u8 *)0x80000400);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14)) = *(s32 *)(m + 0x1570);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0x640) = *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                if (*(u16 *)(rec + 0x24) & 4) {
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 4) = ((Rec7A *)rec)->unk18 * 2;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 8) = 1;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 9) = 0xFF;
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0x780) = ((Rec7A *)rec)->unk18 * 2;
                    d2 = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    PP = (u8 *)0x80000400;
                    k = ((Rec7A *)rec)->unk18;
                    while (k--) {
                        *(s16 *)d2 = *(s8 *)PP << 8;
                        d2 += 2;
                        PP += 1;
                    }
                    *(s32 *)(m + 0x1570) = *(s32 *)(m + 0x1570) + (((Rec7A *)rec)->unk18 * 2);
                    *(s32 *)(m + 0x1570) = (*(s32 *)(m + 0x1570) + 0x1F) & ~0xF;
                    d2 = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    sp = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    if (*(u16 *)(rec + 0x24) & 8) {
                        for (i = 0; i < 0x10; i++) {
                            ((s16 *)(d2 + (*(u32 *)(rec + 0x20) * 2)))[i] = ((struct { s16 v[1]; } *)sp)->v[*(u32 *)(rec + 0x1C) - i - 1];
                        }
                    } else {
                        for (i = 0; i < 0x10; i++) {
                            ((s16 *)(d2 + (*(u32 *)(rec + 0x20) * 2)))[i] = ((struct { s16 v[1]; } *)sp)->v[*(u32 *)(rec + 0x1C) + i];
                        }
                    }
                } else {
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 4) = ((Rec7A *)rec)->unk18;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 8) = 2;
                    *(u8 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 9) = 0xFF;
                    *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0x780) = ((Rec7A *)rec)->unk18;
                    QQ = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    PP = (u8 *)0x80000400;
                    k = ((Rec7A *)rec)->unk18;
                    while (k--) {
                        *QQ = *(s8 *)PP;
                        QQ += 1;
                        PP += 1;
                    }
                    *(s32 *)(m + 0x1570) = *(s32 *)(m + 0x1570) + ((Rec7A *)rec)->unk18;
                    *(s32 *)(m + 0x1570) = (*(s32 *)(m + 0x1570) + 0x1F) & ~0xF;
                    QQ = *(u8 **)((*(u8 **)(m + 0x438)) + (idx * 0x14));
                    acc2 = 0;
                    step2 = *(s8 *)(QQ + ((Rec7A *)rec)->unk18) >> 4;
                    for (i = 0; i < 0x10; i++) {
                        *(s8 *)(QQ + i + ((Rec7A *)rec)->unk18) = *(s8 *)(QQ + ((Rec7A *)rec)->unk18) - acc2;
                        acc2 += step2;
                    }
                }
            }
            if (*(u16 *)(rec + 0x24) & 4) {
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 0xC) = (s32)((*(u8 **)(m + 0x438)) + (idx * 0xC) + 0xB40);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0xC) + 0xB40) = *(u32 *)(rec + 0x1C);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0xC) + 0xB44) = *(u32 *)(rec + 0x20);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0x8C0) = *(u32 *)(rec + 0x1C);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 4) + 0xA00) = *(u32 *)(rec + 0x20);
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0xC) + 0xB48) = -1;
            } else {
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0x14) + 0xC) = 0;
                *(s32 *)((*(u8 **)(m + 0x438)) + (idx * 0xC) + 0xB48) = 0;
            }
            *(u8 *)(m + 0x156E) = *(u8 *)(m + 0x156E) + 1;
            if (*(u8 *)(m + 0x41D) == *(u8 *)(m + 0x156E)) {
                *(u8 *)(m + 0x156C) = 0;
                for (i = 0; i < 0x10; i++) {
                    *(s32 *)((*(u8 **)(m + 0x43C)) + (i * 0x2C) + 0x1C) = *(s32 *)(m + 0x438);
                    *(f32 *)((*(u8 **)(m + 0x43C)) + (i * 0x2C) + 0x20) = 1.0f;
                    *(s16 *)((*(u8 **)(m + 0x43C)) + (i * 0x2C) + 0x24) = 0;
                    *(u8 *)((*(u8 **)(m + 0x43C)) + (i * 0x2C) + 0x26) = 0x40;
                    *(u8 *)((*(u8 **)(m + 0x43C)) + (i * 0x2C) + 0x27) = 0;
                }
                *(u8 *)(m + 0x1580) = 1;
                osWritebackDCacheAll();
            }
        }
    }
}

extern u8 D_1DC6C0[];
extern void dmaRomToRam(void *src, void *dst, s32 size);

void func_8007AC44(dst, idx)
void *dst;
u16 idx;
{
    u16 hdr[4];
    u32 buf[4];

    dmaRomToRam(D_1DC6C0, hdr, 2);
    dmaRomToRam(&D_1DC6C0[idx * 4 + 2], buf, 4);
    dmaRomToRam(&D_1DC6C0[((idx + 1) << 2) + 2], buf + 2, 4);
    dmaRomToRam(&D_1DC6C0[buf[0]], dst, buf[2] - buf[0]);
}

/* mgr is AudioMgr* (0x1594-byte struct, e.g. D_80107290); byte @0x1595 */
void func_8007ACE8(u8 *mgr) {
    *(u8 *)(mgr + 0x1595) = 1;
}

void func_8007ACF4(u8 *mgr) {
    *(u8 *)(mgr + 0x1595) = 0;
}

typedef struct { s16 unk0; s16 pad2; void *unk4; } AudioCmd;
typedef struct { u8 pad88[0x88]; u32 unk88; } AudioMgr;
extern s32 D_800DFE84, D_800DF778;
extern AudioCmd D_80104BF0;
extern AudioMgr D_80108828, D_80109DC0;
extern OSMesgQueue D_80104B10, D_80104B48;
extern void func_80029760();
extern char D_800EE0D0[], D_800EE0F0[], D_800EE0FC[], D_800EE108[], D_800EE114[];
extern char D_800EE130[], D_800EE150[], D_800EE15C[], D_800EE168[], D_800EE174[];

void func_8007ACFC(void *arg) {
    OSMesg msg[4];
    s32 saved = D_800DFE84;
    char *s;
    char *nv;
    D_800DFE84 = 1;
    D_800DF778 = 0;
    if (((u8 *)arg)[0x1595] == 0) {
        if (((u8 *)arg)[0x450] != 1) {
            if (arg == &D_80108828) {
                s = D_800EE0F0;
            } else {
                nv = (arg == &D_80109DC0) ? D_800EE0FC : D_800EE108;
                s = nv;
            }
            func_80029760(D_800EE0D0, s);
            D_80104BF0.unk0 = 1;
            D_80104BF0.unk4 = arg;
            osJamMesg(&D_80104B10, &D_80104BF0, 0);
            osRecvMesg(&D_80104B48, &msg[3], 1);
            func_80029760(D_800EE114);
        }
    }
    D_800DFE84 = saved;
    D_800DF778 = 1;
}

void func_8007ADF8(void *arg) {
    s64 msg;
    char *s;
    s32 saved = D_800DFE84;
    char *nv;
    D_800DFE84 = 1;
    D_800DF778 = 0;
    func_8007ACE8(arg);
    D_80104BF0.unk0 = 0;
    D_80104BF0.unk4 = arg;
    if (arg == &D_80108828) {
        s = D_800EE150;
    } else {
        nv = (arg == &D_80109DC0) ? D_800EE15C : D_800EE168;
        s = nv;
    }
    func_80029760(D_800EE130, s);
    osJamMesg(&D_80104B10, &D_80104BF0, 0);
    osRecvMesg(&D_80104B48, (OSMesg *)&msg, 1);
    func_80029760(D_800EE174);
    D_800DFE84 = saved;
    D_800DF778 = 1;
}

extern s32 D_800DFE84, D_800DF778;
extern AudioCmd D_80104BF8;
extern OSMesgQueue D_80104B80, D_80104B48;
extern const char D_800EE190[], D_800EE1B4[];
extern void func_80029760();
void func_8007AEE0(AudioMgr *arg) {
    OSMesg msg[2];
    s32 saved = D_800DFE84;
    D_800DFE84 = 1;
    D_800DF778 = 0;
    if (arg->unk88 != 1) {
        func_80029760(D_800EE190);
        D_80104BF8.unk0 = 1;
        D_80104BF8.unk4 = arg;
        osJamMesg(&D_80104B80, &D_80104BF8, 0);
        osRecvMesg(&D_80104B48, &msg[1], 1);
        func_80029760(D_800EE1B4);
    }
    D_800DFE84 = saved;
    D_800DF778 = 1;
}

extern s32 D_800DFE84;
extern s32 D_800DF778;
extern OSMesgQueue D_80104B80;
extern OSMesgQueue D_80104B48;
extern const char D_800EE1E0[];
extern const char D_800EE204[];
void func_8007AF98(void *arg) {
    s64 msg;
    s32 saved = D_800DFE84;
    D_800DFE84 = 1;
    D_800DF778 = 0;
    D_80104BF8.unk4 = arg;
    D_80104BF8.unk0 = 0;
    func_80029760(D_800EE1E0);
    osJamMesg(&D_80104B80, &D_80104BF8, 0);
    osRecvMesg(&D_80104B48, (OSMesg*)&msg, 1);
    func_80029760(D_800EE204);
    D_800DFE84 = saved;
    D_800DF778 = 1;
}

extern AudioCmd D_80104BF0;
extern AudioMgr D_80108828;
extern AudioMgr D_80109DC0;
extern OSMesgQueue D_80104B10;
extern char D_800EE230[];
extern char D_800EE250[];
extern char D_800EE25C[];
extern char D_800EE268[];
extern void func_80029760();
extern void func_8007ADF8(void *);
void func_8007B038(void *arg) {
  void *msg;
  s32 saved = D_800DFE84;
  char *new_var;
  char *s;
  D_800DFE84 = 1;
  /* empty at _FINALROM (a debug check); it is LOAD-BEARING -- removing it
   * reorders the arg home against the D_800DF778 store. */
  if (!arg) {
  }
  D_800DF778 = 0;
  s = D_800EE250;
  func_8007ADF8(arg);
  func_8007ACF4(arg);
  D_80104BF0.unk0 = 4;
  D_80104BF0.unk4 = arg;
  if (arg == (&D_80108828))
  {
    s = D_800EE250;
  }
  else
  {
    new_var = (arg == (&D_80109DC0)) ? (D_800EE25C) : (D_800EE268);
    s = new_var;
  }
  func_80029760(D_800EE230, s);
  osJamMesg(&D_80104B10, &D_80104BF0, 0);
  osRecvMesg(&D_80104B48, &msg, 1);
  D_800DFE84 = saved;
  D_800DF778 = 1;
}

typedef struct { s32 unk0; s32 unk4; s16 unk8; u8 padA[2]; s32 unkC; s32 unk10; } EngParam;
/* func_8007B124 -- audio_engine per-frame sequencer tick (810 instructions). */

typedef struct { u8 bytes[0]; } BEmpty; typedef struct { u8 value; } BByte; typedef struct { s32 unk0; s32 unk4; s32 unk8; } BLoop; /* 0xC */
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  unk9;
    /* 0x0A */ u8  padA[2];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} BWav; /* 0x14 */

typedef struct {
    /* 0x000 */ BWav  wav[80];
    /* 0x640 */ s32   unk640[80];
    /* 0x780 */ s32   unk780[80];
    /* 0x8C0 */ s32   unk8C0[80];
    /* 0xA00 */ s32   unkA00[80];
    /* 0xB40 */ BLoop loop[80];
} BBank;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} BPos; /* 0x8 */

typedef struct {
    /* 0x00 */ u8   pad0[8];
    /* 0x08 */ struct BSyn *unk8;
    /* 0x0C */ u8   padC[8];
    /* 0x14 */ u16  unk14;
    /* 0x16 */ u8   pad16[6];
    /* 0x1C */ BPos *unk1C;
    /* 0x20 */ f32  unk20;
    /* 0x24 */ s16  unk24;
    /* 0x26 */ s8   unk26;
    /* 0x27 */ u8   unk27;
    /* 0x28 */ s16  unk28;
    /* 0x2A */ u8   pad2A[2];
} BVoice; /* 0x2C */

typedef struct { u8 pad0[0x1C]; s32 unk1C; } BSynth;

typedef struct BSyn {
    /* 0x00 */ u8   pad0[0xC];
    /* 0x0C */ struct BDrv *unkC;
    /* 0x10 */ u8   pad10[0xC8];
    /* 0xD8 */ s32  unkD8;
} BSyn;

typedef struct BDrv {
    /* 0x00 */ u8   pad0[8];
    /* 0x08 */ void (*unk8)();
} BDrv;

typedef EngParam BParam;








typedef struct {
    /* 0x0000 */ u8     pad0[0x14];
    /* 0x0014 */ BSynth *synth;
    /* 0x0018 */ u8     pad18[0x410];
    /* 0x0428 */ u8     idx[16];
    /* 0x0438 */ BBank *bank;
    /* 0x043C */ u8    *voices;
    /* 0x0440 */ s32    nvoice;
    /* 0x0444 */ u8    *unk444;
    /* 0x0448 */ u8    *unk448;
    /* 0x044C */ u32    unk44C;
    /* 0x0450 */ u8     state;
    /* 0x0451 */ u8     pad451[3];
    /* 0x0454 */ u8     strm[0x1010];
    /* 0x1464 */ u8     ring[0x100];
    /* 0x1564 */ u16    rd;
    /* 0x1566 */ u16    wr;
    /* 0x1568 */ u32    ctr;
    /* 0x156C */ u8     pad156C[8];
    /* 0x1574 */ s32    tempo;
    /* 0x1578 */ s16    vol;
    /* 0x157A */ u8     pad157A[8];
    /* 0x1582 */ u8     delay;
    /* 0x1583 */ u8     volDirty;
    /* 0x1584 */ u8     pad1584[4];
    /* 0x1588 */ u8     panDirty;
    /* 0x1589 */ s8     pan;
    /* 0x158A */ u8     loopFlag;
    /* 0x158B */ u8     pad158B[9];
    /* 0x1594 */ u8     wbFlag;
} BMgr;

typedef struct { s16 op; s16 pad2; BMgr *mgr; } BMsg;

extern OSMesgQueue D_80104B10, D_80104B48;
extern char D_800EE274[], D_800EE28C[], D_800EE2A4[];
extern s32 D_800E2850[];
extern void func_80029760();
extern void func_80079660();
extern void func_80079A80();
extern void func_80079B0C();
extern f32 func_8007E36C(u16 arg);
extern BParam *__allocParam();

s32 func_8007B124(BMgr *m)
{
    BMgr *mm;
    s32 i;
    s32 off;
    BVoice *v;
    BMgr *g;
    BDrv *drv;
    BParam *pp;
    u8 c;
    u8 b;
    s32 nv;
    u32 cursor;
    BMsg *msg;
    s32 st;

    mm = m;
    if (osRecvMesg(&D_80104B10, (OSMesg *)&msg, 0) == 0) {
        g = msg->mgr;
        switch (msg->op) {
        case 0:
            func_80029760(D_800EE274);
            i = 0;
            off = 0;
            if (g->nvoice > 0) {
                do {
                    v = (BVoice *)(g->voices + off);
                    if (v->unk27 != 0) {
                        v->unk27 = 0;
                        alSynStopVoice(g->synth, v);
                    }
                    i++;
                    off += 0x2C;
                } while (i < g->nvoice);
            }
            g->state = 3;
            osSendMesg(&D_80104B48, 0, 0);
            msg->op = 0;
            return g->tempo;
        case 1:
            func_80029760(D_800EE28C);
            g->state = 1;
            msg->op = 0;
            osSendMesg(&D_80104B48, 0, 0);
            break;
        case 4:
            func_80029760(D_800EE2A4);
            g->delay = 0;
            func_80079660(g->unk444, g->strm);
            func_80079B0C(g);
            msg->op = 0;
            osSendMesg(&D_80104B48, 0, 0);
            return g->tempo;
        default:
            msg->op = 0;
            break;
        }
    }
    st = m->state;
    if (st == 3) {
        return m->tempo;
    }
    if ((s32)(st + (u32)st * 0) == 1) {
        if (m->ctr >= m->unk44C) {
            if (m->loopFlag != 0) {
                i = 0;
                off = 0;
                if (m->nvoice > 0) {
                    do {
                        v = (BVoice *)(m->voices + off);
                        if (v->unk27 != 0) {
                            v->unk27 = 0;
                            alSynStopVoice(m->synth, v);
                        }
                        v->unk14 = 0;
                        i++;
                        off += 0x2C;
                    } while (i < mm->nvoice);
                }
                m->delay = 0;
                m->unk444 = m->unk448;
                func_80079660(m->unk444, m->strm);
                func_80079B0C(m);
            } else {
                m->state = 0;
            }
            return m->tempo;
        }
        func_80079A80(m);
        if (m->volDirty != 0) {
            i = 0;
            off = 0;
            if (m->nvoice > 0) {
                do {
                    v = (BVoice *)(m->voices + off);
                    if (v->unk27 != 0) {
                        if (v->unk28 == 0) {
                            v->unk28 = 1;
                        }
                        v->unk24 = (u32)((sqrtf((f32)v->unk28) * (f32)m->vol) / (f32)16);
                        alSynSetVol(m->synth, v, v->unk24, 1);
                    }
                    i += 1 + off * 0;
                    off += 0x2C + i * 0;
                } while (i < mm->nvoice);
            }
            m->volDirty = 0;
        }
        i = 0;
        if (m->panDirty != 0) {
            off = 0;
            if (m->nvoice > 0) {
                do {
                    v = (BVoice *)(m->voices + off);
                    if (v->unk27 != 0) {
                        v->unk26 = m->pan;
                        alSynSetPan(m->synth, (BVoice *)((u8 *)v + off * 0), v->unk26);
                    }
                    i += 1 + off * 0;
                    off += 0x2C + i * 0;
                } while (i < mm->nvoice);
                i = 0;
            }
            m->panDirty = 0;
        }
        if (m->nvoice > 0) {
            off = 0;
            do {
                v = (BVoice *)(m->voices + off);
                if (m->delay != 0) {
                    m->delay = m->delay - 1;
                } else {
                    c = m->ring[(u8)(m->rd & 0xFF)];
                    m->rd = m->rd + 1;
                    m->ctr = m->ctr + 1;
                    if (m->wbFlag == 0) {
                        m->wbFlag = 1;
                        osWritebackDCacheAll();
                    }
                    if (c & 0x80) {
                        m->delay = (u32)c & 0x7F;
                    } else {
                        if ((c & 0x40) != 0) {
                            cursor = (u16)(m->rd * 1);
                            st = ((m->ring[(cursor + 1) & 0xFF] << 8) + ((BByte *)(m->ring + (u8)(cursor & 0xFF)))->value);
                            *(BEmpty *)((u8 *)cursor + 101) = *(BEmpty *)cursor;
                            *(BEmpty *)st = *(BEmpty *)((u8 *)((u32)st) + 32761);
                            *(BEmpty *)((u8 *)cursor + 102) = *(BEmpty *)cursor;
                            *(BEmpty *)((u8 *)c + 203) = *(BEmpty *)c;
                            *(BEmpty *)((u8 *)(s32)c + 204) = *(BEmpty *)(s32)c;
                            *(BEmpty *)((u8 *)((u32)st) + 5) = *(BEmpty *)((u32)st);
                            *(BEmpty *)st = *(BEmpty *)((u8 *)((u32)st) + 32762);
                            *(BEmpty *)((u8 *)((u32)st) + 6) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 7) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 8) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 9) = *(BEmpty *)((u32)st);
                            *(BEmpty *)st = *(BEmpty *)((u8 *)((u32)st) + 32763);
                            *(BEmpty *)((u8 *)((u32)st) + 10) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 11) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 12) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 13) = *(BEmpty *)((u32)st);
                            *(BEmpty *)101 = *(BEmpty *)0;
                            *(BEmpty *)102 = *(BEmpty *)0;
                            *(BEmpty *)((u8 *)((u32)st) + 14) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 15) = *(BEmpty *)((u32)st);
                            *(BEmpty *)st = *(BEmpty *)((u8 *)((u32)st) + 32764);
                            *(BEmpty *)((u8 *)((u32)st) + 16) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 17) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 18) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 19) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 20) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 21) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 22) = *(BEmpty *)((u32)st);
                            *(BEmpty *)201 = *(BEmpty *)301;
                            *(BEmpty *)((u8 *)((u32)st) + 23) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 24) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 25) = *(BEmpty *)((u32)st);
                            *(BEmpty *)202 = *(BEmpty *)302;
                            *(BEmpty *)((u8 *)((u32)st) + 26) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 27) = *(BEmpty *)((u32)st);
                            *(BEmpty *)203 = *(BEmpty *)303;
                            *(BEmpty *)((u8 *)((u32)st) + 28) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 29) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 30) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 31) = *(BEmpty *)((u32)st);
                            *(BEmpty *)204 = *(BEmpty *)304;
                            *(BEmpty *)((u8 *)((u32)st) + 32) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 33) = *(BEmpty *)((u32)st);
                            *(BEmpty *)205 = *(BEmpty *)305;
                            *(BEmpty *)((u8 *)((u32)st) + 34) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 35) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 36) = *(BEmpty *)((u32)st);
                            *(BEmpty *)206 = *(BEmpty *)306;
                            *(BEmpty *)((u8 *)((u32)st) + 37) = *(BEmpty *)((u32)st);
                            *(BEmpty *)103 = *(BEmpty *)0;
                            *(BEmpty *)104 = *(BEmpty *)0;
                            *(BEmpty *)((u8 *)((u32)st) + 38) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 39) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 40) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 41) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 42) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 43) = *(BEmpty *)((u32)st);
                            *(BEmpty *)st = *(BEmpty *)((u8 *)((u32)st) + 32765);
                            *(BEmpty *)((u8 *)((u32)st) + 44) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 45) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 46) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 47) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 48) = *(BEmpty *)((u32)st);
                            cursor = (s32)(u64)(u32)cursor;
                            *(BEmpty *)((u8 *)((u32)st) + 49) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 50) = *(BEmpty *)((u32)st);
                            *(BEmpty *)((u8 *)((u32)st) + 51) = *(BEmpty *)((u32)st);
                            st &= 0xFFFF;
                            m->ctr = m->ctr + 2;
                            m->rd = cursor + 2;
                            st = D_800E2850[(((u32)st) >> 14) & 0xFF] + ((((u32)st) & 0x3FFF) << ((((u32)st) >> 14) & 0xFF)); v->unk20 = func_8007E36C(((u32)st));
                        }
                        if ((u32)(u64)(u32)(c & 0x20) != 0) {
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(BEmpty *)201 = *(BEmpty *)301;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(BEmpty *)202 = *(BEmpty *)302;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(BEmpty *)101 = *(BEmpty *)0;
                            *(BEmpty *)102 = *(BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(BEmpty *)203 = *(BEmpty *)303;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            *(volatile BEmpty *)0 = *(volatile BEmpty *)0;
                            v->unk28 = m->ring[m->rd & 0xFF];
                            m->rd = m->rd + 1;
                            m->ctr = m->ctr + 1 + c * 0;
                            v->unk28 = v->unk28 & 0xFF;
                            if (v->unk28 == 0) {
                                v->unk28 = 1;
                            }
                            v->unk24 = (u32)((sqrtf((f32)v->unk28) * (f32)m->vol) / (f32)16);
                        }
                        cursor = c & 4;
                        if ((c & 0x10) != 0) {
                            v->unk26 = m->ring[(u8)(m->rd & 0xFF)] >> 1;
                            m->rd = m->rd + 1;
                            m->ctr = m->ctr + 1 + c * 0;
                        }
                        if (c & 8) {
                            b = m->ring[(u16)(m->rd * 1) & 0xFF];
                            m->rd = m->rd + 1;
                            m->ctr = m->ctr + 1;
                            v->unk1C = (BPos *)&m->bank->wav[b];
                            mm->idx[i] = b;
                            if (v->unk27 == 1) {
                                drv = v->unk8->unkC;
                                v->unk8->unkD8 = 0x140;
                                pp = __allocParam();
                                if (pp != 0) {
                                    pp->unk4 = m->synth->unk1C;
                                    pp->unkC = 0;
                                    pp->unk8 = 0xB;
                                    pp->unk10 = v->unk8->unkD8 - 0x40;
                                    drv->unk8(drv, 3, pp);
                                }
                                pp = __allocParam();
                                if (pp != 0) {
                                    pp->unk4 = m->synth->unk1C + v->unk8->unkD8;
                                    pp->unk8 = 0xF;
                                    pp->unk0 = 0;
                                    drv->unk8(drv, 3, pp);
                                }
                            }
                        }
                        if ((c & 4) != 0) {
                            nv = m->ring[(u8)(m->rd & 0xFF)] << 8;
                            m->rd = m->rd + 1;
                            m->ctr = m->ctr + 1;
                            v->unk1C->unk0 = m->bank->unk640[m->idx[i]] + nv;

                            v->unk1C->unk4 = m->bank->unk780[m->idx[i]] - (s32)(u32)(v->unk1C->unk0 - m->bank->unk640[m->idx[i]]);
                            if (v->unk27 == 1) {
                                drv = v->unk8->unkC;
                                v->unk8->unkD8 = 0x140;
                                pp = __allocParam();
                                if (pp != 0) {
                                    pp->unk4 = m->synth->unk1C;
                                    pp->unkC = 0;
                                    pp->unk8 = 0xB;
                                    pp->unk10 = v->unk8->unkD8 - 0x40;
                                    drv->unk8(drv, 3, pp);
                                }
                                pp = __allocParam();
                                if (pp != 0) {
                                    pp->unk4 = m->synth->unk1C + v->unk8->unkD8;
                                    pp->unk8 = 0xF;
                                    pp->unk0 = 0;
                                    drv->unk8(drv, 3, pp);
                                }
                            }
                        }
                        st = v[(c & 2) * 0].unk27;
                        if ((c & 2) != 0) {
                            if ((s32)(st + (u32)st * 0) == 1) {
                                drv = v->unk8->unkC;
                                v->unk8->unkD8 = 0x140;
                                pp = __allocParam();
                                if (pp != 0) {
                                    pp->unk4 = m->synth->unk1C;
                                    pp->unkC = 0;
                                    pp->unk8 = 0xB;
                                    pp->unk10 = v->unk8->unkD8 - 0x40;
                                    drv->unk8(drv, 3, pp);
                                }
                                pp = __allocParam();
                                if (pp != 0) {
                                    pp->unk4 = m->synth->unk1C + v->unk8->unkD8;
                                    pp->unk8 = 0xF;
                                    pp->unk0 = 0;
                                    drv->unk8(drv, 3, pp);
                                }
                            }
                            if ((c & 4) != 0) {
                                alSynStartVoiceParams(m->synth, v, v->unk1C, v->unk20, v->unk24, v->unk26, 0, 0x64);
                            } else {
                                alSynStartVoiceParams(m->synth, v, v->unk1C, v->unk20, v->unk24, v->unk26, 0, 1);
                            }
                            v->unk27 = 1;
                            st = v->unk27;
                        }
                        if (st != 0 && (c & 0x40) != 0 && (c & 2) == 0) {
                            alSynSetPitch(m->synth, v, v->unk20);
                            st = v->unk27;
                        }
                        if (st != 0 && (c & 0x20) != 0 && (c & 2) == 0) {
                            v->unk24 = (u32)((sqrtf((f32)v->unk28) * (f32)m->vol) / (f32)16);
                            if ((c & 4) != 0) {
                                alSynSetVol(m->synth, v, v->unk24, 0x64);
                                st = v->unk27;
                            } else {
                                alSynSetVol(m->synth, v, v->unk24, 1);
                                st = v->unk27;
                            }
                        }
                        if (st != 0 && (c & 0x10) != 0 && (c & 2) == 0) {
                            alSynSetPan(m->synth, (BVoice *)((u8 *)v + i * 0), v->unk26);
                        }
                        if (c & 1) {
                            c = m->ring[(u8)(m->rd & 0xFF)];
                            m->rd = m->rd + 1;
                            m->ctr = m->ctr + 1;
                            if (c & 0x40) {
                                m->tempo = 0x07735940 / (m->ring[(u8)(m->rd & 0xFF)] * 0x32);                                 m->rd = m->rd + 1;
                                m->ctr = m->ctr + 1;
                            }
                            if (c & 0x20) {
                                m->rd = m->rd + 1;
                                m->ctr = m->ctr + 1;
                            }
                        }
                    }
                }
                i += 1 + off * 0;
                off += 0x2C + i * 0;
            } while (i < mm->nvoice);
        }
    }
    return m->tempo;
}

/* func_8007BDCC @ ROM 0x5717C (audio_engine, IDO 5.3 -O2 -g0 -mips1)
 * BYTE-EXACT MATCH landed 2026-07-23 (was parked NON_MATCHING with a 5-word residue:
 * ROM keeps p in $a0 for the init-block stores, $s1 after alSynAddPlayer).
 * The crack was NOT a live-range split of p: uopt copypropagate (uoptcopy.c
 * find_replacements) rewrites uses of p to the arrival register $a0 while the implicit
 * p=$a0 entry copy is available, and the first CALL kills it -- that alone yields the
 * ROM's $a0/$s1 phase boundary from a single p. The old `volatile u8 count` was the
 * saboteur: a volatile access nukes availability mid-block, flipping the last five
 * stores to $s1. But plain u8 registerizes count (andi + one lbu, no 3x reload).
 * Resolution: pass count as a 4-byte union-of-structs (byte field at offset 3 = the
 * homed param byte at 0x63($sp), ABI-identical to a promoted u8): a struct param is
 * memory-resident (fresh lbu per read site, never registerized), the p->unk8C store
 * reads the NON-volatile view (no availability kill, keeps $a0 propagation), and the
 * two `n =` reads use the volatile view (forces the post-call reloads + keeps n's
 * callee-saved $s3 web). Idiom is not evidence; matchdiff is the gate.
 * Types from ultratypes.h; ALVoiceConfig + alSyn* protos from PR/libaudio.h. */
struct EngSyn;
typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ struct EngSyn *unk8;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ void *unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ s32 unk28;
} EngVoice; /* 0x2C */

typedef struct {
    /* 0x00 */ u8 *ptr;
    /* 0x04 */ u8 data[4];
    /* 0x08 */ u8 *unk8;
    /* 0x0C */ u8 *unkC;
    /* 0x10 */ u8 *unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 pad15[3];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C[8];
} EngChan; /* 0x24 */

/* The two headers parsed out of the sequence data by func_8007E63C and func_8007E6A0.  Defined
 * here rather than beside those functions so that func_8007C1BC, which is spliced in above them,
 * can use the real types instead of local duplicates.
 * StructE6A0.unkC/unkE are u16: func_8007E6A0 writes them with a sign-agnostic `sh` from an
 * s16-returning helper, while func_8007C1BC reads unkE with `lhu` at 0x8E -- the same
 * one-member-two-signs situation as EngVoice.unk26, resolved on the reader's side. */
typedef struct { u32 unk0; u8 unk4; u8 unk5; u32 unk8; u32 unkC; } StructE63C;
typedef struct { u32 unk0; u32 unk4; u32 unk8; u16 unkC; u16 unkE; } StructE6A0; /* 0x10 */

/* A loaded sequence slot, allocated by func_8007C1BC out of the running allocation pointer and
 * stored into EngPlayer.unk350[].  The trailing byte array at +0x10 is indexed by voice number,
 * one byte per voice; the later `Snd`/`Eng` view of the same object reads unk0/unk4/unk10[]. */
typedef struct { s16 *buf; u32 size; u32 unk8; u32 type; s8 unk10; s8 padA[3]; } SeqSlot; /* 0x14 */

/* The wavetable bank at EngPlayer+0x18 (D_8010C988).  Derived from how the ROM reads it in
 * func_8007C1BC and func_8007D620: a 0x14-strided record array at +0, a parallel pointer array
 * at +0x640, a parallel s32 array at +0x780, and a 0xC-strided loop-record array at +0xB40, all
 * indexed by the same voice number p->unk80. */
typedef struct { s16 *buf; s32 unk4; u8 unk8; u8 unk9; u8 padA[2]; s32 unkC; s32 unk10; } VoiceRec; /* 0x14 */
typedef struct { u32 unk0; u32 unk4; s32 unk8; } LoopRec;                                          /* 0x0C */
typedef struct {
    /* 0x000 */ VoiceRec recs[80];
    /* 0x640 */ void    *bufs[80];
    /* 0x780 */ s32      sizes[80];
    /* 0x8C0 */ u8       gap8C0[0xB40 - 0x8C0];
    /* 0xB40 */ LoopRec  loops[80];
} VoiceBank;

typedef struct EngPlayer {
    /* 0x000 */ struct EngPlayer *next;
    /* 0x004 */ void *clientData;
    /* 0x008 */ void *handler;
    /* 0x00C */ s32 callTime;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ void *synth;
    /* 0x018 */ VoiceBank *unk18;
    /* 0x01C */ EngVoice *voices;
    /* 0x020 */ s32 unk20[16];
    /* 0x060 */ s32 unk60[8];
    /* 0x080 */ s32 unk80;
    /* 0x084 */ s32 unk84;
    /* 0x088 */ s32 unk88;
    /* 0x08C */ s32 unk8C;
    /* 0x090 */ s32 unk90[16];
    /* 0x0D0 */ s32 unkD0[16];
    /* 0x110 */ EngChan chan[16];
    /* 0x350 */ SeqSlot **unk350;
    /* 0x354 */ u8 unk354[16];
    /* 0x364 */ u8 unk364[256];
} EngPlayer;

typedef union {
    struct { u8 pad[3]; u8 b; } s;
    struct { u8 pad[3]; volatile u8 b; } v;
} CountByte;

extern u8 D_8010C988[];
extern EngVoice D_8010D888[];
extern s32 func_8007D620();

void func_8007BDCC(EngPlayer *p, s32 arg1, CountByte count) {
    s32 i;
    u8 n;
    ALVoiceConfig cfg;

    if (arg1 == 0) {
        p->unk18 = (VoiceBank *)D_8010C988;
        p->voices = D_8010D888;
        p->synth = alGlobals;
        p->unk8C = count.s.b;
        p->next = 0;
        p->handler = (void *)func_8007D620;
        p->clientData = p;
        p->callTime = 0;
        alSynAddPlayer(alGlobals, p);
        n = count.v.b;
        cfg.priority = 5;
        cfg.fxBus = 0;
        cfg.unityPitch = 0;
        for (i = 0; i < n; i++) {
            alSynAllocVoice(p->synth, &p->voices[i], &cfg);
        }
        for (i = 0; i < n; i++) {
            p->voices[i].unk1C = p->unk18;
            p->voices[i].unk20 = 1.0f;
            p->voices[i].unk24 = 0;
            p->voices[i].unk26 = 0x40;
            p->voices[i].unk27 = 0;
        }
    }
    n = count.v.b;
    for (i = 0; i < n; i++) {
        EngVoice *v = &p->voices[i];
        p->unk20[i] = 0;
        p->chan[i].ptr = p->chan[i].data;
        p->chan[i].ptr[0] = 0;
        if (v->unk27 == 1) {
            v->unk27 = 0;
            alSynStopVoice(p->synth, v);
        }
        p->unk20[i] = 0;
        p->unk90[i] = 0;
        p->unkD0[i] = 0;
    }
    for (i = 0; i < 255; i++) {
        p->unk364[i] = 0xFF;
    }
    for (i = 0; i < n >> 1; i++) {
        p->unk60[i] = 0;
    }
    p->unk80 = 0;
    p->unk84 = 0;
}

/* func_8007C1BC candidate v2 — reload-idiom faithful, VoiceBank struct, out reused as alloc. */



typedef struct { s16 a, b, c, d; } Rec8;
typedef struct { s8  a, b, c, e; } Rec4;

extern u32 lwDecode();
extern s16 func_8007E710(u8 *p);
extern u16 D_800E2868;
extern u8  D_800EE2BC[];

u8 *func_8007C1BC(EngPlayer *p, u8 *src, u8 *out, s32 arg3) {
    StructE63C hdr;
    StructE6A0 vh;
    s32 slotIdx = (u16)p->unk84;
    s32 i, k, cnt;
    u8 *dst;
    s32 idx;
    s16 *d, *d2, *s, *sp;

    func_8007E63C(src, &hdr);
    arg3 = ~0xF + (hdr.unk0 * 0);
    src += 0xE;
    p->unk350[slotIdx] = (SeqSlot *)out;
    out = (u8 *)(((s32)out + 0x27) & arg3);
    p->unk350[slotIdx]->type = hdr.unk4;
    p->unk350[slotIdx]->buf = (s16 *)out;
    p->unk350[slotIdx]->size = hdr.unk8;
    i = hdr.unk8;
    out += i;
    out = (u8 *)(((s32)out + 0xF) & arg3);
    s = (s16 *)(hdr.unk5 * 0x10 + (u32)src);
    d = p->unk350[slotIdx]->buf;
    while (i--) {
        *(u8 *)d = *(s8 *)s; d = (s16 *)((u8 *)d + 1); s = (s16 *)((u8 *)s + 1);
    }
    do {} while (0);
    dst = (u8 *)(((s32)((u8 *)(hdr.unk5 * 0x10 + (u32)src) + hdr.unk8) + 0xF) & arg3);

    if ((s32)hdr.unk4 >= 3) {
        func_80029760(D_800EE2BC, slotIdx * 4, arg3);
    }

    for (i = 0; i < (s32)hdr.unk5; i++) {
        func_8007E6A0(src, &vh);
        osWritebackDCacheAll();
        cnt = 1;
        k = 0;
        do {
            if (vh.unkE - D_800E2868 == p->unk364[k]) {
                cnt = 0;
                ((u8 *)p->unk350[slotIdx])[0x10 + i] = k;
                break;
            }
            k = (k + 1) & 0xFFFF;
        } while (k < 0xFF);

        if (cnt) {
            p->unk364[p->unk80] = (s8)(vh.unkE - D_800E2868);
            ((u8 *)p->unk350[slotIdx])[0x10 + i] = (s8)p->unk80;
            func_8007AC44((void *)dst, vh.unkE);

            if (vh.unkC & 1) {
                if (vh.unkC & 4) {
                    lwDecode((void *)dst, out);
                    p->unk18->recs[p->unk80].buf = (s16 *)out;
                    p->unk18->bufs[p->unk80] = out;
                    p->unk18->recs[p->unk80].unk4 = (s32)(vh.unk0 * 2);
                    p->unk18->sizes[p->unk80] = (s32)(vh.unk0 * 2);
                    p->unk18->recs[p->unk80].unk8 = 1;
                    p->unk18->recs[p->unk80].unk9 = 1;

                    s = p->unk18->recs[p->unk80].buf;
                    d2 = p->unk18->recs[p->unk80].buf;
                    cnt = vh.unk0;
                    while (cnt--) {
                        *d2 = (u16)(((s8 *)s)[1] << 8) + (((s8 *)s)[0] & 0xFF);
                        d2 += 1; s += 1;
                    }
                    out = (u8 *)(((s32)out + vh.unk0 * 2 + 0x1F) & ~0xF);

                    if (vh.unkC & 4) {
                        d2 = p->unk18->recs[p->unk80].buf;
                        sp = p->unk18->recs[p->unk80].buf;
                        if (vh.unkC & 8) {
                            for (idx = 0; idx < 0x10; idx++) {
                                ((s16 *)((u8 *)d2 + vh.unk8 * 2))[idx] = ((s16 *)sp)[vh.unk4 - idx - 1];
                            }
                        } else {
                            for (idx = 0; idx < 0x10; idx++) {
                                ((s16 *)((u8 *)d2 + vh.unk8 * 2))[idx] = ((s16 *)sp + idx)[vh.unk4];
                            }
                        }
                    } else {
                        d2 = p->unk18->recs[p->unk80].buf;
                        for (idx = 0; idx != 0x10; *(s16 *)((u8 *)d2 + (((idx + vh.unk0 + 1) << 1) << 1)) = 0, *(s16 *)((u8 *)d2 + (((idx + vh.unk0 + 2) << 1) << 1)) = 0, *(s16 *)((u8 *)d2 + (((idx + vh.unk0 + 3) << 1) << 1)) = 0, idx += 4) {
                            *(s16 *)((u8 *)d2 + (((idx + vh.unk0) << 1) << 1)) = 0;
                        }
                        idx = 0;
                    }
                } else {
                    if (vh.unkC & 4) {
                        lwDecode((void *)dst, out + vh.unk0);
                        p->unk18->recs[p->unk80].buf = (s16 *)out;
                        p->unk18->bufs[p->unk80] = out;
                        p->unk18->recs[p->unk80].unk4 = vh.unk0;
                        p->unk18->sizes[p->unk80] = vh.unk0;
                        p->unk18->recs[p->unk80].unk8 = 1;
                        p->unk18->recs[p->unk80].unk9 = 1;
                        d2 = p->unk18->recs[p->unk80].buf;
                        s = (s16 *)((u8 *)p->unk18->recs[p->unk80].buf + vh.unk0);
                        cnt = vh.unk0;
                        while (cnt--) {
                            *d2 = (((s8 *)s)[0] << 8) + (*(u8 *)out * 0); d2 += 1; s = (s16 *)((u8 *)s + 1);
                        }
                        out = (u8 *)(((s32)out + vh.unk0 + 0x1F) & ~0xF);
                    } else {
                        lwDecode((void *)dst, out);
                        p->unk18->recs[p->unk80].buf = (s16 *)out;
                        p->unk18->bufs[p->unk80] = out;
                        p->unk18->recs[p->unk80].unk4 = vh.unk0;
                        p->unk18->sizes[p->unk80] = vh.unk0;
                        p->unk18->recs[p->unk80].unk8 = 2;
                        p->unk18->recs[p->unk80].unk9 = 1;
                        d = p->unk18->recs[p->unk80].buf;
                        s = d;
                        cnt = vh.unk0;
                        while (cnt--) {
                            *(s8 *)d = (s16)(func_8007E710((u8 *)s) >> 8); d = (s16 *)((u8 *)d + 1); s += 1;
                        }
                        out = (u8 *)(((s32)out + vh.unk0 * 2 + 0x1F) & ~0xF);
                    }
                }
            } else {
                lwDecode((void *)dst, out);
                do {} while (0);
                p->unk18->recs[p->unk80].buf = (s16 *)out;
                p->unk18->bufs[p->unk80] = out;
                p->unk18->recs[p->unk80].unk4 = vh.unk0;
                p->unk18->recs[p->unk80].unk8 = 2;
                p->unk18->recs[p->unk80].unk9 = 1;
                p->unk18->sizes[p->unk80] = vh.unk0;
                do {} while (0);
                out = (u8 *)(((s32)out + vh.unk0 + 0x1F) & ~0xF);

                if (vh.unkC & 4) {
                    d = p->unk18->recs[p->unk80].buf;
                    if (vh.unkC & 8) {
                        for (idx = 0; idx < 0x10; idx++) {
                            ((s8 *)d + vh.unk8)[idx] = ((s8 *)(vh.unk4 - idx + (u32)d))[-1];
                        }
                    } else {
                        for (idx = 0; idx < 0x10; idx++) {
                            ((s8 *)d + vh.unk8)[idx] = ((s8 *)(idx + vh.unk4 + (u32)d))[0];
                        }
                    }
                } else {
                    d2 = p->unk18->recs[p->unk80].buf;
                    for (idx = 0; idx < 0x10; idx++) {
                        ((s8 *)d2 + idx)[vh.unk0] = 0;
                    }
                }
            }

            if (vh.unkC & 4) {
                p->unk18->recs[p->unk80].unkC = (s32)&p->unk18->loops[p->unk80];
                p->unk18->loops[p->unk80].unk0 = vh.unk4;
                p->unk18->loops[p->unk80].unk4 = vh.unk8;
                p->unk18->loops[p->unk80].unk8 = -1;
            } else {
                p->unk18->recs[p->unk80].unkC = 0;
            }
            p->unk80 = p->unk80 + 1 + (*(u8 *)s * 0);
        }
        src += 0x10;
    }
    p->unk84 = p->unk84 + 1;
    return out;
}

extern void func_8007D5E0(void);
extern u8 D_80104C08[];
void func_8007CD44(u8 *mgr) {
    s32 i;
    func_8007AF98(mgr);
    func_8007D5E0();
    for (i = 0; (u32)i < *(u32 *)(mgr + 0x8C); i++) {
        u8 *voice = *(u8 **)(mgr + 0x1C) + i * 0x2C;
        if (voice[0x27] == 1) {
            alSynStopVoice(*(void **)(mgr + 0x14), voice);
            voice[0x27] = 0;
        }
        *(s32 *)(mgr + 0x20 + i * 4) = 0;
        **(u8 **)(mgr + 0x110 + i * 0x24) = 0;
        *(u8 *)(mgr + 0x354 + i) = 1;
    }
    for (i = 0; (u32)i < (*(u32 *)(mgr + 0x8C) >> 1); i++) {
        *(s32 *)(mgr + 0x60 + i * 4) = 0;
        D_80104C08[i] = 0xFF;
    }
    func_8007AEE0(mgr);
}

typedef struct {
    u8 pad0[0x20];
    u32 unk20[16];
    u32 unk60[8];
    u8 pad80[0xC];
    u32 unk8C;
} EngP2;

typedef struct { u32 w[16]; } Words16;
extern Words16 D_800E286C;

u8 func_8007CE78(p, lim)
EngP2 *p;
u8 lim;
{
    u8 cnt;
    u8 i;
    u32 best;
    Words16 arr;
    u8 besti;

    arr = D_800E286C;
    cnt = 0;
    i = 0;
    if ((p->unk8C >> 1) != 0) {
        do {
            if (p->unk20[i] == 0) {
                return i;
            }
            if (lim >= p->unk20[i]) {
                arr.w[i] = p->unk60[i];
                cnt++;
            } else {
                arr.w[i] = 0;
            }
            i++;
        } while (i < (p->unk8C >> 1));
    }
    besti = 0;
    if (cnt == 0) {
        return 0xFF;
    }
    best = -1;
    i = 0;
    do {
        if ((arr.w[i] != 0) && (arr.w[i] < best)) {
            besti = i;
            best = arr.w[i];
        }
        i++;
    } while (i < 8);
    return besti;
}

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8[2];
    /* 0x10 */ u8  unk10[8];
} Snd;

typedef struct {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ u8  unk4[4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8  unk14;
    /* 0x15 */ u8  unk15[3];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8  unk1C[8];
} Voice;

typedef struct {
    /* 0x000 */ u8    unk000[0x20];
    /* 0x020 */ s32   unk020[16];
    /* 0x060 */ s32   unk060[16];
    /* 0x0A0 */ u8    unk0A0[0x70];
    /* 0x110 */ Voice unk110[8];
    /* 0x230 */ u8    unk230[0x120];
    /* 0x350 */ Snd **unk350;
    /* 0x354 */ u8    unk354[16];
} Eng;

typedef struct { u8 b[0xB]; } Trk;
typedef struct { Trk *rows; } TrkHdr;

extern u8 D_8010A210;
extern s16 D_800E44A8;
extern TrkHdr D_800E2828;
extern s8 D_80113323;
extern u8 D_801309F8;
extern s32 D_800E28C0;
extern char D_800EE30C[];

void *func_8007CFA0(e, hdr, chan, note)
Eng *e;
TrkHdr *hdr;
u8 chan;
u8 note;
{
    u8 buf[16];
    s32 i;
    s32 j;
    s32 k;
    u8 v;
    u8 first;
    u8 t;
    u8 ka;
    s16 m;
    s32 n;

    if (D_8010A210 == 1) {
        return &D_801309F8;
    }
    if (((D_800E44A8 == 0xA) && (hdr == &D_800E2828)) ||
        ((D_800E44A8 == 3) && (D_80113323 != 0))) {
        return &D_801309F8;
    }
    k = 0xFF;
    goto Ldum;
Ldum:;
    for (i = 0; i < 8; i++) {
        if (chan == D_80104C08[i]) {
            e->unk110[i].unk14 = 1;
            goto Ld3;
Ld3:;
            if (k == 0xFF) {
                goto Ld5;
Ld5:;
                k = i;
            }
        }
    }
    goto Ld2;
Ld2:;
    if (k != 0xFF) {
        return &e->unk110[k];
    }
    n = hdr->rows[chan].b[1] + ((hdr->rows[chan].b[1] & 0x111) * 0);
    m = hdr->rows[chan].b[2];
    k = m + (m * 0);
    goto Ld4;
Ld4:;
    for (i = 0; i < n; i++) {
        buf[i] = hdr->rows[chan].b[i + 3];
    }
    first = 0xFF;
    for (i = 0; i < n; i++) {
        k = m + (m * 0);
        v = func_8007CE78(e, (u8)(k + -i));
        if (v == 0xFF) {
            v = func_8007CE78(e, 0xF0);
            if (v == 0xFF) {
                func_80029760(D_800EE30C);
                return &D_801309F8;
            }
        }
        ka = v;
        e->unk110[ka].unk0 = e->unk110[first].unk4;
        e->unk354[ka * 2] = 2;
        e->unk354[ka * 2 + 1] = 2;
        if (first == 0xFF) {
            first = (u8)ka;
        }
        e->unk020[ka] = 0;
        e->unk060[ka] = 0;
        for (t = 0; t < 2; t++) {
        }
        j = note;
        if ((u32)note != 0) {
            e->unk110[ka].unk0[1] = (u8)j;
            e->unk110[ka].unk0[2] = 1;
        } else {
            e->unk110[ka].unk0[1] = 0;
            e->unk110[ka].unk0[2] = 0;
        }
        D_80104C08[ka] = chan;
        e->unk110[ka].unk14 = 0;
        e->unk110[ka].unk8 = e->unk350[buf[i]]->unk0;
        e->unk110[ka].unkC = e->unk110[ka].unk8 + e->unk350[buf[i]]->unk4;
        e->unk110[ka].unk18 = e->unk350[buf[i]]->unk4;
        for (j = 0; j < 8; j++) {
            e->unk110[ka].unk1C[j] = e->unk350[buf[i]]->unk10[j];
        }
        e->unk020[ka] = k + -i;
        e->unk060[ka] = D_800E28C0 - i;
    }
    return &e->unk110[first] + ((first & 0x111) * 0) + (((u16)first & 0x222) * 0) + (((u32)first & 0x444) * 0) + ((first & 0x555) * 0);
}


extern s32 D_8010B7C4;
extern u8  D_801309F8;
extern void *func_8007CFA0_p(s32 a0, s32 a1, u8 a2, s32 a3);
void *func_8007D45C(s32 a0, s32 a1, u8 a2) {
    if (D_8010B7C4) {
        return func_8007CFA0_p(a0, a1, a2, 0);
    }
    return &D_801309F8;
}

extern Entry D_80104C10[];
void func_8007D4A4(void) {
    s16 i;
    for (i = 0; i < 16; i++) {
        if (D_80104C10[i].unkA != 0x7D00) {
            D_80104C10[i].unkA--;
            if (D_80104C10[i].unkA <= 0) {
                func_8007D45C(D_80104C10[i].unk0, D_80104C10[i].unk4, D_80104C10[i].unk8);
                D_80104C10[i].unkA = 0x7D00;
            }
        }
    }
}

void func_8007D554(s32 a0, s32 a1, u8 a2, s16 a3) {
    s16 i;
    Entry *p;
    for (i = 0; i < 16; i++) {
        if (D_80104C10[i].unkA == 0x7D00) break;
    }
    p = &D_80104C10[i];
    p->unk0 = a0;
    p->unk4 = a1;
    p->unk8 = a2;
    p->unkA = a3;
}

void func_8007D5E0(void){ s16 i; for(i=0;i<16;i++){ D_80104C10[i].unkA=0x7D00; } }

/* func_8007D620 -- audio_engine multi-channel sequencer tick (851 instructions). */

typedef struct EngDrv { u8 pad0[8]; void (*unk8)(); } EngDrv;
typedef struct EngSyn { u8 pad0[0xC]; EngDrv *unkC; u8 pad10[0xC8]; s32 unkD8; } EngSyn;
typedef struct { u8 pad0[0x1C]; s32 unk1C; } EngSynth;

typedef struct { s32 unk0; s32 unk4; } EngPos;
typedef struct { u8 pad0[0x14]; } EngWav;
typedef struct { EngWav wav[80]; s32 unk640[80]; s32 unk780[80]; } EngBank;
typedef struct { s16 op; s16 pad2; EngPlayer *p; } EngMsg;
typedef struct { u8 pad0[0x24]; } EngRow; typedef struct { u8 zero[0]; } EngEmpty;

extern OSMesgQueue D_80104B80, D_80104B48;
extern char D_800EE320[], D_800EE338[], D_800EE350[], D_800EE370[];
extern s32 D_800E2850[];
extern s32 D_800E2860;
extern u8 D_800E28B0[];
typedef struct { u8 v; u8 pad[3]; } EngCtr;
extern EngCtr D_800E28B8_b, D_800E28B8_c, D_800E28B8_d;
extern u8 D_800E28B8_a, D_800E28B8_e, D_800E28B8_f, D_800E28B8_f, D_800E28B8_f, D_800E28B8_i, D_800E28B8_l, D_800E28B8_m, D_800E28B8_n, D_800E28B8_o, D_800E28B8_p;
extern EngParam *__allocParam();
extern f32 func_8007E4D4(s16);
extern s16 func_8007E710(u8 *);
extern void func_8007D4A4(void);

s32 func_8007D620(EngPlayer *m)
{
    EngPlayer *cp;
    EngVoice *v;
    u8 c;
    u8 i;
    u8 b;
    u8 k;
    EngDrv *drv;
    EngParam *pp;
    u8 *p;
    u32 w;
    s32 t;
    EngPlayer *mm;
    EngPlayer *g;
    EngMsg *msg;
    u32 n;
    u8 *xq;

    mm = m;
    if (osRecvMesg(&D_80104B80, (OSMesg *)&msg, 0) == 0) {
        g = msg->p;
        switch (msg->op) {
        case 0:
            func_80029760(D_800EE320);
            i = i * 0;
            if (g->unk8C != 0) {
                do {
                    v = &g->voices[i];
                    if (v->unk27 != 0) {
                        v->unk27 = 0;
                        alSynStopVoice(g->synth, v);
                    }
                    i++;
                } while (i < (u32)g->unk8C);
            }
            g->unk88 = 3;
            osSendMesg(&D_80104B48, 0, 0);
            msg->op = 0;
            return D_800E2860;
        case 1:
            func_80029760(D_800EE338);
            g->unk88 = 1;
            msg->op = 0;
            osSendMesg(&D_80104B48, 0, 0);
            break;
        default:
            msg->op = 0;
            break;
        }
    }
    if (m->unk88 == 3) {
        return D_800E2860;
    }
    if (m->unk88 == 1) {
        func_8007D4A4();
        i = 0;
        if (m->unk8C != 0) {
            do {
                v = &m->voices[i];
                cp = (EngPlayer *)((EngRow *)m + (i >> 1));
                if (cp->chan[0].unk14 != 0) {
                    D_800E28B0[i >> 1] = 0;
                    cp->chan[0].unk14 = 0;
                    cp->chan[0].unk8 = cp->chan[0].unkC - cp->chan[0].unk18;
                    v = &m->voices[i >> 1];
                    if (v->unk27 != 0) {
                        drv = v->unk8->unkC;
                        v->unk8->unkD8 = 0x240;
                        pp = __allocParam();
                        if (pp != 0) {
                            pp->unk4 = ((EngSynth *)m->synth)->unk1C;
                            pp->unkC = 0;
                            pp->unk8 = 0xB;
                            pp->unk10 = v->unk8->unkD8 - 0x40;
                            drv->unk8(drv, 3, pp);
                        }
                        pp = __allocParam();
                        if (pp != 0) {
                            pp->unk4 = ((EngSynth *)m->synth)->unk1C + v->unk8->unkD8;
                            pp->unk8 = 0xF;
                            pp->unk0 = 0;
                            drv->unk8(drv, 3, pp);
                        }
                        alSynStopVoice(m->synth, v);
                        v->unk27 = 0;
                    }
                }
                if (m->unk354[i] != 0) {
                    D_800E28B0[i >> 1] = 0;
                    if (m->unk354[i] != 2) {
                        D_80104C08[i >> 1] = 0xFF;
                    }
                    m->unk354[i] = 0;
                    if (v->unk27 == 1) {
                        drv = v->unk8->unkC;
                        v->unk8->unkD8 = 0x240;
                        pp = __allocParam();
                        if (pp != 0) {
                            pp->unk4 = ((EngSynth *)m->synth)->unk1C;
                            pp->unkC = 0;
                            pp->unk8 = 0xB;
                            pp->unk10 = v->unk8->unkD8 - 0x40;
                            drv->unk8(drv, 3, pp);
                        }
                        pp = __allocParam();
                        if (pp != 0) {
                            pp->unk4 = ((EngSynth *)m->synth)->unk1C + v->unk8->unkD8;
                            pp->unk8 = 0xF;
                            pp->unk0 = 0;
                            drv->unk8(drv, 3, pp);
                        }
                        alSynStopVoice(m->synth, v);
                    } else {
                        alSynStartVoiceParams(m->synth, v, v->unk1C, 0.0f, 0, 0, 0, 0x64);
                        drv = v->unk8->unkC;
                        v->unk8->unkD8 = 0x240;
                        pp = __allocParam();
                        if (pp != 0) {
                            pp->unk4 = ((EngSynth *)m->synth)->unk1C;
                            pp->unkC = 0;
                            pp->unk8 = 0xB;
                            pp->unk10 = v->unk8->unkD8 - 0x40;
                            drv->unk8(drv, 3, pp);
                        }
                        pp = __allocParam();
                        if (pp != 0) {
                            pp->unk4 = ((EngSynth *)m->synth)->unk1C + v->unk8->unkD8;
                            pp->unk8 = 0xF;
                            pp->unk0 = 0;
                            drv->unk8(drv, 3, pp);
                        }
                        alSynStopVoice(m->synth, v);
                    }
                    v->unk27 = 0;
                }
                i++;
            } while (i < (u32)mm->unk8C);
        }
        n = m->unk8C;
        D_800E28B8_a = 0;
        if ((n >> 1) != 0) {
            do {
                cp = (EngPlayer *)((EngRow *)m + D_800E28B8_b.v);
                p = cp->chan[0].unk8;
                if (m->unk20[*(u8 *)&D_800E28B8_b] != 0 && p != 0) {
                    w = (u32)(cp->chan[0].ptr + ((s32)p * 0));
                    if (*(u8 *)w == 3 + (D_800E28B8_f * 0)) {
                        *(u8 *)w = 0;
                        func_80029760(D_800EE350);
                    }
                    xq = &D_800E28B8_c.v;
                    i = 0;
                    do {
                        t = D_800E28B8_c.v << 1;
                        v = (EngVoice *)((u8 *)m->voices + (s32)i * 44 + t * 44);
                        n = (u32)&D_800E28B0[*xq];
                        if ((*(u8 *)n) != 0) {
                            (*(u8 *)n) = (*(u8 *)n) - 1;
                        } else {
                            drv = (EngDrv *)&D_800E28B8_d.v;
                            cp = (EngPlayer *)((EngRow *)m + D_800E28B8_d.v);
                            p = cp->chan[0].unk8;
                            if (p >= cp->chan[0].unkC) {
                                D_80104C08[*(u8 *)drv] = 0xFF;
                                v->unk27 = 0;
                                (*(u8 *)n) = 0;
                                m->unk20[*xq] = 0;
                                m->unk354[t] = 1;
                                m->unk354[t + 1] = 1 + (D_800E2860 * 0);
                            } else {
                                c = *p;
                                cp->chan[0].unk8 = p + 1;
                                if (c & 0x80) {
                                    (*(u8 *)n) = (c & 0x7F) + (D_800EE350[0] * 0);
                                } else {
                                    if (c & 0x40) {
                                        w = (u16)func_8007E710(cp->chan[0].unk8);
                                        cp->chan[0].unk8 = cp->chan[0].unk8 + 2;
                                        pp = (EngParam *)(D_800E2850[(w >> 14) & 0xFF] + ((w & 0x3FFF) << ((w >> 14) & 0xFF)));
                                        v->unk20 = func_8007E4D4((s16)(s32)pp);
                                    }
                                    if (c & 0x20) {
                                        cp = (EngPlayer *)((EngRow *)m + D_800E28B8_f);
                                        p = cp->chan[0].unk8;
                                        b = *p;
                                        cp->chan[0].unk8 = p + 1;
                                        w = (u32)cp->chan[0].ptr;
                                        if (((u8 *)w)[2] != 0) {
                                            v->unk24 = D_80104910[((u8 *)w)[1]];
                                        } else {
                                            v->unk24 = D_80104910[b];
                                        }
                                    }
                                    if ((c & 0x10)) {
                                        cp = (EngPlayer *)((EngRow *)m + D_800E28B8_f);
                                        v->unk26 = *cp->chan[0].unk8 >> 1;
                                        cp->chan[0].unk8 = cp->chan[0].unk8 + 1;
                                    }
                                    if (c & 8) {
                                        cp = (EngPlayer *)((EngRow *)m + D_800E28B8_f);
                                        t = *cp->chan[0].unk8;
                                        cp->chan[0].unk8 = cp->chan[0].unk8 + 1;
                                        v->unk1C = &((EngBank *)m->unk18)->wav[cp->chan[0].unk1C[t]];
                                        m->unkD0[(s32)i + *xq * 2] = t + (D_800E28B8_c.v * 0) + (D_800E2860 * 0);
                                        if (v->unk27 == 1) {
                                            drv = v->unk8->unkC;
                                            v->unk8->unkD8 = 0x240 + (m->unk8C * 0) + (D_800E28B0[0] * 0);
                                            pp = __allocParam();
                                            if (pp != 0) {
                                                pp->unk4 = ((EngSynth *)m->synth)->unk1C + (m->unk8C * 0);
                                                pp->unkC = 0 + (D_800E28B8_b.v * 0);
                                                pp->unk8 = 0xB;
                                                pp->unk10 = v->unk8->unkD8 - 0x40 + (D_800E28B8_d.v * 0) + (D_800EE350[0] * 0) + (D_80104C08[0] * 0);
                                                drv->unk8(drv, 3, pp);
                                            }
                                            pp = __allocParam();
                                            if (pp != 0) {
                                                pp->unk4 = ((EngSynth *)m->synth)->unk1C + v->unk8->unkD8 + (D_800E2850[0] * 0) + (D_80104C08[0] * 0);
                                                pp->unk8 = 0xF;
                                                pp->unk0 = 0 + (D_800E28B8_p * 0);
                                                *(EngEmpty *)m = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u32)pp | 1) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u32)pp | 2) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 1) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 2) = *(EngEmpty *)drv;
                                                *(EngEmpty *)drv = *(EngEmpty *)((u8 *)pp + 0x7ff9);
                                                *(EngEmpty *)((u8 *)pp + 3) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 4) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 5) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 6) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 7) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 8) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 9) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u32)pp | 3) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u32)pp | 4) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 10) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 11) = *(EngEmpty *)drv;
                                                *(EngEmpty *)drv = *(EngEmpty *)((u8 *)pp + 0x7ffa);
                                                *(EngEmpty *)((u8 *)pp + 12) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 13) = *(EngEmpty *)drv;
                                                *(EngEmpty *)((u8 *)pp + 14) = *(EngEmpty *)drv;
                                                drv->unk8(drv, 3, pp);
                                            }
                                        }
                                    }
                                    if ((c & 4) != 0) {
                                        cp = (EngPlayer *)((EngRow *)m + (u8)(D_800E28B8_c.v * 1));
                                        w = (u32)((u8 *)m + (s32)i * 4 + (u8)(((EngCtr *)xq)->v * 1) * 8);
                                        *(EngEmpty *)((u8 *)cp + 1) = *(EngEmpty *)cp;
                                        *(EngEmpty *)cp = *(EngEmpty *)((u8 *)cp + 0x7ff9);
                                        *(EngEmpty *)((u8 *)cp + 2) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 3) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 4) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u32)cp | 1) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u32)cp | 2) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 5) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 6) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 7) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 8) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 9) = *(EngEmpty *)cp;
                                        *(EngEmpty *)((u8 *)cp + 10) = *(EngEmpty *)cp;
                                        ((EngPos *)v->unk1C)->unk0 = ((EngBank *)m->unk18)->unk640[cp->chan[0].unk1C[((EngPlayer *)w)->unkD0[0]]] + (*cp->chan[0].unk8 << 8);
                                        cp->chan[0].unk8 = cp->chan[0].unk8 + 1;
                                        ((EngPos *)v->unk1C)->unk4 = ((EngBank *)m->unk18)->unk780[cp->chan[0].unk1C[((EngPlayer *)w)->unkD0[0]]] - (u32)(((EngPos *)v->unk1C)->unk0 - ((EngBank *)m->unk18)->unk640[cp->chan[0].unk1C[((EngPlayer *)w)->unkD0[0]]]);
                                        *(EngEmpty *)cp = *(EngEmpty *)(D_800EE350 + (u32)cp);
                                        *(EngEmpty *)m = *(EngEmpty *)(D_800EE350 + (u32)cp);
                                    } else if (c & 2) {
                                        *(EngEmpty *)((u8 *)v + 111) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 112) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 1) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 2) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 3) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 4) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 1) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 2) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 3) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 5) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 6) = *(EngEmpty *)v;
                                        *(EngEmpty *)v = *(EngEmpty *)((u8 *)v + 0x7ff9);
                                        *(EngEmpty *)((u8 *)v + 7) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 4) = *(EngEmpty *)v;
                                        *(EngEmpty *)v = *(EngEmpty *)((u8 *)v + 0x7ffa);
                                        *(EngEmpty *)((u32)v | 5) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 6) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 7) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 8) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 9) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 10) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 8) = *(EngEmpty *)v;
                                        *(EngEmpty *)v = *(EngEmpty *)((u8 *)v + 0x7ffb);
                                        *(EngEmpty *)((u32)v | 9) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 10) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 11) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 11) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 12) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 13) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 12) = *(EngEmpty *)v;
                                        *(EngEmpty *)v = *(EngEmpty *)((u8 *)v + 0x7ffc);
                                        *(EngEmpty *)((u32)v | 13) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 14) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u32)v | 15) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 14) = *(EngEmpty *)v;
                                        *(EngEmpty *)((u8 *)v + 15) = *(EngEmpty *)v;
                                        p = (u8 *)m; p += (u8)(*xq * 1) * (36U + ((c & 2) * 0));
                                        w = (u32)((u8 *)m + (s32)i * 4 + (u8)(D_800E28B8_c.v * 1) * 8);
                                        *(EngEmpty *)((u8 *)p + 1) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u32)p | 1) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u32)p | 2) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u8 *)p + 2) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u8 *)p + 3) = *(EngEmpty *)p;
                                        *(EngEmpty *)p = *(EngEmpty *)((u8 *)p + 0x7ff9);
                                        *(EngEmpty *)((u8 *)p + 4) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u8 *)p + 5) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u8 *)p + 6) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u32)p | 3) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u32)p | 4) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u8 *)p + 7) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u8 *)p + 8) = *(EngEmpty *)p;
                                        *(EngEmpty *)p = *(EngEmpty *)((u8 *)p + 0x7ffa);
                                        *(EngEmpty *)((u8 *)p + 9) = *(EngEmpty *)p;
                                        *(EngEmpty *)((u8 *)p + 10) = *(EngEmpty *)p;
                                        ((EngPos *)v->unk1C)->unk0 = ((EngBank *)m->unk18)->unk640[((EngPlayer *)p)->chan[0].unk1C[((EngPlayer *)w)->unkD0[0]]];
                                        ((EngPos *)v->unk1C)->unk4 = ((EngBank *)m->unk18)->unk780[((EngPlayer *)p)->chan[0].unk1C[((EngPlayer *)w)->unkD0[0]]];
                                    }
                                    do {
                                    } while (0);
                                    if (c & 2) {
                                        if (v->unk27 == 1) {
                                            drv = v->unk8->unkC;
                                            v->unk8->unkD8 = 0x240;
                                            pp = __allocParam();
                                            if (pp != 0) {
                                                pp->unk4 = ((EngSynth *)m->synth)->unk1C;
                                                pp->unkC = 0 + (D_800E28B8_b.v * 0);
                                                pp->unk8 = 0xB;
                                                pp->unk10 = v->unk8->unkD8 - 0x40;
                                                drv->unk8(drv, 3, pp);
                                            }
                                            pp = __allocParam();
                                            if (pp != 0) {
                                                pp->unk4 = ((EngSynth *)m->synth)->unk1C + v->unk8->unkD8;
                                                pp->unk8 = 0xF + (D_80104910[0] * 0);
                                                pp->unk0 = 0 + (D_800E28B8_p * 0);
                                                drv->unk8(drv, 3, pp);
                                            }
                                        }
                                        alSynStartVoiceParams(m->synth, v, v->unk1C, v->unk20, v->unk24, v->unk26, 0, 0x1F4);
                                        v->unk27 = 1;
                                    }
                                    do {
                                    } while (0);
                                    if (v->unk27 != 0 && (c & 0x40) && !(c & 2)) {
                                        alSynSetPitch(m->synth, v, v->unk20);
                                    }
                                    if (v->unk27 != 0 && (c & 0x20) && !(c & 2)) {
                                        alSynSetVol(m->synth, v, v->unk24, 0x1F4);
                                    }
                                    if (v->unk27 != 0 && (c & 0x10) && !(c & 2)) {
                                        alSynSetPan(m->synth, v, v->unk26);
                                    }
                                    if (v->unk27 != 0) {
                                        w = (u32)m->chan[*xq].ptr + (D_800E28B8_f * 0) + (D_800EE370[0] * 0) + (D_800EE350[0] * 0);
                                        if (((u8 *)w)[2] != 0) {
                                            v->unk24 = D_80104910[((u8 *)w)[1]];
                                            alSynSetVol(m->synth, v, v->unk24, 0x1F4);
                                        }
                                    }
                                    if (c & 1) {
                                        cp = (EngPlayer *)((EngRow *)m + D_800E28B8_c.v);
                                        p = cp->chan[0].unk8;
                                        c = *p;
                                        cp->chan[0].unk8 = p + 1;
                                        if (c & 0x40) {
                                            ;
                                            if (*cp->chan[0].unk8 != 0) {
                                                D_800E2860 = 0x7735940 / (*cp->chan[0].unk8 * (0x32 + (D_800E2860 * 0)));
                                                cp->chan[0].unk8 = cp->chan[0].unk8 + 1;
                                            } else {
                                                func_80029760(D_800EE370);
                                                cp = (EngPlayer *)((EngRow *)m + D_800E28B8_f);
                                                cp->chan[0].unk8 = cp->chan[0].unk8 + 1;
                                            }
                                        }
                                        if (c & 0x20) {
                                            c = *cp->chan[0].unk8;
                                            cp->chan[0].unk8 = cp->chan[0].unk8 + 1;
                                            if (cp->chan[0].ptr[0] == 1) {
                                                if (c == 1) {
                                                    cp->chan[0].unk10 = cp->chan[0].unk8;
                                                }
                                                if (c == 2) {
                                                    cp->chan[0].unk8 = cp->chan[0].unk10;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        i++;
                    } while (i < 2);
                }
                D_800E28B8_p = D_800E28B8_d.v + 1;
            } while (D_800E28B8_p < ((u32)mm->unk8C >> 1));
        }
    }
    g = (EngPlayer *)&mm;
    return D_800E2860;
}

extern f64 D_800EE440;
extern f64 D_800EE448;
extern s32 D_800E28E0;
extern char D_800EE398[];
extern char D_800EE3B0[];
f32 func_8007E36C(u16 arg) {
    f32 r;
    if ((s32)arg <= 0) {
        return 0.0f;
    }
    r = (f32)(D_800EE440 / (f32)(0xDA7A68 / (s32)arg) * D_800EE448 / (f64)(u32)D_800E28E0);
    if (2.0 <= (f64)r) {
        func_80029760(D_800EE398, (f64)r);
        r = 1.0f;
    }
    if ((f64)r < 0.0) {
        r = (f32)((f64)r * -1.0);
        func_80029760(D_800EE3B0);
    }
    return r;
}

extern f64 D_800EE450;
extern f64 D_800EE458;
extern char D_800EE3C4[];
extern char D_800EE3DC[];
f32 func_8007E4D4(s16 arg) {
    f32 r;
    if (arg <= 0) {
        return 0.0f;
    }
    r = (f32)(D_800EE450 / (f32)(0xDA7A68 / (s32)arg) * D_800EE458 / (f64)(u32)D_800E28E0);
    if (2.0 <= (f64)r) {
        func_80029760(D_800EE3C4, (f64)r);
        r = 1.0f;
    }
    if ((f64)r < 0.0) {
        r = (f32)((f64)r * -1.0);
        func_80029760(D_800EE3DC);
    }
    return r;
}

extern u32 func_8007E758(u8 *p);
extern u32 func_8007E72C(u8 *p);
void func_8007E63C(u8 *p, StructE63C *out) {
    out->unk0 = func_8007E758(p);
    out->unk4 = p[4];
    out->unk5 = p[5];
    p = p + 6;
    out->unk8 = func_8007E72C(p);
    p = p + 4;
    out->unkC = func_8007E72C(p);
}

extern s16 func_8007E710(u8 *p);
void func_8007E6A0(u8 *p, StructE6A0 *out) {
    out->unk0 = func_8007E72C(p); p += 4;
    out->unk4 = func_8007E72C(p); p += 4;
    out->unk8 = func_8007E72C(p); p += 4;
    out->unkC = func_8007E710(p);
    out->unkE = func_8007E710(p + 2);
}

/* reads a little-endian s16 from a byte pointer */
s16 func_8007E710(u8 *p) {
    return p[0] + (p[1] << 8);
}

/* reads a little-endian s32 from a byte pointer */
u32 func_8007E72C(u8 *p) {
    return p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
}

/* reads a big-endian s32 from a byte pointer */
u32 func_8007E758(u8 *p) {
    return p[3] + (p[2] << 8) + (p[1] << 16) + (p[0] << 24);
}

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u16 unkC;
    u16 unkE;
} StructE784; /* size 0x10 */
extern char D_800EE3F0[];
extern char D_800EE3FC[];
extern char D_800EE40C[];
extern char D_800EE41C[];
extern char D_800EE42C[];
void func_8007E784(StructE784 *s) {
    func_80029760(D_800EE3F0, s->unkC);
    func_80029760(D_800EE3FC, s->unk4);
    func_80029760(D_800EE40C, s->unk8);
    func_80029760(D_800EE41C, s->unk0, s->unk0);
    func_80029760(D_800EE42C, s->unkE);
}
