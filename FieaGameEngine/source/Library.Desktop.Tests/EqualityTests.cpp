#include "Foo.h"
#include "Bar.h"
#include <string>
#include "DefaultEquality.h"
#include "CppUnitTest.h"
#ifndef UNREFERENCED_LOCAL
#define UNREFERENCED_LOCAL(L)(L)
#endif // !UNREFERENCED_LOCAL
namespace fge {
	template<>
	bool DefaultEquality<UnitTests::Foo>::operator()(const UnitTests::Foo& lhs, const UnitTests::Foo& rhs) const {
		return lhs.Data() == rhs.Data();
	}
	template<>
	bool DefaultEquality<UnitTests::Bar>::operator()(const UnitTests::Bar& lhs, const UnitTests::Bar& rhs) const {
		return (lhs.Data() == rhs.Data());
	}
}

namespace LibraryDesktopTests
{
	using namespace UnitTests;
	using namespace std::string_literals;
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;

	TEST_CLASS(EqualityTests)
	{
	public:
		TEST_METHOD(Primitives)
		{
			{
				const char* c = "Jimmy's awesome string";
				const char* c1 = c;
				const char* c2 = "Jimmy's awesomer string";
				Assert::IsTrue(DefaultEquality<char*>()(c, c1));
				Assert::IsFalse(DefaultEquality<char*>()(c, c2));
			}
			{
				const std::string s = "Jimmy's awesome string"s;
				const std::string s1 = s;
				const std::string s2 = "Jimmy's awesomer string"s;
				Assert::IsTrue(DefaultEquality<std::string>()(s, s1));
				Assert::IsFalse(DefaultEquality<std::string>()(s, s2));
			}
		}
		TEST_METHOD(Foos)
		{
			Foo f(15);
			Foo f1(f);
			Foo f2(27);
			Assert::IsTrue(DefaultEquality<Foo>()(f, f1));
			Assert::IsFalse(DefaultEquality<Foo>()(f, f2));
		}
		TEST_METHOD(Bars)
		{
			Bar b(15);
			Bar b1(b);
			Bar b2(27);
			Assert::IsTrue(DefaultEquality<Bar>()(b, b1));
			Assert::IsFalse(DefaultEquality<Bar>()(b, b2));
		}
		TEST_METHOD(Pairs)
		{
			std::pair<std::string, Foo> p = std::pair<std::string, Foo>("some Foo"s, Foo(16));
			std::pair<std::string, Foo> p1 = p;
			std::pair<std::string, Foo> p2 = std::pair<std::string, Foo>("some other Foo"s, Foo(72));
			Assert::IsTrue(DefaultEquality<std::pair<std::string, Foo>>()(p, p1));
			Assert::IsFalse(DefaultEquality<std::pair<std::string, Foo>>()(p, p2));
		}
	};
}