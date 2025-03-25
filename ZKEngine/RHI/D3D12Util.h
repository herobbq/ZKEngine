#pragma once
#include<Windows.h>

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

