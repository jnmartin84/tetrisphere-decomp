#include "common.h"

typedef struct {
    u32 outputRate;      /* 0x0 */
    u32 framesPerField;  /* 0x4 */
    u32 maxACMDSize;     /* 0x8 */
} AMConfig;
typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    void *dmaproc;       /* 0x10 */
    void *heap;          /* 0x14 */
    s32 outputRate;      /* 0x18 */
} SynCfg;
typedef struct AMTask_s {
    void *data;             /* 0x0 */
    u8 pad04[0x6C];
    s16 type;               /* 0x70 */
    struct AMTask_s *self;  /* 0x74 */
    u8 pad78[0x18];
} AMTask;                   /* 0x90 */
typedef struct {
    void *ACMDList[2];      /* 0x0 */
    AMTask *audioInfo[3];   /* 0x8 */
    u8 pad14[4];            /* 0x14 align pad */
    u8 thread[0x1B0];       /* 0x18 OSThread */
    u8 frameMsgQ[0x18];     /* 0x1C8 */
    void *frameMsgBuf[8];   /* 0x1E0 */
    u8 replyMsgQ[0x18];     /* 0x200 */
    void *replyMsgBuf[8];   /* 0x218 */
    u8 g[8];                /* 0x238 ALGlobals (size unknown, tail) */
} AM;
extern AM D_80104CD0;
extern u32 D_80106F64;
extern u32 D_80106F68;
extern u32 D_80106F6C;
extern u32 D_80106F70;
extern u32 D_80106FAC;
extern u32 D_80106FB4;
extern u8 *D_80106FB0;
extern u8 D_80106F58[];
extern u8 D_80106F90[];
extern void *D_80106FA8[1];
extern s32 osTvType;
extern void *func_8007F070(void *);
extern void func_8007EBDC(void *);
void func_8007E800(SynCfg *c, s32 pri, AMConfig *amc) {
    s32 frameRate;
    f32 fsize;
    u32 i;
    c->dmaproc = func_8007F070;
    c->outputRate = osAiSetFrequency(amc->outputRate);
    if (osTvType == 0) {
        frameRate = 50;
    } else {
        frameRate = 60;
    }
    fsize = (f32)amc->framesPerField * c->outputRate / (f32)frameRate;
    D_80106F68 = (s32)fsize;
    if ((f32)D_80106F68 < fsize) {
        D_80106F68 += 1;
    }
    if (D_80106F68 & 0xF) {
        D_80106F68 = (D_80106F68 & ~0xF) + 0x10;
    }
    D_80106F64 = D_80106F68 - 0x10;
    D_80106F6C = D_80106F68 + 0x60;
    alInit(D_80104CD0.g, c);
    for (i = 0; i < 2; i++) {
        D_80104CD0.ACMDList[i] = alHeapDBAlloc(0, 0, c->heap, 1, amc->maxACMDSize * 8);
    }
    D_80106F70 = amc->maxACMDSize;
    for (i = 0; i < 3; i++) {
        D_80104CD0.audioInfo[i] = alHeapDBAlloc(0, 0, c->heap, 1, 0x90);
        D_80104CD0.audioInfo[i]->type = 2;
        D_80104CD0.audioInfo[i]->self = D_80104CD0.audioInfo[i];
        D_80104CD0.audioInfo[i]->data = alHeapDBAlloc(0, 0, c->heap, 1, D_80106F6C * 4);
    }
    D_80106FAC = (u32)alHeapDBAlloc(0, 0, c->heap, 1, 0x7530);
    D_80106FB0 = (u8 *)D_80106FAC;
    osCreateMesgQueue(D_80104CD0.replyMsgQ, D_80104CD0.replyMsgBuf, 8);
    osCreateMesgQueue(D_80104CD0.frameMsgQ, D_80104CD0.frameMsgBuf, 8);
    osCreateMesgQueue(D_80106F90, D_80106FA8, 1);
    osCreateThread(D_80104CD0.thread, 3, func_8007EBDC, 0, D_80106F58, pri);
    osStartThread(D_80104CD0.thread);
}

extern s32 D_800E28E0;
extern u32 D_80104F4C;

void func_8007EAD0(s32 arg0) {
    u32 freq;
    s32 rate;
    f32 f;
    u32 v;
    f32 one = 1.0f;
    f32 fq;
    D_800E28E0 = arg0;
    freq = osAiSetFrequency(arg0);
    if (osTvType == 0) {
        rate = 0x32;
    } else {
        rate = 0x3C;
    }
    fq = (f32) freq;
    f = (one * fq) / ((f32) rate);
    D_80106F68 = (s32) f;
    v = D_80106F68;
    if (((f32) v) < f) {
        v = (D_80106F68 = v + 1);
    }
    if (v & 0xF) {
        if (1) {
        }
        v = (D_80106F68 = (v & (~0xF)) + 0x10);
    }
    D_80106F64 = v - 0x10;
    D_80106F6C = v + 0x60;
    D_80104F4C = freq;
}

typedef struct 
{
  s16 type;
  s16 pad2;
  s32 unk4;
} AMMsg;
extern u8 D_800E28D0;
extern u32 D_800E28C0;
extern u8 D_800FDEF0[];
extern u8 D_80104E98[];
extern u8 D_80104ED0[];
extern u8 D_80104F08[];
extern void *D_80104CD8[3];
extern u8 D_80107290[];
extern u8 D_80108828[];
extern u8 D_80109DC0[];
extern void osScAddClient(void *, void *, void *);
extern s32 func_8007ED88();
extern void func_8007EF50(s32);
extern void func_80079B80(s32, void *);
void func_8007EBDC(void *arg)
{
  volatile s32 pad[2];
  AMMsg *msg;
  u8 client[0xC];
  unsigned int done;
  s32 samples;
  done = 0;
  msg = 0;
  samples = 0;
  D_800E28D0 = 0;
  osScAddClient(D_800FDEF0, client, D_80104E98);
  while (!done)
  {
    osRecvMesg((OSMesgQueue *)D_80104E98, (OSMesg *)&msg, 1);
    switch (msg->type)
    {
      case 1:
        if (func_8007ED88(D_80104CD8[D_800E28C0 % 3], samples))
      {
        osRecvMesg((OSMesgQueue *)D_80104ED0, (OSMesg *)&msg, 1);
        func_8007EF50(msg->unk4);
        samples = msg->unk4;
      }
        break;
      case 4:
        D_800E28D0 = 1;
        func_80079B80(0, D_80107290);
        func_80079B80(0, D_80108828);
        func_80079B80(0, D_80109DC0);
        break;
      case 10:
        done = 1;
        break;
    }
  }
  alClose((ALGlobals *)D_80104F08);
}

typedef struct {
    u32 type; u32 flags;
    u64 *ucode_boot; u32 ucode_boot_size;
    u64 *ucode; u32 ucode_size;
    u64 *ucode_data; u32 ucode_data_size;
    u64 *dram_stack; u32 dram_stack_size;
    u64 *output_buff; u32 output_buff_size;
    u64 *data_ptr; u32 data_size;
    u64 *yield_data_ptr; u32 yield_data_size;
} Tsk8ED;
typedef struct ScT8ED {
    struct ScT8ED *next; u32 state; u32 flags; void *framebuffer;
    struct { Tsk8ED t; } list; void *msgQ; void *msg;
} ScT8ED;
typedef struct {
    s16 *data; s16 frameSamples; ScT8ED task; u8 pad60[0x10]; u8 msg[0x10];
} AInf8ED;

extern u32 D_80106F64;
extern u32 D_80106F68;
extern s32 D_800E28C8;
extern u8 D_80104ED0[];
extern void *D_800FE178;
extern u8 D_800DE7D0[];
extern u8 D_800F1D70[];
extern void func_8007F080(void);

#define CMDL ((Acmd *)D_80104CD0.ACMDList[D_800E28C8])
s32 func_8007ED88(info, lastInfo)
AInf8ED *info;
AInf8ED *lastInfo;
{
    s16 *audioPtr;
    Acmd *cmdp;
    s32 cmdLen;
    s32 samplesLeft;
    ScT8ED *t;
    s32 pad1;
    s32 pad2;

    func_8007F080();
    audioPtr = (s16 *) osVirtualToPhysical(info->data);
    if (lastInfo)
        osAiSetNextBuffer(lastInfo->data, lastInfo->frameSamples << 2);
    samplesLeft = osAiGetLength() >> 2;
    info->frameSamples = (16 + (D_80106F68 - samplesLeft + 80)) & 0xfff0;
    if (info->frameSamples < D_80106F64)
        info->frameSamples = D_80106F64;
    cmdLen = 0;
    cmdp = alAudioFrame(CMDL, &cmdLen, audioPtr, info->frameSamples);
    if (cmdLen == 0)
        return 0;
    if (cmdLen == 0)
        return 0;
    t = &info->task;
    t->next = 0;
    t->msgQ = &D_80104ED0;
    t->msg = (void *) &info->msg;
    t->flags = 2;
    t->list.t.data_ptr = (u64 *) CMDL;
    t->list.t.data_size = (cmdp - CMDL) * sizeof(Acmd);
    t->list.t.type = 2;
    t->list.t.ucode_boot = (u64 *) rspbootTextStart;
    t->list.t.ucode_boot_size = ((int) gspFast3D_fifoTextStart - (int) rspbootTextStart);
    t->list.t.flags = 0;
    t->list.t.ucode = (u64 *) D_800DE7D0;
    t->list.t.ucode_data = (u64 *) D_800F1D70;
    t->list.t.ucode_data_size = 0x800;
    t->list.t.dram_stack = (u64 *) 0;
    t->list.t.output_buff = (u64 *) 0;
    t->list.t.output_buff_size = 0;
    t->list.t.yield_data_ptr = 0;
    t->list.t.yield_data_size = 0;
    osSendMesg(D_800FE178, (void *) t, 1);
    D_800E28C8 ^= 1;
    return 1;
}
#undef CMDL

extern s32 D_800E28D4;
extern char D_800EE460[];
extern void func_80029760(char *);
void func_8007EF50(s32 arg0) {
    if (osAiGetLength() >> 2) {
        return;
    }
    if (D_800E28D4) {
        return;
    }
    func_80029760(D_800EE460);
    D_800E28D4 = 0;
}

extern u32 func_800D0480(s32, s32, s32, u32 *);

s32 func_8007EF9C(s32 arg0, s32 arg1, void *arg2) {
    if ((u32)arg0 < 0x80000001U || (u32)arg0 >= 0x80400000U) {
        return arg0;
    }
    D_80106FB4 = D_80106FAC;
    arg1 = (arg1 + 0xF) & ~0xF;
    if (arg1 >= 0x7531) {
        return D_80106FAC;
    }
    if ((u32)(D_80106FAC + 0xEA60) < (u32)(arg1 * 2 + D_80106FAC)) {
        return D_80106FAC;
    }
    D_80106FAC = func_800D0480(arg0, D_80106FAC, arg1, &D_80106FAC);
    D_80106FAC = (D_80106FAC + 0xF) & ~0xF;
    return osVirtualToPhysical((void *)D_80106FB4);
}

typedef s32 (*DmaProc)(s32 addr, s32 len, void *state);
extern s32 func_8007EF9C(s32 addr, s32 len, void *state);
void *func_8007F070(void *arg0) {
    return func_8007EF9C;
}

extern char D_800EE47C[];
void func_8007F080(void) {
    if (++D_800E28C0 == 0) {
        func_80029760(D_800EE47C);
    }
    D_80106FAC = (u32)D_80106FB0;
}
