#pragma once
#include "D3D12Device.h"
#include "D3D12Submission.h"


class FD3D12Device;


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