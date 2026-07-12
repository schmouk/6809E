
#include <cstdint>

#include "./inherent_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    const memory::Byte InherentAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        throw except::InvalidAddressingModeException(
            "Byte addressing is invalid for inherent addressing mode"
        );
    }

    //---------------------------------------------------------
    const memory::Word InherentAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        throw except::InvalidAddressingModeException(
            "Word addressing is invalid for inherent addressing mode"
        );
    }

    //---------------------------------------------------------
    const std::uint64_t InherentAddressing::get_byte_cycles() const
    {
        return 0;
    }

    //---------------------------------------------------------
    const std::uint64_t InherentAddressing::get_word_cycles() const
    {
        return 0;
    }

}