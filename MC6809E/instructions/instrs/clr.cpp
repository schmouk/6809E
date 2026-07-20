#include <cstdint>

#include "./clr.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   CLR Base Class   ================================
    //---------------------------------------------------------
    CLRBase::CLRBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte CLRBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void CLRBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.clr();

        _hw_arch.regCC.clr_carry();
        _hw_arch.regCC.clr_overflow();
        _hw_arch.regCC.set_zero();
        _hw_arch.regCC.clr_negative();
    }

    //---------------------------------------------------------
    const int CLRBase::_evaluate_value([[maybe_unused]] const int value)
    {
        return 0;
    }


    //=====   CLRA   ==========================================
    //-----   CLRA Inherent   ---------------------------------
    CLRAInherent::CLRAInherent(archi::HWArchitecture& hw_arch) noexcept
        : CLRBase{ hw_arch, 0x4F }
    {}

    //---------------------------------------------------------
    void CLRAInherent::exec()
    {
        _hw_arch.regA = _evaluate(_hw_arch.regA);
    }

    //---------------------------------------------------------
    const std::uint64_t CLRAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   CLRB   ==========================================
    //-----   CLRB Inherent   ---------------------------------
    CLRBInherent::CLRBInherent(archi::HWArchitecture& hw_arch) noexcept
        : CLRBase{ hw_arch, 0x5F }
    {}

    //---------------------------------------------------------
    void CLRBInherent::exec()
    {
        _hw_arch.regB = _evaluate(_hw_arch.regB);
    }

    //---------------------------------------------------------
    const std::uint64_t CLRBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   CLR Memory   ====================================
    //-----   CLR Direct   ------------------------------------
    //---------------------------------------------------------
    CLRDirect::CLRDirect(archi::HWArchitecture& hw_arch) noexcept
        : CLRBase{ hw_arch, 0x0F }
    {}

    //---------------------------------------------------------
    void CLRDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
    }

    //---------------------------------------------------------
    const std::uint64_t CLRDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   CLR Indexed   -----------------------------------
    //---------------------------------------------------------
    CLRIndexed::CLRIndexed(archi::HWArchitecture& hw_arch) noexcept
        : CLRBase{ hw_arch, 0x6F }
    {
    }

    //---------------------------------------------------------
    void CLRIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );
    }

    //---------------------------------------------------------
    const std::uint64_t CLRIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   CLR Extended   ----------------------------------
    //---------------------------------------------------------
    CLRExtended::CLRExtended(archi::HWArchitecture& hw_arch) noexcept
        : CLRBase{ hw_arch, 0x7F }
    {
    }

    //---------------------------------------------------------
    void CLRExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
    }

    //---------------------------------------------------------
    const std::uint64_t CLRExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
