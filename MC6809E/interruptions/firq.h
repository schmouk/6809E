#pragma once

#include "./base_interrupt.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace interrupt
{
    //=====   Fast Interrupt Request   ========================
    struct FIRQInterrupt : public BaseInterrupt
    {
        FIRQInterrupt(archi::HWArchitecture& hw_arch)
            : BaseInterrupt(hw_arch, memory::MemAddr(0xFFFC))
        {}

        virtual ~FIRQInterrupt() noexcept = default;

        void exec() override;

    };

}
