#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ROL Base Class   ================================
    class ROLBase : public BaseInstruction
    {
    public:
        ROLBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~ROLBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   ROLA   ==========================================
    //-----   ROLA Inherent   ---------------------------------
    struct ROLAInherent : public ROLBase
    {
        ROLAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ROLAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ROLB   ==========================================
    //-----   ROLB Inherent   ---------------------------------
    struct ROLBInherent : public ROLBase
    {
        ROLBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ROLBInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ROL Memory   ====================================
    //-----   ROL Direct   ------------------------------------
    struct ROLDirect : public ROLBase
    {
        ROLDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ROLDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ROL Indexed   -----------------------------------
    class ROLIndexed : public ROLBase
    {
    public:
        ROLIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ROLIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ROL Extended   ----------------------------------
    struct ROLExtended : public ROLBase
    {
        ROLExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ROLExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
