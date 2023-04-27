
#include "HashMap.h"
#include "Foo.h"
#include "Bar.h"
#include "CppUnitTest.h"
#ifndef UNREFERENCED_LOCAL
#define UNREFERENCED_LOCAL(L)(L)
#endif // !UNREFERENCED_LOCAL




namespace Microsoft::VisualStudio::CppUnitTestFramework {
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	template<>
	std::wstring ToString<Foo>(const UnitTests::Foo& f) {

		RETURN_WIDE_STRING(L"Foo: " + ToString(f.Data()));
	}
	template<>
	std::wstring ToString<Bar>(const UnitTests::Bar& b) {

		RETURN_WIDE_STRING(L"Bar: " + ToString(b.Data()));
	}
	template<>
	std::wstring ToString<HashMap<Bar, Foo>::Iterator>(const HashMap<Bar, Foo>::Iterator& it) {
		std::wstring str;
		try {
			str = L"Iterator: "s + L"(" + ToString((*it).first) + ToString((*it).second) + L")";
		}
		catch (std::out_of_range) {
			str = L"end()";
		}
		RETURN_WIDE_STRING(str);
	}
	template<>
	std::wstring ToString<HashMap<Bar, Foo>::ConstIterator>(const HashMap<Bar, Foo>::ConstIterator& it) {
		std::wstring str;
		try {
			str = L"Iterator: "s + L"(" + ToString((*it).first) + ToString((*it).second) + L")";
		}
		catch (std::out_of_range) {
			str = L"end()";
		}
		RETURN_WIDE_STRING(str);
		
	}
	template<>
	std::wstring ToString<HashMap<Bar, Foo>>(const HashMap<Bar, Foo>& m) {
		m;
		RETURN_WIDE_STRING(L"HashMap");
	}
}

namespace fge {
	size_t DefaultHash<UnitTests::Bar>::operator()(UnitTests::Bar value) const {
		size_t hash = value.Data();
		return hash;
	}

	
	bool DefaultEquality<UnitTests::Bar>::operator()(const UnitTests::Bar& lhs, const UnitTests::Bar& rhs) const {
		return (lhs.Data() == rhs.Data());
	}
	template<typename T2>
	struct DefaultEquality<std::pair<UnitTests::Bar, T2>> final {
		bool operator()(const std::pair<UnitTests::Bar, T2>& lhs, const std::pair<UnitTests::Bar, T2>& rhs) const {
			return DefaultEquality<Bar>()(lhs.first, rhs.first) && DefaultEquality<T2>()(lhs.second, rhs.second);
		}
	};
	
	template<typename T1>
	struct DefaultEquality<std::pair<T1, UnitTests::Bar>> final {
		bool operator()(const std::pair<T1, UnitTests::Bar>& lhs, const std::pair<T1, UnitTests::Bar>& rhs) const {
			return DefaultEquality<T1>()(lhs.first, rhs.first) && DefaultEquality<Bar>()(lhs.second, rhs.second);
		}
	};
	
	template<typename T2>
	struct DefaultEquality<std::pair<const UnitTests::Bar, T2>> final {
		bool operator()(const std::pair<UnitTests::Bar, T2>& lhs, const std::pair<UnitTests::Bar, T2>& rhs) const {
			return DefaultEquality<Bar>()(lhs.first, rhs.first) && DefaultEquality<T2>()(lhs.second, rhs.second);
		}
	};

	template<typename T1>
	struct DefaultEquality<std::pair<T1, const UnitTests::Bar>> final {
		bool operator()(const std::pair<T1, const UnitTests::Bar>& lhs, const std::pair<T1, const UnitTests::Bar>& rhs) const {
			return DefaultEquality<T1>()(lhs.first, rhs.first) && DefaultEquality<const Bar>()(lhs.second, rhs.second);
		}
	};

	



	bool DefaultEquality<UnitTests::Foo>::operator()(const UnitTests::Foo& lhs, const UnitTests::Foo& rhs) const {
		return lhs.Data() == rhs.Data();
	}

}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibraryDesktopTests
{
	TEST_CLASS(HashMapTests)
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
		TEST_METHOD(Constructor)
		{
			HashMap<std::string, Foo> m(5);
			Assert::AreEqual(size_t(0), m.Size());
		}
		TEST_METHOD(Iterator)
		{
			{
				HashMap<Foo, int32_t> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Foo, int32_t>(Foo(i), i));
				}
				HashMap<Foo, int32_t>::Iterator it = m.begin();
				for (; it != m.end(); ++it) {
					Assert::IsNotNull(&*it);
				}
			}
			{
				HashMap<Bar, Foo> m(5);
				m.Insert(std::pair<Bar, Foo>(Bar(2), Foo(2)));
				Assert::AreEqual(Foo(2), (*m.begin()).second);
			}
			{
				HashMap<Bar, Foo> m(5);
				
				Assert::AreEqual(L"end()"s, ToString(m.begin()));
				
			}
			{
				HashMap<Bar, Foo> m(5);
				m.Insert(std::pair<Bar, Foo>(Bar(1), Foo(1)));
				m.Insert(std::pair<Bar, Foo>(Bar(3), Foo(3)));
				HashMap<Bar, Foo>::Iterator it = m.begin();
				++it;
				Assert::AreEqual(Foo(3), (*it).second);
				++it;
				Assert::AreEqual(L"end()"s, ToString(it));
			}
			{
				HashMap<Bar, Foo> m(5);
				m.Insert(std::pair<Bar, Foo>(Bar(1), Foo(1)));
				m.Insert(std::pair<Bar, Foo>(Bar(3), Foo(3)));
				HashMap<Bar, Foo>::Iterator it = m.begin();
				it++;
				Assert::AreEqual(Foo(3), (*it).second);
				Assert::AreEqual(Foo(3), it->second);
				it++;
				Assert::AreEqual(L"end()"s, ToString(it));
			}
			{
				HashMap<Bar, Foo> m(5);
				m.Insert(std::pair<Bar, Foo>(Bar(1), Foo(1)));
				HashMap<Bar, Foo>::Iterator it = m.end();
				Assert::ExpectException<std::out_of_range>([&it] {auto& a = *it; UNREFERENCED_LOCAL(a); });
			}
		}
		TEST_METHOD(ConstIterator)
		{
			{
				HashMap<Foo, int32_t> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Foo, int32_t>(Foo(i), i));
				}
				const HashMap m1(m);
		        HashMap<Foo, int32_t>::ConstIterator it = m1.begin();
				for (; it != m1.end(); ++it) {
					Assert::IsNotNull(&*it);
				}
			}
			{
				HashMap<Bar, Foo> m(5);
				const HashMap<Bar, Foo>* m1 = &m;
				Assert::AreEqual(L"end()"s, ToString(m1->begin()));
				Assert::AreEqual(L"end()"s, ToString(m.cbegin()));
			}
			{
				HashMap<Bar, Foo> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Bar, Foo>(Bar(i), Foo(i)));
				}
				HashMap<Bar, Foo>::Iterator it = m.begin();
				++it;
				++it;
				HashMap<Bar, Foo>::ConstIterator it1(it);
				Assert::AreEqual(Foo(2), (*it1).second);
			}
			{
				HashMap<Bar, Foo> m(5);
				m.Insert(std::pair<Bar, Foo>(Bar(1), Foo(1)));
				m.Insert(std::pair<Bar, Foo>(Bar(3), Foo(3)));
				HashMap<Bar, Foo>::ConstIterator it = m.cbegin();
				++it;
				Assert::AreEqual(Foo(3), (*it).second);
				++it;
				Assert::AreEqual(L"end()"s, ToString(it));
			}
			{
				HashMap<Bar, Foo> m(5);
				m.Insert(std::pair<Bar, Foo>(Bar(1), Foo(1)));
				m.Insert(std::pair<Bar, Foo>(Bar(3), Foo(3)));
				HashMap<Bar, Foo>::ConstIterator it = m.cbegin();
				it++;
				Assert::AreEqual(Foo(3), (*it).second);
				it++;
				Assert::AreEqual(L"end()"s, ToString(it));
			}
			{
				HashMap<Bar, Foo> m(5);
				m.Insert(std::pair<Bar, Foo>(Bar(1), Foo(1)));
				HashMap<Bar, Foo>::ConstIterator it = m.cend();
				Assert::ExpectException<std::out_of_range>([&it] {auto& a = *it; UNREFERENCED_LOCAL(a); });
			}
		}
		TEST_METHOD(Insertion)
		{
			{
				HashMap<std::string, Foo> m(5);
				std::string s = "Hello"s;
				m.Insert(std::pair(s, Foo(6)));
				Assert::IsTrue(m.ContainsKey(s));
				Assert::IsFalse(m.ContainsKey(":)"s));
				Assert::IsTrue(m.Insert(std::pair("Hi Paul"s, Foo(6))).first);
				Assert::AreEqual(size_t(2), m.Size());
				Assert::IsFalse(m.Insert(std::pair(s, Foo(6))).first);
				Assert::AreEqual(size_t(2), m.Size());
			}
			{
				HashMap<Foo, int32_t> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					Assert::IsTrue(m.Insert(std::pair<Foo, int32_t>(Foo(i), i)).first);
					Assert::AreEqual((i + 1) / 5.f, m.GetLoadFactor());
				}
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Foo, int32_t>(Foo(i), i));
					Assert::IsFalse(m.Insert(std::pair<Foo, int32_t>(Foo(i), i)).first);
				}
			}
			{
				HashMap<std::string, Foo> m(5);
				m.Insert(std::move(std::pair("Hello"s, Foo(6))));
				Assert::IsTrue(m.ContainsKey("Hello"s));
				Assert::IsFalse(m.ContainsKey(":)"s));
				Assert::AreEqual(size_t(1), m.Size());
				Assert::IsFalse(m.Insert(std::pair("Hello"s, Foo(6))).first);
				Assert::AreEqual(size_t(1), m.Size());
			}
			{
				HashMap<std::string, Foo> m(5);
				m[":)"s];
				Assert::AreEqual(size_t(1), m.Size());
			}
		}
		TEST_METHOD(Retrieval)
		{
			{
				HashMap<Bar, Foo> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Bar, Foo>(Bar(i), Foo(i)));
				}
				for (int32_t i = 0; i < 5; ++i) {
					Assert::AreEqual(Foo(i), (*m.Find(Bar(i))).second);
					Assert::AreEqual(Foo(i), m.At(Bar(i)));
				}
			}
			{
				HashMap<Bar, Foo> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Bar, Foo>(Bar(i * 5), Foo(i)));
					Assert::AreEqual(Foo(i), (*m.Find(Bar(i * 5))).second);
				}
				
			}
			{
				HashMap<Bar, Foo> m(5);
				
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Bar, Foo>(Bar(i), Foo(i)));
				}
				const HashMap<Bar, Foo>* m1 = &m;
				for (int32_t i = 0; i < 5; ++i) {
					Assert::AreEqual(Foo(i), (*m1->Find(Bar(i))).second);
					Assert::AreEqual(Foo(i), m1->Find(Bar(i))->second);
				}
			}
			{
				HashMap<Bar, Foo> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Bar, Foo>(Bar(i * 5), Foo(i)));
				}
				const HashMap<Bar, Foo>* m1 = &m;
				for (int32_t i = 0; i < 5; ++i) {
					
					Assert::AreEqual(Foo(i), (*m1->Find(Bar(i * 5))).second);
				}
			}
			{
				HashMap<Bar, Foo> m(5);
				
				m.Insert(std::pair<Bar, Foo>(Bar(2), Foo(2)));
				Assert::AreEqual(Foo(2), (*m.Find(Bar(2))).second);
				
			}
			{
				HashMap<Bar, Foo> m(5);

				m.Insert(std::pair<Bar, Foo>(Bar(2), Foo(2)));
				const HashMap<Bar, Foo>* m1 = &m;
				Assert::AreEqual(Foo(2), (*m1->Find(Bar(2))).second);

			}
		}
		TEST_METHOD(Remove)
		{
			{
				HashMap<Bar, Foo> m(5);
				for (int32_t i = 0; i < 5; ++i) {
					m.Insert(std::pair<Bar, Foo>(Bar(i), Foo(i)));
				}
				m.Remove(Bar(17));
				Assert::AreEqual(size_t(5), m.Size());
				for (int32_t i = 0; i < 5; ++i) {
					m.Remove(Bar(i));
					Assert::AreEqual(size_t(4 - i), m.Size());
				}
				
			}
		}
		TEST_METHOD(Clear)
		{
			HashMap<Foo, int32_t> m(5);
			for (int32_t i = 0; i < 5; ++i) {
				m.Insert(std::pair(Foo(i), i));
			}
			m.Clear();
			Assert::AreEqual(size_t(0), m.Size());
		}
		TEST_METHOD(Resize)
		{
			HashMap<Bar, Foo> m(5);
			for (int32_t i = 0; i < 5; ++i) {
				m.Insert(std::pair<Bar, Foo>(Bar(i), Foo(i)));
			}
			m.Resize(5);
			Assert::AreEqual(size_t(5), m.Size());
			m.Resize(7);
			Assert::AreEqual(size_t(5), m.Size());
			m.Resize(3);
			Assert::AreEqual(size_t(5), m.Size());
		}
		TEST_METHOD(Copy)
		{
			HashMap<Bar, Foo> m(5);
			for (int32_t i = 0; i < 5; ++i) {
				m.Insert(std::pair<Bar, Foo>(Bar(i), Foo(i)));
			}
			HashMap<Bar, Foo> m1(m);
			Assert::AreNotSame(m, m1);
		}
	private:
		inline static _CrtMemState _startMemState;
	};
}

