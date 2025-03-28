#pragma once
#include "D3D12Device.h"

class FD3D12Heap : public  FD3D12DeviceChild
{
public:
    FD3D12Heap(FD3D12Device* Parent);
    ID3D12Heap* GetD3DHeap() const { return Heap.Get(); }
    void Create(D3D12_HEAP_DESC& Des);
protected:
    ComPtr<ID3D12Heap> Heap;
};
