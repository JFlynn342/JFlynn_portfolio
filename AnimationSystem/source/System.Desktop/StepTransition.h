#pragma once
#include "Transition.h"
namespace Animation {
	/// <summary>
	/// A Transition that swaps from the origin clip to the target clip instantaneously
	/// </summary>
	class StepTransition final : public Transition {
	public:
		/// <param name="player">the AnimationPlayer to use</param>
		/// <param name="game">the Game that this Transition is a part of</param>
		/// <param name="from">the "origin" clip, the AnimationClip that this Transition exits from</param>
		/// <param name="to">the "target" clip, the AnimationClip that this Transition enters</param>
		StepTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to);
		/// <summary>
		/// Begins execution of the Transition
		/// </summary>
		/// <returns>true if the Transition was successfully run (if the AnimationPlayer was playing the origin clip), otherwise false</returns>
		bool Run()  override;
	};
}


