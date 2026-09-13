#include <ultra64.h>

/* RDP/RSP render state initialization display list */

extern s16 D_800DFE98;

void func_800335F0(Gfx **gdl) {
    gDPPipeSync((*gdl)++);
    gDPSetCycleType((*gdl)++, G_CYC_1CYCLE);
    gSPTexture((*gdl)++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetAlphaCompare((*gdl)++, G_AC_THRESHOLD);
    gDPSetTexturePersp((*gdl)++, G_TP_NONE);
    gDPSetTextureFilter((*gdl)++, G_TF_AVERAGE);
    gDPSetTextureConvert((*gdl)++, G_TC_FILT);
    gDPSetTextureDetail((*gdl)++, G_TD_CLAMP);
    gDPSetTextureLOD((*gdl)++, G_TL_TILE);
    gSPClearGeometryMode((*gdl)++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gDPSetRenderMode((*gdl)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetBlendColor((*gdl)++, 0, 0, 0, 0);
    D_800DFE98 = -1;
}
