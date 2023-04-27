#include "Vector.h"
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
	std::wstring ToString<Foo>(const Foo& f) {

		RETURN_WIDE_STRING(L"Foo: " + ToString(f.Data()));
	}
	template<>
	std::wstring ToString<Vector<Foo>>(const Vector<Foo>& vector) {
		std::wstring str = L"Vector (size: "s + ToString(vector.size()) + L" , Capacity: "s + ToString(vector.Capacity()) + L"): "s;
		for (size_t i = 0; i < vector.size(); ++i) {
			str = str.append(ToString(vector.At(i)) + L" "s);
		}
		RETURN_WIDE_STRING(str);
	}
	template<>
	std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& it) {
		std::wstring str;
		try {
			str = L"Iterator: "s + ToString(*it);
		}
		catch (std::runtime_error) {
			str = L"end()";
		}
		RETURN_WIDE_STRING(str);
	}
	template<>
	std::wstring ToString<Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator& it) {
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
namespace LibraryDesktopTests {
	TEST_CLASS(VectorTests) {
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
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState)){
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
			#endif
		}
		TEST_METHOD(Constructor)
		{
			Vector<Foo> v;
			Assert::AreEqual(size_t(0), v.size());
			Assert::AreEqual(size_t(0), v.Capacity());
		}
		TEST_METHOD(RandomAccess)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Assert::AreEqual(Foo(0), v[0]);
				Assert::AreEqual(Foo(1), v[1]);
				Assert::AreEqual(Foo(2), v[2]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(std::move(f));
				}
				Assert::AreEqual(Foo(0), v[0]);
				Assert::AreEqual(Foo(1), v[1]);
				Assert::AreEqual(Foo(2), v[2]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Assert::AreEqual(Foo(0), v.At(0));
				Assert::AreEqual(Foo(0), v.front());
				Assert::AreEqual(Foo(1), v.At(1));
				Assert::AreEqual(Foo(2), v.At(2));
				Assert::AreEqual(Foo(2), v.back());
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				const Vector v1(v);
				Assert::AreEqual(Foo(0), v1[0]);
				Assert::AreEqual(Foo(0), v1.front());
				Assert::AreEqual(Foo(2), v1.back());
			}
		}
		TEST_METHOD(Reserve)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				Assert::AreEqual(size_t(5), v.Capacity());
				Assert::AreEqual(size_t(0), v.size());
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 6; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Assert::AreEqual(size_t(6), v.size());
				Assert::AreEqual(size_t(6), v.Capacity());
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				v.Reserve(7);
				Assert::AreEqual(size_t(3), v.size());
				Assert::AreEqual(size_t(7), v.Capacity());
				for (size_t i = 0; i < v.size(); i++) {
					Assert::AreEqual(Foo(int32_t(i)), v[i]);
				}
			}
		}
		TEST_METHOD(Shrink)
		{
			Vector<int32_t> v;
			v.Reserve(5);
			for (int32_t i = 0; i < 3; i++) {
				v.push_back(i);
			}
			v.ShrinkToFit();
			Assert::AreEqual(size_t(3), v.Capacity());
			Assert::AreEqual(size_t(3), v.size());
		}
		TEST_METHOD(PopBack)
		{
			Vector<int32_t> v;
			v.Reserve(5);
			for (int32_t i = 0; i < 3; i++) {
				v.push_back(i);
			}
			v.pop_back();
			Assert::AreEqual(size_t(2), v.size());
			Assert::AreEqual(size_t(5), v.Capacity());
			v.Clear();
			v.pop_back();
			Assert::AreEqual(size_t(0), v.size());
		}
		TEST_METHOD(Clear)
		{
			Vector<Foo> v;
			v.Reserve(5);
			for (int32_t i = 0; i < 3; i++) {
				Foo f(i);
				v.push_back(f);
			}
			v.Clear();
			Assert::AreEqual(size_t(0), v.size());
			Assert::IsTrue(v.empty());
			Assert::AreEqual(size_t(5), v.Capacity());
		}
		TEST_METHOD(Copy)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo> v1(v);
				Assert::AreEqual(v.size(), v1.size());
				Assert::AreNotSame(v, v1);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo> v1;
				v1 = v;
				
				Assert::AreEqual(v.size(), v1.size());
				Assert::AreNotSame(v, v1);
				Assert::ExpectException<std::invalid_argument>([&v] {v = v; });
			}
		}
		TEST_METHOD(Move)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo> v1(v);
				Vector<Foo> v2(std::move(v));
				Assert::AreEqual(v1.size(), v2.size());
				Assert::AreNotSame(v1, v2);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo> v1(v);
				Vector<Foo> v2;
				v2 = std::move(v);
				Assert::AreEqual(v1.size(), v2.size());
				Assert::AreNotSame(v1, v2);
			}
		}
		TEST_METHOD(Iterator)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				for (size_t i = 0; i < v.size(); i++) {
					Assert::AreEqual(v[i], *it);
					it++;
				}
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.end();
				Assert::ExpectException<std::out_of_range>([&it] {auto& a = *it; UNREFERENCED_LOCAL(a); });
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				Assert::ExpectException<std::out_of_range>([&it] {--it; });
				Vector<Foo>::Iterator it1 = v.begin();
				Assert::ExpectException<std::out_of_range>([&it1] {it1--; });
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				Assert::ExpectException<std::invalid_argument>([&it] {it = it; });
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				Vector<Foo>::Iterator it1(it);
				Assert::AreEqual(it, it1);
				++it;
				it1++;
				Assert::AreEqual(it, it1);
				++it;
				Assert::AreEqual(*it, it1[1]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				++it;
				++it;
				Vector<Foo>::Iterator it1(it);
				Assert::AreEqual(it, it1);
				--it;
				it1--;
				Assert::AreEqual(it, it1);
				--it;
				Assert::AreEqual(*it, it1[-1]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				Vector<Foo>::Iterator it1(it);
				Assert::IsTrue(it == it1);
				Assert::IsFalse(it != it1);
				++it;
				Assert::IsTrue(it != it1);
				Assert::IsFalse(it == it1);
				Vector<Foo> v1(v);
				Vector<Foo>::Iterator it2 = v1.begin();
				Assert::IsFalse(it2 == it1);
				Assert::IsTrue(it2 != it1);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				it += 2;
				Assert::AreEqual(*it, Foo(2));
				it -= 2;
				Assert::AreEqual(*it, Foo(0));
			}
		}
		TEST_METHOD(ConstIterator)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::ConstIterator it = v.cbegin();
				for (size_t i = 0; i < v.size(); i++) {
					Assert::AreEqual(v[i], *it);
					it++;
				}
				Assert::AreEqual(*v.begin(), *v.cbegin());
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				const Vector v1(v);
				Assert::AreEqual(v1.begin(), v1.cbegin());
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::ConstIterator it = v.cbegin();
				Assert::ExpectException<std::out_of_range>([&it] {--it; });
				Vector<Foo>::ConstIterator it1 = v.cbegin();
				Assert::ExpectException<std::out_of_range>([&it1] {it1--; });
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::ConstIterator it = v.cbegin();
				Vector<Foo>::ConstIterator it1(it);
				Assert::AreEqual(it, it1);
				++it;
				it1++;
				Assert::AreEqual(it, it1);
				++it;
				Assert::AreEqual(*it, it1[1]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::ConstIterator it = v.cbegin();
				Assert::ExpectException<std::invalid_argument>([&it] {it = it; });
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::ConstIterator it = v.cend();
				Assert::ExpectException<std::out_of_range>([&it] {auto& a = *it; UNREFERENCED_LOCAL(a); });
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				const Vector<Foo> v1(v);
				Vector<Foo>::ConstIterator it = v1.begin();
				++it;
				++it;
				Vector<Foo>::ConstIterator it1(it);
				Assert::AreEqual(it, it1);
				--it;
				it1--;
				Assert::AreEqual(it, it1);
				--it;
				Assert::AreEqual(*it, it1[-1]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::ConstIterator it = v.cbegin();
				Vector<Foo>::ConstIterator it1(it);
				Assert::IsTrue(it == it1);
				Assert::IsFalse(it != it1);
				++it;
				Assert::IsTrue(it != it1);
				Assert::IsFalse(it == it1);
				Vector<Foo> v1(v);
				Vector<Foo>::ConstIterator it2 = v1.cbegin();
				Assert::IsFalse(it2 == it1);
				Assert::IsTrue(it2 != it1);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.begin();
				++it;
				Vector<Foo>::ConstIterator it1(it);
				Assert::AreEqual(*it, *it1);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::ConstIterator it = v.cbegin();
				it += 2;
				Assert::AreEqual(*it, Foo(2));
				it -= 2;
				Assert::AreEqual(*it, Foo(0));
			}
		}
		TEST_METHOD(Find)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				Vector<Foo>::Iterator it = v.Find(Foo(0));
				Assert::AreEqual(Foo(0), *it);
				it = v.Find(Foo(1));
				Assert::AreEqual(Foo(1), *it);
				it = v.Find(Foo(2));
				Assert::AreEqual(Foo(2), *it);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				const Vector<Foo> v1(v);
				Vector<Foo>::ConstIterator it = v1.Find(Foo(0));
				Assert::AreEqual(Foo(0), *it);
				it = v1.Find(Foo(1));
				Assert::AreEqual(Foo(1), *it);
				it = v1.Find(Foo(2));
				Assert::AreEqual(Foo(2), *it);
			}
		}
		TEST_METHOD(Remove)
		{
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				v.RemoveAt(0);
				Assert::AreEqual(size_t(2), v.size());
				Assert::AreEqual(size_t(5), v.Capacity());
				Assert::AreEqual(Foo(1), v[0]);
				Assert::AreEqual(Foo(2), v[1]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				v.RemoveAt(1);
				Assert::AreEqual(size_t(2), v.size());
				Assert::AreEqual(size_t(5), v.Capacity());
				Assert::AreEqual(Foo(0), v[0]);
				Assert::AreEqual(Foo(2), v[1]);
			}
			{
				Vector<Foo> v;
				v.Reserve(5);
				for (int32_t i = 0; i < 3; i++) {
					Foo f(i);
					v.push_back(f);
				}
				v.RemoveAt(2);
				Assert::AreEqual(size_t(2), v.size());
				Assert::AreEqual(size_t(5), v.Capacity());
				Assert::AreEqual(Foo(0), v[0]);
				Assert::AreEqual(Foo(1), v[1]);
				Assert::ExpectException<std::out_of_range>([&v] {v.RemoveAt(100); });
			}
		}
	private:
	inline static _CrtMemState _startMemState;
	};
}