#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   BIT Base Class   ================================
    class BITBase : public BaseInstruction
    {
    public:
        BITBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~BITBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int reg_value, const int mem_value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int reg_value, const int mem_value);
    };


    //=====   BITA   ==========================================
    //-----   BITA Immediate   --------------------------------
    struct BITAImmediate : public BITBase
    {
        BITAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITAImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   BITA Direct   -----------------------------------
    struct BITADirect : public BITBase
    {
        BITADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITADirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   BITA Indexed   ----------------------------------
    class BITAIndexed : public BITBase
    {
    public:
        BITAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITAIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   BITA Extended   ---------------------------------
    struct BITAExtended : public BITBase
    {
        BITAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITAExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   BITB   ==========================================
    //-----   BITB Immediate   --------------------------------
    struct BITBImmediate : public BITBase
    {
        BITBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITBImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   BITB Direct   -----------------------------------
    struct BITBDirect : public BITBase
    {
        BITBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITBDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   BITB Indexed   ----------------------------------
    class BITBIndexed : public BITBase
    {
    public:
        BITBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITBIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   BITB Extended   ---------------------------------
    struct BITBExtended : public BITBase
    {
        BITBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~BITBExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
