#pragma once
#include "D3D12Adapter.h"

class FD3D12RootSignature : public FD3D12AdapterChild
{
public:
    explicit FD3D12RootSignature(FD3D12Adapter* InParent)
         : FD3D12AdapterChild(InParent)
    {}
    void Init(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& InDesc);
    ID3D12RootSignature* GetRootSignature() const { return RootSignature.Get(); }
protected:
    ComPtr<ID3DBlob> RootSignatureBlob;
    ComPtr<ID3D12RootSignature> RootSignature;
};
