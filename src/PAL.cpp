
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
    int len = PAL_Wchar0Multibyte(wstring, 0, nullptr);
    if (len == 0) { return nullptr; }

    char* string = (char*)s_Data.allocator.alloc(len + 1);
    if (!string) { return nullptr; }
    
    PAL_Wchar0Multibyte(wstring, len, string);
    return string;
}

wchar_t* PAL_ToWString(const char* string)
{
    // TODO: assert
    int len = PAL_MultibyteToWchar(string, 0, nullptr);
    if (len == 0) { return nullptr; }

    wchar_t* wstring = (wchar_t*)s_Data.allocator.alloc(sizeof(wchar_t) * len);
    if (!wstring) { return nullptr; }

    PAL_MultibyteToWchar(string, len, wstring);
    return wstring;
}