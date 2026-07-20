#include <memory>

#include "./accumulators_offset_addressing.h"
#include "./auto_incr_decr_addressing.h"
#include "./base_addressing.h"
#include "./constant_offset_addressing.h"
#include "./extended_addressing.h"
#include "./immediate_addressing.h"
#include "./indexed_addressing_factory.h"
#include "./pcr_offset_addressing.h"
#include "./register_addressing.h"
#include "./relative_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Factory creation of Indexed Addressing Mode Classes   =====
    //---------------------------------------------------------
    std::unique_ptr<BaseAddressingMode> make_indexed_addressing_class(archi::HWArchitecture& hw_arch)
    {
        const memory::Byte post_byte{ hw_arch.get_byte(hw_arch.regPC() + 1) };

        if ((post_byte & 0x80) == 0) {
            return std::make_unique<Constant5bitsOffsetIndexedAddressing>(hw_arch);
        }
        else {
            const memory::Byte post_byte_payload{ memory::Byte(post_byte & 0b1111) };
            const bool indirect_bit_is_set{ (post_byte & memory::Byte(0b0001'0000)) != 0 };

            switch (post_byte_payload) {
            case 0b0000:
                if (indirect_bit_is_set)
                    throw except::InvalidAddressingModeException("Indirect addressing mode is invalid for +1 post increment register indexing");
                else
                    return std::make_unique<PostIncrementIndexedAddressing<1>>(hw_arch);
                break;

            case 0b0001:
                if (indirect_bit_is_set)
                    return std::make_unique<PostIncrementIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<PostIncrementIndexedAddressing<2>>(hw_arch);
                break;

            case 0b0010:
                if (indirect_bit_is_set)
                    throw except::InvalidAddressingModeException("Indirect addressing mode is invalid for -1 pre decrement register indexing");
                else
                    return std::make_unique<PreDecrementIndexedAddressing<1>>(hw_arch);
                break;

            case 0b0011:
                if (indirect_bit_is_set)
                    return std::make_unique<PreDecrementIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<PreDecrementIndexedAddressing<2>>(hw_arch);
                break;

            case 0b0100:
                if (indirect_bit_is_set)
                    return std::make_unique<ZeroOffsetIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<ZeroOffsetIndexedAddressing>(hw_arch);
                break;

            case 0b0101:
                if (indirect_bit_is_set)
                    return std::make_unique<AccBOffsetIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<AccBOffsetIndexedAddressing>(hw_arch);
                break;

            case 0b0110:
                if (indirect_bit_is_set)
                    return std::make_unique<AccAOffsetIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<AccAOffsetIndexedAddressing>(hw_arch);
                break;

            case 0b1000:
                if (indirect_bit_is_set)
                    return std::make_unique<Constant8bitsOffsetIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<Constant8bitsOffsetIndexedAddressing>(hw_arch);
                break;

            case 0b1001:
                if (indirect_bit_is_set)
                    return std::make_unique<Constant16bitsOffsetIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<Constant16bitsOffsetIndexedAddressing>(hw_arch);
                break;

            case 0b1011:
                if (indirect_bit_is_set)
                    return std::make_unique<AccDOffsetIndirectIndexedAddressing>(hw_arch);
                else
                    return std::make_unique<AccDOffsetIndexedAddressing>(hw_arch);
                break;

            case 0b1100:
                if (indirect_bit_is_set)
                    return std::make_unique<ProgramCounterShortRelativeIndirectAddressing>(hw_arch);
                else
                    return std::make_unique<ProgramCounterShortRelativeAddressing>(hw_arch);
                break;

            case 0b1101:
                if (indirect_bit_is_set)
                    return std::make_unique<ProgramCounterLongRelativeIndirectAddressing>(hw_arch);
                else
                    return std::make_unique<ProgramCounterLongRelativeAddressing>(hw_arch);
                break;

            case 0b1111:
                if (indirect_bit_is_set)
                    return std::make_unique<ExtendedIndirectAddressing>(hw_arch);
                else
                    throw except::InvalidAddressingModeException("Direct extended addressing mode is invalid");
                    //return std::make_unique<ExtendedAddressing>(hw_arch);  // Notice: this is not a valid adderssing mode for the MC6809E
                break;

            default:
                // All other 4 bits combinations are invalid
                throw except::InvalidIndexingPostByteException(post_byte);
                break;
            }
        }
    }

}
