#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   EOR Base Class   ================================
    class EORBase : public BaseInstruction
    {
    public:
        EORBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~EORBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int reg_value, const int mem_value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int reg_value, const int mem_value);
    };


    //=====   EORA   ==========================================
    //-----   EORA Immediate   --------------------------------
    struct EORAImmediate : public EORBase
    {
        EORAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORAImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   EORA Direct   -----------------------------------
    struct EORADirect : public EORBase
    {
        EORADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORADirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   EORA Indexed   ----------------------------------
    class EORAIndexed : public EORBase
    {
    public:
        EORAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORAIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   EORA Extended   ---------------------------------
    struct EORAExtended : public EORBase
    {
        EORAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORAExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   EORB   ==========================================
    //-----   EORB Immediate   --------------------------------
    struct EORBImmediate : public EORBase
    {
        EORBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORBImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   EORB Direct   -----------------------------------
    struct EORBDirect : public EORBase
    {
        EORBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORBDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   EORB Indexed   ----------------------------------
    class EORBIndexed : public EORBase
    {
    public:
        EORBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORBIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   EORB Extended   ---------------------------------
    struct EORBExtended : public EORBase
    {
        EORBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~EORBExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
