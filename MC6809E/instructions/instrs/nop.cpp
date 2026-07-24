#pragma once

#include <cstdint>

#include "./nop.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   NOP   ===========================================
    //-----   NOP Inherent   ----------------------------------
    //---------------------------------------------------------
    NOPInherent::NOPInherent(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x12)
    {}

    //---------------------------------------------------------
    const std::uint64_t NOPInherent::exec()
    {
        // Notice: No-op
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t NOPInherent::get_cycles_count() noexcept
    {
        return 2;
    }

}
