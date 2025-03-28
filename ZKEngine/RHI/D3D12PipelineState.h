#pragma once
#include "D3D12Adapter.h"

class FD3D12PipelineState : public FD3D12AdapterChild
{
public:
    FD3D12PipelineState(FD3D12Adapter* InParent);
    ~FD3D12PipelineState(){};

    void Create(D3D12_GRAPHICS_PIPELINE_STATE_DESC& Des);

    ID3D12PipelineState* GetD3DPipelineState() { return PipelineState.Get(); }
protected:
    ComPtr<ID3D12PipelineState> PipelineState;
};
