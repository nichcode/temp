
#include "PAL_pch.h"
#include "dx11/PAL_dx11device.h"

#include <d3d11.h>

struct PAL_Dx11Device
{
    ID3D11Device* handle;
    ID3D11DeviceContext* context;
};

void* PAL_CreateDx11Device()
{
    if (s_Data.directx_flags & PAL_DIRECTX11) {
        PFN_D3D11_CREATE_DEVICE D3D11CreateDevice_pfn = nullptr;
        
        D3D11CreateDevice_pfn = (PFN_D3D11_CREATE_DEVICE)PAL_GetProcAddress(s_Data.dx11, "D3D11CreateDevice");
        PAL_CHECK(D3D11CreateDevice_pfn, "failed to get D3D11CreateDevice from d3d11.dll", nullptr)

        PAL_Dx11Device* device = (PAL_Dx11Device*)s_Data.allocator.alloc(sizeof(PAL_Dx11Device)); 
        PAL_CHECK(device, "Failed to create dx11 device", nullptr);

        D3D_FEATURE_LEVEL feature_levels[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0
        };
    
        D3D_FEATURE_LEVEL supported_feature_Level;
        D3D11CreateDevice_pfn(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            feature_levels,
            ARRAYSIZE(feature_levels),
            D3D11_SDK_VERSION,
            &device->handle,
            nullptr,
            &device->context
        );

        PAL_CHECK(device->handle, "Failed to create dx11 device, check direct3d version", nullptr);
        if (!device->context) {
            device->handle->Release();
            s_Data.allocator.free(device);
            PAL_SetError("Failed to create dx11 device context, check direct3d version");
            return nullptr;
        }
        return device;
    }
    else {
        PAL_SetError("Directx11 is not supported on your graphics card");
        return nullptr;
    }
}

void PAL_DestroyDx11Device(void* dx11_device)
{
    PAL_Dx11Device* device = (PAL_Dx11Device*)dx11_device;
    device->handle->Release();
    device->context->Release();
    s_Data.allocator.free(device);
}