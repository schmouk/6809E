#pragma once

/**
* This file defines the MC6809E microprocessor registers emulation.
*
* It defines next classes:
* - template<typename IntT> class CPURegisterT;
* - using CPURegister8bits  = CPURegisterT<std::uint8_t>;
* - using CPURegister16bits = CPURegisterT<std::uint16_t>;
* - struct CPUCCRegister;
*/

#include <cstdint>
#include <type_traits>


namespace cpu
{
    //=====   The Microprocessing Registers   =================
    //---------------------------------------------------------
    struct CPURegister {};  // Notice: the base class for every CPU register


    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    class CPURegisterT : private CPURegister
    {
    public:
        //-----   Constructors / Destructors   ----------------
        inline CPURegisterT() noexcept = default;
        inline virtual ~CPURegisterT() noexcept = default;

        inline CPURegisterT(const IntT value) noexcept;

        CPURegisterT(const CPURegisterT&) = delete;   // Can't copy content of registers
        CPURegisterT(CPURegisterT&&) = delete;        // Can't move content of registers


        //-----   Operators   ---------------------------------
        inline const CPURegisterT& operator= (const IntT new_value) noexcept;

        inline const CPURegisterT  operator+  (const IntT offset_value) noexcept;
        inline const CPURegisterT& operator+= (const IntT offset_value) noexcept;

        inline const CPURegisterT  operator-  (const IntT offset_value) noexcept;
        inline const CPURegisterT& operator-= (const IntT offset_value) noexcept;

        inline const IntT operator++() noexcept;    // Notice: pre-increment
        inline const IntT operator++(int) noexcept; // Notice: post-increment

        inline const IntT operator--() noexcept;    // Notice: pre-decrement
        inline const IntT operator--(int) noexcept; // Notice: post-decrement

        inline operator IntT() noexcept;
        inline operator const IntT() const noexcept;

        inline const IntT operator() () const noexcept; // Gets the value of the register content


        //-----   Operations   --------------------------------
        inline const IntT get() const noexcept;         // Gets the value of the register content
        inline void       set(const IntT val) noexcept; // Sets value of the register content


    private:
        IntT _value{ 0 };

    };


    //-----   Specializations   -------------------------------
    using CPURegister8bits = CPURegisterT<std::uint8_t>;    //  8-bits wide registers
    using CPURegister16bits = CPURegisterT<std::uint16_t>;   // 16-bits wide registers
    using CPUIndexRegister = CPURegisterT<std::uint16_t>;   // 16-bits wide indexing registers


    //=====   Registers Indexes   =============================
    enum class EReg : std::uint8_t {
        D = 0b0000,
        X,
        Y,
        U,
        S,
        PC,
        A = 0b1000,
        B,
        CC,
        DP
    };


    //=====   Deeper Specialization - the CC Register   =======
    struct CPUCCRegister : public CPURegister8bits
    {
        //-----   Constructors / Destructors   ----------------
        inline CPUCCRegister() noexcept = default;
        inline virtual ~CPUCCRegister() noexcept = default;

        CPUCCRegister(const CPUCCRegister&) = delete;       // Can't copy content of registers
        CPUCCRegister(CPUCCRegister&&) = delete;            // Can't move content of registers

        CPUCCRegister& operator= (const CPUCCRegister&) = delete;
        CPUCCRegister& operator= (CPUCCRegister&&) = delete;


        //-----   Operations   --------------------------------
        inline const bool carry_flag() const noexcept;      // C flag - Bit 0
        inline void clr_carry() noexcept;
        inline void set_carry() noexcept;

        inline const bool overflow_flag() const noexcept;   // V flag - Bit 1
        inline void clr_overflow() noexcept;
        inline void set_overflow() noexcept;

        inline const bool zero_flag() const noexcept;       // Z flag - Bit 2
        inline void clr_zero() noexcept;
        inline void set_zero() noexcept;

        inline const bool negative_flag() const noexcept;   // N flag - bit 3
        inline void clr_negative() noexcept;
        inline void set_negative() noexcept;

        inline const bool irqmask_flag() const noexcept;    // I flag - bit 4
        inline void clr_irqmask() noexcept;
        inline void set_irqmask() noexcept;

        inline const bool halfcarry_flag() const noexcept;  // H flag - bit 5
        inline void clr_halfcarry() noexcept;
        inline void set_halfcarry() noexcept;

        inline const bool firqmask_flag() const noexcept;   // F flag - bit 6
        inline void clr_firqmask() noexcept;
        inline void set_firqmask() noexcept;

        inline const bool entire_flag() const noexcept;     // E flag - bit 7
        inline void clr_entire() noexcept;
        inline void set_entire() noexcept;


        //-----   Bits Masks   --------------------------------
        inline static constexpr std::uint8_t C_FLAG = 0x01;
        inline static constexpr std::uint8_t V_FLAG = 0x02;
        inline static constexpr std::uint8_t Z_FLAG = 0x04;
        inline static constexpr std::uint8_t N_FLAG = 0x08;
        inline static constexpr std::uint8_t I_FLAG = 0x10;
        inline static constexpr std::uint8_t H_FLAG = 0x20;
        inline static constexpr std::uint8_t F_FLAG = 0x40;
        inline static constexpr std::uint8_t E_FLAG = 0x80;

    };


    //=====   IMPLEMENTATIONS   ===============================
    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    CPURegisterT<IntT>::CPURegisterT(const IntT value) noexcept
        : _value(value)
    {
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::get() const noexcept
    {
        return _value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    void CPURegisterT<IntT>::set(const IntT val) noexcept
    {
        _value = val;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT>& CPURegisterT<IntT>::operator= (const IntT new_value) noexcept
    {
        _value = new_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT> CPURegisterT<IntT>::operator+ (const IntT offset_value) noexcept
    {
        return CPURegisterT<IntT>(_value + offset_value);
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT>& CPURegisterT<IntT>::operator+= (const IntT offset_value) noexcept
    {
        _value += offset_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT> CPURegisterT<IntT>::operator-  (const IntT offset_value) noexcept
    {
        return CPURegisterT<IntT>(_value - offset_value);
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT>& CPURegisterT<IntT>::operator-= (const IntT offset_value) noexcept
    {
        _value -= offset_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::operator++() noexcept
    {
        return ++_value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::operator++(int) noexcept
    {
        const IntT val{ _value };
        ++_value;
        return val;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::operator--() noexcept
    {
        return --_value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::operator--(int) noexcept
    {
        const IntT val{ _value };
        --_value;
        return val;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline CPURegisterT<IntT>::operator IntT() noexcept
    {
        return _value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline CPURegisterT<IntT>::operator const IntT() const noexcept
    {
        return _value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const IntT CPURegisterT<IntT>::operator() () const noexcept
    {
        return _value;
    }

}