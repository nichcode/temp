
#pragma once

#include "PAL_defines.h"

PAL_API void PAL_Assert(b8 expr, const char* file, u32 line, const char* msg, ...);

#ifdef PAL_CONFIG_DEBUG
#ifndef PAL_ENABLE_ASSERT
#define PAL_ENABLE_ASSERT
#endif // PAL_ENABLE_ASSERT
#endif // PAL_CONFIG_DEBUG

#ifdef PAL_ENABLE_ASSERT
#define PAL_ASSERT(expr, ...)  PAL_Assert(expr, PAL_FILE, PAL_LINE, __VA_ARGS__)
#else
#define PAL_ASSERT(expr, ...)
#endif // PAL_ENABLE_ASSERT