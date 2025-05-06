
#pragma once

#include "PAL/PAL_device.h"

void* PAL_CreateGLDevice(PAL_DeviceDesc* desc);
void PAL_DestroyGLDevice(void* gl_device);

void PAL_GLSwapBuffers(void* gl_device, b8 vsync);
void PAL_GLClear(void* gl_device);

void PAL_GLSetClearColor(void* gl_device, PAL_Color* color);