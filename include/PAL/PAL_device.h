
#pragma once

#include "PAL_color.h"

struct PAL_Window;
struct PAL_Device;
struct PAL_Buffer;

enum PAL_DeviceType
{
    PAL_DEVICE_DX11 = 1,
    PAL_DEVICE_GL
};

enum PAL_Primitives
{
    PAL_TRIANGLES = 1
};

enum PAL_DrawMode
{
    PAL_ARRAYS = 1,
    PAL_ARRAYS_INSTANCED,
    PAL_ELEMENTS,
    PAL_ELEMENTS_INSTANCED,
};

struct PAL_BindSlot
{
    PAL_Buffer* vertex_buffer = nullptr;
    u32 slot = 0;
    u32 type = 0;
    u32 divisor = 0;
    u32 stride = 0;
    u32 offset = 0;
};

struct PAL_PipeLine
{
    PAL_BindSlot bind_slots[PAL_MAX_SLOTS]{};
    PAL_Buffer* index_buffer = nullptr;
    u32 primitive_type = 0;
    u32 index_count = 0;
    u32 draw_mode = 0;
    u32 instance_count = 0;
    u32 slots_count = 0;
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
PAL_API void PAL_Flush(PAL_Device* device, PAL_PipeLine* pipe_line);

PAL_API void PAL_SetClearColor(PAL_Device* device, PAL_Color* color);

PAL_API u32 PAL_GetDeviceType(PAL_Device* device);