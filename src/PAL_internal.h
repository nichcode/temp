
#pragma once

#include "PAL/PAL.h"

#include <stdarg.h>

enum PAL_DirectXFlags
{
    PAL_DIRECTX11 = PAL_BIT(1),
    PAL_DIRECTX10 = PAL_BIT(2)
};

struct PAL_Buffer
{
    struct BufferAPI
    {
        void (*destroy)(void* handle) = nullptr;
        void (*setData)(void* handle, void* data, u32 size) = nullptr;
        void (*bind)(void* handle, u32 start_slot, u32 type, u32 divisor, u32 stride, u64 offset) = nullptr;
    };

    BufferAPI API;
    void* handle = nullptr;
    u32 usage = 0, size = 0;
};

struct PAL_Device
{
    struct DeivceAPI
    {
        void (*destroy)(void* handle) = nullptr;
        void (*swapBuffers)(void* handle, b8 vsync) = nullptr;
        void (*clear)(void* handle) = nullptr;
        void (*setClearColor)(void* handle, PAL_Color* color) = nullptr;
    };

    DeivceAPI API;
    void* handle = nullptr;
    u32 type = 0;
};

struct PAL_Data
{
    PAL_Allocator allocator;
    u32 directx_flags = 0;

    void* dx11 = nullptr;
    void* dx10 = nullptr;
};

static PAL_Data s_Data;

PAL_Allocator PAL_GetAllocator();

i32 PAL_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 PAL_WcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

char* PAL_FormatArgs(const char* fmt, va_list args_list);
void PAL_WriteConsole(PAL_LogLevel level, const char* msg);

void PAL_InitInput();
u32 PAL_CheckDirectX();

void PAL_BindBuffer(PAL_Buffer* buffer, u32 start_slot, u32 type, u32 divisor, u32 stride, u32 offset);

#ifdef PAL_CONFIG_DEBUG
#define PAL_CHECK(expr, msg, ret)  if (expr) {} else { PAL_SetError(msg); PAL_BREAK; return ret; }
#else
#define PAL_CHECK(expr, msg, ret)  if (!expr) { PAL_SetError(msg); return ret; }
#endif // PAL_CONFIG_DEBUG