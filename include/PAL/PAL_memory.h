
#pragma once

#include "PAL_defines.h"

typedef void* (*PAL_AllocFun)(u64 size);
typedef void  (*PAL_FreeFun)(void* memory);
typedef void* (*PAL_MemSetFun)(void* memory, i32 value, u64 size);
typedef void* (*PAL_MemCopyFun)(void* dest_memory, const void* src_memory, u64 size);

struct PAL_Allocator
{
    PAL_AllocFun alloc;
    PAL_FreeFun free;
    PAL_MemSetFun set;
    PAL_MemCopyFun copy;
};