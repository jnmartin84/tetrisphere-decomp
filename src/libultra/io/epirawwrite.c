#include "PR/os_internal.h"
#include "PR/rcp.h"

s32 osEPiRawWriteIo(OSPiHandle *pihandle, u32 devAddr, u32 data) {
    register u32 stat;

    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }

    IO_WRITE(pihandle->baseAddress | devAddr, data);
    return 0;
}
