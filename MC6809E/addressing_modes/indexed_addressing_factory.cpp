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


namespace addr
{
    //=====   Factory creation of Indexed Addressing Mode Classes   =====
    //---------------------------------------------------------
    std::unique_ptr<BaseAddressingMode> make_indexed_addressing_class(archi::HWArchitecture& hw_arch)
    {
        const memory::Byte post_byte{ hw_arch.get_byte(hw_arch.regPC) };
        hw_arch.regPC++;

        /** /
        //* - class  OffsetIndexedAddressingMode                  : public BaseAddressingMode;
        * - struct ZeroOffsetIndexedAddressing                  : public OffsetIndexedAddressingMode;
        //* - struct Constant5bitsOffsetIndexedAddressing         : public OffsetIndexedAddressingMode;
        * - struct Constant8bitsOffsetIndexedAddressing         : public OffsetIndexedAddressingMode;
        * - struct Constant16bitsOffsetIndexedAddressing        : public OffsetIndexedAddressingMode;
        * - struct AccAOffsetIndexedAddressing                  : public OffsetIndexedAddressingMode;
        * - struct AccBOffsetIndexedAddressing                  : public AccAOffsetIndexedAddressing;
        * - struct AccDOffsetIndexedAddressing                  : public OffsetIndexedAddressingMode;
        * - template<const memory::Word POST_INC = 1>
        *   struct PostIncrementIndexedAddressing               : public BaseAddressingMode;
        * - template<const memory::Word PRE_DEC = 1>
        *   struct PreDecrementIndexedAddressing                : public BaseAddressingMode;
        * - template<typename IndexedAddrT>
        *   struct OffsetIndirectIndexedAddressingModeT         : public IndexedAddrT;
        * - using  ZeroOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<ZeroOffsetIndexedAddressing>;
        * - using  Constant5bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant5bitsOffsetIndexedAddressing>;
        * - using  Constant8bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant8bitsOffsetIndexedAddressing>;
        * - using  Constant16bitsOffsetIndirectIndexedAddressing= OffsetIndirectIndexedAddressingModeT<Constant16bitsOffsetIndexedAddressing>;
        * - using  AccAOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<AccAOffsetIndexedAddressing>;
        * - using  AccBOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<AccBOffsetIndexedAddressing>;
        * - using  AccDOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<AccDOffsetIndexedAddressing>;
        * - using  PostIncrementIndirectIndexedAddressing       = OffsetIndirectIndexedAddressingModeT<PostIncrementIndexedAddressing<2>>;
        * - using  PreDecrementIndirectIndexedAddressing        = OffsetIndirectIndexedAddressingModeT<PreDecrementIndexedAddressing<2>>;
        /**/

        if ((post_byte & 0x80) == 0) {
            return std::make_unique<Constant5bitsOffsetIndexedAddressing>(post_byte);
        }
        else {
            const memory::Byte post_byte_payload{ memory::Byte(post_byte & 0b1111) };
            const bool indirect_bit_is_set{ (post_byte & memory::Byte(0b0001'0000)) != 0 };

            switch (post_byte_payload) {
            case 0b0000:
                if (indirect_bit_is_set)
                    throw except::InvalidAddressingModeException("Indirect addressing mode is invalid for +1 post increment register indexing");
                else
                    return std::make_unique<PostIncrementIndexedAddressing<1>>(hw_arch, post_byte);
                break;

            case 0b0001:
                if (indirect_bit_is_set)
                    return std::make_unique<PostIncrementIndexedIndirectAddressing>(hw_arch, post_byte);
                else
                    return std::make_unique<PostIncrementIndexedAddressing<2>>(hw_arch, post_byte);
                break;

            case 0b0010:
                break;

            case 0b0011:
                break;

            case 0b0100:
                break;

            case 0b0101:
                break;

            case 0b0110:
                break;

            case 0b0111:
                break;

            case 0b1000:
                break;

            case 0b1001:
                break;

            case 0b1010:
                break;

            case 0b1011:
                break;
            case 0b1100:
                break;

            case 0b1101:
                break;

            case 0b1110:
                break;

            case 0b1111:
                break;
            }
        }
    }

}
