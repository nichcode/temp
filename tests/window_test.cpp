
#include "PAL/PAL.h"

void onWindowClose(PAL_Window* window)
{
	const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo("%s is closed", title);
}

void onWindowPos(PAL_Window* window, i32 x, i32 y)
{
    const char* title = PAL_GetWindowTitle(window);
	PAL_LogInfo("%s - windowPos(%i, %i))", title, x, y);
}

void onWindowSize(PAL_Window* window, u32 width, u32 height)
{
    const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo("size(%i, %i)", width, height);
}

void onKey(PAL_Window* window, u32 key, i32 scancode, u32 action)
{
    const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo(
        "%s - %s, %s", title, 
        PAL_GetKeyName(key), 
        PAL_GetActionName(action)
    );
}

void onMouseButton(PAL_Window* window, u32 button, u32 action)
{
    const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo(
        "%s - %s, %s", title, 
        PAL_GetMouseButtonName(button), 
        PAL_GetActionName(action)
    );
}

void onMousePos(PAL_Window* window, i32 x, i32 y)
{
    const char* title = PAL_GetWindowTitle(window);
	PAL_LogInfo("%s - mousePos(%i, %i))", title, x, y);
}

void onScroll(PAL_Window* window, f32 x_offset, f32 y_offset)
{
    const char* title = PAL_GetWindowTitle(window);
	PAL_LogInfo("%s - mouseScroll(%i, %i))", title, x_offset, y_offset);
}

int main(int argc, char** argv)
{
    PAL_InitData init_data;
    init_data.custom_allocator = false;
    PAL_Init(init_data);

    u32 flags = PAL_APP_WINDOW | PAL_WINDOW_CENTER;
    PAL_Window* window = PAL_CreateWindow("window", 640, 480, flags);

    PAL_SetWindowCloseCallback(window, onWindowClose);
    PAL_SetWindowPosCallback(window, onWindowPos);
    PAL_SetWindowSizeCallback(window, onWindowSize);

    PAL_SetKeyCallback(window, onKey);

    PAL_SetMouseButtonCallback(window, onMouseButton);
    PAL_SetMousePosCallback(window, onMousePos);
    PAL_SetScrollCallback(window, onScroll);

    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();
    }
    
    PAL_DestroyWindow(window);
    PAL_Terminate();
    return 0;
}