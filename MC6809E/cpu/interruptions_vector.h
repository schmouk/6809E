#pragma once

#include <cstdint>
#include <vector>


/**
* This file declares the table of interruptions vetors for the MC6809E
*/

namespace cpu
{
    //=====   MC6809E Interruptions   =========================
    enum class MC6809EInterruptions
    {
        reserved,   // Well, reserved interrupt
        swi3,       // The SOFTWARE INTERRUPT - 3
        swi2,       // The SOFTWARE INTERRUPT - 2
        firq,       // The FAST-INTERRUPT REQUEST (low level)
        irq,        // The INTERRUPT REQUEST (low level)
        swi,        // The SOFTWARE INTERRUPT
        nmi,        // The NON MASKABLE INTERRUPT (low level)
        reset       // The RESET interrupt (low level)
    };


    //=====   Interrupts Vector Table   =======================
    inline constexpr std::uint16_t interrupts_vector[]{
        0xfff0,     // MC6809EInterruptions::reserved
        0xfff2,     // MC6809EInterruptions::swi3
        0xfff4,     // MC6809EInterruptions::swi2
        0xfff6,     // MC6809EInterruptions::firq
        0xfff8,     // MC6809EInterruptions::irq 
        0xfffa,     // MC6809EInterruptions::swi 
        0xfffc,     // MC6809EInterruptions::nmi 
        0xfffe      // MC6809EInterruptions::reset
    };
}
