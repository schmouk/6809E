#include <algorithm>
#include <cassert>
#include <vector>

#include "memory_addresses.h"
#include "memory_schema.h"
#include "types.h"

#include "../exceptions/exceptions.h"


namespace memory
{
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
        const std::size_t word_addr{ addr };

        if (word_addr >= memory::MEM_MAX_SIZE - 1)
            throw except::OutOfMemoryWordAddrException(word_addr);

        if (!_valid[word_addr] || !_valid[word_addr + 1])
            throw except::MemoryException(std::size_t(word_addr + 1));

        _content[word_addr]     = memory::Byte(val >> 8);
        _content[word_addr + 1] = memory::Byte(val & 0xff);
    }

    //---------------------------------------------------------
    memory::Byte& MemorySchema::_get(const memory::MemAddr addr)
    {
        if (_valid[addr])
            return _content[addr];
        else
            throw except::MemoryException(addr);
    }

}