#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   SBC Base Class   ================================
    class SBCBase : public BaseInstruction
    {
    public:
        SBCBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~SBCBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int reg_value, const int mem_value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int reg_value, const int mem_value);
    };


    //=====   SBCA   ==========================================
    //-----   SBCA Immediate   --------------------------------
    struct SBCAImmediate : public SBCBase
    {
        SBCAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCAImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SBCA Direct   -----------------------------------
    struct SBCADirect : public SBCBase
    {
        SBCADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCADirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SBCA Indexed   ----------------------------------
    class SBCAIndexed : public SBCBase
    {
    public:
        SBCAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCAIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   SBCA Extended   ---------------------------------
    struct SBCAExtended : public SBCBase
    {
        SBCAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCAExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   SBCB   ==========================================
    //-----   SBCB Immediate   --------------------------------
    struct SBCBImmediate : public SBCBase
    {
        SBCBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCBImmediate() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SBCB Direct   -----------------------------------
    struct SBCBDirect : public SBCBase
    {
        SBCBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCBDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   SBCB Indexed   ----------------------------------
    class SBCBIndexed : public SBCBase
    {
    public:
        SBCBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCBIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   SBCB Extended   ---------------------------------
    struct SBCBExtended : public SBCBase
    {
        SBCBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~SBCBExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
