#include <cstdint>

#include "./st.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //=====   ST Base Class   =================================
    //---------------------------------------------------------
    STBase::STBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    STBase::STBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode1, const memory::Byte opcode2) noexcept
        : BaseInstruction(hw_arch, opcode1, opcode2)
    {}

    //---------------------------------------------------------
    void STBase::_store_byte(
        const memory::MemAddr byte_addr,
        const memory::Byte    byte_value
    )
    {
        _evaluate_cc_flags(byte_value);
        _hw_arch.set_byte(byte_addr, byte_value);
    }

    //---------------------------------------------------------
    void STBase::_store_word(
        const memory::MemAddr word_addr,
        const memory::Word    word_value
    )
    {
        _evaluate_cc_flags_16(word_value);
        _hw_arch.set_word(word_addr, word_value);
    }

    //---------------------------------------------------------
    void STBase::_evaluate_cc_flags(const int mem_value)
    {
        const memory::Byte intermediate_value{ memory::Byte(mem_value & 0xff) };

        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.clr_overflow();
    }

    //---------------------------------------------------------
    void STBase::_evaluate_cc_flags_16(const int mem_value)
    {
        const memory::Word intermediate_value{ memory::Word(mem_value & 0xffff) };

        _hw_arch.regCC.set_negative((mem_value & 0x8000) != 0);
        _hw_arch.regCC.set_zero(intermediate_value == 0);
        _hw_arch.regCC.clr_overflow();
    }


    //=====   STA   ===========================================
    //-----   STA Direct   ------------------------------------
    //---------------------------------------------------------
    STADirect::STADirect(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x97 }
    {}

    //---------------------------------------------------------
    const std::uint64_t STADirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _store_byte(mem_addr, _hw_arch.regA());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   STA Indexed   -----------------------------------
    //---------------------------------------------------------
    STAIndexed::STAIndexed(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xA7 }
    {}

    //---------------------------------------------------------
    const std::uint64_t STAIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        memory::MemAddr mem_addr{ memory::MemAddr(_indexed_mode_ptr->get_addressed_word()) };

        _store_byte(mem_addr, _hw_arch.regA());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STAIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   STA Extended   ----------------------------------
    //---------------------------------------------------------
    STAExtended::STAExtended(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xB7 }
    {}

    //---------------------------------------------------------
    const std::uint64_t STAExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _store_byte(mem_addr, _hw_arch.regA());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   STB   ===========================================
    //-----   STB Direct   ------------------------------------
    //---------------------------------------------------------
    STBDirect::STBDirect(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xD7 }
    {}

    //---------------------------------------------------------
    const std::uint64_t STBDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _store_byte(mem_addr, _hw_arch.regB());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   STB Indexed   -----------------------------------
    //---------------------------------------------------------
    STBIndexed::STBIndexed(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xE7 }
    {}

    //---------------------------------------------------------
    const std::uint64_t STBIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        memory::MemAddr mem_addr{ memory::MemAddr(_indexed_mode_ptr->get_addressed_word()) };

        _store_byte(mem_addr, _hw_arch.regB());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STBIndexed::get_cycles_count() noexcept
    {
        return 4 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   STB Extended   ----------------------------------
    //---------------------------------------------------------
    STBExtended::STBExtended(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xF7 }
    {}

    //---------------------------------------------------------
    const std::uint64_t STBExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _store_byte(mem_addr, _hw_arch.regB());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STBExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   STD   ===========================================
    //-----   STD Direct   ------------------------------------
    //---------------------------------------------------------
    STDDirect::STDDirect(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xDD }
    {}

    //---------------------------------------------------------
    const std::uint64_t STDDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _store_word(mem_addr, _hw_arch.regD());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STDDirect::get_cycles_count() noexcept
    {
        return 5;
    }

    //-----   STD Indexed   -----------------------------------
    //---------------------------------------------------------
    STDIndexed::STDIndexed(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xED }
    {}

    //---------------------------------------------------------
    const std::uint64_t STDIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        memory::MemAddr mem_addr{ memory::MemAddr(_indexed_mode_ptr->get_addressed_word()) };

        _store_word(mem_addr, _hw_arch.regD());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STDIndexed::get_cycles_count() noexcept
    {
        return 5 + _indexed_mode_ptr->get_byte_cycles();
    }

    //-----   STD Extended   ----------------------------------
    //---------------------------------------------------------
    STDExtended::STDExtended(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xFD }
    {}

    //---------------------------------------------------------
    const std::uint64_t STDExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _store_word(mem_addr, _hw_arch.regD());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STDExtended::get_cycles_count() noexcept
    {
        return 6;
    }


    //=====   STS   ===========================================
    //-----   STS Direct   ------------------------------------
    //---------------------------------------------------------
    STSDirect::STSDirect(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x10, 0xDF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STSDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _store_word(mem_addr, _hw_arch.regS());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STSDirect::get_cycles_count() noexcept
    {
        return 6;
    }

    //-----   STS Indexed   -----------------------------------
    //---------------------------------------------------------
    STSIndexed::STSIndexed(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x10, 0xED }
    {}

    //---------------------------------------------------------
    const std::uint64_t STSIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        memory::MemAddr mem_addr{ memory::MemAddr(_indexed_mode_ptr->get_addressed_word()) };

        _store_word(mem_addr, _hw_arch.regS());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STSIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   STS Extended   ----------------------------------
    //---------------------------------------------------------
    STSExtended::STSExtended(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x10, 0xFF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STSExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _store_word(mem_addr, _hw_arch.regS());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STSExtended::get_cycles_count() noexcept
    {
        return 7;
    }


    //=====   STU   ===========================================
    //-----   STU Direct   ------------------------------------
    //---------------------------------------------------------
    STUDirect::STUDirect(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xDF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STUDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _store_word(mem_addr, _hw_arch.regU());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STUDirect::get_cycles_count() noexcept
    {
        return 5;
    }

    //-----   STU Indexed   -----------------------------------
    //---------------------------------------------------------
    STUIndexed::STUIndexed(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xEF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STUIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        memory::MemAddr mem_addr{ memory::MemAddr(_indexed_mode_ptr->get_addressed_word()) };

        _store_word(mem_addr, _hw_arch.regU());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STUIndexed::get_cycles_count() noexcept
    {
        return 5 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   STU Extended   ----------------------------------
    //---------------------------------------------------------
    STUExtended::STUExtended(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xFF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STUExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _store_word(mem_addr, _hw_arch.regU());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STUExtended::get_cycles_count() noexcept
    {
        return 6;
    }


    //=====   STX   ===========================================
    //-----   STX Direct   ------------------------------------
    //---------------------------------------------------------
    STXDirect::STXDirect(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x9F }
    {}

    //---------------------------------------------------------
    const std::uint64_t STXDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _store_word(mem_addr, _hw_arch.regX());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STXDirect::get_cycles_count() noexcept
    {
        return 5;
    }

    //-----   STX Indexed   -----------------------------------
    //---------------------------------------------------------
    STXIndexed::STXIndexed(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xAF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STXIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        memory::MemAddr mem_addr{ memory::MemAddr(_indexed_mode_ptr->get_addressed_word()) };

        _store_word(mem_addr, _hw_arch.regX());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STXIndexed::get_cycles_count() noexcept
    {
        return 5 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   STX Extended   ----------------------------------
    //---------------------------------------------------------
    STXExtended::STXExtended(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0xBF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STXExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _store_word(mem_addr, _hw_arch.regX());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STXExtended::get_cycles_count() noexcept
    {
        return 6;
    }


    //=====   STY   ===========================================
    //-----   STY Direct   ------------------------------------
    //---------------------------------------------------------
    STYDirect::STYDirect(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x10, 0x9F }
    {}

    //---------------------------------------------------------
    const std::uint64_t STYDirect::exec()
    {
        memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _store_word(mem_addr, _hw_arch.regY());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STYDirect::get_cycles_count() noexcept
    {
        return 6;
    }

    //-----   STY Indexed   -----------------------------------
    //---------------------------------------------------------
    STYIndexed::STYIndexed(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x10, 0xAF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STYIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        memory::MemAddr mem_addr{ memory::MemAddr(_indexed_mode_ptr->get_addressed_word()) };

        _store_word(mem_addr, _hw_arch.regY());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STYIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   STY Extended   ----------------------------------
    //---------------------------------------------------------
    STYExtended::STYExtended(archi::HWArchitecture& hw_arch) noexcept
        : STBase{ hw_arch, 0x10, 0xBF }
    {}

    //---------------------------------------------------------
    const std::uint64_t STYExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _store_word(mem_addr, _hw_arch.regX());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t STYExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
