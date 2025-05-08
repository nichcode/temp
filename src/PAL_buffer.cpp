
#include "PAL_pch.h"

#ifdef PAL_PLATFORM_WINDOWS
#include "dx11/PAL_dx11buffer.h"
#endif // PAL_PLATFORM_WINDOWS

#include "opengl/PAL_glbuffer.h"

#define CHECK_BUFFER(buffer, ret) PAL_CHECK(buffer, "buffer is null", ret)

inline u32 PAL_GetDataTypeSize(u32 type)
{
    switch (type) {
        case PAL_DATATYPE_INT:
        case PAL_DATATYPE_FLOAT: {
            return 4;
        }

        case PAL_DATATYPE_INT2:
        case PAL_DATATYPE_FLOAT2: {
            return 8;
        }

        case PAL_DATATYPE_INT3:
        case PAL_DATATYPE_FLOAT3: {
            return 12;
        }

        case PAL_DATATYPE_INT4:
        case PAL_DATATYPE_FLOAT4: {
            return 16;
        }
    }

    return 0;
}

PAL_Buffer* PAL_CreateBuffer(PAL_Device* device, PAL_BufferDesc* desc)
{
    PAL_CHECK(device, "device is null", nullptr);
    PAL_CHECK(desc, "buffer descriptor is null", nullptr);

    PAL_Buffer* buffer = (PAL_Buffer*)s_Data.allocator.alloc(sizeof(PAL_Buffer));
    PAL_CHECK(buffer, "Failed to create buffer", nullptr);
    buffer->size = desc->size;
    buffer->usage = desc->usage;

    switch (device->type) {
#ifdef PAL_PLATFORM_WINDOWS
        case PAL_DEVICE_DX11: {
            buffer->handle = PAL_CreateDx11Buffer(device->handle, desc);
            buffer->API.destroy = PAL_DestroyDx11Buffer;
            buffer->API.setData = PAL_SetDx11BufferData;
            buffer->API.bind = PAL_BindDx11Buffer;

            return buffer;
            break;
        }
#endif // PAL_PLATFORM_WINDOWS

        case PAL_DEVICE_GL: {
            buffer->handle = PAL_CreateGLBuffer(device->handle, desc);
            buffer->API.destroy = PAL_DestroyGLBuffer;
            buffer->API.setData = PAL_SetGLBufferData;
            buffer->API.bind = PAL_BindGLBuffer;

            return buffer;
            break;
        }
    }
    PAL_CHECK(false, "Failed to create buffer. Invalid device type", nullptr);
    return nullptr;
}

void PAL_DestroyBuffer(PAL_Buffer* buffer)
{
    CHECK_BUFFER(buffer,)
    buffer->API.destroy(buffer->handle);
    s_Data.allocator.free(buffer);
}

void PAL_SetBufferData(PAL_Buffer* buffer, void* data, u32 size)
{
    CHECK_BUFFER(buffer,)
    PAL_CHECK(size <= buffer->size, "size is greater than buffer size",)
    if (buffer->usage) {
        buffer->API.setData(buffer->handle, data, size);
    }
    else { PAL_WARN("can not set data to a static vertex buffer"); }
}

void PAL_BindBuffer(PAL_Buffer* buffer, u32 start_slot, u32 type, u32 divisor, u32 stride, u64 offset)
{
    CHECK_BUFFER(buffer,)
    buffer->API.bind(buffer->handle, start_slot, type, divisor, stride, offset);
}

PAL_BufferLayoutInfo PAL_GetBufferLayoutInfo(u32* layout, u32 count)
{
    PAL_BufferLayoutInfo info;
    info.stride = 0;
    info.count = count;
    for (u32 i = 0; i < count; i++) {
        info.offsets[i] = info.stride;
        info.stride += PAL_GetDataTypeSize(layout[i]);
    }

    return info;
}