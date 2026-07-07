#pragma once

#include <cstdint>
#include <initializer_list>

#include "./cpu6809e.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"
#include <concepts>
#include <type_traits>


/**
* This file defines the many memory addressing modes of the microprocessor MC6809E
*/

namespace cpu
{
    //=====   Base Addressing Class   =========================
    struct BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const = 0;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const = 0;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::CPURegister& reg, memory::MemorySchema& mem) const;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::CPURegister& reg, memory::MemorySchema& mem) const;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const;

        virtual const std::uint64_t get_byte_cycles() const = 0;
        virtual const std::uint64_t get_word_cycles() const = 0;
    };


    //=====   Inherent Addressing   ===========================
    struct InherentAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Immediate Addressing   ==========================
    struct ImmediateAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Extended Addressing   ===========================
    //-----   Extended Addressing   ---------------------------
    struct ExtendedAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };

    //-----   Extended Indirect Addressing   ------------------
    struct ExtendedIndirectAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Direct Addressing   =============================
    struct DirectAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //=====   Register Addressing   ===========================
    class RegisterAddressing : public BaseAddressingMode
    {
    public:
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

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
        inline OffsetIndexedAddressingMode(const memory::Offset offset = 0) noexcept;

        virtual ~OffsetIndexedAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    protected:
        memory::Offset _offset{ 0 };
    };


    //=====   Indexed Addressing   ============================
    //-----   Zero-Offset Indexed Addressing   ----------------
    struct ZeroOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline ZeroOffsetIndexedAddressing(
            [[maybe_unused]] cpu::MicroprocUnit&   mpu,
            [[maybe_unused]] memory::MemorySchema& mem
        ) noexcept;

        virtual ~ZeroOffsetIndexedAddressing() noexcept = default;
    };


    //-----   Constant 5-bits Offset Indexed Addressing   -----
    struct Constant5bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline Constant5bitsOffsetIndexedAddressing(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Constant 8-bits Offset Indexed Addressing   -----
    struct Constant8bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline Constant8bitsOffsetIndexedAddressing(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Constant 16-bits Offset Indexed Addressing   -----
    struct Constant16bitsOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline Constant16bitsOffsetIndexedAddressing(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Accumulator A Offset Indexed Addressing   ---------
    struct AccAOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline AccAOffsetIndexedAddressing(cpu::MicroprocUnit& mpu, [[maybe_unused]] memory::MemorySchema& mem);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Accumulator B Offset Indexed Addressing   ---------
    struct AccBOffsetIndexedAddressing : public AccAOffsetIndexedAddressing
    {
        inline AccBOffsetIndexedAddressing(cpu::MicroprocUnit& mpu, [[maybe_unused]] memory::MemorySchema& mem);
    };


    //-----   Accumulator D Offset Indexed Addressing   ---------
    struct AccDOffsetIndexedAddressing : public OffsetIndexedAddressingMode
    {
        inline AccDOffsetIndexedAddressing(cpu::MicroprocUnit& mpu, [[maybe_unused]] memory::MemorySchema& mem);

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Post Increment Indexed Addressing   -------------
    template<const memory::Word POST_INC = 1>
    struct PostIncrementIndexedAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Pre Decrement Indexed Addressing   --------------
    template<const memory::Word PRE_DEC = 1>
    struct PreDecrementIndexedAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const;

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

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, const cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, const cpu::CPUIndexRegister& reg, memory::MemorySchema& mem) const override;

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


    //=====   Relative Addressing   ===========================
    //-----   Offsets Relative Addressing Base Class   --------
    struct OffsetRelativeAddressing : public BaseAddressingMode
    {
        virtual const memory::Offset get_offset(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const = 0;
    };


    //-----   Short Relative Branching   ----------------------
    struct ShortRelativeAddressing : public OffsetRelativeAddressing
    {
        virtual const memory::Offset get_offset(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----    Long Relative Branching   ----------------------
    struct LongRelativeAddressing : public OffsetRelativeAddressing
    {
        virtual const memory::Offset get_offset(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };


    //-----   Program Counter Relative Addressing   -----------
    //---------------------------------------------------------
    struct ProgramCounterShortRelativeAddressing : public ShortRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    struct ProgramCounterLongRelativeAddressing : public LongRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    struct ProgramCounterShortRelativeIndexedAddressing : public ShortRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };

    //---------------------------------------------------------
    struct ProgramCounterLongRelativeIndexedAddressing : public LongRelativeAddressing
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;

    };


    //=====   Extended Indirect Indexed Addressing   ==========
    struct ExtendedIndirectIndexedAddressing : public BaseAddressingMode
    {
        virtual const memory::Byte  get_addressed_byte(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;
        virtual const memory::Word  get_addressed_word(cpu::MicroprocUnit& mpu, memory::MemorySchema& mem) const override;

        virtual const std::uint64_t get_byte_cycles() const override;
        virtual const std::uint64_t get_word_cycles() const override;
    };



    //=====   IMPLEMENTATIONS   ===============================
    //-----   Post Increment Indexed Addressing   -------------
    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    const memory::Byte PostIncrementIndexedAddressing<POST_INC>::get_addressed_byte(
        cpu::MicroprocUnit&    mpu,
        cpu::CPUIndexRegister& reg,
        memory::MemorySchema&  mem
    ) const
    {
        const memory::Byte byte{ mem.get_byte(reg()) };
        reg += POST_INC;
        return byte;
    }

    //---------------------------------------------------------
    template<const memory::Word POST_INC>
    const memory::Word  PostIncrementIndexedAddressing<POST_INC>::get_addressed_word(
        cpu::MicroprocUnit&    mpu,
        cpu::CPUIndexRegister& reg,
        memory::MemorySchema&  mem
    ) const
    {
        const memory::Word word{ mem.get_word(reg()) };
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
        cpu::MicroprocUnit&    mpu,
        cpu::CPUIndexRegister& reg,
        memory::MemorySchema&  mem
    ) const
    {
        reg -= PRE_DEC;
        return mem.get_byte(reg()) ;
    }

    //---------------------------------------------------------
    template<const memory::Word PRE_DEC>
    const memory::Word  PreDecrementIndexedAddressing<PRE_DEC>::get_addressed_word(
        cpu::MicroprocUnit&    mpu,
        cpu::CPUIndexRegister& reg,
        memory::MemorySchema&  mem
    ) const
    {
        reg -= PRE_DEC;
        return mem.get_word(reg());
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
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(mpu, mem)) };
        const memory::MemAddr final_addr{ memory::MemAddr(mem.get_word(indirect_addr)) };
        return mem.get_byte(final_addr);
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const memory::Word OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_addressed_word(
        cpu::MicroprocUnit&   mpu,
        memory::MemorySchema& mem
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(mpu, mem)) };
        const memory::MemAddr final_addr{ memory::MemAddr(mem.get_word(indirect_addr)) };
        return mem.get_word(final_addr);
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const memory::Byte OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_addressed_byte(
        cpu::MicroprocUnit&          mpu,
        const cpu::CPUIndexRegister& reg,
        memory::MemorySchema&        mem
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(mpu, reg, mem)) };
        const memory::MemAddr final_addr{ memory::MemAddr(mem.get_word(indirect_addr)) };
        return mem.get_byte(final_addr);
    }

    //---------------------------------------------------------
    template<typename IndexedAddrT>
        requires (std::derived_from<IndexedAddrT, OffsetIndexedAddressingMode> ||
                  std::is_same_v<IndexedAddrT, PostIncrementIndexedAddressing<2>> ||
                  std::is_same_v<IndexedAddrT, PreDecrementIndexedAddressing<2>>)
    const memory::Word  OffsetIndirectIndexedAddressingModeT<IndexedAddrT>::get_addressed_word(
        cpu::MicroprocUnit&          mpu,
        const cpu::CPUIndexRegister& reg,
        memory::MemorySchema&        mem
    ) const
    {
        const memory::MemAddr indirect_addr{ memory::MemAddr(IndexedAddrT::get_addressed_word(mpu, reg, mem)) };
        const memory::MemAddr final_addr{ memory::MemAddr(mem.get_word(indirect_addr)) };
        return mem.get_word(final_addr);
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
