#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"
#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   OR Base Class   =================================
    class ORBase : public BaseInstruction
    {
    public:
        ORBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~ORBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int reg_value, const int mem_value);
        void       _evaluate_cc_flags(const int intermediate_value);
        const int  _evaluate_value(const int reg_value, const int mem_value);
    };


    //=====   ORA   ===========================================
    //-----   ORA Immediate   ---------------------------------
    struct ORAImmediate : public ORBase
    {
        ORAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORAImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ORA Direct   ------------------------------------
    struct ORADirect : public ORBase
    {
        ORADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORADirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ORA Indexed   -----------------------------------
    class ORAIndexed : public ORBase
    {
    public:
        ORAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORAIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ORA Extended   ----------------------------------
    struct ORAExtended : public ORBase
    {
        ORAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORAExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ORB   ===========================================
    //-----   ORB Immediate   ---------------------------------
    struct ORBImmediate : public ORBase
    {
        ORBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORBImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ORB Direct   ------------------------------------
    struct ORBDirect : public ORBase
    {
        ORBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORBDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ORB Indexed   -----------------------------------
    class ORBIndexed : public ORBase
    {
    public:
        ORBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORBIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ORB Extended   ----------------------------------
    struct ORBExtended : public ORBase
    {
        ORBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORBExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ORCC   ==========================================
    //-----   ORCC Immediate   --------------------------------
    struct ORCCImmediate : public ORBase
    {
        ORCCImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ORCCImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
