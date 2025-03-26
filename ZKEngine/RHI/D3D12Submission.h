#pragma once
#include <d3d12.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;
struct FD3D12Fence
{
    ComPtr<ID3D12Fence> D3DFence;
    unsigned __int64  LastSignaledValue = 0;

};
