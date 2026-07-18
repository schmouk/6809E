#include <cstdint>
#include <exception>
#include <format>
#include <string>
#include <vector>

#include "./exceptions.h"

#include "../memory/types.h"


namespace except
{
    //=====   H/W Architecture Schema Not Set Exception   =====
    //---------------------------------------------------------
    const char* HWArchitectureNotSet::what() const noexcept
    {
        return "Attempt to access to a not set Hardware Architecture.";
    }


    //=====   Memory Exception   ==============================
    //---------------------------------------------------------
    MemoryException::MemoryException(const std::size_t faulty_addr) noexcept
        : std::exception()
        , _err_msg{}
        , _faulty_addr{ faulty_addr }
        , _specified{ true }
    {}

    //---------------------------------------------------------
    const char* MemoryException::what() const noexcept
    {
        _err_msg = "Memory access violation";

        if (_specified) {
            _err_msg += std::format(": address 0x{:4x} is invalid", _faulty_addr);
        }

        return _err_msg.c_str();
    }


    //=====   Out Of Memory Word Address Exception   ==========
    //---------------------------------------------------------
    OutOfMemoryWordAddrException::OutOfMemoryWordAddrException(const std::size_t word_addr) noexcept
        : std::exception()
        , _err_msg{ std::format("Out of memory Word addressing: address 0x{:4x} is invalid", word_addr) }
    {}

    //---------------------------------------------------------
    const char* OutOfMemoryWordAddrException::what() const noexcept
    {
        return _err_msg.c_str();
    }


    //=====   Invalid Addressing Mode Exception   ==============
    //---------------------------------------------------------
    InvalidAddressingModeException::InvalidAddressingModeException(const std::string& err_msg) noexcept
        : std::exception()
        , _err_msg{ err_msg }
    {}

    //---------------------------------------------------------
    const char* InvalidAddressingModeException::what() const noexcept
    {
        return _err_msg.c_str();
    }


    //=====   Invalid Register Addressing Mode Exception   =====
    //---------------------------------------------------------
    const char* InvalidRegisterAddressingModeException::what() const noexcept
    {
        return "Invalid register addressing mode";
    }


    //=====   Invalid Register Code Addressing Mode Exception   =====
    //---------------------------------------------------------
    InvalidRegisterCodeAddressingModeException::InvalidRegisterCodeAddressingModeException(const std::uint8_t reg_code) noexcept
        : _reg_code{ reg_code }
    {}

    //---------------------------------------------------------
    const char* InvalidRegisterCodeAddressingModeException::what() const noexcept
    {
        _err_msg = std::format("Code '0x{:2X}' is an invalid register code for register addressing mode", _reg_code);
        return _err_msg.c_str();
    }


    //=====   Invalid 8-bits/16-bits mixing Register Addressing Mode Exception   =====
    //---------------------------------------------------------
    const char* InvalidMixedRegisterAddressingModeException::what() const noexcept
    {
        return "Invalid mixing of 8-bits and 16-bits registers on register addressing mode";
    }


    //=====   Invalid Indexing Post-Byte Exception   ==========
    //---------------------------------------------------------
    InvalidIndexingPostByteException::InvalidIndexingPostByteException(const memory::Byte post_byte) noexcept
        : std::exception()
        , _post_byte{ post_byte }
    {}

    //---------------------------------------------------------
    const char* InvalidIndexingPostByteException::what() const noexcept
    {
        _err_msg = std::format(
            "Invalid post_byte value for an indexed addressing mode ({:#08b})", _post_byte
        );
        
        return _err_msg.c_str();
    }


    //=====   Invalid Offset Addressing Mode Exception   ======
    //---------------------------------------------------------
    const char* InvalidOffsetAddressingModeException::what() const noexcept
    {
        return "Invalid offset addressing mode";
    }


    //=====   Invalid Register Code Addressing Mode Exception   =====
    //---------------------------------------------------------
    InvalidInstructionOpCodeException::InvalidInstructionOpCodeException(
        const memory::Byte op_code
    ) noexcept
        : _op_code{ 1, op_code }
    {}

    //---------------------------------------------------------
    InvalidInstructionOpCodeException::InvalidInstructionOpCodeException(
        const memory::Byte op_code1,
        const memory::Byte op_code2
    ) noexcept
        : _op_code{ op_code1, op_code2 }
    {}

    //---------------------------------------------------------
    InvalidInstructionOpCodeException::InvalidInstructionOpCodeException(
        const std::vector<memory::Byte>& op_code
    ) noexcept
        : _op_code{ op_code }
    {}

    //---------------------------------------------------------
    const char* InvalidInstructionOpCodeException::what() const noexcept
    {
        if (_op_code.size() == 1)
            _err_msg = std::format("Code '{:#20X}' is an invalid operating code for an MC6809E instruction", _op_code[0]);

        else if (_op_code.size() == 2)
            _err_msg = std::format("Code '{:#02X}{:02X}' is an invalid operating code for an MC6809E instruction", _op_code[0], _op_code[1]);

        else if (_op_code.empty())
            _err_msg = "operating code of length 0 is an invalid opcode for MC6809E instructions";

        else
            _err_msg = std::format(
                "operating code of length > 2 is an invalid opcode for MC6809E instructions ({:#02X}{:02X}{:02X}{})",
                _op_code[0], _op_code[1], _op_code[2], _op_code.size() == 3 ? "" : "..."
            );

        return _err_msg.c_str();
    }


    //=====   Not Implemented Method Exception   ==============
    //---------------------------------------------------------
    NotImplementedMethodException::NotImplementedMethodException(const std::string& method_name) noexcept
        : _method_name{ method_name }
    {}

    //---------------------------------------------------------
    const char* NotImplementedMethodException::what() const noexcept
    {
        _err_msg = std::format("method '{}' is not implemented", _method_name);
        return _err_msg.c_str();
    }

}
