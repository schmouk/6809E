#pragma once

#include <cstdint>

#include "./pul.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   PUL Base Class   ================================
    //---------------------------------------------------------
    PULBase::PULBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const std::uint64_t PULBase::get_cycles_count() noexcept
    {
        return 5 + _pulled_cycles_count;
    }


    //=====   PULS   ==========================================
    //---------------------------------------------------------
    PULSImmediate::PULSImmediate(archi::HWArchitecture& hw_arch) noexcept
        : PULBase(hw_arch, 0x35)
    {}

    //---------------------------------------------------------
    void PULSImmediate::exec()
    {
        const memory::Byte ctrl_code{ _hw_arch.load_next_byte() };

        _pulled_cycles_count = _hw_arch.pull_system_stack(ctrl_code);
    }


    //=====   PULU   ==========================================
    //---------------------------------------------------------
    PULUImmediate::PULUImmediate(archi::HWArchitecture& hw_arch) noexcept
        : PULBase(hw_arch, 0x37)
    {}

    //---------------------------------------------------------
    void PULUImmediate::exec()
    {
        const memory::Byte ctrl_code{ _hw_arch.load_next_byte() };

        _pulled_cycles_count = _hw_arch.pull_user_stack(ctrl_code);
    }

}
