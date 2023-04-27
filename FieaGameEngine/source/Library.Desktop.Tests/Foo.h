#pragma once
#include <cstdint>
#include "DefaultHash.h"
#include "DefaultEquality.h"
#include "RTTI.h"
namespace UnitTests
{
	class Foo final : public RTTI {
		RTTI_DECLARATIONS(Foo, RTTI);
	public:
		
		explicit Foo(std::int32_t data = 0);
		Foo(const Foo& rhs);
		Foo(Foo&& rhs) noexcept;
		Foo& operator=(const Foo& rhs);
		Foo& operator=(Foo&& rhs) noexcept;
		virtual ~Foo();

		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;

		std::int32_t Data() const;
		void SetData(std::int32_t data);

		bool Equals(const RTTI* rhs) const;
	private:
		std::int32_t* _data;
	};
	
}
namespace fge {
	inline size_t DefaultHash<UnitTests::Foo>::operator()(UnitTests::Foo value) const {
		size_t hash = value.Data();
		return hash;
	}
}
