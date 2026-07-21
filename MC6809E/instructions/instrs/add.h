#pragma once

#include <cstdint>
#include <memory>

#include "./adc.h"

#include "../../addressing_modes/base_addressing.h"
#include "../../architecture/hw_architecture.h"
#include "../../memory/types.h"


namespace instr
{
    //=====   ADD Base Class   ================================
    struct ADDBase : public ADCBase
    {
    public:
        ADDBase(archi::HWArchitecture& hw_arch, const memory::Byte opcode) noexcept;
        virtual ~ADDBase() noexcept = default;

    protected:
        const int  _evaluate_value(const int reg_value, const int mem_value) override;
        const memory::Word _evaluate_16(const int reg_value, const int mem_value);
    };


    //=====   ADDA   ==========================================
    //-----   ADDA Immediate   --------------------------------
    struct ADDAImmediate : public ADDBase
    {
        ADDAImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDAImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADDA Direct   -----------------------------------
    struct ADDADirect : public ADDBase
    {
        ADDADirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDADirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADDA Indexed   ----------------------------------
    class ADDAIndexed : public ADDBase
    {
    public:
        ADDAIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDAIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ADDA Extended   ---------------------------------
    struct ADDAExtended : public ADDBase
    {
        ADDAExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDAExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ADDB   ==========================================
    //-----   ADDB Immediate   --------------------------------
    struct ADDBImmediate : public ADDBase
    {
        ADDBImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDBImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADDB Direct   -----------------------------------
    struct ADDBDirect : public ADDBase
    {
        ADDBDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDBDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADDB Indexed   ----------------------------------
    class ADDBIndexed : public ADDBase
    {
    public:
        ADDBIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDBIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ADDB Extended   ---------------------------------
    struct ADDBExtended : public ADDBase
    {
        ADDBExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDBExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };


    //=====   ADDD   ==========================================
    //-----   ADDD Immediate   --------------------------------
    struct ADDDImmediate : public ADDBase
    {
        ADDDImmediate(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDDImmediate() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADDD Direct   -----------------------------------
    struct ADDDDirect : public ADDBase
    {
        ADDDDirect(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDDDirect() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

    //-----   ADDD Indexed   ----------------------------------
    class ADDDIndexed : public ADDBase
    {
    public:
        ADDDIndexed(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDDIndexed() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;

    private:
        std::unique_ptr<addr::BaseAddressingMode> _indexed_mode_ptr{ nullptr };
    };

    //-----   ADDD Extended   ---------------------------------
    struct ADDDExtended : public ADDBase
    {
        ADDDExtended(archi::HWArchitecture& hw_arch) noexcept;
        virtual ~ADDDExtended() noexcept = default;

        void exec() override;
        const std::uint64_t get_cycles_count() noexcept override;
    };

}
