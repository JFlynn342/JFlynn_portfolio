#pragma once
#include "RTTI.h"
#include "Vector.h"
#include "GameTime.h"
#include <memory>
#include <queue>
#include <mutex>
namespace fge {
	/// <summary>
	/// An abstract base class defining behavior for an object that wants to be notified of an Event
	/// </summary>
	class EventSubscriber {
	public:
		/// <summary>
		/// Notifies this Subscriber that an Event of a type it has subscribed to has fired
		/// </summary>
		/// <param name="event">a reference to the delivered Event</param>
		virtual void Notify(class EventPublisher& event) = 0;
	};

	/// <summary>
	/// A class that defines common behavior for Events
	/// </summary>
	class EventPublisher : public RTTI {
		friend class EventQueue;
		RTTI_DECLARATIONS(EventPublisher, RTTI);
	public:
		EventPublisher() = default;
		EventPublisher(const EventPublisher&) = default;
		EventPublisher& operator=(const EventPublisher&) = default;
		EventPublisher(EventPublisher&&) = default;
		EventPublisher& operator=(EventPublisher&&) = default;
		virtual ~EventPublisher() = default;
		/// <summary>
		/// Gets a boolean indicating whether or not the Event is currently in the EventQueue
		/// </summary>
		/// <returns>true if the EventPublisher instance is currently enqueued, otherwise false</returns>
		bool IsInQueue() const;
		/// <summary>
		/// Notifies all subscribers of this event
		/// </summary>
		virtual void Deliver() = 0;
		/// <summary>
		/// creates an instance of the derived class of this EventPublisher based on this one
		/// </summary>
		/// <returns>a copy of this EventPublisher</returns>
		virtual std::shared_ptr<EventPublisher> Clone() = 0;
		
	private:
		bool _enqueued = false;
	};

	/// <summary>
	/// A templated derived class of EventPublisher that can deliver Events with payload data of its templated type
	/// </summary>
	/// <typeparam name="T">the type of the event data container</typeparam>
	template<typename T>
	class Event final: public EventPublisher {
	public:
		RTTI_DECLARATIONS(Event<T>, EventPublisher);
	public:
		explicit Event(const T& payload);
		Event(const Event&) = default;
		Event& operator=(const Event&) = default;
		Event(Event&&) = default;
		Event& operator=(Event&&) = default;
		~Event() override = default;
		virtual void Deliver() override;
		std::shared_ptr<EventPublisher> Clone() override;
		/// <summary>
		/// Processes all Subscribe/Unsubscribe requests
		/// </summary>
		static void Update();
		/// <summary>
		/// Marks an EventSubscriber for pending add, will be added on next Update() call
		/// </summary>
		/// <param name="sub">the EventSubscriber to register with this Event type</param>
		static void Subscribe(EventSubscriber* sub);
		/// <summary>
		/// Marks an EventSubscriber for pending remove from subscribers list, will be removed on next Update() call
		/// </summary>
		/// <param name="unsub">the EventSubscriber to deregister from this Event type</param>
		static void Unsubscribe(EventSubscriber* unsub);
		/// <summary>
		/// Unsubscribes all current subscribers
		/// </summary>
		static void UnsubscribeAll();
		/// <summary>
		/// accesses the payload data for this Event
		/// </summary>
		/// <returns>the payload of the Event</returns>
		const T& Message() const;
		/// <summary>
		/// initializes static data members
		/// </summary>
		static void Initialize();
		/// <summary>
		/// finalizes static data members
		/// </summary>
		static void Cleanup();
	private:
		T _payload;
		inline static Vector <EventSubscriber*>* _subscribers = nullptr;
		inline static Vector <EventSubscriber*>* _pendingAdds = nullptr;
		inline static Vector <EventSubscriber*>* _pendingRemoves = nullptr;
	};

	/// <summary>
	/// A data structure wrapping data for an enqueued Event
	/// </summary>
	class QueueEntry {
	public:
		QueueEntry(const std::shared_ptr<EventPublisher>& ev, std::chrono::steady_clock::time_point& exp);
		~QueueEntry() = default;
		QueueEntry& operator=(const QueueEntry&);
		/// <summary>
		/// compares two QueueEntries based on expiration time, used to order the queue
		/// </summary>
		/// <param name="other">the QueueEntry to compare with</param>
		/// <returns>true if this QueueEntry's expiration time is earlier than other's, otherwise false</returns>
		bool operator<(const QueueEntry& other) const;
		bool operator==(const QueueEntry& other) const;
		std::shared_ptr<EventPublisher> _event;
		std::chrono::steady_clock::time_point _expiration;
	};

	class EventQueue {
	public:
		EventQueue() = default;
		~EventQueue();
		/// <summary>
		/// Pushes a new QueueEntry into the Queue
		/// </summary>
		/// <param name="event">the EventPublisher instance to create a QueueEntry from</param>
		/// <param name="exp">the expiration time point of the EventPublisher</param>
		void Enqueue(const std::shared_ptr<EventPublisher>& event, std::chrono::steady_clock::time_point& exp);
		/// <summary>
		/// Updates the EventQueue, delivering and removing expired events
		/// </summary>
		/// <param name="time">the GameTime at which this mehod was called</param>
		void Update(const GameTime& time);
		/// <summary>
		/// removes all QueueEntries from the EventQueue
		/// </summary>
		void Clear();
		/// <summary>
		/// Gets whether or not the queue currently has no entries
		/// </summary>
		/// <returns>true if the queue is empty, otherwise false</returns>
		bool IsEmpty() const;
		/// <summary>
		/// gets the current number of entries in the queue
		/// </summary>
		/// <returns>the current size of the queue</returns>
		size_t Size() const;
	private:
		std::priority_queue <QueueEntry , Vector <QueueEntry>, std::less<QueueEntry>> _queue;
		Vector<QueueEntry> _pendingAdds;
		void AsyncDeliver();
		std::mutex _mutex;
	};

}

#include "Event.inl"