#pragma once

#include <cstdint>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Inherent Addressing   ===========================
    struct InherentAddressing : public BaseAddressingMode
    {
        inline InherentAddressing(archi::HWArchitecture& hw_arch) noexcept;
        inline virtual ~InherentAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const override;
        virtual const memory::Word  get_addressed_word() const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

}