
#pragma once

#include "PAL_glfuncs.h"

struct PAL_Window;

struct PAL_GLDevice
{
    PAL_Window* window;
    void* context;
    void* deviceContext;
    u32 vao = 0;
};

struct PAL_GLBuffer
{
    u32 id = 0;
    u32 type = 0;
    u32 usage = 0;
    u32 size = 0;
    u32 binding = 0;
    void* data = nullptr;

    void* re_data = nullptr;
    u32 re_size = 0;
    b8 data_sent = false;
};