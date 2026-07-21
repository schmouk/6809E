#include "./hw_architecture.h"
#include "../cpu/microproc_unit.h"
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
    const bool HWArchitecture::is_waiting_interrupts()
    {
        return _waiting_interrupts;
    }

    //---------------------------------------------------------
    void HWArchitecture::set_memory_schema(const memory::MemorySchema& mem_schema) noexcept
    {
        (void)memory::MemorySchema::operator=(mem_schema);
    }

    //---------------------------------------------------------
    const memory::Byte HWArchitecture::load_next_byte()
    {
        const memory::Byte byte_value{ get_byte(regPC()) };
        regPC++;
        return byte_value;
    }

    //---------------------------------------------------------
    void  HWArchitecture::save_next_byte(const memory::Byte byte_val)
    {
        set_byte(regPC(), byte_val);
        regPC++;
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
    void HWArchitecture::run(const memory::MemAddr start_address)
    {
        //TODO: Implement this

    }

}