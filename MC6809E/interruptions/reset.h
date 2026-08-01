#pragma once

#include "./base_interrupt.h"

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace interrupt
{
    //=====   Reset   =========================================
    struct Reset : public BaseInterrupt
    {
        Reset(archi::HWArchitecture& hw_arch);
        virtual ~Reset() noexcept = default;

        void exec() override;

    };

}
