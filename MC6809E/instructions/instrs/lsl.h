#pragma once

#include "./asl.h"


namespace instr
{

    //=====   LSLA   ==========================================
    //-----   LSLA Inherent   ---------------------------------
    using LSLAInherent = ASLAInherent;


    //=====   LSLB   ==========================================
    //-----   LSLB Inherent   ---------------------------------
    using LSLBInherent = ASLBInherent;


    //=====   LSL Memory   ====================================
    //-----   LSL Direct   ------------------------------------
    using LSLDirect = ASLDirect;

    //-----   LSL Indexed   -----------------------------------
    using LSLIndexed = ASLIndexed;

    //-----   LSL Extended   ----------------------------------
    using LSLExtended = ASLExtended;

}
