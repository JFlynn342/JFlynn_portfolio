#include "GameObjectFoo.h"
#include "CppUnitTest.h"
#pragma warning (push)
#pragma warning(disable:4201)
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)
#include "TableParseHelper.h"

namespace LibraryDesktopTests
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	TEST_CLASS(GameObjectTests)
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
		
		TEST_METHOD(TransformAndName) {
			GameObjectFoo f;
			f._name = "Foo";
			f._transform = glm::mat4(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);
			Assert::AreEqual("Foo"s, f.Find("Name")->As<std::string>());
			Assert::AreEqual(glm::to_string(glm::mat4(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2)), glm::to_string(f.Find("Transform")->As<glm::mat4>()));
		}
		TEST_METHOD(Update) {
			GameObjectFoo f;
			GameObjectFoo& f1 = *new GameObjectFoo;
			f.Adopt(f1, "Children");
			f.Update(GameTime());
			Assert::AreEqual(1, f._value);
			Assert::AreEqual(1, f1._value);
		}
		TEST_METHOD(Parse) {
			
			ScopeWrapper& w = *new ScopeWrapper;
			w.SetScope(*new Scope);
			JsonParseCoordinator coordinator{ w };
			TableParseHelper& h = *new TableParseHelper;
			coordinator.AddHelper(h);
			coordinator.DeserializeObject(R"({"Name": "Foo", "Type": "Table", "Class": "GameObjectFoo"})");
			Assert::IsTrue(w.GetScope()->Find("Foo")->As<Scope*>()->Is(GameObjectFoo::TypeIdClass()));
		}
		inline static _CrtMemState _startMemState;
	};
}
