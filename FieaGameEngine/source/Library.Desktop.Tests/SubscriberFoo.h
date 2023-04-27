#pragma once
#include "Event.h"
namespace UnitTests {
	using namespace fge;
	class SubscriberFoo final : public EventSubscriber {
	public:
		void Notify(EventPublisher& event) override;
		int32_t GetValue() const;
	private:
		int32_t _value = 0;
	};
}