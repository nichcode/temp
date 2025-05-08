
#pragma once

#include "PAL/PAL_device.h"

void* PAL_CreateDx11Device(PAL_DeviceDesc* desc);
void PAL_DestroyDx11Device(void* dx11_device);

void PAL_Dx11SwapBuffers(void* dx11_device, b8 vsync);
void PAL_Dx11Clear(void* dx11_device);
void PAL_Dx11Flush(void* dx11_device, u32 primitive, u32 mode, u32 count, u32 instance_count);

void PAL_Dx11SetClearColor(void* dx11_device, PAL_Color* color);