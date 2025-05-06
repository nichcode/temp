
#include "PAL/PAL.h"

const char* g_window_name = nullptr;
u32 g_device_type = 0;

int main(int argc, char** argv)
{
#if PAL_GL
    g_window_name = "gl window";
    g_device_type = PAL_DEVICE_GL;
#else
    g_window_name = "dx11 window";
    g_device_type = PAL_DEVICE_DX11;
#endif // PAL_GL

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

    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();

        PAL_Clear(device);

        PAL_SwapBuffers(device, true);
    }

    PAL_DestroyDevice(device);
    PAL_DestroyWindow(window);
    PAL_Terminate();
    return 0;
}