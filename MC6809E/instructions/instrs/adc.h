#pragma once

#include <cstdint>

#include "../base_instruction.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ADCA   ==========================================
    //-----   ADCA Immediate   --------------------------------
    struct ADCAImmediate : public BaseInstruction
    {
        inline ADCAImmediate() noexcept;
        virtual ~ADCAImmediate() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Direct   -----------------------------------
    struct ADCADirect : public BaseInstruction
    {
        inline ADCADirect() noexcept;
        virtual ~ADCADirect() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Indexed   ----------------------------------
    struct ADCAIndexed : public BaseInstruction
    {
        inline ADCAIndexed() noexcept;
        virtual ~ADCAIndexed() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Extended   ---------------------------------
    struct ADCAExtended : public BaseInstruction
    {
        inline ADCAExtended() noexcept;
        virtual ~ADCAExtended() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ADCB   ==========================================
    //-----   ADCB Immediate   --------------------------------
    struct ADCBImmediate : public BaseInstruction
    {
        inline ADCBImmediate() noexcept;
        virtual ~ADCBImmediate() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Direct   -----------------------------------
    struct ADCBDirect : public BaseInstruction
    {
        inline ADCBDirect() noexcept;
        virtual ~ADCBDirect() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Indexed   ----------------------------------
    struct ADCBIndexed : public BaseInstruction
    {
        inline ADCBIndexed() noexcept;
        virtual ~ADCBIndexed() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Extended   ---------------------------------
    struct ADCBExtended : public BaseInstruction
    {
        inline ADCBExtended() noexcept;
        virtual ~ADCBExtended() noexcept = default;

        virtual void exec(archi::HWArchitecture& hw_arch) override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

}
