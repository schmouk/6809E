#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   INC Base Class   ================================
    class INCBase : public BaseInstruction
    {
    public:
        INCBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~INCBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   INCA   ==========================================
    //-----   INCA Inherent   ---------------------------------
    struct INCAInherent : public INCBase
    {
        INCAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~INCAInherent() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   INCB   ==========================================
    //-----   INCB Inherent   ---------------------------------
    struct INCBInherent : public INCBase
    {
        INCBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~INCBInherent() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   INC Memory   ====================================
    //-----   INC Direct   ------------------------------------
    struct INCDirect : public INCBase
    {
        INCDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~INCDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   INC Indexed   -----------------------------------
    class INCIndexed : public INCBase
    {
    public:
        INCIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~INCIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   INC Extended   ----------------------------------
    struct INCExtended : public INCBase
    {
        INCExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~INCExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
