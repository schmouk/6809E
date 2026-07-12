#pragma once

#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <type_traits>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"


/**
* This file defines the many memory addressing modes of the microprocessor MC6809E:
* 
* - struct InherentAddressing                           : public BaseAddressingMode;
* - struct ImmediateAddressing                          : public BaseAddressingMode;
* - struct ExtendedAddressing                           : public BaseAddressingMode;
* - struct ExtendedIndirectAddressing                   : public BaseAddressingMode;
* - struct DirectAddressing                             : public BaseAddressingMode;
* - class  RegisterAddressing                           : public BaseAddressingMode;
* - class  OffsetIndexedAddressingMode                  : public BaseAddressingMode;
* - struct ZeroOffsetIndexedAddressing                  : public OffsetIndexedAddressingMode;
* - struct Constant5bitsOffsetIndexedAddressing         : public OffsetIndexedAddressingMode;
* - struct Constant8bitsOffsetIndexedAddressing         : public OffsetIndexedAddressingMode;
* - struct Constant16bitsOffsetIndexedAddressing        : public OffsetIndexedAddressingMode;
* - struct AccAOffsetIndexedAddressing                  : public OffsetIndexedAddressingMode;
* - struct AccBOffsetIndexedAddressing                  : public AccAOffsetIndexedAddressing;
* - struct AccDOffsetIndexedAddressing                  : public OffsetIndexedAddressingMode;
* - template<const memory::Word POST_INC = 1>
*   struct PostIncrementIndexedAddressing               : public BaseAddressingMode;
* - template<const memory::Word PRE_DEC = 1>
*   struct PreDecrementIndexedAddressing                : public BaseAddressingMode;
* - template<typename IndexedAddrT>
*   struct OffsetIndirectIndexedAddressingModeT         : public IndexedAddrT;
* - using  ZeroOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<ZeroOffsetIndexedAddressing>;
* - using  Constant5bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant5bitsOffsetIndexedAddressing>;
* - using  Constant8bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant8bitsOffsetIndexedAddressing>;
* - using  Constant16bitsOffsetIndirectIndexedAddressing= OffsetIndirectIndexedAddressingModeT<Constant16bitsOffsetIndexedAddressing>;
* - using  AccAOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<AccAOffsetIndexedAddressing>;
* - using  AccBOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<AccBOffsetIndexedAddressing>;
* - using  AccDOffsetIndirectIndexedAddressing          = OffsetIndirectIndexedAddressingModeT<AccDOffsetIndexedAddressing>;
* - using  PostIncrementIndirectIndexedAddressing       = OffsetIndirectIndexedAddressingModeT<PostIncrementIndexedAddressing<2>>;
* - using  PreDecrementIndirectIndexedAddressing        = OffsetIndirectIndexedAddressingModeT<PreDecrementIndexedAddressing<2>>;
* - struct OffsetRelativeAddressing                     : public BaseAddressingMode;
* - struct ShortRelativeAddressing                      : public OffsetRelativeAddressing;
* - struct LongRelativeAddressing                       : public OffsetRelativeAddressing;
* - struct ProgramCounterShortRelativeAddressing        : public ShortRelativeAddressing
* - struct ProgramCounterLongRelativeAddressing         : public LongRelativeAddressing;
* - struct ProgramCounterShortRelativeIndexedAddressing : public ShortRelativeAddressing;
* - struct ProgramCounterLongRelativeIndexedAddressing  : public LongRelativeAddressing
* - struct ExtendedIndirectIndexedAddressing            : public BaseAddressingMode;
* 
* - BaseAddressingClass& make_indexed_addressing_class(const memory::Byte mode_post_byte);
*/

namespace addr
{





    //=====   Indexed Addressing   ============================

    //-----   Accumulator A Offset Indexed Addressing   ---------
    class AccAOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        inline AccAOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);
        virtual ~AccAOffsetIndexedAddressing() noexcept = default;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(archi::HWArchitecture& hw_arch, const memory::Byte post_byte) override;
    };


    //-----   Accumulator B Offset Indexed Addressing   ---------
    class AccBOffsetIndexedAddressing : public AccAOffsetIndexedAddressing
    {
    public:
        inline AccBOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);
        virtual ~AccBOffsetIndexedAddressing() noexcept = default;

    protected:
        virtual const memory::Offset _evaluate_offset(archi::HWArchitecture& hw_arch, const memory::Byte post_byte) override;
    };


    //-----   Accumulator D Offset Indexed Addressing   ---------
    class AccDOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
    public:
        inline AccDOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);
        virtual ~AccDOffsetIndexedAddressing() noexcept = default;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(archi::HWArchitecture& hw_arch, const memory::Byte post_byte) override;
    };


    //-----   Post Increment Indexed Addressing   -------------
    template<const memory::Word POST_INC = 1>
    class PostIncrementIndexedAddressing : public BaseAddressingMode
    {
    public:
        inline PostIncrementIndexedAddressing(archi::HWArchitecture& hw_arch);
        virtual ~PostIncrementIndexedAddressing() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;

        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(archi::HWArchitecture& hw_arch, const memory::Byte post_byte) override;
    };


    //-----   Pre Decrement Indexed Addressing   --------------
    template<const memory::Word PRE_DEC = 1>
    class PreDecrementIndexedAddressing : public BaseAddressingMode
    {
    public:
        virtual const memory::Byte  get_addressed_byte(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;
        
        virtual const memory::Word  get_addressed_word(
            archi::HWArchitecture& hw_arch,
            cpu::CPUIndexRegister& reg
        ) const;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(archi::HWArchitecture& hw_arch, const memory::Byte post_byte) override;
    };


    //=====   Offset Indirect Indexed Addressing   ===========
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    class OffsetIndirectIndexedAddressingModeT : public IndexedAddrT
    {
    public:
        inline OffsetIndirectIndexedAddressingModeT(const memory::Offset offset = 0) noexcept;

        virtual ~OffsetIndirectIndexedAddressingModeT() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch, const cpu::CPUIndexRegister& reg) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch, const cpu::CPUIndexRegister& reg) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        virtual const memory::Offset _evaluate_offset(archi::HWArchitecture& hw_arch, const memory::Byte post_byte) override;
    };

    //-----   Specializations   -------------------------------
    using ZeroOffsetIndirectIndexedAddressing           = OffsetIndirectIndexedAddressingModeT<ZeroOffsetIndexedAddressing>;
    using Constant5bitsOffsetIndirectIndexedAddressing  = OffsetIndirectIndexedAddressingModeT<Constant5bitsOffsetIndexedAddressing>;
    using Constant8bitsOffsetIndirectIndexedAddressing  = OffsetIndirectIndexedAddressingModeT<Constant8bitsOffsetIndexedAddressing>;
    using Constant16bitsOffsetIndirectIndexedAddressing = OffsetIndirectIndexedAddressingModeT<Constant16bitsOffsetIndexedAddressing>;
    using AccAOffsetIndirectIndexedAddressing           = OffsetIndirectIndexedAddressingModeT<AccAOffsetIndexedAddressing>;
    using AccBOffsetIndirectIndexedAddressing           = OffsetIndirectIndexedAddressingModeT<AccBOffsetIndexedAddressing>;
    using AccDOffsetIndirectIndexedAddressing           = OffsetIndirectIndexedAddressingModeT<AccDOffsetIndexedAddressing>;
    using PostIncrementIndirectIndexedAddressing        = OffsetIndirectIndexedAddressingModeT<PostIncrementIndexedAddressing<2>>;
    using PreDecrementIndirectIndexedAddressing         = OffsetIndirectIndexedAddressingModeT<PreDecrementIndexedAddressing<2>>;

    //-----   Factory creation of Indexed Addressing Mode Classes   -----
    std::unique_ptr<BaseAddressingMode> make_indexed_addressing_class(archi::HWArchitecture& hw_arch);


    //=====   Relative Addressing   ===========================
    //-----   Offsets Relative Addressing Base Class   --------
    struct OffsetRelativeAddressing : public BaseAddressingMode
    {
        virtual const memory::Offset get_offset(archi::HWArchitecture& hw_arch) const = 0;

        //virtual const std::uint64_t get_byte_cycles() const = 0;
        //virtual const std::uint64_t get_word_cycles() const = 0;
    };


    //-----   Short Relative Branching   ----------------------
    struct ShortRelativeAddressing : public OffsetRelativeAddressing
    {
        virtual const memory::Offset get_offset(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----    Long Relative Branching   ----------------------
    struct LongRelativeAddressing : public OffsetRelativeAddressing
    {
        virtual const memory::Offset get_offset(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Program Counter Relative Addressing   -----------
    //---------------------------------------------------------
    struct ProgramCounterShortRelativeAddressing : public ShortRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    struct ProgramCounterLongRelativeAddressing : public LongRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    struct ProgramCounterShortRelativeIndexedAddressing : public ShortRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    struct ProgramCounterLongRelativeIndexedAddressing : public LongRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };


    //=====   Extended Indirect Indexed Addressing   ==========
    struct ExtendedIndirectIndexedAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };



    //=====   IMPLEMENTATIONS   ===============================
    //-----   Post Increment Indexed Addressing   -------------
    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    PostIncrementIndexedAddressing<POST_INC>::PostIncrementIndexedAddressing(archi::HWArchitecture& hw_arch)
    {

    }

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
        return hw_arch.get_byte(reg()) ;
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

    //-----   Offset Indirect Indexed Addressing   -----------
    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::OffsetIndirectIndexedAddressingModeT(
        const memory::Offset offset
    ) noexcept
        : IndexedAddrT(offset)
    {}

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const memory::Byte OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_addressed_byte(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(hw_arch)) };
        const memory::MemAddr final_addr{ memory::MemAddr(hw_arch.get_word(indirect_addr)) };
        return hw_arch.get_byte(final_addr);
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const memory::Word OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_addressed_word(
        archi::HWArchitecture& hw_arch
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(hw_arch)) };
        const memory::MemAddr final_addr{ memory::MemAddr(hw_arch.get_word(indirect_addr)) };
        return hw_arch.get_word(final_addr);
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const memory::Byte OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_addressed_byte(
        archi::HWArchitecture&       hw_arch,
        const cpu::CPUIndexRegister& reg
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(hw_arch, reg)) };
        const memory::MemAddr final_addr{ memory::MemAddr(hw_arch.get_word(indirect_addr)) };
        return hw_arch.get_byte(final_addr);
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const memory::Word  OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_addressed_word(
        archi::HWArchitecture&       hw_arch,
        const cpu::CPUIndexRegister& reg
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(hw_arch, reg)) };
        const memory::MemAddr final_addr{ memory::MemAddr(hw_arch.get_word(indirect_addr)) };
        return hw_arch.get_word(final_addr);
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const std::uint64_t OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_byte_cycles() const
    {
        return 3 + IndexedAddrT::get_byte_cycles();
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const std::uint64_t OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_word_cycles() const
    {
        return 3 + IndexedAddrT::get_word_cycles();
    }

}
