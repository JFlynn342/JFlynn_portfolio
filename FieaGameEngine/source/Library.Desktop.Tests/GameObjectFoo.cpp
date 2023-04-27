#include "GameObjectFoo.h"
namespace UnitTests {
	using namespace fge;
	RTTI_DEFINITIONS(GameObjectFoo);
	GameObjectFoo::GameObjectFoo(){
		
	}
	void GameObjectFoo::Update(const GameTime& time) {
		time;
		++_value;
		GameObject::Update(time);
	}
	Vector<Signature> GameObjectFoo::Signatures()
	{
		return Vector<Signature>{
			Signature("Value", Datum::DatumType::Integer, 1, offsetof(GameObjectFoo, _value))
		};
	}
}

