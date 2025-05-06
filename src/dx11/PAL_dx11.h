
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