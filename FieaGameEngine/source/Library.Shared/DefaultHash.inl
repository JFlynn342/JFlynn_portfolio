#include <string>

using namespace fge;

template<typename TKey>
inline size_t DefaultHash<TKey>::operator()(TKey value) const {
	unsigned char* b = reinterpret_cast<unsigned char*>(&value);
	size_t hash = 0;
	for (size_t i = 0; i < sizeof(value); ++i) {
		hash += *b;
	}
	return hash;
}

inline size_t DefaultHash<std::string>::operator()(std::string value) const {
	size_t hash = 0;
	for (std::string::iterator it = value.begin(); it < value.end(); ++it) {
		hash += *it;
	}
	return hash;
}

inline size_t DefaultHash<char*>::operator()(char* value) const {
	
	size_t hash = 0;
	for (size_t i = 0; i < strlen(value); ++i) {
		char c = value[i];
		hash += c;
	}
	return hash;
}
