#include "common.h"

extern s32 strlen(const char *);

typedef struct {
    u32 unk0;
    u32 unk4;
    s32 unk8;
} DebugEntry;

extern s32 D_800DFD30;
extern s32 *D_800DFD34;
extern u16 *D_801025D0;
extern u32 D_80102650;
extern char D_801025F0[];
extern char D_800EB504[];
extern char D_800EB50C[];
extern char D_800EBA50[];
extern char D_800EBA54[];
extern char D_800EBA58[];
extern char D_800EBA64[];
extern char D_800EBA68[];
extern char D_800EBA6C[];
extern char D_800EBA70[];

extern void func_8002B084(u8, s32, s32, s32, u8, u8, u8);

void func_8002AF20(u8 *arg0, u8 *arg1) {
    s32 i;

    if (strlen((const char *)arg0) >= 0x29) {
        arg0[0x28] = 0;
    }
    if (strlen((const char *)arg1) >= 0x29) {
        arg1[0x28] = 0;
    }
    for (i = 0; i < strlen((const char *)arg0); i++) {
        if (arg0[i] >= 0x41 && arg0[i] < 0x60) {
            arg0[i] += 0x20;
        }
    }
    sprintf(D_801025F0, D_800EB504, arg0, arg1);
    D_800DFD30 = 1;
    rmonPrintf(D_800EB50C, arg0, arg1, D_801025F0);
    osWritebackDCacheAll();
    *D_800DFD34 = 0;
}

extern u8 D_800DFB58[];

void func_8002B084(u8 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    if (arg0 >= 0x61) {
        arg0 -= 0x20;
    }
    arg0 -= 0x20;
    sp24 = arg0 * 8;
    sp18 = (arg2 * 0x140) + arg1;
    sp20 = 0;
    do {
        sp1C = 0;
        do {
            (u16)(D_800DFB58[sp24] & (1 << (8 - sp1C)))
                ? (((u16 *)arg3)[sp18 + sp1C] = ((arg4 << 8) & 0xF800) | ((arg5 << 3) & 0x7C0) | ((arg6 >> 2) & 0x3E))
                : (((u16 *)arg3)[sp18 + sp1C] = 0xFFFE);
        } while (++sp1C < 8);
        sp18 += 0x140;
        sp24 += 1;
    } while (++sp20 < 8);
    osWritebackDCacheAll();
}

s32 func_8002B210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6) {
    u8 c;
    u8 i;
    u8 col;
    u8 startx;

    startx = arg1;
    for (i = 0, col = 0; (s32)i < strlen((const char *)arg0); i++, col++) {
        c = *(u8 *)(arg0 + i);
        if (c == 0xA) {
            col = 0xFF;
            arg2 += 9;
            arg1 = startx;
        } else {
            arg1 = startx + col * 8;
            func_8002B084(c, arg1, arg2, arg3, arg4, arg5, arg6);
        }
    }
    return (arg1 << 16) | arg2;
}

extern u16 D_803B5000[];
extern u16 *D_801025D4;
extern OSMesgQueue D_801025D8;
extern OSMesg *D_80102648;
extern u32 D_80102D44;
extern s32 D_800DFD40;
extern DebugEntry D_800DF780[];
extern DebugEntry D_800DF8D0[];
extern DebugEntry D_800DFA44[];
extern OSViMode D_800E95B0[];
extern OSThread mainThread;
extern OSThread schedThread;
extern u8 D_800FDEF0[];
extern u32 D_800F22C0;
extern char *D_800F2030;
extern char *D_800F2034;
extern s32 osTvType;

extern char D_800EB534[];
extern char D_800EB568[];
extern char D_800EB580[];
extern char D_800EB590[];
extern char D_800EB598[];
extern char D_800EB59C[];
extern char D_800EB5B0[];
extern char D_800EB5D8[];
extern char D_800EB600[];
extern char D_800EB628[];
extern char D_800EB650[];
extern char D_800EB678[];
extern char D_800EB6A0[];
extern char D_800EB6C8[];
extern char D_800EB6F0[];
extern char D_800EB718[];
extern char D_800EB734[];
extern char D_800EB73C[];
extern char D_800EB74C[];
extern char D_800EB750[];
extern char D_800EB75C[];
extern char D_800EB774[];
extern char D_800EB784[];
extern char D_800EB788[];
extern char D_800EB794[];
extern char D_800EB7A0[];
extern char D_800EB7AC[];
extern char D_800EB7C4[];
extern char D_800EB7DC[];
extern char D_800EB7F4[];
extern char D_800EB80C[];
extern char D_800EB824[];
extern char D_800EB83C[];
extern char D_800EB854[];
extern char D_800EB86C[];
extern char D_800EB884[];
extern char D_800EB89C[];
extern char D_800EB8B4[];
extern char D_800EB8CC[];
extern char D_800EB8E4[];
extern char D_800EB8FC[];
extern char D_800EB918[];
extern char D_800EB930[];
extern char D_800EB948[];
extern char D_800EB960[];
extern char D_800EB978[];
extern char D_800EB990[];
extern char D_800EB9A8[];
extern char D_800EB9C0[];
extern char D_800EB9D8[];
extern char D_800EB9F0[];
extern char D_800EBA08[];
extern char D_800EBA20[];
extern char D_800EBA38[];

extern void func_8002A218(void);
extern s32 func_800334D8(void);
extern s32 func_8002B210(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6);
extern void func_8002CBB0(s32 arg0, DebugEntry *arg1);
extern void func_8002CCC4(s32 arg0, s32 arg1, DebugEntry *arg2);

void func_8002B348(OSThread *arg0) {
    s32 i;
    s32 unused0;
    s32 unused1;
    OSMesg msg;
    OSMesgQueue queue;
    char buf[0x800];
    u32 *stack;
    u32 pos;
    s32 state;
    s32 oldstate;
    u64 unused2;
    s32 sp64 = 0;
    u16 button;
    u16 oldButton;
    OSContPad pad[4];
    __OSThreadContext *ctx = &arg0->context;

    D_80102D44 = ctx->pc;
    D_800DFD40 = 1;
    func_8002A218();
    osCreateMesgQueue(&queue, &msg, 1);
    osSetEventMesg(5, &queue, (OSMesg)1);
    D_801025D0 = D_803B5000;
    D_801025D4 = D_803B5000 + 0x12C00;
    rmonPrintf(D_800EB534, func_800334D8());
    osCreateMesgQueue(&D_801025D8, D_80102648, 8);
    osSpTaskYield();
    osStopThread(&mainThread);
    osStopThread(&schedThread);
    osStopThread(&mainThread);
    osStopThread((OSThread *)(D_800FDEF0 + 0xB0));
    osCreateViManager(0xFE);
    osViBlack(1);
    if (osTvType == 0) {
        osViSetMode(&D_800E95B0[14]);
    }
    if (osTvType == 1) {
        osViSetMode(&D_800E95B0[0]);
    }
    if (osTvType == 2) {
        osViSetMode(&D_800E95B0[28]);
    }
    osViSetSpecialFeatures(0x42);
    osViBlack(0);
    osViSwapBuffer((void *)0x803B5000);
    osViSetEvent(&D_801025D8, (OSMesg)0x29A, 1);
    for (i = 0; i < 0x12C00; i++) {
        D_801025D0[i] = 0;
    }
    D_800F22C0 = 0x80200000;
    osWritebackDCacheAll();
    rmonPrintf(D_800EB568, arg0->id);
    rmonPrintf(D_800EB580, ctx->pc);
    func_8002CCC4(ctx->cause, (s32)D_800EB590, D_800DF780);
    func_8002CCC4(ctx->sr, (s32)D_800EB598, D_800DF8D0);
    rmonPrintf(D_800EB59C, ctx->badvaddr);
    rmonPrintf(D_800EB5B0, ctx->at, ctx->v0, ctx->v1);
    rmonPrintf(D_800EB5D8, ctx->a0, ctx->a1, ctx->a2);
    rmonPrintf(D_800EB600, ctx->a3, ctx->t0, ctx->t1);
    rmonPrintf(D_800EB628, ctx->t2, ctx->t3, ctx->t4);
    rmonPrintf(D_800EB650, ctx->t5, ctx->t6, ctx->t7);
    rmonPrintf(D_800EB678, ctx->s0, ctx->s1, ctx->s2);
    rmonPrintf(D_800EB6A0, ctx->s3, ctx->s4, ctx->s5);
    rmonPrintf(D_800EB6C8, ctx->s6, ctx->s7, ctx->t8);
    rmonPrintf(D_800EB6F0, ctx->t9, ctx->gp, ctx->sp);
    rmonPrintf(D_800EB718, ctx->s8, ctx->ra);
    func_8002CCC4(ctx->fpcsr, (s32)D_800EB734, D_800DFA44);
    sprintf(buf, D_800EB73C);
    D_80102650 = func_8002B210((s32)buf, 30, 20, (s32)D_801025D0, 0, 0, 0);
    sprintf(buf, D_800EB74C, arg0->id);
    func_8002B210((s32)buf, (D_80102650 >> 16) + 8, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0xC8);
    sprintf(buf, D_800EB750, ctx->pc);
    D_80102650 = func_8002B210((s32)buf, 30, 30, (s32)D_801025D0, 0, 0, 0);
    func_8002CBB0(ctx->cause, D_800DF780);
    if ((ctx->cause & D_800DF780->unk0) == 0x3C) {
        func_8002CBB0(ctx->fpcsr, D_800DFA44);
    }
    sprintf(buf, D_800EB75C, ctx->ra << 32, ctx->sp << 32);
    D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, (D_80102650 & 0xFF) + 0xA, (s32)D_801025D0, 0, 0, 0);
    stack = (u32 *)(ctx->sp & 0xFFFFFFFF);
    pos = D_80102650;
    state = 1;
    button = 0x400;
    for (;;) {
        if ((state == 1) && (sp64 == 0)) {
            for (i = 0; i < 0x12C00; i++) {
                D_801025D0[i] = 0xFFFE;
            }
            sprintf(buf, D_800EB774);
            D_80102650 = func_8002B210((s32)buf, 30, 20, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB784, arg0->id);
            func_8002B210((s32)buf, (D_80102650 >> 16) + 8, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0xC8);
            sprintf(buf, D_800EB788, ctx->pc);
            D_80102650 = func_8002B210((s32)buf, 30, 30, (s32)D_801025D0, 0, 0, 0);
            func_8002CBB0(ctx->cause, D_800DF780);
            sprintf(buf, D_800EB794, ctx->ra << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, (D_80102650 & 0xFF) + 2, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB7A0, ctx->sp << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB7AC);
            D_80102650 = func_8002B210((s32)buf, pos >> 16, pos & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB7C4, stack[0], stack[1], stack[2]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, (D_80102650 & 0xFF) + 4, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB7DC, stack[3], stack[4], stack[5]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB7F4, stack[6], stack[7], stack[8]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB80C, stack[9], stack[10], stack[11]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB824, stack[12], stack[13], stack[14]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB83C, stack[15], stack[16], stack[17]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB854, stack[18], stack[19], stack[20]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB86C, stack[21], stack[22], stack[23]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB884, stack[24], stack[25], stack[26]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB89C, stack[27], stack[28], stack[29]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB8B4, stack[30], stack[31], stack[32]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB8CC, stack[33], stack[34], stack[35]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB8E4, stack[36], stack[37], stack[38]);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            oldstate = state;
            state = 0;
            osSetTime(0);
        }
        if ((state == 2) && (sp64 == 0)) {
            for (i = (pos & 0xFF) * 0x140 + (pos >> 16); i < 0x12C00; i++) {
                D_801025D0[i] = 0xFFFE;
            }
            sprintf(buf, D_800EB8FC);
            D_80102650 = func_8002B210((s32)buf, pos >> 16, pos & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB918, ctx->at << 32, ctx->v0 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, (D_80102650 & 0xFF) + 4, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB930, ctx->v1 << 32, ctx->a0 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB948, ctx->a1 << 32, ctx->a2 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB960, ctx->a3 << 32, ctx->t0 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB978, ctx->t1 << 32, ctx->t2 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB990, ctx->t3 << 32, ctx->t4 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB9A8, ctx->t5 << 32, ctx->t6 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB9C0, ctx->t7 << 32, ctx->t8 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EB9D8, ctx->s0 << 32, ctx->s1 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EB9F0, ctx->s2 << 32, ctx->s3 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EBA08, ctx->s4 << 32, ctx->s5 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            sprintf(buf, D_800EBA20, ctx->s6 << 32, ctx->s7 << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0xC8, 0, 0);
            sprintf(buf, D_800EBA38, ctx->s8 << 32, ctx->gp << 32);
            D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, D_80102650 & 0xFF, (s32)D_801025D0, 0, 0, 0);
            oldstate = state;
            state = 0;
            osSetTime(0);
        }
        if (state == 3) {
            for (i = 0; i < 0x12C00; i++) {
                D_801025D0[i] = D_801025D4[i];
            }
            oldstate = state;
            state = 0;
            osSetTime(0);
        }
        if ((state == 0) && (sp64 == 0)) {
            osContStartReadData(&queue);
            osRecvMesg(&queue, &msg, OS_MESG_BLOCK);
            osContGetReadData(pad);
            button = pad->button;
            func_8002B210((s32)D_800F2030, 0xD2, 20, (s32)D_801025D0, 0, 0xFF, 0);
            func_8002B210((s32)D_800F2034, 0xD2, 30, (s32)D_801025D0, 0, 0xFF, 0);
            if ((button & 0x10) && !(oldButton & 0x10)) {
                if (oldstate == 1) {
                    state = 2;
                } else if (oldstate == 2) {
                    state = 3;
                } else if (oldstate == 3) {
                    state = 1;
                }
            }
            sp64 = 0;
            oldButton = button;
        }
    }
}


void func_8002CBB0(s32 arg0, DebugEntry *arg1) {
    s32 flag;
    char buf[256];

    flag = 1;
    if (D_800DFD30 == 1) {
        sprintf(buf, D_800EBA50, D_801025F0);
    } else {
        while (arg1->unk0 != 0) {
            if ((arg1->unk0 & arg0) == arg1->unk4) {
                sprintf(buf, D_800EBA54, arg1->unk8);
            }
            arg1++;
        }
    }
    D_80102650 = func_8002B210((s32)buf, D_80102650 >> 16, (D_80102650 & 0xFF) + 2, (s32)D_801025D0, 0xC8, 0, 0);
}

void func_8002CCC4(s32 arg0, s32 arg1, DebugEntry *arg2) {
    s32 first;

    first = 1;
    rmonPrintf(D_800EBA58, arg1, arg0);
    rmonPrintf(D_800EBA64);
    while (arg2->unk0 != 0) {
        if ((arg2->unk0 & arg0) == arg2->unk4) {
            if (first != 0) {
                first = 0;
            } else {
                rmonPrintf(D_800EBA68);
            }
            rmonPrintf(D_800EBA6C, arg2->unk8);
        }
        arg2++;
    }
    rmonPrintf(D_800EBA70);
}
