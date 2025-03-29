#include "D3D12Descriptor.h"
D3D12_DESCRIPTOR_HEAP_TYPE Translate(ERHIDescriptorHeapType InHeapType)
{
    switch (InHeapType)
    {
    default: D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    case ERHIDescriptorHeapType::Standard:     return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    case ERHIDescriptorHeapType::RenderTarget: return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    case ERHIDescriptorHeapType::DepthStencil: return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    case ERHIDescriptorHeapType::Sampler:      return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
    }
}

D3D12_DESCRIPTOR_HEAP_FLAGS Translate(ED3D12DescriptorHeapFlags InHeapFlags)
{
    if (EnumHasAnyFlags(InHeapFlags, ED3D12DescriptorHeapFlags::GpuVisible))
    {
        return D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    }

    return D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
}
FD3D12DescriptorHeap::FD3D12DescriptorHeap(FD3D12Device* InDevice, ComPtr<ID3D12DescriptorHeap>&& InHeap, ERHIDescriptorHeapType InType, ED3D12DescriptorHeapFlags InFlags)
    : FD3D12DeviceChild(InDevice)
    ,Heap(InHeap)
    ,CpuBase(Heap->GetCPUDescriptorHandleForHeapStart())
    , DescriptorSize(InDevice->GetDevice()->GetDescriptorHandleIncrementSize(Translate(InType)))
    , GpuBase(EnumHasAnyFlags(InFlags, ED3D12DescriptorHeapFlags::GpuVisible) ? Heap->GetGPUDescriptorHandleForHeapStart() : D3D12_GPU_DESCRIPTOR_HANDLE{})
{
}
