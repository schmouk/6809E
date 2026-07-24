#include <cstdint>

#include "./jsr.h"

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   JSR Memory   ====================================
    //-----   JSR Direct   ------------------------------------
    //---------------------------------------------------------
    JSRDirect::JSRDirect(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction{ hw_arch, 0x9D }
    {}

    //---------------------------------------------------------
    const std::uint64_t JSRDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };

        _hw_arch.push_system_stack_pcr();
        _hw_arch.regPC = _hw_arch.get_word(mem_addr);

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t JSRDirect::get_cycles_count() noexcept
    {
        return 7;
    }


    //-----   JSR Indexed   -----------------------------------
    //---------------------------------------------------------
    JSRIndexed::JSRIndexed(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction{ hw_arch, 0xAD }
    {}

    //---------------------------------------------------------
    const std::uint64_t JSRIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _hw_arch.push_system_stack_pcr();
        _hw_arch.regPC = _indexed_mode_ptr->get_addressed_word();  // Notice: Not sure of this

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t JSRIndexed::get_cycles_count() noexcept
    {
        return 7 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   JSR Extended   ----------------------------------
    //---------------------------------------------------------
    JSRExtended::JSRExtended(archi::HWArchitecture& hw_arch) noexcept
        : BaseInstruction{ hw_arch, 0xBD }
    {}

    //---------------------------------------------------------
    const std::uint64_t JSRExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };

        _hw_arch.push_system_stack_pcr();
        _hw_arch.regPC = _hw_arch.get_word(mem_addr);

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t JSRExtended::get_cycles_count() noexcept
    {
        return 8;
    }

}
