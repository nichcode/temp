
#pragma once

#include "PAL/PAL_buffer.h"

void* PAL_CreateDx11Buffer(void* dx11_device, PAL_BufferDesc* desc);
void PAL_DestroyDx11Buffer(void* dx11_buffer);

void PAL_SetDx11BufferData(void* dx11_buffer, void* data, u32 size);
void PAL_BindDx11Buffer(void* dx11_buffer, u32 slot, u32 stride, u32 offset);