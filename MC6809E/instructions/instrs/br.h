#pragma once

#include <cstdint>

#include "../base_instruction.h"

#include "../../addressing_modes/relative_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   Short Relative Branching Base   =================
    class ShortRelativeBranchingBase : public BaseInstruction, public addr::ShortRelativeAddressing
    {
    public:
        ShortRelativeBranchingBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode);
        virtual ~ShortRelativeBranchingBase() noexcept = default;
        const std::uint64_t get_cycles_count() noexcept override;

    protected:
        const std::uint64_t _exec(const bool branch_taken);
    };


    //=====   Long Relative Branching Base   ==================
    struct LongRelativeBranchingBase : public BaseInstruction, public addr::LongRelativeAddressing
    {
        LongRelativeBranchingBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode);
        LongRelativeBranchingBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode1, const memory::Byte opcode2);
        virtual ~LongRelativeBranchingBase() noexcept = default;
        const std::uint64_t get_cycles_count() noexcept override;

    protected:
        const std::uint64_t _exec(const bool branch_taken);
    };


    //=====   BCC / LBCC   ====================================
    //---------------------------------------------------------
    struct BCC : public ShortRelativeBranchingBase
    {
        BCC(archi::HWArchitecture& hw_arch);
        virtual ~BCC() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBCC : public LongRelativeBranchingBase
    {
        LBCC(archi::HWArchitecture& hw_arch);
        virtual ~LBCC() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BCS / LBCS   ====================================
    //---------------------------------------------------------
    struct BCS : public ShortRelativeBranchingBase
    {
        BCS(archi::HWArchitecture& hw_arch);
        virtual ~BCS() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBCS : public LongRelativeBranchingBase
    {
        LBCS(archi::HWArchitecture& hw_arch);
        virtual ~LBCS() noexcept = default;

        const std::uint64_t exec() override;
    };

}
