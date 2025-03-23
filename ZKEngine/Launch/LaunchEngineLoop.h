#pragma once

class IEngineLoop
{
public:
    virtual void Tick() = 0;
};

class FEngineLoop : IEngineLoop
{
public:
    int PreInit();
    void Tick() override;
};
extern FEngineLoop GEngineLoop;;
extern bool GIsRequestingExit;