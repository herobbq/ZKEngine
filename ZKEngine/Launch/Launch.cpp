#include <iostream>
#include  "LaunchEngineLoop.h"

FEngineLoop GEngineLoop;
int EnginePreInit()
{
    std::cout<<"EnginePreInit"<<std::endl;
    return GEngineLoop.PreInit();
}