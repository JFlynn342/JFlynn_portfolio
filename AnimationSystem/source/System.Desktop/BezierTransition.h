#pragma once
#include "BlendTransition.h"
#include "Bone.h"
#include "Keyframe.h"
#include "BezierCurve.h"
namespace Animation {
	class BezierTransition final : public BlendTransition {
	public:
		BezierTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to, float duration, uint32_t keyframe, const BezierCurve& curve);
	private:
		void GetBlendedTransform(Library::Bone& bone, DirectX::XMFLOAT4X4& transform) override;
		const BezierCurve _curve;
	};
}