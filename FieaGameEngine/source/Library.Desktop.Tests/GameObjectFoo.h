#pragma once
#include "GameObject.h"
#include "Factory.h"
namespace UnitTests {
	class GameObjectFoo : public fge::GameObject {
		RTTI_DECLARATIONS(GameObjectFoo, GameObject);
	public:
		GameObjectFoo();
		void Update(const GameTime& time) override;
		int32_t _value;
		static Vector<Signature> Signatures();
	};
	ConcreteFactory(GameObjectFoo, Scope)
}

