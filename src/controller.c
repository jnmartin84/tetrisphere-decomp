#include <ultra64.h>

/* Controller (joypad) input module */

extern u8 D_800DF770;      /* bit pattern of connected controllers */
extern s32 D_800DF778;     /* input processing enabled */
extern u16 D_800DFD5C;
extern char D_800EB1A0[];  /* "Failure initing controllers\n" */
extern OSContStatus D_80102580[4];
extern OSContPad D_80102590[4];

void func_80029760(char *);   /* error print */
void func_8006DF3C(u16, u16); /* handle pad input (buttons, port) */

s32 initControllers(void) {
    OSMesgQueue queue;
    OSMesg msg;
    s32 ret;

    osCreateMesgQueue(&queue, &msg, 1);
    osSetEventMesg(OS_EVENT_SI, &queue, (OSMesg)1);
    ret = osContInit(&queue, &D_800DF770, D_80102580);
    if (ret != 0) {
        func_80029760(D_800EB1A0);
    }
    for (ret = 0; ret < 4; ret++) {
        if ((D_800DF770 & (1 << ret)) && !(D_80102580[ret].errno & CONT_NO_RESPONSE_ERROR)) {
            return -1;
        }
    }
    return D_800DF770;
}

void readAndDispatchControllerData(void) {
    OSContPad *pad;
    u16 i;

    osContGetReadData(D_80102590);
    if (D_800DF778 != 0) {
        for (i = 0; i < 4; i++) {
            if ((D_800DF770 >> i) & 1) {
                pad = &D_80102590[i];
                if (pad->errno != 0) {
                    if (D_800DFD5C != 0) {
                        func_8006DF3C(0, i);
                    } else {
                        func_8006DF3C(0x1000, i);
                    }
                } else {
                    func_8006DF3C(pad->button, i);
                }
            }
        }
    }
}
