
#include "PAL/PAL.h"

int main(int argc, char** argv)
{
    PAL_InitData init_data;
    init_data.custom_allocator = false;
    PAL_Init(init_data);

    u32 flags = PAL_APP_WINDOW | PAL_WINDOW_CENTER;
    PAL_Window* window = PAL_CreateWindow("window", 640, 480, flags);

    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();
    }
    
    PAL_DestroyWindow(window);
    PAL_Terminate();
    return 0;
}