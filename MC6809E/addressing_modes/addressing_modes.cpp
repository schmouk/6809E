#include <cstdint>
#include <initializer_list>
#include <memory>

#include "./addressing_modes.h"
#include "../cpu/cpu_registers.h"

#include "../architecture/hw_architecture.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Base Addressing Class   =========================
    //---------------------------------------------------------
    const memory::Byte BaseAddressingMode::get_addressed_byte(
        archi::HWArchitecture& hw_arch,
        const CPURegister&     reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word BaseAddressingMode::get_addressed_word(
        archi::HWArchitecture& hw_arch,
        const CPURegister&     reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Byte BaseAddressingMode::get_addressed_byte(
        archi::HWArchitecture&  hw_arch,
        const CPUIndexRegister& reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word BaseAddressingMode::get_addressed_word(
        archi::HWArchitecture&  hw_arch,
        const CPUIndexRegister& reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }



    //=====   Direct Addressing   =============================





    //=====   Offset Indexed Addressing   =====================




 



    //=====   Program Counter Relative Addressing   ===========

    //=====   Program Counter Relative Indexed Addressing   =====
    //---------------------------------------------------------
    const memory::Byte ProgramCounterShortRelativeIndexedAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr byte_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterShortRelativeIndexedAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr word_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeIndexedAddressing::get_byte_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeIndexedAddressing::get_word_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const memory::Byte ProgramCounterLongRelativeIndexedAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr byte_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterLongRelativeIndexedAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr word_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeIndexedAddressing::get_byte_cycles() const
    {
        return 8;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeIndexedAddressing::get_word_cycles() const
    {
        return 8;
    }


    //=====   Extended Indirect Indexed Addressing   ==========
    //---------------------------------------------------------
    const memory::Byte  ExtendedIndirectIndexedAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ hw_arch.regPC() };
        const memory::MemAddr byte_addr{ hw_arch.get_word(indexed_addr) };
        hw_arch.regPC += 2;
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word  ExtendedIndirectIndexedAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ hw_arch.regPC() };
        const memory::MemAddr word_addr{ hw_arch.get_word(indexed_addr) };
        hw_arch.regPC += 2;
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectIndexedAddressing::get_byte_cycles() const
    {
        return 5;
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectIndexedAddressing::get_word_cycles() const
    {
        return 5;
    }


    //=====   Factory creation of Addressing Mode Class   =====
}