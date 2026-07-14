#pragma once

#include <cstdint>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Offsets Relative Addressing Base Class   ========
    struct OffsetRelativeAddressing : public BaseAddressingMode
    {
        virtual const memory::Offset get_offset(archi::HWArchitecture& hw_arch) const = 0;
    };


    //=====   Short Relative Branching   ======================
    struct ShortRelativeAddressing : public OffsetRelativeAddressing
    {
        virtual const memory::Offset get_offset(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====    Long Relative Branching   ======================
    struct LongRelativeAddressing : public OffsetRelativeAddressing
    {
        virtual const memory::Offset get_offset(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

}
