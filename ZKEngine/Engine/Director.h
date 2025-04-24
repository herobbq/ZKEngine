#pragma once
#include <memory>

class FViewport;

class FDirector
{
public:
    FViewport* GetViewport(){return  Viewport.get();}
    void SetViewport(std::shared_ptr<FViewport> viewport){Viewport = viewport;}
protected:
    std::shared_ptr<FViewport> Viewport;
};
