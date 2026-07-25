#include <cstdint>

#include "./rti.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //---------------------------------------------------------
    RTIInherent::RTIInherent(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x3B)
    {}

    //---------------------------------------------------------
    const std::uint64_t RTIInherent::exec()
    {
        // pulls CC register value
        _cycles_count = _hw_arch.pull_system_stack_ccr();

        // then pulls all mandatory registers
        if (_hw_arch.regCC.entire_flag())
            _cycles_count += _hw_arch.pull_system_stack(0b1111'1110);
        else
            _cycles_count += _hw_arch.pull_system_stack(0b1000'0000);

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t RTIInherent::get_cycles_count() noexcept
    {
        return 3 + _cycles_count;
    }

}
