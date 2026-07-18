#include <cstdint>

#include "./direct_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    const memory::Byte DirectAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    )
    {
        const memory::Byte byte_low_addr{ hw_arch.load_next_byte() };
        const memory::MemAddr byte_addr{ hw_arch.get_directpage_addr(byte_low_addr) };

        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word DirectAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    )
    {
        const memory::Byte word_low_addr{ hw_arch.load_next_byte() };
        const memory::MemAddr word_addr{ hw_arch.get_directpage_addr(word_low_addr) };

        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t DirectAddressing::get_byte_cycles() const
    {
        return 2;
    }

    //---------------------------------------------------------
    const std::uint64_t DirectAddressing::get_word_cycles() const
    {
        return 2;
    }

}