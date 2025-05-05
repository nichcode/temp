
#include "PAL_pch.h"
#include "PAL_wgl_context.h"
#include "opengl/PAL_glfuncs.h"

void* PAL_LoadGdiProcs(HMODULE gdi32, const char* func_name)
{
    PROC proc = GetProcAddress(gdi32, func_name);
    if (!proc) { PAL_SetError("failed to load gdi32 function %s", func_name); }
    return (void*)proc;
}

void* PAL_LoadWGLProcs(HMODULE opengl32, const char* func_name)
{
PROC proc = s_wglGetProcAddress(func_name);
if (!proc) {
    proc = GetProcAddress(opengl32, func_name);
    if (!proc) { PAL_SetError("failed to load wgl function %s", func_name); }
}
return (void*)proc;
}

void PAL_WGLCreateDummyContext()
{
    // load gdi32.dll procs
    HMODULE gdi32 = LoadLibraryA("gdi32.dll");
    PAL_CHECK(gdi32, "failed to load gdi32.dll",)

    HMODULE opengl32 = LoadLibraryA("opengl32.dll");
    PAL_CHECK(opengl32, "failed to load opengl32.dll",)

    s_ChoosePixelFormat = (ChoosePixelFormatFun)PAL_LoadGdiProcs(gdi32, "ChoosePixelFormat");
    s_SetPixelFormat = (SetPixelFormatFun)PAL_LoadGdiProcs(gdi32, "SetPixelFormat");
    s_DescribePixelFormat = (DescribePixelFormatFun)PAL_LoadGdiProcs(gdi32, "DescribePixelFormat");
    s_SwapBuffers = (SwapBuffersFun)PAL_LoadGdiProcs(gdi32, "SwapBuffers");

    // load wgl procs
    s_wglGetProcAddress = (PFNWGLGETPROCADDRESSPROC)GetProcAddress(opengl32, "wglGetProcAddress");
    PAL_CHECK(s_wglGetProcAddress, "failed to load wglGetProcAddress from opengl32",)

    s_wglCreateContext = (PFNWGLCREATECONTEXTPROC)PAL_LoadWGLProcs(opengl32, "wglCreateContext");
    s_wglDeleteContext = (PFNWGLDELETECONTEXTPROC)PAL_LoadWGLProcs(opengl32, "wglDeleteContext");
    s_wglMakeCurrent = (PFNWGLMAKECURRENTPROC)PAL_LoadWGLProcs(opengl32, "wglMakeCurrent");

    WNDCLASSEXW window_class = {};
    window_class.style = CS_OWNDC;
    window_class.lpfnWndProc = DefWindowProcW;
    window_class.lpszClassName = L"PALDummyWindow";
    window_class.cbSize = sizeof(WNDCLASSEXW);

    auto class_id = RegisterClassExW(&window_class);
    PAL_CHECK(class_id, "failed to register dummy window class",)

    HWND dummy_window = CreateWindowExW(
        0,
        MAKEINTATOM(class_id),
        L"PrimeDummyWindow",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        window_class.hInstance,
        0);

    PAL_CHECK(dummy_window, "Win32 dummy window creation failed",);
    HDC dummy_dc = GetDC(dummy_window);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixel_format = s_ChoosePixelFormat(dummy_dc, &pfd);
    s_SetPixelFormat(dummy_dc, pixel_format, &pfd);

    HGLRC dummy_context = s_wglCreateContext(dummy_dc);
    bool res = s_wglMakeCurrent(dummy_dc, dummy_context);

    PAL_LoadGL();

    s_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)PAL_LoadWGLProcs(opengl32, "wglChoosePixelFormatARB");
    s_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)PAL_LoadWGLProcs(opengl32, "wglCreateContextAttribsARB");
    s_wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)PAL_LoadWGLProcs(opengl32, "wglSwapIntervalEXT");

    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);

    FreeLibrary(gdi32);
    FreeLibrary(opengl32);
}

HGLRC PAL_WGLCreateContext(HWND window, i32 major, i32 minor)
{
    auto hdc = GetDC(window);

    int pixel_format_attrib[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_SWAP_METHOD_ARB,  WGL_SWAP_COPY_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    int pixel_format = 0;
    UINT num_format = 0;
    s_wglChoosePixelFormatARB(hdc, pixel_format_attrib, nullptr, 1, &pixel_format, &num_format);
    PAL_CHECK(num_format, "failed to find pixel format", nullptr);

    PIXELFORMATDESCRIPTOR pixel_format_desc = {};
    s_DescribePixelFormat(hdc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pixel_format_desc);
    s_SetPixelFormat(hdc, pixel_format, &pixel_format_desc);

    b8 valid = major < glVersion.major || (major == glVersion.major && minor <= glVersion.minor);
    if (!valid) { 
        PAL_SetError("your device doesent support opengl version %i.%i", major, minor);
        return nullptr;
    }

    int opengl_attrib[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
        0
    };

    HGLRC context = s_wglCreateContextAttribsARB(hdc, 0, opengl_attrib);
    PAL_CHECK(context, "wgl context creation failed", nullptr)
    ReleaseDC(window, hdc);
    return context;
}