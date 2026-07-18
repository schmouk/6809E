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
        archi::HWArchitecture& hw_arch;

        inline BaseAddressingMode() noexcept = default;
        inline BaseAddressingMode(archi::HWArchitecture& hw_arch_) noexcept;

        inline virtual ~BaseAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const = 0;
        virtual const memory::Word  get_addressed_word() const = 0;

        virtual inline const memory::Byte  get_addressed_byte(const memory::MemAddr addr);
        virtual inline const memory::Word  get_addressed_word(const memory::MemAddr addr);

        virtual void set_addressed_byte(const memory::Byte byte_value) = 0;
        virtual void set_addressed_word(const memory::Word word_value) = 0;

        inline void set_addressed_byte(const memory::MemAddr addr, const memory::Byte byte_value);
        inline void set_addressed_word(const memory::MemAddr addr, const memory::Word word_value);

        virtual const std::uint64_t get_byte_cycles() const = 0;
        virtual const std::uint64_t get_word_cycles() const = 0;
    };

}