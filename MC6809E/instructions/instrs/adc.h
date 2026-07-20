#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ADC Base Class   ================================
    class ADCBase : public BaseInstruction
    {
    public:
        inline ADCBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~ADCBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int reg_value, const int mem_value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int reg_value, const int mem_value);
    };


    //=====   ADCA   ==========================================
    //-----   ADCA Immediate   --------------------------------
    struct ADCAImmediate : public ADCBase
    {
        inline ADCAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Direct   -----------------------------------
    struct ADCADirect : public ADCBase
    {
        inline ADCADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCADirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Indexed   ----------------------------------
    class ADCAIndexed : public ADCBase
    {
    public:
        inline ADCAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ADCA Extended   ---------------------------------
    struct ADCAExtended : public ADCBase
    {
        inline ADCAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ADCB   ==========================================
    //-----   ADCB Immediate   --------------------------------
    struct ADCBImmediate : public ADCBase
    {
        inline ADCBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Direct   -----------------------------------
    struct ADCBDirect : public ADCBase
    {
        inline ADCBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Indexed   ----------------------------------
    class ADCBIndexed : public ADCBase
    {
    public:
        inline ADCBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ADCB Extended   ---------------------------------
    struct ADCBExtended : public ADCBase
    {
        inline ADCBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

}
