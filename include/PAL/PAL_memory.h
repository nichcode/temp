
#pragma once

#include "PAL_defines.h"

typedef void*(*PAL_AllocFunc)(u64 size);
typedef void(*PAL_FreeFunc)(void* memory);
typedef void*(*PAL_MemSetFunc)(void* memory, i32 value, u64 size);
typedef void*(*PAL_MemCopyFunc)(void* dest_memory, const void* src_memory, u64 size);

struct PAL_Allocator
{
    PAL_AllocFunc alloc;
    PAL_FreeFunc free;
    PAL_MemSetFunc set;
    PAL_MemCopyFunc copy;
};