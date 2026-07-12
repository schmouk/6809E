#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
//#include "../cpu/cpu_registers.h"
#include "../memory/types.h"


namespace addr
{
    //---------------------------------------------------------
    void BaseAddressingMode::set_addressed_byte(
        archi::HWArchitecture& hw_arch,
        const memory::MemAddr  addr,
        const memory::Byte     byte_value
    )
    {
        hw_arch.set_byte(addr, byte_value);
    }

    //---------------------------------------------------------
    void BaseAddressingMode::set_addressed_word(
        archi::HWArchitecture& hw_arch,
        const memory::MemAddr  addr,
        const memory::Word     word_value
    )
    {
        hw_arch.set_word(addr, word_value);
    }

}