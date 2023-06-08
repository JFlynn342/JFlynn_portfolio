#pragma once
#include "Transition.h"
#include "Keyframe.h"
namespace Animation {
	/// <summary>
	/// a Transition that blends between the origin and target bone transforms at a constant rate
	/// </summary>
	class LinearTransition : public Transition {
	public:
		/// <param name="player">the AnimationPlayer to use</param>
		/// <param name="game">the Game that this Transition is a part of</param>
		/// <param name="from">the "origin" clip, the AnimationClip that this Transition exits from</param>
		/// <param name="to">the "target" clip, the AnimationClip that this Transition enters</param>
		/// <param name="duration">the duration of the blend in seconds</param>
		/// <param name="keyframe">the keyframe on the target clip to blend to</param>
		LinearTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to, float duration, uint32_t keyframe);
		/// <summary>
		/// begins execution of the Transition
		/// </summary>
		/// <returns>true if the Transition was successfully run (if the AnimationPlayer was playing the origin clip), otherwise false</returns>
		bool Run() override;
		/// <summary>
		/// updates the bone transforms if active, called by the active Game instance
		/// </summary>
		/// <param name="time">the GameTime object being updated by the GameClock</param>
		void Update(const Library::GameTime& time) override;
	private:
		/// <summary>
		/// the duration of the blend period in seconds
		/// </summary>
		float _duration;
		/// <summary>
		/// the keyframe of the target animation to blend to
		/// </summary>
		uint32_t _targetKeyframe;
		/// <summary>
		/// the current percentage (0.0-1.0) of the active blend
		/// </summary>
		float _alpha = 0.0f;
		/// <summary>
		/// the bone transforms at the target keyframe
		/// </summary>
		std::vector<DirectX::XMFLOAT4X4> _targetTransforms;
		/// <summary>
		/// the bone transforms of the origin pose
		/// </summary>
		std::vector<DirectX::XMFLOAT4X4> _originTransforms;
	};
}


