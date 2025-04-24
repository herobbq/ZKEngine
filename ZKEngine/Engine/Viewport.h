#pragma once
#include<string>

#include "RHI/D3D12Adapter.h"
using namespace std;
class FViewport
{
public:
    virtual ~FViewport()
    {
        
    }

    virtual  void Show() = 0;
    virtual void  ViewPeekMessage() = 0;
    
};
