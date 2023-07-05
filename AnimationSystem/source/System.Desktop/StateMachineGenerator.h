#pragma once
#include "StateMachine.h"
namespace Animation {
	class StateMachineGenerator final {
	public:
		/// <summary>
		/// Creates a new StateMachine given a path to the JSON file
		/// </summary>
		/// <param name="player">the active animation player</param>
		/// <param name="game">the game instance</param>
		/// <param name="file">the name of the JSON file</param>
		/// <returns>a shared pointer to the created StateMachine</returns>
		static std::shared_ptr<StateMachine> CreateStateMachine(Library::AnimationPlayer* player, Library::Game& game, std::string file);
	};
}


