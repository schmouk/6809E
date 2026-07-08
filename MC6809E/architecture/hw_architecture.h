#pragma once

/**
* This file defines next classes:
* - class HWArchitecture;  // The HardWare Architecture running any MC6809E emulation
*/

#include "../cpu/cpu6809e.h"
#include "../memory/memory_schema.h"


namespace archi
{
    //=====   H/W Architecture   ==============================
    class HWArchitecture
    {
    public:
        //-----   Constructors / Destructor   -----------------
        inline HWArchitecture() noexcept = default;
        virtual inline ~HWArchitecture() noexcept = default;

        inline HWArchitecture(const HWArchitecture&) noexcept = default;
        inline HWArchitecture(HWArchitecture&&) noexcept = default;

        HWArchitecture(memory::MemorySchema& mem) noexcept;


        //-----   Operations   --------------------------------
        void set_memory_schema(memory::MemorySchema& mem) noexcept;


    private:
        cpu::MicroprocUnit   _mpu{};
        memory::MemorySchema _mem{};

    };

}