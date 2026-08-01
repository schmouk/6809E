#include "./base_interrupt.h"
#include "./firq.h"

#include "../architecture/hw_architecture.h"


namespace interrupt
{
    //---------------------------------------------------------
    void FIRQInterrupt::exec()
    {
        _hw_arch.regCC.set_irqmask();
        _hw_arch.regCC.set_firqmask();
        _hw_arch.regCC.clr_entire();
        _hw_arch.push_system_stack_pcr();
        _hw_arch.regPC = _pcr_value;
    }

}
