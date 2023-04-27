#pragma once
#include <cstdint>
#include "DefaultEquality.h"
#include "DefaultHash.h"
namespace UnitTests
{
	class Bar final
	{
	public:
		explicit Bar(std::int32_t data = 0);
		Bar(const Bar& rhs);
		Bar(Bar&& rhs) noexcept;
		Bar& operator=(const Bar& rhs);
		Bar& operator=(Bar&& rhs) noexcept;
		virtual ~Bar();

		std::int32_t Data() const;
		void SetData(std::int32_t data);

	private:
		std::int32_t* _data;
	};
}




