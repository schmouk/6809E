#include <cstdint>

#include "./dec.h"

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   DEC Base Class   ================================
    //---------------------------------------------------------
    DECBase::DECBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte DECBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void DECBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.clr();

        _hw_arch.regCC.set_overflow((intermediate_value & 0xff) == 0x7f);
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int DECBase::_evaluate_value(const int value)
    {
        return value - 1;
    }


    //=====   DECA   ==========================================
    //-----   DECA Inherent   ---------------------------------
    DECAInherent::DECAInherent(archi::HWArchitecture& hw_arch) noexcept
        : DECBase{ hw_arch, 0x4A }
    {}

    //---------------------------------------------------------
    const std::uint64_t DECAInherent::exec()
    {
        _hw_arch.regA = _evaluate(_hw_arch.regA);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t DECAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   DECB   ==========================================
    //-----   DECB Inherent   ---------------------------------
    DECBInherent::DECBInherent(archi::HWArchitecture& hw_arch) noexcept
        : DECBase{ hw_arch, 0x5A }
    {}

    //---------------------------------------------------------
    const std::uint64_t DECBInherent::exec()
    {
        _hw_arch.regB = _evaluate(_hw_arch.regB);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t DECBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   DEC Memory   ====================================
    //-----   DEC Direct   ------------------------------------
    //---------------------------------------------------------
    DECDirect::DECDirect(archi::HWArchitecture& hw_arch) noexcept
        : DECBase{ hw_arch, 0x0A }
    {}

    //---------------------------------------------------------
    const std::uint64_t DECDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t DECDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   DEC Indexed   -----------------------------------
    //---------------------------------------------------------
    DECIndexed::DECIndexed(archi::HWArchitecture& hw_arch) noexcept
        : DECBase{ hw_arch, 0x6A }
    {}

    //---------------------------------------------------------
    const std::uint64_t DECIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t DECIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   DEC Extended   ----------------------------------
    //---------------------------------------------------------
    DECExtended::DECExtended(archi::HWArchitecture& hw_arch) noexcept
        : DECBase{ hw_arch, 0x7A }
    {}

    //---------------------------------------------------------
    const std::uint64_t DECExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t DECExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
