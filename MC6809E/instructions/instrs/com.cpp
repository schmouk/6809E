#include <cstdint>

#include "./com.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   COM Base Class   ================================
    //---------------------------------------------------------
    COMBase::COMBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte COMBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void COMBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_carry();
        _hw_arch.regCC.clr_overflow();
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int COMBase::_evaluate_value(const int value)
    {
        return ~value;
    }


    //=====   COMA   ==========================================
    //-----   COMA Inherent   ---------------------------------
    COMAInherent::COMAInherent(archi::HWArchitecture& hw_arch) noexcept
        : COMBase{ hw_arch, 0x43 }
    {}

    //---------------------------------------------------------
    void COMAInherent::exec()
    {
        _hw_arch.regA = _evaluate(_hw_arch.regA);
    }

    //---------------------------------------------------------
    const std::uint64_t COMAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   COMB   ==========================================
    //-----   COMB Inherent   ---------------------------------
    COMBInherent::COMBInherent(archi::HWArchitecture& hw_arch) noexcept
        : COMBase{ hw_arch, 0x53 }
    {}

    //---------------------------------------------------------
    void COMBInherent::exec()
    {
        _hw_arch.regB = _evaluate(_hw_arch.regB);
    }

    //---------------------------------------------------------
    const std::uint64_t COMBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   COM Memory   ====================================
    //-----   COM Direct   ------------------------------------
    //---------------------------------------------------------
    COMDirect::COMDirect(archi::HWArchitecture& hw_arch) noexcept
        : COMBase{ hw_arch, 0x03 }
    {}

    //---------------------------------------------------------
    void COMDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
    }

    //---------------------------------------------------------
    const std::uint64_t COMDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   COM Indexed   -----------------------------------
    //---------------------------------------------------------
    COMIndexed::COMIndexed(archi::HWArchitecture& hw_arch) noexcept
        : COMBase{ hw_arch, 0x63 }
    {}

    //---------------------------------------------------------
    void COMIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );
    }

    //---------------------------------------------------------
    const std::uint64_t COMIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   COM Extended   ----------------------------------
    //---------------------------------------------------------
    COMExtended::COMExtended(archi::HWArchitecture& hw_arch) noexcept
        : COMBase{ hw_arch, 0x73 }
    {}

    //---------------------------------------------------------
    void COMExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
    }

    //---------------------------------------------------------
    const std::uint64_t COMExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
