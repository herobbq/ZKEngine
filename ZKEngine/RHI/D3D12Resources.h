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
    D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress(){return Resource->GetGPUVirtualAddress();}
    ComPtr<ID3D12Resource> GetResource(){return Resource;}
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

    uint32 GetSizeInBytes(){return  NumVertices * Stride;}
    void init (std::vector<FStaticMeshVertex>& InData);
    
protected:
    uint8* Data;
    uint32 Stride;
    uint32 NumVertices;
    
};

class FD3D12IndexBuffer : public FD3D12Resource
{
public:
    FD3D12IndexBuffer(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc,D3D12_HEAP_PROPERTIES& InHeapProp);
    void init (std::vector<uint32>& InData);
    inline uint32 GetNumIndex() const
    {
        return NumIndexs;
    }
    uint32 GetSizeInBytes(){return  NumIndexs * Stride;}
protected:
    uint8* Data;
    uint32 Stride;
    uint32 NumIndexs;
};

class FD3D12ConstantBuffer : public FD3D12Resource
{
public:
    FD3D12ConstantBuffer(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc,FD3D12Heap* InHeap, uint64 InOffset);
    void init (void** InData);
protected:
    FD3D12Heap* Heap;
    uint64 Offset;
    uint8* Data;
};