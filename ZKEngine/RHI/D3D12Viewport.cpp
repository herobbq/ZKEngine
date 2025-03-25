#include "D3D12Viewport.h"

#include "D3D12Device.h"

static const uint32 WindowsDefaultNumBackBuffers = 3;
FD3D12Viewport::FD3D12Viewport(class FD3D12Adapter* InParent, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY,
                               bool bInIsFullscreen,EPixelFormat InPixelFormat)
    :FD3D12AdapterChild(InParent)
    , WindowHandle(InWindowHandle)
    , SizeX(InSizeX)
    , SizeY(InSizeY)
    , bIsFullscreen(bInIsFullscreen)
    , PixelFormat(InPixelFormat)
    ,NumBackBuffers(WindowsDefaultNumBackBuffers)
{
}

void FD3D12Viewport::Init()
{
    FD3D12Adapter* Adapter = GetParentAdapter();
    IDXGIFactory5* Factory5 = Adapter->GetDXGIFactory5();
    ComPtr<ID3D12CommandQueue> CommandQueue = Adapter->GetDevice()->GetQueue(ED3D12QueueType::Direct).D3DCommandQueue;
    UINT SwapChainFlags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    DXGI_SWAP_CHAIN_DESC1 stSwapChainDesc = {};
    stSwapChainDesc.BufferCount = NumBackBuffers;
    stSwapChainDesc.Width = SizeX;
    stSwapChainDesc.Height = SizeY;
    stSwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;;
    stSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
    stSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    stSwapChainDesc.SampleDesc.Count = 1;
    
    GRS_THROW_IF_FAILED(Factory5->CreateSwapChainForHwnd(
                CommandQueue.Get(),		// Swap chain needs the queue so that it can force a flush on it.
                WindowHandle,
                &stSwapChainDesc,
                nullptr,
                nullptr,
                &SwapChain1
            ));
    
}
