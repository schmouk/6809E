#pragma once

#include <cstdint>

#include "./indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Offset Indexed Addressing   =====================
    // The base class for all offset indexed addressing modes.
    class OffsetIndexedAddressingMode : public IndexedAddressingMode
    {
    public:
        inline OffsetIndexedAddressingMode(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) noexcept;

        virtual ~OffsetIndexedAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch
        ) const;

        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch
        ) const;

        virtual void set_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     byte_value
        );

        virtual void set_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::Word     word_value
        );

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        memory::Offset _offset{ 0 };

        virtual const memory::Offset _evaluate_offset(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) = 0;

    };

}
