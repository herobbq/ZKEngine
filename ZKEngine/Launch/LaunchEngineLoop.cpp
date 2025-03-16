#include "LaunchEngineLoop.h"
#include "RHI/DynamicRHI.h"
int FEngineLoop::PreInit()
{
    if(!LoadModule("D3D12"))
        return -1;
    RHIInit();
    return  0;
}
