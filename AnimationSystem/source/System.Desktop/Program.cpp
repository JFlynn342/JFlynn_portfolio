#include "UtilityWin32.h"
#include "AnimationGame.h"

using namespace std::string_literals;
using namespace Library;
using namespace Animation;
using namespace DirectX;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int showCommand)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ThrowIfFailed(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED), "Error initializing COM.");

	current_path(UtilityWin32::ExecutableDirectory());

	const std::wstring windowClassName = L"AnimationSystemClass"s;
	const std::wstring windowTitle = L"Animation System"s;

	const SIZE RenderTargetSize = { 480, 640 };
	HWND windowHandle;
	WNDCLASSEX window;

	UtilityWin32::InitializeWindow(window, windowHandle, instance, windowClassName, windowTitle, RenderTargetSize, showCommand);

	auto getRenderTargetSize = [&RenderTargetSize](SIZE& renderTargetSize)
	{
		renderTargetSize = RenderTargetSize;
	};

	auto getWindow = [&]() -> void*
	{
		return reinterpret_cast<void*>(windowHandle);
	};
	AnimationGame game(getWindow, getRenderTargetSize);
	game.UpdateRenderTargetSize();
	game.Initialize();
	MSG message{ 0 };

	try
	{
		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				game.Run();
			}
		}
	}
	catch (GameException ex)
	{
		MessageBox(windowHandle, ex.whatw().c_str(), windowTitle.c_str(), MB_ABORTRETRYIGNORE);
	}
	game.Shutdown();
	UnregisterClass(windowClassName.c_str(), window.hInstance);
	CoUninitialize();

	return static_cast<int>(message.wParam);
}