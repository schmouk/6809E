#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   LEA Base Class   ================================
    struct LEABase : public BaseInstruction
    {
    public:
        LEABase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~LEABase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void _evaluate_cc_flags(const int mem_value);
    };


    //=====   LEAS   ==========================================
    //-----   LEAS Indexed   ----------------------------------
    class LEASIndexed : public LEABase
    {
    public:
        LEASIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LEASIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    protected:
        void _evaluate_cc_flags(const int mem_value) override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };


    //=====   LEAU   ==========================================
    //-----   LEAU Indexed   ----------------------------------
    class LEAUIndexed : public LEABase
    {
    public:
        LEAUIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LEAUIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    protected:
        void _evaluate_cc_flags(const int mem_value) override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };


    //=====   LEAX   ==========================================
    //-----   LEAX Indexed   ----------------------------------
    class LEAXIndexed : public LEABase
    {
    public:
        LEAXIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LEAXIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };


    //=====   LEAY   ==========================================
    //-----   LEAY Indexed   ----------------------------------
    class LEAYIndexed : public LEABase
    {
    public:
        LEAYIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LEAYIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

}
