
#include "PAL_pch.h"
#include "PAL/PAL.h"

i32 PAL_Init(PAL_InitData init_data)
{
    if (init_data.custom_allocator) {
        s_Data.allocator = init_data.allocator;
    }
    else if (!init_data.custom_allocator) {
        s_Data.allocator = PAL_GetAllocator();
    }

    std::cout << "PAL Initialized" << std::endl;
    return 0;
}

void PAL_Terminate()
{
    std::cout << "PAL Terminated" << std::endl;
}

char* PAL_ToString(const wchar_t* wstring)
{
    // TODO: assert
    int len = PAL_WcharToMultibyte(wstring, 0, nullptr);
    if (len == 0) { return nullptr; }

    char* string = (char*)s_Data.allocator.alloc(len + 1);
    if (!string) { return nullptr; }
    
    PAL_WcharToMultibyte(wstring, len, string);
    return string;
}

wchar_t* PAL_ToWstring(const char* string)
{
    // TODO: assert
    int len = PAL_MultibyteToWchar(string, 0, nullptr);
    if (len == 0) { return nullptr; }

    wchar_t* wstring = (wchar_t*)s_Data.allocator.alloc(sizeof(wchar_t) * len);
    if (!wstring) { return nullptr; }

    PAL_MultibyteToWchar(string, len, wstring);
    return wstring;
}

char* PAL_FormatArgs(const char* fmt, va_list args_list)
{
    if (!fmt) { return nullptr; }
    va_list list_copy;
    __builtin_va_copy(list_copy, args_list);
    
    i32 length = vsnprintf(0, 0, fmt, list_copy);
    va_end(list_copy);
    char* result = (char*)s_Data.allocator.alloc(length + 1);
    if (!result) { return nullptr; }

    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* PAL_Format(const char* fmt, ...)
{
    if (!fmt) { return nullptr; }
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = PAL_FormatArgs(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}