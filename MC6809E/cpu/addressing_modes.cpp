#include <cstdint>
#include <type_traits>

#include "cpu6809e.h"
#include "../exceptions/exceptions.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"

#include "addressing_modes.h"


namespace cpu
{
    //=====   Inherent Addressing   ===========================
    //---------------------------------------------------------
    const memory::Byte InherentAddressing::get_addressed_byte(
            cpu::MicroprocUnit& cpu,
            memory::MemorySchema& mem
        ) const
    {}

    //---------------------------------------------------------
    const memory::Word InherentAddressing::get_addressed_word(
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {}

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
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        return mem[cpu.regPC++];
    }

    //---------------------------------------------------------
    const memory::Word ImmediateAddressing::get_addressed_word(
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word w{ mem.get_word(cpu.regPC) };
        cpu.regPC += 2;
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
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        throw except::InvalidAddressingModeException("Byte addressing is not implemented for extended addressing mode");
    }

    //---------------------------------------------------------
    const memory::Word ExtendedAddressing::get_addressed_word(
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word word_addr{ mem.get_word(cpu.regPC) };
        cpu.regPC += 2;

        return mem.get_word(word_addr);
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_byte_cycles() const
    {
        throw except::InvalidAddressingModeException("Byte addressing is not implemented for extended addressing mode");
    }

    //---------------------------------------------------------
    const std::uint64_t ExtendedAddressing::get_word_cycles() const
    {
        return 3;
    }


    //=====   Extended Indirect Addressing   ==================
    //---------------------------------------------------------
    const memory::Byte ExtendedIndirectAddressing::get_addressed_byte(
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word word_addr{ mem.get_word(cpu.regPC) };
        cpu.regPC += 2;

        return mem[mem.get_word(word_addr)];
    }

    //---------------------------------------------------------
    const memory::Word ExtendedIndirectAddressing::get_addressed_word(
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word word_addr{ mem.get_word(cpu.regPC) };
        cpu.regPC += 2;

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
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word byte_addr{ cpu.get_directpage_addr(mem[cpu.regPC]) };
        cpu.regPC++;

        return mem[byte_addr];
    }

    //---------------------------------------------------------
    const memory::Word DirectAddressing::get_addressed_word(
        cpu::MicroprocUnit& cpu,
        memory::MemorySchema& mem
    ) const
    {
        memory::Word word_addr{ cpu.get_directpage_addr(mem[cpu.regPC]) };
        cpu.regPC++;

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

    struct  : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& cpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& cpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

}