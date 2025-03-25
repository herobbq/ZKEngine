#pragma once
#include "RHIViewport.h"
#include "D3D12Adapter.h"
#include "D3D12Util.h"

class FD3D12Viewport : public FRHIViewport, public FD3D12AdapterChild
{
public:
    FD3D12Viewport(class FD3D12Adapter* InParent, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY, bool bInIsFullscreen,EPixelFormat InPixelFormat);
    void Init();

	virtual void* GetNativeSwapChain() override { return SwapChain1.Get(); }
protected:
    HWND WindowHandle;
    uint32 SizeX;
    uint32 SizeY;
    bool bIsFullscreen;
	EPixelFormat PixelFormat;
    uint32 NumBackBuffers;


	ComPtr<IDXGISwapChain1> SwapChain1;
};
