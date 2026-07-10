#include "./hw_architecture.h"
#include "../cpu/microproc_unit.h"
#include "../memory/memory_schema.h"

namespace archi
{
    //---------------------------------------------------------
    HWArchitecture::HWArchitecture(memory::MemorySchema& mem_) noexcept
        : cpu::MicroprocUnit()
        , memory::MemorySchema()
    {}

    //---------------------------------------------------------
    void HWArchitecture::set_memory_schema(const memory::MemorySchema& mem_schema) noexcept
    {
        (void)memory::MemorySchema::operator=(mem_schema);
    }

}