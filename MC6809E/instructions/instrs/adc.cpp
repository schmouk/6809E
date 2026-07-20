#include <cstdint>

#include "./adc.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   ADC Base Class   ================================
    //---------------------------------------------------------
    ADCBase::ADCBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte ADCBase::_evaluate(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ _evaluate_value(reg_value, mem_value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void ADCBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.clr();

        if (intermediate_value == 0) {
            _hw_arch.regCC.set_zero();
        }
        else {
            _hw_arch.regCC.set_carry(intermediate_value > 0xff);
            _hw_arch.regCC.set_overflow(intermediate_value < -128 || intermediate_value > 127);
            _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
        }
    }

    //---------------------------------------------------------
    const int ADCBase::_evaluate_value(const int reg_value, const int mem_value)
    {
        _hw_arch.regCC.set_halfcarry((reg_value & 0x0f) + (mem_value & 0x0f) + _hw_arch.regCC.carry_value() > 0x0f);
        return reg_value + mem_value + _hw_arch.regCC.carry_value();
    }


    //=====   ADCA   ==========================================
    //-----   ADCA Immediate   --------------------------------
    //---------------------------------------------------------
    ADCAImmediate::ADCAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0x89 }
    {}

    //---------------------------------------------------------
    void ADCAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ADCAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }
    

    //-----   ADCA Direct   -----------------------------------
    //---------------------------------------------------------
    ADCADirect::ADCADirect(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0x99 }
    {}

    //---------------------------------------------------------
    void ADCADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ADCADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   ADCA Indexed   ----------------------------------
    //---------------------------------------------------------
    ADCAIndexed::ADCAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0xA9 }
    {}

    //---------------------------------------------------------
    void ADCAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regA = _evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t ADCAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ADCA Extended   ---------------------------------
    //---------------------------------------------------------
    ADCAExtended::ADCAExtended(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0xB9 }
    {}

    //---------------------------------------------------------
    void ADCAExtended::exec()
    {
        memory::MemAddr value_addr { memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ADCAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   ADCB   ==========================================
    //-----   ADCB Immediate   --------------------------------
    //---------------------------------------------------------
    ADCBImmediate::ADCBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0xC9 }
    {}

    //---------------------------------------------------------
    void ADCBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ADCBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ADCB Direct   -----------------------------------
    //---------------------------------------------------------
    ADCBDirect::ADCBDirect(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0xD9 }
    {}

    //---------------------------------------------------------
    void ADCBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ADCBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   ADCB Indexed   ----------------------------------
    //---------------------------------------------------------
    ADCBIndexed::ADCBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0xE9 }
    {}

    //---------------------------------------------------------
    void ADCBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regB = _evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t ADCBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ADCB Extended   ---------------------------------
    //---------------------------------------------------------
    ADCBExtended::ADCBExtended(archi::HWArchitecture& hw_arch) noexcept
        : ADCBase{ hw_arch, 0xF9 }
    {}

    //---------------------------------------------------------
    void ADCBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ADCBExtended::get_cycles_count() noexcept
    {
        return 5;
    }

}
