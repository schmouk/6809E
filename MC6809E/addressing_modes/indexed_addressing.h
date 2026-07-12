#pragma once

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Indexed Addressing   ============================
    // The base class for all indexed addressing mode - Notice: this is based on indexing registers
    class IndexedAddressingMode : public BaseAddressingMode
    {
    public:
        inline IndexedAddressingMode(archi::HWArchitecture& hw_arch, const memory::Byte post_byte) noexcept;
        virtual ~IndexedAddressingMode() noexcept = default;

        virtual const memory::Byte  get_addressed_byte(archi::HWArchitecture& hw_arch) const override;
        virtual const memory::Word  get_addressed_word(archi::HWArchitecture& hw_arch) const override;

        virtual inline void         save_addressed_byte(archi::HWArchitecture& hw_arch, const memory::Byte byte_value);
        virtual inline void         save_addressed_word(archi::HWArchitecture& hw_arch, const memory::Word word_value);

        inline cpu::CPUIndexRegister* get_indexing_reg_ptr() const noexcept;
        inline const memory::Byte     get_post_byte() const noexcept;


    private:
        cpu::CPUIndexRegister* _indexing_reg_ptr{ nullptr };
        memory::Byte           _post_byte{ 0 };
    };


    //=====   Zero-Offset Indexed Addressing   ================
    struct ZeroOffsetIndexedAddressing : public IndexedAddressingMode
    {
    public:
        inline ZeroOffsetIndexedAddressing(
            archi::HWArchitecture& hw_arch,
            const memory::Byte     post_byte
        ) noexcept;

        virtual ~ZeroOffsetIndexedAddressing() noexcept = default;
    };

}
