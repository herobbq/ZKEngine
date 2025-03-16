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
public:
    FD3D12DynamicRHI(shared_ptr<FD3D12Adapter> Adapter);
    ~FD3D12DynamicRHI(){};
    virtual void Init()  override;
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