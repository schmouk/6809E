#pragma once

#include <cstdint>

#include "./sync.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   SYNC   ==========================================
    //---------------------------------------------------------
    SYNCInherent::SYNCInherent(archi::HWArchitecture& hw_arch)
        : BaseInstruction(hw_arch, 0x13)
    {}

    //---------------------------------------------------------
    const std::uint64_t SYNCInherent::exec()
    {
        return get_cycles_count() + _hw_arch.wait_interrupt_synchronization();
    }

    //---------------------------------------------------------
    const std::uint64_t SYNCInherent::get_cycles_count() noexcept
    {
        return 4;
    }

}
