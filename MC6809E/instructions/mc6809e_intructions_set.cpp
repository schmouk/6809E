#include <vector>

#include "./base_instruction.h"
#include "./mc6809e_intructions_set.h"

#include "../exceptions/exceptions.h"
#include "../memory/types.h"


namespace instr
{
    //=====   MC6809E CPU Instructions Set   ==================
    //---------------------------------------------------------
    MC6809InstructionsSet::MC6809InstructionsSet() noexcept
    {
        //TODO: Implement this
    }

    //---------------------------------------------------------
    const BaseInstruction* MC6809InstructionsSet::get(const memory::Byte op_code)
    {
        BaseInstruction* ret_instr_ptr{ _instr_set[op_code] };

        if (ret_instr_ptr)
            return ret_instr_ptr;
        else
            throw except::InvalidInstructionOpCodeException(op_code);
    }
    
    //---------------------------------------------------------
    const BaseInstruction* MC6809InstructionsSet::get(const memory::Byte op_code1, const memory::Byte op_code2)
    {
        BaseInstruction* ret_instr_ptr{ nullptr };

        switch (op_code1) {
        case 0x10:
            ret_instr_ptr = _instr_set_2[op_code2];
            break;

        case 0x11:
            ret_instr_ptr = _instr_set_3[op_code2];
            break;

        default:
            throw except::InvalidInstructionOpCodeException(op_code1, op_code2);
        }

        if (ret_instr_ptr)
            return ret_instr_ptr;
        else
            throw except::InvalidInstructionOpCodeException(op_code1, op_code2);
    }
    
    //---------------------------------------------------------
    const BaseInstruction* MC6809InstructionsSet::get(std::vector<memory::Byte> op_code)
    {
        switch (op_code.size()) {
        case 1:
            return get(op_code[0]);

        case 2:
            return get(op_code[0], op_code[1]);

        default:
            throw except::InvalidInstructionOpCodeException(op_code);
        }
    }

    //---------------------------------------------------------
    void MC6809InstructionsSet::set(const BaseInstruction* instr_ptr) noexcept
    {
    }

}