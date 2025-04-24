#include "Application.h"

#include "Launch/LaunchEngineLoop.h"
#include "Window/WindowDirector.h"
#include "Window/WindowViewPort.h"
extern int EnginePreInit();
int FApplication::run()
{
    EnginePreInit();
    auto&& Director = FWindowDirector::GetInstance();
    if (Director->GetViewport() == nullptr)
    {
        Director->SetViewport(std::shared_ptr<FViewport>(FWindowViewPort::Create("ZKEngine", 1024, 768, false)));
    }
    if (Director->GetViewport() == nullptr)
    {
        return -1;
    }
    auto Viewport = Director->GetViewport();
    Viewport->Show();
    while (!GIsRequestingExit)
    {
        Viewport->ViewPeekMessage();
    }
    return 0;
}

FApplication* FApplication::getInstance()
{
    static FApplication app;
    return &app;
}
