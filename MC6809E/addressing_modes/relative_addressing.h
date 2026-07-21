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
        OffsetRelativeAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~OffsetRelativeAddressing() noexcept = default;

        virtual const memory::Offset get_offset() const = 0;
    };


    //=====   Short Relative Branching   ======================
    struct ShortRelativeAddressing : public OffsetRelativeAddressing
    {
        ShortRelativeAddressing(archi::HWArchitecture& hw_arch);
        virtual ~ShortRelativeAddressing() noexcept = default;

        const memory::Offset get_offset() const override;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;
    };


    //=====    Long Relative Branching   ======================
    struct LongRelativeAddressing : public OffsetRelativeAddressing
    {
        LongRelativeAddressing(archi::HWArchitecture& hw_arch);
        virtual ~LongRelativeAddressing() noexcept = default;

        const memory::Offset get_offset() const override;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;
    };

}
