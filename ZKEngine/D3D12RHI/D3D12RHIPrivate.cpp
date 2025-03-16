#include "D3D12RHIPrivate.h"

#define WIN32_LEAN_AND_MEAN // 从 Windows 头中排除极少使用的资料
#include <wincodec.h>   
#include <wrl.h>		//添加WTL支持 方便使用COM，就是COM只能指针需要的
#include <d3d12.h>       //for d3d12
#include <complex.h>
#if defined(_DEBUG)
#include <dxgidebug.h>//DXGI有一个独自的调试，下面还有一个flag相关的
#endif
#include <iostream>
using namespace  Microsoft::WRL;

//用于判断函数执行错误的，如果出错了就会引发异常
#define GRS_THROW_IF_FAILED(hr) {HRESULT _hr = (hr);if (FAILED(_hr)){ throw CGRSCOMException(_hr); }}
FD3D12DynamicRHI* GD3D12RHI = nullptr;
class CGRSCOMException
{
public:
    CGRSCOMException(HRESULT hr) : m_hrError(hr)
    {
    }
    HRESULT Error() const
    {
        return m_hrError;
    }
private:
    const HRESULT m_hrError;
};

FD3D12DynamicRHI::FD3D12DynamicRHI(shared_ptr<FD3D12Adapter> InAdapter)
    :Adapter(InAdapter)
{
}

void FD3D12DynamicRHI::Init()
{
    if (Adapter)
    {
        Adapter->InitializeDevices();
    }
}

bool FD3D12DynamicRHIModule::IsSupported(ERHIPlatform Platform)
{
    if (Adapter == nullptr)
        FindAdapter();
    if (Adapter == nullptr)
    {
        std::cout << "No adapters were found."<<std::endl;
        return false;
    }
       return  true;
}

void FD3D12DynamicRHIModule::FindAdapter()
{
    ComPtr<IDXGIFactory5>	IDXGIFactory5;
 
    GRS_THROW_IF_FAILED(CreateDXGIFactory2(0, IID_PPV_ARGS(IDXGIFactory5.GetAddressOf())));
    DXGI_ADAPTER_DESC1 stAdapterDesc = {};//适配器描述的结构，待会获取描述时，用这个结构体来接收

     ComPtr<IDXGIAdapter1> TempAdapter;
    //利用DXGIFactory来循环遍历你的所有显卡。
    for (UINT AdapterIndex = 0; DXGI_ERROR_NOT_FOUND != IDXGIFactory5->EnumAdapters1(AdapterIndex, &TempAdapter); ++AdapterIndex)
    {
        TempAdapter->GetDesc1(&stAdapterDesc);//从当前正在遍历的显卡中获取显卡的描述信息，用准备好的结构体接收

        if (stAdapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        {//跳过软件虚拟适配器设备
            continue;
        }
        //检查适配器对D3D支持的兼容级别，这里直接要求支持12.1的能力，注意返回接口的那个参数被置为了nullptr，这样
        //就不会实际创建一个设备了，也不用我们啰嗦的再调用release来释放接口。这也是一个重要的技巧，请记住！
        if (SUCCEEDED(D3D12CreateDevice(TempAdapter.Get(), D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr)))
        {
            FD3D12AdapterDesc CurrentAdapter(stAdapterDesc, AdapterIndex);
            Adapter = make_shared<FD3D12Adapter>((CurrentAdapter));
            break;
        }
        
    }
    if (Adapter == nullptr)
    {
        std::cout << "No adapters were found."<<std::endl;
    }
     
}

FDynamicRHI* FD3D12DynamicRHIModule::CreateRHI()
{
    GD3D12RHI = new FD3D12DynamicRHI(Adapter);
    return GD3D12RHI;
}
