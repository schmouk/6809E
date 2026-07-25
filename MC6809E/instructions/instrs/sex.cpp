#include <cstdint>

#include "./sex.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //---------------------------------------------------------
    SEXInherent::SEXInherent(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x1D)
    {}

    //---------------------------------------------------------
    const std::uint64_t SEXInherent::exec()
    {
        if ((_hw_arch.regB() & 0x80) == 0) {
            _hw_arch.set_regA(0x00);
            _hw_arch.regCC.set_negative();
            _hw_arch.regCC.set_zero(_hw_arch.regB == 0);
        }
        else {
            _hw_arch.set_regA(0xFF);
            _hw_arch.regCC.clr_negative();
            _hw_arch.regCC.clr_zero();
        }

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t SEXInherent::get_cycles_count() noexcept
    {
        return 2;
    }

}
