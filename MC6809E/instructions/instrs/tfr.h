#pragma once

#include <cstdint>

#include "../base_instruction.h"

#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   TFR   ===========================================
    struct TFRImmediate : public BaseInstruction
    {
        TFRImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~TFRImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
