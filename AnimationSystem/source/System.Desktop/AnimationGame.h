#pragma once
#include "Game.h"
#include "KeyboardComponent.h"
#include "StepTransition.h"
#include "Animator.h"
namespace Animation {
	class AnimationGame final : public Library::Game {
	public:
		AnimationGame(std::function<void* ()> getWindowCallback, std::function<void(SIZE&)> getRenderTargetSizeCallback);
		void Initialize() override;
		void Draw(const Library::GameTime& time) override;
		void Update(const Library::GameTime& time) override;
		void Run() override;
	private:
		std::shared_ptr<Library::KeyboardComponent> mKeyboard;
		std::shared_ptr<Animator> demo;
	};
}