
#include "PAL/PAL.h"

#define USE_GL 0

const char* g_window_name = nullptr;
u32 g_device_type = 0;

int main(int argc, char** argv)
{
#if USE_GL
    g_window_name = "gl window";
    g_device_type = PAL_DEVICE_GL;
#else
    g_window_name = "dx11 window";
    g_device_type = PAL_DEVICE_DX11;
#endif // USE_GL

    PAL_InitData init_data;
    init_data.custom_allocator = false;
    PAL_Init(init_data);

    u32 flags = PAL_APP_WINDOW | PAL_WINDOW_CENTER;
    PAL_Window* window = PAL_CreateWindow(g_window_name, 640, 480, flags);

    PAL_DeviceDesc device_desc;
    device_desc.window = window;
    device_desc.device_type = g_device_type;
    PAL_Device* device = PAL_CreateDevice(&device_desc);

    PAL_Color color = { .2f, .2f, .2f, 1.0f };
    PAL_SetClearColor(device, &color);

    f32 vertices[] = {
        -0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f,
    };

    PAL_BufferAttrib position_attrib;
    position_attrib.type = PAL_DATATYPE_FLOAT2;
    PAL_BufferAttribLayout layout;
    layout.attribs[0] = position_attrib;
    layout.count = 1;
    PAL_ProcessBufferLayout(&layout);

    PAL_BufferDesc buffer_desc;
    buffer_desc.usage = PAL_DYNAMIC;
    buffer_desc.type = PAL_VERTEX_BUFFER;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.data = vertices;
    buffer_desc.layout = layout;
    PAL_Buffer* vertex_buffer = PAL_CreateBuffer(device, &buffer_desc);

    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();

        PAL_Clear(device);

        PAL_SwapBuffers(device, true);
    }

    PAL_DestroyBuffer(vertex_buffer);

    PAL_DestroyDevice(device);
    PAL_DestroyWindow(window);
    PAL_Terminate();
    return 0;
}