#include "Foo.h"
#include "CppUnitTest.h"
#ifndef UNREFERENCED_LOCAL
#define UNREFERENCED_LOCAL(L)(L)
#endif // !UNREFERENCED_LOCAL

using namespace UnitTests;
using namespace std::string_literals;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fge;
namespace LibraryDesktopTests
{
	TEST_CLASS(HashTests)
	{
	public:
		TEST_METHOD(String)
		{
			const std::string str = "this is a certified hash brown moment"s;
			const std::string str1(str);
			const std::string str2 = "Jimmy's awesome string";
			size_t hash = DefaultHash<std::string>()(str);
			size_t hash1 = DefaultHash<std::string>()(str1);
			size_t hash2 = DefaultHash<std::string>()(str2);
			Assert::AreEqual(hash, hash1);
			Assert::AreNotEqual(hash, hash2);
		}
		TEST_METHOD(CharPtr)
		{
			DefaultHash<char*> hash;
			char* c = "this is a certified hash brown moment";
			char* c1 = "this is a certified hash brown moment";
			char* c2 = "Jimmy's awesome string";
			size_t hash1 = hash(c);
			size_t hash2 = hash(c1);
			size_t hash3 = hash(c2);
			Assert::AreEqual(hash1, hash2);
			Assert::AreNotEqual(hash1, hash3);
		}
		TEST_METHOD(Foos)
		{
			DefaultHash<Foo> hash;
			Foo f(15);
			Foo f1(f);
			Foo f2(27);
			size_t hash1 = hash(f);
			size_t hash2 = hash(f1);
			size_t hash3 = hash(f2);
			Assert::AreEqual(hash1, hash2);
			Assert::AreNotEqual(hash1, hash3);
		}
	};
}

