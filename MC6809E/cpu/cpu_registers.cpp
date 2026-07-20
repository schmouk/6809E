#include "./cpu_registers.h"
#include "../memory/types.h"


namespace cpu
{

    //---------------------------------------------------------
    const bool CPUCCRegister::carry_flag() const noexcept {
        return (get() & C_FLAG) == C_FLAG;
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
    void CPUCCRegister::set_carry(const bool flag_value) noexcept
    {
        if (flag_value) set_carry(); else clr_carry();
    }

    //---------------------------------------------------------
    inline const memory::Byte CPUCCRegister::carry_value() const noexcept {
        return memory::Byte(carry_flag());
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::overflow_flag() const noexcept {
        return (get() & V_FLAG) == V_FLAG;
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
    void CPUCCRegister::set_overflow(const bool flag_value) noexcept
    {
        if (flag_value) set_overflow(); else clr_overflow();
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::zero_flag() const noexcept {
        return (get() & Z_FLAG) == Z_FLAG;
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
    void CPUCCRegister::set_zero(const bool flag_value) noexcept
    {
        if (flag_value) set_zero(); else clr_zero();
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::negative_flag() const noexcept {
        return (get() & N_FLAG) == N_FLAG;
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
    void CPUCCRegister::set_negative(const bool flag_value) noexcept
    {
        if (flag_value) set_negative(); else clr_negative();
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::irqmask_flag() const noexcept {
        return (get() & I_FLAG) == I_FLAG;
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
        return (get() & H_FLAG) == H_FLAG;
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
    void CPUCCRegister::set_halfcarry(const bool flag_value) noexcept
    {
        if (flag_value) set_halfcarry(); else clr_halfcarry();
    }

    //---------------------------------------------------------
    const bool CPUCCRegister::firqmask_flag() const noexcept {
        return (get() & F_FLAG) == F_FLAG;
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
        return (get() & E_FLAG) == E_FLAG;
    }


    //---------------------------------------------------------
    void CPUCCRegister::clr_entire() noexcept {
        set(get() & ~E_FLAG);
    }

    //---------------------------------------------------------
    void CPUCCRegister::set_entire() noexcept {
        set(get() | E_FLAG);
    }

    //---------------------------------------------------------
    inline void CPUCCRegister::clr() noexcept
    {
        set(get() & CLR_MASK);
    }

}