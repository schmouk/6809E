
#include <cstdint>
#include <initializer_list>

#include "./register_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Register Addressing   ===========================
    //---------------------------------------------------------
    const memory::Byte  RegisterAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::Byte reg_code{ hw_arch.get_byte(hw_arch.regPC()) };
        hw_arch.regPC++;

        return reg_code;
    }

    //---------------------------------------------------------
    const memory::Word  RegisterAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        throw except::InvalidAddressingModeException(
            "Word addressing is invalid for register addressing mode"
        );
    }

    //---------------------------------------------------------
    const std::uint64_t RegisterAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t RegisterAddressing::get_word_cycles() const
    {
        throw except::InvalidAddressingModeException(
            "Word addressing is invalid for register addressing mode"
        );
    }

    //---------------------------------------------------------
    std::initializer_list<cpu::EReg> RegisterAddressing::evaluate_regs(const memory::Byte bytecode)
    {
        const cpu::EReg src{ _get_reg_index(bytecode >> 4) };
        const cpu::EReg dst{ _get_reg_index(bytecode & 0x0f) };

        if (_is_8bits(src) == _is_16bits(dst))
            throw except::InvalidMixedRegisterAddressingModeException();

        return { src, dst };
    }

    //---------------------------------------------------------
    const cpu::EReg RegisterAddressing::_get_reg_index(const memory::Byte reg_ndx)
    {
        if (reg_ndx <= memory::Byte(cpu::EReg::PC))
            return cpu::EReg(reg_ndx);

        if (memory::Byte(cpu::EReg::A) <= reg_ndx && reg_ndx <= memory::Byte(cpu::EReg::DP))
            return cpu::EReg(reg_ndx);

        throw except::InvalidRegisterCodeAddressingModeException(reg_ndx);
    }

}