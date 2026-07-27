#include <cstdint>

#include "./swi.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   SWI Base Class   ================================
    //---------------------------------------------------------
    SWIBase::SWIBase(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     opcode,
        const memory::MemAddr  vector_addr
    ) noexcept
        : BaseInstruction(hw_arch, opcode)
        , _vect_addr{ vector_addr }
    {}

    //---------------------------------------------------------
    SWIBase::SWIBase(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     opcode1,
        const memory::Byte     opcode2,
        const memory::MemAddr  vector_addr
    ) noexcept
        : BaseInstruction(hw_arch, opcode1, opcode2)
        , _vect_addr{ vector_addr }
    {}

    //---------------------------------------------------------
    const std::uint64_t SWIBase::exec()
    {
        _hw_arch.push_system_stack_all();
        _hw_arch.regPC = _hw_arch.get_word(_vect_addr);
        return get_cycles_count();
    }


    //=====   SWI   ===========================================
    //---------------------------------------------------------
    SWIInherent::SWIInherent(archi::HWArchitecture& hw_arch) noexcept
        : SWIBase(hw_arch, 0x3F, 0xFFFA)
    {}

    //---------------------------------------------------------
    const std::uint64_t SWIInherent::get_cycles_count() noexcept
    {
        return 19;
    }

    //=====   SWI2   ==========================================
    //---------------------------------------------------------
    SWI2Inherent::SWI2Inherent(archi::HWArchitecture& hw_arch) noexcept
        : SWIBase(hw_arch, 0x10, 0x3F, 0xFFF4)
    {}

    //---------------------------------------------------------
    const std::uint64_t SWI2Inherent::get_cycles_count() noexcept
    {
        return 20;
    }
    

    //=====   SWI3   ==========================================
    //---------------------------------------------------------
    SWI3Inherent::SWI3Inherent(archi::HWArchitecture& hw_arch) noexcept
        : SWIBase(hw_arch, 0x11, 0x3F, 0xFFF2)
    {}

    //---------------------------------------------------------
    const std::uint64_t SWI3Inherent::get_cycles_count() noexcept
    {
        return 20;
    }

}