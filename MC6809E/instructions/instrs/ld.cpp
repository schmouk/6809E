#include <cstdint>

#include "./ld.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //=====   LD Base Class   =================================
    //---------------------------------------------------------
    LDBase::LDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    LDBase::LDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode1, const memory::Byte opcode2) noexcept
        : BaseInstruction(hw_arch, opcode1, opcode2)
    {}

    //---------------------------------------------------------
    const memory::Byte LDBase::_evaluate(const int value)
    {
        _evaluate_cc_flags(value);
        return memory::Byte(value & 0xff);
    }

    //---------------------------------------------------------
    const memory::Word LDBase::_evaluate_16(const int value)
    {
        _evaluate_cc_flags_16(value);
        return memory::Word(value & 0xff);
    }

    //---------------------------------------------------------
    void LDBase::_evaluate_cc_flags(const int mem_value)
    {
        const memory::Byte intermediate_value{ memory::Byte(mem_value & 0xff) };

        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.clr_overflow();
    }

    //---------------------------------------------------------
    void LDBase::_evaluate_cc_flags_16(const int mem_value)
    {
        const memory::Word intermediate_value{ memory::Word(mem_value & 0xffff) };

        _hw_arch.regCC.set_negative((mem_value & 0x8000) != 0);
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.clr_overflow();
    }


    //=====   LDA   ===========================================
    //-----   LDA Immediate   ---------------------------------
    //---------------------------------------------------------
    LDAImmediate::LDAImmediate(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x86 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDAImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regA = _evaluate(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   LDA Direct   ------------------------------------
    //---------------------------------------------------------
    LDADirect::LDADirect(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x96 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regA = _evaluate(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   LDA Indexed   -----------------------------------
    //---------------------------------------------------------
    LDAIndexed::LDAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xA6 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regA = _evaluate(_indexed_mode_ptr->get_addressed_byte());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LDA Extended   ----------------------------------
    //---------------------------------------------------------
    LDAExtended::LDAExtended(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xB6 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDAExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regA = _evaluate(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   LDB   ===========================================
    //-----   LDB Immediate   ---------------------------------
    //---------------------------------------------------------
    LDBImmediate::LDBImmediate(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xC6 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDBImmediate::exec()
    {
        memory::Byte mem_value{ _hw_arch.load_next_byte() };
        _hw_arch.regB = _evaluate(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   LDB Direct   ------------------------------------
    //---------------------------------------------------------
    LDBDirect::LDBDirect(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xD6 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Byte mem_value{ _hw_arch.get_byte(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regB = _evaluate(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   LDB Indexed   -----------------------------------
    //---------------------------------------------------------
    LDBIndexed::LDBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xE6 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regB = _evaluate(_indexed_mode_ptr->get_addressed_byte());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LDB Extended   ----------------------------------
    //---------------------------------------------------------
    LDBExtended::LDBExtended(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xF6 }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDBExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(value_addr) };

        _hw_arch.regB = _evaluate(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDBExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   LDD   ===========================================
    //-----   LDD Immediate   ---------------------------------
    //---------------------------------------------------------
    LDDImmediate::LDDImmediate(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xCC }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDDImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.set_regD(_evaluate_16(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDDImmediate::get_cycles_count() noexcept
    {
        return 3;
    }


    //-----   LDD Direct   ------------------------------------
    //---------------------------------------------------------
    LDDDirect::LDDDirect(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xDC }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDDDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Word mem_value{ _hw_arch.get_word(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.set_regD(_evaluate_16(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDDDirect::get_cycles_count() noexcept
    {
        return 5;
    }

    //-----   LDD Indexed   -----------------------------------
    //---------------------------------------------------------
    LDDIndexed::LDDIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xE6 }
    {
    }

    //---------------------------------------------------------
    const std::uint64_t LDDIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.set_regD(_evaluate_16(_indexed_mode_ptr->get_addressed_word()));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDDIndexed::get_cycles_count() noexcept
    {
        return 5 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LDD Extended   ----------------------------------
    //---------------------------------------------------------
    LDDExtended::LDDExtended(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xFC }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDDExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Word mem_value{ _hw_arch.get_word(value_addr) };

        _hw_arch.set_regD(_evaluate_16(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDDExtended::get_cycles_count() noexcept
    {
        return 6;
    }


    //=====   LDS   ===========================================
    //-----   LDS Immediate   ---------------------------------
    //---------------------------------------------------------
    LDSImmediate::LDSImmediate(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0xCE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDSImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.regS = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDSImmediate::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   LDS Direct   ------------------------------------
    //---------------------------------------------------------
    LDSDirect::LDSDirect(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0xDE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDSDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Word mem_value{ _hw_arch.get_word(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regS = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDSDirect::get_cycles_count() noexcept
    {
        return 6;
    }

    //-----   LDS Indexed   -----------------------------------
    //---------------------------------------------------------
    LDSIndexed::LDSIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0xEE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDSIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regS = _evaluate_16(_indexed_mode_ptr->get_addressed_word());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDSIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LDS Extended   ----------------------------------
    //---------------------------------------------------------
    LDSExtended::LDSExtended(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0xFE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDSExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Word mem_value{ _hw_arch.get_word(value_addr) };

        _hw_arch.regS = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDSExtended::get_cycles_count() noexcept
    {
        return 7;
    }


    //=====   LDU   ===========================================
    //-----   LDU Immediate   ---------------------------------
    //---------------------------------------------------------
    LDUImmediate::LDUImmediate(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xCE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDUImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.regU = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDUImmediate::get_cycles_count() noexcept
    {
        return 3;
    }


    //-----   LDU Direct   ------------------------------------
    //---------------------------------------------------------
    LDUDirect::LDUDirect(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xDE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDUDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Word mem_value{ _hw_arch.get_word(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regU = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDUDirect::get_cycles_count() noexcept
    {
        return 5;
    }

    //-----   LDU Indexed   -----------------------------------
    //---------------------------------------------------------
    LDUIndexed::LDUIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xEE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDUIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regU = _evaluate_16(_indexed_mode_ptr->get_addressed_word());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDUIndexed::get_cycles_count() noexcept
    {
        return 5 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LDU Extended   ----------------------------------
    //---------------------------------------------------------
    LDUExtended::LDUExtended(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xFE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDUExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Word mem_value{ _hw_arch.get_word(value_addr) };

        _hw_arch.regU = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDUExtended::get_cycles_count() noexcept
    {
        return 6;
    }


    //=====   LDX   ===========================================
    //-----   LDX Immediate   ---------------------------------
    //---------------------------------------------------------
    LDXImmediate::LDXImmediate(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x8E }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDXImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.regX = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDXImmediate::get_cycles_count() noexcept
    {
        return 3;
    }


    //-----   LDX Direct   ------------------------------------
    //---------------------------------------------------------
    LDXDirect::LDXDirect(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x9E }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDXDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Word mem_value{ _hw_arch.get_word(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regX = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDXDirect::get_cycles_count() noexcept
    {
        return 5;
    }

    //-----   LDX Indexed   -----------------------------------
    //---------------------------------------------------------
    LDXIndexed::LDXIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xAE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDXIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regX = _evaluate_16(_indexed_mode_ptr->get_addressed_word());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDXIndexed::get_cycles_count() noexcept
    {
        return 5 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LDX Extended   ----------------------------------
    //---------------------------------------------------------
    LDXExtended::LDXExtended(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0xBE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDXExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Word mem_value{ _hw_arch.get_word(value_addr) };

        _hw_arch.regX = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDXExtended::get_cycles_count() noexcept
    {
        return 6;
    }


    //=====   LDY   ===========================================
    //-----   LDY Immediate   ---------------------------------
    //---------------------------------------------------------
    LDYImmediate::LDYImmediate(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0x8E }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDYImmediate::exec()
    {
        memory::Word mem_value{ _hw_arch.load_next_word() };
        _hw_arch.regY = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDYImmediate::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   LDY Direct   ------------------------------------
    //---------------------------------------------------------
    LDYDirect::LDYDirect(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0x9E }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDYDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::Word mem_value{ _hw_arch.get_word(_hw_arch.get_directpage_addr(value_low_addr)) };

        _hw_arch.regY = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDYDirect::get_cycles_count() noexcept
    {
        return 6;
    }

    //-----   LDY Indexed   -----------------------------------
    //---------------------------------------------------------
    LDYIndexed::LDYIndexed(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0xAE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDYIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regY = _evaluate_16(_indexed_mode_ptr->get_addressed_word());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDYIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   LDY Extended   ----------------------------------
    //---------------------------------------------------------
    LDYExtended::LDYExtended(archi::HWArchitecture& hw_arch) noexcept
        : LDBase{ hw_arch, 0x10, 0xBE }
    {}

    //---------------------------------------------------------
    const std::uint64_t LDYExtended::exec()
    {
        memory::MemAddr value_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Word mem_value{ _hw_arch.get_word(value_addr) };

        _hw_arch.regY = _evaluate_16(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t LDYExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
