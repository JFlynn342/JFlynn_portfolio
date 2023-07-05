#include "StateMachine.h"

namespace Animation {
	void StateMachine::Initialize() {
		for (auto& pair : _states) {
			for (auto& link : pair.second._links) {
				link._transition->Initialize();
			}
		}
	}
	StateMachine::State* StateMachine::CurrentState() const
	{
		return _currentState;
	}
	StateMachine::State* StateMachine::GetState(std::string name)
	{
		return &_states.find(name)->second;
	}
	StateMachine::StateMachine(Library::AnimationPlayer* player, Library::Game& game):
		GameComponent(game), _currentState{nullptr}
	{
		_player = player;
	}
	void StateMachine::LinkStates(State* from, State* to, const std::shared_ptr<Transition>& transition, const TransitionRule& rule)
	{
		from->_links.push_back(StateLink(transition, rule, to));
	}
	void StateMachine::Update(const Library::GameTime&)
	{
		if (_currentState != nullptr) {
			for (const StateLink& link : _currentState->_links) {
				if (link._rule.IsTrue()) {
					link._transition->Run();
					_currentState = nullptr;
				}
			}
		}
		else {
			for (std::pair<const std::string, State>& pair : _states) {
				if (pair.second.IsActive()) {
					_currentState = &pair.second;
				}
			}
		}
		
	}
	void StateMachine::AddState(std::string name, std::shared_ptr<Library::AnimationClip> clip) {
		
		State newState;
		_states.insert(std::make_pair(name, newState));
		if (_states.size() == 1) {
			_currentState = &_states.begin()->second;
		}
	}
	bool StateMachine::State::IsActive() const {
		return _player->CurrentClip() == _clip;
	}
	const std::shared_ptr<Library::AnimationClip> StateMachine::State::GetClip() const
	{
		return _clip;
	}
}