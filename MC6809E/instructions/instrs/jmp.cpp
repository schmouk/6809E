#include <cstdint>

#include "./jmp.h"

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   JMP Memory   ====================================
    //-----   JMP Direct   ------------------------------------
    //---------------------------------------------------------
    JMPDirect::JMPDirect(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction{ hw_arch, 0x0E }
    {}

    //---------------------------------------------------------
    const std::uint64_t JMPDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _hw_arch.regPC = _hw_arch.get_word(mem_addr);

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t JMPDirect::get_cycles_count() noexcept
    {
        return 3;
    }


    //-----   JMP Indexed   -----------------------------------
    //---------------------------------------------------------
    JMPIndexed::JMPIndexed(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction{ hw_arch, 0x6E }
    {}

    //---------------------------------------------------------
    const std::uint64_t JMPIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);
        _hw_arch.regPC = _indexed_mode_ptr->get_addressed_word();  // Notice: Not sure of this

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t JMPIndexed::get_cycles_count() noexcept
    {
        return 3 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   JMP Extended   ----------------------------------
    //---------------------------------------------------------
    JMPExtended::JMPExtended(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction{ hw_arch, 0x7E }
    {}

    //---------------------------------------------------------
    const std::uint64_t JMPExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        _hw_arch.regPC = _hw_arch.get_word(mem_addr);

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t JMPExtended::get_cycles_count() noexcept
    {
        return 4;
    }

}
