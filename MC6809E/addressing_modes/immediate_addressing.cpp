
#include <cstdint>

#include "./immediate_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    const memory::Byte ImmediateAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        return hw_arch.load_next_byte();
    }

    //---------------------------------------------------------
    const memory::Word ImmediateAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        return hw_arch.load_next_word();
    }

    //---------------------------------------------------------
    const std::uint64_t ImmediateAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t ImmediateAddressing::get_word_cycles() const
    {
        return 2;
    }

}