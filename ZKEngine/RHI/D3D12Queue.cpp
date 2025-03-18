#include "D3D12Queue.h"
#include "D3D12Util.h"
FD3D12Queue::FD3D12Queue(FD3D12Device* Device, ED3D12QueueType QueueType)
    :Device(Device)
    ,QueueType(QueueType)
{
    D3D12_COMMAND_QUEUE_DESC stQueueDesc = {};
    stQueueDesc.Type = GetD3DCommandListType(QueueType);
    GRS_THROW_IF_FAILED(Device->GetDevice()->CreateCommandQueue(&stQueueDesc, IID_PPV_ARGS(&D3DCommandQueue)));
    
    GRS_THROW_IF_FAILED(Device->GetDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence.D3DFence)));
}

FD3D12Queue::~FD3D12Queue()
{
}
