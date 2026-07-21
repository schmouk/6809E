#pragma once

#include <cstdint>

#include "./offset_indexed_addressing.h"
#include "./relative_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Program Counter Short Relative Addressing   =====
    //---------------------------------------------------------
    struct ProgramCounterShortRelativeAddressing : public ShortRelativeAddressing
    {
        ProgramCounterShortRelativeAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~ProgramCounterShortRelativeAddressing() noexcept = default;

        const memory::Byte  get_addressed_byte() const override;
        const memory::Word  get_addressed_word() const override;

        void set_addressed_byte(const memory::Byte byte_value) override;
        void set_addressed_word(const memory::Word word_value) override;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    using ProgramCounterShortRelativeIndirectAddressing =
        OffsetIndirectIndexedAddressingModeT<ProgramCounterShortRelativeAddressing>;


    //=====   Program Counter Long Relative Addressing   ======
    struct ProgramCounterLongRelativeAddressing : public LongRelativeAddressing
    {
        ProgramCounterLongRelativeAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~ProgramCounterLongRelativeAddressing() noexcept = default;

        const memory::Byte  get_addressed_byte() const override;       
        const memory::Word  get_addressed_word() const override;

        void set_addressed_byte(const memory::Byte byte_value) override;
        void set_addressed_word(const memory::Word word_value) override;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    using ProgramCounterLongRelativeIndirectAddressing =
        OffsetIndirectIndexedAddressingModeT<ProgramCounterLongRelativeAddressing>;

}