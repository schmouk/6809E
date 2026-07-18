#pragma once

#include <cstdint>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Extended Addressing   ===========================
    struct ExtendedAddressing : public BaseAddressingMode
    {
        inline ExtendedAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~ExtendedAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const override;
        virtual const memory::Word  get_addressed_word() const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Extended Indirect Addressing   ==================
    struct ExtendedIndirectAddressing : public BaseAddressingMode
    {
        inline ExtendedIndirectAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~ExtendedIndirectAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const override;
        virtual const memory::Word  get_addressed_word() const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

}
