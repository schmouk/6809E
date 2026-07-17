#include <cstdint>

#include "./adc.h"
#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"
#include "../../cpu/microproc_unit.h"


namespace instr
{
    //-----   ADCA Immediate   --------------------------------
    //---------------------------------------------------------
    ADCAImmediate::ADCAImmediate() noexcept
        : BaseInstruction{ 0x89 }
    {}

    //---------------------------------------------------------
    void ADCAImmediate::exec(archi::HWArchitecture& hw_arch)
    {
        memory::Byte mem_value{ hw_arch.get_byte(hw_arch.regPC) };
        hw_arch.regPC++;

        hw_arch.regA += mem_value + hw_arch.regCC.carry_value();
    }

    //---------------------------------------------------------
    const std::uint64_t ADCAImmediate::get_cycles_count() noexcept
    {
        return 2;
    }
    

    //-----   ADCA Direct   -----------------------------------
    //---------------------------------------------------------
    ADCADirect::ADCADirect() noexcept
        : BaseInstruction{ 0x99 }
    {}

    //---------------------------------------------------------
    void ADCADirect::exec(archi::HWArchitecture& hw_arch)
    {
        memory::Byte value_low_addr{ hw_arch.get_byte(hw_arch.regPC) };
        hw_arch.regPC++;
        memory::Byte mem_value{ hw_arch.get_byte(hw_arch.get_directpage_addr(value_low_addr)) };

        hw_arch.regA += mem_value + hw_arch.regCC.carry_value();
    }

    //---------------------------------------------------------
    const std::uint64_t ADCADirect::get_cycles_count() noexcept
    {
        return 4;
    }


    //-----   ADCA Indexed   ----------------------------------
    //---------------------------------------------------------

    //---------------------------------------------------------

    //---------------------------------------------------------

    struct ADCAIndexed : public BaseInstruction
    {
        inline ADCAIndexed();
        virtual ~ADCAIndexed() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //-----   ADCA Extended   ---------------------------------
    //---------------------------------------------------------
    ADCAExtended::ADCAExtended() noexcept
        : BaseInstruction{ 0x99 }
    {}

    //---------------------------------------------------------
    void ADCAExtended::exec(archi::HWArchitecture& hw_arch)
    {
        memory::MemAddr value_addr { memory::MemAddr(hw_arch.get_word(hw_arch.regPC)) };
        hw_arch.regPC += 2;
        memory::Byte mem_value{ hw_arch.get_byte(value_addr) };

        hw_arch.regA += mem_value + hw_arch.regCC.carry_value();
    }

    //---------------------------------------------------------
    const std::uint64_t ADCAExtended::get_cycles_count() noexcept
    {
        return 5;
    }


    //-----   ADCB Immediate   --------------------------------
    //---------------------------------------------------------
    ADCBImmediate::ADCBImmediate() noexcept
        : BaseInstruction{ 0x89 }
    {}

    //---------------------------------------------------------
    void ADCBImmediate::exec(archi::HWArchitecture& hw_arch)
    {
        memory::Byte mem_value{ hw_arch.get_byte(hw_arch.regPC) };
        hw_arch.regPC++;

        hw_arch.regA += mem_value + hw_arch.regCC.carry_value();
    }

    //---------------------------------------------------------
    const std::uint64_t ADCBImmediate::get_cycles_count() noexcept
    {
        return 2;
    }


    //-----   ADCB Direct   -----------------------------------
    //---------------------------------------------------------
    ADCBDirect::ADCBDirect() noexcept
        : BaseInstruction{ 0x99 }
    {}

    //---------------------------------------------------------
    void ADCBDirect::exec(archi::HWArchitecture& hw_arch)
    {
        memory::Byte value_low_addr{ hw_arch.get_byte(hw_arch.regPC) };
        hw_arch.regPC++;
        memory::Byte mem_value{ hw_arch.get_byte(hw_arch.get_directpage_addr(value_low_addr)) };

        hw_arch.regA += mem_value + hw_arch.regCC.carry_value();
    }

    //---------------------------------------------------------
    const std::uint64_t ADCBDirect::get_cycles_count() noexcept
    {
        return 4;
    }

    //-----   ADCB Indexed   ----------------------------------
    struct ADCBIndexed : public BaseInstruction
    {
        inline ADCBIndexed();
        virtual ~ADCBIndexed() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Extended   ---------------------------------
    //---------------------------------------------------------
    ADCBExtended::ADCBExtended() noexcept
        : BaseInstruction{ 0x99 }
    {}

    //---------------------------------------------------------
    void ADCBExtended::exec(archi::HWArchitecture& hw_arch)
    {
        memory::MemAddr value_addr{ memory::MemAddr(hw_arch.get_word(hw_arch.regPC)) };
        hw_arch.regPC += 2;
        memory::Byte mem_value{ hw_arch.get_byte(value_addr) };

        hw_arch.regA += mem_value + hw_arch.regCC.carry_value();
    }

    //---------------------------------------------------------
    const std::uint64_t ADCBExtended::get_cycles_count() noexcept
    {
        return 5;
    }

}
