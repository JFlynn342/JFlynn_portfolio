#include "GameObjectFoo.h"
#include "ActionFoo.h"
#include "CppUnitTest.h"
#pragma warning (push)
#pragma warning(disable:4201)
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)
#include "TableParseHelper.h"
#include <filesystem>
#include "EventMessageAttributed.h"
#include "Reaction.h"
#include "ReactionAttributed.h"
#include "Action.h"
namespace Microsoft::VisualStudio::CppUnitTestFramework {
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	template<>
	std::wstring ToString<GameState>(const GameState&) {
		RETURN_WIDE_STRING("GameState");
	}
}
namespace LibraryDesktopTests
{

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	TEST_CLASS(ReactionTests)
	{

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
			Event<EventMessageAttributed>::Initialize();
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
			
			GameState::Cleanup();
			Event<EventMessageAttributed>::Cleanup();
			
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState)) {
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}
		TEST_METHOD(Message) {
			EventMessageAttributed m;
			Assert::AreEqual(0, m.GetSubtype());
			m.SetSubtype(2);
			Assert::AreEqual(2, m.GetSubtype());
			GameState& state = GameState::GetWorld();
			m.SetWorld(state);
			Assert::AreSame(state, m.GetWorld());
		}
		TEST_METHOD(Reaction) {
			ReactionAttributed reaction;
			Event<EventMessageAttributed>::Update();
			EventMessageAttributed message;
			message.AppendAuxiliaryAttribute("ExtraStuff") = 5;
			Event<EventMessageAttributed> event(message);
			event.Deliver();
			Assert::IsNotNull(reaction.Find("ExtraStuff"));
			Assert::AreEqual(5, reaction.Find("ExtraStuff")->As<int32_t>());
		}
		TEST_METHOD(Action) {
			ActionEvent action;
			action.AppendAuxiliaryAttribute("ExtraStuff") = 7;
			GameState& state = GameState::GetWorld();
			ReactionAttributed reaction;
			Event<EventMessageAttributed>::Update();
			GameTime t;
			action.Update(t);
			state.GetQueue().Update(t);
			Assert::IsNotNull(reaction.Find("ExtraStuff"));
			Assert::AreEqual(7, reaction.Find("ExtraStuff")->As<int32_t>());
		}
		TEST_METHOD(State) {
			GameState& state = GameState::GetWorld();
			Assert::IsNotNull(&state);
		}
		TEST_METHOD(Parse) {
			ScopeWrapper& w = *new ScopeWrapper;
			w.SetScope(*new Scope);
			JsonParseCoordinator coordinator{ w };
			TableParseHelper& h = *new TableParseHelper;
			coordinator.AddHelper(h);
			coordinator.DeserializeObjectFromFile(std::filesystem::absolute(R"(ReactionTest.json)").string());
			Event<EventMessageAttributed>::Update();
			const GameTime time;
			Scope* s = w.GetScope()->Find("FooObject"s)->As<Scope*>();
			GameObjectFoo& foo = *s->As<GameObjectFoo>();
			foo.Update(time);
			GameState::GetWorld().GetQueue().Update(time);
			Scope* reaction = foo.Find("Reactions")->As<Scope*>()->Find("Reaction")->As<Scope*>();
			Assert::IsTrue(reaction->Is(ReactionAttributed::TypeIdClass()));
			Assert::AreEqual(13, reaction->Find("ExtraStuff")->As<int32_t>());
		}
		inline static _CrtMemState _startMemState;
	};
}