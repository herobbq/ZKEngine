#pragma once
#include <string>
extern  void RHIInit();
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
};
class IDynamicRHIModule
{
public:
    virtual bool IsSupported(ERHIPlatform Platform) = 0;
    virtual FDynamicRHI* CreateRHI() = 0;
};