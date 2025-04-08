#include "D3D12CommandList.h"
#include "D3D12Queue.h"
#include "D3D12CommandAllocator.h"
#include "D3D12PipelineState.h"

FD3D12CommandList::FD3D12CommandList(FD3D12CommandAllocator* CommandAllocator)
    :Device(CommandAllocator->Device)
    ,QueueType(CommandAllocator->QueueType)
{
    switch (QueueType)
    {   default:
            break;
        case ED3D12QueueType::Direct:
        case ED3D12QueueType::Async:
        GRS_THROW_IF_FAILED(Device->GetDevice()->CreateCommandList(0, GetD3DCommandListType(QueueType)
                , *CommandAllocator, nullptr, IID_PPV_ARGS(&Interfaces.GraphicsCommandList)));
        Interfaces.CommandList = Interfaces.GraphicsCommandList;
        Interfaces.CommandList->QueryInterface(IID_PPV_ARGS(&Interfaces.CopyCommandList));
        break;
        case ED3D12QueueType::Copy:
            GRS_THROW_IF_FAILED(Device->GetDevice()->CreateCommandList(
            0,
            GetD3DCommandListType(QueueType),
            *CommandAllocator,
            nullptr,
            IID_PPV_ARGS(&Interfaces.CopyCommandList)
        ));
        Interfaces.CommandList = Interfaces.CopyCommandList;
        break;
    }
}

void FD3D12CommandList::CopyTextureRegion(const D3D12_TEXTURE_COPY_LOCATION* pDst, UINT DstX, UINT DstY, UINT DstZ,
    const D3D12_TEXTURE_COPY_LOCATION* pSrc, const D3D12_BOX* pSrcBox)
{
     Interfaces.CopyCommandList->CopyTextureRegion(pDst, DstX, DstY, DstZ, pSrc, pSrcBox);
    D3D12_RESOURCE_BARRIER stResBar = {};
    stResBar.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    stResBar.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    stResBar.Transition.pResource = pDst->pResource;
    stResBar.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    stResBar.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    stResBar.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

     Interfaces.CopyCommandList->ResourceBarrier(1, &stResBar);
}

void FD3D12CommandList::Close()
{
    if (Interfaces.CopyCommandList)
    {
        GRS_THROW_IF_FAILED(Interfaces.CopyCommandList->Close());
    }
    else
    {
        GRS_THROW_IF_FAILED(Interfaces.GraphicsCommandList->Close());
    }
}

void FD3D12CommandList::Reset(FD3D12CommandAllocator* newCommandAllocator, FD3D12PipelineState* newPipelineState)
{
    if (Interfaces.CopyCommandList)
    {
        GRS_THROW_IF_FAILED(Interfaces.CopyCommandList->Reset(*newCommandAllocator, newPipelineState->GetD3DPipelineState()));
    }
    else
    {
        GRS_THROW_IF_FAILED(Interfaces.GraphicsCommandList->Reset(*newCommandAllocator, newPipelineState->GetD3DPipelineState()));
    }
}
