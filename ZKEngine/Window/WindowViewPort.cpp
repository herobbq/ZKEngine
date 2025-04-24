#include "WindowViewPort.h"

#include "RHI/D3D12Adapter.h"

#include <Windows.h>
#include <string>

#include "Launch/LaunchEngineLoop.h"

LPCWSTR ConverStringToWString(const std::string& str)
{
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
    //LPCWSTR lpcwstr = wstr;
    return  wstr;
}


FViewport* FWindowViewPort::Create(const std::string& ViewName, int width, int height, bool Resizeable)
{
    auto&& ret = new FWindowViewPort();
    if (ret && ret->initWithRect(ViewName,width,height,Resizeable))
    {
        return ret;
    }
    delete ret;
    return nullptr;
}

void FWindowViewPort::Show()
{
    ShowWindow(WindowHanld, 1);
    UpdateWindow(WindowHanld);
}

void FWindowViewPort::ViewPeekMessage()
{
    MSG									msg = {};
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}



LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        GIsRequestingExit = true;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
bool FWindowViewPort::initWithRect(const std::string& viewName, int width, int height, bool resizable)
{
    WNDCLASSEX wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_GLOBALCLASS;
    wcex.lpfnWndProc = WndProc1;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//防止无聊的背景重绘
    wcex.lpszClassName = ConverStringToWString(viewName);
    RegisterClassEx(&wcex);

    DWORD dwWndStyle = WS_OVERLAPPED | WS_SYSMENU;
    RECT rtWnd = { 0, 0, width, height };
    AdjustWindowRect(&rtWnd, dwWndStyle, FALSE);

    // 计算窗口居中的屏幕坐标
    INT posX = (GetSystemMetrics(SM_CXSCREEN) - rtWnd.right - rtWnd.left) / 2;
    INT posY = (GetSystemMetrics(SM_CYSCREEN) - rtWnd.bottom - rtWnd.top) / 2;

    WindowHanld = CreateWindowW(ConverStringToWString(viewName)
        , ConverStringToWString("ZKEngine")
        , dwWndStyle //这里会关闭全屏效果。
        , posX
        , posY
        , rtWnd.right - rtWnd.left
        , rtWnd.bottom - rtWnd.top
        , nullptr
        , nullptr
        , GetModuleHandle(NULL)
        , nullptr);

    if (!WindowHanld)
    {
        DWORD error = GetLastError();
        // 根据错误代码处理错误
        return false;
    }
}

