
#include "PAL_pch.h"
#include "PAL/PAL.h"

static std::string s_Error;

void PAL_SetError(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* string = PAL_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);

    char* out_string = PAL_Format("%s\n", string);
    s_Error = out_string;

    s_Data.allocator.free(string);
    s_Data.allocator.free(out_string);

#if defined(PAL_CONFIG_DEBUG) || defined(PAL_ENABLE_ASSERT)
    PAL_WriteConsole(PAL_LOG_LEVEL_ERROR, s_Error.c_str());
    PAL_BREAK;
#endif // PAL_CONFIG_DEBUG || PAL_ENABLE_ASSERT
}

const char* PAL_GetError()
{
    return s_Error.c_str();
}

void PAL_ClearError()
{
    s_Error.clear();
}