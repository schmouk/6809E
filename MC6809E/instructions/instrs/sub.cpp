#include <cstdint>

#include "./sub.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   SUB Base Class   ================================
    //---------------------------------------------------------
    SUBBase::SUBBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte SUBBase::_evaluate(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ _evaluate_value(reg_value, mem_value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    const memory::Word SUBBase::_evaluate_16(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ _evaluate_value(reg_value, mem_value, 0x8000) };
        _evaluate_cc_flags(intermediate_value, 0x8000);
        return memory::Word(intermediate_value & 0xffff);
    }

    //---------------------------------------------------------
    void SUBBase::_evaluate_cc_flags(const int intermediate_value, const int bit_mask)
    {
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.set_negative((intermediate_value & bit_mask) != 0);
    }

    //---------------------------------------------------------
    const int SUBBase::_evaluate_value(const int reg_value, const int mem_value, const int bit_mask)
    {
        const int res_value{ reg_value - mem_value };

        _hw_arch.regCC.set_carry(res_value < 0);

        const bool reg7{ (reg_value & bit_mask) != 0 };
        const bool mem7{ (mem_value & bit_mask) != 0 };
        const bool res7{ (res_value & bit_mask) != 0 };
        _hw_arch.regCC.set_overflow(
            (reg7 && !mem7 && !res7) || (!reg7 && mem7 && res7)
        );

        return res_value;
    }


    //=====   SUBA   ==========================================
    //-----   SUBA Immediate   --------------------------------
    //---------------------------------------------------------
    SUBAImmediate::SUBAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0x80 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.set_regA(_evaluate(_hw_arch.regA, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   SUBA Direct   -----------------------------------
    //---------------------------------------------------------
    SUBADirect::SUBADirect(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0x90 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.set_regA(_evaluate(_hw_arch.regA, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   SUBA Indexed   ----------------------------------
    //---------------------------------------------------------
    SUBAIndexed::SUBAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xA0 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.set_regA(_evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte()));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   SUBA Extended   ---------------------------------
    //---------------------------------------------------------
    SUBAExtended::SUBAExtended(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xB0 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.set_regA(_evaluate(_hw_arch.regA, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   SUBB   ==========================================
    //-----   SUBB Immediate   --------------------------------
    //---------------------------------------------------------
    SUBBImmediate::SUBBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xC0 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.set_regB(_evaluate(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   SUBB Direct   -----------------------------------
    //---------------------------------------------------------
    SUBBDirect::SUBBDirect(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xD0 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.set_regB(_evaluate(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   SUBB Indexed   ----------------------------------
    //---------------------------------------------------------
    SUBBIndexed::SUBBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xE0 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.set_regB(_evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte()));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   SUBB Extended   ---------------------------------
    //---------------------------------------------------------
    SUBBExtended::SUBBExtended(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xF0 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.set_regB(_evaluate(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBBExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   SUBD   ==========================================
    //-----   SUBD Immediate   --------------------------------
    //---------------------------------------------------------
    SUBDImmediate::SUBDImmediate(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0x83 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBDImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.set_regD(_evaluate_16(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBDImmediate::get_cycles_count() noexcept
    {
        return 3;
    }


    //-----   SUBD Direct   -----------------------------------
    //---------------------------------------------------------
    SUBDDirect::SUBDDirect(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0x93 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBDDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.set_regD(_evaluate_16(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBDDirect::get_cycles_count() noexcept
    {
        return 6;
    }

    //-----   SUBD Indexed   ----------------------------------
    //---------------------------------------------------------
    SUBDIndexed::SUBDIndexed(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xA3 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBDIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.set_regD(_evaluate_16(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte()));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBDIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   SUBD Extended   ---------------------------------
    //---------------------------------------------------------
    SUBDExtended::SUBDExtended(archi::HWArchitecture& hw_arch) noexcept
        : SUBBase{ hw_arch, 0xB3 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SUBDExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.set_regD(_evaluate_16(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SUBDExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
