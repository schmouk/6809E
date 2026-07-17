#pragma once

#include <concepts>
#include <cstdint>

#include "./indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Offset Indexed Addressing   =====================
    // The base class for all offset indexed addressing modes.
    class OffsetIndexedAddressingMode : public IndexedAddressingMode
    {
    public:
        inline OffsetIndexedAddressingMode(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) noexcept;

        virtual ~OffsetIndexedAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch
        ) const;

        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch
        ) const;

        virtual void set_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     byte_value
        );

        virtual void set_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::Word     word_value
        );

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        memory::Offset _offset{ 0 };

        virtual const memory::Offset _evaluate_offset(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) = 0;

    };


    //=====   Offset Indirect Indexed Addressing   ===========
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    class OffsetIndirectIndexedAddressingModeT : public OffsetIndexedAddrT
    {
    public:
        inline OffsetIndirectIndexedAddressingModeT(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) noexcept;

        virtual ~OffsetIndirectIndexedAddressingModeT() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch
        ) const override;

        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch
        ) const override;

        virtual void set_addressed_byte(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     byte_value
        );

        virtual void set_addressed_word(
            archi::HWArchitecture& hw_arch,
            const memory::Word     word_value
        );

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;


    private:
        const memory::MemAddr _evaluate_indirect_address(archi::HWArchitecture& hw_arch);

    };


    //=====   IMPLEMENTATIONS   ===============================
    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::OffsetIndirectIndexedAddressingModeT(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     post_byte
    ) noexcept
        : OffsetIndexedAddrT(hw_arch, post_byte)
    {}

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    const memory::Byte OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_addressed_byte(
            archi::HWArchitecture& hw_arch
        ) const
    {
        return hw_arch.get_byte(_evaluate_indirect_address(hw_arch));
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    const memory::Word OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_addressed_word(
            archi::HWArchitecture& hw_arch
        ) const
    {
        return hw_arch.get_word(_evaluate_indirect_address(hw_arch));
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    void OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::set_addressed_byte(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     byte_value
    )
    {
        return hw_arch.set_byte(_evaluate_indirect_address(hw_arch), byte_value);
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    void OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::set_addressed_word(
        archi::HWArchitecture& hw_arch,
        const memory::Word     word_value
    )
    {
        return hw_arch.set_word(_evaluate_indirect_address(hw_arch), word_value);
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    const std::uint64_t OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_byte_cycles() const
    {
        return 3 + OffsetIndexedAddrT::get_byte_cycles();
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    const std::uint64_t OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_word_cycles() const
    {
        return 3 + OffsetIndexedAddrT::get_word_cycles();
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode>
    const memory::MemAddr OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::_evaluate_indirect_address(
        archi::HWArchitecture& hw_arch
    )
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(OffsetIndexedAddrT::get_addressed_word(hw_arch)) };
        const memory::MemAddr final_addr{ memory::MemAddr(hw_arch.get_word(indirect_addr)) };
        return final_addr;
    }

}
