#pragma once

/**
* This file defines next class:
* - class CPUInstruction;      // The base class for every MC6809E microprocessing unit instruction
* - class CPUInstructionsSet;  // The set of MC6809E instructions
*/

#include <cstdint>
#include <vector>

#include "../architecture/hw_architecture.h"
#include "../memory/types.h"


namespace instr
{
    //=====   MC6809E CPU Instruction Base Class   ============
    class BaseInstruction
    {
    public:
        //-----   Constructors / Destructor   -----------------
        inline BaseInstruction() noexcept = default;
        inline virtual ~BaseInstruction() noexcept = default;

        BaseInstruction(const BaseInstruction&) = delete;
        BaseInstruction(BaseInstruction&&) = delete;

        inline BaseInstruction(const memory::Byte opcode) noexcept;
        inline BaseInstruction(const memory::Byte opcode1, const memory::Byte opcode2) noexcept;

        BaseInstruction(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     opcode
        ) noexcept;

        BaseInstruction(
            archi::HWArchitecture& hw_arch, 
            const memory::Byte     opcode1,
            const memory::Byte     opcode2
        ) noexcept;


        //-----   Operators   ---------------------------------
        const bool operator== (const memory::Byte opcode) const noexcept;
        const bool operator== (const std::vector<memory::Byte>& opcode) const noexcept;


        //-----   Operations   --------------------------------
        virtual void exec() = 0;
        virtual const std::uint64_t get_cycles_count() noexcept = 0;


    protected:
        archi::HWArchitecture _hw_arch{};

    private:
        std::vector<memory::Byte> _opcode{};

    };

}