#pragma once

/**
* This file defines the MC6809E microprocessor H/W emulation.
* 
* It defines next class:
* - struct MicroprocUnit;  // The composition of all 8-bits and 16-bits MC6809E registers
*/

#include "./cpu_registers.h"
#include "../memory/types.h"


namespace cpu
{
    //=====   The Microprocessing Unit   ======================
    struct MicroprocUnit
    {
        //-----   Constructor / Destructor   ------------------
        inline MicroprocUnit() noexcept = default;
        inline virtual ~MicroprocUnit() noexcept = default;

        MicroprocUnit(const MicroprocUnit&) = default;
        MicroprocUnit(MicroprocUnit&&) = default;

        MicroprocUnit& operator=(const MicroprocUnit&) = default;
        MicroprocUnit& operator=(MicroprocUnit&&) = default;


        //-----   CPU Registers   -----------------------------
        CPUIndexRegister  regX{} , regY{}, regU{}, regS{};
        CPURegister16bits regPC{}, regD{};
        CPURegister8bits  regA{} , regB{}, regDP{};
        CPUCCRegister     regCC{};


        //-----   Operations   ---------------------------------
        const memory::MemAddr get_directpage_addr(const memory::Byte addr_low) const noexcept;

        const memory::Word get_reg_value(const cpu::EReg reg_index) const;

    };

}