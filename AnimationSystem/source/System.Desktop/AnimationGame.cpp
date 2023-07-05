#include "AnimationGame.h"
#include "OrthographicCamera.h"
#include "SamplerStates.h"
#include "AnimationDemo.h"
#include "GameException.h"
#include "Grid.h"
#include "PerspectiveCamera.h"
#include "UtilityWin32.h"
#include "SamplerStates.h"
#include "Texture.h"
#include "Animator.h"
#include "Model.h"
#include "Transition.h"
#include "LinearTransition.h"
using namespace std;
using namespace Library;
namespace Animation {
	
	AnimationGame::AnimationGame(std::function<void* ()> getWindowCallback, std::function<void(SIZE&)> getRenderTargetSizeCallback):
		Game(getWindowCallback, getRenderTargetSizeCallback)
	{
	}
	void AnimationGame::Initialize() {
		SamplerStates::Initialize(Direct3DDevice());
		
		mKeyboard = std::make_shared<KeyboardComponent>(*this);
		mComponents.push_back(mKeyboard);
		mServices.AddService(KeyboardComponent::TypeIdClass(), mKeyboard.get());

		auto camera = std::make_shared<PerspectiveCamera>(*this, 90.f, .75f, 1.0f, 20.0f);
		mComponents.push_back(camera);
		mServices.AddService(Camera::TypeIdClass(), camera.get());
		demo = make_shared<Animator>(*this, camera);
		mComponents.push_back(demo);

		Game::Initialize();

		for (const shared_ptr<Transition>& t : demo->Transitions()) {
			mComponents.push_back(t);
		}

		
		camera->SetPosition(0.0f, 3.0f, 5.0f);
	}
	void AnimationGame::Draw(const Library::GameTime& time)
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView.get(), DirectX::Colors::AliceBlue);
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		Game::Draw(time);
		HRESULT hr = mSwapChain->Present(1, 0);

		// If the device was removed either by a disconnection or a driver upgrade, we must recreate all device resources.
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			HandleDeviceLost();
		}
		else
		{
			ThrowIfFailed(hr, "IDXGISwapChain::Present() failed.");
		}
	}
	void AnimationGame::Update(const Library::GameTime& time) {
		Game::Update(time);
	}
	void AnimationGame::Run() {
		Game::Run();
	}
}
