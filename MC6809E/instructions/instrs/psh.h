#pragma once

#include <cstdint>

#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   PSH Base Class   ================================
    class PSHBase : public BaseInstruction
    {
    public:
        PSHBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~PSHBase() noexcept = default;

        const std::uint64_t get_cycles_count() noexcept override;

    protected:
        std::uint64_t _pushed_cycles_count{ 0 };
    };


    //=====   PSHS   ==========================================
    struct PSHSImmediate : public PSHBase
    {
        PSHSImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~PSHSImmediate() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   PSHU   ==========================================
    struct PSHUImmediate : public PSHBase
    {
        PSHUImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~PSHUImmediate() noexcept = default;

        const std::uint64_t exec() override;
    };

}
