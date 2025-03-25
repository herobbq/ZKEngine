#pragma once
#include <memory>
#include <string>
#include "RHIViewport.h"
extern  void RHIInit();
extern  std::shared_ptr<FRHIViewport> RHICreateViewport(void* WindowHandle, unsigned int SizeX, unsigned int SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat);
extern  bool LoadModule(std::string Platform);
enum ERHIPlatform :int
{
    WINDOW_D3D11,
    WINDOW_D3D12,
    WINDOW_VULKAN,
    Num
};


class FDynamicRHI
{
public:
    virtual ~FDynamicRHI() {}
    virtual void Init() = 0;
    virtual std::shared_ptr<FRHIViewport> RHICreateViewport(void* WindowHandle, unsigned int SizeX, unsigned int SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat) = 0;
};
class IDynamicRHIModule
{
public:
    virtual bool IsSupported(ERHIPlatform Platform) = 0;
    virtual FDynamicRHI* CreateRHI() = 0;
};



extern  FDynamicRHI* GDynamicRHI;


