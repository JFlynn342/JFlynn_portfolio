#pragma once
#include "Action.h"
#include "Factory.h"
namespace fge {
	class ActionFoo final: public Action {
	public:
		void Update(const GameTime& time) override;
		bool _called = false;
	};
	ConcreteFactory(ActionFoo, Scope);
}