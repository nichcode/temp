
#include "PAL/PAL.h"

struct PAL_Data
{
    PAL_Allocator allocator;
};

static PAL_Data s_Data;

PAL_Allocator PAL_GetAllocator();

i32 PAL_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 PAL_Wchar0Multibyte(const wchar_t* wstr, u32 wstr_len, char* str);