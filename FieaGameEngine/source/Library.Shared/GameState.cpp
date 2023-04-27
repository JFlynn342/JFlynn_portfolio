#include "GameState.h"
namespace fge {
	const GameClock& GameState::GetClock() const
	{
		return _clock;
	}
	EventQueue& GameState::GetQueue()
	{
		return _queue;
	}
	GameState& GameState::GetWorld() {
		if (_instance == nullptr) {
			_instance = new GameState;
		}
		return *_instance;
	}
	void GameState::Cleanup() {
		delete _instance;
		_instance = nullptr;
	}
	GameState::~GameState() {

	}
}

