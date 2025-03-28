#include "D3D12Resources.h"

FD3D12Heap::FD3D12Heap(FD3D12Device* Parent)
    : FD3D12DeviceChild(Parent)
{
    
}

void FD3D12Heap::Create(D3D12_HEAP_DESC& Des)
{
    Parent->GetDevice()->CreateHeap(&Des, IID_PPV_ARGS(&Heap));
}
