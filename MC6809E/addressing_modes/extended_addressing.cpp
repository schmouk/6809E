
#include <cstdint>

#include "./base_addressing.h"
#include "./extended_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Extended Addressing   ===========================
    //---------------------------------------------------------
    ExtendedAddressing::ExtendedAddressing(archi::HWArchitecture& hw_arch_)
        : BaseAddressingMode(hw_arch_)
    {}

    //---------------------------------------------------------
    const memory::Byte ExtendedAddressing::get_addressed_byte() const
    {
        memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.load_next_word()) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ExtendedAddressing::get_addressed_word() const
    {
        memory::MemAddr word_addr{ memory::MemAddr(hw_arch.load_next_word()) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_byte_cycles() const
    {
        return 0;
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_word_cycles() const
    {
        return 0;
    }


    //=====   Extended Indirect Addressing   ==================
    //---------------------------------------------------------
    ExtendedIndirectAddressing::ExtendedIndirectAddressing(archi::HWArchitecture& hw_arch_)
        : BaseAddressingMode(hw_arch_)
    {}

    //---------------------------------------------------------
    const memory::Byte ExtendedIndirectAddressing::get_addressed_byte() const
    {
        const memory::MemAddr byte_memaddr{ memory::MemAddr(hw_arch.load_next_word()) };
        const memory::MemAddr byte_addr{ hw_arch.get_word(byte_memaddr) };

        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ExtendedIndirectAddressing::get_addressed_word() const
    {
        const memory::MemAddr word_memaddr{ memory::MemAddr(hw_arch.load_next_word()) };
        const memory::MemAddr word_addr{ hw_arch.get_word(word_memaddr) };

        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectAddressing::get_byte_cycles() const
    {
        return 5;
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectAddressing::get_word_cycles() const
    {
        return 5;
    }

}