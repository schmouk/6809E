#pragma once

#include <cstdint>

#include "./offset_indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Accumulator A Offset Indexed Addressing   =========
    class AccAOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        inline AccAOffsetIndexedAddressing(archi::HWArchitecture& hw_arch_);

        virtual ~AccAOffsetIndexedAddressing() noexcept = default;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset() const override;

    };

    //---------------------------------------------------------
    using AccAOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<AccAOffsetIndexedAddressing>;


    //=====   Accumulator B Offset Indexed Addressing   =========
    class AccBOffsetIndexedAddressing : public AccAOffsetIndexedAddressing
    {
    public:
        inline AccBOffsetIndexedAddressing(archi::HWArchitecture& hw_arch_);

        virtual ~AccBOffsetIndexedAddressing() noexcept = default;

    protected:
        virtual const memory::Offset _evaluate_offset() const override;

    };

    //---------------------------------------------------------
    using AccBOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<AccBOffsetIndexedAddressing>;


    //=====   Accumulator D Offset Indexed Addressing   =========
    class AccDOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        inline AccDOffsetIndexedAddressing(archi::HWArchitecture& hw_arch_);

        virtual ~AccDOffsetIndexedAddressing() noexcept = default;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset() const override;

    };

    //---------------------------------------------------------
    using AccDOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<AccDOffsetIndexedAddressing>;

}
