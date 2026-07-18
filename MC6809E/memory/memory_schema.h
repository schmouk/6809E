#pragma once

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <string>
#include <vector>

#include "./memory_addresses.h"
#include "./types.h"


/**
* This file defines memory schemas - i.e. the memory mappings.
*/

namespace memory
{
    //=====   Memory schemas   ================================
    class MemorySchema
    {
    public:
        //-----   Constructors / Destructor   -----------------
        MemorySchema() noexcept;

        template<typename... RangeTs>
            requires (std::derived_from<RangeTs, memory::BaseMemAddrRange> && ...)
        MemorySchema(RangeTs... ranges) noexcept;

        MemorySchema(const MemorySchema&) noexcept = default;
        MemorySchema(MemorySchema&&) noexcept = default;

        virtual ~MemorySchema() noexcept = default;


        //-----   Operators   ---------------------------------
        MemorySchema& operator= (const MemorySchema&) noexcept = default;
        MemorySchema& operator= (MemorySchema&&) noexcept = default;

        memory::Byte& operator[] (const memory::MemAddr addr);
        const memory::Byte operator[] (const memory::MemAddr addr) const;


        //-----   Operations   --------------------------------
        template<typename... RangeTs>
            requires (std::derived_from<RangeTs, memory::BaseMemAddrRange> && ...)
        void add_range(RangeTs... ranges) noexcept;

        void add_sized_range(const memory::MemAddr low_addr, const std::size_t size);

        const memory::Byte get_byte(const memory::MemAddr addr) const;
        void               set_byte(const memory::MemAddr addr, const memory::Byte val);

        const memory::Word get_word(const memory::MemAddr addr) const;
        void               set_word(const memory::MemAddr addr, const memory::Word val);


    private:
        std::vector<memory::Byte> _content;
        std::vector<std::uint8_t> _valid;

        memory::Byte& _get(const memory::MemAddr addr);
        const memory::Byte& _get(const memory::MemAddr addr) const;

    };


    //=====   IMPLEMENTATIONS   ===============================
    //---------------------------------------------------------
    template<typename... RangeTs>
        requires (std::derived_from<RangeTs, memory::BaseMemAddrRange> && ...)
    MemorySchema::MemorySchema(RangeTs... ranges) noexcept
        : _content(memory::MEM_MAX_SIZE, 0x00)
        , _valid(memory::MEM_MAX_SIZE, false)
    {
        add_range(ranges...);
    }

    //---------------------------------------------------------
    template<typename... RangeTs>
        requires (std::derived_from<RangeTs, memory::BaseMemAddrRange> && ...)
    void MemorySchema::add_range(RangeTs... ranges) noexcept
    {
        for (auto range : ranges)
            std::ranges::fill_n(_valid.begin() + range.LOW_ADDR, range.size(), true);
    }

}
