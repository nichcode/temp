
#pragma once

#include "PAL_defines.h"

enum PAL_LogLevel
{
    PAL_LOG_LEVEL_TRACE,
    PAL_LOG_LEVEL_INFO,
    PAL_LOG_LEVEL_WARN,
    PAL_LOG_LEVEL_ERROR
};

PAL_API void PAL_Log(PAL_LogLevel level, const char* msg, ...);
PAL_API void PAL_LogTrace(const char* msg, ...);
PAL_API void PAL_LogInfo(const char* msg, ...);

PAL_API void PAL_LogWarn(const char* msg, ...);
PAL_API void PAL_LogError(const char* msg, ...);
