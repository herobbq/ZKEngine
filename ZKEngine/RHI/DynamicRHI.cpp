#include "DynamicRHI.h"
#include <iostream>

#include "D3D12RHI/D3D12RHIPrivate.h"

FDynamicRHI* GDynamicRHI = nullptr;
IDynamicRHIModule* GDynamicRHIModule = nullptr;
void RHIInit()
{
    if (GDynamicRHI == nullptr)
    {
        GDynamicRHI = GDynamicRHIModule->CreateRHI();
        GDynamicRHI->Init();
    }
    std::cout<<"RHIInit"<<std::endl;
}

bool LoadModule(std::string Platform)
{
    if (Platform == "D3D12")
    {
        GDynamicRHIModule = new FD3D12DynamicRHIModule();
        return GDynamicRHIModule->IsSupported(ERHIPlatform::WINDOW_D3D12);
    }
}

std::shared_ptr<FRHIViewport> RHICreateViewport(void* WindowHandle, unsigned int SizeX, unsigned int SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat)
{
    return  GDynamicRHI->RHICreateViewport(WindowHandle, SizeX, SizeY, bIsFullscreen, PreferredPixelFormat);
}