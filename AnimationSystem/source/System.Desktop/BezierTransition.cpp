#include "BezierTransition.h"
#include "Model.h"
#include "GameTime.h"
#include "VectorHelper.h"
using namespace DirectX;
namespace Animation {
	BezierTransition::BezierTransition(Library::AnimationPlayer* player, Library::Game& game, const std::shared_ptr<Library::AnimationClip>& from, const std::shared_ptr<Library::AnimationClip>& to, float duration, uint32_t keyframe, const BezierCurve& curve):
		BlendTransition(player, game, from, to, duration, keyframe), _curve{ curve } {
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

}


