#include "GameObject.h"
#include "GameTime.h"
#include "Action.h"
namespace fge {
	RTTI_DEFINITIONS(GameObject);
	GameObject::GameObject():
	Attributed(GameObject::TypeIdClass()) {
	}
	Vector<Signature> GameObject::Signatures() {
		return Vector<Signature>{
			Signature("Name", Datum::DatumType::String, 1, offsetof(GameObject, _name)),
			Signature("Transform", Datum::DatumType::Matrix, 1, offsetof(GameObject, _transform)),
			Signature("Children", Datum::DatumType::Table, 0, 0),
			Signature("Actions", Datum::DatumType::Table, 0, 0)
		};
	}
	void GameObject::Update(const GameTime& time) {
		Datum* children = Find("Children");
		if (children != nullptr) {
			for (size_t i = 0; i < children->Size(); ++i) {
				Scope* child = children->As<Scope*>(i);
				assert(child->Is(GameObject::TypeIdClass()));
				reinterpret_cast<GameObject*>(child)->Update(time);
			}
		}
		Datum* actions = Find("Actions");
		if (actions != nullptr) {
			for (size_t i = 0; i < actions->As<Scope*>()->Size(); ++i) {
				Scope* action = actions->As<Scope*>()->operator[](i).As<Scope*>();
				assert(action->Is(Action::TypeIdClass()));
				reinterpret_cast<Action*>(action)->Update(time);
			}
		}
	}
}