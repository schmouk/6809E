#pragma once

#include "./types.h"

namespace memory
{
    //=====   Specific Memeory Addresses   ====================
    constexpr MemAddr MIN_MEM_ADDR{ 0x0000 };
    constexpr MemAddr MAX_MEM_ADDR{ 0xffff };


    //=====   Memory Addresses Ranges   =======================
    struct MemAddrRange
    {
        MemAddr low_addr{ MIN_MEM_ADDR };
        MemAddr highAddr{ MAX_MEM_ADDR };
    };

}