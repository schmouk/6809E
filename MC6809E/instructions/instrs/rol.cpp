#include <cstdint>

#include "./rol.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   ROL Base Class   ================================
    //---------------------------------------------------------
    ROLBase::ROLBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte ROLBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void ROLBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_carry((intermediate_value & 0x100) != 0);
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int ROLBase::_evaluate_value(const int value)
    {
        const bool bit7{ (value & 0x80) == 0x80 };
        const bool bit6{ (value & 0x40) == 0x40 };
        _hw_arch.regCC.set_overflow(bit7 != bit6);

        return (value << 1) + int(_hw_arch.regCC.carry_flag());
    }


    //=====   ROLA   ==========================================
    //-----   ROLA Inherent   ---------------------------------
    ROLAInherent::ROLAInherent(archi::HWArchitecture& hw_arch) noexcept
        : ROLBase{ hw_arch, 0x49 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ROLAInherent::exec()
    {
        _hw_arch.set_regA(_evaluate(_hw_arch.regA));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ROLAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   ROLB   ==========================================
    //-----   ROLB Inherent   ---------------------------------
    ROLBInherent::ROLBInherent(archi::HWArchitecture& hw_arch) noexcept
        : ROLBase{ hw_arch, 0x59 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ROLBInherent::exec()
    {
        _hw_arch.set_regB(_evaluate(_hw_arch.regB));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ROLBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   ROL Memory   ====================================
    //-----   ROL Direct   ------------------------------------
    //---------------------------------------------------------
    ROLDirect::ROLDirect(archi::HWArchitecture& hw_arch) noexcept
        : ROLBase{ hw_arch, 0x09 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ROLDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ROLDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   ROL Indexed   -----------------------------------
    //---------------------------------------------------------
    ROLIndexed::ROLIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ROLBase{ hw_arch, 0x69 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ROLIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ROLIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ROL Extended   ----------------------------------
    //---------------------------------------------------------
    ROLExtended::ROLExtended(archi::HWArchitecture& hw_arch) noexcept
        : ROLBase{ hw_arch, 0x79 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ROLExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ROLExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
