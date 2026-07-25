#include <cstdint>

#include "./asl.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   ASL Base Class   ================================
    //---------------------------------------------------------
    ASLBase::ASLBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte ASLBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void ASLBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_carry((intermediate_value & 0x100) != 0);
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int ASLBase::_evaluate_value(const int value)
    {
        const bool bit7{ (value & 0x80) == 0x80 };
        const bool bit6{ (value & 0x40) == 0x40 };
        _hw_arch.regCC.set_overflow(bit7 != bit6);

        return value << 1;
    }


    //=====   ASLA   ==========================================
    //-----   ASLA Inherent   ---------------------------------
    ASLAInherent::ASLAInherent(archi::HWArchitecture& hw_arch) noexcept
        : ASLBase{ hw_arch, 0x48 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASLAInherent::exec()
    {
        _hw_arch.set_regA(_evaluate(_hw_arch.regA));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASLAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   ASLB   ==========================================
    //-----   ASLB Inherent   ---------------------------------
    ASLBInherent::ASLBInherent(archi::HWArchitecture& hw_arch) noexcept
        : ASLBase{ hw_arch, 0x58 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASLBInherent::exec()
    {
        _hw_arch.set_regB(_evaluate(_hw_arch.regB));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASLBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   ASL Memory   ====================================
    //-----   ASL Direct   ------------------------------------
    //---------------------------------------------------------
    ASLDirect::ASLDirect(archi::HWArchitecture& hw_arch) noexcept
        : ASLBase{ hw_arch, 0x08 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASLDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASLDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   ASL Indexed   -----------------------------------
    //---------------------------------------------------------
    ASLIndexed::ASLIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ASLBase{ hw_arch, 0x68 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASLIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASLIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ASL Extended   ----------------------------------
    //---------------------------------------------------------
    ASLExtended::ASLExtended(archi::HWArchitecture& hw_arch) noexcept
        : ASLBase{ hw_arch, 0x78 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASLExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASLExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
