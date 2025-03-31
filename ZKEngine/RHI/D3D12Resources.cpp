#include "D3D12Resources.h"

FD3D12Heap::FD3D12Heap(FD3D12Device* Parent)
    : FD3D12DeviceChild(Parent)
{
    
}

void FD3D12Heap::Create(D3D12_HEAP_DESC& Des)
{
    Parent->GetDevice()->CreateHeap(&Des, IID_PPV_ARGS(&Heap));
}

FD3D12Resource::FD3D12Resource(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc)
    : FD3D12DeviceChild(Parent)
    , Desc(InDesc)
{
}

FD3D12VertexBuffer::FD3D12VertexBuffer(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc,D3D12_HEAP_PROPERTIES& InHeapProp)
    :FD3D12Resource(Parent, InDesc)
{
    GRS_THROW_IF_FAILED(Parent->GetDevice()->CreateCommittedResource(
                &InHeapProp,
                D3D12_HEAP_FLAG_NONE,
                &InDesc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&Resource)));
}
