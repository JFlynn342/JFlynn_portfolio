#include "Event.h"
#include "CppUnitTest.h"
#include "SubscriberFoo.h"
#include "Foo.h"
#include "Bar.h"
#include <crtdbg.h>
namespace LibraryDesktopTests
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	using namespace std::chrono_literals;
	TEST_CLASS(EventTests)
	{

	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
			Event<Foo>::Initialize();
			Event<Bar>::Initialize();
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
			Event<Foo>::Cleanup();
			Event<Bar>::Cleanup();
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState)) {
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}
		TEST_METHOD(Notify) {
			SubscriberFoo subscriber;
			Event<Foo>::Subscribe(&subscriber);
			Event<Foo>::Update();
			Event<Foo> event(Foo(5));
			event.Deliver();
			Assert::AreEqual(5, subscriber.GetValue());
		}
		TEST_METHOD(Unsubscribe) {
			{
				SubscriberFoo subscriber;
				Event<Foo>::Subscribe(&subscriber);
				Event<Foo>::Update();
				Event<Foo>::Unsubscribe(&subscriber);
				Event<Foo>::Update();
				Event<Foo> event(Foo(5));
				event.Deliver();
				Assert::AreEqual(0, subscriber.GetValue());
			}
			{
				SubscriberFoo subscriber;
				SubscriberFoo subscriber1;
				Event<Foo>::Subscribe(&subscriber);
				Event<Foo>::Subscribe(&subscriber1);
				Event<Foo>::Update();
				Event<Foo>::UnsubscribeAll();
				Event<Foo>::Update();
				Event<Foo> event(Foo(5));
				event.Deliver();
				Assert::AreEqual(0, subscriber.GetValue());
				Assert::AreEqual(0, subscriber1.GetValue());
			}
		}
		TEST_METHOD(RTTI) {
			Event<Foo> f(Foo(0));
			Event<Bar> b(Bar(0));
			Assert::IsTrue(f.Is(Event<Foo>::TypeIdClass()));
			Assert::IsTrue(b.Is(Event<Bar>::TypeIdClass()));
			Assert::IsFalse(f.TypeIdInstance() == b.TypeIdInstance());
		}
		TEST_METHOD(Entry) {
	
			std::chrono::steady_clock::time_point currentTime(0ms);
			std::shared_ptr<EventPublisher> event1 = std::make_shared<Event<Foo>>(Foo(5));
			std::shared_ptr<EventPublisher> event2 = std::make_shared<Event<Foo>>(Foo(6));
			QueueEntry e(event1, currentTime);
			QueueEntry e1(event2, currentTime);
			e1 = e;
			Assert::IsTrue(e == e1);
			Assert::AreEqual(5, e1._event->As<Event<Foo>>()->Message().Data());
		
		}
		TEST_METHOD(Queue) {
			EventQueue queue;
			Assert::IsTrue(queue.IsEmpty());
			Assert::AreEqual(size_t(0), queue.Size());
			SubscriberFoo subscriber;
			GameTime time;
			Event<Foo>::Subscribe(&subscriber);
			Event<Foo>::Update();
			std::shared_ptr<EventPublisher> event1 = std::make_shared<Event<Foo>>(Foo(5));
			std::chrono::steady_clock::time_point currentTime(0ms);
			queue.Enqueue(event1, currentTime);
			queue.Update(time);
			Assert::AreEqual(5, subscriber.GetValue());
			std::shared_ptr<EventPublisher> event2 = std::make_shared<Event<Bar>>(Bar(5));
			queue.Enqueue(event2, currentTime);
			queue.Update(time);
			queue.Clear();
			Assert::IsTrue(queue.IsEmpty());
		}
		TEST_METHOD(Cloning) {
			std::shared_ptr<EventPublisher> event1 = std::make_shared<Event<Foo>>(Foo(5));
			std::shared_ptr<EventPublisher> event2 = event1->Clone();
			Assert::AreEqual(event1->As<Event<Foo>>()->Message().Data(), event2->As<Event<Foo>>()->Message().Data());
		}
		inline static _CrtMemState _startMemState;
	};
}