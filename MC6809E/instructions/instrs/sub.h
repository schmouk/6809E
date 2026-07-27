#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   SUB Base Class   ================================
    class SUBBase : public BaseInstruction
    {
    public:
        SUBBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~SUBBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int reg_value, const int mem_value);
        const memory::Word _evaluate_16(const int reg_value, const int mem_value);
        virtual void       _evaluate_cc_flags(const int intermediate_value, const int bit_mask = 0x80);
        virtual const int  _evaluate_value(const int reg_value, const int mem_value, const int bit_mask = 0x80);
    };


    //=====   SUBA   ==========================================
    //-----   SUBA Immediate   --------------------------------
    struct SUBAImmediate : public SUBBase
    {
        SUBAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBAImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SUBA Direct   -----------------------------------
    struct SUBADirect : public SUBBase
    {
        SUBADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBADirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SUBA Indexed   ----------------------------------
    class SUBAIndexed : public SUBBase
    {
    public:
        SUBAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBAIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   SUBA Extended   ---------------------------------
    struct SUBAExtended : public SUBBase
    {
        SUBAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBAExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   SUBB   ==========================================
    //-----   SUBB Immediate   --------------------------------
    struct SUBBImmediate : public SUBBase
    {
        SUBBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBBImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SUBB Direct   -----------------------------------
    struct SUBBDirect : public SUBBase
    {
        SUBBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBBDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SUBB Indexed   ----------------------------------
    class SUBBIndexed : public SUBBase
    {
    public:
        SUBBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBBIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   SUBB Extended   ---------------------------------
    struct SUBBExtended : public SUBBase
    {
        SUBBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBBExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   SUBD   ==========================================
    //-----   SUBD Immediate   --------------------------------
    struct SUBDImmediate : public SUBBase
    {
        SUBDImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBDImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SUBD Direct   -----------------------------------
    struct SUBDDirect : public SUBBase
    {
        SUBDDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBDDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SUBD Indexed   ----------------------------------
    class SUBDIndexed : public SUBBase
    {
    public:
        SUBDIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBDIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   SUBD Extended   ---------------------------------
    struct SUBDExtended : public SUBBase
    {
        SUBDExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SUBDExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
