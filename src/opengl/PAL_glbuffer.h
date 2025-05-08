
#pragma once

#include "PAL/PAL_buffer.h"

void* PAL_CreateGLBuffer(void* gl_device, PAL_BufferDesc* desc);
void PAL_DestroyGLBuffer(void* gl_buffer);

void PAL_SetGLBufferData(void* gl_buffer, void* data, u32 size);
void PAL_BindGLBuffer(void* gl_buffer, u32 start_slot, u32 type, u32 divisor, u32 stride, u64 offset);