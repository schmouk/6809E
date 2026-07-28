#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   TST Base Class   ================================
    class TSTBase : public BaseInstruction
    {
    public:
        TSTBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~TSTBase() noexcept = default;

    protected:
        virtual void _evaluate_cc_flags(const memory::Byte value);
    };


    //=====   TSTA   ==========================================
    //-----   TSTA Inherent   ---------------------------------
    struct TSTAInherent : public TSTBase
    {
        TSTAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~TSTAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   TSTB   ==========================================
    //-----   TSTB Inherent   ---------------------------------
    struct TSTBInherent : public TSTBase
    {
        TSTBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~TSTBInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   TST Memory   ====================================
    //-----   TST Direct   ------------------------------------
    struct TSTDirect : public TSTBase
    {
        TSTDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~TSTDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   TST Indexed   -----------------------------------
    class TSTIndexed : public TSTBase
    {
    public:
        TSTIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~TSTIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   TST Extended   ----------------------------------
    struct TSTExtended : public TSTBase
    {
        TSTExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~TSTExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
