#include "D3D12Device.h"
#include "D3D12CommandAllocator.h"
FD3D12Device::FD3D12Device(FD3D12Adapter* InAdapter)
    :FD3D12AdapterChild(InAdapter)
{
    for (int QueueType = 0; QueueType < (int)ED3D12QueueType::Count; ++QueueType)
    {
        Queues.push_back({this, (ED3D12QueueType)QueueType});
    }
}

FD3D12Device::~FD3D12Device()
{
}

ID3D12Device* FD3D12Device::GetDevice()
{
    return GetParentAdapter()->GetD3DDevice();
}

void FD3D12Device::SetupAfterDeviceCreation()
{
}

FD3D12CommandAllocator* FD3D12Device::ObtainCommandAllocator(ED3D12QueueType QueueType)
{
    FD3D12CommandAllocator* Allocator;
    if (Queues[(unsigned int)QueueType].ObjectPool.Allocators.size()>0)
    {
        Allocator = Queues[(unsigned int)QueueType].ObjectPool.Allocators.top();
        Queues[(unsigned int)QueueType].ObjectPool.Allocators.pop();
    }
    else 
    {
        Allocator = new FD3D12CommandAllocator(this, QueueType);
    }
    return Allocator;
}
