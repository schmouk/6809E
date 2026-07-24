#include <cstdint>

#include "./ror.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   ROR Base Class   ================================
    //---------------------------------------------------------
    RORBase::RORBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte RORBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void RORBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_carry((intermediate_value & 0x100) != 0);
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int RORBase::_evaluate_value(const int value)
    {
        const int carry_value{ _hw_arch.regCC.carry_flag() };
        _hw_arch.regCC.set_carry(value & 0x01);
        return (value >> 1) | (carry_value << 7);
    }


    //=====   RORA   ==========================================
    //-----   RORA Inherent   ---------------------------------
    RORAInherent::RORAInherent(archi::HWArchitecture& hw_arch) noexcept
        : RORBase{ hw_arch, 0x46 }
    {}

    //---------------------------------------------------------
    const std::uint64_t RORAInherent::exec()
    {
        _hw_arch.regA = _evaluate(_hw_arch.regA);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t RORAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   RORB   ==========================================
    //-----   RORB Inherent   ---------------------------------
    RORBInherent::RORBInherent(archi::HWArchitecture& hw_arch) noexcept
        : RORBase{ hw_arch, 0x56 }
    {}

    //---------------------------------------------------------
    const std::uint64_t RORBInherent::exec()
    {
        _hw_arch.regB = _evaluate(_hw_arch.regB);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t RORBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   ROR Memory   ====================================
    //-----   ROR Direct   ------------------------------------
    //---------------------------------------------------------
    RORDirect::RORDirect(archi::HWArchitecture& hw_arch) noexcept
        : RORBase{ hw_arch, 0x06 }
    {}

    //---------------------------------------------------------
    const std::uint64_t RORDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t RORDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   ROR Indexed   -----------------------------------
    //---------------------------------------------------------
    RORIndexed::RORIndexed(archi::HWArchitecture& hw_arch) noexcept
        : RORBase{ hw_arch, 0x66 }
    {}

    //---------------------------------------------------------
    const std::uint64_t RORIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t RORIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ROR Extended   ----------------------------------
    //---------------------------------------------------------
    RORExtended::RORExtended(archi::HWArchitecture& hw_arch) noexcept
        : RORBase{ hw_arch, 0x76 }
    {}

    //---------------------------------------------------------
    const std::uint64_t RORExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t RORExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
