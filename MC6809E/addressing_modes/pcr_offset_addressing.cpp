#include <cstdint>

#include "./pcr_offset_addressing.h"
#include "./relative_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Program Counter Short Relative Addressing   =====
    //---------------------------------------------------------
    ProgramCounterShortRelativeAddressing::ProgramCounterShortRelativeAddressing(archi::HWArchitecture& hw_arch_)
        : ShortRelativeAddressing(hw_arch_)
    {}

    //---------------------------------------------------------
    const memory::Byte ProgramCounterShortRelativeAddressing::get_addressed_byte() const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset()) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterShortRelativeAddressing::get_addressed_word() const
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset()) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    void ProgramCounterShortRelativeAddressing::set_addressed_byte(
        const memory::Byte byte_value
    )
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset()) };
        hw_arch.set_byte(byte_addr, byte_value);
    }

    //---------------------------------------------------------
    void ProgramCounterShortRelativeAddressing::set_addressed_word(
        const memory::Word word_value
    )
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset()) };
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
    ProgramCounterLongRelativeAddressing::ProgramCounterLongRelativeAddressing(archi::HWArchitecture& hw_arch_)
        : LongRelativeAddressing(hw_arch_)
    {}

    //---------------------------------------------------------
    const memory::Byte ProgramCounterLongRelativeAddressing::get_addressed_byte() const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset()) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterLongRelativeAddressing::get_addressed_word() const
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset()) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    void ProgramCounterLongRelativeAddressing::set_addressed_byte(
        const memory::Byte byte_value
    )
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset()) };
        hw_arch.set_byte(byte_addr, byte_value);
    }

    //---------------------------------------------------------
    void ProgramCounterLongRelativeAddressing::set_addressed_word(
        const memory::Word word_value
    )
    {
        const memory::MemAddr word_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset()) };
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
