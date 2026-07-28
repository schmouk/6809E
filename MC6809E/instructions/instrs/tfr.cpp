#pragma once

#include <cstdint>
#include <tuple>

#include "./tfr.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   TFR   ===========================================
    //---------------------------------------------------------
    TFRImmediate::TFRImmediate(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x1F)
    {}

    //---------------------------------------------------------
    const std::uint64_t TFRImmediate::exec()
    {
        cpu::CPURegister* reg1_ptr{ nullptr };
        cpu::CPURegister* reg2_ptr{ nullptr };

        std::tie(reg1_ptr, reg2_ptr) = _hw_arch.get_registers_defs(_hw_arch.load_next_byte());

        reg2_ptr->set(reg1_ptr->get());

        // Notice: next lines are unsatisfactory implementation
        if (reg2_ptr == &_hw_arch.regA) {
            _hw_arch.set_regA(_hw_arch.regA());
        }
        else if (reg2_ptr == &_hw_arch.regB) {
            _hw_arch.set_regB(_hw_arch.regB());
        }
        else if (reg2_ptr == &_hw_arch.regD) {
            _hw_arch.set_regD(_hw_arch.regD());
        }

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t TFRImmediate::get_cycles_count() noexcept
    {
        return 6;
    }

}
