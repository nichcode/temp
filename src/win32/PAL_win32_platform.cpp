
#include "PAL_pch.h"
#include "PAL/PAL_memory.h"

PAL_API PAL_Allocator PAL_GetAllocator()
{
    PAL_Allocator allocator;
    allocator.alloc = malloc;
    allocator.free = free;
    allocator.copy = memcpy;
    allocator.set = memset;

    return allocator;
}

i32 PAL_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
{
    return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
}

i32 PAL_Wchar0Multibyte(const wchar_t* wstr, u32 wstr_len, char* str)
{
    return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
} 