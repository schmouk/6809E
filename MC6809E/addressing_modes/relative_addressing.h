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
        inline OffsetRelativeAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~OffsetRelativeAddressing() noexcept = default;

        virtual const memory::Offset get_offset() const = 0;
    };


    //=====   Short Relative Branching   ======================
    struct ShortRelativeAddressing : public OffsetRelativeAddressing
    {
        inline ShortRelativeAddressing(archi::HWArchitecture& hw_arch);
        virtual ~ShortRelativeAddressing() noexcept = default;

        virtual const memory::Offset get_offset() const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====    Long Relative Branching   ======================
    struct LongRelativeAddressing : public OffsetRelativeAddressing
    {
        inline LongRelativeAddressing(archi::HWArchitecture& hw_arch);
        virtual ~LongRelativeAddressing() noexcept = default;

        virtual const memory::Offset get_offset() const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

}
