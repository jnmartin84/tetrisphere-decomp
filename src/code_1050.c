#include "common.h"

#include <PR/abi.h>
#include "synthInternals.h"

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} SubBuf;

typedef struct {
    /* 0x00 */ char pad0[0x1C];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ SubBuf *unk28;
    /* 0x2C */ char pad2C[0xC];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ char pad3C[0x8];
    /* 0x44 */ s32 unk44;
} AudioThing;

Acmd *func_80025CA0(AudioThing *arg0, s16 *arg1, s32 arg2, s32 arg3, Acmd *arg4) {
    Acmd *cmd;
    s32 v48;
    s32 v44;
    s32 v40;
    s32 v3C;
    s32 v38;
    s32 v34;
    s32 v30;
    s32 v2C;
    AudioThing *thing;
    AudioThing *dead;

    cmd = arg4;
    thing = arg0;
    dead = arg0;
    if ((arg0 == NULL) || (arg1 == NULL) || (arg2 == 0) || (arg4 == NULL)) {
        return cmd;
    }
    if (arg2 == 0) {
        return cmd;
    }
    if (((u32) (thing->unk38 + arg2) > (u32) thing->unk20) && (thing->unk24 != 0)) {
        v30 = thing->unk20 - thing->unk38;
        v48 = v30 * 2;
        if (v30 > 0) {
            v44 = thing->unk44 + 0x80000000;
            v40 = v44 & 7;
            v48 += v40;
            aSetBuffer(cmd++, 0, *arg1, 0, ((v48 - (v48 & 7)) + 8));
            aLoadBuffer(cmd++, v44 - v40);
        } else {
            v40 = 0;
        }
        *arg1 += v40;
        thing->unk44 = thing->unk28->unk0 + (thing->unk1C * 2);
        thing->unk38 = thing->unk1C;
        v2C = *arg1;
        if (v30 < arg2) {
            do {
                v2C += v30 * 2;
                arg2 -= v30;
                if ((thing->unk24 != -1) && (thing->unk24 != 0)) {
                    thing->unk24 = thing->unk24 - 1;
                }
                if ((u32) arg2 < (u32) (thing->unk20 - thing->unk1C)) {
                    v30 = arg2;
                } else {
                    v30 = thing->unk20 - thing->unk1C;
                }
                v48 = v30 * 2;
                v44 = thing->unk44 + 0x80000000;
                v40 = v44 & 7;
                v48 += v40;
                if (v2C & 7) {
                    v3C = 8 - (v2C & 7);
                } else {
                    v3C = 0;
                }
                aSetBuffer(cmd++, 0, v2C + v3C, 0, ((v48 - (v48 & 7)) + 8));
                aLoadBuffer(cmd++, v44 - v40);
                if ((v40 != 0) || (v3C != 0)) {
                    aDMEMMove(cmd++, v2C + v40 + v3C, v2C, v30 * 2);
                }
            } while (v30 < arg2);
        }
        thing->unk38 = thing->unk38 + arg2;
        thing->unk44 = thing->unk44 + (arg2 * 2);
        return cmd;
    }
    v48 = arg2 * 2;
    v38 = (thing->unk44 + v48) - (thing->unk28->unk0 + thing->unk28->unk4);
    if (v38 < 0) {
        v38 = 0;
    }
    if (v38 > v48) {
        v38 = v48;
    }
    if (v38 < v48) {
        if (arg2 > 0) {
            v48 -= v38;
            v44 = thing->unk44 + 0x80000000;
            v40 = v44 & 7;
            v48 += v40;
            aSetBuffer(cmd++, 0, *arg1, 0, ((v48 - (v48 & 7)) + 8));
            aLoadBuffer(cmd++, v44 - v40);
        } else {
            v40 = 0;
        }
        *arg1 += v40;
        thing->unk38 = thing->unk38 + arg2;
        thing->unk44 = thing->unk44 + (arg2 * 2);
    } else {
        thing->unk44 = thing->unk44 + (arg2 * 2);
    }
    if (v38 != 0) {
        v34 = (arg2 * 2) - v38;
        if (v34 < 0) {
            v34 = 0;
        }
        aClearBuffer(cmd++, *arg1 + v34, v38);
    }
    return cmd;
}


typedef struct {
    u8              pad00[0x1C];
    /* 0x1C */ u32   loopStart;
    /* 0x20 */ u32   loopEnd;
    /* 0x24 */ u32   loopCount;
    /* 0x28 */ Awords *table;
    /* 0x2C */ s32   bookSize;
    /* 0x30 */ s32 (*dma)(s32, s32, void *);
    /* 0x34 */ void *dmaState;
    /* 0x38 */ s32   sample;
    /* 0x3C */ s32   lastsam;
    /* 0x40 */ s32   first;
    /* 0x44 */ s32   memin;
} LoadFilter;

Acmd *func_80026370(void *arg0, s16 *arg1, s32 arg2, s32 arg3, Acmd *cmdBuf) {
    Acmd *p;
    s32 v68;
    s32 v64;
    s32 v60;
    s32 v5C;
    s32 v58;
    s32 v54;
    s32 v50;
    s32 v4C;
    s32 pad48;
    s32 pad44;
    LoadFilter *f;
    LoadFilter *dead;

    p = cmdBuf;
    f = arg0;
    dead = arg0;
    if (arg2 == 0) {
        return p;
    }
    if ((arg0 == NULL) || (arg1 == NULL) || (arg2 == 0) || (cmdBuf == NULL)) {
        return p;
    }
    if (((f->sample + arg2) > f->loopEnd) && (f->loopCount != 0)) {
        v50 = f->loopEnd - f->sample;
        v68 = v50 * 2;
        if (v50 > 0) {
            v64 = f->dma(f->memin, v68 >> 1, f->dmaState);
            v60 = v64 & 7;
            v68 += v60;
            aSetBuffer(p++, 0, *arg1, 0, (v68 - (v68 & 7)) + 8);
            aLoadBuffer(p++, v64 - v60);
        } else {
            v60 = 0;
        }
        *arg1 += v60;
        f->memin = f->table->w0 + f->loopStart;
        f->sample = f->loopStart;
        v4C = *arg1;
        while (arg2 > v50) {
            v4C += v50 * 2;
            arg2 -= v50;
            if ((f->loopCount != -1) && (f->loopCount != 0)) {
                f->loopCount = f->loopCount - 1;
            }
            v50 = (arg2 < f->loopEnd - f->loopStart) ? arg2 : (f->loopEnd - f->loopStart);
            v68 = v50 * 2;
            v64 = f->dma(f->memin, v68 >> 1, f->dmaState);
            v60 = v64 & 7;
            v68 += v60;
            if (v4C & 7) {
                v5C = 8 - (v4C & 7);
            } else {
                v5C = 0;
            }
            aSetBuffer(p++, 0, v4C + v5C, 0, (v68 - (v68 & 7)) + 8);
            aLoadBuffer(p++, v64 - v60);
            if ((v60 != 0) || (v5C != 0)) {
                aDMEMMove(p++, v4C + v60 + v5C, v4C, v50 * 2);
            }
        }
        f->sample += arg2;
        f->memin += arg2;
        return p;
    }
    v68 = arg2 * 2;
    v58 = (f->memin + v68) - (f->table->w0 + f->table->w1);
    if (v58 < 0) {
        v58 = 0;
    }
    if (v58 > v68) {
        v58 = v68;
    }
    if (v58 < v68) {
        if (arg2 > 0) {
            v68 -= v58;
            v64 = f->dma(f->memin, v68 >> 1, f->dmaState);
            v60 = v64 & 7;
            v68 += v60;
            aSetBuffer(p++, 0, *arg1, 0, (v68 - (v68 & 7)) + 8);
            aLoadBuffer(p++, v64 - v60);
        } else {
            v60 = 0;
        }
        *arg1 += v60;
        f->sample += arg2;
        f->memin += arg2;
    } else {
        f->memin += arg2;
    }
    if (v58 != 0) {
        v54 = (arg2 * 2) - v58;
        if (v54 < 0) {
            v54 = 0;
        }
        aClearBuffer(p++, *arg1 + v54, v58);
    }
    return p;
}


s32 alLoadParam(void *filter, s32 paramID, void *param) {
    ALLoadFilter *a = (ALLoadFilter *) filter;
    ALFilter *f = (ALFilter *) filter;

    switch (paramID) {
        case AL_FILTER_SET_WAVETABLE:
            a->table = (ALWaveTable *) param;
            a->memin = (s32) a->table->base;
            a->sample = 0;
            switch (a->table->type) {
                case AL_ADPCM_WAVE:
                    break;
                case AL_RAW16_WAVE:
                    f->handler = (ALCmdHandler) func_80025CA0;
                    if (a->table->waveInfo.adpcmWave.loop) {
                        a->loop.start = a->table->waveInfo.adpcmWave.loop->start;
                        a->loop.end = a->table->waveInfo.adpcmWave.loop->end;
                        a->loop.count = a->table->waveInfo.adpcmWave.loop->count;
                    } else {
                        a->loop.start = a->loop.end = a->loop.count = 0;
                    }
                    break;
                case AL_RAW16_WAVE + 1:
                    f->handler = (ALCmdHandler) func_80026370;
                    if (a->table->waveInfo.rawWave.loop) {
                        a->loop.start = a->table->waveInfo.rawWave.loop->start;
                        a->loop.end = a->table->waveInfo.rawWave.loop->end;
                        a->loop.count = a->table->waveInfo.rawWave.loop->count;
                    } else {
                        a->loop.start = a->loop.end = a->loop.count = 0;
                    }
                    break;
                default:
                    break;
            }
            break;

        case AL_FILTER_RESET:
            a->memin = (s32) a->table->base;
            a->lastsam = 0;
            a->first = 1;
            a->sample = 0;
            break;

        default:
            break;
    }
}

