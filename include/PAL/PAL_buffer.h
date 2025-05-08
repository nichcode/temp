
#pragma once

#include "PAL_defines.h"

struct PAL_Device;
struct PAL_Buffer;

enum PAL_DataType
{
    PAL_DATATYPE_INT = 1,
    PAL_DATATYPE_INT2,
    PAL_DATATYPE_INT3,
    PAL_DATATYPE_INT4,
    PAL_DATATYPE_FLOAT,
    PAL_DATATYPE_FLOAT2,
    PAL_DATATYPE_FLOAT3,
    PAL_DATATYPE_FLOAT4
};

enum PAL_BufferType
{
    PAL_VERTEX_BUFFER = 1, 
    PAL_INDEX_BUFFER,
    PAL_STORAGE_BUFFER,
    PAL_UNIFORM_BUFFER
};

enum PAL_BufferUsage
{
    PAL_STATIC = 1,
    PAL_DYNAMIC
};

struct PAL_BufferLayoutInfo
{
    u32 offsets[PAL_MAX_ATTRIB]{};
    u32 count, stride = 0;
};

struct PAL_BufferDesc
{
    u32 type = 0;
    u32 usage = 0;
    u32 size = 0;
    u32 binding = 0;
    void* data = nullptr;
};

PAL_API PAL_Buffer* PAL_CreateBuffer(PAL_Device* device, PAL_BufferDesc* desc);
PAL_API void PAL_DestroyBuffer(PAL_Buffer* buffer);
PAL_API void PAL_SetBufferData(PAL_Buffer* buffer, u32 type, void* data, u32 size);

PAL_API PAL_BufferLayoutInfo PAL_GetBufferLayoutInfo(u32* layout, u32 count);