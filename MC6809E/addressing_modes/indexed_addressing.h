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
        IndexedAddressingMode(archi::HWArchitecture& hw_arch_) noexcept;
        virtual ~IndexedAddressingMode() noexcept = default;

        cpu::CPUIndexRegister* get_indexing_reg_ptr() const noexcept;
        const memory::Byte     get_post_byte() const noexcept;


    private:
        cpu::CPUIndexRegister* _indexing_reg_ptr{ nullptr };
        memory::Byte           _post_byte{ 0 };
    };

}
