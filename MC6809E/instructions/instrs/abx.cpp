#include <cstdint>

#include "./abx.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //===== Instruction ABX   =================================
    //---------------------------------------------------------
    ABX::ABX() noexcept
        : BaseInstruction{ 0x3a }
    {}

    //---------------------------------------------------------
    void  ABX::exec(archi::HWArchitecture& hw_arch)
    {
        hw_arch.regX += hw_arch.regB;
    }

    //---------------------------------------------------------
    const std::uint64_t ABX::get_cycles_count() noexcept
    {
        return 3;
    }

}
