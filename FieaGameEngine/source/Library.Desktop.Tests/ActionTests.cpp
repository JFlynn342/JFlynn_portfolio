#include "GameObjectFoo.h"
#include "ActionFoo.h"
#include "CppUnitTest.h"
#pragma warning (push)
#pragma warning(disable:4201)
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)
#include "TableParseHelper.h"
#include <filesystem>

namespace LibraryDesktopTests
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	TEST_CLASS(ActionTests)
	{

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState)) {
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}
		TEST_METHOD(Parse) {
			ScopeWrapper& w = *new ScopeWrapper;
			w.SetScope(*new Scope);
			JsonParseCoordinator coordinator{ w };
			TableParseHelper& h = *new TableParseHelper;
			coordinator.AddHelper(h);
			coordinator.DeserializeObjectFromFile(std::filesystem::absolute(R"(ActionTest.json)").string());
			Scope* s = w.GetScope()->Find("FooObject"s)->As<Scope*>();
			Assert::IsTrue(s->Is(GameObjectFoo::TypeIdClass()));
			GameObjectFoo& foo = *s->As<GameObjectFoo>();
			foo.Update(GameTime());
			Assert::IsTrue(foo.Find("Actions")->As<Scope*>()->Find("SingleFooAction")->As<Scope*>()->As<ActionFoo>()->_called);
			Assert::IsTrue(foo.Find("Actions")->As<Scope*>()->Find("List")->As<Scope*>()->Find("Actions")->As<Scope*>()->Find("ListedFooAction2")->As<Scope*>()->As<ActionFoo>()->_called);
			Assert::IsTrue(foo.Find("Actions")->As<Scope*>()->Find("TrueIf")->As<Scope*>()->Find("Then")->As<Scope*>()->Find("SingleFooAction")->As<Scope*>()->As<ActionFoo>()->_called);
			Assert::IsTrue(foo.Find("Actions")->As<Scope*>()->Find("FalseIf")->As<Scope*>()->Find("Else")->As<Scope*>()->Find("SingleFooAction")->As<Scope*>()->As<ActionFoo>()->_called);
		}
		inline static _CrtMemState _startMemState;
	};
}