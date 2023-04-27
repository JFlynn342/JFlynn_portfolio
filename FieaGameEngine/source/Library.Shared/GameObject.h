#pragma once
#include "Attributed.h"
#include "GameTime.h"
#include "Factory.h"
namespace fge {
	class GameObject : public Attributed {
		RTTI_DECLARATIONS(GameObject, Attributed);
	public:
		GameObject();
		GameObject(const GameObject&) = default;
		GameObject(GameObject&&) = default;
		GameObject& operator=(const GameObject&) = default;
		GameObject& operator=(GameObject&&) = default;
		virtual ~GameObject() = default;
		/// <summary>
		/// gets the array of signatures that correspond to the prescribed attributes of GameObject
		/// </summary>
		/// <returns>GameObject's prescribed attribute signatures</returns>
		static Vector<Signature> Signatures();
		std::string _name;
		glm::mat4 _transform;
		/// <summary>
		/// updates this GameObject and all of its children
		/// </summary>
		/// <param name="time"></param>
		virtual void Update(const GameTime& time);
	};
	ConcreteFactory(GameObject, Scope)
}


