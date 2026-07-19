
#include <cstdint>

#include "./base_addressing.h"
#include "./inherent_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    InherentAddressing::InherentAddressing(archi::HWArchitecture& hw_arch) noexcept
        : BaseAddressingMode(hw_arch)
    {}

    //---------------------------------------------------------
    const memory::Byte InherentAddressing::get_addressed_byte() const
    {
        throw except::InvalidAddressingModeException(
            "Byte addressing is invalid for inherent addressing mode"
        );
    }

    //---------------------------------------------------------
    const memory::Word InherentAddressing::get_addressed_word() const
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