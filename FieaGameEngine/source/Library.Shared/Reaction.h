#pragma once
#include "Action.h"
#include "Event.h"

namespace fge {
	/// <summary>
	/// An Action that Updates when an event it has subscribed to has been delivered
	/// </summary>
	class Reaction : public ActionList, public EventSubscriber {
		RTTI_DECLARATIONS(Reaction, ActionList);
	public:
		void Notify(EventPublisher& event) override = 0;
	protected:
		Reaction(RTTI::IdType id);
	};
}