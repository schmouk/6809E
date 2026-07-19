#pragma once

#include <cstdint>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Direct Addressing   =============================
    struct DirectAddressing : public BaseAddressingMode
    {
        inline DirectAddressing(archi::HWArchitecture& hw_arch) noexcept;
        inline virtual ~DirectAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte();
        virtual const memory::Word  get_addressed_word();

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

}
