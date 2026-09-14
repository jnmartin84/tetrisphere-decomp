#include "common.h"

#include <ultra64.h>
/* os_host.h macro-expands osInitialize() to __osInitialize_common(); this ROM
 * calls the real osInitialize (symbol_addrs.txt: 0x800D1DC0), so bypass the
 * macro. ultracheck cannot catch this class of error -- it masks jal targets,
 * so calling the wrong function still reads as a match. Only the linker did. */
#undef osInitialize
extern void osInitialize(void);
extern s32 leomecha_bss_0004;
extern u8 D_800DF72C;
extern OSThread idleThread;
extern u8 idleThreadStack[];
extern void idle(void *);
void main(void *arg) {
    u32 i;
    s32 addr;
    u32 buf[16];
    leomecha_bss_0004 = 0;
    D_800DF72C = 0;
    osInitialize();
    addr = 0xFFB000;
    for (i = 0; i < 16; i++, addr += 4) {
        osPiRawReadIo(addr, &buf[i]);
    }
    osCreateThread(&idleThread, 1, idle, arg, idleThreadStack + 0x2000, 0xA);
    osStartThread(&idleThread);
}

#include <ultra64.h>
extern OSMesgQueue D_80102340;
extern s32 D_800F2044;
extern OSThread *D_800F2040;
extern void func_8002B348(OSThread *);
extern void func_800D045C(void);
void fault(void *arg) {
    OSMesg msg;
    volatile s32 pad[2];
    osSetEventMesg(OS_EVENT_FAULT, &D_80102340, (OSMesg)0x10);
    D_800F2044 = 0;
    while (1) {
        osRecvMesg(&D_80102340, &msg, 1);
        D_800F2040 = __osGetCurrFaultedThread();
        if (D_800F2040 != 0) {
            func_8002B348(D_800F2040);
            func_800D045C();
            while (1) {
            }
        }
    }
}

#include <ultra64.h>
extern OSMesgQueue D_800FAB68;
extern OSMesg D_800FA848[];
extern OSMesg D_80102358[];
extern OSThread faultThread;
extern u8 faultThreadStack[];
extern OSThread mainThread;
extern u8 mainThreadStack[];
extern void fault(void *);
extern void mainproc(void *);
void idle(void *arg) {
    osCreatePiManager(0x96, &D_800FAB68, D_800FA848, 0xC8);
    osCreateMesgQueue(&D_80102340, D_80102358, 1);
    osCreateThread(&faultThread, 2, fault, arg, faultThreadStack + 0x400, 0x32);
    osStartThread(&faultThread);
    osCreateThread(&mainThread, 6, mainproc, arg, mainThreadStack + 0x2000, 0xA);
    osStartThread(&mainThread);
    osSetThreadPri(0, 0);
    while (1) {
    }
}

void func_80029760(const char *fmt, ...) {
}

#include <ultra64.h>
extern u8 D_800F2050[];
extern u8 D_800F2250[];
extern s32 D_800DF754;
extern void *D_800F204C;
extern s16 D_800F2048;
extern u8 D_800DF744;
extern OSMesgQueue D_800FAC68;
extern u8 D_800EAFC0[];
extern void func_80029760(const char *, ...);
void requestEepromWrite(u8 *arg) {
    s32 i;
    s32 j;
    for (i = 0; i < 0x40; i++) {
        for (j = 0; j < 8; j++) {
            if (arg[i * 8 + j] != D_800F2050[i * 8 + j]) {
                D_800F2250[i] = 1;
                func_80029760(D_800EAFC0, i);
                break;
            }
        }
    }
    for (i = 0; i < 0x200; i++) {
        D_800F2050[i] = arg[i];
    }
    if (D_800DF754 != 0) {
        D_800F204C = arg;
        D_800F2048 = 1;
        D_800DF744 = 1;
        osSendMesg(&D_800FAC68, &D_800F2048, 0);
    }
}

#include <ultra64.h>
extern u8 D_800DF740;
void func_800298C4(void *arg) {
    if (D_800DF754 != 0) {
        D_800F204C = arg;
        D_800F2048 = 2;
        D_800DF740 = 1;
        osSendMesg(&D_800FAC68, &D_800F2048, 0);
    }
}

#include <ultra64.h>
#include <PR/sched.h>
typedef struct {
    s16 type;
} BootMsg;
extern OSMesgQueue D_800FABB8;
extern OSMesg D_800FABD0[];
extern OSMesgQueue D_800FAC10;
extern OSSched D_800FDEF0;
extern OSScClient D_80100188;
extern BootMsg D_80102360;
extern BootMsg D_80102380;
extern BootMsg *D_800DF738;
extern OSMesg D_800DF73C;
extern void *D_8010018C;
extern u8 D_800F2290;
extern s32 leomecha_bss_0004;
extern s32 D_800DF714;
extern s32 D_800DF718;
extern s32 D_800DF71C;
extern s32 D_801023A0;
extern u8 D_800EAFD4[];
extern u8 D_800EAFE4[];
extern u8 D_800EAFFC[];
extern u8 D_800EB00C[];
extern u8 D_800EB01C[];
extern u8 D_800EB030[];
extern u8 D_800EB03C[];
extern void func_80029760(const char *, ...);
extern void readAndDispatchControllerData(void);
void controllerEepromThreadMain(void *arg) {
    volatile s32 pad;
    u16 flag;
    BootMsg *msg;
    s32 j;
    flag = 0;
    osSetEventMesg(5, &D_800FABB8, &D_80102360);
    osScAddClient(&D_800FDEF0, &D_80100188, &D_800FABB8);
    D_800F2290 = 0x32;
    D_800DF72C = 1;
    leomecha_bss_0004 = 0;
    while (1) {
        osRecvMesg(&D_800FABB8, (OSMesg *)&D_800DF738, 1);
        if (osRecvMesg(&D_800FAC68, (OSMesg *)&msg, 0) == 0) {
            func_80029760(D_800EAFD4);
            switch (msg->type) {
            case 1:
                osSetEventMesg(5, &D_800FAC10, &D_80102380);
                D_8010018C = &D_800FAC10;
                for (j = 0; j < 0x40; j++) {
                    if (D_800F2250[j] == 1) {
                        D_800F2250[j] = 0;
                        func_80029760(D_800EAFE4, j);
                        if (osEepromWrite(&D_800FAC10, j, j * 8 + (u8 *)D_800F204C) != 0) {
                            func_80029760(D_800EAFFC);
                            break;
                        }
                        osRecvMesg(&D_800FAC10, &D_800DF73C, 1);
                    }
                }
                D_800DF744 = 0;
                osSetEventMesg(5, &D_800FABB8, &D_80102360);
                D_8010018C = &D_800FABB8;
                D_800FABB8.validCount = 0;
                D_800FABD0[D_800FABB8.first] = D_800FABD0[D_800FABB8.first & 8];
                break;
            case 2:
                osSetEventMesg(5, &D_800FAC10, &D_80102380);
                D_8010018C = &D_800FAC10;
                func_80029760(D_800EB00C);
                for (j = 0; j < 0x40; j++) {
                    if (osEepromRead(&D_800FAC10, j, j * 8 + (u8 *)D_800F204C) != 0) {
                        func_80029760(D_800EB01C, j);
                        break;
                    }
                    osRecvMesg(&D_800FAC10, &D_800DF73C, 1);
                }
                for (j = 0; j < 0x200; j++) {
                    D_800F2050[j] = ((u8 *)D_800F204C)[j];
                }
                func_80029760(D_800EB030);
                osSetEventMesg(5, &D_800FABB8, &D_80102360);
                D_8010018C = &D_800FABB8;
                D_800FABB8.validCount = 0;
                D_800FABD0[D_800FABB8.first] = D_800FABD0[D_800FABB8.first & 8];
                D_800DF740 = 0;
                break;
            default:
                break;
            }
        }
        if (D_800DF740 == 0 || D_800DF744 == 0) {
            switch (D_800DF738->type) {
            case 1:
                if (D_800DF718 == D_800DF714) {
                    D_800DF71C++;
                    if (D_800DF71C == 0x258) {
                        func_80029760(D_800EB03C);
                    }
                } else {
                    D_800DF718 = D_800DF714;
                    D_800DF71C = 0;
                }
                if (D_801023A0 != 0) {
                    D_801023A0 = 0;
                    osContStartReadData(&D_800FABB8);
                }
                break;
            case 3:
                readAndDispatchControllerData();
                D_801023A0 = 1;
                break;
            case 0xA:
                flag = 1;
                break;
            default:
                break;
            }
        }
    }
}

#include <ultra64.h>
extern u8 D_80166F20[];
extern u8 *D_800F22C0;
extern u8 *D_800F22C4;
extern u8 D_802A2000[];
extern u8 D_800FACC0[];
extern u8 D_800EB06C[];
extern u8 D_800EB094[];
extern OSThread schedThread;
extern u8 D_80108811;
extern u8 D_80108825;
extern u8 D_80107290[];
extern u8 gAnimPlayer[];
extern u8 gAnimPlayer2[];
extern OSMesgQueue D_800F22C8;
extern u32 D_800DF720;
extern s32 leomecha_bss_0004;
extern u32 func_800334D8(void);
extern void func_80029760(const char *, ...);
extern void initScheduler(void);
extern void buildAndSubmitGraphicsTasks(void *);
extern void func_8007ACFC(void *);
extern void func_8007ADF8(void *);
void mainproc(void *arg) {
    s32 unk34 = 0;
    BootMsg *msg = NULL;
    volatile s32 pad;
    s32 i;
    D_800F22C0 = D_80166F20;
    D_800F22C4 = D_800F22C0;
    *(u8 **)(D_800FACC0 + 0x18EC) = D_802A2000 + 0xFFFC4000;
    *(u8 **)(D_800FACC0 + 0x3204) = D_802A2000 + 0xFFFC6000;
    *(u8 **)(D_800FACC0 + 0x18E8) = D_802A2000 + 0xFFFC8000;
    *(u8 **)(D_800FACC0 + 0x3200) = D_802A2000 + 0xFFFE0000;
    func_80029760(D_800EB06C, func_800334D8());
    initScheduler();
    for (i = 0; i < 0x200; i++) {
        D_800F2050[i] = 0;
    }
    for (i = 0; i < 0x40; i++) {
        D_800F2250[i] = 0;
    }
    osSetEventMesg(5, &D_800FABB8, &D_80102360);
    D_800DF754 = osEepromProbe(&D_800FABB8);
    if (D_800DF754 != 0) {
    } else {
    }
    osStartThread(&schedThread);
    D_80108811 = 1;
    D_80108825 = 0;
    func_8007ACFC(D_80107290);
    while (1) {
        osRecvMesg(&D_800F22C8, (OSMesg *)&msg, 1);
        if (D_800DF720 < 2) {
            buildAndSubmitGraphicsTasks(D_800FACC0);
        }
        switch (msg->type) {
        case 1:
            break;
        case 2:
            D_800DF714++;
            D_800DF720--;
            break;
        case 4:
            func_80029760(D_800EB094);
            leomecha_bss_0004 = 1;
            func_8007ADF8(D_80107290);
            func_8007ADF8(gAnimPlayer);
            func_8007ADF8(gAnimPlayer2);
            break;
        }
    }
}

extern u8 D_490B10[];
extern u8 *loadAsset(u8 *, s32, s32);
void *loadAnim(s32 arg) {
    return loadAsset(D_490B10, arg, 8);
}

extern u8 D_5921F0[];
extern u8 *loadAsset(u8 *, s32, s32);
void *loadMesh(s32 arg) {
    return loadAsset(D_5921F0, arg, 8);
}

#include <ultra64.h>
extern s32 leomecha_bss_0004;
extern void func_8007ADF8(void *);
void func_8002A140(void) {
    s32 unk2C = 0;
    s32 unk28 = 0;
    BootMsg *msg = NULL;
    osRecvMesg(&D_800F22C8, (OSMesg *)&msg, 1);
    switch (msg->type) {
    case 2:
        D_800DF714++;
        D_800DF720--;
        break;
    case 4:
        leomecha_bss_0004 = 1;
        func_8007ADF8(D_80107290);
        func_8007ADF8(gAnimPlayer);
        func_8007ADF8(gAnimPlayer2);
        break;
    }
}

extern s32 leomecha_bss_0004;
extern void buildAndSubmitGraphicsTasks(void *);
extern void func_8007ADF8(void *);
void func_8002A218(void) {
    s32 unk2C = 0;
    s32 unk28 = 0;
    BootMsg *msg = NULL;
    while (1) {
        osRecvMesg(&D_800F22C8, (OSMesg *)&msg, 1);
        if (D_800DF720 < 2) {
            buildAndSubmitGraphicsTasks(D_800FACC0);
        }
        switch (msg->type) {
        case 1:
            break;
        case 2:
            D_800DF714++;
            D_800DF720--;
            break;
        case 4:
            leomecha_bss_0004 = 1;
            func_8007ADF8(D_80107290);
            func_8007ADF8(gAnimPlayer);
            func_8007ADF8(gAnimPlayer2);
            break;
        }
    }
}

#include <ultra64.h>
extern OSMesgQueue D_800FAB80;
extern OSMesg D_800F22B0;
extern u8 D_800DF758;
s32 dmaReady(void) {
    if (osRecvMesg(&D_800FAB80, &D_800F22B0, 0) != -1) {
        D_800DF758 = 0;
    }
    return D_800DF758 == 0;
}

#include <ultra64.h>
extern OSIoMesg D_800F2298;
extern s32 dmaReady(void);
void dmaRomToRamAsync(u32 devAddr, void *dramAddr, u32 size) {
    while (!dmaReady()) {
    }
    D_800DF758 = 1;
    osInvalDCache(dramAddr, size);
    osPiStartDma(&D_800F2298, 0, 0, devAddr, dramAddr, size, &D_800FAB80);
}

#include <ultra64.h>
extern s32 dmaReady(void);
void dmaRomToRam(u32 devAddr, void *dramAddr, u32 size) {
    while (!dmaReady()) {
    }
    osInvalDCache(dramAddr, size);
    osPiStartDma(&D_800F2298, 0, 0, devAddr, dramAddr, size, &D_800FAB80);
    osRecvMesg(&D_800FAB80, &D_800F22B0, 1);
}

#include <ultra64.h>
#include <PR/sched.h>
extern s16 D_8013FAD6;
extern u8 D_803B5000[];
extern u8 D_803DA800[];
extern OSMesg D_800FAB98[];
extern OSMesg D_800F22E0[];
extern u8 D_800FE180[];
extern OSMesgQueue *D_800FE178;
extern OSScClient D_80100180;
extern OSMesg D_800FAC28[];
extern u8 schedThreadStack[];
extern u8 D_CD3F0[];
extern u8 D_CD570[];
extern u8 D_80164E60[];
extern u8 D_800F2328[];
extern void controllerEepromThreadMain(void *);
extern s32 initControllers(void);
extern void func_8007F0D0(void *);
extern void dmaRomToRam(u32, void *, u32);
extern void func_8002A754(void);
extern void func_800AF09C(s32);
void initScheduler(void) {
    /* ROM reserves 24 bytes of frame that no instruction touches (frame 0x48
     * against 0x30 of live content); the originals are unrecoverable. `i` must
     * be `register` -- an ordinary local gets a -g stack home, which ROM's
     * counter does not have. */
    s32 pad[6];
    register s32 i;
    D_8013FAD6 = 1;
    for (i = 0; i < 0x25800; i++) {
        ((s16 *)D_803B5000)[i] = 0;
    }
    osCreateViManager(OS_PRIORITY_VIMGR);
    osCreateMesgQueue(&D_800FAB80, D_800FAB98, 8);
    osCreateMesgQueue(&D_800F22C8, D_800F22E0, 8);
    if (osTvType == 0) {
        osCreateScheduler(&D_800FDEF0, D_800FE180 + 0x2000, 13, OS_VI_PAL_LAN1, 1);
    }
    if (osTvType == 1) {
        osCreateScheduler(&D_800FDEF0, D_800FE180 + 0x2000, 13, OS_VI_NTSC_LAN1, 1);
    }
    if (osTvType == 2) {
        osCreateScheduler(&D_800FDEF0, D_800FE180 + 0x2000, 13, OS_VI_MPAL_LAN1, 1);
    }
    osViSwapBuffer(D_803DA800);
    osScAddClient(&D_800FDEF0, &D_80100180, &D_800F22C8);
    D_800FE178 = osScGetCmdQ(&D_800FDEF0);
    osCreateMesgQueue(&D_800FABB8, D_800FABD0, 16);
    osCreateMesgQueue(&D_800FAC10, D_800FAC28, 16);
    osCreateMesgQueue(&D_800FAC68, D_800FAC28, 16);
    osCreateThread(&schedThread, 5, controllerEepromThreadMain, NULL, schedThreadStack + 0x2000, 11);
    D_801023A0 = initControllers();
    func_8007F0D0(D_800F2328);
    dmaRomToRam((u32)D_CD3F0, D_80164E60, D_CD570 - D_CD3F0);
    func_8002A754();
    D_80102360.type = 3;
    D_80102380.type = 5;
    func_800AF09C(1);
}

#include <ultra64.h>
extern u8 D_CD7C0[];
extern u8 *D_800DF75C;
extern u8 D_80164FE0[];
extern u8 D_800E95B0[];
extern void dmaRomToRam(u32, void *, u32);
void func_8002A754(void) {
    s32 size = D_CD7C0 - D_CD570;
    D_800DF75C = D_80164FE0;
    dmaRomToRam((u32)D_CD570, D_800DF75C, size);
    *(s16 *)(D_800FACC0 + 0x18F0) = 2;
    *(u8 **)(D_800FACC0 + 0x1910) = D_803B5000;
    *(s16 *)(D_800FACC0 + 0x3208) = 2;
    *(u8 **)(D_800FACC0 + 0x3228) = D_803DA800;
    if (osTvType == 0) {
        osViSetMode((OSViMode *)(D_800E95B0 + 0x500));
    }
    if (osTvType == 1) {
        osViSetMode((OSViMode *)(D_800E95B0 + 0xA0));
    }
    if (osTvType == 2) {
        osViSetMode((OSViMode *)(D_800E95B0 + 0x960));
    }
    osViSetSpecialFeatures(0x42);
}

extern u8 D_7D4A70[];
extern u8 D_8013D270[];
extern void func_8002AB74(u8 *, u8 *, s32);
extern void func_80088914(void);
void func_8002A870(s32 arg) {
    func_8002AB74(D_7D4A70, D_8013D270, arg);
    func_80088914();
}

#include <ultra64.h>
extern u8 D_800EB0A4[];
extern u8 D_800EB0B8[];
extern u8 D_800EB0D4[];
extern u8 D_800EB0F4[];
extern u8 D_800EB110[];
extern u8 D_800EB124[];
extern u8 D_800EB134[];
extern u8 D_800EB154[];
extern u8 D_800F2300[];
extern void dmaRomToRam(u32, void *, u32);
extern void func_8002AF20(const char *, const char *);
extern u32 lwDecode(void *, void *);
extern u32 func_800334D8(void);
u8 *loadAsset(u8 *romAddr, s32 idx, s32 arg2) {
    u8 *ret;
    /* ROM reserves 8 bytes at 0x3C-0x43 that nothing touches. The table
     * offsets must be spelled `romAddr + 2 + (idx << 2)`: `* 4` lets IDO
     * reassociate (idx+1)*4+2 into idx*4+6, which ROM does not do -- `<< 2`
     * blocks the fold, and the `+ 2` must bind to romAddr (the table base,
     * past the 2-byte header) rather than trail the index term. */
    volatile s32 pad[2];
    u32 hdr;
    u32 ents[4];
    u16 i;
    u8 *dst;
    u32 size;
    u32 x;
    i = 0;
    D_800F22C0 = (u8 *)(((u32)D_800F22C0 + 0xF) & ~0xF);
    dmaRomToRam((u32)romAddr, &hdr, 2);
    dmaRomToRam((u32)(romAddr + 2 + (idx << 2)), &ents[0], 4);
    dmaRomToRam((u32)(romAddr + 2 + ((idx + 1) << 2)), &ents[2], 4);
    dst = (u8 *)0x80000400;
    size = ents[2] - ents[0];
    if (size == 0 || size >= 0x400000) {
        sprintf((char *)D_800F2300, (const char *)D_800EB0A4, idx, romAddr);
        func_8002AF20((const char *)D_800F2300, (const char *)D_800EB0B8);
    }
    if (func_800334D8() < size) {
        sprintf((char *)D_800F2300, (const char *)D_800EB0D4, idx, romAddr);
        func_8002AF20((const char *)D_800F2300, (const char *)D_800EB0F4);
    }
    dmaRomToRam(ents[0] + (u32)romAddr, dst, size);
    for (i = 0; i < dst[0]; i++) {
        if (dst[i + 1] == 0x48) {
            sprintf((char *)D_800F2300, (const char *)D_800EB110, romAddr, idx);
            func_8002AF20((const char *)D_800EB124, (const char *)D_800F2300);
        }
    }
    x = lwDecode(dst, D_800F22C0);
    if (func_800334D8() < x) {
        sprintf((char *)D_800F2300, (const char *)D_800EB134, idx, romAddr);
        func_8002AF20((const char *)D_800F2300, (const char *)D_800EB154);
    }
    ret = D_800F22C0;
    D_800F22C0 += x;
    D_800F22C0 = (u8 *)(((u32)D_800F22C0 + 0xF) & ~0xF);
    return ret;
}

#include <ultra64.h>
extern u8 D_800EB170[];
extern u8 D_800EB184[];
extern void dmaRomToRam(u32, void *, u32);
extern void func_8002AF20(const char *, const char *);
extern u32 lwDecode(void *, void *);
void func_8002AB74(u8 *romAddr, u8 *arg1, s32 idx) {
    volatile s32 pad;
    u32 hdr;
    u32 ents[4];
    u16 i;
    u8 *dst;
    s32 size;
    s32 ret;
    i = 0;
    dmaRomToRam((u32)romAddr, &hdr, 2);
    dmaRomToRam((u32)(romAddr + 2 + (idx << 2)), &ents[0], 4);
    dmaRomToRam((u32)(romAddr + 2 + ((idx + 1) << 2)), &ents[2], 4);
    dst = (u8 *)0x80000400;
    size = ents[2] - ents[0];
    dmaRomToRam((u32)romAddr + ents[0], dst, size);
    for (i = 0; i < dst[0]; i++) {
        if (dst[i + 1] == 0x48) {
            sprintf((char *)D_800F2300, (const char *)D_800EB170, romAddr, idx);
            func_8002AF20((const char *)D_800EB184, (const char *)D_800F2300);
        }
    }
    ret = lwDecode(dst, arg1);
}

extern void func_8002AB74(u8 *, u8 *, s32);
void func_8002ACDC(u8 *a, u8 *b, s32 c) {
    func_8002AB74(a, b, c);
}
