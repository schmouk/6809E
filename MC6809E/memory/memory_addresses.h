#pragma once

#include <vector>

#include "./types.h"


namespace memory
{
    //=====   Specific Memeory Addresses   ====================
    constexpr MemAddr MEM_MIN_ADDR{ 0x0000 };
    constexpr MemAddr MEM_MAX_ADDR{ 0xffff };

    constexpr std::size_t MEM_MAX_SIZE{ 0x1'0000 };


    //=====   Memory Addresses Ranges   =======================
    //---------------------------------------------------------
    struct BaseMemAddrRange {};  // Notice: the base class for all memory address ranges


    //---------------------------------------------------------
    template<const MemAddr LOW_ADDR, const MemAddr HIGH_ADDR>
        requires (LOW_ADDR <= HIGH_ADDR)
    struct MemAddrRange : public BaseMemAddrRange
    {
        inline constexpr std::size_t size() const noexcept {
            return std::size_t(HIGH_ADDR - LOW_ADDR) + 1;
        };

    };

}