#include "LaunchEngineLoop.h"

#include <iostream>
#include <ostream>

#include "RHI/DynamicRHI.h"
bool GIsRequestingExit  = false;
int FEngineLoop::PreInit()
{
    if(!LoadModule("D3D12"))
        return -1;
    RHIInit();
    return  0;
}

void FEngineLoop::Tick()
{
    std::cout<<"FEngineLoop::Tick()"<<std::endl;
}
