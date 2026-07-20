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

        BaseAddressingMode() noexcept = default;
        BaseAddressingMode(archi::HWArchitecture& hw_arch_) noexcept;

        virtual ~BaseAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const;
        virtual const memory::Word  get_addressed_word() const;

        virtual const memory::Byte  get_addressed_byte(const memory::MemAddr addr);
        virtual const memory::Word  get_addressed_word(const memory::MemAddr addr);

        virtual void set_addressed_byte(const memory::Byte byte_value);
        virtual void set_addressed_word(const memory::Word word_value);

        void set_addressed_byte(const memory::MemAddr addr, const memory::Byte byte_value);
        void set_addressed_word(const memory::MemAddr addr, const memory::Word word_value);

        virtual const std::uint64_t get_byte_cycles() const = 0;
        virtual const std::uint64_t get_word_cycles() const = 0;
    };

}