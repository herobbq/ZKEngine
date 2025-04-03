#include "D3D12CommandList.h"
#include "D3D12Queue.h"
#include "D3D12CommandAllocator.h"
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
