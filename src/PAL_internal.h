
#include "PAL/PAL.h"

struct PAL_Data
{
    PAL_Allocator allocator;
};

static PAL_Data s_Data;

PAL_Allocator PAL_GetAllocator();