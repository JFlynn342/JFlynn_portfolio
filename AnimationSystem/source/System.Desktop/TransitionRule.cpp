#include "TransitionRule.h"
namespace Animation {
	TransitionRule::TransitionRule(std::function<bool()> rule) :
		_predicate{rule}
	{
	}

	bool TransitionRule::IsTrue() const {
		return _predicate();
	}

}

