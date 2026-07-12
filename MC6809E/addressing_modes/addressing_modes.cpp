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


    //=====   Register Addressing   ===========================
    //---------------------------------------------------------
    const memory::Byte  RegisterAddressing::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::Byte reg_code{ hw_arch.get_byte(hw_arch.regPC()) };
        hw_arch.regPC++;

        return reg_code;
    }

    //---------------------------------------------------------
    const memory::Word  RegisterAddressing::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        throw except::InvalidAddressingModeException(
            "Word addressing is invalid for register addressing mode"
        );
    }

    //---------------------------------------------------------
    const std::uint64_t RegisterAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t RegisterAddressing::get_word_cycles() const
    {
        throw except::InvalidAddressingModeException(
            "Word addressing is invalid for register addressing mode"
        );
    }

    //---------------------------------------------------------
    std::initializer_list<EReg> RegisterAddressing::evaluate_regs(const memory::Byte bytecode)
    {
        const EReg src{ _get_reg_index(bytecode >> 4) };
        const EReg dst{ _get_reg_index(bytecode & 0x0f) };
        
        if (_is_8bits(src) == _is_16bits(dst))
            throw except::InvalidMixedRegisterAddressingModeException();

        return { src, dst };
    }

    //---------------------------------------------------------
    const EReg RegisterAddressing::_get_reg_index(const memory::Byte reg_ndx)
    {
        if (reg_ndx <= memory::Byte(EReg::PC))
            return EReg(reg_ndx);

        if (memory::Byte(EReg::A) <= reg_ndx && reg_ndx <= memory::Byte(EReg::DP))
            return EReg(reg_ndx);

        throw except::InvalidRegisterCodeAddressingModeException(reg_ndx);
    }


    //=====   Indexed Register Addressing   ===================
    //---------------------------------------------------------
    IndexedAddressingMode::IndexedAddressingMode(archi::HWArchitecture& hw_arch) noexcept
        : BaseAddressingMode()
    {
        // Gets the post_byte value
        _post_byte = hw_arch.get_next_byte();

        // Sets the internal pointer to the indexing register
        constexpr memory::Byte REG_MASK{ 0b0110'0000 };
        switch (_post_byte & REG_MASK) {
        case 0:
            _indexing_reg_ptr = &(hw_arch.regX);
            break;
        case 1:
            _indexing_reg_ptr = &(hw_arch.regY);
            break;
        case 2:
            _indexing_reg_ptr = &(hw_arch.regU);
            break;
        case 3:
            _indexing_reg_ptr = &(hw_arch.regS);
            break;
        }
    }

    //---------------------------------------------------------
    const memory::Byte  IndexedAddressingMode::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        throw except::InvalidOffsetAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word  IndexedAddressingMode::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        throw except::InvalidOffsetAddressingModeException();
    }


    //=====   Offset Indexed Addressing   =====================
    //---------------------------------------------------------
    OffsetIndexedAddressingMode::OffsetIndexedAddressingMode(archi::HWArchitecture& hw_arch) noexcept
        : IndexedAddressingMode(hw_arch)
    {
        _evaluate_offset(hw_arch, _post_byte);  // Notice: _post_byte is set at IndexedAddressingMode construction-time
    }

    //---------------------------------------------------------
    const std::uint64_t OffsetIndexedAddressingMode::get_byte_cycles() const
    {
        return 0;
    }

    //---------------------------------------------------------
    const std::uint64_t OffsetIndexedAddressingMode::get_word_cycles() const
    {
        return 0;
    }


    //=====   Zero-Offset Indexed Addressing   ================
    //---------------------------------------------------------
    ZeroOffsetIndexedAddressing::ZeroOffsetIndexedAddressing(archi::HWArchitecture& hw_arch) noexcept
        : IndexedAddressingMode(hw_arch)
    {}


    //=====   Constant 5-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant5bitsOffsetIndexedAddressing::Constant5bitsOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch
    )
        : OffsetIndexedAddressingMode(hw_arch)
    {}

    //---------------------------------------------------------
    const std::uint64_t Constant5bitsOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t Constant5bitsOffsetIndexedAddressing::get_word_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const memory::Offset Constant5bitsOffsetIndexedAddressing::_evaluate_offset(
        [[maybe_unused]] archi::HWArchitecture& hw_arch,
        const memory::Byte post_byte
    )
    {
        memory::Offset ret_offset{ memory::Offset(post_byte & 0x0f) };
        if (post_byte & 0x10)
            // Negative offset!
            ret_offset -= 0x10;
        
        return ret_offset;
    }


    //=====   Constant 8-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant8bitsOffsetIndexedAddressing::Constant8bitsOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Byte opcode{ hw_arch.get_byte(hw_arch.regPC()) };
        hw_arch.regPC++;
        if (opcode & 0x80)  // Notice: signed offset, negative value
            _offset = memory::Offset(opcode & 0x7f) - 0x80;
        else
            _offset = memory::Offset(opcode & 0x7f);
    }

    //---------------------------------------------------------
    const std::uint64_t Constant8bitsOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 1;
    }

    //---------------------------------------------------------
    const std::uint64_t Constant8bitsOffsetIndexedAddressing::get_word_cycles() const
    {
        return 1;
    }


    //=====   Constant 16-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant16bitsOffsetIndexedAddressing::Constant16bitsOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Word opcode{ hw_arch.get_word(hw_arch.regPC()) };
        hw_arch.regPC += 2;
        if (opcode & 0x8000)  // Notice: signed offset, negative value
            _offset = memory::Offset(opcode & 0x7fff) - 0x8000;
        else
            _offset = memory::Offset(opcode & 0x7fff);
    }

    //---------------------------------------------------------
    const std::uint64_t Constant16bitsOffsetIndexedAddressing::get_byte_cycles() const
    {
        return 4;
    }

    //---------------------------------------------------------
    const std::uint64_t Constant16bitsOffsetIndexedAddressing::get_word_cycles() const
    {
        return 4;
    }


    //=====   Accumulator A Offset Indexed Addressing   =======
    //---------------------------------------------------------
    AccAOffsetIndexedAddressing::AccAOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Byte acc_value{ hw_arch.regA() };
        if (acc_value & 0x80)  // Notice: signed offset, negative value
            _offset = memory::Offset(acc_value & 0x7f) - 0x80;
        else
            _offset = memory::Offset(acc_value & 0x7f);
    }

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


    //=====   Accumulator B Offset Indexed Addressing   =======
    //---------------------------------------------------------
    AccBOffsetIndexedAddressing::AccBOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch
    )
        : AccAOffsetIndexedAddressing(hw_arch)
    {
        const memory::Byte acc_value{ hw_arch.regB() };
        if (acc_value & 0x80)  // Notice: signed offset, negative value
            _offset = memory::Offset(acc_value & 0x7f) - 0x80;
        else
            _offset = memory::Offset(acc_value);
    }


    //=====   Accumulator D Offset Indexed Addressing   =======
    //---------------------------------------------------------
    AccDOffsetIndexedAddressing::AccDOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Word acc_value{ hw_arch.regD() };
        if (acc_value & 0x8000)  // Notice: signed offset, negative value
            _offset = memory::Offset(acc_value & 0x7fff) - 0x8000;
        else
            _offset = memory::Offset(acc_value);
    }

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