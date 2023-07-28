#pragma once
#include "BlendTransition.h"
#include "Keyframe.h"
#include "Bone.h"
namespace Animation {
	/// <summary>
	/// a Transition that blends between the origin and target bone transforms at a constant rate
	/// </summary>
	class LinearTransition : public BlendTransition {
	public:
		/// <param name="player">the AnimationPlayer to use</param>
		/// <param name="game">the Game that this Transition is a part of</param>
		/// <param name="from">the "origin" clip, the AnimationClip that this Transition exits from</param>
		/// <param name="to">the "target" clip, the AnimationClip that this Transition enters</param>
		/// <param name="duration">the duration of the blend in seconds</param>
		/// <param name="keyframe">the keyframe on the target clip to blend to</param>
		LinearTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to, float duration, uint32_t keyframe);
	private:
		/// <summary>
		/// gets the transform for a bone at a specified point in the blend
		/// </summary>
		/// <param name="bone">the bone to get the transform for</param>
		/// <param name="transform">output parameter that will contain the transform</param>
		void GetBlendedTransform(Library::Bone& bone, DirectX::XMFLOAT4X4& transform) override;
	};
}


