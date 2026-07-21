#pragma once

#include <cstdint>

#include "./offset_indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Zero-Offset Indexed Addressing   ================
    struct ZeroOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        ZeroOffsetIndexedAddressing(archi::HWArchitecture& hw_arch_) noexcept;

        virtual ~ZeroOffsetIndexedAddressing() noexcept = default;
    };

    //---------------------------------------------------------
    using ZeroOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<ZeroOffsetIndexedAddressing>;


    //=====   Constant 5-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    class Constant5bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        Constant5bitsOffsetIndexedAddressing(archi::HWArchitecture& hw_arch_);

        virtual ~Constant5bitsOffsetIndexedAddressing() noexcept = default;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;

    protected:
        const memory::Offset _evaluate_offset() const override;
    };

    //---------------------------------------------------------
    // Notice: next addressing mode is not valid w. MC6809E
    //using Constant5bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant5bitsOffsetIndexedAddressing>;


    //=====   Constant 8-bits Offset Indexed Addressing   =====
    class Constant8bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        Constant8bitsOffsetIndexedAddressing(archi::HWArchitecture& hw_arch_);

        virtual ~Constant8bitsOffsetIndexedAddressing() noexcept = default;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;

    protected:
        const memory::Offset _evaluate_offset() const override;
    };

    //---------------------------------------------------------
    using Constant8bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant8bitsOffsetIndexedAddressing>;


    //=====   Constant 16-bits Offset Indexed Addressing   =====
    class Constant16bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        Constant16bitsOffsetIndexedAddressing(archi::HWArchitecture& hw_arch_);

        virtual ~Constant16bitsOffsetIndexedAddressing() noexcept = default;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;

    protected:
        const memory::Offset _evaluate_offset() const override;
    };

    //---------------------------------------------------------
    using Constant16bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant16bitsOffsetIndexedAddressing>;

}
