#pragma once
#include <memory>

#include "RHI/D3D12Adapter.h"
#include "RHI/DynamicRHI.h"
using namespace std;
struct ID3D12DynamicRHI : public FDynamicRHI
{
    virtual void Init() = 0;
};



class FD3D12DynamicRHI : public ID3D12DynamicRHI
{
    static FD3D12DynamicRHI* SingleD3DRHI;
public:
    FD3D12DynamicRHI(shared_ptr<FD3D12Adapter> Adapter);
    ~FD3D12DynamicRHI(){};
    virtual void Init()  override;
    FD3D12Device* GetRHIDevice() const;
    const FD3D12Adapter& GetAdapter() const {return  *Adapter;}
    FD3D12Adapter& GetAdapter() {return  *Adapter;}
    static FD3D12DynamicRHI* GetD3DRHI() { return SingleD3DRHI; }
    std::shared_ptr<FRHIViewport> RHICreateViewport(void* WindowHandle, unsigned int SizeX, unsigned int SizeY, bool bIsFullscreen, EPixelFormat PreferredPixelFormat);
protected:
    shared_ptr<FD3D12Adapter> Adapter;
    
};
class FD3D12DynamicRHIModule : public IDynamicRHIModule
{
public:
    FD3D12DynamicRHIModule()
    {
    }
    ~FD3D12DynamicRHIModule()
    {
    }
    virtual bool IsSupported(ERHIPlatform Platform);
    void FindAdapter();
    virtual FDynamicRHI* CreateRHI() override;
    shared_ptr<FD3D12Adapter> Adapter;
};