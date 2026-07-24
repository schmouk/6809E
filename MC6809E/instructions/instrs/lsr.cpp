#include <cstdint>

#include "./lsr.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   LSR Base Class   ================================
    //---------------------------------------------------------
    LSRBase::LSRBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte LSRBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void LSRBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.clr_negative();
    }

    //---------------------------------------------------------
    const int LSRBase::_evaluate_value(const int value)
    {
        _hw_arch.regCC.set_carry((value & 0x01) != 0);
        return value >> 1;
    }


    //=====   LSRA   ==========================================
    //-----   LSRA Inherent   ---------------------------------
    LSRAInherent::LSRAInherent(archi::HWArchitecture& hw_arch) noexcept
        : LSRBase{ hw_arch, 0x44 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LSRAInherent::exec()
    {
        _hw_arch.regA = _evaluate(_hw_arch.regA);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LSRAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   LSRB   ==========================================
    //-----   LSRB Inherent   ---------------------------------
    LSRBInherent::LSRBInherent(archi::HWArchitecture& hw_arch) noexcept
        : LSRBase{ hw_arch, 0x54 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LSRBInherent::exec()
    {
        _hw_arch.regB = _evaluate(_hw_arch.regB);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LSRBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   LSR Memory   ====================================
    //-----   LSR Direct   ------------------------------------
    //---------------------------------------------------------
    LSRDirect::LSRDirect(archi::HWArchitecture& hw_arch) noexcept
        : LSRBase{ hw_arch, 0x04 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LSRDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LSRDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   LSR Indexed   -----------------------------------
    //---------------------------------------------------------
    LSRIndexed::LSRIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LSRBase{ hw_arch, 0x64 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LSRIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LSRIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LSR Extended   ----------------------------------
    //---------------------------------------------------------
    LSRExtended::LSRExtended(archi::HWArchitecture& hw_arch) noexcept
        : LSRBase{ hw_arch, 0x74 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LSRExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LSRExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
