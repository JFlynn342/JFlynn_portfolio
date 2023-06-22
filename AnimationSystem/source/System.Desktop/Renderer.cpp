#include "Renderer.h"
#include "OrthographicCamera.h"
#include "SamplerStates.h"
namespace Animation {
	void Renderer::Initialize() {
		Library::SamplerStates::Initialize(Direct3DDevice());

		auto camera = std::make_shared<Library::OrthographicCamera>(
			*this,
			static_cast<float>(mRenderTargetSize.cx),
			static_cast<float>(mRenderTargetSize.cy),
			-20.0f,
			20.0f);
		mComponents.push_back(camera);
		mServices.AddService(Library::Camera::TypeIdClass(), camera.get());

		Game::Initialize();

		camera->SetPosition(0.0f, 0.0f, 2.5f);
	}
}