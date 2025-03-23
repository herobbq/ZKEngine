#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>//DXGI的头
#include <wrl/client.h>

class FD3D12Device;
using namespace Microsoft::WRL;
struct FD3D12AdapterDesc
{
    FD3D12AdapterDesc(const DXGI_ADAPTER_DESC1& InDesc, unsigned int InAdapterIndex);
    DXGI_ADAPTER_DESC1 Desc{};
    unsigned int AdapterIndex = -1;
};
class FD3D12Adapter
{
public:
    FD3D12Adapter(FD3D12AdapterDesc& DescIn);
    virtual ~FD3D12Adapter(){};
    
    ID3D12Device* GetD3DDevice() const { return RootDevice.Get(); }
    IDXGIAdapter* GetAdapter() { return DxgiAdapter.Get(); }
    FD3D12Device* GetDevice() const {return  Device;}
    void InitializeDevices();
protected:
    void CreateDXGIFactory(bool bWithDebug);
    void EnumeAdapters();

    void CreateRootDevice(bool bWithDebug);
protected:
    FD3D12AdapterDesc Desc;
    ComPtr<ID3D12Device> RootDevice;
    ComPtr<IDXGIFactory5> DxgiFactory5;
    ComPtr<IDXGIAdapter1> DxgiAdapter;

    FD3D12Device* Device;
};

class FD3D12AdapterChild
{
public:
    FD3D12AdapterChild(FD3D12Adapter* InParent = nullptr) : ParentAdapter(InParent) {}
     FD3D12Adapter* GetParentAdapter() const
    {
        return ParentAdapter;
    }

    // To be used with delayed setup
    inline void SetParentAdapter(FD3D12Adapter* InParent)
    {
        ParentAdapter = InParent;
    }
protected:
    FD3D12Adapter* ParentAdapter;
};


