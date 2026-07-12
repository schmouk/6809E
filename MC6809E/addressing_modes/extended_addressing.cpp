
#include <cstdint>

#include "./extended_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Extended Addressing   ===========================
    //---------------------------------------------------------
    const memory::Byte ExtendedAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.load_next_word()) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ExtendedAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        memory::MemAddr word_addr{ memory::MemAddr(hw_arch.load_next_word()) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_word_cycles() const
    {
        return 3;
    }


    //=====   Extended Indirect Addressing   ==================
    //---------------------------------------------------------
    const memory::Byte ExtendedIndirectAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr byte_memaddr{ memory::MemAddr(hw_arch.load_next_word()) };
        const memory::MemAddr byte_addr{ hw_arch.get_word(byte_memaddr) };

        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ExtendedIndirectAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr word_memaddr{ memory::MemAddr(hw_arch.load_next_word()) };
        const memory::MemAddr word_addr{ hw_arch.get_word(word_memaddr) };

        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectAddressing::get_byte_cycles() const
    {
        return 3;
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectAddressing::get_word_cycles() const
    {
        return 3;
    }

}