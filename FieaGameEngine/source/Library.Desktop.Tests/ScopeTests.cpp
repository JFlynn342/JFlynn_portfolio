#include "Scope.h"
#include "CppUnitTest.h"
#include "StringConversions.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework {
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	template<>
	std::wstring ToString<Datum>(const Datum&) {

		RETURN_WIDE_STRING(L"Datum");
	}
	template<>
	std::wstring ToString<Scope>(const Scope&) {
		RETURN_WIDE_STRING("Scope");
	}
}

namespace LibraryDesktopTests
{

	
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	TEST_CLASS(ScopeTests)
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
		TEST_METHOD(CreateAndDestroy) {
			Scope s;
		}
		TEST_METHOD(Append) {
			{
				Scope s;
				s.Append("someDatum");
				Datum* d = s.Find("someDatum");
				Datum& d1 = s["someOtherDatum"];
				Assert::AreSame(*d, s[0]);
				Assert::AreSame(d1, s[1]);
				d->SetType(Datum::DatumType::Integer);
				d->Resize(1);
				Assert::IsNotNull(d);
				Assert::IsNotNull(s.Find("someOtherDatum"));
				d->Set(5);
				Assert::AreEqual(5, d->As<int32_t>());
			}
		}
		TEST_METHOD(AppendScope) {

			{
				Scope s;
				Scope& s1 = s.AppendScope("childScope");
				Assert::IsNotNull(s.Find("childScope"));
				Datum& d = s1.Append("someDatum");
				Scope& s2 = s.AppendScope("childScope");
				Assert::AreSame(*s1.GetParent(), s);
				Assert::IsNotNull(s.FindContainedScope(s2).first);
				Assert::AreEqual(s2, s[0][1]);
				Assert::IsNull(s.Find("someDatum"));
				Assert::IsNotNull(s1.Find("someDatum"));
				Assert::AreSame(d, *s1.Find("someDatum"));
			}
			{
				Scope s;
				const Scope& s1 = s.AppendScope("childScope");
				Assert::IsNotNull(s.Find("childScope"));
				Assert::AreSame(*s1.GetParent(), s);
			}
		}
		TEST_METHOD(Search) {
			{
				Scope s;
				Scope& s1 = s.AppendScope("childScope");
				s.Append("someDatum") = 3;
				Assert::IsNotNull(s1.Search("someDatum"));
			}
			{
				Scope s;
				Scope& s1 = s.AppendScope("childScope");
				const Scope* s2 = s.Clone();
				Assert::IsNotNull(s2);
				const Scope& s3 = *s2->Find("childScope")->As<Scope*>(0);
				Assert::AreEqual(s2->operator[](0), *s2->FindContainedScope(s3).first);
				Assert::IsNotNull(s2->FindContainedScope(s3).first);
				s.Append("someDatum") = 3;
				Scope** out = new Scope*;
				Assert::IsNotNull(s1.Search("someDatum", out));
				Assert::IsNull(s3.Search("someDatum"));
				Assert::IsNotNull(*out);
				Assert::AreSame(s, **out);
				delete s2;
				delete out;
			}
		}
		TEST_METHOD(Comparison) {
			Scope s;
			Scope s1;
			Assert::IsTrue(s == s1);
			Assert::IsFalse(s != s1);
			s.Append("ADatum") = 5;
			Datum& d1 = s1.Append("ADatum") = 5;
			Assert::IsTrue(s == s1);
			Assert::IsFalse(s != s1);
			d1 = 7;
			Assert::IsTrue(s != s1);
			Assert::IsFalse(s == s1);
		}
		TEST_METHOD(Copy) {
			{
				Scope s;
				s.Append("someDatum");
				Scope s1(s);
				Assert::IsNotNull(s1.Find("someDatum"));
				Assert::IsTrue(s == s1);
			}
			{
				Scope s;
				s.Append("someDatum");
				Scope s1;
				s1.Append("someOtherDatum");
				s = s1;
				Assert::IsNull(s.Find("someDatum"));
				Assert::IsTrue(s == s1);
				Assert::IsNotNull(s.Find("someOtherDatum"));
			}
		}
		TEST_METHOD(Adopt) {
			{
				Scope s;
				Scope s1;
				Scope& child = s.AppendScope("childScope");
				s1.Adopt(child, "childScope");
				Assert::IsNotNull(s1.FindContainedScope(child).first);
				Assert::IsNull(s.FindContainedScope(child).first);
			}
		}
		TEST_METHOD(Move) {
			{
				Scope s;
				s.Append("someDatum");
				Scope s1(s);
				Scope s2(std::move(s));
				Assert::IsNotNull(s2.Find("someDatum"));
				Assert::IsTrue(s1 == s2);
			}
			{
				Scope s;
				s.Append("someDatum");
				Scope s1(s);
				Scope s2;
				s2 = std::move(s);
				Assert::IsNotNull(s2.Find("someDatum"));
				Assert::IsTrue(s1 == s2);
			}
			{
				Scope s;
				Scope& child = s.AppendScope("childScope");
				Scope* newChild = new Scope(std::move(child));
				Assert::IsNotNull(s.FindContainedScope(*newChild).first);
			}
			{
				Scope s;
				Scope& s1 = s.AppendScope("child");
				Scope* s2 = new Scope;
				*s2 = std::move(s1);
				Assert::IsNotNull(s.FindContainedScope(*s2).first);
			}
		}
		TEST_METHOD(Orphan) {
			Scope s;
			Scope& child = s.AppendScope("childScope");
			child.Append("someDatum");
			Scope* orphan = s.Orphan(child);
			Assert::IsNull(s.FindContainedScope(child).first);
			Assert::AreSame(child, *orphan);
			Assert::IsNotNull(orphan->Find("someDatum"));
			Assert::IsNull(orphan->Search("childScope"));
			delete orphan;
		}
		inline static _CrtMemState _startMemState;
	};
}