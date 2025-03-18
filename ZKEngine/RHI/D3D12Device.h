#pragma once
#include <vector>

#include "D3D12Adapter.h"
//#include "D3D12Queue.h"

class FD3D12Queue;
class FD3D12Device : public  FD3D12AdapterChild
{
public:
    FD3D12Device(FD3D12Adapter * InAdapter);
    ~FD3D12Device();
  
    ID3D12Device* GetDevice();

private:
    std::vector<FD3D12Queue> Queues;
};

