#include "../architecture/hw_architecture.h"
#include "./base_interrupt.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace interrupt
{
    //---------------------------------------------------------
    BaseInterrupt::BaseInterrupt(
        archi::HWArchitecture& hw_arch,
        const memory::MemAddr  interrupt_vector_addr
    )
        : _hw_arch{ hw_arch }
        , _pcr_value{ memory::MemAddr(hw_arch.get_word(interrupt_vector_addr)) }
    {}

}
