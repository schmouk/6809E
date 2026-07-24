#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   JMP Memory   ====================================
    //-----   JMP Direct   ------------------------------------
    struct JMPDirect : public BaseInstruction
    {
        JMPDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~JMPDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   JMP Indexed   -----------------------------------
    class JMPIndexed : public BaseInstruction
    {
    public:
        JMPIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~JMPIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   JMP Extended   ----------------------------------
    struct JMPExtended : public BaseInstruction
    {
        JMPExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~JMPExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
