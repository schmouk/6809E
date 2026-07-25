#pragma once

#include <cstdint>

#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   SEX   ===========================================
    class SEXInherent : public BaseInstruction
    {
    public:
        SEXInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SEXInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        mutable std::uint64_t _cycles_count{ 0 };
    };

}
