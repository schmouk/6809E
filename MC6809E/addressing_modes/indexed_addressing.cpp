#include "./base_addressing.h"
#include "./indexed_addressing.h"

#include "../architecture/hw_architecture.h"
#include "../cpu/cpu_registers.h"
#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace addr
{
    //=====   Indexed Addressing   ============================
    //---------------------------------------------------------
    IndexedAddressingMode::IndexedAddressingMode(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     post_byte
    ) noexcept
        : BaseAddressingMode()
        , _post_byte{ post_byte }
    {
        // Sets the internal pointer to the indexing register
        constexpr memory::Byte REG_MASK{ 0b0110'0000 };
        switch ((post_byte & REG_MASK) >> 5) {
        case 0b00:
            _indexing_reg_ptr = &(hw_arch.regX);
            break;

        case 0b01:
            _indexing_reg_ptr = &(hw_arch.regY);
            break;

        case 0b10:
            _indexing_reg_ptr = &(hw_arch.regU);
            break;

        case 0b11:
            _indexing_reg_ptr = &(hw_arch.regS);
            break;
        }
    }

    //---------------------------------------------------------
    cpu::CPUIndexRegister* IndexedAddressingMode::get_indexing_reg_ptr() const noexcept
    {
        return _indexing_reg_ptr;
    }

    //---------------------------------------------------------
    const memory::Byte IndexedAddressingMode::get_post_byte() const noexcept
    {
        return _post_byte;
    }


    //=====   Zero-Offset Indexed Addressing   ================
    //---------------------------------------------------------
    ZeroOffsetIndexedAddressing::ZeroOffsetIndexedAddressing(
        archi::HWArchitecture& hw_arch,
        const memory::Byte     post_byte
    ) noexcept
        : IndexedAddressingMode(hw_arch, post_byte)
    {}

}
