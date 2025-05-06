
#include "PAL_pch.h"
#include "PAL/PAL_device.h"

#ifdef PAL_PLATFORM_WINDOWS
#include "dx11/PAL_dx11device.h"
#endif // PAL_PLATFORM_WINDOWS

#include "opengl/PAL_gldevice.h"

#define CHECK_DEVICE(device, ret) PAL_CHECK(device, "device is null", ret)

struct PAL_Device
{
    struct DeivceAPI
    {
        void (*destroy)(void* handle) = nullptr;
        void (*swapBuffers)(void* handle, b8 vsync) = nullptr;
        void (*clear)(void* handle) = nullptr;
        void (*setClearColor)(void* handle, PAL_Color* color) = nullptr;
    };

    DeivceAPI API;
    void* handle = nullptr;
    u32 type = 0;
};

PAL_Device* PAL_CreateDevice(PAL_DeviceDesc* desc)
{
    PAL_CHECK(desc->window, "window is null", nullptr);

    PAL_Device* device = (PAL_Device*)s_Data.allocator.alloc(sizeof(PAL_Device));
    PAL_CHECK(device, "Failed to create device", nullptr);
    device->type = desc->device_type;

    switch (device->type) {
#ifdef PAL_PLATFORM_WINDOWS
        case PAL_DEVICE_DX11: {
            device->handle = PAL_CreateDx11Device(desc);
            device->API.destroy = PAL_DestroyDx11Device;
            device->API.swapBuffers = PAL_Dx11SwapBuffers;
            device->API.clear = PAL_Dx11Clear;
            device->API.setClearColor = PAL_Dx11SetClearColor;

            return device;
            break;
        }
#endif // PAL_PLATFORM_WINDOWS

        case PAL_DEVICE_GL: {
            device->handle = PAL_CreateGLDevice(desc);
            device->API.destroy = PAL_DestroyGLDevice;
            device->API.swapBuffers = PAL_GLSwapBuffers;
            device->API.clear = PAL_GLClear;
            device->API.setClearColor = PAL_GLSetClearColor;

            return device;
            break;
        }
    }
    PAL_SetError("invalid device type");
    return nullptr;
}

void PAL_DestroyDevice(PAL_Device* device)
{
    CHECK_DEVICE(device,)
    device->API.destroy(device->handle);
    s_Data.allocator.set(&device->API, 0, sizeof(PAL_Device::API));
    s_Data.allocator.free(device);
}

void PAL_SwapBuffers(PAL_Device* device, b8 vsync)
{
    CHECK_DEVICE(device,)
    device->API.swapBuffers(device->handle, vsync);
}

void PAL_Clear(PAL_Device* device)
{
    CHECK_DEVICE(device,)
    device->API.clear(device->handle);
}

void PAL_SetClearColor(PAL_Device* device, PAL_Color* color)
{
    CHECK_DEVICE(device,)
    device->API.setClearColor(device->handle, color);
}

u32 PAL_GetDeviceType(PAL_Device* device)
{
    CHECK_DEVICE(device, 0)
    return device->type;
}