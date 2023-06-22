#include "StepTransition.h"

namespace Animation {
	StepTransition::StepTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to) :
		Transition(player, game, from, to) {
	}
	bool StepTransition::Run() {
		if (_player->CurrentClip() == _start) {
			_player->StartClip(_end);
			return true;
		}
		return false;
	}
}