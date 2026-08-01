#pragma once

#include "./base_interrupt.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace interrupt
{
    //=====   Non Maskable Interrupt   ========================
    struct NMIInterrupt : public BaseInterrupt
    {
        NMIInterrupt(archi::HWArchitecture& hw_arch)
            : BaseInterrupt(hw_arch, memory::MemAddr(0xFFFC))
        {}

        virtual ~NMIInterrupt() noexcept = default;
    };

}
