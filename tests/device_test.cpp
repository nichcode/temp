
#include "PAL/PAL.h"

#define USE_GL 1

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

    u32 indices[3] = { 0, 1, 2 };

    u32 layouts[1] = {
        PAL_DATATYPE_FLOAT2
    };

    PAL_BufferLayoutInfo layout_info = PAL_GetBufferLayoutInfo(layouts, 1);

    PAL_BufferDesc buffer_desc;
    buffer_desc.usage = PAL_STATIC;
    buffer_desc.type = PAL_VERTEX_BUFFER;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.data = vertices;
    PAL_Buffer* vertex_buffer = PAL_CreateBuffer(device, &buffer_desc);

    buffer_desc.usage = PAL_STATIC;
    buffer_desc.type = PAL_INDEX_BUFFER;
    buffer_desc.size = sizeof(u32) * 3;
    buffer_desc.data = indices;
    PAL_Buffer* index_buffer = PAL_CreateBuffer(device, &buffer_desc);

    PAL_BindSlot slot_0;
    slot_0.offset = layout_info.offsets[0];
    slot_0.slot = 0;
    slot_0.stride = layout_info.stride;
    slot_0.type = PAL_DATATYPE_FLOAT2;
    slot_0.vertex_buffer = vertex_buffer;

    PAL_PipeLine pipe_line;
    pipe_line.bind_slots[0] = slot_0;
    pipe_line.draw_mode = PAL_ELEMENTS;
    pipe_line.index_buffer = index_buffer;
    pipe_line.primitive_type = PAL_TRIANGLES;
    pipe_line.slots_count = 1;
    pipe_line.index_count = 3;

    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();

        PAL_Clear(device);
        PAL_Flush(device, &pipe_line);
        PAL_SwapBuffers(device, true);
    }

    PAL_DestroyBuffer(vertex_buffer);
    PAL_DestroyBuffer(index_buffer);

    PAL_DestroyDevice(device);
    PAL_DestroyWindow(window);
    PAL_Terminate();
    return 0;
}