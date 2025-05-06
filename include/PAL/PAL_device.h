
#pragma once

#include "PAL_color.h"

struct PAL_Window;
struct PAL_Device;

enum PAL_DeviceType
{
    PAL_DEVICE_DX11 = 1,
    PAL_DEVICE_GL
};

struct PAL_DeviceDesc
{
    PAL_Window* window = nullptr;
    u32 device_type = 0;
    u32 swap_chain_width = 0;
    u32 swap_chain_height = 0;

    i32 version_major = 0;
    i32 version_minor = 0;

    b8 use_window_size = true;
    b8 use_gl_version = true;
};

PAL_API PAL_Device* PAL_CreateDevice(PAL_DeviceDesc* desc);
PAL_API void PAL_DestroyDevice(PAL_Device* device);

PAL_API void PAL_SwapBuffers(PAL_Device* device, b8 vsync);
PAL_API void PAL_Clear(PAL_Device* device);

PAL_API void PAL_SetClearColor(PAL_Device* device, PAL_Color* color);

PAL_API u32 PAL_GetDeviceType(PAL_Device* device);