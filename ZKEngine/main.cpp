//-----------------------------------【头文件包含】-----------------------------------
//------------------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN // 从 Windows 头中排除极少使用的资料
#include <windows.h>
#include <tchar.h>//字符串相关的，这里使用的Windows的字符串，东西很乱。
#include <strsafe.h>//字符串相关的
#include <wrl.h>		//添加WTL支持 方便使用COM，就是COM只能指针需要的
#include <dxgi1_6.h>//DXGI的头
#include <DirectXMath.h>//我们涉及的变换矩阵，向量的头
#include <d3d12.h>       //for d3d12
#include <d3dcompiler.h>//D3D 编译相关的
#if defined(_DEBUG)
#include <dxgidebug.h>//DXGI有一个独自的调试，下面还有一个flag相关的
#endif
#include <iostream>
#include <wincodec.h>  
using namespace Microsoft;
using namespace Microsoft::WRL;
using namespace DirectX;
//-----------------------------------???????-----------------------------------
#define WINDOWTITLE L"ZKEngine"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
//------------------------------------------------------------------------------------

//更简洁的向上边界对齐算法 内存管理中常用 请记住
#define GRS_UPPER(A,B) ((UINT)(((A)+((B)-1))&~(B - 1)))
//用于判断函数执行错误的，如果出错了就会引发异常
#define GRS_THROW_IF_FAILED(hr) {HRESULT _hr = (hr);if (FAILED(_hr)){ throw CGRSCOMException(_hr); }}

//-----------------------------------【全局变量部分】-----------------------------------
// 这部分C++基础哦，不懂的话，自己找点资料看明白
//-----------------------------------------------------------------------------------------------
class CGRSCOMException
{
public:
	CGRSCOMException(HRESULT hr) : m_hrError(hr)
	{
	}
	HRESULT Error() const
	{
		return m_hrError;
	}
private:
	const HRESULT m_hrError;
};
//-----------------------------------????????-----------------------------------
float g_posX = 0;
float g_posY = 0;
HINSTANCE g_hInstance = 0;
int g_nCmdShow = 0;
HWND g_hwnd = 0;
//------------------------------------------------------------------------------------



//-----------------------------------【函数声明部分】-----------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void InitWindow();//初始化窗口
void Init();//初始化程序
void UpdateScene();//更新绘制的数据
void DrawScene();//进行绘制操作
void Run();
//------------------------------------------------------------------------------------

void LogMessage(const WCHAR* message) {
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, message, -1, NULL, 0, NULL, NULL);
	char* buffer = new char[size_needed];
    
	WideCharToMultiByte(CP_UTF8, 0, message, -1, buffer, size_needed, NULL, NULL);
    
	std::cout << buffer << std::endl;
    
	delete[] buffer;
}

UINT								nDXGIFactoryFlags = 0U;
ComPtr<IDXGIFactory5>				pIDXGIFactory5;
ComPtr<IDXGIAdapter1>				pIAdapter1;
ComPtr<ID3D12Device4>				pID3D12Device4;
//-----------------------------------?WinMain???-----------------------------------
//Win32?????
//------------------------------------------------------------------------------------
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;

	Init();

	Run();

	return 0;
}
//-----------------------------------【初始化创建窗口】-----------------------------------
// 初始化窗口
//--------------------------------------------------------------------------------------
void InitWindow()
{
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = g_hInstance;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hIcon = nullptr;
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = L"ForTheDreamOfGameDevelop";
	if (!RegisterClassEx(&wndClass))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return;
	}


	g_hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOWTITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, g_hInstance, NULL);

	if (!g_hwnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return;
	}
	//创建DXGI Factory对象
	GRS_THROW_IF_FAILED(CreateDXGIFactory2(nDXGIFactoryFlags, IID_PPV_ARGS(pIDXGIFactory5.GetAddressOf())));
	{
		DXGI_ADAPTER_DESC1 stAdapterDesc = {};//适配器描述的结构，待会获取描述时，用这个结构体来接收
		//利用DXGIFactory来循环遍历你的所有显卡。
		for (UINT nAdapterIndex = 0; DXGI_ERROR_NOT_FOUND != pIDXGIFactory5->EnumAdapters1(nAdapterIndex, &pIAdapter1); ++nAdapterIndex)
		{
			pIAdapter1->GetDesc1(&stAdapterDesc);//从当前正在遍历的显卡中获取显卡的描述信息，用准备好的结构体接收
			LogMessage(stAdapterDesc.Description);
			if (stAdapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{//跳过软件虚拟适配器设备
				continue;
			}
			//检查适配器对D3D支持的兼容级别，这里直接要求支持12.1的能力，注意返回接口的那个参数被置为了nullptr，这样
			//就不会实际创建一个设备了，也不用我们啰嗦的再调用release来释放接口。这也是一个重要的技巧，请记住！
			if (SUCCEEDED(D3D12CreateDevice(pIAdapter1.Get(), D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr)))
			{
				
				break;
			}
		}
		// 创建D3D12.1的设备，这里是真正创建出来设备。
		GRS_THROW_IF_FAILED(D3D12CreateDevice(pIAdapter1.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&pID3D12Device4)));

		TCHAR pszWndTitle[MAX_PATH] = {};
		GRS_THROW_IF_FAILED(pIAdapter1->GetDesc1(&stAdapterDesc));
		::GetWindowText(g_hwnd, pszWndTitle, MAX_PATH);
		StringCchPrintf(pszWndTitle
			, MAX_PATH
			, _T("%s (GPU:%s)")
			, pszWndTitle
			, stAdapterDesc.Description);
		::SetWindowText(g_hwnd, pszWndTitle);
	}

	
	


	MoveWindow(g_hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	ShowWindow(g_hwnd, g_nCmdShow);
	UpdateWindow(g_hwnd);
}


//-----------------------------------【窗口处理函数】-----------------------------------
// 处理外来信息
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		else if (wParam == VK_LEFT)
			g_posX -= 1.0f;
		else if (wParam == VK_RIGHT)
			g_posX += 1.0f;
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
//-----------------------------------【程序初始化】-----------------------------------
// 初始化窗口和数据等
//--------------------------------------------------------------------------------------
void Init()
{
	InitWindow();

	g_posX = 400.0f;
	g_posY = 1.0f;
}



//-----------------------------------【更新绘制的数据】-----------------------------------
// 处理外来信息
//--------------------------------------------------------------------------------------
void UpdateScene()
{
	g_posY += 0.001f;
}
//-----------------------------------【进行绘制】-----------------------------------
// 处理外来信息
//--------------------------------------------------------------------------------------
void DrawScene()
{
	HDC hdc = GetDC(g_hwnd);
	TextOut(hdc, g_posX, g_posY, L"hello", 5);
	ReleaseDC(g_hwnd, hdc);
}

//-----------------------------------【游戏运行函数】-----------------------------------
// 游戏循环框架封装在其中
//--------------------------------------------------------------------------------------
void Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT && g_hwnd != nullptr)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			UpdateScene();
			DrawScene();
		}
	}
}