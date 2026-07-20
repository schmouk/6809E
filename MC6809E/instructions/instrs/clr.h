#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   CLR Base Class   ================================
    class CLRBase : public BaseInstruction
    {
    public:
        CLRBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~CLRBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   CLRA   ==========================================
    //-----   CLRA Inherent   ---------------------------------
    struct CLRAInherent : public CLRBase
    {
        CLRAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CLRAInherent() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CLRB   ==========================================
    //-----   CLRB Inherent   ---------------------------------
    struct CLRBInherent : public CLRBase
    {
        CLRBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CLRBInherent() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   CLR Memory   ====================================
    //-----   CLR Direct   ------------------------------------
    struct CLRDirect : public CLRBase
    {
        CLRDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CLRDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   CLR Indexed   -----------------------------------
    class CLRIndexed : public CLRBase
    {
    public:
        CLRIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CLRIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   CLR Extended   ----------------------------------
    struct CLRExtended : public CLRBase
    {
        CLRExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~CLRExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

}
