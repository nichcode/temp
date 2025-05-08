
#include "PAL_pch.h"
#include "PAL_glbuffer.h"
#include "PAL_gl.h"

inline u32 PAL_GetGLDataTypeCount(u32 type)
{
    switch (type) {
        case PAL_DATATYPE_FLOAT:
        case PAL_DATATYPE_INT: {
            return 1;
        }

        case PAL_DATATYPE_FLOAT2:
        case PAL_DATATYPE_INT2: {
            return 2;
        }

        case PAL_DATATYPE_FLOAT3:
        case PAL_DATATYPE_INT3: {
            return 3;
        }

        case PAL_DATATYPE_FLOAT4:
        case PAL_DATATYPE_INT4: {
            return 4;
        }
    }

    return 0;
}

void PAL_SetBufferLayout(u32 start_slot, u32 type, u32 divisor, u32 stride, u64 offset)
{
    switch (type) {
        case PAL_DATATYPE_FLOAT: 
        case PAL_DATATYPE_FLOAT2: 
        case PAL_DATATYPE_FLOAT3: 
        case PAL_DATATYPE_FLOAT4: {
            u32 count = PAL_GetGLDataTypeCount(type);
            glVertexAttribPointer(start_slot, count, type, false, stride, (const void*)offset);
            glEnableVertexAttribArray(start_slot);
            glVertexAttribDivisor(start_slot, divisor);
            break;
        }

        case PAL_DATATYPE_INT: 
        case PAL_DATATYPE_INT2: 
        case PAL_DATATYPE_INT3: 
        case PAL_DATATYPE_INT4: {
            u32 count = PAL_GetGLDataTypeCount(type);
            glVertexAttribIPointer(start_slot, count, type, stride, (const void*)offset);
            glEnableVertexAttribArray(start_slot);
            glVertexAttribDivisor(start_slot, divisor);
            break;
        }
    }
}

inline u32 PAL_GetGLBufferType(u32 type)
{
    switch (type) {
        case PAL_VERTEX_BUFFER: {
            return GL_ARRAY_BUFFER;
            break;
        }
        case PAL_INDEX_BUFFER: {
            return GL_ELEMENT_ARRAY_BUFFER;  
            break;
        }

        case PAL_STORAGE_BUFFER: {
            return GL_SHADER_STORAGE_BUFFER;
            break;
        }

        case PAL_UNIFORM_BUFFER: {
            return GL_UNIFORM_BUFFER;
            break;
        }
    }

    return 0;
}

inline u32 PAL_GetGLBufferUsage(u32 usage)
{
    switch (usage) {
        case PAL_STATIC: {
            return GL_STATIC_DRAW;
            break;
        }
        case PAL_DYNAMIC: {
            return GL_DYNAMIC_DRAW;  
            break;
        }
    }

    return 0;
}

void* PAL_CreateGLBuffer(void* gl_device, PAL_BufferDesc* desc)
{
    PAL_GLBuffer* buffer = (PAL_GLBuffer*)s_Data.allocator.alloc(sizeof(PAL_GLBuffer));
    PAL_CHECK(buffer, "Failed to create gl buffer", nullptr);

    glGenBuffers(1, &buffer->id);
    buffer->size = desc->size;
    buffer->data = desc->data;
    buffer->binding = desc->binding;
    buffer->type = PAL_GetGLBufferType(desc->type);
    buffer->usage = PAL_GetGLBufferUsage(desc->usage);
    buffer->data_sent = false;

    return buffer;
}

void PAL_DestroyGLBuffer(void* gl_buffer)
{
    PAL_GLBuffer* buffer = (PAL_GLBuffer*)gl_buffer;
    glDeleteBuffers(1, &buffer->id);
    s_Data.allocator.free(buffer);
}

void PAL_SetGLBufferData(void* gl_buffer, void* data, u32 size)
{
    PAL_GLBuffer* buffer = (PAL_GLBuffer*)gl_buffer;
    buffer->re_data = data;
    buffer->re_size = size;
}

void PAL_BindGLBuffer(void* gl_buffer, u32 start_slot, u32 type, u32 divisor, u32 stride, u64 offset)
{
    PAL_GLBuffer* buffer = (PAL_GLBuffer*)gl_buffer;
    if (buffer->data_sent == false) {
        glBindBuffer(buffer->type, buffer->id);
        glBufferData(buffer->type, buffer->size, buffer->data, buffer->usage);
        
        switch (buffer->type) {
            case GL_UNIFORM_BUFFER:
            case GL_SHADER_STORAGE_BUFFER: {
                glBindBufferBase(buffer->type, buffer->binding, buffer->id);
                break;
            }
        }

        PAL_SetBufferLayout(start_slot, type, divisor, stride, offset);
        buffer->data_sent = true;
    }

    else if (buffer->data_sent) {
        glBindBuffer(buffer->type, buffer->id);
        if (buffer->re_data) {
            glBufferSubData(buffer->type, 0, buffer->re_size, buffer->re_data);
        }
        return;
    } 
}