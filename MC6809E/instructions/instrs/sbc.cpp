#include <cstdint>

#include "./sbc.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   SBC Base Class   ================================
    //---------------------------------------------------------
    SBCBase::SBCBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte SBCBase::_evaluate(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ _evaluate_value(reg_value, mem_value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void SBCBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int SBCBase::_evaluate_value(const int reg_value, const int mem_value)
    {
        const int sub_value{ mem_value + _hw_arch.regCC.carry_value() };
        const int res_value{ (reg_value - sub_value) & 0xff };

        _hw_arch.regCC.set_carry(
            memory::Byte(reg_value & 0xff) < memory::Byte(sub_value & 0xff)
        );

        const bool reg7{ (reg_value & 0x80) != 0 };
        const bool mem7{ (mem_value & 0x80) != 0 };
        const bool res7{ (res_value & 0x80) != 0 };
        _hw_arch.regCC.set_overflow(
            (reg7 && !mem7 && !res7) || (!reg7 && mem7 && res7)
        );

        return res_value;
    }


    //=====   SBCA   ==========================================
    //-----   SBCA Immediate   --------------------------------
    //---------------------------------------------------------
    SBCAImmediate::SBCAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0x82 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.set_regA(_evaluate(_hw_arch.regA, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   SBCA Direct   -----------------------------------
    //---------------------------------------------------------
    SBCADirect::SBCADirect(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0x92 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.set_regA(_evaluate(_hw_arch.regA, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   SBCA Indexed   ----------------------------------
    //---------------------------------------------------------
    SBCAIndexed::SBCAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0xA2 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.set_regA(_evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte()));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   SBCA Extended   ---------------------------------
    //---------------------------------------------------------
    SBCAExtended::SBCAExtended(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0xB2 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.set_regA(_evaluate(_hw_arch.regA, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   SBCB   ==========================================
    //-----   SBCB Immediate   --------------------------------
    //---------------------------------------------------------
    SBCBImmediate::SBCBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0xC2 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.set_regB(_evaluate(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   SBCB Direct   -----------------------------------
    //---------------------------------------------------------
    SBCBDirect::SBCBDirect(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0xD2 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.set_regB(_evaluate(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   SBCB Indexed   ----------------------------------
    //---------------------------------------------------------
    SBCBIndexed::SBCBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0xE2 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.set_regB(_evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte()));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   SBCB Extended   ---------------------------------
    //---------------------------------------------------------
    SBCBExtended::SBCBExtended(archi::HWArchitecture& hw_arch) noexcept
        : SBCBase{ hw_arch, 0xF2 }
    {}

    //---------------------------------------------------------
    const std::uint64_t SBCBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.set_regB(_evaluate(_hw_arch.regB, mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SBCBExtended::get_cycles_count() noexcept
    {
        return 5;
    }

}
