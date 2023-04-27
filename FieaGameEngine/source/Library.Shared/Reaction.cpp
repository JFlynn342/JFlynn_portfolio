#include "Reaction.h"
#include "GameState.h"
namespace fge {
	RTTI_DEFINITIONS(Reaction);
	void Reaction::Notify(EventPublisher&)
	{
		GameTime time;
		time.SetCurrentTime(GameState::GetWorld().GetClock().CurrentTime());
		Update(time);
	}
	Reaction::Reaction(RTTI::IdType id) :
		ActionList(id) {
		
	}
}
