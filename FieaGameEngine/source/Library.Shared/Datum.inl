#include <stdexcept>
#include "Datum.h"
namespace fge {

	template<>
	inline Datum::integer_type& Datum::As<Datum::integer_type>(const size_t index) {
		if (_type != DatumType::Integer) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._int + index);
	}
	template<>
	inline Datum::float_type& Datum::As<Datum::float_type>(const size_t index) {
		if (_type != DatumType::Float) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._float + index);
	}
	template<>
	inline Datum::vector_type& Datum::As<Datum::vector_type>(const size_t index) {
		if (_type != DatumType::Vector) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._vec + index);
	}
	template<>
	inline Datum::matrix_type& Datum::As<Datum::matrix_type>(const size_t index) {
		if (_type != DatumType::Matrix) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._mat + index);
	}
	template<>
	inline Datum::table_type& Datum::As<Datum::table_type>(const size_t index) {
		if (_type != DatumType::Table) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._tbl + index);
	}
	template<>
	inline Datum::string_type& Datum::As<Datum::string_type>(const size_t index) {
		if (_type != DatumType::String) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._str + index);
	}
	template<>
	inline Datum::pointer_type& Datum::As<Datum::pointer_type>(const size_t index) {
		if (_type != DatumType::Pointer) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._poi + index);
	}
	template<>
	inline const Datum::integer_type& Datum::As<Datum::integer_type>(const size_t index) const {
		if (_type != DatumType::Integer) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._int + index);
	}
	template<>
	inline const Datum::float_type& Datum::As<Datum::float_type>(const size_t index) const {
		if (_type != DatumType::Float) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._float + index);
	}
	template<>
	inline const Datum::vector_type& Datum::As<Datum::vector_type>(const size_t index) const {
		if (_type != DatumType::Vector) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._vec + index);
	}
	template<>
	inline const Datum::matrix_type& Datum::As<Datum::matrix_type>(const size_t index) const {
		if (_type != DatumType::Matrix) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._mat + index);
	}
	template<>
	inline const Datum::table_type& Datum::As<Datum::table_type>(const size_t index) const {
		if (_type != DatumType::Table) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._tbl + index);
	}
	template<>
	inline const Datum::string_type& Datum::As<Datum::string_type>(const size_t index) const {
		if (_type != DatumType::String) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._str + index);
	}
	template<>
	inline const Datum::pointer_type& Datum::As<Datum::pointer_type>(const size_t index) const {
		if (_type != DatumType::Pointer) {
			throw std::invalid_argument("invalid type argument");
		}
		if (!_hasExternalStorage && (index >= _size || index < 0)) {
			throw std::out_of_range("attempted access to uninitialized element");
		}
		return *(_array._poi + index);
	}
	
	template<>
	inline Datum::integer_type& Datum::Front<Datum::integer_type>() {
		return As<integer_type>(0);
	}
	template<>
	inline Datum::float_type& Datum::Front<Datum::float_type>() {
		return As<float_type>(0);
	}
	template<>
	inline Datum::vector_type& Datum::Front<Datum::vector_type>() {
		return As<vector_type>(0);
	}
	template<>
	inline Datum::matrix_type& Datum::Front<Datum::matrix_type>() {
		return As<matrix_type>(0);
	}
	template<>
	inline Datum::string_type& Datum::Front<Datum::string_type>() {
		return As<string_type>(0);
	}
	template<>
	inline Datum::pointer_type& Datum::Front<Datum::pointer_type>() {
		return As<pointer_type>(0);
	}
	template<>
	inline const Datum::integer_type& Datum::Front<Datum::integer_type>() const {
		return As<integer_type>(0);
	}
	template<>
	inline const Datum::float_type& Datum::Front<Datum::float_type>() const {
		return As<float_type>(0);
	}
	template<>
	inline const Datum::vector_type& Datum::Front<Datum::vector_type>() const {
		return As<vector_type>(0);
	}
	template<>
	inline const Datum::matrix_type& Datum::Front<Datum::matrix_type>() const {
		return As<matrix_type>(0);
	}
	template<>
	inline const Datum::string_type& Datum::Front<Datum::string_type>() const {
		return As<string_type>(0);
	}
	template<>
	inline const Datum::pointer_type& Datum::Front<Datum::pointer_type>() const {
		return As<pointer_type>(0);
	}
	template<>
	inline Datum::integer_type& Datum::Back<Datum::integer_type>() {
		return As<integer_type>(_size - 1);
	}
	template<>
	inline Datum::float_type& Datum::Back<Datum::float_type>() {
		return As<float_type>(_size - 1);
	}
	template<>
	inline Datum::vector_type& Datum::Back<Datum::vector_type>() {
		return As<vector_type>(_size - 1);
	}
	template<>
	inline Datum::matrix_type& Datum::Back<Datum::matrix_type>() {
		return As<matrix_type>(_size - 1);
	}
	template<>
	inline Datum::table_type& Datum::Back<Datum::table_type>() {
		return As<table_type>(_size - 1);
	}
	template<>
	inline Datum::string_type& Datum::Back<Datum::string_type>() {
		return As<string_type>(_size - 1);
	}
	template<>
	inline Datum::pointer_type& Datum::Back<Datum::pointer_type>() {
		return As<pointer_type>(_size - 1);
	}
	template<>
	inline const Datum::integer_type& Datum::Back<Datum::integer_type>() const {
		return As<integer_type>(_size - 1);
	}
	template<>
	inline const Datum::float_type& Datum::Back<Datum::float_type>() const {
		return As<float_type>(_size - 1);
	}
	template<>
	inline const Datum::vector_type& Datum::Back<Datum::vector_type>() const {
		return As<vector_type>(_size - 1);
	}
	template<>
	inline const Datum::matrix_type& Datum::Back<Datum::matrix_type>() const {
		return As<matrix_type>(_size - 1);
	}
	template<>
	inline const Datum::table_type& Datum::Back<Datum::table_type>() const {
		return As<table_type>(_size - 1);
	}
	template<>
	inline const Datum::string_type& Datum::Back<Datum::string_type>() const {
		return As<string_type>(_size - 1);
	}
	template<>
	inline const Datum::pointer_type& Datum::Back<Datum::pointer_type>() const {
		return As<pointer_type>(_size - 1);
	}
	template<>
	inline std::pair<bool, Datum::integer_type*> Datum::Find<Datum::integer_type>(integer_type value)
	{
		for (size_t i = 0; i < _size; ++i) {
			integer_type* temp = &As<integer_type>(i);
			if (*temp == value) {
				return std::pair<bool, integer_type*>(true, temp);
			}
		}
		return std::pair<bool, integer_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, Datum::float_type*> Datum::Find<Datum::float_type>(float_type value)
	{
		for (size_t i = 0; i < _size; ++i) {
			float_type* temp = &As<float_type>(i);
			if (*temp == value) {
				return std::pair<bool, float_type*>(true, temp);
			}
		}
		return std::pair<bool, float_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, Datum::vector_type*> Datum::Find<Datum::vector_type>(vector_type value)
	{
		for (size_t i = 0; i < _size; ++i) {
			vector_type* temp = &As<vector_type>(i);
			if (*temp == value) {
				return std::pair<bool, vector_type*>(true, temp);
			}
		}
		return std::pair<bool, vector_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, Datum::matrix_type*> Datum::Find<Datum::matrix_type>(matrix_type value)
	{
		for (size_t i = 0; i < _size; ++i) {
			matrix_type* temp = &As<matrix_type>(i);
			if (*temp == value) {
				return std::pair<bool, matrix_type*>(true, temp);
			}
		}
		return std::pair<bool, matrix_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, Datum::table_type*> Datum::Find(table_type value)
	{
		for (size_t i = 0; i < _size; ++i) {
			table_type* temp = &As<table_type>(i);
			if (*temp == value) {
				return std::pair<bool, table_type*>(true, temp);
			}
		}
		return std::pair<bool, table_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, Datum::string_type*> Datum::Find<Datum::string_type>(string_type value)
	{
		for (size_t i = 0; i < _size; ++i) {
			string_type* temp = &As<string_type>(i);
			if (*temp == value) {
				return std::pair<bool, string_type*>(true, temp);
			}
		}
		return std::pair<bool, string_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, Datum::pointer_type*> Datum::Find<Datum::pointer_type>(pointer_type value)
	{
		for (size_t i = 0; i < _size; ++i) {
			pointer_type* temp = &As<pointer_type>(i);
			if (*temp == value) {
				return std::pair<bool, pointer_type*>(true, temp);
			}
		}
		return std::pair<bool, pointer_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, const Datum::integer_type* const> Datum::Find<Datum::integer_type>(integer_type value) const
	{
		for (size_t i = 0; i < _size; ++i) {
			const integer_type* const temp = &As<integer_type>(i);
			if (*temp == value) {
				return std::pair<bool, const integer_type* const>(true, temp);
			}
		}
		return std::pair<bool, const integer_type* const>(false, nullptr);
	}
	template<>
	inline std::pair<bool, const Datum::float_type* const> Datum::Find<Datum::float_type>(float_type value) const
	{
		for (size_t i = 0; i < _size; ++i) {
			const float_type* const temp = &As<float_type>(i);
			if (*temp == value) {
				return std::pair<bool, const float_type* const>(true, temp);
			}
		}
		return std::pair<bool, const float_type* const>(false, nullptr);
	}
	template<>
	inline std::pair<bool, const Datum::vector_type* const> Datum::Find<Datum::vector_type>(vector_type value) const
	{
		for (size_t i = 0; i < _size; ++i) {
			const vector_type* const temp = &As<vector_type>(i);
			if (*temp == value) {
				return std::pair<bool, const vector_type* const>(true, temp);
			}
		}
		return std::pair<bool, const vector_type* const>(false, nullptr);
	}
	template<>
	inline std::pair<bool, const Datum::matrix_type* const> Datum::Find<Datum::matrix_type>(matrix_type value) const
	{
		for (size_t i = 0; i < _size; ++i) {
			const matrix_type* const temp = &As<matrix_type>(i);
			if (*temp == value) {
				return std::pair<bool, const matrix_type* const>(true, temp);
			}
		}
		return std::pair<bool, const matrix_type* const>(false, nullptr);
	}
	template<>
	inline std::pair<bool, const Datum::table_type* const> Datum::Find(table_type value) const
	{
		for (size_t i = 0; i < _size; ++i) {
			const table_type* temp = &As<table_type>(i);
			if (*temp == value) {
				return std::pair<bool, const table_type*>(true, temp);
			}
		}
		return std::pair<bool, table_type*>(false, nullptr);
	}
	template<>
	inline std::pair<bool, const Datum::string_type* const> Datum::Find<Datum::string_type>(string_type value) const
	{
		for (size_t i = 0; i < _size; ++i) {
			const string_type* const temp = &As<string_type>(i);
			if (*temp == value) {
				return std::pair<bool, const string_type* const>(true, temp);
			}
		}
		return std::pair<bool, const string_type* const>(false, nullptr);
	}
	template<>
	inline std::pair<bool, const Datum::pointer_type* const> Datum::Find<Datum::pointer_type>(pointer_type value) const
	{
		for (size_t i = 0; i < _size; ++i) {
			const pointer_type* const temp = &As<pointer_type>(i);
			if (*temp == value) {
				return std::pair<bool, const pointer_type* const>(true, temp);
			}
		}
		return std::pair<bool, const pointer_type* const>(false, nullptr);
	}
	template<>
	inline void Datum::RemoveAt<Datum::integer_type>(size_t index) {
		if (index >= _size || index < 0) {
			throw std::out_of_range("invalid index");
		}
		if (_type != DatumType::Integer) {
			throw std::invalid_argument("invalid type parameter");
		}
		if (index == _size - 1) {
			PopBack();
		}
		else {
			memmove(_array._int + index, _array._int + index + 1, sizeof(integer_type) * (_size - index));
			--_size;
		}

	}
	template<>
	inline void Datum::RemoveAt<Datum::float_type>(size_t index) {
		if (index >= _size || index < 0) {
			throw std::out_of_range("invalid index");
		}
		if (_type != DatumType::Float) {
			throw std::invalid_argument("invalid type parameter");
		}
		if (index == _size - 1) {
			PopBack();
		}
		else {
			memmove(_array._float + index, _array._float + index + 1, sizeof(float_type) * (_size - index));
			--_size;
		}

	}
	template<>
	inline void Datum::RemoveAt<Datum::vector_type>(size_t index) {
		if (index >= _size || index < 0) {
			throw std::out_of_range("invalid index");
		}
		if (_type != DatumType::Vector) {
			throw std::invalid_argument("invalid type parameter");
		}
		if (index == _size - 1) {
			PopBack();
		}
		else {
			memmove(_array._vec + index, _array._vec + index + 1, sizeof(vector_type) * (_size - index));
			--_size;
		}

	}
	template<>
	inline void Datum::RemoveAt<Datum::matrix_type>(size_t index) {
		if (index >= _size || index < 0) {
			throw std::out_of_range("invalid index");
		}
		if (_type != DatumType::Matrix) {
			throw std::invalid_argument("invalid type parameter");
		}
		if (index == _size - 1) {
			PopBack();
		}
		else {
			memmove(_array._mat + index, _array._mat + index + 1, sizeof(matrix_type) * (_size - index));
			--_size;
		}

	}
	template<>
	inline void Datum::RemoveAt<Datum::string_type>(size_t index) {
		if (index >= _size || index < 0) {
			throw std::out_of_range("invalid index");
		}
		if (_type != DatumType::String) {
			throw std::invalid_argument("invalid type parameter");
		}
		if (index == _size - 1) {
			PopBack();
		}
		else {
			(_array._str + index)->~string_type();
			memmove(_array._str + index, _array._str + index + 1, sizeof(string_type) * (_size - index));
			--_size;
		}

	}
	template<>
	inline void Datum::RemoveAt<Datum::pointer_type>(size_t index) {
		if (index >= _size || index < 0) {
			throw std::out_of_range("invalid index");
		}
		if (_type != DatumType::Pointer) {
			throw std::invalid_argument("invalid type parameter");
		}
		if (index == _size - 1) {
			PopBack();
		}
		else {
			memmove(_array._poi + index, _array._poi + index + 1, sizeof(pointer_type) * (_size - index));
			--_size;
		}
	}
};