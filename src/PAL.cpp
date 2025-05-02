
#include "PAL_pch.h"
#include "PAL/PAL.h"

i32 PAL_Init()
{
    std::cout << "PAL Initialized" << std::endl;
    return 0;
}

void PAL_Terminate()
{
    std::cout << "PAL Terminated" << std::endl;
}