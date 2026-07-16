#include <cstdint>

#include "./pcr_offset_addressing.h"
#include "./relative_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Program Counter Short Relative Addressing   =====
    //---------------------------------------------------------
    const memory::Byte ProgramCounterShortRelativeAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterShortRelativeAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    void ProgramCounterShortRelativeAddressing::set_addressed_byte(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     byte_value
    )
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        hw_arch.set_byte(byte_addr, byte_value);
    }

    //---------------------------------------------------------
    void ProgramCounterShortRelativeAddressing::set_addressed_word(
        archi::HWArchitecture& hw_arch,
        const memory::Word     word_value
    )
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        hw_arch.set_word(word_addr, word_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeAddressing::get_word_cycles() const
    {
        return 1;
    }


    //=====   Program Counter Long Relative Addressing   ======
    //---------------------------------------------------------
    const memory::Byte ProgramCounterLongRelativeAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterLongRelativeAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    void ProgramCounterLongRelativeAddressing::set_addressed_byte(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     byte_value
    )
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        hw_arch.set_byte(byte_addr, byte_value);
    }

    //---------------------------------------------------------
    void ProgramCounterLongRelativeAddressing::set_addressed_word(
        archi::HWArchitecture& hw_arch,
        const memory::Word     word_value
    )
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        hw_arch.set_word(word_addr, word_value);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeAddressing::get_byte_cycles() const
    {
        return 5;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeAddressing::get_word_cycles() const
    {
        return 5;
    }


}
