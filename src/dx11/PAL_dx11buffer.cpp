
#include "PAL_pch.h"
#include "PAL_dx11.h"

inline D3D11_USAGE PAL_GetDx11BufferUsage(u32 buffer_type)
{
    switch (buffer_type) {
        case PAL_STATIC:
            return D3D11_USAGE_IMMUTABLE;

        case PAL_DYNAMIC:
            return D3D11_USAGE_DYNAMIC;
    };

    PAL_CHECK(false, "invalid buffer type", D3D11_USAGE_DEFAULT);
}

inline u32 PAL_GetDx11BufferAccess(u32 buffer_usage)
{
    switch (buffer_usage) {
        case PAL_STATIC:
            return 0;

        case PAL_DYNAMIC:
            return D3D11_CPU_ACCESS_WRITE;
    };

    PAL_CHECK(false, "invalid buffer type", 0);
}

inline u32 PAL_GetDx11BufferType(u32 buffer_type)
{
    switch (buffer_type) {
        case PAL_VERTEX_BUFFER:
            return D3D11_BIND_VERTEX_BUFFER;

        case PAL_INDEX_BUFFER:
            return D3D11_BIND_INDEX_BUFFER;

        case PAL_STORAGE_BUFFER:
            return D3D11_BIND_SHADER_RESOURCE;

        case PAL_UNIFORM_BUFFER:
            return D3D11_BIND_CONSTANT_BUFFER;
    };

    PAL_CHECK(false, "invalid buffer type", 0);
}

void* PAL_CreateDx11Buffer(void* dx11_device, PAL_BufferDesc* desc)
{
    if (s_Data.directx_flags & PAL_DIRECTX11) {

        PAL_Dx11Buffer* buffer = (PAL_Dx11Buffer*)s_Data.allocator.alloc(sizeof(PAL_Dx11Buffer)); 
        PAL_CHECK(buffer, "Failed to create dx11 buffer", nullptr);

        PAL_Dx11Device* device = (PAL_Dx11Device*)dx11_device;
        buffer->device = device;
        buffer->type = desc->type;

        D3D11_BUFFER_DESC buffer_desc = {};
        buffer_desc.Usage = PAL_GetDx11BufferUsage(desc->usage);
        buffer_desc.ByteWidth = desc->size;
        buffer_desc.BindFlags = PAL_GetDx11BufferType(desc->type);
        buffer_desc.CPUAccessFlags = PAL_GetDx11BufferAccess(desc->usage);
        buffer_desc.MiscFlags = 0;
        buffer_desc.StructureByteStride = 0;

        if (desc->data) {
            D3D11_SUBRESOURCE_DATA subresource_data = {};
            subresource_data.pSysMem = desc->data;
            device->handle->CreateBuffer(&buffer_desc, &subresource_data, &buffer->handle);
        }
        else {
            device->handle->CreateBuffer(&buffer_desc, nullptr, &buffer->handle);
        }

        PAL_CHECK(buffer->handle, "Failed to create dx11 buffer", nullptr)
        return buffer;
    }
    return nullptr;
}

void PAL_DestroyDx11Buffer(void* dx11_buffer)
{
    PAL_Dx11Buffer* buffer = (PAL_Dx11Buffer*)dx11_buffer;
    buffer->handle->Release();
}

void PAL_SetDx11BufferData(void* dx11_buffer, void* data, u32 size)
{
    PAL_Dx11Buffer* buffer = (PAL_Dx11Buffer*)dx11_buffer;
    ID3D11DeviceContext* context = buffer->device->context;

    D3D11_MAPPED_SUBRESOURCE mapped_resource;
    HRESULT hr = context->Map(
        buffer->handle,
        0,
        D3D11_MAP_WRITE_DISCARD,
        0,
        &mapped_resource
    );

    PAL_CHECK(SUCCEEDED(hr), "Couldn't set data to the dx11 buffer",)
    memcpy(mapped_resource.pData, data, size);
    context->Unmap(buffer->handle, 0);
}

void PAL_BindDx11Buffer(void* dx11_buffer, u32 slot, u32 stride, u32 offset)
{
    PAL_Dx11Buffer* buffer = (PAL_Dx11Buffer*)dx11_buffer;
    ID3D11DeviceContext* context = buffer->device->context;
    PAL_CHECK(slot < PAL_MAX_SLOTS, "slot is out of bounds", )

    if (buffer->type == PAL_VERTEX_BUFFER) {
        context->IASetVertexBuffers(slot, 1, &buffer->handle, &stride, &offset);
    }
    else if (buffer->type == PAL_INDEX_BUFFER) {
        context->IASetIndexBuffer(buffer->handle, DXGI_FORMAT_R32_UINT, offset);
    }
}