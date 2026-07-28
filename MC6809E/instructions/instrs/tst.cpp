#include <cstdint>

#include "./tst.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   TST Base Class   ================================
    //---------------------------------------------------------
    TSTBase::TSTBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    void TSTBase::_evaluate_cc_flags(const memory::Byte value)
    {
        _hw_arch.regCC.set_zero(value == 0);
        _hw_arch.regCC.set_negative((value & 0x80) != 0);
    }


    //=====   TSTA   ==========================================
    //-----   TSTA Inherent   ---------------------------------
    TSTAInherent::TSTAInherent(archi::HWArchitecture& hw_arch) noexcept
        : TSTBase{ hw_arch, 0x4D }
    {}

    //---------------------------------------------------------
    const std::uint64_t TSTAInherent::exec()
    {
        _evaluate_cc_flags(_hw_arch.regA);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t TSTAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   TSTB   ==========================================
    //-----   TSTB Inherent   ---------------------------------
    TSTBInherent::TSTBInherent(archi::HWArchitecture& hw_arch) noexcept
        : TSTBase{ hw_arch, 0x5D }
    {}

    //---------------------------------------------------------
    const std::uint64_t TSTBInherent::exec()
    {
        _evaluate_cc_flags(_hw_arch.regB);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t TSTBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   TST Memory   ====================================
    //-----   TST Direct   ------------------------------------
    //---------------------------------------------------------
    TSTDirect::TSTDirect(archi::HWArchitecture& hw_arch) noexcept
        : TSTBase{ hw_arch, 0x0D }
    {}

    //---------------------------------------------------------
    const std::uint64_t TSTDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _evaluate_cc_flags(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t TSTDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   TST Indexed   -----------------------------------
    //---------------------------------------------------------
    TSTIndexed::TSTIndexed(archi::HWArchitecture& hw_arch) noexcept
        : TSTBase{ hw_arch, 0x6D }
    {}

    //---------------------------------------------------------
    const std::uint64_t TSTIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _evaluate_cc_flags(_indexed_mode_ptr->get_addressed_byte());
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t TSTIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   TST Extended   ----------------------------------
    //---------------------------------------------------------
    TSTExtended::TSTExtended(archi::HWArchitecture& hw_arch) noexcept
        : TSTBase{ hw_arch, 0x7D }
    {}

    //---------------------------------------------------------
    const std::uint64_t TSTExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _evaluate_cc_flags(mem_value);
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t TSTExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
