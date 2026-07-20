#include <cstdint>

#include "./abx.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //===== Instruction ABX   =================================
    //---------------------------------------------------------
    ABX::ABX(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction{ hw_arch, 0x3a }
    {}

    //---------------------------------------------------------
    void  ABX::exec()
    {
        _hw_arch.regX += _hw_arch.regB;
    }

    //---------------------------------------------------------
    const std::uint64_t ABX::get_cycles_count() noexcept
    {
        return 3;
    }

}
