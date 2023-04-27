#pragma once
#include "GameClock.h"
#include "Event.h"

namespace fge {
	/// <summary>
	/// A class that wraps globally shared data
	/// </summary>
	class GameState final {
	public:
		GameState() = default;
		const GameClock& GetClock() const;
		EventQueue& GetQueue();
		GameTime _time;
		/// <summary>
		/// Gets the GameState, creating one if necessary
		/// </summary>
		static GameState& GetWorld();
		/// <summary>
		///	Deletes the instance
		/// </summary>
		static void Cleanup();
		~GameState();
	private:
		inline static GameState* _instance = nullptr;
		GameClock _clock;
		EventQueue _queue;
	};
}
