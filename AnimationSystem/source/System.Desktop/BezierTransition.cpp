#include "BezierTransition.h"
#include "Model.h"
#include "GameTime.h"
#include "VectorHelper.h"
using namespace DirectX;
namespace Animation {
	BezierTransition::BezierTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to, float duration, uint32_t keyframe, const BezierCurve& curve):
		Transition(player, game, from, to), _duration{ duration }, _targetKeyframe{ keyframe }, _curve{ curve } {
		_targetPose.resize(_player->mModel->Bones().size());
		_originPose.resize(_player->mModel->Bones().size());
	}
	bool BezierTransition::Run() {
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
	void BezierTransition::Initialize() {
		auto& baseClip = _player->CurrentClip();
		_player->StartClip(_end);
		_player->SetCurrentKeyFrame(_targetKeyframe);
		GetPose(_targetPose);
		_player->StartClip(baseClip);
		GameComponent::Initialize();
	}
	void BezierTransition::Update(const Library::GameTime& time) {
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
	void BezierTransition::GetBlendedTransform(Library::Bone& bone, DirectX::XMFLOAT4X4& transform) {
		XMFLOAT4 translation;
		float blendValue = _curve.GetValueAtPosition(_alpha);
		XMStoreFloat4(&translation, XMVectorLerp((XMLoadFloat4x4(&_poseMapping.find(&bone)->second.first)).r[3], XMLoadFloat4x4(&_poseMapping.find(&bone)->second.second).r[3], blendValue));
		XMFLOAT4 scale1;
		XMStoreFloat(&scale1.x, XMVector4Length(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.first).r[0]));
		XMStoreFloat(&scale1.y, XMVector4Length(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.first).r[1]));
		XMStoreFloat(&scale1.z, XMVector4Length(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.first).r[2]));
		scale1.w = 0;
		XMFLOAT4 scale2;
		XMStoreFloat(&scale2.x, XMVector4Length(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.second).r[0]));
		XMStoreFloat(&scale2.y, XMVector4Length(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.second).r[1]));
		XMStoreFloat(&scale2.z, XMVector4Length(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.second).r[2]));
		scale2.w = 0;
		XMFLOAT4 scale;
		XMStoreFloat4(&scale, XMVectorLerp(XMLoadFloat4(&scale1), XMLoadFloat4(&scale2), blendValue));
		XMFLOAT4 w(0.f, 0.f, 0.f, 1.f);
		XMFLOAT4X4 rotationMatrix1;
		XMFLOAT4X4 rotationMatrix2;
		XMStoreFloat4x4(&rotationMatrix1, FXMMATRIX(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.first).r[0] / scale1.x, XMLoadFloat4x4(&_poseMapping.find(&bone)->second.first).r[1] / scale1.y, XMLoadFloat4x4(&_poseMapping.find(&bone)->second.first).r[2] / scale1.z, XMLoadFloat4(&w)));
		XMStoreFloat4x4(&rotationMatrix2, FXMMATRIX(XMLoadFloat4x4(&_poseMapping.find(&bone)->second.second).r[0] / scale2.x, XMLoadFloat4x4(&_poseMapping.find(&bone)->second.second).r[1] / scale2.y, XMLoadFloat4x4(&_poseMapping.find(&bone)->second.second).r[2] / scale2.z, XMLoadFloat4(&w)));
		XMFLOAT4 rotation;
		XMStoreFloat4(&rotation, XMQuaternionSlerp(XMQuaternionRotationMatrix(XMLoadFloat4x4(&rotationMatrix1)), XMQuaternionRotationMatrix(XMLoadFloat4x4(&rotationMatrix2)), blendValue));
		XMFLOAT4 originRot;
		XMStoreFloat4(&originRot, XMLoadFloat4(&Library::Vector4Helper::Zero));

		XMStoreFloat4x4(&transform, XMMatrixAffineTransformation(XMLoadFloat4(&scale), XMLoadFloat4(&originRot), XMLoadFloat4(&rotation), XMLoadFloat4(&translation)));
	}
	void BezierTransition::PopulateMapping(Library::SceneNode* baseRoot) {
		Library::Bone* bone = baseRoot->As<Library::Bone>();
		if (bone != nullptr) {
			_poseMapping.insert(std::make_pair(baseRoot, std::make_pair(_originPose[_player->mModel->BoneIndexMapping().at(bone->Name())], _targetPose[_player->mModel->BoneIndexMapping().at(bone->Name())])));
		}
		for (std::shared_ptr<Library::SceneNode> childNode : baseRoot->Children()) {
			PopulateMapping(childNode.get());
		}
	}
	void BezierTransition::MoveBone(Library::SceneNode* node) {
		XMFLOAT4X4 newTransform;
		Library::Bone* bone = node->As<Library::Bone>();
		if (bone != nullptr)
		{
			GetBlendedTransform(*bone, newTransform);
		}
		else
		{
			newTransform = node->Transform();
		}

		XMMATRIX toRootTransform = XMLoadFloat4x4(&newTransform);
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
	void BezierTransition::GetPose(std::vector<DirectX::XMFLOAT4X4>& pose) {
		for (auto& pair : _player->mToRootTransforms) {
			Library::Bone* bone = pair.first->As<Library::Bone>();
			if (bone != nullptr) {
				pose[bone->Index()] = pair.second;
			}
		}
	}
}


