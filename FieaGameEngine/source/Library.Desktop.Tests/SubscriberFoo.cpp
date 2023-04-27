#include "SubscriberFoo.h"
#include "Foo.h"
namespace UnitTests {
	using namespace fge;

	void SubscriberFoo::Notify(EventPublisher& event) {
		if (event.Is(Event<Foo>::TypeIdClass())) {
			_value = event.As<Event<Foo>>()->Message().Data();
		}
	}

	int32_t SubscriberFoo::GetValue() const
	{
		return _value;
	}

}