
#include "PAL_pch.h"
#include "PAL/PAL_device.h"

#include "dx11/PAL_dx11device.h"

#define CHECK_DEVICE(device, ret) PAL_CHECK(device, "device is null", ret)

struct PAL_Device
{
    void* handle;

    struct DeivceAPI
    {
        void (*destroyDevice)(void* device_handle) = nullptr;
    };
    DeivceAPI API;
};

PAL_Device* PAL_CreateDevice(u32 device_type)
{
    PAL_Device* device = (PAL_Device*)s_Data.allocator.alloc(sizeof(PAL_Device));
    PAL_CHECK(device, "Failed to create device", nullptr);

    switch (device_type) {
        case PAL_DEVICE_DX11: {
            device->handle = PAL_CreateDx11Device();
            device->API.destroyDevice = PAL_DestroyDx11Device;
            break;
        }
        PAL_SetError("invalid device type");
    }
    
    return device;
}

void PAL_DestroyDevice(PAL_Device* device)
{
    CHECK_DEVICE(device,)
    device->API.destroyDevice(device->handle);
    s_Data.allocator.set(&device->API, 0, sizeof(PAL_Device::API));
    s_Data.allocator.free(device);
}