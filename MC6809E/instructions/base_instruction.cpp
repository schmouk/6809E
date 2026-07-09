#include <vector>

#include "./base_instruction.h"
#include "../memory/types.h"

namespace instr
{
    //---------------------------------------------------------
    BaseInstruction::BaseInstruction(const memory::Byte opcode) noexcept
        : _opcode{opcode}
    {}

    //---------------------------------------------------------
    BaseInstruction::BaseInstruction(const memory::Byte opcode1, const memory::Byte opcode2) noexcept
        : _opcode{ opcode1, opcode2 }
    {}

    //---------------------------------------------------------
    const bool BaseInstruction::operator== (const memory::Byte opcode) const noexcept
    {
        return _opcode.size() == 1 && _opcode[0] == opcode;
    }

    //---------------------------------------------------------
    const bool BaseInstruction::operator== (const std::vector<memory::Byte>& opcode) const noexcept
    {
        return _opcode == opcode;
    }

}