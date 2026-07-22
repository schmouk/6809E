#include <cstdint>
#include <utility>

#include "./hw_architecture.h"
#include "../cpu/microproc_unit.h"
#include "../cpu/cpu_registers.h"
#include "../exceptions/exceptions.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"


namespace archi
{
    //---------------------------------------------------------
    HWArchitecture::HWArchitecture(memory::MemorySchema& mem_) noexcept
        : cpu::MicroprocUnit()
        , memory::MemorySchema()
    {}

    //---------------------------------------------------------
    void HWArchitecture::clr_interrupts_wait()
    {
        _waiting_interrupts = false;
    }

    //---------------------------------------------------------
    void HWArchitecture::set_interrupts_wait()
    {
        _waiting_interrupts = true;
    }

    //---------------------------------------------------------
    const bool HWArchitecture::is_waiting_interrupts() const
    {
        return _waiting_interrupts;
    }

    //---------------------------------------------------------
    std::pair<cpu::CPURegister*, cpu::CPURegister*> HWArchitecture::get_registers_defs(const memory::Byte post_byte)
    {
        cpu::CPURegister* reg1_ptr{ _get_register_def(post_byte >> 4) };
        cpu::CPURegister* reg2_ptr{ _get_register_def(post_byte & 0x0f) };
        if (reg1_ptr->is_8bits() != reg2_ptr->is_8bits())
            throw except::InvalidMixedRegisterAddressingModeException();

        return { reg1_ptr, reg2_ptr };
    }

    //---------------------------------------------------------
    const memory::Byte HWArchitecture::load_next_byte()
    {
        return get_byte(regPC++);
    }

    //---------------------------------------------------------
    void  HWArchitecture::save_next_byte(const memory::Byte byte_val)
    {
        set_byte(regPC++, byte_val);
    }

    //---------------------------------------------------------
    const memory::Word HWArchitecture::load_next_word()
    {
        const memory::Word word_value{ get_word(regPC()) };
        regPC += 2;
        return word_value;
    }

    //---------------------------------------------------------
    void  HWArchitecture::save_next_word(const memory::Word word_val)
    {
        set_word(regPC(), word_val);
        regPC += 2;
    }

    //---------------------------------------------------------
    const std::uint64_t HWArchitecture::pull_system_stack(const memory::Byte ctrl_code)
    {
        std::uint64_t cycles_count{ 0 };

        if (ctrl_code & 0b000'001) {
            regCC = get_byte(regS++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b000'0010) {
            regA = get_byte(regS++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b000'0100) {
            regB = get_byte(regS++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b000'1000) {
            regDP = get_byte(regS++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0001'0000) {
            regX= get_word(regS);
            regS += 2;
            cycles_count += 3;
        }

        if (ctrl_code & 0b0010'0000) {
            regY = get_word(regS);
            regS += 2;
            cycles_count += 3;
        }

        if (ctrl_code & 0b0100'0000) {
            regU = get_word(regS);
            regS += 2;
            cycles_count += 3;
        }

        if (ctrl_code & 0b1000'0000) {
            regPC = get_word(regS);
            regS += 2;
            cycles_count += 3;
        }

        return cycles_count;
    }

    //---------------------------------------------------------
    const std::uint64_t HWArchitecture::push_system_stack(const memory::Byte ctrl_code)
    {
        std::uint64_t cycles_count{ 0 };

        if (ctrl_code & 0b1000'0000) {
            regS -= 2;
            set_word(regS, regPC);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0100'0000) {
            regS -= 2;
            set_word(regS, regU);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0010'0000) {
            regS -= 2;
            set_word(regS, regY);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0001'0000) {
            regS -= 2;
            set_word(regS, regX);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0000'1000) {
            set_word(--regS, regDP);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0000'0100) {
            set_word(--regS, regB);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0000'0010) {
            set_word(--regS, regA);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0000'0001) {
            set_word(--regS, regCC);
            cycles_count += 2;
        }

        return cycles_count;
    }

    //---------------------------------------------------------
    const std::uint64_t HWArchitecture::pull_user_stack(const memory::Byte ctrl_code)
    {
        std::uint64_t cycles_count{ 0 };

        if (ctrl_code & 0b000'001) {
            regCC = get_byte(regU++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b000'0010) {
            regA = get_byte(regU++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b000'0100) {
            regB = get_byte(regU++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b000'1000) {
            regDP = get_byte(regU++);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0001'0000) {
            regX = get_word(regU);
            regU += 2;
            cycles_count += 3;
        }

        if (ctrl_code & 0b0010'0000) {
            regY = get_word(regU);
            regU += 2;
            cycles_count += 3;
        }

        if (ctrl_code & 0b0100'0000) {
            regU = get_word(regU);
            regU += 2;
            cycles_count += 3;
        }

        if (ctrl_code & 0b1000'0000) {
            regPC = get_word(regU);
            regU += 2;
            cycles_count += 3;
        }

        return cycles_count;
    }

    //---------------------------------------------------------
    const std::uint64_t HWArchitecture::push_user_stack(const memory::Byte ctrl_code)
    {
        std::uint64_t cycles_count{ 0 };

        if (ctrl_code & 0b1000'0000) {
            regU -= 2;
            set_word(regU, regPC);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0100'0000) {
            regU -= 2;
            set_word(regU, regU);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0010'0000) {
            regU -= 2;
            set_word(regU, regY);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0001'0000) {
            regU -= 2;
            set_word(regU, regX);
            cycles_count += 3;
        }

        if (ctrl_code & 0b0000'1000) {
            set_word(--regU, regDP);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0000'0100) {
            set_word(--regU, regB);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0000'0010) {
            set_word(--regU, regA);
            cycles_count += 2;
        }

        if (ctrl_code & 0b0000'0001) {
            set_word(--regU, regCC);
            cycles_count += 2;
        }

        return cycles_count;
    }

    //---------------------------------------------------------
    void HWArchitecture::run(const memory::MemAddr start_address)
    {
        //TODO: Implement this
    }

    //---------------------------------------------------------
    void HWArchitecture::set_memory_schema(const memory::MemorySchema& mem_schema) noexcept
    {
        (void)memory::MemorySchema::operator=(mem_schema);
    }

    //---------------------------------------------------------
    cpu::CPURegister* HWArchitecture::_get_register_def(const memory::Byte def_4bits)
    {
        switch (cpu::EReg(def_4bits)) {
        case cpu::EReg::D:
            return &regD;

        case cpu::EReg::X:
            return &regX;

        case cpu::EReg::Y:
            return &regY;

        case cpu::EReg::U:
            return &regU;

        case cpu::EReg::S:
            return &regS;

        case cpu::EReg::PC:
            return &regPC;

        case cpu::EReg::A:
            return &regA;

        case cpu::EReg::B:
            return &regB;

        case cpu::EReg::CC:
            return &regCC;

        case cpu::EReg::DP:
            return &regDP;

        default:
            throw except::InvalidRegisterCodeAddressingModeException(def_4bits);
        }
    }

}