#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   JSR Memory   ====================================
    //-----   JSR Direct   ------------------------------------
    struct JSRDirect : public BaseInstruction
    {
        JSRDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~JSRDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   JSR Indexed   -----------------------------------
    class JSRIndexed : public BaseInstruction
    {
    public:
        JSRIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~JSRIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   JSR Extended   ----------------------------------
    struct JSRExtended : public BaseInstruction
    {
        JSRExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~JSRExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
