#include <cstdint>

#include "./adc.h"
#include "./and.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //=====   AND Base Class   ================================
    //---------------------------------------------------------
    ANDBase::ANDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : ADCBase(hw_arch, opcode)
    {
    }

    //---------------------------------------------------------
    const int ANDBase::_evaluate_value(const int reg_value, const int mem_value)
    {
        return reg_value & mem_value;
    }


    //=====   ANDA   ==========================================
    //-----   ANDA Immediate   --------------------------------
    //---------------------------------------------------------
    ANDAImmediate::ANDAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0x84 }
    {
    }

    //---------------------------------------------------------
    void ANDAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ANDAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ANDA Direct   -----------------------------------
    //---------------------------------------------------------
    ANDADirect::ANDADirect(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0x94 }
    {
    }

    //---------------------------------------------------------
    void ANDADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ANDADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   ANDA Indexed   ----------------------------------
    //---------------------------------------------------------
    ANDAIndexed::ANDAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0xA4 }
    {
    }

    //---------------------------------------------------------
    void ANDAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regA = _evaluate(_hw_arch.regA, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t ANDAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ANDA Extended   ---------------------------------
    //---------------------------------------------------------
    ANDAExtended::ANDAExtended(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0xB4 }
    {
    }

    //---------------------------------------------------------
    void ANDAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regA = _evaluate(_hw_arch.regA, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ANDAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   ANDB   ==========================================
    //-----   ANDB Immediate   --------------------------------
    //---------------------------------------------------------
    ANDBImmediate::ANDBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0xC4 }
    {
    }

    //---------------------------------------------------------
    void ANDBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ANDBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ANDB Direct   -----------------------------------
    //---------------------------------------------------------
    ANDBDirect::ANDBDirect(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0xD4 }
    {
    }

    //---------------------------------------------------------
    void ANDBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ANDBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   ANDB Indexed   ----------------------------------
    //---------------------------------------------------------
    ANDBIndexed::ANDBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0xE4 }
    {
    }

    //---------------------------------------------------------
    void ANDBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regB = _evaluate(_hw_arch.regB, _indexed_mode_ptr->get_addressed_byte());
    }

    //---------------------------------------------------------
    const std::uint64_t ANDBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ANDB Extended   ---------------------------------
    //---------------------------------------------------------
    ANDBExtended::ANDBExtended(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0xF4 }
    {
    }

    //---------------------------------------------------------
    void ANDBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regB = _evaluate(_hw_arch.regB, mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ANDBExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   ANDCC   =========================================
    //-----   ANDCC Immediate   -------------------------------
    //---------------------------------------------------------
    ANDCCImmediate::ANDCCImmediate(archi::HWArchitecture& hw_arch) noexcept
        : ANDBase{ hw_arch, 0x1C }
    {
    }

    //---------------------------------------------------------
    void ANDCCImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.regCC = std::uint8_t(_hw_arch.regCC & mem_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ANDCCImmediate::get_cycles_count() noexcept
    {
        return 3;
    }

}
