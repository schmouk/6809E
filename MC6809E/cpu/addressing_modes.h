#pragma once

#include <cstdint>
#include <initializer_list>

#include "./cpu6809e.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"


/**
* This file defines the many memory addressing modes of the microprocessor MC6809E
*/

namespace cpu
{
    //=====   Base Addressing Class   =========================
    struct BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const = 0;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const = 0;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const;

        virtual const std::uint64_t get_byte_cycles() const = 0;
        virtual const std::uint64_t get_word_cycles() const = 0;
    };


    //=====   Inherent Addressing   ===========================
    struct InherentAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Immediate Addressing   ==========================
    struct ImmediateAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Extended Addressing   ===========================
    //-----   Extended Addressing   ---------------------------
    struct ExtendedAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

    //-----   Extended Indirect Addressing   ------------------
    struct ExtendedIndirectAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Direct Addressing   =============================
    struct DirectAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Register Addressing   ===========================
    class RegisterAddressing : public BaseAddressingMode
    {
    public:
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

        std::initializer_list<cpu::EReg> evaluate_regs(const memory::Byte bytecode);


    private:
        static inline const bool _is_8bits(const cpu::EReg reg_ndx) {
            return (memory::Byte(reg_ndx) & 0b1000) == 0b1000;
        }

        static inline const bool _is_16bits(const cpu::EReg reg_ndx) {
            return (memory::Byte(reg_ndx) & 0b1000) == 0b0000;
        }

        static inline const cpu::EReg _get_reg_index(const memory::Byte reg_ndx);
    };


    //=====   Offset Indexed Addressing   =====================
    // Notice: base class for all offset indexed addressing modes.
    class OffsetIndexedAddressingMode : public BaseAddressingMode
    {
    public:
        inline OffsetIndexedAddressingMode(const std::int16_t offset = 0) noexcept;
        inline OffsetIndexedAddressingMode(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem);
        inline OffsetIndexedAddressingMode(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem);

        virtual ~OffsetIndexedAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        std::int16_t _offset{ 0 };
    };


    //=====   Indexed Addressing   ============================
    //-----   Zero-Offset Indexed Addressing   ----------------
    struct ZeroOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline ZeroOffsetIndexedAddressing() noexcept;
        virtual ~ZeroOffsetIndexedAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const override;
    };


    //-----   Constant 5-bits Offset Indexed Addressing   -----
    struct Constant5bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline Constant5bitsOffsetIndexedAddressing(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem);

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::EReg reg, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Accumulator Offset Indexed Addressing   ---------


    //-----   Auto Increment / Decrement Indexed Addressing   -----

        
    //-----   Zero-Offset Indexed Indirect Addressing   -------


    //-----   Constant Offset Indexed Indirect Addressing   -----


    //-----   Accumulator Offset Indexed Indirect Addressing   -----


    //-----   Auto Increment / Decrement Indexed Addressing   -----


    //=====   Relative Addressing   ===========================
    //-----   Short / Long Relative Branching   ---------------

    //-----   Program Counter Relative Addressing   -----------



    //=====   IMPLEMENTATIONS   ===============================
}
