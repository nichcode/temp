
#include "PAL_pch.h"
#include "PAL/PAL.h"
#include "opengl/PAL_glfuncs.h"

i32 PAL_Init(PAL_InitData init_data)
{
    if (init_data.custom_allocator) {
        s_Data.allocator = init_data.allocator;
    }
    else if (!init_data.custom_allocator) {
        s_Data.allocator = PAL_GetAllocator();
    }

#ifdef PAL_PLATFORM_WINDOWS
    PAL_Win32Init();
#endif // PAL_PLATFORM_WINDOWS

    PAL_InitInput();

    if (init_data.glversion_major == 0) {
        s_Data.glversion_major = glVersion.major;
    }
    if (init_data.glversion_minor == 0) {
        s_Data.glversion_minor = glVersion.minor;
    }

    PAL_INFO("PAL Initialized");
    return 0;
}

void PAL_Terminate()
{
#ifdef PAL_PLATFORM_WINDOWS
    PAL_Win32Terminate();
#endif // PAL_PLATFORM_WINDOWS
    PAL_INFO("PAL Terminated");
}

char* PAL_ToString(const wchar_t* wstring)
{
    PAL_CHECK(wstring, "wstring is null", nullptr);
    int len = PAL_WcharToMultibyte(wstring, 0, nullptr);
    PAL_CHECK(len, "wstring is empty", nullptr);

    char* string = (char*)s_Data.allocator.alloc(len + 1);
    PAL_CHECK(string, "failed to allocate string buffer", nullptr);
    
    PAL_WcharToMultibyte(wstring, len, string);
    return string;
}

wchar_t* PAL_ToWstring(const char* string)
{
    PAL_CHECK(string, "string is null", nullptr);
    int len = PAL_MultibyteToWchar(string, 0, nullptr);
    PAL_CHECK(len, "string is empty", nullptr);

    wchar_t* wstring = (wchar_t*)s_Data.allocator.alloc(sizeof(wchar_t) * len);
    PAL_CHECK(string, "failed to allocate wstring buffer", nullptr);

    PAL_MultibyteToWchar(string, len, wstring);
    return wstring;
}

char* PAL_FormatArgs(const char* fmt, va_list args_list)
{
    PAL_CHECK(fmt, "fmt is null", nullptr);

    va_list list_copy;
    __builtin_va_copy(list_copy, args_list);
    
    i32 length = vsnprintf(0, 0, fmt, list_copy);
    va_end(list_copy);
    char* result = (char*)s_Data.allocator.alloc(length + 1);
    PAL_CHECK(result, "failed to allocate string buffer", nullptr);

    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* PAL_Format(const char* fmt, ...)
{
    PAL_CHECK(fmt, "fmt is null", nullptr);
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = PAL_FormatArgs(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}