#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   LSR Base Class   ================================
    class LSRBase : public BaseInstruction
    {
    public:
        LSRBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~LSRBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   LSRA   ==========================================
    //-----   LSRA Inherent   ---------------------------------
    struct LSRAInherent : public LSRBase
    {
        LSRAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LSRAInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LSRB   ==========================================
    //-----   LSRB Inherent   ---------------------------------
    struct LSRBInherent : public LSRBase
    {
        LSRBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LSRBInherent() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   LSR Memory   ====================================
    //-----   LSR Direct   ------------------------------------
    struct LSRDirect : public LSRBase
    {
        LSRDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LSRDirect() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   LSR Indexed   -----------------------------------
    class LSRIndexed : public LSRBase
    {
    public:
        LSRIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LSRIndexed() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   LSR Extended   ----------------------------------
    struct LSRExtended : public LSRBase
    {
        LSRExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~LSRExtended() noexcept = default;

        const std::uint64_t exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
