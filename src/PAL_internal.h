
#pragma once

#include "PAL/PAL.h"

#include <stdarg.h>

struct PAL_Data
{
    PAL_Allocator allocator;
};

static PAL_Data s_Data;

PAL_Allocator PAL_GetAllocator();

i32 PAL_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 PAL_WcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

char* PAL_FormatArgs(const char* fmt, va_list args_list);
void PAL_WriteConsole(PAL_LogLevel level, const char* msg);

void PAL_InitInput();

#ifdef PAL_CONFIG_DEBUG
#define PAL_CHECK(expr, msg, ret)  if (expr) {} else { PAL_SetError(msg); PAL_BREAK; return ret; }
#else
#define PAL_CHECK(expr, msg, ret)  if (!expr) { PAL_SetError(msg); return ret; }
#endif // PAL_CONFIG_DEBUG