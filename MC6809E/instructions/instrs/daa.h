#pragma once

#include <cstdint>

#include "../base_instruction.h"

#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   DAA   ===========================================
    struct DAAInherent : public BaseInstruction
    {
        DAAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~DAAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
