#pragma once
#include "AnimationDemo.h"
#include "Transition.h"
#include "StateMachine.h"
namespace Animation{
	class Animator final: public Rendering::AnimationDemo {
	public:
		Animator(Library::Game& game, const std::shared_ptr<Library::Camera>& camera);
		void Initialize() override;
		void Update(const Library::GameTime&) override;
		void Draw(const Library::GameTime& time) override;
		const StateMachine& GetStateMachine();
	private:
		std::shared_ptr<StateMachine> _stateMachine;
	};
}


