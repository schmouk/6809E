#include <cstdint>

#include "./daa.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //---------------------------------------------------------
    DAAInherent::DAAInherent(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction(hw_arch, 0x19)
    {}

    //---------------------------------------------------------
    const std::uint64_t DAAInherent::exec()
    {
        memory::Byte add_decimal_mask{ memory::Byte(_hw_arch.regCC.carry_flag() ? 0x60 : 0x00) };
        if (_hw_arch.regCC.halfcarry_flag())
            add_decimal_mask += 0x06;
        _hw_arch.regA += add_decimal_mask;

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t DAAInherent::get_cycles_count() noexcept
    {
        return 2;
    }

}
