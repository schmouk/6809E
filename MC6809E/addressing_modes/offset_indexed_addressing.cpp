#include <cstdint>

#include "./indexed_addressing.h"
#include "./offset_indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    OffsetIndexedAddressingMode::OffsetIndexedAddressingMode(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     post_byte
    ) noexcept
        : IndexedAddressingMode(hw_arch, post_byte)
    {
        _evaluate_offset(hw_arch, post_byte);
    }

    //---------------------------------------------------------
    const std::uint64_t OffsetIndexedAddressingMode::get_byte_cycles() const
    {
        return 0;
    }

    //---------------------------------------------------------
    const std::uint64_t OffsetIndexedAddressingMode::get_word_cycles() const
    {
        return 0;
    }

}
