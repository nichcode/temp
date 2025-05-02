
#pragma once

#include "PAL_memory.h"
#include "PAL_log.h"
#include "PAL_window.h"
#include "PAL_input.h"

struct PAL_InitData
{
    b8 custom_allocator = false;
    PAL_Allocator allocator;
};

PAL_API i32 PAL_Init(PAL_InitData init_data);
PAL_API void PAL_Terminate();

PAL_API char* PAL_ToString(const wchar_t* wstring);
PAL_API wchar_t* PAL_ToWstring(const char* string);

PAL_API char* PAL_Format(const char* fmt, ...);