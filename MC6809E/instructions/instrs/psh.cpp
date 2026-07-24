#pragma once

#include <cstdint>

#include "./psh.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   PSH Base Class   ================================
    //---------------------------------------------------------
    PSHBase::PSHBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const std::uint64_t PSHBase::get_cycles_count() noexcept
    {
        return 5 + _pushed_cycles_count;
    }


    //=====   PSHS   ==========================================
    //---------------------------------------------------------
    PSHSImmediate::PSHSImmediate(archi::HWArchitecture& hw_arch) noexcept
        : PSHBase(hw_arch, 0x34)
    {}

    //---------------------------------------------------------
    void PSHSImmediate::exec()
    {
        const memory::Byte ctrl_code{ _hw_arch.load_next_byte() };

        _pushed_cycles_count = _hw_arch.push_system_stack(ctrl_code);
    }


    //=====   PSHU   ==========================================
    //---------------------------------------------------------
    PSHUImmediate::PSHUImmediate(archi::HWArchitecture& hw_arch) noexcept
        : PSHBase(hw_arch, 0x36)
    {}

    //---------------------------------------------------------
    void PSHUImmediate::exec()
    {
        const memory::Byte ctrl_code{ _hw_arch.load_next_byte() };

        _pushed_cycles_count = _hw_arch.push_user_stack(ctrl_code);
    }

}
