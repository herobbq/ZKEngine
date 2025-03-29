#pragma once
#define WIN32_LEAN_AND_MEAN // 从 Windows 头中排除极少使用的资料
#include <windows.h>
typedef unsigned char  uint8;
typedef unsigned int  uint32;
#define MAX_uint8		((uint8)	0xff)
#include"d3d12.h"
class CGRSCOMException
{
public:
    CGRSCOMException(HRESULT hr) : m_hrError(hr)
    {
    }
    HRESULT Error() const
    {
        return m_hrError;
    }
private:
    const HRESULT m_hrError;
};
//用于判断函数执行错误的，如果出错了就会引发异常
#define GRS_THROW_IF_FAILED(hr) {HRESULT _hr = (hr);if (FAILED(_hr)){ throw CGRSCOMException(_hr); }}

enum class ERHIDescriptorHeapType : uint8
{
    Standard,
    Sampler,
    RenderTarget,
    DepthStencil,
    Count,
    Invalid = MAX_uint8
};
enum class ED3D12DescriptorHeapFlags : uint8
{
    None       = 0,
    GpuVisible = 1 << 0,
    Poolable   = 1 << 1,
};
template<typename Enum>
constexpr bool EnumHasAnyFlags(Enum Flags, Enum Contains)
{
    using UnderlyingType = __underlying_type(Enum);
    return ((UnderlyingType)Flags & (UnderlyingType)Contains) != 0;
}

