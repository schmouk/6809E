#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ASL Base Class   ================================
    class ASLBase : public BaseInstruction
    {
    public:
        ASLBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~ASLBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   ASLA   ==========================================
    //-----   ASLA Inherent   ---------------------------------
    struct ASLAInherent : public ASLBase
    {
        ASLAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASLAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ASLB   ==========================================
    //-----   ASLB Inherent   ---------------------------------
    struct ASLBInherent : public ASLBase
    {
        ASLBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASLBInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ASL Memory   ====================================
    //-----   ASL Direct   ------------------------------------
    struct ASLDirect : public ASLBase
    {
        ASLDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASLDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ASL Indexed   -----------------------------------
    class ASLIndexed : public ASLBase
    {
    public:
        ASLIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASLIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ASL Extended   ----------------------------------
    struct ASLExtended : public ASLBase
    {
        ASLExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASLExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
