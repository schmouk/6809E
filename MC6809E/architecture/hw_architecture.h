#pragma once

/**
* This file defines next classes:
* - class HWArchitecture;  // The HardWare Architecture running any MC6809E emulation
*/

#include <cstdint>
#include <utility>

#include "../cpu/microproc_unit.h"
#include "../cpu/cpu_registers.h"
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


        //-----   Operations   --------------------------------
        std::pair<cpu::CPURegister*, cpu::CPURegister*> get_registers_defs(const memory::Byte post_byte);

        const memory::Byte load_next_byte();                // PC register relative
        void  save_next_byte(const memory::Byte byte_val);  // PC register relative

        const memory::Word load_next_word();                // PC register relative
        void  save_next_word(const memory::Word word_val);  // PC register relative

        const std::uint64_t pull_system_stack(const memory::Byte ctrl_code); // Notice: returns a cycles-count
        const std::uint64_t push_system_stack(const memory::Byte ctrl_code); // Notice: returns a cycles-count
        const std::uint64_t pull_system_stack_all(); // Notice: returns a cycles-count
        const std::uint64_t push_system_stack_all(); // Notice: returns a cycles-count
        const std::uint64_t pull_system_stack_ccr(); // Notice: returns a cycles-count
        const std::uint64_t pull_system_stack_pcr(); // Notice: returns a cycles-count
        const std::uint64_t push_system_stack_pcr(); // Notice: returns a cycles-count

        const std::uint64_t pull_user_stack(const memory::Byte ctrl_code); // Notice: returns a cycles-count
        const std::uint64_t push_user_stack(const memory::Byte ctrl_code); // Notice: returns a cycles-count

        void run(const memory::MemAddr start_address);

        void set_memory_schema(const memory::MemorySchema& mem_) noexcept;

        const std::uint64_t wait_interrupt_synchronization(); // Notice: waits for any unmasked interruption

        //-----   Accessors / Mutators   ----------------------
        void clr_interrupts_wait();
        void set_interrupts_wait();
        const bool is_waiting_interrupts() const;


    private:
        memory::Byte _waiting_interrupts{ false };

        cpu::CPURegister* _get_register_def(const memory::Byte def_4bits);

    };

}