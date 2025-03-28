#include "D3D12PipelineState.h"

FD3D12PipelineState::FD3D12PipelineState(FD3D12Adapter* InParent)
    : FD3D12AdapterChild(InParent)
{
}

void FD3D12PipelineState::Create(D3D12_GRAPHICS_PIPELINE_STATE_DESC& Des)
{
    ParentAdapter->GetD3DDevice()->CreateGraphicsPipelineState(&Des, IID_PPV_ARGS(&PipelineState));
}
