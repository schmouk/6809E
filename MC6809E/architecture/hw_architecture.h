#pragma once

/**
* This file defines next classes:
* - class HWArchitecture;  // The HardWare Architecture running any MC6809E emulation
*/

#include "../cpu/microproc_unit.h"
#include "../memory/memory_schema.h"
#include "../memory/types.h"


namespace archi
{
    //=====   H/W Architecture   ==============================
    class HWArchitecture : public cpu::MicroprocUnit, public memory::MemorySchema
    {
    public:
        //-----   Constructors / Destructor   -----------------
        inline HWArchitecture() noexcept = default;
        virtual inline ~HWArchitecture() noexcept = default;

        inline HWArchitecture(const HWArchitecture&) noexcept = default;
        inline HWArchitecture(HWArchitecture&&) noexcept = default;

        HWArchitecture(memory::MemorySchema& mem_) noexcept;

        //-----   Accessors   ---------------------------------
        void clr_interrupts_wait();
        void set_interrupts_wait();
        const bool is_waiting_interrupts();

        //-----   Operations   --------------------------------
        void set_memory_schema(const memory::MemorySchema& mem_) noexcept;

        const memory::Byte load_next_byte();                // PC register relative
        void  save_next_byte(const memory::Byte byte_val);  // PC register relative

        const memory::Word load_next_word();                // PC register relative
        void  save_next_word(const memory::Word word_val);  // PC register relative

        void run(const memory::MemAddr start_address);


    private:
        bool _waiting_interrupts{ false };
    };

}