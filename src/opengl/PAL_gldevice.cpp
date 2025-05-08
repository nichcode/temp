
#include "PAL_pch.h"
#include "PAL_gldevice.h"
#include "PAL_gl.h"

#ifdef PAL_PLATFORM_WINDOWS
#include "win32/PAL_wgl_context.h"
#endif // PAL_PLATFORM_WINDOWS 

inline GLenum PAL_GetGLPrimitive(u32 primitive)
{
    switch (primitive) {
        case PAL_TRIANGLES: {
            return GL_TRIANGLES;
            break;
        }
    }

    return 0;
}

void* PAL_CreateGLDevice(PAL_DeviceDesc* desc)
{
    PAL_GLDevice* device = (PAL_GLDevice*)s_Data.allocator.alloc(sizeof(PAL_GLDevice));
    device->window = desc->window;

    u32 major, minor = 0;
    if (desc->use_gl_version) {
        major = glVersion.major;
        minor = glVersion.minor;
    }
    else {
        major = desc->version_major;
        minor = desc->version_minor;
    }

    PAL_CHECK(major && minor, "invalid gl version", nullptr)

#ifdef PAL_PLATFORM_WINDOWS
    HWND window = (HWND)PAL_GetWindowHandle(device->window);
    device->context = PAL_WGLCreateContext(window, major, minor);

    device->deviceContext = GetDC(window);
    s_wglMakeCurrent((HDC)device->deviceContext, (HGLRC)device->context);
#endif // PAL_PLATFORM_WINDOWS 

    if (!desc->use_window_size) {
        glViewport(0, 0, (GLsizei)desc->swap_chain_width, (GLsizei)desc->swap_chain_height);
    }

    glGenVertexArrays(1, &device->vao);
    glBindVertexArray(device->vao);
    return device;
}

void PAL_DestroyGLDevice(void* gl_device)
{
    PAL_GLDevice* device = (PAL_GLDevice*)gl_device;

#ifdef PAL_PLATFORM_WINDOWS
    HGLRC context = (HGLRC)device->context;
    HWND window = (HWND)PAL_GetWindowHandle(device->window);
    HDC dc = (HDC)device->deviceContext;

    s_wglDeleteContext(context);
    ReleaseDC(window, dc);
#endif // PAL_PLATFORM_WINDOWS 

}

void PAL_GLSwapBuffers(void* gl_device, b8 vsync)
{
    PAL_GLDevice* device = (PAL_GLDevice*)gl_device;

#ifdef PAL_PLATFORM_WINDOWS
    s_SwapBuffers((HDC)device->deviceContext);
#endif // PAL_PLATFORM_WINDOWS 
}

void PAL_GLClear(void* gl_device)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PAL_GLDevice* device = (PAL_GLDevice*)gl_device;
}

void PAL_GLFlush(void* gl_device, u32 primitive, u32 mode, u32 count, u32 instance_count)
{
    u32 gl_mode = PAL_GetGLPrimitive(primitive);
    if (mode == PAL_ARRAYS) {
        glDrawArrays(gl_mode, 0, count);
    }

    else if (mode == PAL_ELEMENTS) {
        glDrawElements(gl_mode, count, GL_UNSIGNED_INT, nullptr);
    }

    else if (mode == PAL_ARRAYS_INSTANCED) {
        glDrawArraysInstanced(gl_mode, 0, count, instance_count);
    }

    else if (mode == PAL_ELEMENTS_INSTANCED) {
        glDrawElementsInstanced(gl_mode, count, GL_UNSIGNED_INT, nullptr, instance_count);
    }
}

void PAL_GLSetClearColor(void* gl_device, PAL_Color* color)
{
    glClearColor(color->r, color->g, color->b, color->a);
}