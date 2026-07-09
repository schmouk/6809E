#include "./cpu_registers.h"


namespace cpu
{

    //---------------------------------------------------------
    const bool CPUCCRegister::carry_flag() const noexcept {
        return get() & C_FLAG;
    }

    //---------------------------------------------------------
    void CPUCCRegister::clr_carry() noexcept {
        set(get() & ~C_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_carry() noexcept {
        set(get() | C_FLAG);
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::overflow_flag() const noexcept {
        return get() & V_FLAG;
    }

    //---------------------------------------------------------
    void CPUCCRegister::clr_overflow() noexcept {
        set(get() & ~V_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_overflow() noexcept {
        set(get() | V_FLAG);
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::zero_flag() const noexcept {
        return get() & Z_FLAG;
    }

    //---------------------------------------------------------
    void CPUCCRegister::clr_zero() noexcept {
        set(get() & ~Z_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_zero() noexcept {
        set(get() | Z_FLAG);
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::negative_flag() const noexcept {
        return get() | N_FLAG;
    }

    //---------------------------------------------------------
    void CPUCCRegister::clr_negative() noexcept {
        set(get() & ~N_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_negative() noexcept {
        set(get() | N_FLAG);
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::irqmask_flag() const noexcept {
        return get() | I_FLAG;
    }

    //---------------------------------------------------------
    void CPUCCRegister::clr_irqmask() noexcept {
        set(get() & ~I_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_irqmask() noexcept {
        set(get() | I_FLAG);
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::halfcarry_flag() const noexcept {
        return get() | H_FLAG;
    }

    //---------------------------------------------------------
    void CPUCCRegister::clr_halfcarry() noexcept {
        set(get() & ~H_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_halfcarry() noexcept {
        set(get() | H_FLAG);
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::firqmask_flag() const noexcept {
        return get() | F_FLAG;
    }

    //---------------------------------------------------------
    void CPUCCRegister::clr_firqmask() noexcept {
        set(get() & ~F_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_firqmask() noexcept {
        set(get() | F_FLAG);
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::entire_flag() const noexcept {
        return get() | E_FLAG;
    }


    //---------------------------------------------------------
    void CPUCCRegister::clr_entire() noexcept {
        set(get() & ~E_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_entire() noexcept {
        set(get() | E_FLAG);
    }

}