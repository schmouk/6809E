#pragma once

#include <cstdint>

#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //===== Instruction ABX   =================================
    //---------------------------------------------------------
    // Notice: Inherent addressing mode only
    struct ABX : public BaseInstruction
    {
        inline ABX(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ABX() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
