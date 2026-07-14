#include <cstdint>
#include <initializer_list>
#include <memory>

#include "./addressing_modes.h"
#include "../cpu/cpu_registers.h"

#include "../architecture/hw_architecture.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Base Addressing Class   =========================
    //---------------------------------------------------------
    const memory::Byte BaseAddressingMode::get_addressed_byte(
        archi::HWArchitecture& hw_arch,
        const CPURegister&     reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word BaseAddressingMode::get_addressed_word(
        archi::HWArchitecture& hw_arch,
        const CPURegister&     reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Byte BaseAddressingMode::get_addressed_byte(
        archi::HWArchitecture&  hw_arch,
        const CPUIndexRegister& reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word BaseAddressingMode::get_addressed_word(
        archi::HWArchitecture&  hw_arch,
        const CPUIndexRegister& reg
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }



    //=====   Direct Addressing   =============================





    //=====   Offset Indexed Addressing   =====================




 

    //=====   Short Relative Branching   ======================
    //---------------------------------------------------------
    const memory::Offset ShortRelativeAddressing::get_offset(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::Byte byte{ hw_arch.get_byte(hw_arch.regPC()) };
        hw_arch.regPC++;

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
        const memory::Word word{ hw_arch.get_word(hw_arch.regPC()) };
        hw_arch.regPC += 2;

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


    //=====   Program Counter Relative Addressing   ===========
    //---------------------------------------------------------
    const memory::Byte ProgramCounterShortRelativeAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterShortRelativeAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_word(byte_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeAddressing::get_word_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const memory::Byte ProgramCounterLongRelativeAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterLongRelativeAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        return hw_arch.get_word(byte_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeAddressing::get_byte_cycles() const
    {
        return 5;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeAddressing::get_word_cycles() const
    {
        return 5;
    }


    //=====   Program Counter Relative Indexed Addressing   =====
    //---------------------------------------------------------
    const memory::Byte ProgramCounterShortRelativeIndexedAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr byte_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterShortRelativeIndexedAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + ShortRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr word_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeIndexedAddressing::get_byte_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterShortRelativeIndexedAddressing::get_word_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const memory::Byte ProgramCounterLongRelativeIndexedAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr byte_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word ProgramCounterLongRelativeIndexedAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ memory::MemAddr(hw_arch.regPC() + LongRelativeAddressing::get_offset(hw_arch)) };
        const memory::MemAddr word_addr{ hw_arch.get_word(indexed_addr) };
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeIndexedAddressing::get_byte_cycles() const
    {
        return 8;
    }

    //---------------------------------------------------------
    const std::uint64_t ProgramCounterLongRelativeIndexedAddressing::get_word_cycles() const
    {
        return 8;
    }


    //=====   Extended Indirect Indexed Addressing   ==========
    //---------------------------------------------------------
    const memory::Byte  ExtendedIndirectIndexedAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ hw_arch.regPC() };
        const memory::MemAddr byte_addr{ hw_arch.get_word(indexed_addr) };
        hw_arch.regPC += 2;
        return hw_arch.get_byte(byte_addr);
    }

    //---------------------------------------------------------
    const memory::Word  ExtendedIndirectIndexedAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indexed_addr{ hw_arch.regPC() };
        const memory::MemAddr word_addr{ hw_arch.get_word(indexed_addr) };
        hw_arch.regPC += 2;
        return hw_arch.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectIndexedAddressing::get_byte_cycles() const
    {
        return 5;
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectIndexedAddressing::get_word_cycles() const
    {
        return 5;
    }


    //=====   Factory creation of Addressing Mode Class   =====
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
            const memory::Byte post_byte_payload{ post_byte & 0b1111 };
            const bool indirect_bit_is_set{ (post_byte & 0b0001'0000) != 0 };

            switch (post_byte_payload) {
            case 0b0000:
                if (indirect_bit_is_set)
                    throw except::InvalidAddressingModeException("Indirect addressing mode is invalid for +1 post increment register indexing");
                else
                    return std::make_unique<PostIncrementIndexedAddressing<1>>(hw_arch, post_byte);
                break;
            case 0b0001:
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