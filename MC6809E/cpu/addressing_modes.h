#pragma once

#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <type_traits>

#include "./cpu_registers.h"

#include "../architecture/hw_architecture.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"


/**
* This file defines the many memory addressing modes of the microprocessor MC6809E:
* 
* - struct BaseAddressingMode;
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

namespace cpu
{
    //=====   Base Addressing Class   =========================
    struct BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const = 0;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const = 0;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch, const CPURegister& reg) const;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch, const CPURegister& reg) const;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch, const CPUIndexRegister& reg) const;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch, const CPUIndexRegister& reg) const;

        virtual const std::uint64_t get_byte_cycles() const = 0;
        virtual const std::uint64_t get_word_cycles() const = 0;
    };


    //=====   Inherent Addressing   ===========================
    struct InherentAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Immediate Addressing   ==========================
    struct ImmediateAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Extended Addressing   ===========================
    //-----   Extended Addressing   ---------------------------
    struct ExtendedAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

    //-----   Extended Indirect Addressing   ------------------
    struct ExtendedIndirectAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Direct Addressing   =============================
    struct DirectAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Register Addressing   ===========================
    class RegisterAddressing : public BaseAddressingMode
    {
    public:
        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

        std::initializer_list<cpu::EReg> evaluate_regs(const memory::Byte bytecode);


    private:
        static inline const bool _is_8bits(const cpu::EReg reg_ndx) {
            return (memory::Byte(reg_ndx) & 0b1000) == 0b1000;
        }

        static inline const bool _is_16bits(const cpu::EReg reg_ndx) {
            return (memory::Byte(reg_ndx) & 0b1000) == 0b0000;
        }

        static const cpu::EReg _get_reg_index(const memory::Byte reg_ndx);
    };


    //=====   Offset Indexed Addressing   =====================
    // Notice: base class for all offset indexed addressing modes.
    class OffsetIndexedAddressingMode : public BaseAddressingMode
    {
    public:
        inline OffsetIndexedAddressingMode(archi::HWArchitecture& hw_arch) noexcept;

        virtual ~OffsetIndexedAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        memory::Offset    _offset{ 0 };
        CPUIndexRegister* _indexing_reg_ptr{ nullptr };

        void _evaluate_indexing_register(archi::HWArchitecture& hw_arch) noexcept;
        const memory::Offset _evaluate_offset(const memory::Byte post_byte);

    };


    //=====   Indexed Addressing   ============================
    //-----   Zero-Offset Indexed Addressing   ----------------
    struct ZeroOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline ZeroOffsetIndexedAddressing(archi::HWArchitecture& hw_arch) noexcept;

        virtual ~ZeroOffsetIndexedAddressing() noexcept = default;
    };


    //-----   Constant 5-bits Offset Indexed Addressing   -----
    struct Constant5bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline Constant5bitsOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Constant 8-bits Offset Indexed Addressing   -----
    struct Constant8bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline Constant8bitsOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Constant 16-bits Offset Indexed Addressing   -----
    struct Constant16bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline Constant16bitsOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Accumulator A Offset Indexed Addressing   ---------
    struct AccAOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline AccAOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Accumulator B Offset Indexed Addressing   ---------
    struct AccBOffsetIndexedAddressing : public AccAOffsetIndexedAddressing
    {
        inline AccBOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);
    };


    //-----   Accumulator D Offset Indexed Addressing   ---------
    struct AccDOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline AccDOffsetIndexedAddressing(archi::HWArchitecture& hw_arch);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Post Increment Indexed Addressing   -------------
    template<const memory::Word POST_INC = 1>
    struct PostIncrementIndexedAddressing : public BaseAddressingMode
    {
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
    };


    //-----   Pre Decrement Indexed Addressing   --------------
    template<const memory::Word PRE_DEC = 1>
    struct PreDecrementIndexedAddressing : public BaseAddressingMode
    {
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
    };


    //=====   Offset Indirect Indexed Addressing   ===========
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    struct OffsetIndirectIndexedAddressingModeT : public IndexedAddrT
    {
        inline OffsetIndirectIndexedAddressingModeT(const memory::Offset offset = 0) noexcept;

        virtual ~OffsetIndirectIndexedAddressingModeT() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch, const cpu::CPUIndexRegister& reg) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch, const cpu::CPUIndexRegister& reg) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
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

    //-----   Factory creation of Addressing Mode Class   -----
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
