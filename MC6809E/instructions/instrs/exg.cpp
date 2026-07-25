#pragma once

#include <cstdint>
#include <tuple>

#include "./exg.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   EXG   ===========================================
    //---------------------------------------------------------
    EXGImmediate::EXGImmediate(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x1E)
    {}

    //---------------------------------------------------------
    const std::uint64_t EXGImmediate::exec()
    {
        cpu::CPURegister* reg1_ptr{ nullptr };
        cpu::CPURegister* reg2_ptr{ nullptr };

        std::tie(reg1_ptr, reg2_ptr) = _hw_arch.get_registers_defs(_hw_arch.load_next_byte());

        const int tmp{ reg1_ptr->get() };
        reg1_ptr->set(reg2_ptr->get());
        reg2_ptr->set(tmp);

        // Notice: next lines are unsatisfactory implementation
        if (reg1_ptr == &_hw_arch.regA || reg2_ptr == &_hw_arch.regA) {
            _hw_arch.set_regA(_hw_arch.regA());
        }
        else if (reg1_ptr == &_hw_arch.regB || reg2_ptr == &_hw_arch.regB) {
            _hw_arch.set_regB(_hw_arch.regB());
        }
        else if (reg1_ptr == &_hw_arch.regD || reg2_ptr == &_hw_arch.regD) {
            _hw_arch.set_regD(_hw_arch.regD());
        }

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t EXGImmediate::get_cycles_count() noexcept
    {
        return 8;
    }

}
