
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

#ifdef PAL_CONFIG_DEBUG
#define PAL_TRACE(...)   PAL_LogTrace(__VA_ARGS__)
#define PAL_INFO(...)    PAL_LogInfo(__VA_ARGS__)
#define PAL_WARN(...)    PAL_LogWarn(__VA_ARGS__)
#define PAL_ERROR(...)   PAL_LogError(__VA_ARGS__)
#else 
#define PAL_TRACE(...)   
#define PAL_INFO(...)    
#define PAL_WARN(...)    
#define PAL_ERROR(...)   
#endif // PAL_CONFIG_DEBUG