#pragma once
#include <functional>
namespace Animation {
	class TransitionRule {
	public:
		TransitionRule(std::function<bool()> rule);
		/// <summary>
		/// checks the rule to see if the predicate is true
		/// </summary>
		/// <returns>the return value of the predicate</returns>
		bool IsTrue() const;
	private:
		/// <summary>
		/// a callback which determines the value of the rule (true/false)
		/// </summary>
		const std::function<bool()> _predicate;
	};
}


