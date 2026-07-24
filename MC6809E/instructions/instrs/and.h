#pragma once

#include <cstdint>
#include <memory>

#include "./adc.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   AND Base Class   ================================
    class ANDBase : public ADCBase
    {
    public:
        ANDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~ANDBase() noexcept = default;

    protected:
        void       _evaluate_cc_flags(const int intermediate_value) override;
        const int  _evaluate_value(const int reg_value, const int mem_value) override;
    };


    //=====   ANDA   ==========================================
    //-----   ANDA Immediate   --------------------------------
    struct ANDAImmediate : public ANDBase
    {
        ANDAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDAImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ANDA Direct   -----------------------------------
    struct ANDADirect : public ANDBase
    {
        ANDADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDADirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ANDA Indexed   ----------------------------------
    class ANDAIndexed : public ANDBase
    {
    public:
        ANDAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDAIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ANDA Extended   ---------------------------------
    struct ANDAExtended : public ANDBase
    {
        ANDAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDAExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ANDB   ==========================================
    //-----   ANDB Immediate   --------------------------------
    struct ANDBImmediate : public ANDBase
    {
        ANDBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDBImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ANDB Direct   -----------------------------------
    struct ANDBDirect : public ANDBase
    {
        ANDBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDBDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ANDB Indexed   ----------------------------------
    class ANDBIndexed : public ANDBase
    {
    public:
        ANDBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDBIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ANDB Extended   ---------------------------------
    struct ANDBExtended : public ANDBase
    {
        ANDBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDBExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ANDCC   =========================================
    //-----   ANDCC Immediate   -------------------------------
    struct ANDCCImmediate : public ANDBase
    {
        ANDCCImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ANDCCImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
