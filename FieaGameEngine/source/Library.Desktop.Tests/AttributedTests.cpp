#include "AttributedFoo.h"
#include "CppUnitTest.h"
#include "GameObject.h"
#include "Action.h"
#include "Factory.h"
#include "GameObjectFoo.h"
#include "ActionFoo.h"
#include "Reaction.h"
#include "ReactionAttributed.h"
#include "EventMessageAttributed.h"
#pragma warning (push)
#pragma warning(disable:4201)
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)

namespace Microsoft::VisualStudio::CppUnitTestFramework {
	using namespace fge;
	using namespace UnitTests;
	using namespace std::string_literals;
	template<>
	std::wstring ToString<AttributedFoo>(const UnitTests::AttributedFoo&) {

		RETURN_WIDE_STRING(L"AttributedFoo");
	}
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
	TEST_MODULE_INITIALIZE(ModuleInit) {
		TypeManager::CreateInstance();
		TypeManager::RegisterTypes(AttributedFoo::TypeIdClass(), AttributedFoo::Signatures());
		TypeManager::RegisterTypes(GameObject::TypeIdClass(), GameObject::Signatures());
		TypeManager::RegisterTypes(Action::TypeIdClass(), Action::Signatures());
		TypeManager::RegisterTypes(ActionList::TypeIdClass(), ActionList::Signatures());
		TypeManager::RegisterTypes(ActionIf::TypeIdClass(), ActionIf::Signatures());
		TypeManager::RegisterTypes(ActionEvent::TypeIdClass(), ActionEvent::Signatures());
		TypeManager::RegisterTypes(EventMessageAttributed::TypeIdClass(), EventMessageAttributed::Signatures());
		TypeManager::RegisterTypes(ReactionAttributed::TypeIdClass(), ReactionAttributed::Signatures());

		new GameObjectFooFactory;
		new ActionFooFactory;
		new ActionListFactory;
		new ActionIfFactory;
		new ActionEventFactory;
		new ReactionAttributedFactory;
	}
	TEST_MODULE_CLEANUP(ModuleCleanup) {
		TypeManager::DestroyInstance();
	}
	TEST_CLASS(AttributedTests)
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
		TEST_METHOD(Population) {
			AttributedFoo f;
			Assert::AreSame(f, *static_cast<AttributedFoo*>(f.Find("this")->As<RTTI*>()));
			Assert::IsNotNull(f.Find("Table")->As<Scope*>());
			Assert::AreEqual(0, f.Find("ExternalInt")->As<int32_t>());
			Assert::AreEqual(0.f, f.Find("ExternalFloat")->As<float>());
			Assert::AreEqual(glm::to_string(glm::vec4()), glm::to_string(f.Find("ExternalVector")->As<glm::vec4>()));
			Assert::AreEqual(std::string(), f.Find("ExternalString")->As<std::string>());
			Assert::AreEqual(glm::to_string(glm::mat4()), glm::to_string(f.Find("ExternalMatrix")->As<glm::mat4>()));

			Assert::IsTrue(f.IsAttribute("ExternalIntArray"));
			Assert::IsTrue(f.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(f.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(f.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(f.IsAttribute("ExternalMatrixArray"));
		}
		TEST_METHOD(Copy) {
			{
				AttributedFoo f;
				f._externalInt = 1;
				AttributedFoo f1(f);
				Assert::AreEqual(1, f1._externalInt);
				Assert::AreNotSame(f, f1);
				Assert::AreEqual(f.Find("ExternalInt")->As<int32_t>(), f1.Find("ExternalInt")->As<int32_t>());
				Assert::AreSame(f1, *static_cast<AttributedFoo*>(f1.Find("this")->As<RTTI*>()));
				Assert::AreNotSame(*f.Find("Table")->As<Scope*>(), *f1.Find("Table")->As<Scope*>());
			}
			{
				AttributedFoo f;
				f._externalInt = 1;
				AttributedFoo f1;
				f1 = f;
				Assert::AreEqual(1, f1._externalInt);
			}
		}
		TEST_METHOD(Move) {
			{
				AttributedFoo f;
				f._externalInt = 1;
				AttributedFoo f1(f);
				AttributedFoo f2(std::move(f));
				Assert::AreEqual(1, f2._externalInt);
				Assert::AreNotSame(f1, f2);
				Assert::AreEqual(f1.Find("ExternalInt")->As<int32_t>(), f2.Find("ExternalInt")->As<int32_t>());
				Assert::AreSame(f1, *static_cast<AttributedFoo*>(f1.Find("this")->As<RTTI*>()));
			}
			{
				AttributedFoo f;
				f._externalInt = 1;
				AttributedFoo f1(f);
				AttributedFoo f2;
				f2 = std::move(f);
				Assert::AreEqual(1, f2._externalInt);
				Assert::AreNotSame(f1, f2);
				Assert::AreEqual(f1.Find("ExternalInt")->As<int32_t>(), f2.Find("ExternalInt")->As<int32_t>());
			}
		}
		TEST_METHOD(Accessors) {
			AttributedFoo f;
			Assert::IsNull(f.GetFirstAuxiliaryAttribute().second);
			Assert::IsNull(f.GetLastAuxiliaryAttribute().second);
			Assert::AreEqual(size_t(12), f.GetAllAttributes().size());
			Datum& d = f.AppendAuxiliaryAttribute("Auxiliary");
			Datum& d1 = f.AppendAuxiliaryAttribute("Auxiliary1");
			Assert::AreEqual(size_t(12), f.GetFirstAuxiliaryAttribute().first);
			Assert::AreEqual(size_t(13), f.GetLastAuxiliaryAttribute().first);
			Assert::AreSame(d, *f.GetFirstAuxiliaryAttribute().second);
			Assert::AreSame(d1, *f.GetLastAuxiliaryAttribute().second);
		}
		TEST_METHOD(IsAttribute) {
			AttributedFoo f;
			Assert::IsTrue(f.IsAttribute("ExternalInt"));
			Assert::IsTrue(f.IsAttribute("ExternalFloat"));
			Assert::IsTrue(f.IsAttribute("ExternalVector"));
			Assert::IsTrue(f.IsAttribute("ExternalString"));
			Assert::IsTrue(f.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(f.IsAttribute("ExternalIntArray"));
			Assert::IsTrue(f.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(f.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(f.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(f.IsAttribute("ExternalMatrixArray"));
			
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInt"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalIntArray"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(f.IsPrescribedAttribute("ExternalMatrixArray"));


			f.AppendAuxiliaryAttribute("Auxiliary");
			
			Assert::IsTrue(f.IsAttribute("Auxiliary"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("Auxiliary"));
			Assert::IsFalse(f.IsPrescribedAttribute("Auxiliary"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInt"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalVector"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalMatrix"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalIntArray"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalMatrixArray"));
		}
		inline static _CrtMemState _startMemState;
	};
}
