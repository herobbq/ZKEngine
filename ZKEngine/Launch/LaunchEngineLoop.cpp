#include "LaunchEngineLoop.h"
#include "RHI/DynamicRHI.h"
int FEngineLoop::PreInit()
{
    RHIInit();
    return  0;
}
