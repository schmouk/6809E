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


    //=====   BEQ / LBEQ   ====================================
    //---------------------------------------------------------
    struct BEQ : public ShortRelativeBranchingBase
    {
        BEQ(archi::HWArchitecture& hw_arch);
        virtual ~BEQ() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBEQ : public LongRelativeBranchingBase
    {
        LBEQ(archi::HWArchitecture& hw_arch);
        virtual ~LBEQ() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BGE / LBGE   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BGE : public ShortRelativeBranchingBase
    {
        BGE(archi::HWArchitecture& hw_arch);
        virtual ~BGE() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBGE : public LongRelativeBranchingBase
    {
        LBGE(archi::HWArchitecture& hw_arch);
        virtual ~LBGE() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BGT / LBGT   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BGT : public ShortRelativeBranchingBase
    {
        BGT(archi::HWArchitecture& hw_arch);
        virtual ~BGT() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBGT : public LongRelativeBranchingBase
    {
        LBGT(archi::HWArchitecture& hw_arch);
        virtual ~LBGT() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BHI / LBHI   ====================================
    // Notice: unsigned comparisons
    //---------------------------------------------------------
    struct BHI : public ShortRelativeBranchingBase
    {
        BHI(archi::HWArchitecture& hw_arch);
        virtual ~BHI() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBHI : public LongRelativeBranchingBase
    {
        LBHI(archi::HWArchitecture& hw_arch);
        virtual ~LBHI() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BHS / LBHS   ====================================
    // Notice: unsigned comparisons
    using BHS  = BCC;
    using LBHS = LBCC;


    //=====   BLE / LBLE   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BLE : public ShortRelativeBranchingBase
    {
        BLE(archi::HWArchitecture& hw_arch);
        virtual ~BLE() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBLE : public LongRelativeBranchingBase
    {
        LBLE(archi::HWArchitecture& hw_arch);
        virtual ~LBLE() noexcept = default;

        const std::uint64_t exec() override;
    };







    //=====   BNE / LBNE   ====================================
    //---------------------------------------------------------
    struct BNE : public ShortRelativeBranchingBase
    {
        BNE(archi::HWArchitecture& hw_arch);
        virtual ~BNE() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBNE : public LongRelativeBranchingBase
    {
        LBNE(archi::HWArchitecture& hw_arch);
        virtual ~LBNE() noexcept = default;

        const std::uint64_t exec() override;
    };

}
