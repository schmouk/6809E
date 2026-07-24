#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ASR Base Class   ================================
    class ASRBase : public BaseInstruction
    {
    public:
        ASRBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~ASRBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   ASRA   ==========================================
    //-----   ASRA Inherent   ---------------------------------
    struct ASRAInherent : public ASRBase
    {
        ASRAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASRAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ASRB   ==========================================
    //-----   ASRB Inherent   ---------------------------------
    struct ASRBInherent : public ASRBase
    {
        ASRBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASRBInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ASR Memory   ====================================
    //-----   ASR Direct   ------------------------------------
    struct ASRDirect : public ASRBase
    {
        ASRDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASRDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ASR Indexed   -----------------------------------
    class ASRIndexed : public ASRBase
    {
    public:
        ASRIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASRIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ASR Extended   ----------------------------------
    struct ASRExtended : public ASRBase
    {
        ASRExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ASRExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
