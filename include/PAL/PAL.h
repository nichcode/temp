
#include "PAL_memory.h"

struct PAL_InitData
{
    b8 custom_allocator = false;
    PAL_Allocator allocator;
};

PAL_API i32 PAL_Init(PAL_InitData init_data);
PAL_API void PAL_Terminate();