#include "TableParseHelper.h"
#pragma warning (push)
#pragma warning(disable:4201)
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)
#include "CppUnitTest.h"
#include <filesystem>

namespace LibraryDesktopTests
{

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	using namespace std::string_literals;
	TEST_CLASS(TableParseTests) {
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
		TEST_METHOD(ParseNestedScopes) {
			ScopeWrapper& w = *new ScopeWrapper;
			w.SetScope(*new Scope);
			JsonParseCoordinator coordinator{w};
			TableParseHelper& h = *new TableParseHelper;
			coordinator.AddHelper(h);
			coordinator.DeserializeObjectFromFile(std::filesystem::absolute(R"(ChonkyRaccoon.json)").string());
			Datum& leadsTable = *w.GetScope()->Find("Chonky Raccoon Studios")->As<Scope*>()->Find("Leads");
			Assert::AreEqual("Jonathan Conrad"s, leadsTable.As<Scope*>()->Find("Jonathan")->As<std::string>());
		}
		TEST_METHOD(PrimitiveParse) {
			ScopeWrapper& w = *new ScopeWrapper;
			w.SetScope(*new Scope);
			JsonParseCoordinator coordinator{ w };
			TableParseHelper& h = *new TableParseHelper;
			coordinator.AddHelper(h);
			coordinator.DeserializeObjectFromFile(std::filesystem::absolute(R"(ExtraTableTests.json)").string());
			Scope& root = *w.GetScope()->Find("TableOfThings")->As<Scope*>();
			Assert::AreEqual(70, root.Find("SomeInt")->As<int32_t>());
			Assert::AreEqual(4.5f, root.Find("SomeFloat")->As<float>());
			Assert::AreEqual(glm::to_string(glm::vec4(5.0, 4.7, 3.6, 2.9)), glm::to_string(root.Find("SomeVector")->As<glm::vec4>()));
			Assert::AreEqual(glm::to_string(glm::mat4(glm::vec4(5, 0, 0, 0), glm::vec4(6, 0, 0, 0), glm::vec4(7, 0, 0, 0), glm::vec4(8, 0, 0, 0))), glm::to_string(root.Find("SomeMatrix")->As<glm::mat4>()));
			Assert::AreEqual(3, root.Find("IntArray")->As<int32_t>(2));
			Assert::AreEqual(1.8f, root.Find("FloatArray")->As<float>(2));
			Assert::AreEqual(glm::to_string(glm::vec4(7, 0, 0, 0)), glm::to_string(root.Find("VectorArray")->As<glm::vec4>(2)));
			Assert::AreEqual(glm::to_string(glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(2, 0, 0, 0), glm::vec4(3, 0, 0, 0), glm::vec4(4, 0, 0, 0))), glm::to_string(root.Find("MatrixArray")->As<glm::mat4>(1)));
			Assert::AreEqual("string"s, root.Find("StringArray")->As<std::string>(3));
		}
private:
	inline static _CrtMemState _startMemState;
	};
}