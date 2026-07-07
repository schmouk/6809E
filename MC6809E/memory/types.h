#pragma once

#include <cstdint>


/**
* This file declares the basic types related to memory management
*/

namespace memory
{
    using MemAddr = std::uint16_t;  // Memory addressing bus is 16-bits wide

    using Byte    = std::uint8_t;   // The base type for  8-bits content data
    using Word    = std::uint16_t;  // The base type for 16-bits content data

    using Offset  = std::int16_t;   // The type for 16-bits offsets
    using Offset8 = std::int8_t;    // The shorter type for 8-bits offsets

}