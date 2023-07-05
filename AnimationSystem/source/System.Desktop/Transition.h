#pragma once
#include "GameComponent.h"
#include "AnimationPlayer.h"
#include "TransitionRule.h"
namespace Animation {
	/// <summary>
	/// a link between two AnimationClips that facilitates changing from one clip to the other
	/// </summary>
	class Transition: public Library::GameComponent {
	public:
		/// <param name="player">the AnimationPlayer to use</param>
		/// <param name="game">the Game that this Transition is a part of</param>
		/// <param name="from">the "origin" clip, the AnimationClip that this Transition exits from</param>
		/// <param name="to">the "target" clip, the AnimationClip that this Transition enters</param>
		Transition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to);
		virtual ~Transition() = default;
		Transition(const Transition&) = delete;
		Transition operator=(Transition& other) = delete;
		Transition(Transition&&) = delete;
		Transition operator=(Transition&&) = delete;
		/// <summary>
		/// Begins execution of the Transition
		/// </summary>
		/// <returns>true if the Transition was successfully run (if the AnimationPlayer was playing the origin clip), otherwise false</returns>
		virtual bool Run() = 0;
		/// <summary>
		/// gets whether the Transition is currently active (if it is currently being updated every frame)
		/// </summary>
		/// <returns>true if active, otherwise false</returns>
		inline bool IsActive() { return _active; };
	protected:
		/// <summary>
		/// the AnimationPlayer being used
		/// </summary>
		Library::AnimationPlayer* _player;
		/// <summary>
		/// the origin clip
		/// </summary>
		std::shared_ptr<Library::AnimationClip> _start;
		/// <summary>
		/// the target clip
		/// </summary>
		std::shared_ptr<Library::AnimationClip> _end;

		bool _active = false;
	};
}


