#pragma once

#include "./base_interrupt.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace interrupt
{
    //=====   Interrupt Request   =============================
    struct IRQInterrupt : public BaseInterrupt
    {
        IRQInterrupt(archi::HWArchitecture& hw_arch)
            : BaseInterrupt(hw_arch, memory::MemAddr(0xFFFB))
        {}

        virtual ~IRQInterrupt() noexcept = default;
    };

}
