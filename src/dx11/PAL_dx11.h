
#pragma once

#include <d3d11.h>

struct PAL_Dx11Device
{
    ID3D11Device* handle;
    ID3D11DeviceContext* context;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* view = nullptr;

    f32 color[4]{};
};

struct PAL_Dx11Buffer
{
    ID3D11Buffer* handle;
    PAL_Dx11Device* device;
    u32 type;
};