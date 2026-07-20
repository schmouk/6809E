#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"


namespace instr
{
    //=====   ADCA   ==========================================
    //-----   ADCA Immediate   --------------------------------
    struct ADCAImmediate : public BaseInstruction
    {
        inline ADCAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Direct   -----------------------------------
    struct ADCADirect : public BaseInstruction
    {
        inline ADCADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCADirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCA Indexed   ----------------------------------
    class ADCAIndexed : public BaseInstruction
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
    struct ADCAExtended : public BaseInstruction
    {
        inline ADCAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCAExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ADCB   ==========================================
    //-----   ADCB Immediate   --------------------------------
    struct ADCBImmediate : public BaseInstruction
    {
        inline ADCBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Direct   -----------------------------------
    struct ADCBDirect : public BaseInstruction
    {
        inline ADCBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADCB Indexed   ----------------------------------
    class ADCBIndexed : public BaseInstruction
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
    struct ADCBExtended : public BaseInstruction
    {
        inline ADCBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADCBExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

}
