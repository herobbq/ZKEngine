#include "D3D12RootSignature.h"

#include "D3D12Util.h"

void FD3D12RootSignature::Init(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& InDesc)
{
    ID3D12Device* Device = GetParentAdapter()->GetD3DDevice();
	
    // Serialize the desc. 
    ComPtr<ID3DBlob> Error;
   GRS_THROW_IF_FAILED(D3D12SerializeVersionedRootSignature(&InDesc
                , &RootSignatureBlob
                , &Error));

    // Create and analyze the root signature.
    GRS_THROW_IF_FAILED(Device->CreateRootSignature(0,
        RootSignatureBlob->GetBufferPointer(),
        RootSignatureBlob->GetBufferSize(),
        IID_PPV_ARGS(&RootSignature)));
} 
