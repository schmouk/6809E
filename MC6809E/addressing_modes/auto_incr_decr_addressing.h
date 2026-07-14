#pragma once

#include <cstdint>

#include "./indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Post Increment Indexed Addressing   =============
    template<const memory::Word POST_INC = 1>
    struct PostIncrementIndexedAddressing : public IndexedAddressingMode
    {
        inline PostIncrementIndexedAddressing(archi::HWArchitecture& hw_arch);
        virtual ~PostIncrementIndexedAddressing() noexcept = default;

        virtual const memory::Byte get_addressed_byte(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;

        virtual const memory::Word get_addressed_word(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;

        void set_addressed_byte(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg,
            const memory::Byte     byte_val
        );

        void set_addressed_word(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg,
            const memory::Word     word_val
        );

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Pre Decrement Indexed Addressing   ==============
    template<const memory::Word PRE_DEC = 1>
    struct PreDecrementIndexedAddressing : public IndexedAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;

        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;

        void set_addressed_byte(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg,
            const memory::Byte     byte_val
        );

        void set_addressed_word(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg,
            const memory::Word     word_val
        );

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   IMPLEMENTATIONS   ===============================
    //-----   Post Increment Indexed Addressing   -------------
    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    PostIncrementIndexedAddressing<POST_INC>::PostIncrementIndexedAddressing(archi::HWArchitecture& hw_arch)
    {}

    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    const memory::Byte PostIncrementIndexedAddressing<POST_INC>::get_addressed_byte(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg
    ) const
    {
        const memory::Byte byte{ hw_arch.get_byte(reg()) };
        reg += POST_INC;
        return byte;
    }

    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    const memory::Word  PostIncrementIndexedAddressing<POST_INC>::get_addressed_word(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg
    ) const
    {
        const memory::Word word{ hw_arch.get_word(reg()) };
        reg += POST_INC;
        return word;
    }

    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    void PostIncrementIndexedAddressing<POST_INC>::set_addressed_byte(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg,
        const memory::Byte     byte_val
    )
    {
        hw_arch.set_byte(reg(), byte_val);
        reg += POST_INC;
    }

    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    void PostIncrementIndexedAddressing<POST_INC>::set_addressed_word(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg,
        const memory::Word     word_val
    )
    {
        hw_arch.set_word(reg(), word_val);
        reg += POST_INC;
    }

    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    const std::uint64_t PostIncrementIndexedAddressing<POST_INC>::get_byte_cycles() const
    {
        return 1 + POST_INC;
    }

    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    const std::uint64_t PostIncrementIndexedAddressing<POST_INC>::get_word_cycles() const
    {
        return 1 + POST_INC;
    }


    //-----   Pre Decrement Indexed Addressing   --------------
    //---------------------------------------------------------
    template<const memory::Word PRE_DEC>
    const memory::Byte PreDecrementIndexedAddressing<PRE_DEC>::get_addressed_byte(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg
    ) const
    {
        reg -= PRE_DEC;
        return hw_arch.get_byte(reg());
    }

    //---------------------------------------------------------
    template<const memory::Word PRE_DEC>
    const memory::Word  PreDecrementIndexedAddressing<PRE_DEC>::get_addressed_word(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg
    ) const
    {
        reg -= PRE_DEC;
        return hw_arch.get_word(reg());
    }

    //---------------------------------------------------------
    template<const memory::Word PRE_DEC>
    void PreDecrementIndexedAddressing<PRE_DEC>::set_addressed_byte(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg,
        const memory::Byte     byte_val
    )
    {
        hw_arch.set_byte(reg(), byte_val);
        reg -= PRE_DEC;
    }

    //---------------------------------------------------------
    template<const memory::Word PRE_DEC>
    void PreDecrementIndexedAddressing<PRE_DEC>::set_addressed_word(
        archi::HWArchitecture& hw_arch,
        cpu::CPUIndexRegister& reg,
        const memory::Word     word_val
    )
    {
        hw_arch.set_word(reg(), word_val);
        reg -= PRE_DEC;
    }

    //---------------------------------------------------------
    template<const memory::Word PRE_DEC>
    const std::uint64_t PreDecrementIndexedAddressing<PRE_DEC>::get_byte_cycles() const
    {
        return 1 + PRE_DEC;
    }

    //---------------------------------------------------------
    template<const memory::Word PRE_DEC>
    const std::uint64_t PreDecrementIndexedAddressing<PRE_DEC>::get_word_cycles() const
    {
        return 1 + PRE_DEC;
    }

}
