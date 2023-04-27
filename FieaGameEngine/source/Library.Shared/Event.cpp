#include "Event.h"
#include <cassert>
#include <thread>
#include <future>

namespace fge {
	RTTI_DEFINITIONS(EventPublisher);


	QueueEntry::QueueEntry(const std::shared_ptr<EventPublisher>& ev, std::chrono::steady_clock::time_point& exp):
		_event{ ev }, _expiration{ exp } {

	}

	QueueEntry& QueueEntry::operator=(const QueueEntry& other)
	{
		_event = other._event;
		_expiration = other._expiration;
		return *this;
	}

	bool QueueEntry::operator<(const QueueEntry& other) const
	{
		return(_expiration < other._expiration);
	}

	bool QueueEntry::operator==(const QueueEntry& other) const {
		return (_event == other._event && _expiration == other._expiration);
	}
	
	void EventQueue::Enqueue(const std::shared_ptr<EventPublisher>& event, std::chrono::steady_clock::time_point& exp) {
		assert(!event->IsInQueue());
		_pendingAdds.push_back(QueueEntry(event, exp));
		event->_enqueued = true;
	}

	void EventQueue::Update(const GameTime& time) {
		for (QueueEntry& pendingEntry : _pendingAdds) {
			_queue.push(std::move(pendingEntry));
		}
		_pendingAdds.Clear();
		Vector<std::future<void>> futures;
		while (!_queue.empty()) {
			if (_queue.top()._expiration <= time.CurrentTime()) {
				std::future<void>&& future = std::async(std::launch::async, [this] {AsyncDeliver(); });
				futures.push_back(std::move(future));
			}
			else break;
		}
		for (std::future<void>& f : futures) {
			f.get();
		}
	}

	void EventQueue::Clear() {
		while (!_queue.empty()) {
			_queue.pop();
		}
	}

	bool EventQueue::IsEmpty() const {
		return _queue.empty();
	}

	size_t EventQueue::Size() const {
		return _queue.size();
	}

	bool EventPublisher::IsInQueue() const {
		return _enqueued;
	}

	EventQueue::~EventQueue() {

	}

	void EventQueue::AsyncDeliver() {
		std::lock_guard<std::mutex> lock(_mutex);
		if (!_queue.empty()) {
			_queue.top()._event->Deliver();
			_queue.pop();
		}
	}
}

