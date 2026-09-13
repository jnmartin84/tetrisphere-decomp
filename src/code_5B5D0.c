#include "common.h"

extern u8 D_800E2A98;
extern u8 D_800E2A9C;
extern u8 *D_8010FDB0;
extern u32 D_8010FDB8;
extern s32 D_8010FDA0;
extern s32 D_8010FDA4;
extern s32 D_8010FDC4;
extern u8 D_8010FDD8;

void lwCopy(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *d = arg0;
    u8 *s = arg1;
    while (arg2--) {
        *d++ = *s++;
    }
}

void func_80080280(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p = arg0;
    while (arg2--) {
        *p++ = arg1;
    }
}

extern u8 *D_8010FDB0;
extern u32 D_8010FDB4;
extern u32 D_8010FDB8;
extern u8 *D_8010FDBC;
extern s32 D_8010FDC0;
extern u8 *D_80110218;
void lwFilterD(void) {
    D_8010FDC0 = 0;
    D_8010FDB8 = 0;
    D_8010FDBC[D_8010FDC0++] = D_8010FDB0[D_8010FDB8++];
    while (D_8010FDB8 < D_8010FDB4) {
        D_8010FDBC[D_8010FDC0++] = D_8010FDBC[D_8010FDC0 - 1] - D_8010FDB0[D_8010FDB8++];
    }
    D_80110218 = D_8010FDB0;
    D_8010FDB0 = D_8010FDBC;
    D_8010FDBC = D_80110218;
    D_8010FDB4 = D_8010FDC0;
}


extern u8 *D_8010FDB0;
extern u32 D_8010FDB4;
extern u32 D_8010FDB8;
extern u8 *D_8010FDBC;
extern s32 D_8010FDC0;
extern u8 *D_80110218;
void lwFilterF(void) {
    D_8010FDC0 = 0;
    D_8010FDB8 = 0;
    D_8010FDBC[D_8010FDC0++] = D_8010FDB0[D_8010FDB8++];
    D_8010FDBC[D_8010FDC0++] = D_8010FDB0[D_8010FDB8++];
    if ((u32)D_8010FDB8 < (u32)D_8010FDB4) {
        do {
            D_8010FDBC[D_8010FDC0++] = D_8010FDBC[D_8010FDC0 - 2] - D_8010FDB0[D_8010FDB8++];
            if ((u32)D_8010FDB8 < (u32)D_8010FDB4) {
                D_8010FDBC[D_8010FDC0++] = D_8010FDBC[D_8010FDC0 - 2] - D_8010FDB0[D_8010FDB8++];
            }
        } while ((u32)D_8010FDB8 < (u32)D_8010FDB4);
    }
    D_80110218 = D_8010FDB0;
    D_8010FDB0 = D_8010FDBC;
    D_8010FDBC = D_80110218;
    D_8010FDB4 = D_8010FDC0;
}


extern char D_800EE6D0[];
extern char D_800EE6D8[];
void func_8002AF20(char *, char *);

void lwFilterH(void) {
    func_8002AF20(D_800EE6D0, D_800EE6D8);
}

void func_80080688(u8 *arg0) {
    D_8010FDB8 = 0;
    D_8010FDC4 = 0;
    D_8010FDD8 = 0;
    for (D_8010FDA0 = 0; D_8010FDA0 < 0x100; D_8010FDA0++) {
        arg0[D_8010FDA0] = D_8010FDA0;
    }
    for (D_8010FDA0 = 0x100; D_8010FDA0 < 0x200; D_8010FDA0++) {
        arg0[D_8010FDA0] = 0x1FF - D_8010FDA0;
    }
    for (D_8010FDA0 = 0; D_8010FDA0 < 0x100; D_8010FDA0++) {
        for (D_8010FDA4 = 0; D_8010FDA4 < 4; D_8010FDA4++) {
            arg0[0x200 + (D_8010FDA0 * 4) + D_8010FDA4] = D_8010FDA0;
        }
    }
    for (D_8010FDA0 = 0x600; D_8010FDA0 < 0x1000; D_8010FDA0++) {
        arg0[D_8010FDA0] = D_8010FDA0 & 0xFF;
    }
}

extern s32 D_8010FDA0;
extern u8 *D_8010FDB0;
extern u32 D_8010FDB4;
extern u32 D_8010FDB8;
extern u8 *D_8010FDBC;
extern s32 D_8010FDC0;
extern s32 D_8010FDC4;
extern u16 D_8010FDDC;
extern u8 D_8010FDF1;
extern u8 *D_80110218;

void lwFilterS(void) {
    u8 window[0x1000];

    D_8010FDC0 = 0;
    D_8010FDB8 = 0;
    func_80080688(window);
    while (D_8010FDB8 < D_8010FDB4) {
        D_8010FDF1 = D_8010FDB0[D_8010FDB8++];
        if (!(D_8010FDF1 & 0xF0)) {
            D_8010FDF1++;
            while (D_8010FDF1) {
                D_8010FDBC[D_8010FDC0++] = window[D_8010FDC4++] = D_8010FDB0[D_8010FDB8++];
                D_8010FDC4 &= 0xFFF;
                D_8010FDF1--;
            }
        } else {
            D_8010FDA0 = (D_8010FDF1 >> 4) + 2;
            D_8010FDDC = D_8010FDB0[D_8010FDB8++] + ((D_8010FDF1 & 0xF) << 8);
            while (D_8010FDA0) {
                D_8010FDBC[D_8010FDC0++] = window[D_8010FDC4++] = window[D_8010FDDC++];
                D_8010FDC4 &= 0xFFF;
                D_8010FDDC &= 0xFFF;
                D_8010FDA0--;
            }
        }
    }
    D_80110218 = D_8010FDB0;
    D_8010FDB0 = D_8010FDBC;
    D_8010FDBC = D_80110218;
    D_8010FDB4 = D_8010FDC0;
}


extern u8 D_8010FD9A;
extern s32 D_8010FDA0;
extern s32 D_8010FDA4;
extern u8 *D_8010FDB0;
extern u32 D_8010FDB4;
extern u32 D_8010FDB8;
extern u8 *D_8010FDBC;
extern s32 D_8010FDC0;
extern u8 *D_80110218;

void lwFilterR(void) {
    D_8010FDC0 = 0;
    D_8010FDA4 = 0;
    D_8010FDA0 = 0;
    D_8010FDB8 = 0;
    while (D_8010FDB8 < D_8010FDB4) {
        D_8010FDA0 = (D_8010FDB0[D_8010FDB8] << 8) + (D_8010FDB8 + D_8010FDB0)[1];
        D_8010FDB8 += 2;
        if (!(D_8010FDA0 & 0x8000)) {
            while (D_8010FDA0--) {
                D_8010FDBC[D_8010FDC0++] = D_8010FDB0[D_8010FDB8++];
            }
        } else {
            D_8010FDA0 &= 0x7FFF;
            D_8010FD9A = D_8010FDB0[D_8010FDB8++];
            while (D_8010FDA0--) {
                D_8010FDBC[D_8010FDC0++] = D_8010FD9A;
            }
        }
    }
    D_80110218 = D_8010FDB0;
    D_8010FDB0 = D_8010FDBC;
    D_8010FDBC = D_80110218;
    D_8010FDB4 = D_8010FDC0;
}


extern s32 D_800E28F0[];
extern s32 D_800E2930[];

typedef struct {
    s16 unk0;
    u8 unk2;
} AdpcmState;

void func_80080D54(s8 *arg0, s16 *arg1, s32 arg2, AdpcmState *arg3) {
    s8 *sp2C;
    s16 *sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_a2;

    sp28 = arg1;
    sp2C = arg0;
    sp18 = (s32) arg3->unk0;
    sp10 = (s32) arg3->unk2;
    sp1C = D_800E2930[sp10];
    sp8 = 0;
    arg2 = arg2 * 2;
    if (arg2 > 0) {
        do {
            if (sp8 != 0) {
                sp20 = spC & 0xF;
            } else {
                spC = *sp2C++;
                sp20 = (spC >> 4) & 0xF;
            }
            sp8 = !sp8;
            sp10 += D_800E28F0[sp20];
            if (sp10 < 0) {
                sp10 = 0;
            } else if (sp10 >= 0x59) {
                sp10 = 0x58;
            }
            sp24 = sp20 & 8;
            sp20 &= 7;
            sp14 = 0;
            if (sp20 & 4) {
                sp14 = sp1C * 4;
            }
            if (sp20 & 2) {
                sp14 += sp1C * 2;
            }
            if (sp20 & 1) {
                sp14 += sp1C;
            }
            sp14 = sp14 >> 2;
            if (sp24 != 0) {
                sp18 -= sp14;
            } else {
                sp18 += sp14;
            }
            if (sp18 >= 0x8000) {
                sp18 = 0x7FFF;
            } else if (sp18 < -0x8000) {
                sp18 = -0x8000;
            }
            sp1C = D_800E2930[sp10];
            *sp28 = (s16) sp18;
            sp28 += 1;
            arg2 -= 1;
        } while (arg2 > 0);
    }
    arg3->unk0 = (s16) sp18;
    arg3->unk2 = (u8) sp10;
}


extern s32 D_8010FDA0;
extern s32 D_8010FDA4;
extern u8 *D_8010FDAC;
extern u8 *D_8010FDB0;
extern u32 D_8010FDB4;
extern u32 D_8010FDB8;
extern u8 *D_8010FDBC;
extern s32 D_8010FDC0;
extern u8 *D_80110218;

void lwCopy(u8 *arg0, u8 *arg1, s32 arg2);
void func_80080D54(s8 *arg0, s16 *arg1, s32 arg2, AdpcmState *arg3);

void lwFilterA(void) {
    AdpcmState sp9E4;
    s8 sp7F0[0x1F4];
    s16 sp20[0x3E8];
    u8 sp1F;
    u8 sp1E;

    D_8010FDB8 = 0;
    D_8010FDC0 = 0;
    while (D_8010FDB8 < D_8010FDB4) {
        D_8010FDA4 = D_8010FDB8 + 0x1F4;
        if ((u32) D_8010FDA4 > D_8010FDB4) {
            D_8010FDA4 = D_8010FDB4;
        }
        D_8010FDA4 -= D_8010FDB8;
        lwCopy((u8 *) sp7F0, D_8010FDB0 + D_8010FDB8, D_8010FDA4);
        D_8010FDB8 += D_8010FDA4;
        func_80080D54(sp7F0, sp20, D_8010FDA4, &sp9E4);
        D_8010FDAC = (u8 *) sp20;
        for (D_8010FDA0 = 0; D_8010FDA0 < 0x3E8; D_8010FDA0++) {
            sp1F = *(D_8010FDA0 * 2 + D_8010FDAC);
            sp1E = *(D_8010FDA0 * 2 + D_8010FDAC + 1);
            *(D_8010FDAC + D_8010FDA0 * 2) = sp1E;
            *(D_8010FDAC + D_8010FDA0 * 2 + 1) = sp1F;
        }
        lwCopy(D_8010FDBC + D_8010FDC0, (u8 *) sp20, D_8010FDA4 * 4);
        D_8010FDC0 += D_8010FDA4 * 4;
    }
    D_80110218 = D_8010FDB0;
    D_8010FDB0 = D_8010FDBC;
    D_8010FDBC = D_80110218;
    D_8010FDB4 = D_8010FDC0;
}


s32 lwUnLz(u8 *arg0, u16 *arg1, s32 arg2)
{
  s32 spC;
  s32 sp8;
  s32 sp4;
  s32 sp0;
  sp0 = 0;
  spC = 0;
  if (spC < arg2)
  {
    do
    {
      sp8 = arg0[spC];
 do { } while (0);
      spC += 1;
      if (sp8 & 0x80)
      {
        sp8 = (sp8 & 0x7F) + 1;
        sp4 = (arg0[spC] << 8) | arg0[spC + 1];
        spC += 2;
        if (sp8 != 0)
        {
          do
          {
            arg1[sp0] = arg1[sp4];
            sp0 += 1;
            sp4 += 1;
            sp8 -= 1;
          }
          while (sp8 != 0);
        }
      }
      else
      {
        sp8 += 1;
        if (sp8 != 0)
        {
          do
          {
            arg1[sp0] = (arg0[spC] << 8) | arg0[spC + 1];
            sp0 += 1;
            spC += 2;
            sp8 -= 1;
          }
          while (sp8 != 0);
        }
      }
    }
    while (spC < arg2);
  }
  return sp0 * 2;
}


s32 lwFilterJ(u8 *arg0, s32 arg1, s32 arg2)
{
  s32 sp24;
  s32 sp20;
  s32 sp1C;
  sp1C = 0;
  if (arg2 != 0)
  {
    do
    {
      sp24 = (((arg0[4] << 0x18) | (arg0[5] << 0x10)) | (arg0[6] << 8)) | arg0[7];
      sp20 = (((arg0[8] << 0x18) | (arg0[9] << 0x10)) | (arg0[0xA] << 8)) | arg0[0xB];
      arg0 += 0xC;
      arg2 -= 0xC;
      sp20 = sp20;
      if (sp24 == sp20)
      {
        lwCopy(arg1, arg0, sp20);
      }
      else
      {
        lwUnLz(arg0, arg1, sp20);
      }
      arg1 += ((sp24 + 1) / 2) * 2;
      arg0 += sp20;
      arg2 -= sp20;
      sp1C += sp24;
    }
    while (arg2 != 0);
  }
  return sp1C;
}


s32 func_800815D0(u8 arg0) {
    s32 val;

    val = 0;
    while (arg0--) {
        if (D_800E2A9C == 0) {
            D_800E2A98 = D_8010FDB0[D_8010FDB8++];
            D_800E2A9C = 8;
        }
        val <<= 1;
        val |= D_800E2A98 >> 7;
        D_800E2A98 <<= 1;
        D_800E2A9C--;
    }
    return val;
}

s32 func_800815D0(u8);

void func_800816BC(s16 *arg0, s16 *arg1, s32 arg2, u16 arg3, u16 arg4) {
    s32 v;
    s32 i;
    for (i = 0; i < arg2; i++) {
        v = func_800815D0(arg4);
        arg1[i] = arg0[i] + v - arg3;
    }
}

extern s32 D_8010FD90;
extern s32 D_8010FD94;
extern u8 *D_8010FDBC;
extern s32 D_8010FDC0;

void func_80081754(s16 arg0) {
    if (D_8010FD94 != 0) {
        if (D_8010FD90 == 0) {
            arg0 += 0x8000;
        }
        D_8010FDBC[D_8010FDC0] = arg0 >> 8;
        D_8010FDC0 += 1;
        D_8010FDBC[D_8010FDC0] = arg0 & 0xFF;
        D_8010FDC0 += 1;
    } else {
        if (D_8010FD90 == 0) {
            arg0 += 0x80;
        }
        D_8010FDBC[D_8010FDC0++] = arg0;
    }
}


extern u8 D_8010FC10[];
extern u8 D_8010FD98;
extern u8 D_8010FD99;

s32 func_800815D0(u8);
void func_800816BC(s16 *, s16 *, s32, u16, u16);

void func_80081864(s32 arg0, s32 *arg1) {
    s32 i;
    s16 *ptr;
    s32 unused;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;

    i = 0;
    do {
        ptr = (s16 *)&D_8010FC10[i * 2 + 0x80];
        if ((i + arg0) >= 0x81) {
            arg0 = 0x80 - i;
        }
        if (func_800815D0(1) != 0) {
            if (func_800815D0(1) != 0) {
                sp30 = *arg1;
            } else {
                sp30 = func_800815D0(6) + 1;
            }
            sp2C = func_800815D0(D_8010FD99);
            sp28 = func_800815D0(sp2C);
            func_800816BC(ptr - sp30, ptr, arg0, sp28, sp2C);
            *arg1 = sp30;
        } else {
            for (sp24 = 0; sp24 < arg0; sp24++) {
                ptr[sp24] = func_800815D0(D_8010FD98);
            }
        }
    } while ((i += arg0) < 0x80);
}


extern u8 D_8010FC10[];
extern s16 D_8010FC90[];
extern s32 D_8010FD90;
extern s32 D_8010FD94;
extern u8 D_8010FD98;
extern u8 D_8010FD99;
extern u8 *D_8010FDB0;
extern u32 D_8010FDB4;
extern u32 D_8010FDB8;
extern u8 *D_8010FDBC;
extern s32 D_8010FDC0;
extern u8 *D_80110218;

void func_80080280(u8 *, s32, s32);
void lwCopy(u8 *, u8 *, s32);
s32 func_800815D0(u8);
void func_80081754(s16);
void func_80081864(s32, s32 *);

void lwFilterW(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    sp20 = 0;
    D_8010FDC0 = 0;
    D_8010FDB8 = 0;
    func_80080280(D_8010FC10, 0, 0x180);
    if (func_800815D0(8) != 0x42) {
        return;
    }
    sp24 = func_800815D0(0x18);
    D_8010FD94 = func_800815D0(1);
    D_8010FD90 = func_800815D0(1);
    if (D_8010FD94 != 0) {
        D_8010FD98 = 0x10;
    } else {
        D_8010FD98 = 8;
    }
    if (D_8010FD94 != 0) {
        D_8010FD99 = 4;
    } else {
        D_8010FD99 = 3;
    }
    for (sp28 = 0; sp28 < sp24; sp28 += 0x80) {
        lwCopy(D_8010FC10, D_8010FC10 + 0x100, 0x80);
        sp1C = func_800815D0(6) + 4;
        func_80081864(sp1C, &sp20);
        if ((sp28 + 0x80) < sp24) {
            sp18 = 0x80;
        } else {
            sp18 = sp24 - sp28;
        }
        for (sp2C = 0; sp2C < sp18; sp2C += 1) {
            func_80081754(D_8010FC90[sp2C]);
        }
    }
    D_80110218 = D_8010FDB0;
    D_8010FDB0 = D_8010FDBC;
    D_8010FDBC = D_80110218;
    D_8010FDB4 = D_8010FDC0;
}


extern u8 D_800E2A94;
extern u8 D_8010FDE0[];
extern u8 D_8010FDF0;

s32 lwDecode(u8 *arg0, u8 *arg1) {
    D_8010FDB0 = arg0;
    D_8010FDBC = arg1;
    D_800E2A94 = *D_8010FDB0;
    lwCopy(D_8010FDE0, D_8010FDB0 + 1, D_800E2A94);
    D_8010FDB4 = (D_8010FDB0[D_800E2A94 + 1] << 24) +
                 (D_8010FDB0[D_800E2A94 + 2] << 16) +
                 (D_8010FDB0[D_800E2A94 + 3] << 8) +
                  D_8010FDB0[D_800E2A94 + 4];
    lwCopy(D_8010FDB0, D_8010FDB0 + D_800E2A94 + 5, D_8010FDB4);
    D_8010FDF0 = 0;
    while (D_800E2A94--) {
        switch (D_8010FDE0[D_8010FDF0++]) {
        case 'D':
            lwFilterD();
            break;
        case 'F':
            lwFilterF();
            break;
        case 'H':
            lwFilterH();
            break;
        case 'S':
            lwFilterS();
            break;
        case 'J':
            D_8010FDC0 = lwFilterJ(D_8010FDB0, D_8010FDBC, D_8010FDB4);
            D_8010FDB4 = D_8010FDC0;
            D_80110218 = D_8010FDB0;
            D_8010FDB0 = D_8010FDBC;
            D_8010FDBC = D_80110218;
            break;
        case 'R':
            lwFilterR();
            break;
        case 'A':
            lwFilterA();
            break;
        case 'W':
            lwFilterW();
            break;
        }
    }
    if (D_8010FDB0 == arg0) {
        lwCopy(D_8010FDBC, D_8010FDB0, D_8010FDB4);
    }
    return D_8010FDB4;
}

