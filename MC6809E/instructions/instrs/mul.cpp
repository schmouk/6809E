#pragma once

#include <cstdint>

#include "./mul.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   MUL   ===========================================
    //-----   MUL Inherent   ----------------------------------
    //---------------------------------------------------------
    MULInherent::MULInherent(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x3D)
    {}

    //---------------------------------------------------------
    const std::uint64_t MULInherent::exec()
    {
        const memory::Word value{
            memory::Word(memory::Word(_hw_arch.regA) * memory::Word(_hw_arch.regB))
        };

        _hw_arch.regCC.set_zero(value == 0);
        _hw_arch.regCC.set_carry((value & 0x0080) != 0);

        _hw_arch.set_regD(value);

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t MULInherent::get_cycles_count() noexcept
    {
        return 11;
    }

}
