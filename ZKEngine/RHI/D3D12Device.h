﻿#pragma once
#include <memory>
#include <stack>
#include <vector>
#include "D3D12Submission.h"
#include "D3D12Adapter.h"

#include "D3D12Util.h"
class FD3D12CommandList;
class FD3D12DescriptorHeap;
class FD3D12Heap;
//#include "D3D12Queue.h"
typedef unsigned __int64 uint64;
class FD3D12PipelineState;
class FD3D12CommandAllocator;


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

    struct
    {
        //std::shared_ptr<FD3D12ContextCommon   > Contexts;
        std::stack<FD3D12CommandAllocator* > Allocators;
        //std::stack<FD3D12CommandList> Lists;
    } ObjectPool;
    
    FD3D12Queue(FD3D12Device* Device, ED3D12QueueType QueueType);
    ~FD3D12Queue();
    void FlushCommandQueue()
    {
        HANDLE hEventFence = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        uint64 ValueToSignal = ++Fence.LastSignaledValue;
        GRS_THROW_IF_FAILED(D3DCommandQueue->Signal(
            Fence.D3DFence.Get(),
            ValueToSignal
        ));
        Fence.D3DFence->SetEventOnCompletion(ValueToSignal, hEventFence);
        WaitForSingleObject(hEventFence, INFINITE);
        //return ValueToSignal;
    }
    void ExecuteCommandLists(std::vector<FD3D12CommandList*>& CommandList);
    ComPtr<ID3D12CommandQueue> D3DCommandQueue;
protected:
    bool bRequiresSignal = false;

    FD3D12Fence Fence;
};
class FD3D12Queue;
class FD3D12Device : public  FD3D12AdapterChild
{
public:
    FD3D12Device(FD3D12Adapter * InAdapter);
    ~FD3D12Device();
    
    ID3D12Device* GetDevice();
    bool bRequiresSignal = false;
    FD3D12Queue& GetQueue(ED3D12QueueType QueueType) { return Queues[(unsigned int)QueueType]; }
    void SetupAfterDeviceCreation();
    std::shared_ptr<FD3D12PipelineState> CreatePipelineState(D3D12_GRAPHICS_PIPELINE_STATE_DESC& Des);
    std::shared_ptr<FD3D12Heap> CreateHeap(D3D12_HEAP_DESC& Des);
    std::shared_ptr<FD3D12DescriptorHeap> CreateDescriptorHeap(ERHIDescriptorHeapType HeapType,uint32 NumDescriptors, ED3D12DescriptorHeapFlags Flags);
    FD3D12CommandAllocator* ObtainCommandAllocator (ED3D12QueueType QueueType);
private:
    std::vector<FD3D12Queue> Queues;
};

class FD3D12DeviceChild
{
protected:
    FD3D12Device* Parent;

public:
    FD3D12DeviceChild(FD3D12Device* InParent = nullptr) : Parent(InParent) {}

    FORCEINLINE FD3D12Device* GetParentDevice() const
    {
        return Parent;
    }

   
};