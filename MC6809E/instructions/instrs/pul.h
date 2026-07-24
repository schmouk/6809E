#pragma once

#include <cstdint>

#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   PUL Base Class   ================================
    class PULBase : public BaseInstruction
    {
    public:
        PULBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~PULBase() noexcept = default;

        const std::uint64_t get_cycles_count() noexcept override;

    protected:
        std::uint64_t _pulled_cycles_count{ 0 };
    };


    //=====   PULS   ==========================================
    struct PULSImmediate : public PULBase
    {
        PULSImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~PULSImmediate() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   PULU   ==========================================
    struct PULUImmediate : public PULBase
    {
        PULUImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~PULUImmediate() noexcept = default;

        const std::uint64_t exec() override;
    };

}
