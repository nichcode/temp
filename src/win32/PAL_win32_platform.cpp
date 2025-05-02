
#include "PAL_pch.h"
#include "PAL/PAL_memory.h"

PAL_API PAL_Allocator PAL_GetAllocator()
{
    PAL_Allocator allocator;
    allocator.alloc = malloc;
    allocator.free = free;
    allocator.copy = memcpy;
    allocator.set = memset;

    return allocator;
}