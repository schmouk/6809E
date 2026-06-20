#include <cassert>
#include <exception>
#include <format>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>
#include <type_traits>

#include "./memory_addresses.h"
#include "./memory_schema.h"
#include "./types.h"
#include <algorithm>


namespace memory
{
    //=====   Memory Exception   ==============================
    //---------------------------------------------------------
    MemoryException::MemoryException(const std::size_t faulty_addr) noexcept
        : std::exception()
        , _err_msg{}
        , _filepath{}
        , _faulty_addr{ faulty_addr }
        , _numline{}
        , _specified{ true }
    {}

    //---------------------------------------------------------
    MemoryException::MemoryException(
        std::string       filepath,
        const int         num_line,
        const std::size_t faulty_addr
    ) noexcept
        : std::exception()
        , _err_msg{}
        , _filepath{ filepath }
        , _faulty_addr{ faulty_addr }
        , _numline{ num_line }
        , _specified{ true }
    {}

    //---------------------------------------------------------
    const char* MemoryException::what() const noexcept
    {
        _err_msg = "Memory access violation";

        if (_specified) {
            _err_msg += std::format(": address 0x{:4x} is invalid", _faulty_addr);

            if (!_filepath.empty()) {
                _err_msg += std::format(" (file '{}', line {})", _filepath, _numline);
            }
        }

        return _err_msg.c_str();
    }

    //=====   Memory schemas   ================================
    //---------------------------------------------------------
    MemorySchema::MemorySchema() noexcept
        : _content(memory::MEM_MAX_SIZE, 0x00)
        , _valid(memory::MEM_MAX_SIZE, false)
    {}

    //---------------------------------------------------------
    memory::Byte& MemorySchema::operator[] (const memory::MemAddr addr)
    {
        return _get(addr);
    }

    //---------------------------------------------------------
    const memory::Byte& MemorySchema::operator[] (const memory::MemAddr addr) const
    {
        return operator[](addr);
    }

    //---------------------------------------------------------
    void MemorySchema::add_sized_range(const memory::MemAddr low_addr, const std::size_t size)
    {
        assert(low_addr + size <= memory::MEM_MAX_SIZE);
        std::ranges::fill_n(_valid.begin() + low_addr, size, true);
    }

    //---------------------------------------------------------
    const memory::Word MemorySchema::get_word(const memory::MemAddr addr) const
    {
        return get_word(addr);
    }

    //---------------------------------------------------------
    void MemorySchema::set_word(const memory::MemAddr addr, const memory::Word val)
    {
        const std::size_t base_addr{ addr };

        assert(base_addr + 1 < memory::MEM_MAX_SIZE);
        
        if (!_valid[base_addr] || !_valid[base_addr + 1])
            throw memory::MemoryException(std::size_t(base_addr + 1));

        _content[base_addr]     = memory::Byte(val >> 8);
        _content[base_addr + 1] = memory::Byte(val & 0xff);
    }

    //---------------------------------------------------------
    memory::Byte& MemorySchema::_get(const memory::MemAddr addr)
    {
        if (_valid[addr])
            return _content[addr];
        else
            throw memory::MemoryException(addr);
    }

}