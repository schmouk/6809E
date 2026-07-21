#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   COM Base Class   ================================
    class COMBase : public BaseInstruction
    {
    public:
        COMBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~COMBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   COMA   ==========================================
    //-----   COMA Inherent   ---------------------------------
    struct COMAInherent : public COMBase
    {
        COMAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~COMAInherent() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   COMB   ==========================================
    //-----   COMB Inherent   ---------------------------------
    struct COMBInherent : public COMBase
    {
        COMBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~COMBInherent() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   COM Memory   ====================================
    //-----   COM Direct   ------------------------------------
    struct COMDirect : public COMBase
    {
        COMDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~COMDirect() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   COM Indexed   -----------------------------------
    class COMIndexed : public COMBase
    {
    public:
        COMIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~COMIndexed() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   COM Extended   ----------------------------------
    struct COMExtended : public COMBase
    {
        COMExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~COMExtended() noexcept = default;

        virtual void exec() override;
        virtual const std::uint64_t get_cycles_count() noexcept override;
    };

}
