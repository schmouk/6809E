#pragma once

#include <cstdint>

#include "../base_instruction.h"

#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   MUL   ===========================================
    //-----   MUL Inherent   ----------------------------------
    struct MULInherent : public BaseInstruction
    {
        MULInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~MULInherent() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
