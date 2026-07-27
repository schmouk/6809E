#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   SWI Base Class   ================================
    class SWIBase : public BaseInstruction
    {
    public:
        SWIBase(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     opcode,
            const memory::MemAddr  vector_addr
        ) noexcept;

        SWIBase(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     opcode1,
            const memory::Byte     opcode2,
            const memory::MemAddr  vector_addr
        ) noexcept;

        virtual ~SWIBase() noexcept = default;

        const std::uint64_t exec() override;

    private:
        memory::MemAddr _vect_addr{ 0x0000 };
    };


    //=====   SWI   ===========================================
    struct SWIInherent : public SWIBase
    {
        SWIInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SWIInherent() noexcept = default;

        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   SWI2   ==========================================
    struct SWI2Inherent : public SWIBase
    {
        SWI2Inherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SWI2Inherent() noexcept = default;

        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   SWI3   ==========================================
    struct SWI3Inherent : public SWIBase
    {
        SWI3Inherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SWI3Inherent() noexcept = default;

        const std::uint64_t get_cycles_count() noexcept override;
    };

}
