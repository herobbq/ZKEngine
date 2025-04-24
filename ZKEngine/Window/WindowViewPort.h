#pragma once
#include "Engine/Viewport.h"
#include <wrl/client.h>

class FWindowViewPort : public  FViewport
{
public:
    static  FViewport* Create(const std::string& ViewName, int width, int height, bool Resizeable);
    void Show() override;
    void ViewPeekMessage() override;
protected:
    bool initWithRect(const std::string& viewName, int width, int height, bool resizable);
protected:
    
    HWND		WindowHanld = nullptr;
};
