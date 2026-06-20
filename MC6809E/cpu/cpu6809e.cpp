#include "cpu6809e.h"


namespace cpu
{
    //---------------------------------------------------------
    inline const bool CpuCCRegister::carry_flag() const noexcept {
        return get() & C_FLAG;
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::clr_carry() noexcept {
        set(get() & ~C_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_carry() noexcept {
        set(get() | C_FLAG);
    }

    //---------------------------------------------------------
    inline const bool CpuCCRegister::overflow_flag() const noexcept {
        return get() & V_FLAG;
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::clr_overflow() noexcept {
        set(get() & ~V_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_overflow() noexcept {
        set(get() | V_FLAG);
    }

    //---------------------------------------------------------
    inline const bool CpuCCRegister::zero_flag() const noexcept {
        return get() & Z_FLAG;
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::clr_zero() noexcept {
        set(get() & ~Z_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_zero() noexcept {
        set(get() | Z_FLAG);
    }

    //---------------------------------------------------------
    inline const bool CpuCCRegister::negative_flag() const noexcept {
        return get() | N_FLAG;
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::clr_negative() noexcept {
        set(get() & ~N_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_negative() noexcept {
        set(get() | N_FLAG);
    }

    //---------------------------------------------------------
    inline const bool CpuCCRegister::irqmask_flag() const noexcept {
        return get() | I_FLAG;
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::clr_irqmask() noexcept {
        set(get() & ~I_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_irqmask() noexcept {
        set(get() | I_FLAG);
    }

    //---------------------------------------------------------
    inline const bool CpuCCRegister::halfcarry_flag() const noexcept {
        return get() | H_FLAG;
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::clr_halfcarry() noexcept {
        set(get() & ~H_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_halfcarry() noexcept {
        set(get() | H_FLAG);
    }

    //---------------------------------------------------------
    inline const bool CpuCCRegister::firqmask_flag() const noexcept {
        return get() | F_FLAG;
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::clr_firqmask() noexcept {
        set(get() & ~F_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_firqmask() noexcept {
        set(get() | F_FLAG);
    }

    //---------------------------------------------------------
    inline const bool CpuCCRegister::entire_flag() const noexcept {
        return get() | E_FLAG;
    }


    //---------------------------------------------------------
    inline void CpuCCRegister::clr_entire() noexcept {
        set(get() & ~E_FLAG);
    }

    //---------------------------------------------------------
    inline void CpuCCRegister::set_entire() noexcept {
        set(get() | E_FLAG);
    }

}