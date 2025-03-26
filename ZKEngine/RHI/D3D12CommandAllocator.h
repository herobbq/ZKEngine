#pragma once
#include "RHI/D3D12Device.h"
class FD3D12CommandAllocator final
{
public:
    FD3D12CommandAllocator(FD3D12Device* Device, ED3D12QueueType QueueType);
    ~FD3D12CommandAllocator(){};
    FD3D12Device* const Device;
    ED3D12QueueType const QueueType;
    operator ID3D12CommandAllocator*() { return CommandAllocator.Get(); }
    void Reset();
private:
    ComPtr<ID3D12CommandAllocator> CommandAllocator; 
};
