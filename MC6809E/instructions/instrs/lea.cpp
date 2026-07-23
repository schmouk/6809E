#include <cstdint>

#include "./lea.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //=====   LEA Base Class   ================================
    //---------------------------------------------------------
    LEABase::LEABase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte LEABase::_evaluate(const int value)
    {
        _evaluate_cc_flags(value);
        return memory::Byte(value & 0xffff);
    }

    //---------------------------------------------------------
    void LEABase::_evaluate_cc_flags(const int mem_value)
    {
        const memory::Word intermediate_value{ memory::Byte(mem_value & 0xffff) };
        _hw_arch.regCC.set_zero(intermediate_value == 0);
    }


    //=====   LEAS   ==========================================
    //-----   LEAS Indexed   ----------------------------------
    //---------------------------------------------------------
    LEASIndexed::LEASIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LEABase{ hw_arch, 0x32 }
    {}

    //---------------------------------------------------------
    void LEASIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regS = _evaluate(_indexed_mode_ptr->get_addressed_word());
    }

    //---------------------------------------------------------
    const std::uint64_t LEASIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }

    //---------------------------------------------------------
    void LEASIndexed::_evaluate_cc_flags(const int mem_value)
    {}


    //=====   LEAU   ==========================================
    //-----   LEAU Indexed   ----------------------------------
    //---------------------------------------------------------
    LEAUIndexed::LEAUIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LEABase{ hw_arch, 0x33 }
    {}

    //---------------------------------------------------------
    void LEAUIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regU = _evaluate(_indexed_mode_ptr->get_addressed_word());
    }

    //---------------------------------------------------------
    const std::uint64_t LEAUIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }

    //---------------------------------------------------------
    void LEAUIndexed::_evaluate_cc_flags(const int mem_value)
    {}


    //=====   LEAX   ==========================================
    //-----   LEAX Indexed   ----------------------------------
    //---------------------------------------------------------
    LEAXIndexed::LEAXIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LEABase{ hw_arch, 0x30 }
    {}

    //---------------------------------------------------------
    void LEAXIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regX = _evaluate(_indexed_mode_ptr->get_addressed_word());
    }

    //---------------------------------------------------------
    const std::uint64_t LEAXIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //=====   LEAY   ==========================================
    //-----   LEAY Indexed   ----------------------------------
    //---------------------------------------------------------
    LEAYIndexed::LEAYIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LEABase{ hw_arch, 0x31 }
    {
    }

    //---------------------------------------------------------
    void LEAYIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regY = _evaluate(_indexed_mode_ptr->get_addressed_word());
    }

    //---------------------------------------------------------
    const std::uint64_t LEAYIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }

}
