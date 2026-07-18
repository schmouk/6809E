#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    inline BaseAddressingMode::BaseAddressingMode(archi::HWArchitecture& hw_arch_) noexcept
        : hw_arch(hw_arch_)
    {}

    //---------------------------------------------------------
    const memory::Byte BaseAddressingMode::get_addressed_byte() const
    {
        throw except::NotImplementedMethodException("BaseAddressingMode::get_addressed_byte()");
    }

    //---------------------------------------------------------
    const memory::Word BaseAddressingMode::get_addressed_word() const
    {
        throw except::NotImplementedMethodException("BaseAddressingMode::get_addressed_word()");
    }

    //---------------------------------------------------------
    const memory::Byte BaseAddressingMode::get_addressed_byte(
        const memory::MemAddr addr
    )
    {
        return hw_arch.get_byte(addr);
    }

    //---------------------------------------------------------
    const memory::Word BaseAddressingMode::get_addressed_word(
        const memory::MemAddr addr
    )
    {
       return hw_arch.get_word(addr);
    }

    //---------------------------------------------------------
    void BaseAddressingMode::set_addressed_byte(const memory::Byte byte_value)
    {
        throw except::NotImplementedMethodException("BaseAddressingMode::set_addressed_byte(const memory::Byte)");
    }

    //---------------------------------------------------------
    void BaseAddressingMode::set_addressed_word(const memory::Word word_value)
    {
        throw except::NotImplementedMethodException("BaseAddressingMode::set_addressed_word(const memory::Word)");
    }

    //---------------------------------------------------------
    void BaseAddressingMode::set_addressed_byte(
        const memory::MemAddr addr,
        const memory::Byte    byte_value
    )
    {
        hw_arch.set_byte(addr, byte_value);
    }

    //---------------------------------------------------------
    void BaseAddressingMode::set_addressed_word(
        const memory::MemAddr addr,
        const memory::Word    word_value
    )
    {
        hw_arch.set_word(addr, word_value);
    }

}