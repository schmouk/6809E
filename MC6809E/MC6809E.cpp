// MC6809E.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "cpu/cpu6809e.h"
#include "cpu/interruptions_vector.h"
#include "exceptions/exceptions.h"
#include "memory/memory_addresses.h"
#include "memory/memory_schema.h"
#include "memory/types.h"


int main()
{
    except::MemoryException except(__FILE__, __LINE__, 0x8000);
    return 0;
}
