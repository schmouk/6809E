#pragma once

#include <cstdint>

#include "./relative_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Program Counter Short Relative Addressing   =====
    struct ProgramCounterShortRelativeAddressing : public ShortRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr
        ) const override;

        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr
        ) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //=====   Program Counter Long Relative Addressing   ======
    struct ProgramCounterLongRelativeAddressing : public LongRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr
        ) const override;
        
        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr
        ) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

}