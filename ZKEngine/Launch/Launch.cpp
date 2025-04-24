#include <iostream>
#include  "LaunchEngineLoop.h"

FEngineLoop GEngineLoop;
int EnginePreInit()
{
    return GEngineLoop.PreInit();
}