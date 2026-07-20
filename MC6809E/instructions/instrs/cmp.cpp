#include <cstdint>

#include "./cmp.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //=====   CMP Base Class   ================================
    //---------------------------------------------------------
    CMPBase::CMPBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    void CMPBase::_evaluate_cc_flags(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ reg_value - mem_value };

        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.set_carry(reg_value < mem_value);

        const bool reg7{ (reg_value & 0x80) != 0 };
        const bool mem7{ (mem_value & 0x80) != 0 };
        const bool int7{ (intermediate_value & 0x80) != 0 };
        _hw_arch.regCC.set_overflow(
            (reg7 && !mem7 && !int7) || (!reg7 && mem7 && int7)
        );
    }

    //---------------------------------------------------------
    void CMPBase::_evaluate_cc_flags_16(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ reg_value - mem_value };

        _hw_arch.regCC.set_negative((intermediate_value & 0x8000) != 0);
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.set_carry(reg_value < mem_value);

        const bool reg15{ (reg_value & 0x8000) != 0 };
        const bool mem15{ (mem_value & 0x8000) != 0 };
        const bool int15{ (intermediate_value & 0x8000) != 0 };
        _hw_arch.regCC.set_overflow(
            (reg15 && !mem15 && !int15) || (!reg15 && mem15 && int15)
        );
    }


    //=====   CMPA   ==========================================
    //-----   CMPA Immediate   --------------------------------
    //---------------------------------------------------------
    CMPAImmediate::CMPAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0x81 }
    {}

    //---------------------------------------------------------
    void CMPAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _evaluate_cc_flags(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   CMPA Direct   -----------------------------------
    //---------------------------------------------------------
    CMPADirect::CMPADirect(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0x91 }
    {}

    //---------------------------------------------------------
    void CMPADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _evaluate_cc_flags(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   CMPA Indexed   ----------------------------------
    //---------------------------------------------------------
    CMPAIndexed::CMPAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0xA1 }
    {}

    //---------------------------------------------------------
    void CMPAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _evaluate_cc_flags(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t CMPAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   CMPA Extended   ---------------------------------
    //---------------------------------------------------------
    CMPAExtended::CMPAExtended(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0xB1 }
    {}

    //---------------------------------------------------------
    void CMPAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _evaluate_cc_flags(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   CMPB   ==========================================
    //-----   CMPB Immediate   --------------------------------
    //---------------------------------------------------------
    CMPBImmediate::CMPBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0xC1 }
    {}

    //---------------------------------------------------------
    void CMPBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _evaluate_cc_flags(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   CMPB Direct   -----------------------------------
    //---------------------------------------------------------
    CMPBDirect::CMPBDirect(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0xD1 }
    {}

    //---------------------------------------------------------
    void CMPBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _evaluate_cc_flags(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   CMPB Indexed   ----------------------------------
    //---------------------------------------------------------
    CMPBIndexed::CMPBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0xE1 }
    {}

    //---------------------------------------------------------
    void CMPBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _evaluate_cc_flags(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t CMPBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   CMPB Extended   ---------------------------------
    //---------------------------------------------------------
    CMPBExtended::CMPBExtended(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0xF1 }
    {}

    //---------------------------------------------------------
    void CMPBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _evaluate_cc_flags(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPBExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   CMPD   ==========================================
    //-----   CMPD Immediate   --------------------------------
    //---------------------------------------------------------
    CMPDImmediate::CMPDImmediate(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0x10, 0x83 }
    {}

    //---------------------------------------------------------
    void CMPDImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _evaluate_cc_flags_16(_hw_arch.regD, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPDImmediate::get_cycles_count() noexcept
    {
        return 5;
    }


    //-----   CMPD Direct   -----------------------------------
    //---------------------------------------------------------
    CMPDDirect::CMPDDirect(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0x10, 0x93 }
    {}

    //---------------------------------------------------------
    void CMPDDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Word mem_value{ _hw_arch.get_word(_hw_arch.get_directpage_addr(value_low_addr)) };

        _evaluate_cc_flags_16(_hw_arch.regD, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPDDirect::get_cycles_count() noexcept
    {
        return 7;
    }

    //-----   CMPD Indexed   ----------------------------------
    //---------------------------------------------------------
    CMPDIndexed::CMPDIndexed(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0x10, 0xA3 }
    {}

    //---------------------------------------------------------
    void CMPDIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _evaluate_cc_flags_16(_hw_arch.regD, _indexed_mode_ptr->get_addressed_word());
    }

    //---------------------------------------------------------
    const std::uint64_t CMPDIndexed::get_cycles_count() noexcept
    {
        return 7 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   CMPD Extended   ---------------------------------
    //---------------------------------------------------------
    CMPDExtended::CMPDExtended(archi::HWArchitecture& hw_arch) noexcept
        : CMPBase{ hw_arch, 0x10, 0xB3 }
    {}

    //---------------------------------------------------------
    void CMPDExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Word mem_value{ _hw_arch.get_word(value_addr) };

        _evaluate_cc_flags_16(_hw_arch.regD, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t CMPDExtended::get_cycles_count() noexcept
    {
        return 8;
    }

}
