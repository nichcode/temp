
#include "PAL_pch.h"

#include "dx11/PAL_dx11swapchain.h"

#define CHECK_DEVICE(swap_chain, ret) PAL_CHECK(swap_chain, "swapchain is null", ret)

struct PAL_SwapChain
{
    struct SwapChainAPI
    {
        void (*destroy)(void* handle) = nullptr;
    };

    void* handle = nullptr;
    PAL_Window* window = nullptr;
    SwapChainAPI API;
};

PAL_SwapChain* PAL_CreateSwapChain(PAL_Device* device, PAL_SwapChainDesc* desc)
{
    PAL_CHECK(device, "device is null", nullptr);
    PAL_SwapChain* swap_chain = (PAL_SwapChain*)s_Data.allocator.alloc(sizeof(PAL_SwapChain));
    PAL_CHECK(swap_chain, "Failed to create swapchain", nullptr);

    swap_chain->window = desc->window;

    switch (PAL_GetDeviceType(device)) {
        case PAL_DEVICE_DX11: {
            swap_chain->handle = PAL_CreateDx11SwapChain(desc);
            swap_chain->API.destroy = PAL_DestroyDx11SwapChain;
            break;
        }
        PAL_SetError("invalid device type");
    }
    
    return swap_chain;
}

void PAL_DestroySwapChain(PAL_SwapChain* swap_chain)
{
    CHECK_DEVICE(swap_chain,)
    swap_chain->API.destroy(swap_chain->handle);
    s_Data.allocator.set(&swap_chain->API, 0, sizeof(PAL_SwapChain::API));
    s_Data.allocator.free(swap_chain);
}