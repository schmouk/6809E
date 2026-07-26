#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ST Base Class   =================================
    class STBase : public BaseInstruction
    {
    public:
        STBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        STBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode1, const memory::Byte opcode2) noexcept;
        virtual ~STBase() noexcept = default;

    protected:
        void _store_byte(const memory::MemAddr byte_addr, const memory::Byte byte_value);
        void _store_word(const memory::MemAddr word_addr, const memory::Word word_value);

        virtual void _evaluate_cc_flags(const int mem_value);
        virtual void _evaluate_cc_flags_16(const int mem_value);
    };


    //=====   STA   ===========================================
    //-----   STA Direct   ------------------------------------
    struct STADirect : public STBase
    {
        STADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STADirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   STA Indexed   -----------------------------------
    class STAIndexed : public STBase
    {
    public:
        STAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STAIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   STA Extended   ----------------------------------
    struct STAExtended : public STBase
    {
        STAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STAExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   STB   ===========================================
    //-----   STB Direct   ------------------------------------
    struct STBDirect : public STBase
    {
        STBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STBDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   STB Indexed   -----------------------------------
    class STBIndexed : public STBase
    {
    public:
        STBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STBIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   STB Extended   ----------------------------------
    struct STBExtended : public STBase
    {
        STBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STBExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   STD   ===========================================
    //-----   STD Direct   ------------------------------------
    struct STDDirect : public STBase
    {
        STDDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STDDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   STD Indexed   -----------------------------------
    class STDIndexed : public STBase
    {
    public:
        STDIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STDIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   STD Extended   ----------------------------------
    struct STDExtended : public STBase
    {
        STDExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STDExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   STS   ===========================================
    //-----   STS Direct   ------------------------------------
    struct STSDirect : public STBase
    {
        STSDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STSDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   STS Indexed   -----------------------------------
    class STSIndexed : public STBase
    {
    public:
        STSIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STSIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   STS Extended   ----------------------------------
    struct STSExtended : public STBase
    {
        STSExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STSExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   STU   ===========================================
    //-----   STU Direct   ------------------------------------
    struct STUDirect : public STBase
    {
        STUDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STUDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   STU Indexed   -----------------------------------
    class STUIndexed : public STBase
    {
    public:
        STUIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STUIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   STU Extended   ----------------------------------
    struct STUExtended : public STBase
    {
        STUExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STUExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   STX   ===========================================
    //-----   STX Direct   ------------------------------------
    struct STXDirect : public STBase
    {
        STXDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STXDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   STX Indexed   -----------------------------------
    class STXIndexed : public STBase
    {
    public:
        STXIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STXIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   STX Extended   ----------------------------------
    struct STXExtended : public STBase
    {
        STXExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STXExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   STY   ===========================================
    //-----   STY Direct   ------------------------------------
    struct STYDirect : public STBase
    {
        STYDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STYDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   STY Indexed   -----------------------------------
    class STYIndexed : public STBase
    {
    public:
        STYIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STYIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   STY Extended   ----------------------------------
    struct STYExtended : public STBase
    {
        STYExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~STYExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
