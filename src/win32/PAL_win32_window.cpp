
#include "PAL_pch.h"

#define CHECK_WINDOW(window, ret) PAL_CHECK(window, "window is null", ret)

struct PAL_Window
{
    HWND handle;
    const char* title;
    u32 width, height, flags;
    i32 x, y;
    b8 shouldClose, focused, hidden;
    b8 maximized, minimized;
};

void PAL_CenterWindow(PAL_Window* window)
{
    MONITORINFO monitor_info;
    monitor_info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromWindow(window->handle, MONITOR_DEFAULTTONEAREST), &monitor_info);
    u32 max_hwidth = monitor_info.rcMonitor.right;
    u32 max_hheight = monitor_info.rcMonitor.bottom;

    i32 x = (max_hwidth - window->width) / 2;
    i32 y = (max_hheight - window->height) / 2;
    window->x = x;
    window->y = y;
    i32 show_flags = SWP_HIDEWINDOW;
    if (window->flags & PAL_WINDOW_SHOWN) { show_flags = SWP_SHOWWINDOW; }
    SetWindowPos(window->handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | show_flags);
}

PAL_Window* PAL_CreateWindow(const char* title, u32 width, u32 height, u32 flags)
{
    u32 style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    u32 ex_style = WS_EX_APPWINDOW;

    if (flags & PAL_WINDOW_MINIMIZEBOX) {
        style |= WS_MINIMIZEBOX;
    }

    if (flags & PAL_WINDOW_RESIZABLE) {
        style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
    }

    RECT rect = { 0, 0, 0, 0 };
    rect.right = width;
    rect.bottom = height;
    AdjustWindowRectEx(&rect, style, 0, ex_style);
    wchar_t* wstr = PAL_ToWstring(title);

    PAL_Window* window = (PAL_Window*)s_Data.allocator.alloc(sizeof(PAL_Window));
    if (!window) { PAL_SetError("failed to create window"); return nullptr; }

    window->x = CW_USEDEFAULT;
    window->y = CW_USEDEFAULT;
    window->title = title;
    window->width = width;
    window->height = height;
    window->flags = flags;

    window->handle = CreateWindowExW(
        ex_style, 
        s_ClassName, 
        wstr, 
        style, 
        window->x,
        window->y, 
        rect.right - rect.left,
        rect.bottom - rect.top, 
        NULL, 
        NULL, 
        s_Instance,  
        NULL
    );

    if (!window->handle) { 
        PAL_SetError("failed to create windows window handle"); 
        s_Data.allocator.free(window);
        return nullptr;
    }

    i32 show_flag = SW_HIDE;
    if (flags & PAL_WINDOW_MAXIMIZE) { show_flag = SW_SHOWMAXIMIZED; }
    if (flags & PAL_WINDOW_CENTER) { PAL_CenterWindow(window); }

    if (flags & PAL_WINDOW_SHOWN) {
        if (show_flag == SW_HIDE) { show_flag = SW_NORMAL; }
        UpdateWindow(window->handle);
        ShowWindow(window->handle, show_flag); 
    }

    SetPropW(window->handle, s_PropName, window);
    s_Data.allocator.free(wstr);

    window->focused = true;
    window->shouldClose = false;
    return window;
}

void PAL_DestroyWindow(PAL_Window* window)
{
    CHECK_WINDOW(window, )
    DestroyWindow(window->handle);
    s_Data.allocator.free(window);
}

void PAL_PullEvents()
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

void PAL_HideWindow(PAL_Window* window)
{
    CHECK_WINDOW(window,)
    ShowWindow(window->handle, SW_HIDE);
}

void PAL_ShowWindow(PAL_Window* window)
{
    CHECK_WINDOW(window,)
    i32 show_flag = SW_NORMAL;
    window->hidden = false;
    if (window->maximized) {
        show_flag = SW_SHOWMAXIMIZED;
    }
    ShowWindow(window->handle, show_flag);
}

void PAL_MaximizeWindow(PAL_Window* window)
{
    CHECK_WINDOW(window,)
    window->minimized = false;
    window->maximized = true;
    ShowWindow(window->handle, SW_SHOWMAXIMIZED);
}

void PAL_MinimizeWindow(PAL_Window* window)
{
    CHECK_WINDOW(window,)
    window->minimized = true;
    window->maximized = false;
    ShowWindow(window->handle, SW_SHOWMINIMIZED);
}

void PAL_SetWindowTitle(PAL_Window* window, const char* title)
{
    CHECK_WINDOW(window,)
    window->title = title;
    wchar_t* wstr = PAL_ToWstring(title);
    SetWindowText(window->handle, wstr);
    s_Data.allocator.free(wstr);
}

void PAL_SetWindowPos(PAL_Window* window, i32 x, i32 y, b8 center)
{
    CHECK_WINDOW(window,)
    if (center) {
        PAL_CenterWindow(window);
    }
    else {
        RECT rect = { x, y, x, y };
        AdjustWindowRectEx(&rect, window->flags, 0, WS_EX_APPWINDOW);
        window->x = x;
        window->y = y;

        SetWindowPos(
            window->handle,
            NULL, 
            rect.left, 
            rect.top, 
            0, 
            0, 
            SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE
        );
    }
}

void PAL_SetWindowSize(PAL_Window* window, u32 width, u32 height)
{
    CHECK_WINDOW(window,)
    RECT rect = { 0, 0, 0, 0 };
    rect.right = width;
    rect.bottom = height;
    AdjustWindowRectEx(&rect, window->flags, 0, WS_EX_APPWINDOW);
    window->width = width;
    window->height = height;

    SetWindowPos(
        window->handle, 
        HWND_TOP, 
        0, 
        0, 
        rect.right - rect.left, 
        rect.bottom - rect.top,
        SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER
    );
}

const char* PAL_GetWindowTitle(PAL_Window* window)
{
    CHECK_WINDOW(window, nullptr)
    return window->title;
}

void PAL_GetWindowSize(PAL_Window* window, u32* width, u32* height)
{
    CHECK_WINDOW(window,)
    PAL_CHECK(width && height, "pointer is null",);
    *width = window->width;
    *height = window->height;
}

void PAL_GetWindowPos(PAL_Window* window, i32* x, i32* y)
{
    CHECK_WINDOW(window,)
    PAL_CHECK(x && y, "pointer is null",);
    *x = window->x;
    *y = window->y;
}

void* PAL_GetWindowHandle(PAL_Window* window)
{
    CHECK_WINDOW(window, nullptr)
    return window->handle;
}

b8 PAL_WindowShouldClose(PAL_Window* window)
{
    CHECK_WINDOW(window, false)
    return window->shouldClose;
}

b8 PAL_WindowIsHidden(PAL_Window* window)
{
    CHECK_WINDOW(window, false)
    return window->hidden;
}

b8 PAL_WindowIsMaximized(PAL_Window* window)
{
    CHECK_WINDOW(window, false)
    return window->maximized;
}

b8 PAL_WindowIsMinimized(PAL_Window* window)
{
    CHECK_WINDOW(window, false)
    return window->minimized;
}

LRESULT CALLBACK PAL_Win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    PAL_Window* window = (PAL_Window*)GetPropW(hwnd, s_PropName);
    if (!window) { return DefWindowProcW(hwnd, msg, w_param, l_param); }

    switch (msg) {
        case WM_CLOSE: {
            window->shouldClose = true;
            return 0;
            break;
        } 
    }

    return DefWindowProcW(hwnd, msg, w_param, l_param);
}