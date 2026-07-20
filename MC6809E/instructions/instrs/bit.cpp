#include <cstdint>

#include "./bit.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   BIT Base Class   ================================
    //---------------------------------------------------------
    BITBase::BITBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte BITBase::_evaluate(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ _evaluate_value(reg_value, mem_value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void BITBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
        _hw_arch.regCC.set_zero(intermediate_value != 0);
        _hw_arch.regCC.clr_overflow();
    }

    //---------------------------------------------------------
    const int BITBase::_evaluate_value(const int reg_value, const int mem_value)
    {
        return reg_value & mem_value;
    }


    //=====   BITA   ==========================================
    //-----   BITA Immediate   --------------------------------
    //---------------------------------------------------------
    BITAImmediate::BITAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0x85 }
    {
    }

    //---------------------------------------------------------
    void BITAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t BITAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   BITA Direct   -----------------------------------
    //---------------------------------------------------------
    BITADirect::BITADirect(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0x95 }
    {
    }

    //---------------------------------------------------------
    void BITADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t BITADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   BITA Indexed   ----------------------------------
    //---------------------------------------------------------
    BITAIndexed::BITAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0xA5 }
    {
    }

    //---------------------------------------------------------
    void BITAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regA = _evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t BITAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   BITA Extended   ---------------------------------
    //---------------------------------------------------------
    BITAExtended::BITAExtended(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0xB5 }
    {
    }

    //---------------------------------------------------------
    void BITAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t BITAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   BITB   ==========================================
    //-----   BITB Immediate   --------------------------------
    //---------------------------------------------------------
    BITBImmediate::BITBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0xC5 }
    {
    }

    //---------------------------------------------------------
    void BITBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t BITBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   BITB Direct   -----------------------------------
    //---------------------------------------------------------
    BITBDirect::BITBDirect(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0xD5 }
    {
    }

    //---------------------------------------------------------
    void BITBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t BITBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   BITB Indexed   ----------------------------------
    //---------------------------------------------------------
    BITBIndexed::BITBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0xE5 }
    {
    }

    //---------------------------------------------------------
    void BITBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regB = _evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t BITBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   BITB Extended   ---------------------------------
    //---------------------------------------------------------
    BITBExtended::BITBExtended(archi::HWArchitecture& hw_arch) noexcept
        : BITBase{ hw_arch, 0xF5 }
    {
    }

    //---------------------------------------------------------
    void BITBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t BITBExtended::get_cycles_count() noexcept
    {
        return 5;
    }

}
