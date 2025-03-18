#include "D3D12Device.h"
#include "D3D12Queue.h"
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
