#include "Event.h"
#include <cassert>
namespace fge {
	template<typename T>
	RTTI_DEFINITIONS(Event<T>);
	template<typename T>
	inline Event<T>::Event(const T& payload):
		_payload{payload}
	{

	}
	template<typename T>
	inline std::shared_ptr<EventPublisher> Event<T>::Clone()
	{
		return std::make_shared<Event<T>>(*this);
	}
	template<typename T>
	inline void Event<T>::Update() {
		for (EventSubscriber* add : *_pendingAdds) {
			_subscribers->push_back(add);
		}
		for (EventSubscriber* remove : *_pendingRemoves) {
			_subscribers->Remove(remove);
		}
		_pendingAdds->Clear();
		_pendingRemoves->Clear();
	}
	template<typename T>
	inline void Event<T>::Subscribe(EventSubscriber* sub) {
		assert(_subscribers->Find(sub) == _subscribers->end() && _pendingAdds->Find(sub) == _pendingAdds->end());
		_pendingAdds->push_back(sub);
	}
	template<typename T>
	inline void Event<T>::Unsubscribe(EventSubscriber* unsub) {
		assert(_subscribers->Find(unsub) != _subscribers->end() && _pendingRemoves->Find(unsub) == _pendingRemoves->end());
		_pendingRemoves->push_back(unsub);
	}
	template<typename T>
	inline void Event<T>::UnsubscribeAll() {
		for (EventSubscriber* sub : *_subscribers) {
			Unsubscribe(sub);
		}
	}
	template<typename T>
	inline const T& Event<T>::Message() const {
		return _payload;
	}
	template<typename T>
	inline void Event<T>::Initialize() {
		_subscribers = new Vector<EventSubscriber*>;
		_pendingAdds = new Vector<EventSubscriber*>;
		_pendingRemoves = new Vector<EventSubscriber*>;
	}
	template<typename T>
	inline void Event<T>::Cleanup() {

		delete _subscribers;
		delete _pendingAdds;
		delete _pendingRemoves;
	}
	template<typename T>
	inline void Event<T>::Deliver() {
		for (EventSubscriber* s : *_subscribers) {
			s->Notify(*this);
		}
	}
}