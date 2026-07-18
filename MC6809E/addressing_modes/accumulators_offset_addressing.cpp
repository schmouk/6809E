#include <cstdint>

#include "./accumulators_offset_addressing.h"
#include "./offset_indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Accumulator A Offset Indexed Addressing   =======
    //---------------------------------------------------------
    AccAOffsetIndexedAddressing::AccAOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch_
    )
        : OffsetIndexedAddressingMode(hw_arch_)
    {}

    //---------------------------------------------------------
    const std::uint64_t AccAOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t AccAOffsetIndexedAddressing::get_word_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const memory::Offset AccAOffsetIndexedAddressing::_evaluate_offset() const
    {
        const memory::Byte acc_value{ hw_arch.regA() };
        if (acc_value & 0x80)  // Notice: signed offset, negative value
            return memory::Offset(acc_value & 0x7f) - 0x80;
        else
            return memory::Offset(acc_value & 0x7f);
    }


    //=====   Accumulator B Offset Indexed Addressing   =======
    //---------------------------------------------------------
    AccBOffsetIndexedAddressing::AccBOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch_
    )
        : AccAOffsetIndexedAddressing(hw_arch_)
    {}

    //---------------------------------------------------------
    const memory::Offset AccBOffsetIndexedAddressing::_evaluate_offset() const
    {
        const memory::Byte acc_value{ hw_arch.regB() };
        if (acc_value & 0x80)  // Notice: signed offset, negative value
            return memory::Offset(acc_value & 0x7f) - 0x80;
        else
            return memory::Offset(acc_value & 0x7f);
    }


    //=====   Accumulator D Offset Indexed Addressing   =======
    //---------------------------------------------------------
    AccDOffsetIndexedAddressing::AccDOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch_
    )
        : OffsetIndexedAddressingMode(hw_arch_)
    {}

    //---------------------------------------------------------
    const std::uint64_t AccDOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const std::uint64_t AccDOffsetIndexedAddressing::get_word_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const memory::Offset AccDOffsetIndexedAddressing::_evaluate_offset() const
    {
        const memory::Word acc_value{ hw_arch.regD() };
        if (acc_value & 0x8000)  // Notice: signed offset, negative value
            return memory::Offset(acc_value & 0x7fff) - 0x8000;
        else
            return memory::Offset(acc_value);
    }

}
