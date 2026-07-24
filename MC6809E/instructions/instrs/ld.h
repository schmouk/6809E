#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   LD Base Class   =================================
    class LDBase : public BaseInstruction
    {
    public:
        LDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        LDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode1, const memory::Byte opcode2) noexcept;
        virtual ~LDBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        const memory::Word _evaluate_16(const int value);

        virtual void _evaluate_cc_flags(const int mem_value);
        virtual void _evaluate_cc_flags_16(const int mem_value);
    };


    //=====   LDA   ===========================================
    //-----   LDA Immediate   ---------------------------------
    struct LDAImmediate : public LDBase
    {
        LDAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDAImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDA Direct   ------------------------------------
    struct LDADirect : public LDBase
    {
        LDADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDADirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDA Indexed   -----------------------------------
    class LDAIndexed : public LDBase
    {
    public:
        LDAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDAIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LDA Extended   ----------------------------------
    struct LDAExtended : public LDBase
    {
        LDAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDAExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LDB   ===========================================
    //-----   LDB Immediate   ---------------------------------
    struct LDBImmediate : public LDBase
    {
        LDBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDBImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDB Direct   ------------------------------------
    struct LDBDirect : public LDBase
    {
        LDBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDBDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDB Indexed   -----------------------------------
    class LDBIndexed : public LDBase
    {
    public:
        LDBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDBIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LDB Extended   ----------------------------------
    struct LDBExtended : public LDBase
    {
        LDBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDBExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LDD   ===========================================
    //-----   LDD Immediate   ---------------------------------
    struct LDDImmediate : public LDBase
    {
        LDDImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDDImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDD Direct   ------------------------------------
    struct LDDDirect : public LDBase
    {
        LDDDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDDDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDD Indexed   -----------------------------------
    class LDDIndexed : public LDBase
    {
    public:
        LDDIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDDIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LDD Extended   ----------------------------------
    struct LDDExtended : public LDBase
    {
        LDDExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDDExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LDS   ===========================================
    //-----   LDS Immediate   ---------------------------------
    struct LDSImmediate : public LDBase
    {
        LDSImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDSImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDS Direct   ------------------------------------
    struct LDSDirect : public LDBase
    {
        LDSDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDSDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDS Indexed   -----------------------------------
    class LDSIndexed : public LDBase
    {
    public:
        LDSIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDSIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LDS Extended   ----------------------------------
    struct LDSExtended : public LDBase
    {
        LDSExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDSExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LDU   ===========================================
    //-----   LDU Immediate   ---------------------------------
    struct LDUImmediate : public LDBase
    {
        LDUImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDUImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDU Direct   ------------------------------------
    struct LDUDirect : public LDBase
    {
        LDUDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDUDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDU Indexed   -----------------------------------
    class LDUIndexed : public LDBase
    {
    public:
        LDUIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDUIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LDU Extended   ----------------------------------
    struct LDUExtended : public LDBase
    {
        LDUExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDUExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LDX   ===========================================
    //-----   LDX Immediate   ---------------------------------
    struct LDXImmediate : public LDBase
    {
        LDXImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDXImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDX Direct   ------------------------------------
    struct LDXDirect : public LDBase
    {
        LDXDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDXDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDX Indexed   -----------------------------------
    class LDXIndexed : public LDBase
    {
    public:
        LDXIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDXIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LDX Extended   ----------------------------------
    struct LDXExtended : public LDBase
    {
        LDXExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDXExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LDY   ===========================================
    //-----   LDY Immediate   ---------------------------------
    struct LDYImmediate : public LDBase
    {
        LDYImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDYImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDY Direct   ------------------------------------
    struct LDYDirect : public LDBase
    {
        LDYDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDYDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LDY Indexed   -----------------------------------
    class LDYIndexed : public LDBase
    {
    public:
        LDYIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDYIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LDY Extended   ----------------------------------
    struct LDYExtended : public LDBase
    {
        LDYExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LDYExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
