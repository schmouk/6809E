#include <cstdint>

#include "./inc.h"

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   INC Base Class   ================================
    //---------------------------------------------------------
    INCBase::INCBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte INCBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void INCBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.clr();

        _hw_arch.regCC.set_overflow((intermediate_value & 0xff) == 0x80);
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int INCBase::_evaluate_value(const int value)
    {
        return value + 1;
    }


    //=====   INCA   ==========================================
    //-----   INCA Inherent   ---------------------------------
    INCAInherent::INCAInherent(archi::HWArchitecture& hw_arch) noexcept
        : INCBase{ hw_arch, 0x4C }
    {}

    //---------------------------------------------------------
    const std::uint64_t INCAInherent::exec()
    {
        _hw_arch.set_regA(_evaluate(_hw_arch.regA));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t INCAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   INCB   ==========================================
    //-----   INCB Inherent   ---------------------------------
    INCBInherent::INCBInherent(archi::HWArchitecture& hw_arch) noexcept
        : INCBase{ hw_arch, 0x5C }
    {}

    //---------------------------------------------------------
    const std::uint64_t INCBInherent::exec()
    {
        _hw_arch.set_regB(_evaluate(_hw_arch.regB));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t INCBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   INC Memory   ====================================
    //-----   INC Direct   ------------------------------------
    //---------------------------------------------------------
    INCDirect::INCDirect(archi::HWArchitecture& hw_arch) noexcept
        : INCBase{ hw_arch, 0x0C }
    {}

    //---------------------------------------------------------
    const std::uint64_t INCDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t INCDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   INC Indexed   -----------------------------------
    //---------------------------------------------------------
    INCIndexed::INCIndexed(archi::HWArchitecture& hw_arch) noexcept
        : INCBase{ hw_arch, 0x6C }
    {}

    //---------------------------------------------------------
    const std::uint64_t INCIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t INCIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   INC Extended   ----------------------------------
    //---------------------------------------------------------
    INCExtended::INCExtended(archi::HWArchitecture& hw_arch) noexcept
        : INCBase{ hw_arch, 0x7C }
    {}

    //---------------------------------------------------------
    const std::uint64_t INCExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t INCExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
