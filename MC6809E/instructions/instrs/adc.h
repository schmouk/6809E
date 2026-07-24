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
        ADCBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
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
        ADCAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Direct   -----------------------------------
    struct ADCADirect : public ADCBase
    {
        ADCADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCADirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Indexed   ----------------------------------
    class ADCAIndexed : public ADCBase
    {
    public:
        ADCAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ADCA Extended   ---------------------------------
    struct ADCAExtended : public ADCBase
    {
        ADCAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ADCB   ==========================================
    //-----   ADCB Immediate   --------------------------------
    struct ADCBImmediate : public ADCBase
    {
        ADCBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Direct   -----------------------------------
    struct ADCBDirect : public ADCBase
    {
        ADCBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Indexed   ----------------------------------
    class ADCBIndexed : public ADCBase
    {
    public:
        ADCBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ADCB Extended   ---------------------------------
    struct ADCBExtended : public ADCBase
    {
        ADCBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
