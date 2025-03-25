#pragma once
#include <vector>
#include "D3D12Submission.h"
#include "D3D12Adapter.h"
//#include "D3D12Queue.h"
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
class FD3D12Queue;
class FD3D12Device : public  FD3D12AdapterChild
{
public:
    FD3D12Device(FD3D12Adapter * InAdapter);
    ~FD3D12Device();
  
    ID3D12Device* GetDevice();
    FD3D12Queue& GetQueue(ED3D12QueueType QueueType) { return Queues[(unsigned int)QueueType]; }
    void SetupAfterDeviceCreation();
private:
    std::vector<FD3D12Queue> Queues;
};

