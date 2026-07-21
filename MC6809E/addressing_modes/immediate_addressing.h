#pragma once

#include <cstdint>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Immediate Addressing   ==========================
    struct ImmediateAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;
    };

}
