#include <cstdint>

#include "./relative_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Short Relative Branching   ======================
    //---------------------------------------------------------
    const memory::Offset ShortRelativeAddressing::get_offset(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::Byte byte{ hw_arch.load_next_byte() };

        if (byte & 0x80)
            return memory::Offset(byte & 0x7f) - 0x8000;
        else
            return memory::Offset(byte);
    }

    //---------------------------------------------------------
    const std::uint64_t ShortRelativeAddressing::get_byte_cycles() const
    {
        return 3;
    }

    //---------------------------------------------------------
    const std::uint64_t ShortRelativeAddressing::get_word_cycles() const
    {
        return 3;
    }


    //=====    Long Relative Branching   ======================
    //---------------------------------------------------------
    const memory::Offset LongRelativeAddressing::get_offset(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::Word word{ hw_arch.load_next_word() };

        if (word & 0x8000)
            return memory::Offset(word & 0x7fff) - 0x8000;
        else
            return memory::Offset(word);
    }

    //---------------------------------------------------------
    const std::uint64_t LongRelativeAddressing::get_byte_cycles() const
    {
        return 5;
    }

    //---------------------------------------------------------
    const std::uint64_t LongRelativeAddressing::get_word_cycles() const
    {
        return 5;
    }

}
