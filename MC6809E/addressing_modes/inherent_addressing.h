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
        InherentAddressing(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~InherentAddressing() noexcept = default;

        const memory::Byte  get_addressed_byte() const override;
        const memory::Word  get_addressed_word() const override;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;
    };

}