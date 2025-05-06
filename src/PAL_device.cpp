
#include "PAL_pch.h"
#include "PAL/PAL_device.h"

#include "dx11/PAL_dx11device.h"

#define CHECK_DEVICE(device, ret) PAL_CHECK(device, "device is null", ret)

struct PAL_Device
{
    struct DeivceAPI
    {
        void (*destroy)(void* handle) = nullptr;
        void (*swapBuffers)(void* handle, b8 vsync) = nullptr;
    };

    void* handle = nullptr;
    u32 type = 0;
    DeivceAPI API;
};

PAL_Device* PAL_CreateDevice(PAL_DeviceDesc* desc)
{
    PAL_Device* device = (PAL_Device*)s_Data.allocator.alloc(sizeof(PAL_Device));
    PAL_CHECK(device, "Failed to create device", nullptr);
    device->type = desc->device_type;

    switch (device->type) {
        case PAL_DEVICE_DX11: {
            device->handle = PAL_CreateDx11Device(desc);
            device->API.destroy = PAL_DestroyDx11Device;
            device->API.swapBuffers = PAL_Dx11SwapBuffers;
            break;
        }
        PAL_SetError("invalid device type");
    }
    
    return device;
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

u32 PAL_GetDeviceType(PAL_Device* device)
{
    CHECK_DEVICE(device, 0)
    return device->type;
}