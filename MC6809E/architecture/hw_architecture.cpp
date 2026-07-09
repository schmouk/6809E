#include "./hw_architecture.h"
#include "../cpu/cpu6809e.h"
#include "../memory/memory_schema.h"

namespace archi
{
    //---------------------------------------------------------
    HWArchitecture::HWArchitecture(memory::MemorySchema& mem_) noexcept
        : mem{ mem_ }
    {}

    //---------------------------------------------------------
    void HWArchitecture::set_memory_schema(memory::MemorySchema& mem_) noexcept
    {
        mem = mem_;
    }

}