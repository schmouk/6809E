#pragma once

#include <cstdint>

#include "./indexed_addressing.h"
#include "./offset_indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Constant 5-bits Offset Indexed Addressing   =====
    class Constant5bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        inline Constant5bitsOffsetIndexedAddressing(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        );

        virtual ~Constant5bitsOffsetIndexedAddressing() noexcept = default;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) override;
    };


    //=====   Constant 8-bits Offset Indexed Addressing   =====
    class Constant8bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        inline Constant8bitsOffsetIndexedAddressing(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        );

        virtual ~Constant8bitsOffsetIndexedAddressing() noexcept = default;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) override;
    };


    //=====   Constant 16-bits Offset Indexed Addressing   =====
    class Constant16bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        inline Constant16bitsOffsetIndexedAddressing(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        );

        virtual ~Constant16bitsOffsetIndexedAddressing() noexcept = default;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) override;
    };

}
