
#include "PAL_pch.h"
#include "dx11/PAL_dx11device.h"
#include "PAL_dx11.h"

void* PAL_CreateDx11Device(PAL_DeviceDesc* desc)
{
    if (s_Data.directx_flags & PAL_DIRECTX11) {
        PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN D3D11CreateDevice_pfn = nullptr;
        
        D3D11CreateDevice_pfn = (PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN)PAL_GetProcAddress(
            s_Data.dx11, "D3D11CreateDeviceAndSwapChain");
        PAL_CHECK(D3D11CreateDevice_pfn, "failed to get D3D11CreateDeviceAndSwapChain from d3d11.dll", nullptr)

        PAL_Dx11Device* device = (PAL_Dx11Device*)s_Data.allocator.alloc(sizeof(PAL_Dx11Device)); 
        PAL_CHECK(device, "Failed to create dx11 device", nullptr);

        D3D_FEATURE_LEVEL feature_levels[] = {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0
        };

        DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
        if (desc->use_window_size) {
            swap_chain_desc.BufferDesc.Width = 0;
            swap_chain_desc.BufferDesc.Height = 0;
        }
        else {
            swap_chain_desc.BufferDesc.Width = desc->swap_chain_width;
            swap_chain_desc.BufferDesc.Height = desc->swap_chain_height;
        }
        swap_chain_desc.BufferCount = 2;
        swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = 120;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.OutputWindow = (HWND)PAL_GetWindowHandle(desc->window);
        swap_chain_desc.SampleDesc.Count = 1;
        swap_chain_desc.SampleDesc.Quality = 0;
        swap_chain_desc.Windowed = TRUE;
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swap_chain_desc.Flags = 0;
    
        D3D11CreateDevice_pfn(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            feature_levels,
            ARRAYSIZE(feature_levels),
            D3D11_SDK_VERSION,
            &swap_chain_desc,
            &device->swapChain,
            &device->handle,
            nullptr,
            &device->context
        );

        PAL_CHECK(device->handle, "Failed to create dx11 device", nullptr);
        PAL_CHECK(device->context, "Failed to create dx11 device context", nullptr);

        ID3D11Texture2D* back_buffer = nullptr;
        device->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer));
        PAL_CHECK(back_buffer, "failed to get back buffer from dx11 swap chain", nullptr)

        device->handle->CreateRenderTargetView(back_buffer, nullptr, &device->view);
        PAL_CHECK(device->view, "failed to create rendertarget", nullptr)

        back_buffer->Release();
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
    device->view->Release();
    device->swapChain->Release();
    device->context->Release();
    device->handle->Release();
    s_Data.allocator.free(device);
}

void PAL_Dx11SwapBuffers(void* dx11_device, b8 vsync)
{
    PAL_Dx11Device* device = (PAL_Dx11Device*)dx11_device;
    device->swapChain->Present(vsync, 0);
}

void PAL_Dx11Clear(void* dx11_device)
{
    PAL_Dx11Device* device = (PAL_Dx11Device*)dx11_device;
    device->context->ClearRenderTargetView(device->view, device->color);
}

void PAL_Dx11SetClearColor(void* dx11_device, PAL_Color* color)
{
    PAL_Dx11Device* device = (PAL_Dx11Device*)dx11_device;
    device->color[0] = color->r;
    device->color[1] = color->g;
    device->color[2] = color->b;
    device->color[3] = color->a;
}