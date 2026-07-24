#include <cstdint>

#include "./adc.h"
#include "./add.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //=====   ADD Base Class   ================================
    //---------------------------------------------------------
    ADDBase::ADDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : ADCBase(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const int ADDBase::_evaluate_value(const int reg_value, const int mem_value)
    {
        _hw_arch.regCC.set_halfcarry((reg_value & 0x0f) + (mem_value & 0x0f) > 0x0f);
        return reg_value + mem_value;
    }

    //---------------------------------------------------------
    const memory::Word ADDBase::_evaluate_16(const int reg_value, const int mem_value)
    {
        const int intermediate_value{ reg_value + mem_value };
        _evaluate_cc_flags(intermediate_value);
        return memory::Word(intermediate_value & 0xffff);
    }


    //=====   ADDA   ==========================================
    //-----   ADDA Immediate   --------------------------------
    //---------------------------------------------------------
    ADDAImmediate::ADDAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0x8B }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ADDA Direct   -----------------------------------
    //---------------------------------------------------------
    ADDADirect::ADDADirect(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0x9B }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   ADDA Indexed   ----------------------------------
    //---------------------------------------------------------
    ADDAIndexed::ADDAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xAB }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regA = _evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ADDA Extended   ---------------------------------
    //---------------------------------------------------------
    ADDAExtended::ADDAExtended(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xBB }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   ADDB   ==========================================
    //-----   ADDB Immediate   --------------------------------
    //---------------------------------------------------------
    ADDBImmediate::ADDBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xCB }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ADDB Direct   -----------------------------------
    //---------------------------------------------------------
    ADDBDirect::ADDBDirect(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xDB }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   ADDB Indexed   ----------------------------------
    //---------------------------------------------------------
    ADDBIndexed::ADDBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xEB }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regB = _evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ADDB Extended   ---------------------------------
    //---------------------------------------------------------
    ADDBExtended::ADDBExtended(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xFB }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDBExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   ADDD   ==========================================
    //-----   ADDD Immediate   --------------------------------
    //---------------------------------------------------------
    ADDDImmediate::ADDDImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xC3 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDDImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.regD = _evaluate_16(_hw_arch.regD, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDDImmediate::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   ADDD Direct   -----------------------------------
    //---------------------------------------------------------
    ADDDDirect::ADDDDirect(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xD3 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDDDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Word mem_value{ _hw_arch.get_word(_hw_arch.get_directpage_addr(value_low_addr)) };
        return get_cycles_count();

        _hw_arch.regD = _evaluate_16(_hw_arch.regD, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ADDDDirect::get_cycles_count() noexcept
    {
        return 6;
    }

    //-----   ADDD Indexed   ----------------------------------
    //---------------------------------------------------------
    ADDDIndexed::ADDDIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xE3 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDDIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regD = _evaluate_16(_hw_arch.regD, _indexed_mode_ptr->get_addressed_word());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDDIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ADDD Extended   ---------------------------------
    //---------------------------------------------------------
    ADDDExtended::ADDDExtended(archi::HWArchitecture& hw_arch) noexcept
        : ADDBase{ hw_arch, 0xF3 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ADDDExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Word mem_value{ _hw_arch.get_word(value_addr) };

        _hw_arch.regD = _evaluate_16(_hw_arch.regD, mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ADDDExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
