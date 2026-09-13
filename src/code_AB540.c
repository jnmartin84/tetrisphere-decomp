#include "common.h"

extern s32 D_800E9590;
extern s32 D_800E9594;
extern s32 D_800E9598;
extern s32 D_800E959C;

void func_800D0190(u8 *arg0) {
    s32 argc;
    u8 *argv[32];
    u8 **p;
    u8 *s;

    argc = 1;
    p = argv;
    if (arg0 == 0 || *arg0 == 0) {
        return;
    }
    s = arg0;
    if (*s != 0) {
        do {
            if (*s != 0 && *s == 0x20) {
                do {
                    *s = 0;
                    s++;
                } while (*s != 0 && *s == 0x20);
            }
            if (*s != 0) {
                argv[argc] = s;
                argc++;
            }
            if (*s != 0 && *s != 0x20) {
                do {
                    s++;
                } while (*s != 0 && *s != 0x20);
            }
        } while (*s != 0);
    }
    if (argc >= 2 && p[1][0] == 0x2D) {
        do {
            switch (p[1][1]) {
            case 0x64: D_800E9594 = 1; break;
            case 0x76: D_800E9590 = 1; break;
            case 0x73: D_800E9598 = 1; break;
            case 0x6C: D_800E959C = 1; break;
            default: break;
            }
            argc--;
            p++;
        } while (argc >= 2 && p[1][0] == 0x2D);
    }
}
