#include "LinearTransition.h"
#include "Model.h"
#include "AnimationClip.h"
#include "Bone.h"
#include "GameTime.h"
#include "Game.h"
using namespace DirectX;
namespace Animation {
	LinearTransition::LinearTransition(Library::AnimationPlayer* player, Library::Game& game,  const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to, float duration, uint32_t keyframe):
		Transition(player, game,  from, to), _duration{ duration }, _targetKeyframe{ keyframe } {
		_targetTransforms.reserve(player->GetModel()->Bones().size());
		_originTransforms.reserve(player->GetModel()->Bones().size());
		for (size_t i = 0; i < player->GetModel()->Bones().size(); ++i) {
			_targetTransforms.push_back(XMFLOAT4X4());
		}
		for(size_t j = 0; j < player->GetModel()->Bones().size(); ++j) {
			_originTransforms.push_back(XMFLOAT4X4());
		}
		to->GetTransforms(0.0f, _targetTransforms);
	}

	bool LinearTransition::Run() {
		if(_player->CurrentClip() == _start) {
			_player->PauseClip();
			_player->CurrentClip()->GetTransforms(0.0f, _originTransforms);
			_alpha = 0.0f;
			_active = true;
			return true;
		}
		return false;
	}

	void LinearTransition::Update(const Library::GameTime& time) {
		if (_active) {
			_alpha += (time.ElapsedGameTimeSeconds().count() / _duration);
			if (_alpha >= 1.0) {
				_player->StartClip(_end);
				_active = false;
				return;
			}
			// this is a bad algorithm
			for (size_t i = 0; i < _player->GetModel()->Bones().size(); ++i) {
				XMFLOAT4X4 newTransform;
				for (size_t j = 0; j < 4; ++j) {
					for (size_t k = 0; k < 4; ++k) {
						newTransform(j, k) = _originTransforms[i](j, k) + ((_targetTransforms[i](j, k) - _originTransforms[i](j, k)) * _alpha);
					}
				}
				_player->mFinalTransforms[i] = newTransform;
			}
			GameComponent::Update(time);
		}
	}

}