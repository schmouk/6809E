#pragma once

#include <cstdint>
#include <initializer_list>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Register Addressing   ===========================
    class RegisterAddressing : public BaseAddressingMode
    {
    public:
        RegisterAddressing(archi::HWArchitecture& hw_arch_);
        virtual ~RegisterAddressing() noexcept = default;

        const memory::Byte  get_addressed_byte() const override;
        const memory::Word  get_addressed_word() const override;

        const std::uint64_t get_byte_cycles() const override;
        const std::uint64_t get_word_cycles() const override;

        std::initializer_list<cpu::EReg> evaluate_regs(const memory::Byte bytecode);


    private:
        static inline constexpr bool _is_8bits(const cpu::EReg reg_ndx) {
            return (memory::Byte(reg_ndx) & 0b1000) == 0b1000;
        }

        static inline constexpr bool _is_16bits(const cpu::EReg reg_ndx) {
            return (memory::Byte(reg_ndx) & 0b1000) == 0b0000;
        }

        static const cpu::EReg _get_reg_index(const memory::Byte reg_ndx);
    };

}
