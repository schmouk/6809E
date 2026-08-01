#pragma once

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace interrupt
{
    //=====   Base Interrupt   ================================
    // The base class for every interruption class
    class BaseInterrupt
    {
    public:
        //-----   Constructors / Destructor   -----------------
        BaseInterrupt(archi::HWArchitecture& hw_arch, const memory::MemAddr interrupt_vector_addr);

        virtual ~BaseInterrupt() noexcept = default;


        //-----   Operations   --------------------------------
        virtual void exec();


    protected:
        archi::HWArchitecture _hw_arch;
        memory::MemAddr       _pcr_value;

    };
}
