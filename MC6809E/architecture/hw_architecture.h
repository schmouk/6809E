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
    struct HWArchitecture
    {
        cpu::MicroprocUnit   mpu{};
        memory::MemorySchema mem{};

        //-----   Constructors / Destructor   -----------------
        inline HWArchitecture() noexcept = default;
        virtual inline ~HWArchitecture() noexcept = default;

        inline HWArchitecture(const HWArchitecture&) noexcept = default;
        inline HWArchitecture(HWArchitecture&&) noexcept = default;

        HWArchitecture(memory::MemorySchema& mem_) noexcept;


        //-----   Operations   --------------------------------
        void set_memory_schema(memory::MemorySchema& mem_) noexcept;

    };

}