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


    //=====   BLO / LBLO   ====================================
    // Notice: unsigned comparisons
    using BLO = BCS;
    using LBLO = LBCS;


    //=====   BLS / LBLS   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BLS : public ShortRelativeBranchingBase
    {
        BLS(archi::HWArchitecture& hw_arch);
        virtual ~BLS() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBLS : public LongRelativeBranchingBase
    {
        LBLS(archi::HWArchitecture& hw_arch);
        virtual ~LBLS() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BLT / LBLT   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BLT : public ShortRelativeBranchingBase
    {
        BLT(archi::HWArchitecture& hw_arch);
        virtual ~BLT() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBLT : public LongRelativeBranchingBase
    {
        LBLT(archi::HWArchitecture& hw_arch);
        virtual ~LBLT() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BMI / LBMI   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BMI : public ShortRelativeBranchingBase
    {
        BMI(archi::HWArchitecture& hw_arch);
        virtual ~BMI() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBMI : public LongRelativeBranchingBase
    {
        LBMI(archi::HWArchitecture& hw_arch);
        virtual ~LBMI() noexcept = default;

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


    //=====   BPL / LBPL   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BPL : public ShortRelativeBranchingBase
    {
        BPL(archi::HWArchitecture& hw_arch);
        virtual ~BPL() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBPL : public LongRelativeBranchingBase
    {
        LBPL(archi::HWArchitecture& hw_arch);
        virtual ~LBPL() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BRA / LBRA   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BRA : public ShortRelativeBranchingBase
    {
        BRA(archi::HWArchitecture& hw_arch);
        virtual ~BRA() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBRA : public LongRelativeBranchingBase
    {
        LBRA(archi::HWArchitecture& hw_arch);
        virtual ~LBRA() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   BRN / LBRN   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BRN : public ShortRelativeBranchingBase
    {
        BRN(archi::HWArchitecture& hw_arch);
        virtual ~BRN() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBRN : public LongRelativeBranchingBase
    {
        LBRN(archi::HWArchitecture& hw_arch);
        virtual ~LBRN() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BSR / LBSR   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BSR : public ShortRelativeBranchingBase
    {
        BSR(archi::HWArchitecture& hw_arch);
        virtual ~BSR() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBSR : public LongRelativeBranchingBase
    {
        LBSR(archi::HWArchitecture& hw_arch);
        virtual ~LBSR() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BVC / LBVC   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BVC : public ShortRelativeBranchingBase
    {
        BVC(archi::HWArchitecture& hw_arch);
        virtual ~BVC() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBVC : public LongRelativeBranchingBase
    {
        LBVC(archi::HWArchitecture& hw_arch);
        virtual ~LBVC() noexcept = default;

        const std::uint64_t exec() override;
    };


    //=====   BVS / LBVS   ====================================
    // Notice: signed comparisons
    //---------------------------------------------------------
    struct BVS : public ShortRelativeBranchingBase
    {
        BVS(archi::HWArchitecture& hw_arch);
        virtual ~BVS() noexcept = default;

        const std::uint64_t exec() override;
    };

    //---------------------------------------------------------
    struct LBVS : public LongRelativeBranchingBase
    {
        LBVS(archi::HWArchitecture& hw_arch);
        virtual ~LBVS() noexcept = default;

        const std::uint64_t exec() override;
    };

}
