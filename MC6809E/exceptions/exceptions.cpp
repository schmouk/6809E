#include <exception>
#include <format>
#include <string>

#include "exceptions.h"


namespace except
{
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

    
}
