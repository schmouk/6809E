#pragma once

#include <concepts>
#include <cstdint>

#include "./indexed_addressing.h"
#include "./relative_addressing.h"

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
        inline OffsetIndexedAddressingMode(archi::HWArchitecture& hw_arch_) noexcept;

        virtual ~OffsetIndexedAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const;
        virtual const memory::Word  get_addressed_word() const;

        virtual void set_addressed_byte(const memory::Byte byte_value);
        virtual void set_addressed_word(const memory::Word word_value);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        memory::Offset _offset{ 0 };

        virtual const memory::Offset _evaluate_offset() const;

    };


    //=====   Offset Indirect Indexed Addressing   ===========
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    class OffsetIndirectIndexedAddressingModeT : public OffsetIndexedAddrT
    {
    public:
        inline OffsetIndirectIndexedAddressingModeT(archi::HWArchitecture& hw_arch_);

        virtual ~OffsetIndirectIndexedAddressingModeT() noexcept = default;

        virtual const memory::Byte  get_addressed_byte() const override;
        virtual const memory::Word  get_addressed_word() const override;

        virtual void set_addressed_byte(const memory::Byte byte_value);
        virtual void set_addressed_word(const memory::Word word_value);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;


    private:
        const memory::MemAddr _evaluate_indirect_address() const;

    };


    //=====   IMPLEMENTATIONS   ===============================
    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::OffsetIndirectIndexedAddressingModeT(
        archi::HWArchitecture& hw_arch_
    )
        : OffsetIndexedAddrT(hw_arch_)
    {}

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    const memory::Byte OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_addressed_byte() const
    {
        return OffsetIndexedAddrT::hw_arch.get_byte(_evaluate_indirect_address());
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    const memory::Word OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_addressed_word() const
    {
        return OffsetIndexedAddrT::hw_arch.get_word(_evaluate_indirect_address());
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    void OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::set_addressed_byte(
        const memory::Byte byte_value
    )
    {
        return OffsetIndexedAddrT::hw_arch.set_byte(_evaluate_indirect_address(), byte_value);
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    void OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::set_addressed_word(
        const memory::Word word_value
    )
    {
        return OffsetIndexedAddrT::hw_arch.set_word(_evaluate_indirect_address(), word_value);
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    const std::uint64_t OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_byte_cycles() const
    {
        return 3 + OffsetIndexedAddrT::get_byte_cycles();
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    const std::uint64_t OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::get_word_cycles() const
    {
        return 3 + OffsetIndexedAddrT::get_word_cycles();
    }

    //---------------------------------------------------------
    template<typename OffsetIndexedAddrT>
        requires (std::derived_from<OffsetIndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::derived_from<OffsetIndexedAddrT, OffsetRelativeAddressing>)
    const memory::MemAddr OffsetIndirectIndexedAddressingModeT<OffsetIndexedAddrT>::_evaluate_indirect_address() const
    {
        const memory::MemAddr indirect_addr{
            memory::MemAddr(OffsetIndexedAddrT::get_addressed_word())
        };
        const memory::MemAddr final_addr{ memory::MemAddr(OffsetIndexedAddrT::hw_arch.get_word(indirect_addr)) };
        return final_addr;
    }

}
