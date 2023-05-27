#include "pch.h"
#include "RTTI.h"

namespace fge
{
	std::string RTTI::ToString() const
	{
		using namespace std::string_literals;
		return "RTTI"s;
	}

	bool RTTI::Equals(const RTTI* rhs) const
	{
		return this == rhs;
	}
}