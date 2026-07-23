#include <cstdint>

#include "./or.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //=====   OR Base Class   =================================
    //---------------------------------------------------------
    ORBase::ORBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte ORBase::_evaluate(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ _evaluate_value(reg_value, mem_value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void ORBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.clr_overflow();
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int ORBase::_evaluate_value(const int reg_value, const int mem_value)
    {
        return reg_value | mem_value;
    }


    //=====   ORA   ===========================================
    //-----   ORA Immediate   ---------------------------------
    //---------------------------------------------------------
    ORAImmediate::ORAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0x8A }
    {}

    //---------------------------------------------------------
    void ORAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ORAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ORA Direct   ------------------------------------
    //---------------------------------------------------------
    ORADirect::ORADirect(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0x9A }
    {
    }

    //---------------------------------------------------------
    void ORADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ORADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   ORA Indexed   -----------------------------------
    //---------------------------------------------------------
    ORAIndexed::ORAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0xAA }
    {}

    //---------------------------------------------------------
    void ORAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regA = _evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t ORAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ORA Extended   ----------------------------------
    //---------------------------------------------------------
    ORAExtended::ORAExtended(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0xBA }
    {}

    //---------------------------------------------------------
    void ORAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ORAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   ORB   ===========================================
    //-----   ORB Immediate   ---------------------------------
    //---------------------------------------------------------
    ORBImmediate::ORBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0xCA }
    {}

    //---------------------------------------------------------
    void ORBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ORBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ORB Direct   ------------------------------------
    //---------------------------------------------------------
    ORBDirect::ORBDirect(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0xDA }
    {}

    //---------------------------------------------------------
    void ORBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ORBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   ORB Indexed   -----------------------------------
    //---------------------------------------------------------
    ORBIndexed::ORBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0xEA }
    {}

    //---------------------------------------------------------
    void ORBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regB = _evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t ORBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ORB Extended   ----------------------------------
    //---------------------------------------------------------
    ORBExtended::ORBExtended(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0xFA }
    {}

    //---------------------------------------------------------
    void ORBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ORBExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   ORCC   ==========================================
    //-----   ORCC Immediate   --------------------------------
    //---------------------------------------------------------
    ORCCImmediate::ORCCImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ORBase{ hw_arch, 0x1A }
    {}

    //---------------------------------------------------------
    void ORCCImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.regCC = std::uint8_t(_hw_arch.regCC() | mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ORCCImmediate::get_cycles_count() noexcept
    {
        return 3;
    }

}
