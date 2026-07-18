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
        inline ProgramCounterShortRelativeAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~ProgramCounterShortRelativeAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const override;
        virtual const memory::Word  get_addressed_word() const override;

        virtual void set_addressed_byte(const memory::Byte byte_value) override;
        virtual void set_addressed_word(const memory::Word word_value) override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //=====   Program Counter Long Relative Addressing   ======
    struct ProgramCounterLongRelativeAddressing : public LongRelativeAddressing
    {
        inline ProgramCounterLongRelativeAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~ProgramCounterLongRelativeAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const override;       
        virtual const memory::Word  get_addressed_word() const override;

        virtual void set_addressed_byte(const memory::Byte byte_value) override;
        virtual void set_addressed_word(const memory::Word word_value) override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

}