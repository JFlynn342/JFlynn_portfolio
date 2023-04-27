#include "AttributedFoo.h"
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
	
	TEST_CLASS(FactoryTests)
	{
		TEST_CLASS_INITIALIZE(ClassInit) {
			new AttributedFooFactory;
		}
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
		TEST_METHOD(Creation)
		{
			Scope* foo = Factory<Scope>::Create("AttributedFoo");
			Assert::IsTrue(foo->Is(AttributedFoo::TypeIdClass()));
			delete foo;
		}
		TEST_METHOD(Parse) {
			ScopeWrapper& w = *new ScopeWrapper;
			w.SetScope(*new Scope);
			JsonParseCoordinator coordinator{ w };
			TableParseHelper& h = *new TableParseHelper;
			coordinator.AddHelper(h);
			coordinator.DeserializeObject(R"({"Name": "Foo", "Type": "Table", "Class": "AttributedFoo"})");
			Scope& s = *w.GetScope()->Find("Foo")->As<Scope*>();
			Assert::IsTrue(s.Is(AttributedFoo::TypeIdClass()));

		}
		inline static _CrtMemState _startMemState;
	};
}
