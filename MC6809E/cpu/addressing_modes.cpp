#include <cassert>
#include <cstdint>
#include <initializer_list>

#include "cpu6809e.h"
#include "../exceptions/exceptions.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"

#include "addressing_modes.h"


namespace cpu
{
    //=====   Base Addressing Class   =========================
    //---------------------------------------------------------
    const memory::Byte  BaseAddressingMode::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        throw except::InvalidAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word  BaseAddressingMode::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        throw except::InvalidAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Byte  BaseAddressingMode::get_addressed_byte(
        cpu::MicroprocUnit&          mpu,
        const cpu::CpuIndexRegister& reg,
        memory::MemorySchema&        mem
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word  BaseAddressingMode::get_addressed_word(
        cpu::MicroprocUnit&          mpu,
        const cpu::CpuIndexRegister& reg,
        memory::MemorySchema&        mem
    ) const
    {
        throw except::InvalidRegisterAddressingModeException();
    }


    //=====   Inherent Addressing   ===========================
    //---------------------------------------------------------
    const memory::Byte InherentAddressing::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        throw except::InvalidAddressingModeException(
            "Byte addressing is invalid for inherent addressing mode"
        );
    }

    //---------------------------------------------------------
    const memory::Word InherentAddressing::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
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


    //=====   Immediate Addressing   ==========================
    //---------------------------------------------------------
    const memory::Byte ImmediateAddressing::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        return mem[mpu.regPC++];
    }

    //---------------------------------------------------------
    const memory::Word ImmediateAddressing::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word w{ mem.get_word(mpu.regPC) };
        mpu.regPC += 2;
        return w;
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


    //=====   Extended Addressing   ===========================
    //---------------------------------------------------------
    const memory::Byte ExtendedAddressing::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        throw except::InvalidAddressingModeException(
            "Byte addressing is invalid for extended addressing mode"
        );
    }

    //---------------------------------------------------------
    const memory::Word ExtendedAddressing::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word word_addr{ mem.get_word(mpu.regPC) };
        mpu.regPC += 2;

        return mem.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_byte_cycles() const
    {
        throw except::InvalidAddressingModeException(
            "Byte addressing is invalid for extended addressing mode"
        );
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_word_cycles() const
    {
        return 3;
    }


    //=====   Extended Indirect Addressing   ==================
    //---------------------------------------------------------
    const memory::Byte ExtendedIndirectAddressing::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word word_addr{ mem.get_word(mpu.regPC) };
        mpu.regPC += 2;

        return mem[mem.get_word(word_addr)];
    }

    //---------------------------------------------------------
    const memory::Word ExtendedIndirectAddressing::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word word_addr{ mem.get_word(mpu.regPC) };
        mpu.regPC += 2;

        return mem.get_word(mem.get_word(word_addr));
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectAddressing::get_byte_cycles() const
    {
        return 3;
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedIndirectAddressing::get_word_cycles() const
    {
        return 3;
    }


    //=====   Direct Addressing   =============================
    //---------------------------------------------------------
    const memory::Byte DirectAddressing::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        const memory::MemAddr byte_addr{ mpu.get_directpage_addr(mem[mpu.regPC]) };
        mpu.regPC++;

        return mem[byte_addr];
    }

    //---------------------------------------------------------
    const memory::Word DirectAddressing::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        const memory::MemAddr word_addr{ mpu.get_directpage_addr(mem[mpu.regPC]) };
        mpu.regPC++;

        return mem.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t DirectAddressing::get_byte_cycles() const
    {
        return 2;
    }

    //---------------------------------------------------------
    const std::uint64_t DirectAddressing::get_word_cycles() const
    {
        return 2;
    }


    //=====   Register Addressing   ===========================
    //---------------------------------------------------------
    const memory::Byte  RegisterAddressing::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        const memory::Byte reg_code{ mem[mpu.regPC] };
        mpu.regPC++;

        return reg_code;
    }

    //---------------------------------------------------------
    const memory::Word  RegisterAddressing::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
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
    std::initializer_list<cpu::EReg> RegisterAddressing::evaluate_regs(const memory::Byte bytecode)
    {
        const cpu::EReg src{ _get_reg_index(bytecode >> 4) };
        const cpu::EReg dst{ _get_reg_index(bytecode & 0x0f) };
        
        if (_is_8bits(src) == _is_16bits(dst))
            throw except::InvalidMixedRegisterAddressingModeException();

        return { src, dst };
    }

    //---------------------------------------------------------
    const cpu::EReg RegisterAddressing::_get_reg_index(const memory::Byte reg_ndx)
    {
        if (reg_ndx <= memory::Byte(cpu::EReg::PC))
            return cpu::EReg(reg_ndx);

        if (memory::Byte(cpu::EReg::A) <= reg_ndx && reg_ndx <= memory::Byte(cpu::EReg::DP))
            return cpu::EReg(reg_ndx);

        throw except::InvalidRegisterCodeAddressingModeException(reg_ndx);
    }


    //=====   Offset Indexed Addressing   =====================
    //---------------------------------------------------------
    OffsetIndexedAddressingMode::OffsetIndexedAddressingMode(const std::int16_t offset) noexcept
        : _offset{ offset }
    {}

    //---------------------------------------------------------
    const memory::Byte  OffsetIndexedAddressingMode::get_addressed_byte(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        throw except::InvalidOffsetAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Word  OffsetIndexedAddressingMode::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        throw except::InvalidOffsetAddressingModeException();
    }

    //---------------------------------------------------------
    const memory::Byte  OffsetIndexedAddressingMode::get_addressed_byte(
        cpu::MicroprocUnit&          mpu,
        const cpu::CpuIndexRegister& reg,
        memory::MemorySchema&        mem
    ) const
    {
        const memory::MemAddr byte_addr{ memory::MemAddr(reg() + _offset) };
        return mem[byte_addr];
    }

    //---------------------------------------------------------
    const memory::Word  OffsetIndexedAddressingMode::get_addressed_word(
        cpu::MicroprocUnit&          mpu,
        const cpu::CpuIndexRegister& reg,
        memory::MemorySchema&        mem
    ) const
    {
        const memory::MemAddr word_addr{ memory::MemAddr(reg() + _offset) };
        return mem.get_word(word_addr);
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
    ZeroOffsetIndexedAddressing::ZeroOffsetIndexedAddressing(
        [[maybe_unused]] cpu::MicroprocUnit&   mpu,
        [[maybe_unused]] memory::MemorySchema& mem
    ) noexcept
        : OffsetIndexedAddressingMode{ 0 }
    {}


    //=====   Constant 5-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant5bitsOffsetIndexedAddressing::Constant5bitsOffsetIndexedAddressing(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Byte opcode{ mem[mpu.regPC() - 1]};
        if (opcode & 0x10)  // Notice: signed offset, negative value
            _offset = std::int16_t(opcode & 0x0f) - 0x10;
        else
            _offset = std::int16_t(opcode & 0x0f);
    }

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


    //=====   Constant 8-bits Offset Indexed Addressing   =====
    //---------------------------------------------------------
    Constant8bitsOffsetIndexedAddressing::Constant8bitsOffsetIndexedAddressing(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Byte opcode{ mem[mpu.regPC()] };
        mpu.regPC++;
        if (opcode & 0x80)  // Notice: signed offset, negative value
            _offset = std::int16_t(opcode & 0x7f) - 0x80;
        else
            _offset = std::int16_t(opcode & 0x7f);
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
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Word opcode{ mem.get_word(mpu.regPC()) };
        mpu.regPC += 2;
        if (opcode & 0x8000)  // Notice: signed offset, negative value
            _offset = std::int16_t(opcode & 0x7fff) - 0x8000;
        else
            _offset = std::int16_t(opcode & 0x7fff);
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
        cpu::MicroprocUnit&                    mpu,
        [[maybe_unused]] memory::MemorySchema& mem
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Byte acc_value{ mpu.regA() };
        if (acc_value & 0x80)  // Notice: signed offset, negative value
            _offset = std::int16_t(acc_value & 0x7f) - 0x80;
        else
            _offset = std::int16_t(acc_value & 0x7f);
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
        cpu::MicroprocUnit&                    mpu,
        [[maybe_unused]] memory::MemorySchema& mem
    )
        : AccAOffsetIndexedAddressing(mpu, mem)
    {
        const memory::Byte acc_value{ mpu.regB() };
        if (acc_value & 0x80)  // Notice: signed offset, negative value
            _offset = std::int16_t(acc_value & 0x7f) - 0x80;
        else
            _offset = std::int16_t(acc_value);
    }


    //=====   Accumulator D Offset Indexed Addressing   =======
    //---------------------------------------------------------
    AccDOffsetIndexedAddressing::AccDOffsetIndexedAddressing(
        cpu::MicroprocUnit&                    mpu,
        [[maybe_unused]] memory::MemorySchema& mem
    )
        : OffsetIndexedAddressingMode()
    {
        const memory::Word acc_value{ mpu.regD() };
        if (acc_value & 0x8000)  // Notice: signed offset, negative value
            _offset = std::int16_t(acc_value & 0x7fff) - 0x8000;
        else
            _offset = std::int16_t(acc_value);
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
    const std::int16_t ShortRelativeAddressing::get_offset(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const
    {
        const memory::Byte byte{ mem.get_byte(mpu.regPC()) };
        mpu.regPC++;

        if (byte & 0x80)
            return std::int16_t(byte & 0x7f) - 0x8000;
        else
            return std::int16_t(byte);
    }


    //=====    Long Relative Branching   ======================
    const std::int16_t LongRelativeAddressing::get_offset(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const
    {
        const memory::Word word{ mem.get_word(mpu.regPC()) };
        mpu.regPC += 2;

        if (word & 0x8000)
            return std::int16_t(word & 0x7fff) - 0x8000;
        else
            return std::int16_t(word);
    }

}