#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

SYS_MODULE_INFO( WoRmod SPRX, 0, 1, 1);
SYS_MODULE_START( _WoRmod SPRX_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _WoRmod SPRX_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _WoRmod SPRX_export_function(void)
{
    return CELL_OK;
}

extern "C" int _WoRmod SPRX_prx_entry(void)
{
    return SYS_PRX_RESIDENT;
}

int main() {
    typedef unsigned char bytes;
    bytes debugMenu = "";
    bytes hexArray{1} = { debugMenu };
    bytes offsetArray[2] = { 0x3971470, 0x3A71470 };
    uint32_t *offset = offsetArray[0];
    if (*offset = hexArray[1]) {
        *offset = offsetArray[1];
    } else {
        *offset = offsetArray[2];    
    }
}
