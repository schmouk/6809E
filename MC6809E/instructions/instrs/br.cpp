#include <cstdint>

#include "./br.h"

#include "../base_instruction.h"

#include "../../addressing_modes/relative_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   Short Relative Branching Base   =================
    //---------------------------------------------------------
    ShortRelativeBranchingBase::ShortRelativeBranchingBase(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     opcode
    )
        : BaseInstruction(hw_arch, opcode)
        , addr::ShortRelativeAddressing(hw_arch)
    {}

    //---------------------------------------------------------
    const std::uint64_t ShortRelativeBranchingBase::_exec(const bool branch_taken)
    {
        if (branch_taken) {
            _hw_arch.regPC += get_offset();  // Notice: evaluated at ShortRelativeAddressing construction time
        }

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ShortRelativeBranchingBase::get_cycles_count() noexcept
    {
        return 3;
    }


    //=====   Long Relative Branching Base   ==================
    //---------------------------------------------------------
    LongRelativeBranchingBase::LongRelativeBranchingBase(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     opcode
    )
        : BaseInstruction(hw_arch, opcode)
        , addr::LongRelativeAddressing(hw_arch)
    {}

    //---------------------------------------------------------
    LongRelativeBranchingBase::LongRelativeBranchingBase(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     opcode1,
        const memory::Byte     opcode2
    )
        : BaseInstruction(hw_arch, opcode1, opcode2)
        , addr::LongRelativeAddressing(hw_arch)
    {}

    //---------------------------------------------------------
    const std::uint64_t LongRelativeBranchingBase::_exec(const bool branch_taken)
    {
        if (branch_taken) {
            _hw_arch.regPC += get_offset();  // Notice: evaluated at LongRelativeAddressing construction time
        }

        return get_cycles_count() + branch_taken;  // Notice: similar to " + (branch_taken ? 1 : 0);"
    }

    //---------------------------------------------------------
    const std::uint64_t LongRelativeBranchingBase::get_cycles_count() noexcept
    {
        return 5;
    }


    //=====   BCC / LBCC   ====================================
    //---------------------------------------------------------
    BCC::BCC(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x24)
    {}

    //---------------------------------------------------------
    const std::uint64_t BCC::exec()
    {
        return _exec(!_hw_arch.regCC.carry_flag());
    }

    //---------------------------------------------------------
    LBCC::LBCC(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x24)
    {}

    //---------------------------------------------------------
    const std::uint64_t LBCC::exec()
    {
        return _exec(!_hw_arch.regCC.carry_flag());
    }


    //=====   BCS / LBCS   ====================================
    //---------------------------------------------------------
    BCS::BCS(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x25)
    {}

    //---------------------------------------------------------
    const std::uint64_t BCS::exec()
    {
        return _exec(_hw_arch.regCC.carry_flag());
    }

    //---------------------------------------------------------
    LBCS::LBCS(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x25)
    {}

    //---------------------------------------------------------
    const std::uint64_t LBCS::exec()
    {
        return _exec(_hw_arch.regCC.carry_flag());
    }


    //=====   BEQ / LBEQ   ====================================
    //---------------------------------------------------------
    BEQ::BEQ(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x27)
    {}

    //---------------------------------------------------------
    const std::uint64_t BEQ::exec()
    {
        return _exec(_hw_arch.regCC.zero_flag());
    }

    //---------------------------------------------------------
    LBEQ::LBEQ(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x27)
    {}

    //---------------------------------------------------------
    const std::uint64_t LBEQ::exec()
    {
        return _exec(_hw_arch.regCC.zero_flag());
    }


    //=====   BGE / LBGE   ====================================
    //---------------------------------------------------------
    BGE::BGE(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x2C)
    {}

    //---------------------------------------------------------
    const std::uint64_t BGE::exec()
    {
        return _exec(!(_hw_arch.regCC.negative_flag() ^ _hw_arch.regCC.overflow_flag()));
    }

    //---------------------------------------------------------
    LBGE::LBGE(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x2C)
    {}

    //---------------------------------------------------------
    const std::uint64_t LBGE::exec()
    {
        return _exec(!(_hw_arch.regCC.negative_flag() ^ _hw_arch.regCC.overflow_flag()));
    }


    //=====   BGT / LBGT   ====================================
    //---------------------------------------------------------
    BGT::BGT(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x2E)
    {}

    //---------------------------------------------------------
    const std::uint64_t BGT::exec()
    {
        return _exec(
            !_hw_arch.regCC.zero_flag() &&
            !(_hw_arch.regCC.negative_flag() ^ _hw_arch.regCC.overflow_flag())
        );
    }

    //---------------------------------------------------------
    LBGT::LBGT(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x2E)
    {}

    //---------------------------------------------------------
    const std::uint64_t LBGT::exec()
    {
        return _exec(
            !_hw_arch.regCC.zero_flag() &&
            !(_hw_arch.regCC.negative_flag() ^ _hw_arch.regCC.overflow_flag())
        );
    }


    //=====   BHI / LBHI   ====================================
    //---------------------------------------------------------
    BHI::BHI(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x22)
    {}

    //---------------------------------------------------------
    const std::uint64_t BHI::exec()
    {
        return _exec(!_hw_arch.regCC.zero_flag() && !_hw_arch.regCC.negative_flag());
    }

    //---------------------------------------------------------
    LBHI::LBHI(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x22)
    {}

    //---------------------------------------------------------
    const std::uint64_t LBHI::exec()
    {
        return _exec(!_hw_arch.regCC.zero_flag() && !_hw_arch.regCC.negative_flag());
    }


    //=====   BLE / LBLE   ====================================
    //---------------------------------------------------------
    BLE::BLE(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x2F)
    {}

    //---------------------------------------------------------
    const std::uint64_t BLE::exec()
    {
        return _exec(
            _hw_arch.regCC.zero_flag() ||
            (_hw_arch.regCC.negative_flag() ^ _hw_arch.regCC.overflow_flag())
        );
    }

    //---------------------------------------------------------
    LBLE::LBLE(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x2F)
    {}

    //---------------------------------------------------------
    const std::uint64_t LBLE::exec()
    {
        return _exec(
            _hw_arch.regCC.zero_flag() ||
            (_hw_arch.regCC.negative_flag() ^ _hw_arch.regCC.overflow_flag())
        );
    }








    //=====   BNE / LBNE   ====================================
    //---------------------------------------------------------
    BNE::BNE(archi::HWArchitecture& hw_arch)
        : ShortRelativeBranchingBase(hw_arch, 0x27)
    {
    }

    //---------------------------------------------------------
    const std::uint64_t BNE::exec()
    {
        return _exec(!_hw_arch.regCC.zero_flag());
    }

    //---------------------------------------------------------
    LBNE::LBNE(archi::HWArchitecture& hw_arch)
        : LongRelativeBranchingBase(hw_arch, 0x10, 0x27)
    {
    }

    //---------------------------------------------------------
    const std::uint64_t LBNE::exec()
    {
        return _exec(!_hw_arch.regCC.zero_flag());
    }

}
