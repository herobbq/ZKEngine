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

void FD3D12VertexBuffer::init(std::vector<FStaticMeshVertex>& InData)
{
    
    Data = (uint8*)InData.data();
    Stride = sizeof(FStaticMeshVertex);
    NumVertices = InData.size();
    D3D12_RANGE stReadRange = { 0, 0 };
    
    GRS_THROW_IF_FAILED(Resource->Map(0, &stReadRange, reinterpret_cast<void**>(&Data)));
    memcpy(Data,InData.data(),InData.size() * Stride);
    Resource->Unmap(0, nullptr);
       
    
}

FD3D12IndexBuffer::FD3D12IndexBuffer(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc,
    D3D12_HEAP_PROPERTIES& InHeapProp)
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

void FD3D12IndexBuffer::init(std::vector<uint32>& InData)
{
    
    Data = (uint8*)InData.data();
    Stride = sizeof(FStaticMeshVertex);
    NumIndexs = InData.size();
    D3D12_RANGE stReadRange = { 0, 0 };
    
    GRS_THROW_IF_FAILED(Resource->Map(0, &stReadRange, reinterpret_cast<void**>(&Data)));
    memcpy(Data,InData.data(),InData.size() * Stride);
    Resource->Unmap(0, nullptr);
}

FD3D12ConstantBuffer::FD3D12ConstantBuffer(FD3D12Device* Parent, D3D12_RESOURCE_DESC& InDesc, FD3D12Heap* InHeap,
    uint64 InOffset)
        :FD3D12Resource(Parent, InDesc)
        , Heap(InHeap)
        , Offset(InOffset)
{
    GRS_THROW_IF_FAILED(Parent->GetDevice()->CreatePlacedResource(
        InHeap->GetD3DHeap()
            , InOffset
            , &InDesc
            , D3D12_RESOURCE_STATE_GENERIC_READ
            , nullptr
            , IID_PPV_ARGS(&Resource)));
}

void FD3D12ConstantBuffer::init(void** InData)
{
    GRS_THROW_IF_FAILED(Resource->Map(0, nullptr, reinterpret_cast<void**>(InData)));
}

