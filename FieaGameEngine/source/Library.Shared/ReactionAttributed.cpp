#include "ReactionAttributed.h"
#include "EventMessageAttributed.h"
namespace fge {
	RTTI_DEFINITIONS(ReactionAttributed);

	ReactionAttributed::ReactionAttributed():
	Reaction(ReactionAttributed::TypeIdClass()) {
		Event<EventMessageAttributed>::Subscribe(this);
	}
	void ReactionAttributed::Notify(EventPublisher& event)
	{
		assert(event.Is(Event<EventMessageAttributed>::TypeIdClass()));
		const EventMessageAttributed& message = reinterpret_cast<Event<EventMessageAttributed>*>(&event)->Message();

		if (message.GetSubtype() == _subtype) {
			for (size_t i = message.GetFirstAuxiliaryAttribute().first; i <= message.GetLastAuxiliaryAttribute().first; ++i) {
				auto& [name, datum] = *message.GetAllAttributes()[i];
				AppendAuxiliaryAttribute(name) = datum;
			}
		}
		
	}
	Vector<Signature> ReactionAttributed::Signatures()
	{
		return Vector<Signature>{
			Signature("Subtype", Datum::DatumType::Integer, 1, offsetof(ReactionAttributed, _subtype))
		};
	}
}
