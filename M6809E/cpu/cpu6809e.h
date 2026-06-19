#pragma once

/**
* This file defines the MC6809E microprocessor H/W emulation.
* 
* It defines next classes:
* 
* - template<typename IntT> class CPURegister;
* - using CpuRegister8bits  = CPURegister<std::uint8_t>;
* - using CpuRegister16bits = CPURegister<std::uint16_t>;
* - struct CpuCCRegister;
* 
* - struct MicroprocUnit;  // The composition of all 8-bits and 16-bits MC6809 registers
*/

#include <cstdint>
#include <type_traits>

namespace cpu
{
    //=====   The Microprocessing Registers   =================
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    class CPURegister
    {
    public:
        //-----   Constructors / Destructors   ----------------
        inline CPURegister() noexcept = default;
        inline virtual ~CPURegister() noexcept = default;

        CPURegister(const CPURegister&) = delete;   // Can't copy content of registers
        CPURegister(CPURegister&&) = delete;        // Can't move content of registers

        //-----   Operations   --------------------------------
        inline void set(const IntT val) noexcept;   // Sets value of the register content

        inline const IntT get() const noexcept;     // Gets the value of the register content


    private:
        IntT _value{};

    };


    //-----   Specializations   -------------------------------
    using CpuRegister8bits  = CPURegister<std::uint8_t>;    //  8-bits wide registers
    using CpuRegister16bits = CPURegister<std::uint16_t>;   // 16-bits wide registers


    //=====   Deeper Specialization - the CC Register   =======
    struct CpuCCRegister : public CpuRegister8bits
    {
        //-----   Constructors / Destructors   ----------------
        inline CpuCCRegister() noexcept = default;
        inline virtual ~CpuCCRegister() noexcept = default;

        CpuCCRegister(const CpuCCRegister&) = delete;       // Can't copy content of registers
        CpuCCRegister(CpuCCRegister&&) = delete;            // Can't move content of registers

        CpuCCRegister& operator= (const CpuCCRegister&) = delete;
        CpuCCRegister& operator= (CpuCCRegister&&) = delete;


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


    //=====   The Microprocessing Unit   ======================
    struct MicroprocUnit
    {
    public:
        //-----   Constructor / Destructor   ------------------
        inline MicroprocUnit() noexcept = default;
        inline virtual ~MicroprocUnit() noexcept = default;

        MicroprocUnit(const MicroprocUnit&) = delete;   // Can't copy CPUs content
        MicroprocUnit(MicroprocUnit&&) = delete;        // Can't move CPUs content


        //-----   CPU Registers   -----------------------------
        CpuCCRegister     regCC;
        CpuRegister16bits regX, regY, regU, regS, regPC, regD;
        CpuRegister8bits  regA, regB, regDP;

    };


    //=====   IMPLEMENTATIONS   ===============================
    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    void CPURegister<IntT>::set(const IntT val) noexcept
    {
        _value = val;
    }

    //---------------------------------------------------------
    template<typename IntT>
        requires std::is_same_v<std::uint8_t, IntT> || std::is_same_v<std::uint16_t, IntT>
    const IntT CPURegister<IntT>::get() const noexcept
    {
        return _value;
    }

}