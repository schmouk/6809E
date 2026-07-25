#include <cstdint>

#include "./rts.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //---------------------------------------------------------
    RTSInherent::RTSInherent(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x39)
    {}

    //---------------------------------------------------------
    const std::uint64_t RTSInherent::exec()
    {
        (void)_hw_arch.pull_system_stack_pcr();
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t RTSInherent::get_cycles_count() noexcept
    {
        return 5;
    }

}
