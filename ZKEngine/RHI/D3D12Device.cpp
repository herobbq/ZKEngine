#include "D3D12Device.h"
#include "D3D12CommandAllocator.h"
#include "D3D12PipelineState.h"
#include "D3D12Resources.h"

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

std::shared_ptr<FD3D12PipelineState> FD3D12Device::CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& Des)
{
    auto&& D3D12PipelineState =  std::make_shared<FD3D12PipelineState>(ParentAdapter);
    D3D12PipelineState->Create(Des);
    return D3D12PipelineState;
}

std::shared_ptr<FD3D12Heap> FD3D12Device::CreateHeap(D3D12_HEAP_DESC& Des)
{
    auto&& D3D12Heap =  std::make_shared<FD3D12Heap>(this);
    D3D12Heap->Create(Des);
    return D3D12Heap;
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
