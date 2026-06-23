#include <cstdint>
#include "cpu6809e.h"

#include "../exceptions/exceptions.h"


namespace cpu
{
    //---------------------------------------------------------
    const memory::MemAddr MicroprocUnit::get_directpage_addr(const memory::Byte addr_low) const noexcept
    {
        return (memory::MemAddr(regDP()) << 8) | memory::MemAddr(addr_low);
    }

    //---------------------------------------------------------
    const memory::Word MicroprocUnit::get_reg_value(const cpu::EReg reg_index) const
    {
        switch (reg_index) {
            case cpu::EReg::D:
                return regD;
            case cpu::EReg::X:
                return regX;
            case cpu::EReg::Y:
                return regY;
            case cpu::EReg::U:
                return regU;
            case cpu::EReg::S:
                return regS;
            case cpu::EReg::PC:
                return regPC;
            case cpu::EReg::A:
                return regA;
            case cpu::EReg::B:
                return regB;
            case cpu::EReg::CC:
                return regCC;
            case cpu::EReg::DP:
                return regDP;
            default:
                throw except::InvalidRegisterCodeAddressingModeException(std::uint8_t(reg_index));
        }
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::carry_flag() const noexcept {
        return get() & C_FLAG;
    }

    //---------------------------------------------------------
    void CpuCCRegister::clr_carry() noexcept {
        set(get() & ~C_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_carry() noexcept {
        set(get() | C_FLAG);
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::overflow_flag() const noexcept {
        return get() & V_FLAG;
    }

    //---------------------------------------------------------
    void CpuCCRegister::clr_overflow() noexcept {
        set(get() & ~V_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_overflow() noexcept {
        set(get() | V_FLAG);
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::zero_flag() const noexcept {
        return get() & Z_FLAG;
    }

    //---------------------------------------------------------
    void CpuCCRegister::clr_zero() noexcept {
        set(get() & ~Z_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_zero() noexcept {
        set(get() | Z_FLAG);
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::negative_flag() const noexcept {
        return get() | N_FLAG;
    }

    //---------------------------------------------------------
    void CpuCCRegister::clr_negative() noexcept {
        set(get() & ~N_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_negative() noexcept {
        set(get() | N_FLAG);
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::irqmask_flag() const noexcept {
        return get() | I_FLAG;
    }

    //---------------------------------------------------------
    void CpuCCRegister::clr_irqmask() noexcept {
        set(get() & ~I_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_irqmask() noexcept {
        set(get() | I_FLAG);
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::halfcarry_flag() const noexcept {
        return get() | H_FLAG;
    }

    //---------------------------------------------------------
    void CpuCCRegister::clr_halfcarry() noexcept {
        set(get() & ~H_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_halfcarry() noexcept {
        set(get() | H_FLAG);
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::firqmask_flag() const noexcept {
        return get() | F_FLAG;
    }

    //---------------------------------------------------------
    void CpuCCRegister::clr_firqmask() noexcept {
        set(get() & ~F_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_firqmask() noexcept {
        set(get() | F_FLAG);
    }

    //---------------------------------------------------------
    const bool CpuCCRegister::entire_flag() const noexcept {
        return get() | E_FLAG;
    }


    //---------------------------------------------------------
    void CpuCCRegister::clr_entire() noexcept {
        set(get() & ~E_FLAG);
    }

    //---------------------------------------------------------
    void CpuCCRegister::set_entire() noexcept {
        set(get() | E_FLAG);
    }

}