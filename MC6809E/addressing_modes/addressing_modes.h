#pragma once

#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <type_traits>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"


/**
* This file defines the many memory addressing modes of the microprocessor MC6809E:
* 
* - struct InherentAddressing                           : public BaseAddressingMode;
* - struct ImmediateAddressing                          : public BaseAddressingMode;
* - struct ExtendedAddressing                           : public BaseAddressingMode;
* - struct ExtendedIndirectAddressing                   : public BaseAddressingMode;
* - struct DirectAddressing                             : public BaseAddressingMode;
* - class  RegisterAddressing                           : public BaseAddressingMode;
* - class  OffsetIndexedAddressingMode                  : public BaseAddressingMode;
* - struct ZeroOffsetIndexedAddressing                  : public OffsetIndexedAddressingMode;
* - struct Constant5bitsOffsetIndexedAddressing         : public OffsetIndexedAddressingMode;
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
* - struct OffsetRelativeAddressing                     : public BaseAddressingMode;
* - struct ShortRelativeAddressing                      : public OffsetRelativeAddressing;
* - struct LongRelativeAddressing                       : public OffsetRelativeAddressing;
* - struct ProgramCounterShortRelativeAddressing        : public ShortRelativeAddressing
* - struct ProgramCounterLongRelativeAddressing         : public LongRelativeAddressing;
* - struct ProgramCounterShortRelativeIndexedAddressing : public ShortRelativeAddressing;
* - struct ProgramCounterLongRelativeIndexedAddressing  : public LongRelativeAddressing
* - struct ExtendedIndirectIndexedAddressing            : public BaseAddressingMode;
* 
* - BaseAddressingClass& make_indexed_addressing_class(const memory::Byte mode_post_byte);
*/

namespace addr
{





    //=====   Indexed Addressing   ============================




}
