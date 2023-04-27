#pragma once
#include "Attributed.h"
#include "Factory.h"
#include "GameState.h"
namespace fge {
	/// <summary>
	/// An Attributed-derived generic payload that only notifies ReactionAttributed instances of matching subtype
	/// </summary>
	class EventMessageAttributed final : public Attributed {
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed);
	public:
		EventMessageAttributed();
		static Vector<Signature> Signatures();
		/// <summary>
		/// gets the subtype
		/// </summary>
		int32_t GetSubtype() const;
		/// <summary>
		/// gets the world
		/// </summary>
		GameState& GetWorld() const;
		void SetSubtype(int32_t type);
		void SetWorld(GameState& world);
	private:
		int32_t _subtype = 0;
		GameState* _world = nullptr;
	};
	ConcreteFactory(EventMessageAttributed, Scope);

}