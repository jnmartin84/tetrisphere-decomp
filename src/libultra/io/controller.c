#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

OSPifRam __osContPifRam;
u8 __osContLastCmd;
u8 __osMaxControllers;

OSTimer __osEepromTimer;
OSMesgQueue __osEepromTimerQ ALIGNED(0x8);
OSMesg __osEepromTimerMsg;

extern s32 __osContinitialized;
extern u64 osClockRate;

void __osPackRequestData(u8);

s32 osContInit(OSMesgQueue* mq, u8* bitpattern, OSContStatus* status) {
    OSMesg mesg;
    u32 ret = 0;
    OSTime currentTime;
    OSTimer timer;
    OSMesgQueue timerMesgQueue;

    if (__osContinitialized) {
        return 0;
    }
    __osContinitialized = 1;
    currentTime = osGetTime();
    if (500000 * osClockRate / 1000000 > currentTime) {
        osCreateMesgQueue(&timerMesgQueue, &mesg, 1);
        osSetTimer(&timer, 500000 * osClockRate / 1000000 - currentTime, 0, &timerMesgQueue, &mesg);
        osRecvMesg(&timerMesgQueue, &mesg, OS_MESG_BLOCK);
    }
    __osMaxControllers = 4;
    __osPackRequestData(0);
    ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
    osRecvMesg(mq, &mesg, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
    osRecvMesg(mq, &mesg, OS_MESG_BLOCK);
    __osContGetInitData(bitpattern, status);
    __osContLastCmd = 0;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&__osEepromTimerQ, &__osEepromTimerMsg, 1);
    return ret;
}
void __osContGetInitData(u8* bitpattern, OSContStatus* status) {
    u8* ptr;
    __OSContRequesFormat response;
    s32 i;
    u8 bits;

    bits = 0;
    ptr = (u8*) __osContPifRam.ramarray;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(response), status++) {
        response = *((__OSContRequesFormat*) (ptr));
        status->errno = CHNL_ERR(response);
        if (status->errno == 0) {
            status->type = response.typel << 8 | response.typeh;
            status->status = response.status;

            bits |= 1 << i;
        }
    }

    *bitpattern = bits;
}
void __osPackRequestData(u8 command) {
    u8* ptr;
    __OSContRequesFormat requestHeader;
    s32 i;

    for (i = 0; i < ARRLEN(__osContPifRam.ramarray) + 1; i++) {
        __osContPifRam.ramarray[i] = 0;
    }

    __osContPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8*) __osContPifRam.ramarray;
    requestHeader.dummy = CONT_CMD_NOP;
    requestHeader.txsize = CONT_CMD_RESET_TX;
    requestHeader.rxsize = CONT_CMD_RESET_RX;
    requestHeader.cmd = command;
    requestHeader.typeh = CONT_CMD_NOP;
    requestHeader.typel = CONT_CMD_NOP;
    requestHeader.status = CONT_CMD_NOP;
    requestHeader.dummy1 = CONT_CMD_NOP;

    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContRequesFormat*) ptr = requestHeader;
        ptr += sizeof(requestHeader);
    }
    *ptr = CONT_CMD_END;
}
