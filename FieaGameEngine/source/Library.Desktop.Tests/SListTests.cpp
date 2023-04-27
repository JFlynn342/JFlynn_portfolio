#include "SList.h"
#include "Foo.h"
#include "CppUnitTest.h"
#ifndef UNREFERENCED_LOCAL
#define UNREFERENCED_LOCAL(L)(L)
#endif // !UNREFERENCED_LOCAL
using namespace fge;
using namespace UnitTests;
using namespace std::string_literals;
namespace Microsoft::VisualStudio::CppUnitTestFramework {
	template<>
	std::wstring ToString<Foo>(const UnitTests::Foo& f) {

		RETURN_WIDE_STRING(L"Foo: " + ToString(f.Data()));
	}

	template<>
	std::wstring ToString<SList<Foo>::Iterator>(const SList<Foo>::Iterator& it) {
		std::wstring str;
		try {
			str = L"Iterator: "s + ToString(*it);
		}
		catch(std::runtime_error) {
			str = L"end()";
		}
		RETURN_WIDE_STRING(str);
	}

	template<>
	std::wstring ToString<SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator& it) {
		std::wstring str;
		try {
			str = L"ConstIterator: "s + ToString(*it);
		}
		catch (std::runtime_error) {
			str = L"end()";
		}
		RETURN_WIDE_STRING(str);
	}

}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace LibraryDesktopTests
{
	TEST_CLASS(SListTests)
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
			if (_CrtMemDifference(&diffMemState, &_startMemState,
				&endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(Constructor)
		{
			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}
		TEST_METHOD(PushFront)
		{
			SList<Foo> list;
			Foo firstFront = Foo(1);
			Foo secondFront = Foo(2);
			list.PushFront(firstFront);
			Assert::AreEqual(firstFront, list.Front());
			Assert::AreEqual(firstFront, list.Back());
			list.PushFront(secondFront);
			Assert::AreEqual(secondFront, list.Front());
			Assert::AreEqual(firstFront, list.Back());
			list.Clear();
		}
		TEST_METHOD(PopFront)
		{
			SList<Foo> list;
			Foo firstFront = Foo(1);
			Foo secondFront = Foo(2);
			list.PushFront(firstFront);
			list.PushFront(secondFront);
			list.PopFront();
			Assert::AreEqual(firstFront, list.Front());
			Assert::AreEqual(size_t(1), list.Size());
			list.PopFront();
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {list.PopFront(); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
			
		}
		TEST_METHOD(PushBack)
		{
			SList<Foo> list;
			Foo firstBack = Foo(1);
			Foo secondBack = Foo(2);
			list.PushBack(firstBack);
			Assert::AreEqual(firstBack, list.Back());
			Assert::AreEqual(firstBack, list.Front());
			Assert::AreEqual(size_t(1), list.Size());
			list.PushBack(secondBack);
			Assert::AreEqual(secondBack, list.Back());
			Assert::AreEqual(firstBack, list.Front());
			Assert::AreEqual(size_t(2), list.Size());
			list.Clear();
		}
		TEST_METHOD(IsEmpty)
		{
			SList<Foo> list;
			Assert::IsTrue(list.IsEmpty());
			Foo aFoo;
			list.PushFront(aFoo);
			Assert::IsFalse(list.IsEmpty());
			list.PopFront();
			Assert::IsTrue(list.IsEmpty());
		}
		TEST_METHOD(Size) {
			SList<Foo> list;
			for (size_t i = 0; i < 20; i++) {
				Foo aFoo;
				list.PushBack(aFoo);
			}
			Assert::AreEqual(size_t(20), list.Size());
			for (size_t i = 0; i < 10; i++) {
				list.PopFront();
			}
			Assert::AreEqual(size_t(10), list.Size());
			for (size_t i = 0; i < 5; i++) {
				Foo aFoo;
				list.PushFront(aFoo);
			}
			Assert::AreEqual(size_t(15), list.Size());
			list.PopBack();
			Assert::AreEqual(size_t(14), list.Size());
			list.Clear();
		}
		TEST_METHOD(CopyConstructor) 
		{
			SList<Foo> list1;
			Foo Foo1(1);
			Foo Foo2(2);
			list1.PushBack(Foo1);
			list1.PushBack(Foo2);
			SList<Foo> list2(list1);
			Assert::AreEqual(list1.Size(), list2.Size());
			Assert::AreEqual(list1.Front(), list2.Front());
			Assert::AreEqual(list1.Back(), list2.Back());
			list2.PopBack();
			Assert::AreNotEqual(list1.Size(), list2.Size());
			list1.Clear();
			list2.Clear();
		}
		TEST_METHOD(CopyAssignment)
		{
			SList<Foo> list1;
			Foo Foo1(1);
			Foo Foo2(2);
			list1.PushBack(Foo1);
			list1.PushBack(Foo2);
			SList<Foo> list2;
			list2 = list1;
			Assert::AreEqual(list1.Size(), list2.Size());
			Assert::AreEqual(list1.Front(), list2.Front());
			Assert::AreEqual(list1.Back(), list2.Back());
			list2.PopBack();
			Assert::AreNotEqual(list1.Size(), list2.Size());
			list1.Clear();
			list2.Clear();
		}
		TEST_METHOD(Destructor)
		{
			SList<Foo>* listPtr = new SList<Foo>;
			Foo aFoo;
			listPtr->PushFront(aFoo);
			delete listPtr;
		}
		TEST_METHOD(Clear) 
		{
			SList<Foo> list;
			for (size_t i = 0; i < 20; i++) {
				Foo aFoo;
				list.PushBack(aFoo);
			}
			list.Clear();
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}
		TEST_METHOD(PopBack) 
		{
			SList<Foo> list;
			Foo firstBack(1);
			Foo secondBack(2);
			list.PushBack(firstBack);
			list.PushBack(secondBack);
			list.PopBack();			
			Assert::AreEqual(firstBack, list.Back());
			Assert::AreEqual(size_t(1), list.Size());
			list.PopBack();
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {list.PopBack();});
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}
		TEST_METHOD(Iterator)
		{
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::Iterator it = list.begin();
				it++;
				Assert::AreNotEqual(it, list.begin());
				Assert::AreEqual(it, ++list.begin());
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::Iterator it = list.end();
				Assert::ExpectException<std::out_of_range>([&it] {auto& end = *it; UNREFERENCED_LOCAL(end); });
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo> list1(list);
				SList<Foo>::Iterator it = list.begin();
				SList<Foo>::Iterator it1 = list1.begin();
				Assert::AreNotSame(it, it1);
				Assert::AreNotSame(*it, *it1);
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::Iterator it = list.end();
				Assert::ExpectException<std::runtime_error>([&it] {it++; });
				Assert::ExpectException<std::runtime_error>([&it] {++it; });
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::Iterator it = list.begin();
				SList<Foo>::Iterator it1(it);
				Assert::IsFalse(it != it1);
				Assert::IsFalse(++it == it1);
			}

			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo> list1(list);
				SList<Foo>::Iterator it = list.begin();
				SList<Foo>::Iterator it1 = list1.begin();
				Assert::IsTrue(it != it1);
				Assert::IsFalse(it == it1);
			}
		}
		TEST_METHOD(ConstIterator)
		{
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::ConstIterator it = list.cbegin();
				it++;
				Assert::AreNotEqual(it, list.cbegin());
				Assert::AreEqual(it, ++list.cbegin());
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::ConstIterator it = list.cend();
				Assert::ExpectException<std::runtime_error>([&it] {auto& end = *it; UNREFERENCED_LOCAL(end); });
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo> list1(list);
				SList<Foo>::ConstIterator it = list.cbegin();
				SList<Foo>::ConstIterator it1 = list1.cbegin();
				Assert::AreNotSame(it, it1);
				Assert::AreNotSame(*it, *it1);
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::Iterator it = list.begin();
				SList<Foo>::ConstIterator cit(it);
				SList<Foo>::ConstIterator cit1 = list.cbegin();
				Assert::AreEqual(cit, cit1);
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::ConstIterator it = list.cend();
				SList<Foo>::ConstIterator it1(it);
				Assert::ExpectException<std::runtime_error>([&it] {it++; });
				Assert::ExpectException<std::runtime_error>([&it1] {++it1; });
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::ConstIterator it = list.cbegin();
				SList<Foo>::ConstIterator it1(it);
				Assert::IsFalse(it != it1);
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo> list1(list);
				SList<Foo>::ConstIterator it = list.cbegin();
				SList<Foo>::ConstIterator it1 = list1.cbegin();
				Assert::IsTrue(it != it1);
				Assert::IsFalse(it == it1);
			}
		}
		TEST_METHOD(Find)
		{
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				const SList<Foo> list1(list);
				Foo start(0);
				Foo end(19);
				Foo middle(9);
				Foo beyond(21);
				Assert::AreEqual(*list1.Find(start), start);
				Assert::AreEqual(*list1.Find(end), end);
				Assert::AreEqual(*list1.Find(middle), middle);
				Assert::AreEqual(list1.Find(beyond), list1.cend());
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				const SList<Foo> list1(list);
				Foo start(0);
				Foo end(19);
				Foo middle(9);
				Foo beyond(21);

				
				Assert::AreEqual(*list1.Find(start), start);
				Assert::AreEqual(*list1.Find(end), end);
				Assert::AreEqual(*list1.Find(middle), middle);
				Assert::AreEqual(list1.Find(beyond), list1.cend());
			}
		}
		TEST_METHOD(InsertAfter)
		{
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				size_t baseSize = list.Size();
				SList<Foo>::Iterator it = list.begin();
				for (int i = 0; i < 10; ++i) {
					it++;
				}
				Foo insert(154);
				list.InsertAfter(insert, it);
				Assert::AreEqual(baseSize + 1, list.Size());
				Assert::AreEqual(*(++it), insert);
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo> list1(list);
				SList<Foo>::Iterator it = list.begin();
				Assert::ExpectException<std::runtime_error>([&list1, &it] {auto i = list1.InsertAfter(Foo(100), it); UNREFERENCED_LOCAL(i); });
			}
			{
				SList<Foo> list;
				for (int i = 0; i < 20; ++i) {
					Foo f(i);
					list.PushBack(f);
				}
				SList<Foo>::Iterator it = list.begin();
				for (int i = 0; i < 10; i++) {
					it++;
				}
				Foo f(100);
				SList<Foo>::Iterator it1 = list.InsertAfter(f, it);
				Assert::AreEqual(++it, it1);
			}
		}
		TEST_METHOD(Remove)
		{
			SList<Foo> list;
			for (int i = 0; i < 20; ++i) {
				Foo f(i);
				list.PushBack(f);
			}
			size_t baseSize = list.Size();
			Foo start(0);
			Foo end(19);
			Foo middle(9);
			Foo beyond(21);
			list.Remove(start);
			Assert::AreNotEqual(start, list.Front());
			Assert::AreEqual(baseSize - 1, list.Size());
			list.Remove(middle);
			Assert::AreEqual(baseSize - 2, list.Size());
			list.Remove(end);
			Assert::AreNotEqual(end, list.Back());
			Assert::AreEqual(baseSize - 3, list.Size());
			list.Remove(beyond);
			Assert::AreEqual(baseSize - 3, list.Size());
		}
		private:
			inline static _CrtMemState _startMemState;
	};
}
