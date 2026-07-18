#pragma once

/**
* This file defines MC6809E software exceptions
*/

#include <cstdint>
#include <exception>
#include <string>
#include <vector>

#include "../memory/types.h"


namespace except
{
    //=====   H/W schema not set   ============================
    struct HWArchitectureNotSet : public std::exception
    {
        const char* what() const noexcept override;
    };


    //=====   Memory Exception   ==============================
    class MemoryException : public std::exception
    {
    public:
        MemoryException() noexcept = default;
        MemoryException(const std::size_t faulty_addr) noexcept;

        virtual ~MemoryException() noexcept = default;

        const char* what() const noexcept override;

    private:
        mutable std::string _err_msg{};
        const std::size_t   _faulty_addr{};

        bool _specified{ false };
    };


    //=====   Out Of Memory Word Address Exception   ==========
    class OutOfMemoryWordAddrException : public std::exception
    {
    public:
        OutOfMemoryWordAddrException(const std::size_t word_addr) noexcept;

        virtual ~OutOfMemoryWordAddrException() noexcept = default;

        const char* what() const noexcept override;

    private:
        mutable std::string _err_msg{};
    };


    //=====   Invalid Addressing Mode Exception   ==============
    class InvalidAddressingModeException : public std::exception
    {
    public:
        InvalidAddressingModeException(const std::string& err_msg = {}) noexcept;
        const char* what() const noexcept override;

    private:
        const std::string _err_msg{};
    };


    //=====   Invalid Register Addressing Mode Exception   =====
    struct InvalidRegisterAddressingModeException : public std::exception
    {
        const char* what() const noexcept override;
    };


    //=====   Invalid Register Code Addressing Mode Exception   =====
    class InvalidRegisterCodeAddressingModeException : public std::exception
    {
    public:
        InvalidRegisterCodeAddressingModeException(const std::uint8_t reg_code) noexcept;
        virtual ~InvalidRegisterCodeAddressingModeException() noexcept = default;

        const char* what() const noexcept override;

    private:
        const std::uint8_t  _reg_code{};
        mutable std::string _err_msg{};
    };


    //=====   Invalid 8-bits/16-bits mixing Register Addressing Mode Exception   =====
    struct InvalidMixedRegisterAddressingModeException : public std::exception
    {
        const char* what() const noexcept override;
    };


    //=====   Invalid Offset Addressing Mode Exception   ======
    struct InvalidOffsetAddressingModeException : public std::exception
    {
        const char* what() const noexcept override;
    };


    //=====   Invalid Instruction OpCode Exception   =========-
    class InvalidInstructionOpCodeException : public std::exception
    {
    public:
        InvalidInstructionOpCodeException(const memory::Byte op_code) noexcept;
        InvalidInstructionOpCodeException(const memory::Byte op_code1, const memory::Byte op_code2) noexcept;
        InvalidInstructionOpCodeException(const std::vector<memory::Byte>& op_code) noexcept;
        virtual ~InvalidInstructionOpCodeException() noexcept = default;

        const char* what() const noexcept override;

    private:
        const std::vector<memory::Byte>  _op_code{};
        mutable std::string _err_msg{};
    };

}
