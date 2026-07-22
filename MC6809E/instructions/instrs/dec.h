#pragma once

#include <cstdint>
#include <memory>

#include "../base_instruction.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   DEC Base Class   ================================
    class DECBase : public BaseInstruction
    {
    public:
        DECBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~DECBase() noexcept = default;

    protected:
        const memory::Byte _evaluate(const int value);
        virtual void       _evaluate_cc_flags(const int intermediate_value);
        virtual const int  _evaluate_value(const int value);
    };


    //=====   DECA   ==========================================
    //-----   DECA Inherent   ---------------------------------
    struct DECAInherent : public DECBase
    {
        DECAInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~DECAInherent() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   DECB   ==========================================
    //-----   DECB Inherent   ---------------------------------
    struct DECBInherent : public DECBase
    {
        DECBInherent(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~DECBInherent() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   DEC Memory   ====================================
    //-----   DEC Direct   ------------------------------------
    struct DECDirect : public DECBase
    {
        DECDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~DECDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   DEC Indexed   -----------------------------------
    class DECIndexed : public DECBase
    {
    public:
        DECIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~DECIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   DEC Extended   ----------------------------------
    struct DECExtended : public DECBase
    {
        DECExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~DECExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
