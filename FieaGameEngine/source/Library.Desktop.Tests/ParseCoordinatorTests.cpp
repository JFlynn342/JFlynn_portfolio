#include "IntegerParseHelper.h"
#include "CppUnitTest.h"
#include <filesystem>


namespace Microsoft::VisualStudio::CppUnitTestFramework {
	using namespace UnitTests;
	template<>
	std::wstring ToString<IntegerWrapper>(const IntegerWrapper&) {

		RETURN_WIDE_STRING(L"IntegerWrapper");
	}
	template<>
	std::wstring ToString<JsonParseCoordinator>(const JsonParseCoordinator&) {

		RETURN_WIDE_STRING(L"JsonParseCoordinator");
	}
}
namespace LibraryDesktopTests
{
	
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	using namespace UnitTests;
	TEST_CLASS(ParseCoordinatorTests) {
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
		TEST_METHOD(Helpers) {
			IntegerWrapper& w = *new IntegerWrapper;
			JsonParseCoordinator c(w);
			Assert::AreSame(w, *dynamic_cast<IntegerWrapper*>(c.GetWrapper()));
			IntegerParseHelper& h = *new IntegerParseHelper;
			IntegerParseHelper& h1 = *new IntegerParseHelper;
			c.AddHelper(h);
			c.AddHelper(h1);
			c.RemoveHelper(h1);
			c.RemoveHelper(h);
		}
		TEST_METHOD(IntegerParse) {
			{
				IntegerWrapper& w = *new IntegerWrapper;
				JsonParseCoordinator c(w);
				IntegerParseHelper& h = *new IntegerParseHelper;
				c.AddHelper(h);
				std::string input = R"({ "Integer" : 10 })";
				c.DeserializeObject(input);
				Assert::AreEqual(10, w._data);
			}
			{
				IntegerWrapper& w = *new IntegerWrapper;
				JsonParseCoordinator c(w);
				IntegerParseHelper& h = *new IntegerParseHelper;
				c.AddHelper(h);
				std::filesystem::path path = std::filesystem::absolute(R"(IntegerTest.json)");
				std::string input = std::filesystem::absolute(path).string();
				c.DeserializeObjectFromFile(input);
				Assert::AreEqual(10, w._data);
			}
		}
		TEST_METHOD(Depth) {
			IntegerWrapper& w = *new IntegerWrapper;
			JsonParseCoordinator c(w);
			Assert::AreSame(c, *w.GetJsonParseCoordinator());
			Assert::AreEqual(size_t(0), c.GetWrapper()->Depth());
		}
		TEST_METHOD(Clone) {
			{
				IntegerWrapper& w = *new IntegerWrapper;
				JsonParseCoordinator c(w);
				c.AddHelper(*new IntegerParseHelper);
				std::shared_ptr<JsonParseCoordinator> c1 = c.Clone();
				Assert::IsNotNull(c1->GetWrapper());
			}
		}
		TEST_METHOD(Move) {
			{
				IntegerWrapper& w = *new IntegerWrapper;
				JsonParseCoordinator c(w);
				c.AddHelper(*new IntegerParseHelper);
				JsonParseCoordinator c1(std::move(c));
				Assert::IsNotNull(c1.GetWrapper());
			}
			{
				IntegerWrapper& w = *new IntegerWrapper;
				JsonParseCoordinator c(w);
				c.AddHelper(*new IntegerParseHelper);
				JsonParseCoordinator c1;
				c1 = std::move(c);
				Assert::IsNotNull(c1.GetWrapper());
			}
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}