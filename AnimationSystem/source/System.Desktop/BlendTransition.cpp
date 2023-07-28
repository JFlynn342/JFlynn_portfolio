#include "BlendTransition.h"
#include "Model.h"
#include "GameTime.h"
namespace Animation {
	BlendTransition::BlendTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to, float duration, uint32_t keyframe):
		Transition(player, game, from, to), _duration{duration}, _targetKeyframe{keyframe}
	{
		_targetPose.resize(_player->mModel->Bones().size());
		_originPose.resize(_player->mModel->Bones().size());
	}
	bool BlendTransition::Run() {
		if (_player->CurrentClip() == _start && !_active) {
			_player->PauseClip();
			GetPose(_originPose);
			PopulateMapping(_player->mModel->RootNode().get());
			_alpha = 0.0f;
			_active = true;
			return true;
		}
		return false;

	}
	void BlendTransition::Initialize() {
		auto& baseClip = _player->CurrentClip();
		_player->StartClip(_end);
		_player->SetCurrentKeyFrame(_targetKeyframe);
		GetPose(_targetPose);
		_player->StartClip(baseClip);
		GameComponent::Initialize();
	}
	void BlendTransition::Update(const Library::GameTime& time) {
		if (_active) {
			_alpha += (time.ElapsedGameTimeSeconds().count() / _duration);
			if (_alpha >= 1.0f) {
				_player->StartClip(_end);
				_player->SetCurrentKeyFrame(_targetKeyframe);
				_active = false;
				return;
			}
			auto parentNode = _player->mModel->RootNode();


			MoveBone(parentNode.get());
		}
	}
	void BlendTransition::PopulateMapping(Library::SceneNode* baseRoot) {
		Library::Bone* bone = baseRoot->As<Library::Bone>();
		if (bone != nullptr) {
			_poseMapping.insert(std::make_pair(baseRoot, std::make_pair(_originPose[_player->mModel->BoneIndexMapping().at(bone->Name())], _targetPose[_player->mModel->BoneIndexMapping().at(bone->Name())])));
		}
		for (std::shared_ptr<Library::SceneNode> childNode : baseRoot->Children()) {
			PopulateMapping(childNode.get());
		}
	}
	void BlendTransition::MoveBone(Library::SceneNode* node) {
		DirectX::XMFLOAT4X4 newTransform;
		Library::Bone* bone = node->As<Library::Bone>();
		if (bone != nullptr)
		{
			GetBlendedTransform(*bone, newTransform);
		}
		else
		{
			newTransform = node->Transform();
		}

		DirectX::XMMATRIX toRootTransform = XMLoadFloat4x4(&newTransform);
		XMStoreFloat4x4(&(_player->mToRootTransforms[node]), toRootTransform);

		if (bone != nullptr)
		{
			XMStoreFloat4x4(&(_player->mFinalTransforms[bone->Index()]), bone->OffsetTransformMatrix() * toRootTransform * XMLoadFloat4x4(&_player->mInverseRootTransform));
		}

		for (const auto& childNode : node->Children())
		{
			MoveBone(childNode.get());
		}
	}
	void BlendTransition::GetPose(std::vector<DirectX::XMFLOAT4X4>& pose) {
		for (auto& pair : _player->mToRootTransforms) {
			Library::Bone* bone = pair.first->As<Library::Bone>();
			if (bone != nullptr) {
				pose[bone->Index()] = pair.second;
			}
		}
	}
}