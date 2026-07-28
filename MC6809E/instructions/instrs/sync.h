#pragma once

#include <cstdint>

#include "../base_instruction.h"

#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   SYNC   ==========================================
    struct SYNCInherent : public BaseInstruction
    {
        SYNCInherent(archi::HWArchitecture& hw_arch);
        virtual ~SYNCInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
