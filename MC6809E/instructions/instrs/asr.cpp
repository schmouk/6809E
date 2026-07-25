#include <cstdint>

#include "./asr.h"
#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../addressing_modes/indexed_addressing_factory.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"
#include "../../cpu/cpu_registers.h"


namespace instr
{
    //=====   ASR Base Class   ================================
    //---------------------------------------------------------
    ASRBase::ASRBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept
        : BaseInstruction(hw_arch, opcode)
    {}

    //---------------------------------------------------------
    const memory::Byte ASRBase::_evaluate(const int value)
    {
        const int intermediate_value{ _evaluate_value(value) };
        _evaluate_cc_flags(intermediate_value);
        return memory::Byte(intermediate_value & 0xff);
    }

    //---------------------------------------------------------
    void ASRBase::_evaluate_cc_flags(const int intermediate_value)
    {
        _hw_arch.regCC.set_zero((intermediate_value & 0xff) == 0);
        _hw_arch.regCC.set_negative((intermediate_value & 0x80) != 0);
    }

    //---------------------------------------------------------
    const int ASRBase::_evaluate_value(const int value)
    {
        _hw_arch.regCC.set_carry((value & 0x01) != 0);

        const int high_bit{ value & 0x80 };
        return high_bit | (value >> 1);
    }


    //=====   ASRA   ==========================================
    //-----   ASRA Inherent   ---------------------------------
    ASRAInherent::ASRAInherent(archi::HWArchitecture& hw_arch) noexcept
        : ASRBase{ hw_arch, 0x47 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASRAInherent::exec()
    {
        _hw_arch.set_regA(_evaluate(_hw_arch.regA));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASRAInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   ASRB   ==========================================
    //-----   ASRB Inherent   ---------------------------------
    ASRBInherent::ASRBInherent(archi::HWArchitecture& hw_arch) noexcept
        : ASRBase{ hw_arch, 0x57 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASRBInherent::exec()
    {
        _hw_arch.set_regB(_evaluate(_hw_arch.regB));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASRBInherent::get_cycles_count() noexcept
    {
        return 2;
    }


    //=====   ASR Memory   ====================================
    //-----   ASR Direct   ------------------------------------
    //---------------------------------------------------------
    ASRDirect::ASRDirect(archi::HWArchitecture& hw_arch) noexcept
        : ASRBase{ hw_arch, 0x07 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASRDirect::exec()
    {
        const memory::Byte value_low_addr{ _hw_arch.load_next_byte() };
        const memory::MemAddr mem_addr{ _hw_arch.get_directpage_addr(value_low_addr) };
        const memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASRDirect::get_cycles_count() noexcept
    {
        return 6;
    }


    //-----   ASR Indexed   -----------------------------------
    //---------------------------------------------------------
    ASRIndexed::ASRIndexed(archi::HWArchitecture& hw_arch) noexcept
        : ASRBase{ hw_arch, 0x67 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASRIndexed::exec()
    {
        _indexed_mode_ptr = addr::make_indexed_addressing_class(_hw_arch);

        _indexed_mode_ptr->set_addressed_byte(
            _evaluate(_indexed_mode_ptr->get_addressed_byte())
        );

        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASRIndexed::get_cycles_count() noexcept
    {
        return 6 + _indexed_mode_ptr->get_byte_cycles();
    }


    //-----   ASR Extended   ----------------------------------
    //---------------------------------------------------------
    ASRExtended::ASRExtended(archi::HWArchitecture& hw_arch) noexcept
        : ASRBase{ hw_arch, 0x77 }
    {}

    //---------------------------------------------------------
    const std::uint64_t ASRExtended::exec()
    {
        memory::MemAddr mem_addr{ memory::MemAddr(_hw_arch.load_next_word()) };
        memory::Byte mem_value{ _hw_arch.get_byte(mem_addr) };

        _hw_arch.set_byte(mem_addr, _evaluate(mem_value));
        return get_cycles_count();
    }

    //---------------------------------------------------------
    const std::uint64_t ASRExtended::get_cycles_count() noexcept
    {
        return 7;
    }

}
