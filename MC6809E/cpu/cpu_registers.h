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

#include "../memory/types.h"


namespace cpu
{
    //=====   The Microprocessing Registers   =================
    //---------------------------------------------------------
    struct CPURegister  // Notice: the base class for every CPU register
    {
        virtual bool is_8bits() const noexcept = 0;
        virtual const int get() const noexcept = 0;
        virtual void set(const int val) noexcept = 0;
    };


    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    class CPURegisterT : public CPURegister
    {
    public:
        //-----   Constructors / Destructors   ----------------
        inline CPURegisterT() noexcept = default;
        inline virtual ~CPURegisterT() noexcept = default;

        inline CPURegisterT(const IntT value) noexcept;

        inline CPURegisterT(const CPURegisterT&) noexcept = default;
        inline CPURegisterT(CPURegisterT&&) noexcept = default;

        inline CPURegisterT& operator=(const CPURegisterT&) noexcept = default;
        inline CPURegisterT& operator=(CPURegisterT&&) noexcept = default;


        //-----   Operators   ---------------------------------
        inline const CPURegisterT& operator= (const IntT new_value) noexcept;

        inline const IntT          operator+  (const IntT offset_value) const noexcept;
        inline const CPURegisterT& operator+= (const IntT offset_value) noexcept;

        inline const IntT          operator-  (const IntT offset_value) const noexcept;
        inline const CPURegisterT& operator-= (const IntT offset_value) noexcept;

        inline const IntT          operator&  (const IntT offset_value) const noexcept;
        inline const CPURegisterT& operator&= (const IntT offset_value) noexcept;

        inline const IntT          operator|  (const IntT offset_value) const noexcept;
        inline const CPURegisterT& operator|= (const IntT offset_value) noexcept;

        inline const IntT          operator^  (const IntT offset_value)const  noexcept;
        inline const CPURegisterT& operator^= (const IntT offset_value) noexcept;

        inline const CPURegisterT& operator~  () noexcept;

        inline const IntT operator++() noexcept;    // Notice: pre-increment
        inline const IntT operator++(int) noexcept; // Notice: post-increment

        inline const IntT operator--() noexcept;    // Notice: pre-decrement
        inline const IntT operator--(int) noexcept; // Notice: post-decrement

        inline operator IntT() noexcept;
        inline operator const IntT() const noexcept;

        inline const IntT operator() () const noexcept; // Gets the value of the register content


        //-----   Operations   --------------------------------
        inline const int get() const noexcept override;         // Gets the value of the register content
        inline void      set(const int val) noexcept override;  // Sets value of the register content

        inline bool is_8bits() const noexcept override;


    private:
        IntT _value{ 0 };

    };


    //-----   Specializations   -------------------------------
    using CPURegister8bits  = CPURegisterT<std::uint8_t>;    //  8-bits wide registers
    using CPURegister16bits = CPURegisterT<std::uint16_t>;   // 16-bits wide registers
    using CPUIndexRegister  = CPURegisterT<std::uint16_t>;   // 16-bits wide indexing registers


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
        CPUCCRegister() noexcept = default;
        virtual ~CPUCCRegister() noexcept = default;

        CPUCCRegister(const CPUCCRegister&) noexcept = default;
        CPUCCRegister(CPUCCRegister&&) noexcept = default;

        CPUCCRegister& operator= (const CPUCCRegister&) noexcept = default;
        CPUCCRegister& operator= (CPUCCRegister&&) noexcept = default;

        const CPUCCRegister& operator= (const int new_value) noexcept;


        //-----   Operations   --------------------------------
        const bool carry_flag() const noexcept;      // C flag - Bit 0
        void clr_carry() noexcept;
        void set_carry() noexcept;
        void set_carry(const bool flag_value) noexcept;
        const memory::Byte carry_value() const noexcept;

        const bool overflow_flag() const noexcept;   // V flag - Bit 1
        void clr_overflow() noexcept;
        void set_overflow() noexcept;
        void set_overflow(const bool flag_value) noexcept;

        const bool zero_flag() const noexcept;       // Z flag - Bit 2
        void clr_zero() noexcept;
        void set_zero() noexcept;
        void set_zero(const bool flag_value) noexcept;

        const bool negative_flag() const noexcept;   // N flag - bit 3
        void clr_negative() noexcept;
        void set_negative() noexcept;
        void set_negative(const bool flag_value) noexcept;

        const bool irqmask_flag() const noexcept;    // I flag - bit 4
        void clr_irqmask() noexcept;
        void set_irqmask() noexcept;

        const bool halfcarry_flag() const noexcept;  // H flag - bit 5
        void clr_halfcarry() noexcept;
        void set_halfcarry() noexcept;
        void set_halfcarry(const bool flag_value) noexcept;

        const bool firqmask_flag() const noexcept;   // F flag - bit 6
        void clr_firqmask() noexcept;
        void set_firqmask() noexcept;

        const bool entire_flag() const noexcept;     // E flag - bit 7
        void clr_entire() noexcept;
        void set_entire() noexcept;


        void clr() noexcept;


        //-----   Bits Masks   --------------------------------
        inline static constexpr std::uint8_t C_FLAG = 0x01;
        inline static constexpr std::uint8_t V_FLAG = 0x02;
        inline static constexpr std::uint8_t Z_FLAG = 0x04;
        inline static constexpr std::uint8_t N_FLAG = 0x08;
        inline static constexpr std::uint8_t I_FLAG = 0x10;
        inline static constexpr std::uint8_t H_FLAG = 0x20;
        inline static constexpr std::uint8_t F_FLAG = 0x40;
        inline static constexpr std::uint8_t E_FLAG = 0x80;

        inline static constexpr std::uint8_t CLR_MASK = 0b01010000;  // Notice: does not change status of I and F flags

    };


    //=====   IMPLEMENTATIONS   ===============================
    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    CPURegisterT<IntT>::CPURegisterT(const IntT value) noexcept
        : _value(value)
    {}

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const int CPURegisterT<IntT>::get() const noexcept
    {
        return int(_value);
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    void CPURegisterT<IntT>::set(const int val) noexcept
    {
        _value = IntT(val);
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline bool CPURegisterT<IntT>::is_8bits() const noexcept
    {
        return sizeof(IntT) == 1;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const CPURegisterT<IntT>& CPURegisterT<IntT>::operator= (const IntT new_value) noexcept
    {
        _value = new_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::operator+ (const IntT offset_value) const noexcept
    {
        return _value + offset_value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const CPURegisterT<IntT>& CPURegisterT<IntT>::operator+= (const IntT offset_value) noexcept
    {
        _value += offset_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::operator- (const IntT offset_value) const noexcept
    {
        return _value - offset_value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const CPURegisterT<IntT>& CPURegisterT<IntT>::operator-= (const IntT offset_value) noexcept
    {
        _value -= offset_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const IntT  CPURegisterT<IntT>::operator& (const IntT offset_value) const noexcept
    {
        return _value & offset_value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT>& CPURegisterT<IntT>::operator&= (const IntT offset_value) noexcept
    {
        _value &= offset_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const IntT CPURegisterT<IntT>::operator| (const IntT offset_value) const noexcept
    {
        return _value | offset_value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT>& CPURegisterT<IntT>::operator|= (const IntT offset_value) noexcept
    {
        _value |= offset_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const IntT CPURegisterT<IntT>::operator^ (const IntT offset_value) const noexcept
    {
        return _value ^ offset_value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT>& CPURegisterT<IntT>::operator^= (const IntT offset_value) noexcept
    {
        _value ^= offset_value;
        return *this;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    inline const CPURegisterT<IntT>& CPURegisterT<IntT>::operator~ () noexcept
    {
        _value = ~_value;
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
    CPURegisterT<IntT>::operator IntT() noexcept
    {
        return _value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    CPURegisterT<IntT>::operator const IntT() const noexcept
    {
        return _value;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegisterT<IntT>::operator() () const noexcept
    {
        return _value;
    }

}