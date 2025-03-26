#include "D3D12CommandAllocator.h"

#include "D3D12Queue.h"

FD3D12CommandAllocator::FD3D12CommandAllocator(FD3D12Device* Device, ED3D12QueueType QueueType)
    :Device(Device)
    ,QueueType(QueueType)
{
    GRS_THROW_IF_FAILED(Device->GetDevice()->CreateCommandAllocator(GetD3DCommandListType(QueueType)
                , IID_PPV_ARGS(&CommandAllocator)));
}

void FD3D12CommandAllocator::Reset()
{
    GRS_THROW_IF_FAILED(CommandAllocator->Reset());
}
