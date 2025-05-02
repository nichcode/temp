
#include "PAL_pch.h"
#include "PAL/PAL.h"

i32 PAL_Init(PAL_InitData init_data)
{
    if (init_data.custom_allocator) {
        s_Data.allocator = init_data.allocator;
    }
    else if (!init_data.custom_allocator) {
        s_Data.allocator = PAL_GetAllocator();
    }

    std::cout << "PAL Initialized" << std::endl;
    return 0;
}

void PAL_Terminate()
{
    std::cout << "PAL Terminated" << std::endl;
}