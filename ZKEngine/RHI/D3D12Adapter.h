#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>//DXGI的头
#include <wrl/client.h>
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
    void InitializeDevices();
protected:
    void CreateDXGIFactory(bool bWithDebug);
    void EnumeAdapters();
protected:
    FD3D12AdapterDesc Desc;
    ComPtr<ID3D12Device> RootDevice;
    ComPtr<IDXGIFactory5> DxgiFactory5;
    ComPtr<IDXGIAdapter1> DxgiAdapter;
};



