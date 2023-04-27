#pragma once
#include <string>

namespace fge {
	template<typename TKey>
	struct DefaultHash final {
	public:
		size_t operator()(TKey value) const;
	};

	template<>
	struct DefaultHash<std::string> final {
		size_t operator()(std::string value) const;
	};

	template<>
	struct DefaultHash<char*> final {
		size_t operator()(char* value) const;
	};
}

#include "DefaultHash.inl"