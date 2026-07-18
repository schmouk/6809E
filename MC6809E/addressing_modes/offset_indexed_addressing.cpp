#include <cstdint>

#include "./indexed_addressing.h"
#include "./offset_indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    OffsetIndexedAddressingMode::OffsetIndexedAddressingMode(
        archi::HWArchitecture& hw_arch_
    ) noexcept
        : IndexedAddressingMode(hw_arch_)
    {
        _evaluate_offset();
    }

    //---------------------------------------------------------
    const memory::Byte  OffsetIndexedAddressingMode::get_addressed_byte() const
    {
        const memory::MemAddr reg_content{ memory::MemAddr((*get_indexing_reg_ptr())()) };
        return hw_arch.get_byte(reg_content + _offset);
    }

    //---------------------------------------------------------
    const memory::Word  OffsetIndexedAddressingMode::get_addressed_word() const
    {
        const memory::MemAddr reg_content{ memory::MemAddr((*get_indexing_reg_ptr())()) };
        return hw_arch.get_word(reg_content + _offset);
    }

    //---------------------------------------------------------
    void OffsetIndexedAddressingMode::set_addressed_byte(const memory::Byte byte_value)
    {
        const memory::MemAddr reg_content{ memory::MemAddr((*get_indexing_reg_ptr())()) };
        return hw_arch.set_byte(reg_content + _offset, byte_value);
    }

    //---------------------------------------------------------
    void OffsetIndexedAddressingMode::set_addressed_word(const memory::Word word_value)
    {
        const memory::MemAddr reg_content{ memory::MemAddr((*get_indexing_reg_ptr())()) };
        return hw_arch.set_word(reg_content + _offset, word_value);
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

    //---------------------------------------------------------
    const memory::Offset OffsetIndexedAddressingMode::_evaluate_offset() const
    {
        return memory::Offset(0);
    }
}
