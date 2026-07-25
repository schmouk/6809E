#include <cstdint>

#include "./neg.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   NEG Base Class   ================================
    //---------------------------------------------------------
    NEGBase::NEGBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte NEGBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void NEGBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_carry();
        _hw_arch.regCC.clr_overflow();
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int NEGBase::_evaluate_value(const int value)
    {
        return ~value + 1;
    }


    //=====   NEGA   ==========================================
    //-----   NEGA Inherent   ---------------------------------
    NEGAInherent::NEGAInherent(archi::HWArchitecture& hw_arch) noexcept
        : NEGBase{ hw_arch, 0x40 }
    {}

    //---------------------------------------------------------
    const std::uint64_t NEGAInherent::exec()
    {
        _hw_arch.set_regA(_evaluate(_hw_arch.regA));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t NEGAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   NEGB   ==========================================
    //-----   NEGB Inherent   ---------------------------------
    NEGBInherent::NEGBInherent(archi::HWArchitecture& hw_arch) noexcept
        : NEGBase{ hw_arch, 0x50 }
    {}

    //---------------------------------------------------------
    const std::uint64_t NEGBInherent::exec()
    {
        _hw_arch.set_regB(_evaluate(_hw_arch.regB));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t NEGBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   NEG Memory   ====================================
    //-----   NEG Direct   ------------------------------------
    //---------------------------------------------------------
    NEGDirect::NEGDirect(archi::HWArchitecture& hw_arch) noexcept
        : NEGBase{ hw_arch, 0x00 }
    {}

    //---------------------------------------------------------
    const std::uint64_t NEGDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t NEGDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   NEG Indexed   -----------------------------------
    //---------------------------------------------------------
    NEGIndexed::NEGIndexed(archi::HWArchitecture& hw_arch) noexcept
        : NEGBase{ hw_arch, 0x60 }
    {}

    //---------------------------------------------------------
    const std::uint64_t NEGIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t NEGIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   NEG Extended   ----------------------------------
    //---------------------------------------------------------
    NEGExtended::NEGExtended(archi::HWArchitecture& hw_arch) noexcept
        : NEGBase{ hw_arch, 0x70 }
    {}

    //---------------------------------------------------------
    const std::uint64_t NEGExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t NEGExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
