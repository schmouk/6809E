#include "./hw_architecture.h"
#include "../cpu/cpu6809e.h"
#include "../memory/memory_schema.h"

namespace archi
{
    //---------------------------------------------------------
    HWArchitecture::HWArchitecture(memory::MemorySchema& mem) noexcept
        : _mem{mem}
    {}

    //---------------------------------------------------------
    void HWArchitecture::set_memory_schema(memory::MemorySchema& mem) noexcept
    {
        _mem = mem;
    }

}