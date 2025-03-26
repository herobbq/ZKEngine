#pragma once
#include <memory>
#include <stack>
#include <vector>
#include "D3D12Submission.h"
#include "D3D12Adapter.h"
#include "D3D12Util.h"
//#include "D3D12Queue.h"
typedef unsigned __int64 uint64;

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
    FD3D12CommandAllocator* ObtainCommandAllocator (ED3D12QueueType QueueType);
private:
    std::vector<FD3D12Queue> Queues;
};

