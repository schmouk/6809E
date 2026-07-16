#pragma once

#include <cstdint>

#include "../architecture/hw_architecture.h"
//#include "../cpu/cpu_registers.h"
#include "../memory/types.h"

namespace addr
{
    //=====   Base Addressing Class   =========================
    struct BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch
        ) const = 0;

        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch
        ) const = 0;

        virtual inline const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr
        ) const;

        virtual inline const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr
        ) const;

        virtual void set_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     byte_value
        ) = 0;

        virtual void set_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::Word     word_value
        ) = 0;

        inline void set_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr,
            const memory::Byte     byte_value
        );

        inline void set_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::MemAddr  addr,
            const memory::Word     word_value
        );

        virtual const std::uint64_t get_byte_cycles() const = 0;
        virtual const std::uint64_t get_word_cycles() const = 0;
    };

}