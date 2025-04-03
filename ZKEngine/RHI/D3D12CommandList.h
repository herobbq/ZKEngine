#pragma once
#include <wrl/client.h>

#include "D3D12CommandAllocator.h"
using namespace Microsoft::WRL;
enum class ED3D12QueueType;
class FD3D12Device;
class FD3D12CommandAllocator;
class FD3D12CommandList
{
public:
    FD3D12CommandList(FD3D12CommandAllocator* CommandAllocator);
protected:
    FD3D12Device*       const Device;
    ED3D12QueueType     const QueueType;
private:
    struct FInterfaces
    {
       ComPtr<ID3D12CommandList>          CommandList;
        ComPtr<ID3D12GraphicsCommandList>  CopyCommandList;
        ComPtr<ID3D12GraphicsCommandList>  GraphicsCommandList;
    }Interfaces;
};
