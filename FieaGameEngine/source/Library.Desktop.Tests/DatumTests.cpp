
#include "Datum.h"
#include "Foo.h"
#include "Bar.h"
#include "gsl/gsl_util"
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
	std::wstring ToString<RTTI>(const RTTI& r) {
		UNREFERENCED_LOCAL(r);
		RETURN_WIDE_STRING(L"RTTI");
	}
}






namespace LibraryDesktopTests
{
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace fge;
	TEST_CLASS(DatumTests)
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
			{
				// testing default constructor / destructor
				Datum d(3, Datum::DatumType::Integer);
			}
			{
				// testing default constructor / destructor
				Datum d(3, Datum::DatumType::Float);
			}
			{
				// testing default constructor / destructor
				Datum d(3, Datum::DatumType::Vector);
			}
			{
				// testing default constructor / destructor
				Datum d(3, Datum::DatumType::Matrix);
			}
			{
				// testing default constructor / destructor
				Datum d(3, Datum::DatumType::String);
			}
			{
				// testing default constructor / destructor
				Datum d(3, Datum::DatumType::Pointer);
			}
		}
		//TODO: continue Datum refactor into this test
		TEST_METHOD(Resize)
		{
			size_t defaultSize = 3;
			size_t upperSize = 7;
			size_t lowerSize = 1;
			{
				Datum d;
				d.SetType(Datum::DatumType::Integer);
				d.Reserve(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.PushBack(int32_t(1));
				Assert::AreEqual(upperSize, d.Capacity());
				d.ShrinkToFit();
				Assert::AreEqual(lowerSize, d.Capacity());
				Assert::AreEqual(d.Size(), d.Size());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Integer);
				Assert::AreEqual((int32_t)Datum::DatumType::Integer, (int32_t)d.Type());
				d.Resize(defaultSize);
				Assert::AreEqual(defaultSize, d.Capacity());
				d.Resize(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.Resize(lowerSize);
				Assert::AreEqual(lowerSize, d.Capacity());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Float);
				d.Reserve(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.PushBack(float(1));
				Assert::AreEqual(upperSize, d.Capacity());
				d.ShrinkToFit();
				Assert::AreEqual(lowerSize, d.Capacity());
				Assert::AreEqual(d.Size(), d.Size());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Float);
				Assert::AreEqual((int32_t)Datum::DatumType::Float, (int32_t)d.Type());
				d.Resize(defaultSize);
				Assert::AreEqual(defaultSize, d.Capacity());
				d.Resize(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.Resize(lowerSize);
				Assert::AreEqual(lowerSize, d.Capacity());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Vector);
				d.Reserve(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.PushBack(glm::vec4());
				Assert::AreEqual(upperSize, d.Capacity());
				d.ShrinkToFit();
				Assert::AreEqual(lowerSize, d.Capacity());
				Assert::AreEqual(d.Size(), d.Size());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Vector);
				Assert::AreEqual((int32_t)Datum::DatumType::Vector, (int32_t)d.Type());
				d.Resize(defaultSize);
				Assert::AreEqual(defaultSize, d.Capacity());
				d.Resize(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.Resize(lowerSize);
				Assert::AreEqual(lowerSize, d.Capacity());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Matrix);
				d.Reserve(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.PushBack(glm::mat4());
				Assert::AreEqual(upperSize, d.Capacity());
				d.ShrinkToFit();
				Assert::AreEqual(lowerSize, d.Capacity());
				Assert::AreEqual(d.Size(), d.Size());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Matrix);
				Assert::AreEqual((int32_t)Datum::DatumType::Matrix, (int32_t)d.Type());
				d.Resize(defaultSize);
				Assert::AreEqual(defaultSize, d.Capacity());
				d.Resize(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.Resize(lowerSize);
				Assert::AreEqual(lowerSize, d.Capacity());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::String);
				d.Reserve(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.PushBack("Hello"s);
				Assert::AreEqual(upperSize, d.Capacity());
				d.ShrinkToFit();
				Assert::AreEqual(lowerSize, d.Capacity());
				Assert::AreEqual(d.Size(), d.Size());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::String);
				Assert::AreEqual((int32_t)Datum::DatumType::String, (int32_t)d.Type());
				d.Resize(defaultSize);
				Assert::AreEqual(defaultSize, d.Capacity());
				d.Resize(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.Resize(lowerSize);
				Assert::AreEqual(lowerSize, d.Capacity());
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Pointer);
				Assert::AreEqual((int32_t)Datum::DatumType::Pointer, (int32_t)d.Type());
				d.Resize(defaultSize);
				Assert::AreEqual(defaultSize, d.Capacity());
				d.Resize(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.Resize(lowerSize);
				Assert::AreEqual(lowerSize, d.Capacity());
			}
			{
				Datum d;
				Foo* f = new Foo;
				d.SetType(Datum::DatumType::Pointer);
				d.Reserve(upperSize);
				Assert::AreEqual(upperSize, d.Capacity());
				d.PushBack(f);
				Assert::AreEqual(upperSize, d.Capacity());
				d.ShrinkToFit();
				Assert::AreEqual(lowerSize, d.Capacity());
				Assert::AreEqual(d.Size(), d.Size());
				delete f;
			}
		}
		TEST_METHOD(SettingAndGetting)
		{
			size_t defaultSize = 3;
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(int32_t(i), i);
					Assert::AreEqual(int32_t(i), d.As<int32_t>(i));
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(float(i), i);
					Assert::AreEqual(float(i), d.As<float>(i));
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(float(i), 0.f, 0.f, 0.f), i);
					Assert::AreEqual(float(i), d.As<glm::vec4>(i).x);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					glm::mat4 temp = glm::mat4(glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f));
					d.Set(temp, i);
					Assert::AreEqual(float(i), d.As<glm::mat4>(i)[0][0]);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str1(c);
					d.Set(str1, i);
					char c1[10];
					sprintf_s(c1, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str2(c);
					Assert::AreEqual(str2, d.As<std::string>(i));
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo f1;
				Foo f2;
				Foo f3;
				d.Set(&f1, 0);
				Assert::AreSame(*(reinterpret_cast<RTTI*>(&f1)), *(d.As<RTTI*>(0)));
				d.Set(&f2, 1);
				Assert::AreSame(*(reinterpret_cast<RTTI*>(&f2)), *(d.As<RTTI*>(1)));
				d.Set(&f3, 2);
				Assert::AreSame(*(reinterpret_cast<RTTI*>(&f3)), *(d.As<RTTI*>(2)));
			}
			{
				{
					Datum d;
					d = int32_t(6);
					Assert::AreEqual(int32_t(6), d.As<int32_t>(0));
					Assert::AreEqual(int32_t(6), d.Front<int32_t>());
					Assert::AreEqual(int32_t(6), d.Back<int32_t>());
					const Datum d1(d);
					Assert::AreEqual(int32_t(6), d.Front<int32_t>());
					Assert::AreEqual(int32_t(6), d1.Back<int32_t>());
				}
				{
					Datum d;
					d = 6.f;
					Assert::AreEqual(float(6), d.As<float>(0));
					Assert::AreEqual(float(6), d.Front<float>());
					Assert::AreEqual(float(6), d.Back<float>());
					const Datum d1(d);
					Assert::AreEqual(float(6), d1.Front<float>());
					Assert::AreEqual(float(6), d1.Back<float>());
				}
				{
					Datum d;
					d = glm::vec4(6.f, 0.f, 0.f, 0.f);
					Assert::AreEqual(6.f, d.As<glm::vec4>(0).x);
					Assert::AreEqual(6.f, d.Front<glm::vec4>().x);
					Assert::AreEqual(6.f, d.Back<glm::vec4>().x);
					const Datum d1(d);
					Assert::AreEqual(6.f, d1.Front<glm::vec4>().x);
					Assert::AreEqual(6.f, d1.Back<glm::vec4>().x);
				}
				{
					Datum d;
					glm::mat4 temp;
					temp[0][0] = 6.f;
					d = temp;
					Assert::AreEqual(6.f, d.As<glm::mat4>(0)[0][0]);
					Assert::AreEqual(6.f, d.Front<glm::mat4>()[0][0]);
					Assert::AreEqual(6.f, d.Back<glm::mat4>()[0][0]);
					const Datum d1(d);
					Assert::AreEqual(6.f, d1.Front<glm::mat4>()[0][0]);
					Assert::AreEqual(6.f, d1.Back<glm::mat4>()[0][0]);
				}
				{
					Datum d;
					d = "Hello"s;
					Assert::AreEqual("Hello"s, d.As<std::string>(0));
					Assert::AreEqual("Hello"s, d.Front<std::string>());
					Assert::AreEqual("Hello"s, d.Back<std::string>());
					const Datum d1(d);
					Assert::AreEqual("Hello"s, d1.Front<std::string>());
					Assert::AreEqual("Hello"s, d1.Back<std::string>());
				}
				{
					Foo* temp = new Foo(6);
					Datum d;
					d = temp;
					Assert::AreEqual(*temp, *reinterpret_cast<Foo*>(d.As<RTTI*>(0)));
					Assert::AreEqual(*temp, *reinterpret_cast<Foo*>(d.Front<RTTI*>()));
					Assert::AreEqual(*temp, *reinterpret_cast<Foo*>(d.Back<RTTI*>()));
					const Datum d1(d);
					Assert::AreEqual(*temp, *reinterpret_cast<Foo*>(d1.Front<RTTI*>()));
					Assert::AreEqual(*temp, *reinterpret_cast<Foo*>(d1.Back<RTTI*>()));
					delete temp;
				}
			}
		}
		TEST_METHOD(Find)
		{
			size_t defaultSize = 3;
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(int32_t(i), i);
					Assert::IsTrue(d.Find<int32_t>(int32_t(i)).first);
					Assert::AreEqual(int32_t(i), *d.Find<int32_t>(int32_t(i)).second);
				}
				Assert::IsFalse(d.Find<int32_t>(int32_t(5)).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(float(i), i);
					Assert::IsTrue(d.Find<float>(float(i)).first);
					Assert::AreEqual(float(i), *d.Find<float>(float(i)).second);
				}
				Assert::IsFalse(d.Find<float>(float(5)).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(float(i), 0.f, 0.f, 0.f), i);
					Assert::IsTrue(d.Find<glm::vec4>(glm::vec4(float(i), 0.f, 0.f, 0.f)).first);
					Assert::AreEqual(float(i), (*d.Find<glm::vec4>(glm::vec4(float(i), 0.f, 0.f, 0.f)).second).x);

					
				}
				Assert::IsFalse(d.Find<glm::vec4>(glm::vec4(5.f, 0.f, 0.f, 0.f)).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					glm::mat4 temp = glm::mat4(glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f));
					d.Set(temp, i);
					Assert::IsTrue(d.Find<glm::mat4>(temp).first);
					Assert::AreEqual(float(i), (*d.Find<glm::mat4>(temp).second)[0][0]);

					
				}
				Assert::IsFalse(d.Find<glm::mat4>(glm::mat4(glm::vec4(5.f, 0.f, 0.f, 0.f), glm::vec4(5.f, 0.f, 0.f, 0.f), glm::vec4(5.f, 0.f, 0.f, 0.f), glm::vec4(5.f, 0.f, 0.f, 0.f))).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str1(c);
					d.Set(str1, i);
					char c1[10];
					sprintf_s(c1, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str2(c);
					Assert::IsTrue(d.Find<std::string>(str2).first);
					Assert::AreEqual(str2, *d.Find<std::string>(str2).second);

					
				}
				Assert::IsFalse(d.Find("string 4"s).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo f1(1);
				Foo f2(2);
				Foo f3(3);
				Foo f4(4);
				d.Set(&f1, 0);
				Assert::IsTrue(d.Find<RTTI*>(&f1).first);
				Assert::AreSame(f1, *reinterpret_cast<Foo*>(*d.Find<RTTI*>(&f1).second));
				d.Set(&f2, 1);
				Assert::IsTrue(d.Find<RTTI*>(&f2).first);
				Assert::AreSame(f2, *reinterpret_cast<Foo*>(*d.Find<RTTI*>(&f2).second));
				d.Set(&f3, 2);
				Assert::IsTrue(d.Find<RTTI*>(&f3).first);
				Assert::AreSame(f3, *reinterpret_cast<Foo*>(*d.Find<RTTI*>(&f3).second));

				Assert::IsFalse(d.Find<RTTI*>(&f4).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<int32_t>(i), i);
				}
				const Datum d1(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::IsTrue(d1.Find<int32_t>(int32_t(i)).first);
					Assert::AreEqual(int32_t(i), *d1.Find<int32_t>(int32_t(i)).second);
				}
				Assert::IsFalse(d1.Find<int32_t>(int32_t(5)).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(float(i), i);
				}
				const Datum d1(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::IsTrue(d1.Find<float>(float(i)).first);
					Assert::AreEqual(float(i), *d1.Find<float>(float(i)).second);
				}
				Assert::IsFalse(d1.Find<float>(float(5)).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(float(i), 0.f, 0.f, 0.f), i);
				}
				const Datum d1(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::IsTrue(d1.Find<glm::vec4>(glm::vec4(float(i), 0.f, 0.f, 0.f)).first);
					Assert::AreEqual(float(i), (*d1.Find<glm::vec4>(glm::vec4(float(i), 0.f, 0.f, 0.f)).second).x);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					glm::mat4 temp = glm::mat4(glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f));
					d.Set(temp, i);
					
				}
				const Datum d1(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::IsTrue(d1.Find<glm::mat4>(glm::mat4(glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f))).first);
					Assert::AreEqual(float(i), (*d1.Find<glm::mat4>(glm::mat4(glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f))).second)[0][0]);
				}
				Assert::IsFalse(d1.Find<glm::mat4>(glm::mat4(glm::vec4(float(5), 0.f, 0.f, 0.f), glm::vec4(float(5), 0.f, 0.f, 0.f), glm::vec4(float(5), 0.f, 0.f, 0.f), glm::vec4(float(5), 0.f, 0.f, 0.f))).first);
			}
			{
				Foo* f1 = new Foo(1);
				Foo* f2 = new Foo(2);
				Foo* f3 = new Foo(3);
				Foo* f4 = new Foo(4);
				Datum d(defaultSize, Datum::DatumType::Pointer);
				d.Set(f1, 0);
				d.Set(f2, 1);
				d.Set(f3, 2);
				const Datum d1(d);
				Assert::IsTrue(d1.Find<RTTI*>(f1).first);
				Assert::AreEqual(*f1, *reinterpret_cast<Foo*>(*d1.Find<RTTI*>(f1).second));
				Assert::IsTrue(d1.Find<RTTI*>(f2).first);
				Assert::AreEqual(*f2, *reinterpret_cast<Foo*>(*d1.Find<RTTI*>(f2).second));
				Assert::IsTrue(d1.Find<RTTI*>(f3).first);
				Assert::AreEqual(*f3, *reinterpret_cast<Foo*>(*d1.Find<RTTI*>(f3).second));
				Assert::IsFalse(d1.Find<RTTI*>(f4).first);
				delete f1;
				delete f2;
				delete f3;
				delete f4;
			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str1(c);
					d.Set(str1, i);
				}
				const Datum d1(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str2(c);
					Assert::IsTrue(d1.Find<std::string>(str2).first);
					Assert::AreEqual(str2, *d1.Find<std::string>(str2).second);
				}
				Assert::IsFalse(d1.Find("string 4"s).first);
			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo* f1 = new Foo(1);
				Foo* f2 = new Foo(2);
				Foo* f3 = new Foo(3);
				d.Set(f1, 0);
				Assert::IsTrue(d.Find<RTTI*>(f1).first);
				Assert::AreSame(*f1, *reinterpret_cast<Foo*>(*d.Find<RTTI*>(f1).second));
				d.Set(f2, 1);
				Assert::IsTrue(d.Find<RTTI*>(f2).first);
				Assert::AreSame(*f2, *reinterpret_cast<Foo*>(*d.Find<RTTI*>(f2).second));
				d.Set(f3, 2);
				Assert::IsTrue(d.Find<RTTI*>(f3).first);
				Assert::AreSame(*f3, *reinterpret_cast<Foo*>(*d.Find<RTTI*>(f3).second));
				delete f1;
				delete f2;
				delete f3;
			}

		}
		//Need to fix this after refactor, solely a test writing issue
		TEST_METHOD(Remove)
		{
			size_t defaultSize = 4;
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(int32_t(i), i);
				}
				d.Remove(int32_t(1));
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(int32_t(1)).first);

				d.Remove(int32_t(3));
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(int32_t(3)).first);

				d.Remove(int32_t(0));
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(int32_t(0)).first);

				d.Remove(int32_t(0));
				Assert::AreEqual(defaultSize - 3, d.Size());

				d.Remove(int32_t(4));
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(int32_t(4)).first);

				d.Remove(int32_t(2));
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(float(i), i);
				}

				d.Remove(1.f);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(1.f).first);

				d.Remove(3.f);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(3.f).first);

				d.Remove(0.f);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(0.f).first);

				d.Remove(0.f);
				Assert::AreEqual(defaultSize - 3, d.Size());

				d.Remove(4.f);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(41.f).first);

				d.Remove(2.f);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(float(i), 0.f, 0.f, 0.f), i);
				}

				d.Remove(glm::vec4(1.f, 0.f, 0.f, 0.f));
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::vec4(1.f, 0.f, 0.f, 0.f)).first);

				d.Remove(glm::vec4(3.f, 0.f, 0.f, 0.f));
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::vec4(3.f, 0.f, 0.f, 0.f)).first);

				d.Remove(glm::vec4(0.f, 0.f, 0.f, 0.f));
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::vec4(0.f, 0.f, 0.f, 0.f)).first);

				d.Remove(glm::vec4(4.f, 0.f, 0.f, 0.f));
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::vec4(4.f, 0.f, 0.f, 0.f)).first);

				d.Remove(glm::vec4(2.f, 0.f, 0.f, 0.f));
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::mat4(glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f)), i);
				}

				d.Remove(glm::mat4(glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f)));
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::mat4(glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f))).first);

				d.Remove(glm::mat4(glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f)));
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::mat4(glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f))).first);

				d.Remove(glm::mat4(glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f)));
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::mat4(glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f))).first);

				d.Remove(glm::mat4(glm::vec4(4.f, 0.f, 0.f, 0.f), glm::vec4(4.f, 0.f, 0.f, 0.f), glm::vec4(4.f, 0.f, 0.f, 0.f), glm::vec4(4.f, 0.f, 0.f, 0.f)));
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::mat4(glm::vec4(4.f, 0.f, 0.f, 0.f), glm::vec4(4.f, 0.f, 0.f, 0.f), glm::vec4(4.f, 0.f, 0.f, 0.f), glm::vec4(4.f, 0.f, 0.f, 0.f))).first);

				d.Remove(glm::mat4(glm::vec4(2.f, 0.f, 0.f, 0.f), glm::vec4(2.f, 0.f, 0.f, 0.f), glm::vec4(2.f, 0.f, 0.f, 0.f), glm::vec4(2.f, 0.f, 0.f, 0.f)));
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str(c);
					d.Set(str, i);
				}

				d.Remove("string 1"s);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find("string 1"s).first);

				d.Remove("string 3"s);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find("string 3"s).first);

				d.Remove("string 0"s);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find("string 0"s).first);

				d.Remove("string 4"s);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find("string 4"s).first);

				d.Remove("string 2"s);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo f1;
				Foo f2;
				Foo f3;
				Foo f4;
				Foo f5;
				d.Set(&f1, 0);
				d.Set(&f2, 1);
				d.Set(&f3, 2);
				d.Set(&f4, 3);

				d.Remove(&f2);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find<RTTI*>(&f2).first);

				d.Remove(&f4);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find<RTTI*>(&f4).first);

				d.Remove(&f1);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find<RTTI*>(&f1).first);

				d.Remove(&f5);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find<RTTI*>(&f5).first);

				d.Remove(&f3);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(int32_t(i), i);
				}
				d.RemoveAt<int32_t>(1);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(int32_t(1)).first);

				d.RemoveAt<int32_t>(2);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(int32_t(3)).first);

				d.RemoveAt<int32_t>(0);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(int32_t(0)).first);


				Assert::ExpectException<std::out_of_range>([&d] {d.RemoveAt<int32_t>(4); });

				d.RemoveAt<int32_t>(0);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(float(i), i);
				}

				d.RemoveAt<float>(1);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(1.f).first);

				d.RemoveAt<float>(2);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(3.f).first);

				d.RemoveAt<float>(0);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(0.f).first);


				Assert::ExpectException<std::out_of_range>([&d] {d.RemoveAt<float>(4); });

				d.RemoveAt<float>(0);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(float(i), 0.f, 0.f, 0.f), i);
				}

				d.RemoveAt<glm::vec4>(1);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::vec4(1.f, 0.f, 0.f, 0.f)).first);

				d.RemoveAt<glm::vec4>(2);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::vec4(3.f, 0.f, 0.f, 0.f)).first);

				d.RemoveAt<glm::vec4>(0);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::vec4(0.f, 0.f, 0.f, 0.f)).first);

				Assert::ExpectException<std::out_of_range>([&d] {d.RemoveAt<glm::vec4>(4); });

				d.RemoveAt<glm::vec4>(0);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::mat4(glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f), glm::vec4(float(i), 0.f, 0.f, 0.f)), i);
				}

				d.RemoveAt<glm::mat4>(1);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::mat4(glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f))).first);

				d.RemoveAt<glm::mat4>(2);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::mat4(glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f), glm::vec4(3.f, 0.f, 0.f, 0.f))).first);

				d.RemoveAt<glm::mat4>(0);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find(glm::mat4(glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 0.f, 0.f))).first);

				Assert::ExpectException<std::out_of_range>([&d] {d.RemoveAt<glm::mat4>(4); });

				d.RemoveAt<glm::mat4>(0);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					std::string str(c);
					d.Set(str, i);
				}

				d.RemoveAt<std::string>(1);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find("string 1"s).first);

				d.RemoveAt<std::string>(2);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find("string 3"s).first);

				d.RemoveAt<std::string>(0);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find("string 0"s).first);

				Assert::ExpectException<std::out_of_range>([&d] {d.RemoveAt<std::string>(4); });

				d.RemoveAt<std::string>(0);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo f1;
				Foo f2;
				Foo f3;
				Foo f4;
				Foo f5;
				d.Set(&f1, 0);
				d.Set(&f2, 1);
				d.Set(&f3, 2);
				d.Set(&f4, 3);

				d.RemoveAt<RTTI*>(1);
				Assert::AreEqual(defaultSize - 1, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find<RTTI*>(&f2).first);

				d.RemoveAt<RTTI*>(2);
				Assert::AreEqual(defaultSize - 2, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find<RTTI*>(&f4).first);

				d.RemoveAt<RTTI*>(0);
				Assert::AreEqual(defaultSize - 3, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
				Assert::IsFalse(d.Find<RTTI*>(&f1).first);

				Assert::ExpectException<std::out_of_range>([&d] {d.RemoveAt<RTTI*>(4); });

				d.RemoveAt<RTTI*>(0);
				Assert::AreEqual(defaultSize - 4, d.Size());
				Assert::AreEqual(defaultSize, d.Capacity());
			}
		}
		TEST_METHOD(Storage)
		{
			size_t defaultSize = 3;
			size_t externalSize = 7;
			{
				int32_t* ext = reinterpret_cast<int32_t*>(malloc(externalSize * sizeof(int32_t)));
				for (size_t i = 0; i < externalSize; ++i) {
					new(ext + i)int32_t(gsl::narrow_cast<int32_t>(i));
				}
				Datum d(defaultSize, Datum::DatumType::Integer);
				d.SetStorage(ext, externalSize, externalSize);
				Assert::ExpectException<std::runtime_error>([&d] {d.PushBack(int32_t(15)); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(1); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(10); });
				for (size_t i = 0; i < externalSize; ++i) {
					Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d.As<int32_t>(i));
				}
				free(ext);
			}
			{
				float* ext = reinterpret_cast<float*>(malloc(externalSize * sizeof(float)));
				for (size_t i = 0; i < externalSize; ++i) {
					new(ext + i)float(gsl::narrow_cast<float>(i));
				}
				Datum d(defaultSize, Datum::DatumType::Float);
				d.SetStorage(ext, externalSize, externalSize);
				Assert::ExpectException<std::runtime_error>([&d] {d.PushBack(15.f); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(1); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(10); });
				for (size_t i = 0; i < externalSize; ++i) {
					Assert::AreEqual(float(i), d.As<float>(i));
				}
				free(ext);
			}
			{
				glm::vec4* ext = reinterpret_cast<glm::vec4*>(malloc(externalSize * sizeof(glm::vec4)));
				for (size_t i = 0; i < externalSize; ++i) {
					new(ext + i)glm::vec4(float(i), 0.f, 0.f, 0.f);
				}
				Datum d(defaultSize, Datum::DatumType::Vector);
				d.SetStorage(ext, externalSize, externalSize);
				Assert::ExpectException<std::runtime_error>([&d] {d.PushBack(glm::vec4(15.f, 0.f, 0.f, 0.f)); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(1); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(10); });
				for (size_t i = 0; i < externalSize; ++i) {
					Assert::AreEqual(float(i), d.As<glm::vec4>(i).x);
				}
				free(ext);
			}
			{
				glm::mat4* ext = reinterpret_cast<glm::mat4*>(malloc(externalSize * sizeof(glm::mat4)));
				for (size_t i = 0; i < externalSize; ++i) {
					new(ext + i)glm::mat4();
					(*(ext + i))[0][0] = float(i);
				}
				Datum d(defaultSize, Datum::DatumType::Matrix);
				d.SetStorage(ext, externalSize, externalSize);
				glm::mat4 invalidValue;
				invalidValue[0][0] = 15.f;
				Assert::ExpectException<std::runtime_error>([&d, &invalidValue] {d.PushBack(invalidValue); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(1); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(10); });
				for (size_t i = 0; i < externalSize; ++i) {
					Assert::AreEqual(float(i), d.As<glm::mat4>(i)[0][0]);
				}
				free(ext);
			}
			{
				std::string* ext = reinterpret_cast<std::string*>(malloc(externalSize * sizeof(std::string)));
				for (size_t i = 0; i < externalSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					new(ext + i)std::string(c);
				}
				Datum d(defaultSize, Datum::DatumType::String);
				d.SetStorage(ext, externalSize, externalSize);
				Assert::ExpectException<std::runtime_error>([&d] {d.PushBack("string 15"s); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(1); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(10); });
				for (size_t i = 0; i < externalSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					Assert::AreEqual(std::string(c), d.As<std::string>(i));
				}
				for (size_t i = 0; i < externalSize; ++i) {
					(ext + i)->~basic_string();
				}
				free(ext);
			}
			{
				Foo** ext = reinterpret_cast<Foo**>(malloc(externalSize * sizeof(Foo*)));
				for (size_t i = 0; i < externalSize; ++i) {
					Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
					new(ext + i)Foo*(fp);
				}
				Datum d(defaultSize, Datum::DatumType::Pointer);
				d.SetStorage(reinterpret_cast<RTTI**>(ext), externalSize, externalSize);
				Foo* invalidValue = new Foo(15);
				Assert::ExpectException<std::runtime_error>([&d, &invalidValue] {d.PushBack(invalidValue); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(1); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Resize(10); });
				for (size_t i = 0; i < externalSize; ++i) {
					Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>((d.As<RTTI*>(i))));
				}
				for (size_t i = 0; i < externalSize; ++i) {
					delete* (ext + i);
				}
				delete invalidValue;
				free(ext);
			}
		}
		TEST_METHOD(Copy)
		{
			size_t defaultSize = 3;
			size_t externalSize = 7;
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<int32_t>(i), i);
				}
				{
					Datum d1(d);
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d1.As<int32_t>(i));
						Assert::AreEqual(d.As<int32_t>(i), d1.As<int32_t>(i));
						Assert::AreNotSame(d.As<int32_t>(i), d1.As<int32_t>(i));
					}
				}
				{
					int32_t* ext = reinterpret_cast<int32_t*>(malloc(externalSize * sizeof(int32_t)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)int32_t(gsl::narrow_cast<int32_t>(i));
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1(d);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d1.As<int32_t>(i));
						Assert::AreEqual(d.As<int32_t>(i), d1.As<int32_t>(i));
					}
					free(ext);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<float>(i), i);
				}
				{
					Datum d1(d);
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<float>(i));
						Assert::AreEqual(d.As<float>(i), d1.As<float>(i));
						Assert::AreNotSame(d.As<float>(i), d1.As<float>(i));
					}
				}
				{
					float* ext = reinterpret_cast<float*>(malloc(externalSize * sizeof(float)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)float(gsl::narrow_cast<float>(i));
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1(d);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<float>(i));
						Assert::AreEqual(d.As<float>(i), d1.As<float>(i));
					}
					free(ext);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f), i);
				}
				{
					Datum d1(d);
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::vec4>(i).x);
						Assert::AreEqual(d.As<glm::vec4>(i).x, d1.As<glm::vec4>(i).x);
					}
				}
				{
					glm::vec4* ext = reinterpret_cast<glm::vec4*>(malloc(externalSize * sizeof(glm::vec4)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f);
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1(d);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::vec4>(i).x);
						Assert::AreEqual(d.As<glm::vec4>(i).x, d1.As<glm::vec4>(i).x);
						Assert::AreSame(d.As<glm::vec4>(i).x, d1.As<glm::vec4>(i).x);
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					glm::mat4 temp;
					temp[0][0] = gsl::narrow_cast<float>(i);
					d.Set(temp, i);
				}
				{
					Datum d1(d);
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::mat4>(i)[0][0]);
						Assert::AreEqual(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
						Assert::AreNotSame(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
					}
				}
				{
					glm::mat4* ext = reinterpret_cast<glm::mat4*>(malloc(externalSize * sizeof(glm::mat4)));
					for (size_t i = 0; i < externalSize; ++i) {
						glm::mat4 temp;
						temp[0][0] = gsl::narrow_cast<float>(i);
						new(ext + i)glm::mat4(temp);
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1(d);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::mat4>(i)[0][0]);
						Assert::AreEqual(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
						Assert::AreSame(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					d.Set(std::string(c), i);
				}
				{
					Datum d1(d);
					for (size_t i = 0; i < defaultSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						Assert::AreEqual(std::string(c), d1.As<std::string>(i));
						Assert::AreEqual(d.As<std::string>(i), d1.As<std::string>(i));
						Assert::AreNotSame(d.As<std::string>(i), d1.As<std::string>(i));
					}
				}
				{
					std::string* ext = reinterpret_cast<std::string*>(malloc(externalSize * sizeof(std::string)));
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						new(ext + i)std::string(c);
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1(d);
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						Assert::AreEqual(std::string(c), d1.As<std::string>(i));
						Assert::AreEqual(d.As<std::string>(i), d1.As<std::string>(i));
						Assert::AreSame(d.As<std::string>(i), d1.As<std::string>(i));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						(ext + i)->~basic_string();
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo** foos = reinterpret_cast<Foo**>(malloc(defaultSize * sizeof(Foo*)));
				for (size_t i = 0; i < defaultSize; ++i) {
					Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
					new(foos + i)Foo*(fp);
					d.Set(fp, i);
				}
				{
					Datum d1(d);
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
						Assert::AreEqual(*reinterpret_cast<Foo*>(d.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
					}
				}
				{
					Foo** ext = reinterpret_cast<Foo**>(malloc(externalSize * sizeof(Foo*)));
					for (size_t i = 0; i < externalSize; ++i) {
						Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
						new(ext + i)Foo*(fp);
					}
					d.SetStorage(reinterpret_cast<RTTI**>(ext), externalSize, externalSize);
					Datum d1(d);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
						Assert::AreEqual(*reinterpret_cast<Foo*>(d.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
						Assert::AreSame(*reinterpret_cast<Foo*>(d.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						delete* (ext + i);
					}
					for (size_t i = 0; i < defaultSize; ++i) {
						delete* (foos + i);
					}
					free(ext);
					free(foos);
				}
				
			}
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<int32_t>(i), i);
				}
				{
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d1.As<int32_t>(i));
						Assert::AreEqual(d.As<int32_t>(i), d1.As<int32_t>(i));
						Assert::AreNotSame(d.As<int32_t>(i), d1.As<int32_t>(i));
					}
				}
				{
					int32_t* ext = reinterpret_cast<int32_t*>(malloc(externalSize * sizeof(int32_t)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)int32_t(gsl::narrow_cast<int32_t>(i));
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d1.As<int32_t>(i));
						Assert::AreEqual(d.As<int32_t>(i), d1.As<int32_t>(i));
						Assert::AreSame(d.As<int32_t>(i), d1.As<int32_t>(i));
					}
					free(ext);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<float>(i), i);
				}
				{
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<float>(i));
						Assert::AreEqual(d.As<float>(i), d1.As<float>(i));
						Assert::AreNotSame(d.As<float>(i), d1.As<float>(i));
					}
				}
				{
					float* ext = reinterpret_cast<float*>(malloc(externalSize * sizeof(float)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)float(gsl::narrow_cast<float>(i));
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<float>(i));
						Assert::AreEqual(d.As<float>(i), d1.As<float>(i));
						Assert::AreSame(d.As<float>(i), d1.As<float>(i));
					}
					free(ext);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f), i);
				}
				{
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::vec4>(i).x);
						Assert::AreEqual(d.As<glm::vec4>(i).x, d1.As<glm::vec4>(i).x);
						Assert::AreNotSame(d.As<glm::vec4>(i).x, d1.As<glm::vec4>(i).x);
					}
				}
				{
					glm::vec4* ext = reinterpret_cast<glm::vec4*>(malloc(externalSize * sizeof(glm::vec4)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f);
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::vec4>(i).x);
						Assert::AreEqual(d.As<glm::vec4>(i).x, d1.As<glm::vec4>(i).x);
						Assert::AreSame(d.As<glm::vec4>(i).x, d1.As<glm::vec4>(i).x);
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					glm::mat4 temp;
					temp[0][0] = gsl::narrow_cast<float>(i);
					d.Set(temp, i);
				}
				{
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::mat4>(i)[0][0]);
						Assert::AreEqual(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
						Assert::AreNotSame(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
					}
				}
				{
					glm::mat4* ext = reinterpret_cast<glm::mat4*>(malloc(externalSize * sizeof(glm::mat4)));
					for (size_t i = 0; i < externalSize; ++i) {
						glm::mat4 temp;
						temp[0][0] = gsl::narrow_cast<float>(i);
						new(ext + i)glm::mat4(temp);
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d1.As<glm::mat4>(i)[0][0]);
						Assert::AreEqual(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
						Assert::AreSame(d.As<glm::mat4>(i)[0][0], d1.As<glm::mat4>(i)[0][0]);
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					d.Set(std::string(c), i);
				}
				{
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < defaultSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						Assert::AreEqual(std::string(c), d1.As<std::string>(i));
						Assert::AreEqual(d.As<std::string>(i), d1.As<std::string>(i));
						Assert::AreNotSame(d.As<std::string>(i), d1.As<std::string>(i));
					}
				}
				{
					std::string* ext = reinterpret_cast<std::string*>(malloc(externalSize * sizeof(std::string)));
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						new(ext + i)std::string(c);
					}
					d.SetStorage(ext, externalSize, externalSize);
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						Assert::AreEqual(std::string(c), d1.As<std::string>(i));
						Assert::AreEqual(d.As<std::string>(i), d1.As<std::string>(i));
						Assert::AreSame(d.As<std::string>(i), d1.As<std::string>(i));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						(ext + i)->~basic_string();
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo** foos = reinterpret_cast<Foo**>(malloc(defaultSize * sizeof(Foo*)));
				for (size_t i = 0; i < defaultSize; ++i) {
					Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
					new(foos + i)Foo*(fp);
					d.Set(fp, i);
				}
				{
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
						Assert::AreEqual(*reinterpret_cast<Foo*>(d.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
					}
				}
				{
					Foo** ext = reinterpret_cast<Foo**>(malloc(externalSize * sizeof(Foo*)));
					for (size_t i = 0; i < externalSize; ++i) {
						Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
						new(ext + i)Foo*(fp);
					}
					d.SetStorage(reinterpret_cast<RTTI**>(ext), externalSize, externalSize);
					Datum d1;
					d1 = d;
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
						Assert::AreEqual(*reinterpret_cast<Foo*>(d.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
						Assert::AreSame(*reinterpret_cast<Foo*>(d.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d1.As<RTTI*>(i)));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						delete* (ext + i);
					}
					for (size_t i = 0; i < defaultSize; ++i) {
						delete* (foos + i);
					}
					free(ext);
					free(foos);
				}
				
			}
		}
		TEST_METHOD(Move)

		{
			size_t defaultSize = 3;
			size_t externalSize = 7;
			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<int32_t>(i), i);
				}
				Datum d1(d);
				Datum d2(std::move(d));
				{
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d2.As<int32_t>(i));
						Assert::AreEqual(d1.As<int32_t>(i), d2.As<int32_t>(i));
						Assert::AreNotSame(d1.As<int32_t>(i), d2.As<int32_t>(i));
					}
				}
				{
					int32_t* ext = reinterpret_cast<int32_t*>(malloc(externalSize * sizeof(int32_t)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)int32_t(gsl::narrow_cast<int32_t>(i));
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(std::move(d1));
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d4.As<int32_t>(i));
						Assert::AreEqual(d3.As<int32_t>(i), d4.As<int32_t>(i));
						Assert::AreSame(d3.As<int32_t>(i), d4.As<int32_t>(i));
					}
					free(ext);
				}
			}
			
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<float>(i), i);
				}
				Datum d1(d);
				Datum d2(std::move(d));
				{
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d2.As<float>(i));
						Assert::AreEqual(d1.As<float>(i), d2.As<float>(i));
						Assert::AreNotSame(d1.As<float>(i), d2.As<float>(i));
					}
				}
				{
					float* ext = reinterpret_cast<float*>(malloc(externalSize * sizeof(float)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)float(gsl::narrow_cast<float>(i));
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(std::move(d1));
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d4.As<float>(i));
						Assert::AreEqual(d3.As<float>(i), d4.As<float>(i));
						Assert::AreSame(d3.As<float>(i), d4.As<float>(i));
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f), i);
				}
				Datum d1(d);
				Datum d2(std::move(d));
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::AreEqual(gsl::narrow_cast<float>(i), d2.As<glm::vec4>(i).x);
					Assert::AreEqual(d1.As<glm::vec4>(i).x, d2.As<glm::vec4>(i).x);
					Assert::AreNotSame(d1.As<glm::vec4>(i).x, d2.As<glm::vec4>(i).x);
				}

				{
					glm::vec4* ext = reinterpret_cast<glm::vec4*>(malloc(externalSize * sizeof(glm::vec4)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f);
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(std::move(d1));
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d4.As<glm::vec4>(i).x);
						Assert::AreEqual(d3.As<glm::vec4>(i).x, d4.As<glm::vec4>(i).x);
						Assert::AreSame(d3.As<glm::vec4>(i).x, d4.As<glm::vec4>(i).x);
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					glm::mat4 temp;
					temp[0][0] = gsl::narrow_cast<float>(i);
					d.Set(temp, i);
				}

				Datum d1(d);
				Datum d2(std::move(d));

				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::AreEqual(gsl::narrow_cast<float>(i), d2.As<glm::mat4>(i)[0][0]);
					Assert::AreEqual(d1.As<glm::mat4>(i)[0][0], d2.As<glm::mat4>(i)[0][0]);
					Assert::AreNotSame(d1.As<glm::mat4>(i)[0][0], d2.As<glm::mat4>(i)[0][0]);
				}

				{
					glm::mat4* ext = reinterpret_cast<glm::mat4*>(malloc(externalSize * sizeof(glm::mat4)));
					for (size_t i = 0; i < externalSize; ++i) {
						glm::mat4 temp;
						temp[0][0] = gsl::narrow_cast<float>(i);
						new(ext + i)glm::mat4(temp);
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(std::move(d1));
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d4.As<glm::mat4>(i)[0][0]);
						Assert::AreEqual(d3.As<glm::mat4>(i)[0][0], d4.As<glm::mat4>(i)[0][0]);
						Assert::AreSame(d3.As<glm::mat4>(i)[0][0], d4.As<glm::mat4>(i)[0][0]);
					}
					free(ext);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					d.Set(std::string(c), i);
				}

				Datum d1(d);
				Datum d2(std::move(d));
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					Assert::AreEqual(std::string(c), d2.As<std::string>(i));
					Assert::AreEqual(d1.As<std::string>(i), d2.As<std::string>(i));
					Assert::AreNotSame(d1.As<std::string>(i), d2.As<std::string>(i));
				}

				{
					std::string* ext = reinterpret_cast<std::string*>(malloc(externalSize * sizeof(std::string)));
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						new(ext + i)std::string(c);
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(std::move(d1));
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						Assert::AreEqual(std::string(c), d4.As<std::string>(i));
						Assert::AreEqual(d3.As<std::string>(i), d4.As<std::string>(i));
						Assert::AreSame(d3.As<std::string>(i), d4.As<std::string>(i));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						(ext + i)->~basic_string();
					}
					free(ext);
				}
			}

			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo** foos = reinterpret_cast<Foo**>(malloc(defaultSize * sizeof(Foo*)));
				for (size_t i = 0; i < defaultSize; ++i) {
					Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
					new(foos + i)Foo* (fp);
					d.Set(fp, i);
				}

				Datum d1(d);
				Datum d2(std::move(d));
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d2.As<RTTI*>(i)));
					Assert::AreEqual(*reinterpret_cast<Foo*>(d1.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d2.As<RTTI*>(i)));
				}

				{
					Foo** ext = reinterpret_cast<Foo**>(malloc(externalSize * sizeof(Foo*)));
					for (size_t i = 0; i < externalSize; ++i) {
						Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
						new(ext + i)Foo* (fp);
					}
					d1.SetStorage(reinterpret_cast<RTTI**>(ext), externalSize, externalSize);
					Datum d3(d1);
					Datum d4(std::move(d1));
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d4.As<RTTI*>(i)));
						Assert::AreEqual(*reinterpret_cast<Foo*>(d3.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d4.As<RTTI*>(i)));
						Assert::AreSame(*reinterpret_cast<Foo*>(d3.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d4.As<RTTI*>(i)));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						delete* (ext + i);
					}
					for (size_t i = 0; i < defaultSize; ++i) {
						delete* (foos + i);
					}
					free(ext);
					free(foos);
				}

			}

			{
				Datum d(defaultSize, Datum::DatumType::Integer);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<int32_t>(i), i);
				}
				Datum d1(d);
				Datum d2(defaultSize, Datum::DatumType::Integer);
				d2 = std::move(d);
				{
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d2.As<int32_t>(i));
						Assert::AreEqual(d1.As<int32_t>(i), d2.As<int32_t>(i));
						Assert::AreNotSame(d1.As<int32_t>(i), d2.As<int32_t>(i));
					}
				}
				{
					int32_t* ext = reinterpret_cast<int32_t*>(malloc(externalSize * sizeof(int32_t)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)int32_t(gsl::narrow_cast<int32_t>(i));
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(defaultSize, Datum::DatumType::Integer);
					d4 = std::move(d1);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<int32_t>(i), d4.As<int32_t>(i));
						Assert::AreEqual(d3.As<int32_t>(i), d4.As<int32_t>(i));
						Assert::AreSame(d3.As<int32_t>(i), d4.As<int32_t>(i));
					}
					free(ext);
				}
			}
			
			{
				Datum d(defaultSize, Datum::DatumType::Float);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(gsl::narrow_cast<float>(i), i);
				}
				Datum d1(d);
				Datum d2(defaultSize, Datum::DatumType::Float);
				d2 = std::move(d);
				{
					for (size_t i = 0; i < defaultSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d2.As<float>(i));
						Assert::AreEqual(d1.As<float>(i), d2.As<float>(i));
						Assert::AreNotSame(d1.As<float>(i), d2.As<float>(i));
					}
				}
				{
					float* ext = reinterpret_cast<float*>(malloc(externalSize * sizeof(float)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)float(gsl::narrow_cast<float>(i));
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(defaultSize, Datum::DatumType::Float);
					d4 = std::move(d1);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d4.As<float>(i));
						Assert::AreEqual(d3.As<float>(i), d4.As<float>(i));
						Assert::AreSame(d3.As<float>(i), d4.As<float>(i));
					}
					free(ext);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::Vector);
				for (size_t i = 0; i < defaultSize; ++i) {
					d.Set(glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f), i);
				}
				Datum d1(d);
				Datum d2(defaultSize, Datum::DatumType::Vector);
				d2 = std::move(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::AreEqual(gsl::narrow_cast<float>(i), d2.As<glm::vec4>(i).x);
					Assert::AreEqual(d1.As<glm::vec4>(i).x, d2.As<glm::vec4>(i).x);
					Assert::AreNotSame(d1.As<glm::vec4>(i).x, d2.As<glm::vec4>(i).x);
				}

				{
					glm::vec4* ext = reinterpret_cast<glm::vec4*>(malloc(externalSize * sizeof(glm::vec4)));
					for (size_t i = 0; i < externalSize; ++i) {
						new(ext + i)glm::vec4(gsl::narrow_cast<float>(i), 0.f, 0.f, 0.f);
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(defaultSize, Datum::DatumType::Vector);
					d4 = std::move(d1);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d4.As<glm::vec4>(i).x);
						Assert::AreEqual(d3.As<glm::vec4>(i).x, d4.As<glm::vec4>(i).x);
						Assert::AreSame(d3.As<glm::vec4>(i).x, d4.As<glm::vec4>(i).x);
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Matrix);
				for (size_t i = 0; i < defaultSize; ++i) {
					glm::mat4 temp;
					temp[0][0] = gsl::narrow_cast<float>(i);
					d.Set(temp, i);
				}

				Datum d1(d);
				Datum d2(defaultSize, Datum::DatumType::Matrix);
				d2 = std::move(d);

				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::AreEqual(gsl::narrow_cast<float>(i), d2.As<glm::mat4>(i)[0][0]);
					Assert::AreEqual(d1.As<glm::mat4>(i)[0][0], d2.As<glm::mat4>(i)[0][0]);
					Assert::AreNotSame(d1.As<glm::mat4>(i)[0][0], d2.As<glm::mat4>(i)[0][0]);
				}

				{
					glm::mat4* ext = reinterpret_cast<glm::mat4*>(malloc(externalSize * sizeof(glm::mat4)));
					for (size_t i = 0; i < externalSize; ++i) {
						glm::mat4 temp;
						temp[0][0] = gsl::narrow_cast<float>(i);
						new(ext + i)glm::mat4(temp);
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(defaultSize, Datum::DatumType::Matrix);
					d4 = std::move(d1);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(gsl::narrow_cast<float>(i), d4.As<glm::mat4>(i)[0][0]);
						Assert::AreEqual(d3.As<glm::mat4>(i)[0][0], d4.As<glm::mat4>(i)[0][0]);
						Assert::AreSame(d3.As<glm::mat4>(i)[0][0], d4.As<glm::mat4>(i)[0][0]);
					}
					free(ext);
				}
			}
			{
				Datum d(defaultSize, Datum::DatumType::String);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					d.Set(std::string(c), i);
				}

				Datum d1(d);
				Datum d2(defaultSize, Datum::DatumType::String);
				d2 = std::move(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					char c[10];
					sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
					Assert::AreEqual(std::string(c), d2.As<std::string>(i));
					Assert::AreEqual(d1.As<std::string>(i), d2.As<std::string>(i));
					Assert::AreNotSame(d1.As<std::string>(i), d2.As<std::string>(i));
				}

				{
					std::string* ext = reinterpret_cast<std::string*>(malloc(externalSize * sizeof(std::string)));
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						new(ext + i)std::string(c);
					}
					d1.SetStorage(ext, externalSize, externalSize);
					Datum d3(d1);
					Datum d4(defaultSize, Datum::DatumType::String);
					d4 = std::move(d1);
					for (size_t i = 0; i < externalSize; ++i) {
						char c[10];
						sprintf_s(c, 10, "string %d", gsl::narrow_cast<int32_t>(i));
						Assert::AreEqual(std::string(c), d4.As<std::string>(i));
						Assert::AreEqual(d3.As<std::string>(i), d4.As<std::string>(i));
						Assert::AreSame(d3.As<std::string>(i), d4.As<std::string>(i));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						(ext + i)->~basic_string();
					}
					free(ext);
				}

			}
			{
				Datum d(defaultSize, Datum::DatumType::Pointer);
				Foo** foos = reinterpret_cast<Foo**>(malloc(defaultSize * sizeof(Foo*)));
				for (size_t i = 0; i < defaultSize; ++i) {
					Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
					new(foos + i)Foo* (fp);
					d.Set(fp, i);
				}

				Datum d1(d);
				Datum d2(defaultSize, Datum::DatumType::Pointer);
				d2 = std::move(d);
				for (size_t i = 0; i < defaultSize; ++i) {
					Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d2.As<RTTI*>(i)));
					Assert::AreEqual(*reinterpret_cast<Foo*>(d1.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d2.As<RTTI*>(i)));
				}

				{
					Foo** ext = reinterpret_cast<Foo**>(malloc(externalSize * sizeof(Foo*)));
					for (size_t i = 0; i < externalSize; ++i) {
						Foo* fp = new Foo(gsl::narrow_cast<int32_t>(i));
						new(ext + i)Foo* (fp);
					}
					d1.SetStorage(reinterpret_cast<RTTI**>(ext), externalSize, externalSize);
					Datum d3(d1);
					Datum d4(defaultSize, Datum::DatumType::Pointer);
					d4 = std::move(d1);
					for (size_t i = 0; i < externalSize; ++i) {
						Assert::AreEqual(Foo(gsl::narrow_cast<int32_t>(i)), *reinterpret_cast<Foo*>(d4.As<RTTI*>(i)));
						Assert::AreEqual(*reinterpret_cast<Foo*>(d3.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d4.As<RTTI*>(i)));
						Assert::AreSame(*reinterpret_cast<Foo*>(d3.As<RTTI*>(i)), *reinterpret_cast<Foo*>(d4.As<RTTI*>(i)));
					}
					for (size_t i = 0; i < externalSize; ++i) {
						delete* (ext + i);
					}
					for (size_t i = 0; i < defaultSize; ++i) {
						delete* (foos + i);
					}
					free(ext);
					free(foos);
				}

			}
	
		}
		TEST_METHOD(ToString)
		{
			Datum i(1, Datum::DatumType::Integer);
			Datum f(1, Datum::DatumType::Float);
			Datum v(1, Datum::DatumType::Vector);
			Datum m(1, Datum::DatumType::Matrix);
			Datum s(1, Datum::DatumType::String);
			Datum p(1, Datum::DatumType::Pointer);

			i = 10;
			f = 10.f;
			v = glm::vec4(10.f, 10.f, 10.f, 10.f);
			m = glm::mat4(glm::vec4(10.f, 10.f, 10.f, 10.f), glm::vec4(10.f, 10.f, 10.f, 10.f), glm::vec4(10.f, 10.f, 10.f, 10.f), glm::vec4(10.f, 10.f, 10.f, 10.f));
			s = "string 10"s;
			Foo foo;
			char ptr[25];
			p = &foo;
			sprintf_s(ptr, "ptr %p", &foo);

			Assert::AreEqual("int 10"s, i.ToString(0));
			Assert::AreEqual("flt 10.000000"s, f.ToString(0));
			Assert::AreEqual("vec vec4(10.000000,10.000000,10.000000,10.000000)"s, v.ToString(0));
			Assert::AreEqual("mat mat4(vec4(10.000000,10.000000,10.000000,10.000000),vec4(10.000000,10.000000,10.000000,10.000000),vec4(10.000000,10.000000,10.000000,10.000000),vec4(10.000000,10.000000,10.000000,10.000000))"s, m.ToString(0));
			Assert::AreEqual("str string 10"s, s.ToString(0));
			Assert::AreEqual(std::string(ptr), p.ToString(0));
		}	
		TEST_METHOD(SetFromString)
		{
			Datum i(1, Datum::DatumType::Integer);
			Datum f(1, Datum::DatumType::Float);
			Datum v(1, Datum::DatumType::Vector);
			Datum m(1, Datum::DatumType::Matrix);
			Datum s(1, Datum::DatumType::String);
			Datum p(1, Datum::DatumType::Pointer);

			i.SetFromString("int 10"s);
			f.SetFromString("flt 10"s);
			v.SetFromString("vec vec4(10,10,10,10)"s);
			m.SetFromString("mat mat4(vec4(10,10,10,10),vec4(10,10,10,10),vec4(10,10,10,10),vec4(10,10,10,10))"s);
			s.SetFromString("str string 10"s);
			Foo* foo = new Foo(10);
			char ptr[25];
			sprintf_s(ptr, "ptr %p", foo);
			p.SetFromString(ptr);
			
			Assert::AreEqual(int32_t(10), i.As<int32_t>(0));
			Assert::AreEqual(float(10), f.As<float>(0));
			Assert::AreEqual(10.f, v.As<glm::vec4>(0).x);
			Assert::AreEqual(10.f, v.As<glm::vec4>(0).y);
			Assert::AreEqual(10.f, v.As<glm::vec4>(0).z);
			Assert::AreEqual(10.f, v.As<glm::vec4>(0).a);
			for (size_t l = 0; l < 4; ++l) {
				for (size_t j = 0; j < 4; ++j) {
					Assert::AreEqual(10.f, m.As<glm::mat4>(0)[glm::vec4::length_type(l)][glm::vec4::length_type(j)]);
				}
			}
			Assert::AreEqual("string 10"s, s.As<std::string>(0));
			Assert::AreSame(*foo, *reinterpret_cast<Foo*>(p.As<RTTI*>(0)));
			delete foo;
		}
		TEST_METHOD(Comparison)
		{
			// Compare different/same types
			{
				Datum i(1, Datum::DatumType::Integer);
				Datum f(1, Datum::DatumType::Float);
				Datum v(1, Datum::DatumType::Vector);
				Datum m(1, Datum::DatumType::Matrix);
				Datum s(1, Datum::DatumType::String);
				Datum p(1, Datum::DatumType::Pointer);

				Datum i1(i);
				Datum f1(f);
				Datum v1(v);
				Datum m1(m);
				Datum s1(s);
				Datum p1(p);

				Assert::IsTrue(i == i1);
				Assert::IsTrue(f == f1);
				Assert::IsTrue(v == v1);
				Assert::IsTrue(m == m1);
				Assert::IsTrue(s == s1);
				Assert::IsTrue(p == p1);
				{
					Assert::IsFalse(i == f1);
					Assert::IsFalse(i == v1);
					Assert::IsFalse(i == m1);
					Assert::IsFalse(i == s1);
					Assert::IsFalse(i == p1);

					Assert::IsTrue(i != f1);
					Assert::IsTrue(i != v1);
					Assert::IsTrue(i != m1);
					Assert::IsTrue(i != s1);
					Assert::IsTrue(i != p1);
				}
				{
					Assert::IsFalse(f == i1);
					Assert::IsFalse(f == v1);
					Assert::IsFalse(f == m1);
					Assert::IsFalse(f == s1);
					Assert::IsFalse(f == p1);

					Assert::IsTrue(f != i1);
					Assert::IsTrue(f != v1);
					Assert::IsTrue(f != m1);
					Assert::IsTrue(f != s1);
					Assert::IsTrue(f != p1);
				}
				{
					Assert::IsFalse(v == f1);
					Assert::IsFalse(v == i1);
					Assert::IsFalse(v == m1);
					Assert::IsFalse(v == s1);
					Assert::IsFalse(v == p1);

					Assert::IsTrue(v != f1);
					Assert::IsTrue(v != i1);
					Assert::IsTrue(v != m1);
					Assert::IsTrue(v != s1);
					Assert::IsTrue(v != p1);
				}
				{
					Assert::IsFalse(m == f1);
					Assert::IsFalse(m == v1);
					Assert::IsFalse(m == i1);
					Assert::IsFalse(m == s1);
					Assert::IsFalse(m == p1);

					Assert::IsTrue(m != f1);
					Assert::IsTrue(m != v1);
					Assert::IsTrue(m != i1);
					Assert::IsTrue(m != s1);
					Assert::IsTrue(m != p1);
				}
				{
					Assert::IsFalse(s == f1);
					Assert::IsFalse(s == v1);
					Assert::IsFalse(s == m1);
					Assert::IsFalse(s == i1);
					Assert::IsFalse(s == p1);

					Assert::IsTrue(s != f1);
					Assert::IsTrue(s != v1);
					Assert::IsTrue(s != m1);
					Assert::IsTrue(s != i1);
					Assert::IsTrue(s != p1);
				}
				{
					Assert::IsFalse(p == f1);
					Assert::IsFalse(p == v1);
					Assert::IsFalse(p == m1);
					Assert::IsFalse(p == i1);
					Assert::IsFalse(p == s1);

					Assert::IsTrue(p != f1);
					Assert::IsTrue(p != v1);
					Assert::IsTrue(p != m1);
					Assert::IsTrue(p != i1);
					Assert::IsTrue(p != s1);
				}
			}
			// Compare different/same storage states
			{
				Datum i(1, Datum::DatumType::Integer);
				Datum f(1, Datum::DatumType::Float);
				Datum v(1, Datum::DatumType::Vector);
				Datum m(1, Datum::DatumType::Matrix);
				Datum s(1, Datum::DatumType::String);
				Datum p(1, Datum::DatumType::Pointer);

				Datum i1(i);
				Datum f1(f);
				Datum v1(v);
				Datum m1(m);
				Datum s1(s);
				Datum p1(p);

				Datum i2(i);
				Datum f2(f);
				Datum v2(v);
				Datum m2(m);
				Datum s2(s);
				Datum p2(p);
				void* ptr = malloc(5 * sizeof(glm::mat4));
				i1.SetStorage(reinterpret_cast<int32_t*>(ptr), 0, 5);
				f1.SetStorage(reinterpret_cast<float*>(ptr), 0, 5);
				v1.SetStorage(reinterpret_cast<glm::vec4*>(ptr), 0, 5);
				m1.SetStorage(reinterpret_cast<glm::mat4*>(ptr), 0, 5);
				s1.SetStorage(reinterpret_cast<std::string*>(ptr), 0, 5);
				p1.SetStorage(reinterpret_cast<RTTI**>(ptr), 0, 5);


				i2.SetStorage(reinterpret_cast<int32_t*>(ptr), 0, 5);
				f2.SetStorage(reinterpret_cast<float*>(ptr), 0, 5);
				v2.SetStorage(reinterpret_cast<glm::vec4*>(ptr), 0, 5);
				m2.SetStorage(reinterpret_cast<glm::mat4*>(ptr), 0, 5);
				s2.SetStorage(reinterpret_cast<std::string*>(ptr), 0, 5);
				p2.SetStorage(reinterpret_cast<RTTI**>(ptr), 0, 5);

				Assert::IsFalse(i == i1);
				Assert::IsFalse(f == f1);
				Assert::IsFalse(v == v1);
				Assert::IsFalse(m == m1);
				Assert::IsFalse(s == s1);
				Assert::IsFalse(p == p1);

				Assert::IsTrue(i != i1);
				Assert::IsTrue(f != f1);
				Assert::IsTrue(v != v1);
				Assert::IsTrue(m != m1);
				Assert::IsTrue(s != s1);
				Assert::IsTrue(p != p1);

				Assert::IsTrue(i2 == i1);
				Assert::IsTrue(f2 == f1);
				Assert::IsTrue(v2 == v1);
				Assert::IsTrue(m2 == m1);
				Assert::IsTrue(s2 == s1);
				Assert::IsTrue(p2 == p1);

				Assert::IsFalse(i2 != i1);
				Assert::IsFalse(f2 != f1);
				Assert::IsFalse(v2 != v1);
				Assert::IsFalse(m2 != m1);
				Assert::IsFalse(s2 != s1);
				Assert::IsFalse(p2 != p1);

				free(ptr);
			}
			// Compare different/equal data
			{
				Datum i(1, Datum::DatumType::Integer);
				Datum f(1, Datum::DatumType::Float);
				Datum v(1, Datum::DatumType::Vector);
				Datum m(1, Datum::DatumType::Matrix);
				Datum s(1, Datum::DatumType::String);
				Datum p(1, Datum::DatumType::Pointer);

				Datum i1(i);
				Datum f1(f);
				Datum v1(v);
				Datum m1(m);
				Datum s1(s);
				Datum p1(p);
				
				i1.Set(int32_t(7));
				f1.Set(7.f);
				v1.Set(glm::vec4(7.f, 0.f, 0.f, 0.f));
				m1.Set(glm::mat4(glm::vec4(7.f, 0.f, 0.f, 0.f), glm::vec4(7.f, 0.f, 0.f, 0.f), glm::vec4(7.f, 0.f, 0.f, 0.f), glm::vec4(7.f, 0.f, 0.f, 0.f)));
				s1.Set("Hello"s);
				Foo* foo = new Foo(13);
				Foo* foo1 = new Foo(17);
				p1.Set(foo);

				Assert::IsTrue(i != i1);
				Assert::IsTrue(f != f1);
				Assert::IsTrue(v != v1);
				Assert::IsTrue(m != m1);
				Assert::IsTrue(s != s1);
				Assert::IsTrue(p != p1);

				Assert::IsFalse(i == i1);
				Assert::IsFalse(f == f1);
				Assert::IsFalse(v == v1);
				Assert::IsFalse(m == m1);
				Assert::IsFalse(s == s1);
				Assert::IsFalse(p == p1);

				Assert::IsTrue(i1 != int32_t(8));
				Assert::IsTrue(f1 != 8.f);
				Assert::IsTrue(v1 != glm::vec4(8.f, 0.f, 0.f, 0.f));
				Assert::IsTrue(m1 != glm::mat4(glm::vec4(8.f, 0.f, 0.f, 0.f), glm::vec4(8.f, 0.f, 0.f, 0.f), glm::vec4(8.f, 0.f, 0.f, 0.f), glm::vec4(8.f, 0.f, 0.f, 0.f)));
				Assert::IsTrue(s1 != "Goodbye"s);
				Assert::IsTrue(p1 != foo1);

				Assert::IsTrue(i1 != 8.f);
				Assert::IsTrue(f1 != int32_t(8));
				Assert::IsTrue(v1 != glm::mat4(glm::vec4(8.f, 0.f, 0.f, 0.f), glm::vec4(8.f, 0.f, 0.f, 0.f), glm::vec4(8.f, 0.f, 0.f, 0.f), glm::vec4(8.f, 0.f, 0.f, 0.f)));
				Assert::IsTrue(m1 != glm::vec4(8.f, 0.f, 0.f, 0.f));
				Assert::IsTrue(s1 != foo1);
				Assert::IsTrue(p1 != "Goodbye"s);

				Assert::IsTrue(i1 == int32_t(7));
				Assert::IsTrue(f1 == 7.f);
				Assert::IsTrue(v1 == glm::vec4(7.f, 0.f, 0.f, 0.f));
				Assert::IsTrue(m1 == glm::mat4(glm::vec4(7.f, 0.f, 0.f, 0.f), glm::vec4(7.f, 0.f, 0.f, 0.f), glm::vec4(7.f, 0.f, 0.f, 0.f), glm::vec4(7.f, 0.f, 0.f, 0.f)));
				Assert::IsTrue(s1 == "Hello"s);
				Assert::IsTrue(p1 == foo);

				p.Set(foo1);
				Assert::IsFalse(p == p1);
				Assert::IsTrue(p != p1);
				p.Set(foo);
				Assert::IsTrue(p == p1);
				Assert::IsFalse(p != p1);
				delete foo;
				delete foo1;
			}
		}
		inline static _CrtMemState _startMemState;
	};
}