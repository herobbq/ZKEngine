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


class FD3D12Resource :  public FD3D12DeviceChild
{
public:
    FD3D12Resource(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc);
    
protected:
    ComPtr<ID3D12Resource> Resource;
    D3D12_RESOURCE_DESC Desc;
};

class FD3D12VertexBuffer : public FD3D12Resource
{
public:
    FD3D12VertexBuffer(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc,D3D12_HEAP_PROPERTIES& InHeapProp);
    void* GetVertexData() { return Data; }
    inline  uint32 GetStride() const
    {
        return Stride;
    }
    inline uint32 GetNumVertices() const
    {
        return NumVertices;
    }
protected:
    uint8* Data;
    uint32 Stride;
    uint32 NumVertices;
    
};