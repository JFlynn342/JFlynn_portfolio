#pragma once
#include "AnimationDemo.h"
#include "Transition.h"
namespace Animation{
	class Animator final: public Rendering::AnimationDemo {
	public:
		Animator(Library::Game& game, const std::shared_ptr<Library::Camera>& camera);
		void Initialize() override;
		void Update(const Library::GameTime&) override;
		const std::vector<std::shared_ptr<Transition>>& Transitions();
		void Draw(const Library::GameTime& time) override;
	private:
		std::vector<std::shared_ptr<Transition>> _transitions;
	};
}


