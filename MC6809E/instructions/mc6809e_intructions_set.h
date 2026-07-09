#pragma once

#include <vector>

#include "./base_instruction.h"
#include "../memory/types.h"


namespace instr
{
    //=====   MC6809E CPU Instructions Set   ==================
    class MC6809InstructionsSet
    {
    public:
        //-----   Constructor / Destructor   ------------------
        MC6809InstructionsSet() noexcept;
        virtual ~MC6809InstructionsSet() noexcept = default;

        //-----   Operations   --------------------------------
        const BaseInstruction* get(const memory::Byte op_code);
        const BaseInstruction* get(const memory::Byte op_code1, const memory::Byte op_code2);
        const BaseInstruction* get(std::vector<memory::Byte> op_code);

        void set(const BaseInstruction* instr_ptr) noexcept;


    private:
        //-----------------------------------------------------
        std::vector<BaseInstruction*> _instr_set  { 256, nullptr };  // Notice: 1-byte instructions set
        std::vector<BaseInstruction*> _instr_set_2{ 256, nullptr };  // Notice: Page 2 instructions set
        std::vector<BaseInstruction*> _instr_set_3{ 256, nullptr };  // Notice: Page 3 instructions set

    };

}