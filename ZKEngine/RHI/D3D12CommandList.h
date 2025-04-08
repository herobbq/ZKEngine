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
    void    CopyTextureRegion(const D3D12_TEXTURE_COPY_LOCATION *pDst,
            UINT DstX,
            UINT DstY,
            UINT DstZ,
            const D3D12_TEXTURE_COPY_LOCATION *pSrc,
            const D3D12_BOX *pSrcBox);
    void    Close();
    ID3D12CommandList* GetD3DCommandList(){return Interfaces.CommandList.Get();}
    ID3D12GraphicsCommandList* GetD3DGraphicsCommandList(){return Interfaces.GraphicsCommandList.Get();}
    void  Reset(FD3D12CommandAllocator * newCommandAllocator, FD3D12PipelineState*  newPipelineState = nullptr);
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
