#include "EventMessageAttributed.h"
#include "Reaction.h"
#include "GameState.h"
namespace fge {
	RTTI_DEFINITIONS(EventMessageAttributed);
	EventMessageAttributed::EventMessageAttributed():
	Attributed(EventMessageAttributed::TypeIdClass()) {

	}
	Vector<Signature> EventMessageAttributed::Signatures()
	{
		return Vector<Signature> {
			Signature("Subtype", Datum::DatumType::Integer, 1, offsetof(EventMessageAttributed, _subtype)),
			Signature("World", Datum::DatumType::Table, 1, offsetof(EventMessageAttributed, _world))
		};
	}

	int32_t EventMessageAttributed::GetSubtype() const {
		return _subtype;
	}

	GameState& EventMessageAttributed::GetWorld() const {
		return *_world;
	}

	void EventMessageAttributed::SetSubtype(int32_t type)
	{
		_subtype = type;
	}

	void EventMessageAttributed::SetWorld(GameState& world)
	{
		_world = &world;
	}

}
