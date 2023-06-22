#include "Animator.h"
#include "Camera.h"
#include "VertexDeclarations.h"
#include "Game.h"
#include "GameException.h"
#include "Model.h"
#include "Mesh.h"
#include "ProxyModel.h"
#include "SkinnedModelMaterial.h"
#include "Texture2D.h"
#include "AnimationPlayer.h"
#include "AnimationClip.h"
#include "BoneAnimation.h"
#include "Keyframe.h"
#include "StepTransition.h"
#include "LinearTransition.h"
#include <vector>

using namespace Library;
using namespace Rendering;
using namespace gsl;
using namespace std;
using namespace DirectX;
using namespace std::string_literals;

bool NoTransitionsActive(Animation::Animator& animator) {
	for (shared_ptr<Animation::Transition> t : animator.Transitions()) {
		if (t->IsActive()) {
			return false;
		}
	}
	return true;
}

void ModifyContent(Model& model) {
	AnimationClipData TPose;
	TPose.TicksPerSecond = 1.0f;
	TPose.Duration = 0.f;
	TPose.Name = "TPose";
	TPose.BoneAnimations = model.Animations()[0]->BoneAnimations();
	TPose.BoneAnimationsByBone = model.Animations()[0]->BoneAnimationsByBone();
	TPose.KeyframeCount = 1;
	model.Data().Animations.emplace_back(make_shared<AnimationClip>(move(TPose)));
}

namespace Animation {
	Animator::Animator(Library::Game& game, const std::shared_ptr<Library::Camera>& camera):
		AnimationDemo(game, camera)
	{
	}

	void Animator::Initialize()
	{
		auto direct3DDevice = mGame->Direct3DDevice();
		mSkinnedModel = mGame->Content().Load<Model>(L"Models\\RunningSoldier.dae.bin"s);
		ModifyContent(*mSkinnedModel);
		Mesh* mesh = mSkinnedModel->Meshes().at(0).get();
		VertexSkinnedPositionTextureNormal::CreateVertexBuffer(direct3DDevice, *mesh, not_null<ID3D11Buffer**>(mVertexBuffer.put()));
		mesh->CreateIndexBuffer(*direct3DDevice, not_null<ID3D11Buffer**>(mIndexBuffer.put()));
		mIndexCount = narrow<uint32_t>(mesh->Indices().size());

		auto texture = mGame->Content().Load<Texture2D>(L"Textures\\Soldier.png"s);
		mMaterial = make_shared<SkinnedModelMaterial>(*mGame, texture);
		mMaterial->Initialize();

		mAnimationPlayer = make_unique<Library::AnimationPlayer>(*mGame, mSkinnedModel, false);
		mAnimationPlayer->StartClip(mSkinnedModel->Animations().at(0));
		mMaterial->UpdateBoneTransforms(mAnimationPlayer->BoneTransforms());
	   
		//_transitions.push_back(make_shared<StepTransition>(mAnimationPlayer.get(), *mGame, mSkinnedModel->Animations().at(0), mSkinnedModel->Animations().at(1)));
		//_transitions.push_back(make_shared<StepTransition>(mAnimationPlayer.get(), *mGame, mSkinnedModel->Animations().at(1), mSkinnedModel->Animations().at(0)));
		_transitions.push_back(make_shared<LinearTransition>(mAnimationPlayer.get(), *mGame,
			mSkinnedModel->Animations().at(0),
			mSkinnedModel->Animations().at(1),
			2.0f, 0));
		_transitions.push_back(make_shared<LinearTransition>(mAnimationPlayer.get(), *mGame,
			mSkinnedModel->Animations().at(1),
			mSkinnedModel->Animations().at(0),
			2.0f, 1));
		

		for (auto& t : _transitions) {
			t->Initialize();
		}

		mProxyModel = make_unique<ProxyModel>(*mGame, mCamera, "Models\\DirectionalLightProxy.obj.bin"s, 0.5f);
		mProxyModel->Initialize();
		mProxyModel->SetPosition(10.0f, 0.0, 0.0f);
		mProxyModel->ApplyRotation(XMMatrixRotationY(XM_PIDIV2));

		mMaterial->SetLightDirection(mDirectionalLight.DirectionToLight());

		auto updateMaterialFunc = [this]() { mUpdateMaterial = true; };
		mCamera->AddViewMatrixUpdatedCallback(updateMaterialFunc);
		mCamera->AddProjectionMatrixUpdatedCallback(updateMaterialFunc);

		XMStoreFloat4x4(&mWorldMatrix, XMMatrixScaling(0.05f, 0.05f, 0.05f));
	}

	void Animator::Update(const Library::GameTime& time)
	{
		for (const shared_ptr<Transition>& t : _transitions) {

			t->Update(time);
		}
		
		AnimationDemo::Update(time);
		
	}
	const std::vector<std::shared_ptr<Transition>>& Animator::Transitions()
	{
		return _transitions;
	}
	void Animator::Draw(const Library::GameTime& time)
	{
		if (mUpdateMaterial)
		{
			const XMMATRIX worldMatrix = XMLoadFloat4x4(&mWorldMatrix);
			const XMMATRIX wvp = XMMatrixTranspose(worldMatrix * mCamera->ViewProjectionMatrix());
			mMaterial->UpdateTransforms(wvp, XMMatrixTranspose(worldMatrix));
			mUpdateMaterial = false;
		}

		if (mUpdateMaterialBoneTransforms)
		{
			mMaterial->UpdateBoneTransforms(mAnimationPlayer->BoneTransforms());
			mUpdateMaterialBoneTransforms = false;
		}

		mMaterial->DrawIndexed(not_null<ID3D11Buffer*>(mVertexBuffer.get()), not_null<ID3D11Buffer*>(mIndexBuffer.get()), mIndexCount);
		mProxyModel->Draw(time);
	}
}