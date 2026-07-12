#include <cstdint>

#include "./constant_offset_addressing.h"
#include "./indexed_addressing.h"
#include "./offset_indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Constant 5-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant5bitsOffsetIndexedAddressing::Constant5bitsOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     post_byte
    )
        : OffsetIndexedAddressingMode(hw_arch, post_byte)
    {}

    //---------------------------------------------------------
    const std::uint64_t Constant5bitsOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t Constant5bitsOffsetIndexedAddressing::get_word_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const memory::Offset Constant5bitsOffsetIndexedAddressing::_evaluate_offset(
        [[maybe_unused]] archi::HWArchitecture& hw_arch,
        const memory::Byte                      post_byte
    )
    {
        memory::Offset ret_offset{ memory::Offset(post_byte & 0x0f) };
        if (post_byte & 0x10)
            // Negative offset!
            ret_offset -= 0x10;

        return ret_offset;
    }


    //=====   Constant 8-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant8bitsOffsetIndexedAddressing::Constant8bitsOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     post_byte
    )
        : OffsetIndexedAddressingMode(hw_arch, post_byte)
    {}

    //---------------------------------------------------------
    const std::uint64_t Constant8bitsOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t Constant8bitsOffsetIndexedAddressing::get_word_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const memory::Offset Constant8bitsOffsetIndexedAddressing::_evaluate_offset(
        archi::HWArchitecture&              hw_arch,
        [[maybe_unused]] const memory::Byte post_byte
    )
    {
        const memory::Byte offset_code{ hw_arch.load_next_byte() };

        memory::Offset ret_offset{ memory::Offset(offset_code & 0x7f) };
        if (offset_code & 0x80)  // Notice: signed offset, negative value
            ret_offset -= 0x80;
        
        return ret_offset;
    }


    //=====   Constant 16-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant16bitsOffsetIndexedAddressing::Constant16bitsOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     post_byte
    )
        : OffsetIndexedAddressingMode(hw_arch, post_byte)
    {}

    //---------------------------------------------------------
    const std::uint64_t Constant16bitsOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const std::uint64_t Constant16bitsOffsetIndexedAddressing::get_word_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const memory::Offset Constant16bitsOffsetIndexedAddressing::_evaluate_offset(
        archi::HWArchitecture&              hw_arch,
        [[maybe_unused]] const memory::Byte post_byte
    )
    {
        const memory::Word offset_code{ hw_arch.load_next_word() };

        memory::Offset ret_offset{ memory::Offset(offset_code & 0x7fff) };
        if (offset_code & 0x8000)  // Notice: signed offset, negative value
            ret_offset -= 0x8000;

        return ret_offset;
    }

}