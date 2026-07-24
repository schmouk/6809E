#include <cstdint>

#include "./eor.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   EOR Base Class   ================================
    //---------------------------------------------------------
    EORBase::EORBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte EORBase::_evaluate(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ _evaluate_value(reg_value, mem_value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void EORBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.clr_overflow();
    }

    //---------------------------------------------------------
    const int EORBase::_evaluate_value(const int reg_value, const int mem_value)
    {
        return reg_value & mem_value;
    }


    //=====   EORA   ==========================================
    //-----   EORA Immediate   --------------------------------
    //---------------------------------------------------------
    EORAImmediate::EORAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0x88 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   EORA Direct   -----------------------------------
    //---------------------------------------------------------
    EORADirect::EORADirect(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0x98 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   EORA Indexed   ----------------------------------
    //---------------------------------------------------------
    EORAIndexed::EORAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0xA8 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regA = _evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   EORA Extended   ---------------------------------
    //---------------------------------------------------------
    EORAExtended::EORAExtended(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0xB8 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   EORB   ==========================================
    //-----   EORB Immediate   --------------------------------
    //---------------------------------------------------------
    EORBImmediate::EORBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0xC8 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   EORB Direct   -----------------------------------
    //---------------------------------------------------------
    EORBDirect::EORBDirect(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0xD8 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   EORB Indexed   ----------------------------------
    //---------------------------------------------------------
    EORBIndexed::EORBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0xE8 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regB = _evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   EORB Extended   ---------------------------------
    //---------------------------------------------------------
    EORBExtended::EORBExtended(archi::HWArchitecture& hw_arch) noexcept
        : EORBase{ hw_arch, 0xF8 }
    {}

    //---------------------------------------------------------
    const std::uint64_t EORBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EORBExtended::get_cycles_count() noexcept
    {
        return 5;
    }

}
