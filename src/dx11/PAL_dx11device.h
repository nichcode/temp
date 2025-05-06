
#pragma once

#include "PAL/PAL_device.h"

void* PAL_CreateDx11Device(PAL_DeviceDesc* desc);
void PAL_DestroyDx11Device(void* dx11_device);

void PAL_Dx11SwapBuffers(void* dx11_device, b8 vsync);