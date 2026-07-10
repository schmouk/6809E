#include <cstdint>

#include "./microproc_unit.h"

#include "../exceptions/exceptions.h"
#include "../memory/types.h" 


namespace cpu
{
    //---------------------------------------------------------
    const memory::MemAddr MicroprocUnit::get_directpage_addr(const memory::Byte addr_low) const noexcept
    {
        return (memory::MemAddr(regDP()) << 8) | memory::MemAddr(addr_low);
    }

    //---------------------------------------------------------
    const memory::Word MicroprocUnit::get_reg_value(const cpu::EReg reg_index) const
    {
        switch (reg_index) {
            case cpu::EReg::D:
                return regD;
            case cpu::EReg::X:
                return regX;
            case cpu::EReg::Y:
                return regY;
            case cpu::EReg::U:
                return regU;
            case cpu::EReg::S:
                return regS;
            case cpu::EReg::PC:
                return regPC;
            case cpu::EReg::A:
                return regA;
            case cpu::EReg::B:
                return regB;
            case cpu::EReg::CC:
                return regCC;
            case cpu::EReg::DP:
                return regDP;
            default:
                throw except::InvalidRegisterCodeAddressingModeException(std::uint8_t(reg_index));
        }
    }

}