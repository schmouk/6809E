#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   CMP Base Class   ================================
    struct CMPBase : public BaseInstruction
    {
    public:
        CMPBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        CMPBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode1, const memory::Byte opcode2) noexcept;
        virtual ~CMPBase() noexcept = default;

    protected:
        virtual void _evaluate_cc_flags(const int reg_value, const int mem_value);
        virtual void _evaluate_cc_flags_16(const int reg_value, const int mem_value);
    };


    //=====   CMPA   ==========================================
    //-----   CMPA Immediate   --------------------------------
    struct CMPAImmediate : public CMPBase
    {
        CMPAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPAImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPA Direct   -----------------------------------
    struct CMPADirect : public CMPBase
    {
        CMPADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPADirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPA Indexed   ----------------------------------
    class CMPAIndexed : public CMPBase
    {
    public:
        CMPAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPAIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CMPA Extended   ---------------------------------
    struct CMPAExtended : public CMPBase
    {
        CMPAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPAExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CMPB   ==========================================
    //-----   CMPB Immediate   --------------------------------
    struct CMPBImmediate : public CMPBase
    {
        CMPBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPBImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPB Direct   -----------------------------------
    struct CMPBDirect : public CMPBase
    {
        CMPBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPBDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPB Indexed   ----------------------------------
    class CMPBIndexed : public CMPBase
    {
    public:
        CMPBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPBIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CMPB Extended   ---------------------------------
    struct CMPBExtended : public CMPBase
    {
        CMPBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPBExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CMPD   ==========================================
    //-----   CMPD Immediate   --------------------------------
    struct CMPDImmediate : public CMPBase
    {
        CMPDImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPDImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPD Direct   -----------------------------------
    struct CMPDDirect : public CMPBase
    {
        CMPDDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPDDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPD Indexed   ----------------------------------
    class CMPDIndexed : public CMPBase
    {
    public:
        CMPDIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPDIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CMPD Extended   ---------------------------------
    struct CMPDExtended : public CMPBase
    {
        CMPDExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPDExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CMPS   ==========================================
    //-----   CMPS Immediate   --------------------------------
    struct CMPSImmediate : public CMPBase
    {
        CMPSImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPSImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPS Direct   -----------------------------------
    struct CMPSDirect : public CMPBase
    {
        CMPSDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPSDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPS Indexed   ----------------------------------
    class CMPSIndexed : public CMPBase
    {
    public:
        CMPSIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPSIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CMPS Extended   ---------------------------------
    struct CMPSExtended : public CMPBase
    {
        CMPSExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPSExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CMPU   ==========================================
    //-----   CMPU Immediate   --------------------------------
    struct CMPUImmediate : public CMPBase
    {
        CMPUImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPUImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPU Direct   -----------------------------------
    struct CMPUDirect : public CMPBase
    {
        CMPUDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPUDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPU Indexed   ----------------------------------
    class CMPUIndexed : public CMPBase
    {
    public:
        CMPUIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPUIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CMPU Extended   ---------------------------------
    struct CMPUExtended : public CMPBase
    {
        CMPUExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPUExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CMPX   ==========================================
    //-----   CMPX Immediate   --------------------------------
    struct CMPXImmediate : public CMPBase
    {
        CMPXImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPXImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPX Direct   -----------------------------------
    struct CMPXDirect : public CMPBase
    {
        CMPXDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPXDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPX Indexed   ----------------------------------
    class CMPXIndexed : public CMPBase
    {
    public:
        CMPXIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPXIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CMPX Extended   ---------------------------------
    struct CMPXExtended : public CMPBase
    {
        CMPXExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPXExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CMPY   ==========================================
    //-----   CMPY Immediate   --------------------------------
    struct CMPYImmediate : public CMPBase
    {
        CMPYImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPYImmediate() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPY Direct   -----------------------------------
    struct CMPYDirect : public CMPBase
    {
        CMPYDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPYDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CMPY Indexed   ----------------------------------
    class CMPYIndexed : public CMPBase
    {
    public:
        CMPYIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPYIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CMPY Extended   ---------------------------------
    struct CMPYExtended : public CMPBase
    {
        CMPYExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CMPYExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

}
