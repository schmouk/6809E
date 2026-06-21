#pragma once

/**
* This file defines MC6809E software exceptions
*/

#include <exception>
#include <string>


namespace except
{
    //=====   Memory Exception   ==============================
    class MemoryException : public std::exception
    {
    public:
        inline MemoryException() noexcept = default;
        inline MemoryException(const std::size_t faulty_addr) noexcept;

        virtual inline ~MemoryException() noexcept = default;

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
        inline OutOfMemoryWordAddrException(const std::size_t word_addr) noexcept;

        virtual inline ~OutOfMemoryWordAddrException() noexcept = default;

        const char* what() const noexcept override;

    private:
        mutable std::string _err_msg{};
    };


    //=====   Invalid Addressing Mode Exception   ==============
    class InvalidAddressingModeException : public std::exception
    {
    public:
        inline InvalidAddressingModeException(const std::string& err_msg = {}) noexcept;
        const char* what() const noexcept override;

    private:
        const std::string _err_msg{};
    };

}
