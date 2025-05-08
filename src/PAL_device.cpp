
#include "PAL_pch.h"
#include "PAL/PAL_device.h"

#ifdef PAL_PLATFORM_WINDOWS
#include "dx11/PAL_dx11device.h"
#endif // PAL_PLATFORM_WINDOWS

#include "opengl/PAL_gldevice.h"

#define CHECK_DEVICE(device, ret) PAL_CHECK(device, "device is null", ret)

PAL_Device* PAL_CreateDevice(PAL_DeviceDesc* desc)
{
    PAL_CHECK(desc, "device descriptor is null", nullptr);
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
            device->API.flush = PAL_Dx11Flush;

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
            device->API.flush = PAL_GLFlush;

            return device;
            break;
        }
    }
    PAL_CHECK(false, "Failed to create device. Invalid device type", nullptr);
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

void PAL_Flush(PAL_Device* device, PAL_PipeLine* pipe_line)
{
    CHECK_DEVICE(device,)
    PAL_CHECK(pipe_line, "pipeline is null",)

    PAL_CHECK(pipe_line->slots_count, "invalid vertex buffer slots",)
    PAL_CHECK(pipe_line->index_buffer, "pipeline index buffer is null",)
    PAL_CHECK(pipe_line->draw_mode > 0, "invalid draw mode",)
    PAL_CHECK(pipe_line->index_count > 0, "invalid index count",)
    PAL_CHECK(pipe_line->primitive_type > 0, "invalid primitive type",)

    if (pipe_line->draw_mode == (PAL_ARRAYS_INSTANCED || PAL_ELEMENTS_INSTANCED)) {
        PAL_CHECK(pipe_line->instance_count > 0, "invalid instance count",)
    }

    // bind vertex buffers into their slots
    for (u32 i = 0; i < pipe_line->slots_count; i++) {
        PAL_BindSlot* slot = &pipe_line->bind_slots[i];
        PAL_BindBuffer(
            slot->vertex_buffer,
            slot->slot,
            slot->type,
            slot->divisor,
            slot->stride,
            slot->offset
        );
    }

    // bind index buffer
    PAL_BindBuffer(pipe_line->index_buffer, 0, 0, 0, 0, 0);

    // bind shader and textures

    // flush
    device->API.flush(
        device->handle, 
        pipe_line->primitive_type, 
        pipe_line->draw_mode, 
        pipe_line->index_count, 
        pipe_line->instance_count
    );
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