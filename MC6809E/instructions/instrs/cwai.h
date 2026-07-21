#pragma once

#include <cstdint>

#include "../base_instruction.h"

#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   CWAI   ==========================================
    struct CWAIImmediate : public BaseInstruction
    {
        CWAIImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CWAIImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
