#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ROR Base Class   ================================
    class RORBase : public BaseInstruction
    {
    public:
        RORBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~RORBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   RORA   ==========================================
    //-----   RORA Inherent   ---------------------------------
    struct RORAInherent : public RORBase
    {
        RORAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~RORAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   RORB   ==========================================
    //-----   RORB Inherent   ---------------------------------
    struct RORBInherent : public RORBase
    {
        RORBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~RORBInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ROR Memory   ====================================
    //-----   ROR Direct   ------------------------------------
    struct RORDirect : public RORBase
    {
        RORDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~RORDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ROR Indexed   -----------------------------------
    class RORIndexed : public RORBase
    {
    public:
        RORIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~RORIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ROR Extended   ----------------------------------
    struct RORExtended : public RORBase
    {
        RORExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~RORExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
