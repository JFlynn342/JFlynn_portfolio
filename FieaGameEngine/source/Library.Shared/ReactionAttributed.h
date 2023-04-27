#pragma once
#include "Reaction.h"

namespace fge{
	/// <summary>
	/// A concrete implementation of Reaction that responds to Event<EventMessageAttributed>
	/// </summary>
	class ReactionAttributed final : public Reaction {
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);
	public:
		ReactionAttributed();
		void Notify(EventPublisher& event) override;
		static Vector<Signature> Signatures();
	private:
		int32_t _subtype = 0;
	};
	ConcreteFactory(ReactionAttributed, Scope);
}