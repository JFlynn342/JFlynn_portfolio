#include "Transition.h"

Animation::Transition::Transition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to):
	_player{player}, _start{from}, _end{to}, GameComponent(game) {

}
