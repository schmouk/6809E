// MC6809E.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdint>
#include <iostream>

#include "cpu/microproc_unit.h"
//#include "exceptions/exceptions.h"
#include "interruptions/interruptions_vector.h"
#include "memory/memory_addresses.h"
#include "memory/memory_schema.h"
#include "memory/types.h"


int main()
{
    std::int16_t v{ 0x0f };
    v -= 0x10;
    std::cout << v << std::endl;

    return 0;
}
