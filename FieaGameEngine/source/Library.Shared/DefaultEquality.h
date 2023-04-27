#pragma once
#include <string>
namespace fge {
	template<typename T>
	struct DefaultEquality final {
	public:
		bool operator()(const T& lhs, const T& rhs) const {
			return lhs == rhs;
		};
	};
	template<typename T1, typename T2>
	struct DefaultEquality<std::pair<T1, T2>> final {
		bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
			return DefaultEquality<T1>()(lhs.first, rhs.first) && DefaultEquality<T2>()(lhs.second, rhs.second);
		}
	};
	template<>
	struct DefaultEquality<char*> final {
		bool operator()(const char* lhs, const char* rhs) const {
			std::string lstring = lhs;
			std::string rstring = rhs;
			return DefaultEquality<std::string>()(lstring, rstring);
		}
	};
}