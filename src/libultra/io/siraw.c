#include "PR/os_internal.h"
#include "assert.h"
#include "PRinternal/siint.h"









































// Adjust line numbers to match assert
#if BUILD_VERSION < VERSION_J
#line 47
#endif

#define PIF_RAM_SIZE (PIF_RAM_END + 1 - PIF_RAM_START)

// TODO: this comes from a header
#ident "$Revision: 1.17 $"
s32 __osSiRawReadIo(u32 devAddr, u32* data) {
    assert((devAddr & 0x3) == 0);
    assert(data != NULL);
    
    if (__osSiDeviceBusy()) {
        return -1;
    }

    *data = IO_READ(devAddr);
    return 0;
}

s32 __osSiRawWriteIo(u32 devAddr, u32 data) {
    assert((devAddr & 0x3) == 0);

    if (__osSiDeviceBusy()) {
        return -1;
    }

    IO_WRITE(devAddr, data);
    return 0;
}
