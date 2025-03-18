#pragma once
#include "D3D12Device.h"
#include "D3D12Submission.h"
enum class ED3D12QueueType
{
    Direct = 0,
    Copy,
    Async,

    Count,
};


class FD3D12Queue final
{
public:
    FD3D12Device* const Device;
    ED3D12QueueType const QueueType;
    FD3D12Queue(FD3D12Device* Device, ED3D12QueueType QueueType);
    ~FD3D12Queue();
    ComPtr<ID3D12CommandQueue> D3DCommandQueue;
    FD3D12Fence Fence;
};

inline D3D12_COMMAND_LIST_TYPE GetD3DCommandListType(ED3D12QueueType QueueType)
{
    switch (QueueType)
    {
    case ED3D12QueueType::Direct: return D3D12_COMMAND_LIST_TYPE_DIRECT;
    case ED3D12QueueType::Copy:   return D3D12_COMMAND_LIST_TYPE_COPY;
    case ED3D12QueueType::Async:  return D3D12_COMMAND_LIST_TYPE_COMPUTE;
    default: return D3D12_COMMAND_LIST_TYPE_DIRECT;
    }
}