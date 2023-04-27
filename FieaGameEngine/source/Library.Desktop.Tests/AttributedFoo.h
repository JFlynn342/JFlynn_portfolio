#pragma once
#include "Attributed.h"
#include "Factory.h"
namespace UnitTests {
	class AttributedFoo : public Attributed {
		RTTI_DECLARATIONS(AttributedFoo, Attributed);
	public:
		static const size_t _arraySize = 5;
		AttributedFoo();
		AttributedFoo(const AttributedFoo& other) = default;
		AttributedFoo(AttributedFoo&& other) noexcept = default;
		AttributedFoo& operator=(const AttributedFoo& other) = default;
		AttributedFoo& operator=(AttributedFoo&& other) noexcept = default;
		~AttributedFoo() = default;

		int _externalInt = 0;
		float _externalFloat = 0.f;
		std::string _externalString;
		glm::vec4 _externalVector;
		glm::mat4 _externalMatrix;


		int _externalIntArray[_arraySize];
		float _externalFloatArray[_arraySize];
		std::string _externalStringArray[_arraySize];
		glm::vec4 _externalVectorArray[_arraySize];
		glm::mat4 _externalMatrixArray[_arraySize];

		static Vector<Signature> Signatures();
		[[nodiscard]] Scope* Clone() const override;
	};
	ConcreteFactory(AttributedFoo, Scope);
}


