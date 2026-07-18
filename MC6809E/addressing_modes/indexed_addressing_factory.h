#pragma once

#include <memory>

#include "./base_addressing.h"

#include "../architecture/hw_architecture.h"


namespace addr
{
    //=====   Factory creation of Indexed Addressing Mode Classes   =====
    std::unique_ptr<BaseAddressingMode> make_indexed_addressing_class(archi::HWArchitecture& hw_arch);

}
