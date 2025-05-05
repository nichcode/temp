
#pragma once

#include "PAL_defines.h"

struct PAL_Device;

enum PAL_DeviceType
{
    PAL_DEVICE_DX11
};

PAL_API PAL_Device* PAL_CreateDevice(u32 device_type);
PAL_API void PAL_DestroyDevice(PAL_Device* device);