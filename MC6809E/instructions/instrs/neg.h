#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   NEG Base Class   ================================
    class NEGBase : public BaseInstruction
    {
    public:
        NEGBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~NEGBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   NEGA   ==========================================
    //-----   NEGA Inherent   ---------------------------------
    struct NEGAInherent : public NEGBase
    {
        NEGAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~NEGAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   NEGB   ==========================================
    //-----   NEGB Inherent   ---------------------------------
    struct NEGBInherent : public NEGBase
    {
        NEGBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~NEGBInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   NEG Memory   ====================================
    //-----   NEG Direct   ------------------------------------
    struct NEGDirect : public NEGBase
    {
        NEGDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~NEGDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   NEG Indexed   -----------------------------------
    class NEGIndexed : public NEGBase
    {
    public:
        NEGIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~NEGIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   NEG Extended   ----------------------------------
    struct NEGExtended : public NEGBase
    {
        NEGExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~NEGExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
