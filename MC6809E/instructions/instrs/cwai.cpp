#include <cstdint>

#include "./cwai.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //---------------------------------------------------------
    CWAIImmediate::CWAIImmediate(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x3C)
    {}

    //---------------------------------------------------------
    const std::uint64_t CWAIImmediate::exec()
    {
        const memory::Byte post_byte{ _hw_arch.load_next_byte() };
        _hw_arch.regCC &= post_byte;
        _hw_arch.push_system_stack(0xff);
        _hw_arch.set_interrupts_wait();

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t CWAIImmediate::get_cycles_count() noexcept
    {
        return 20;
    }

}
