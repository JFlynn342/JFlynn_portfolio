#include "AnimationDemo.h"
#include "Camera.h"
#include "Game.h"
#include "UtilityWin32.h"
using namespace std::string_literals;
using namespace Library;
using namespace Rendering;
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int showCommand)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ThrowIfFailed(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED), "Error initializing COM.");

	current_path(UtilityWin32::ExecutableDirectory());

	const std::wstring windowClassName = L"FlappyBirdClass"s;
	const std::wstring windowTitle = L"Flappy Bird"s;

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

	Game game(getWindow, getRenderTargetSize);
	game.Initialize();
	
}
