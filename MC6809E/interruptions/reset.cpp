#include "./base_interrupt.h"
#include "./reset.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace interrupt
{
    //---------------------------------------------------------
    Reset::Reset(archi::HWArchitecture& hw_arch)
        : BaseInterrupt(hw_arch, memory::MemAddr(0xFFFE))
    {}

    //---------------------------------------------------------
    void Reset::exec()
    {
        _hw_arch.regDP = 0x00;
        _hw_arch.regCC.set_firqmask();
        _hw_arch.regCC.set_irqmask();

        _hw_arch.regPC = _pcr_value;
    }

}
