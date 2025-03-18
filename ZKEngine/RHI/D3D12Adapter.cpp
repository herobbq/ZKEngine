#include "D3D12Adapter.h"
#include "D3D12Device.h"
#include "D3D12Util.h"
FD3D12AdapterDesc::FD3D12AdapterDesc(const DXGI_ADAPTER_DESC1& InDesc, unsigned int InAdapterIndex)
    :Desc(InDesc),
    AdapterIndex(InAdapterIndex)
{
}

FD3D12Adapter::FD3D12Adapter(FD3D12AdapterDesc& DescIn)
    : Desc(DescIn)
{
}

void FD3D12Adapter::InitializeDevices()
{
    if (!RootDevice)
    {
        bool WithDebug = false;
#if defined(_DEBUG)
        WithDebug = true;
#endif
        CreateRootDevice(WithDebug);
        
    }
    Device = new FD3D12Device(this);
}

void FD3D12Adapter::CreateDXGIFactory(bool bWithDebug)
{
    unsigned int DXGIFactoryFlags = 0u;
    if (bWithDebug)
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
            // 打开附加的调试支持
            DXGIFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        }
    }
    
    //5、创建DXGI Factory对象
    {
        CreateDXGIFactory2(DXGIFactoryFlags, IID_PPV_ARGS(DxgiFactory5.GetAddressOf()));
    }
}

void FD3D12Adapter::EnumeAdapters()
{
    if (!DxgiFactory5 || Desc.AdapterIndex ==  -1)
        return;
    DxgiFactory5->EnumAdapters1(Desc.AdapterIndex, &DxgiAdapter);
}

void FD3D12Adapter::CreateRootDevice(bool bWithDebug)
{
    CreateDXGIFactory(bWithDebug);
    EnumeAdapters();
    GRS_THROW_IF_FAILED(D3D12CreateDevice(GetAdapter(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&RootDevice)));
}
