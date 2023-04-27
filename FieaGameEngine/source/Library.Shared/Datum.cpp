#include "Datum.h"
#include <stdexcept>

namespace fge {
	using namespace std::string_literals;
	Scope& Datum::operator[](uint32_t index){
		return *As<table_type>(index);
	}
	Datum::Datum(size_t startSize, DatumType type) {
		
	
		SetType(type);
		if (_type != DatumType::Unknown) {
			Resize(startSize);
		}
		
	}
	Datum::~Datum() {
		if (!_hasExternalStorage && _array._vp != nullptr) {
			Clear();
			free(_array._vp);
		}
	}

	Datum::Datum(const Datum& other) :
		_type{ other._type } {


		if (_hasExternalStorage) {
			_array._vp = other._array._vp;
		}
		else if (!other._hasExternalStorage) {
			Clear();
			Resize(other._capacity);
			if (_type == DatumType::String) {
				for (size_t i = 0; i < other._size; ++i) {
					Set(other.As<string_type>(i), i);
				}
			}
			else { 
				memcpy(_array._vp, other._array._vp, _capacity * _capacityTable[(int)_type]);
			}
			_size = other._size;
		}
		else {
			_hasExternalStorage = true;
			_array._vp = other._array._vp;
			_capacity = other._capacity;
			_size = other._size;
		}
	}

	Datum& Datum::operator=(Datum& other)
	{
		if (&other == this) {
			throw std::invalid_argument("attempted self-assignment");
		}
		_type = other._type;


		if (!_hasExternalStorage) {
			Clear();
			free(_array._vp);
		}
		if (other._hasExternalStorage) {
			_hasExternalStorage = true;
			_array._vp = other._array._vp;
			_size = other._size;
			_capacity = other._capacity;
		}
		else if (_type == DatumType::String) {
			Resize(other._capacity);
			for (size_t i = 0; i < other._size; ++i) {
				Set(other.As<string_type>(i), i);
			}
		}
		else {
			Resize(other._capacity);
			memcpy(_array._vp, other._array._vp, _capacity * _capacityTable[(int)_type]);
		}
		return *this;
	}

	Datum::Datum(Datum&& other) noexcept {
		_array._vp = other._array._vp;
		if (other._hasExternalStorage) {
			_hasExternalStorage = true;
		}
		else {
			other._array._vp = nullptr;
		}
		_type = other._type;
		_capacity = other._capacity;
		_size = other._size;
	}

	Datum& Datum::operator=(Datum&& other) noexcept {
		if (!_hasExternalStorage) {
			Clear();
			free(_array._vp);
		}
		_array._vp = other._array._vp;
		if (other._hasExternalStorage) {
			_hasExternalStorage = true;
		}
		else {
			other._array._vp = nullptr;
		}
		_type = other._type;
		_capacity = other._capacity;
		_size = other._size;
		return *this;
	}

	Datum& Datum::operator=(integer_type newValue) {
		if (_type != DatumType::Unknown && _type != DatumType::Integer) {
			throw std::invalid_argument("invalid assignment");
		}
		if (_type == DatumType::Unknown) {
			SetType(DatumType::Integer);
			Resize(1);
		}

		Set(newValue);

		return *this;
	}

	Datum& Datum::operator=(float_type newValue) {
		if (_type != DatumType::Unknown && _type != DatumType::Float) {
			throw std::invalid_argument("invalid assignment");
		}
		if (_type == DatumType::Unknown) {
			SetType(DatumType::Float);
			Resize(1);
		}

		Set(newValue);
		return *this;
	}

	Datum& Datum::operator=(vector_type newValue) {
		if (_type != DatumType::Unknown && _type != DatumType::Vector) {
			throw std::invalid_argument("invalid assignment");
		}
		if (_type == DatumType::Unknown) {
			SetType(DatumType::Vector);
			Resize(1);
		}

		Set(newValue);
		return *this;
	}

	Datum& Datum::operator=(matrix_type newValue) {
		if (_type != DatumType::Unknown && _type != DatumType::Matrix) {
			throw std::invalid_argument("invalid assignment");
		}
		if (_type == DatumType::Unknown) {
			SetType(DatumType::Matrix);
			Resize(1);
		}

		Set(newValue);
		return *this;
	}


	Datum& Datum::operator=(pointer_type newValue) {
		if (_type != DatumType::Unknown && _type != DatumType::Pointer) {
			throw std::invalid_argument("invalid assignment");
		}
		if (_type == DatumType::Unknown) {
			SetType(DatumType::Pointer);
			Resize(1);
		}

		Set(newValue);
		return *this;
	}

	Datum& Datum::operator=(string_type newValue) {
		if (_type != DatumType::Unknown && _type != DatumType::String) {
			throw std::invalid_argument("invalid assignment");
		}
		if (_type == DatumType::Unknown) {
			SetType(DatumType::String);
			Resize(1);
		}

		Set(newValue);
		return *this;
	}

	Datum::DatumType Datum::Type() const {
		return _type;
	}

	void Datum::SetType(DatumType newType) {
		if (_type != DatumType::Unknown && _type != newType) {
			throw std::invalid_argument("Cannot set type of Datum with type already set");
		}
		_type = newType;
	}

	size_t Datum::Capacity() const {
		return _capacity;
	}

	void Datum::Resize(size_t newSize) {
		if (_hasExternalStorage) {
			throw std::runtime_error("cannot resize external storage");
		}
		if (newSize > _capacity) {
			Reserve(newSize);
			if (_type == DatumType::String) {
				for (size_t i = _size; i < newSize; ++i) {
					PushBack(string_type());
				}
			}
			else {
				memset(reinterpret_cast<std::byte*>(_array._vp) + (_size * _capacityTable[(int)_type]), 0, ((newSize - _size) * _capacityTable[(int)_type]));
				_size = newSize;
			}
		}
		if (newSize < _size) {
			
			for (size_t i = _size; i > newSize; --i) {
				PopBack();
			}
			ShrinkToFit();

		}
		
		assert(_size == newSize);
		_capacity = newSize;
	}

	void Datum::Clear() {
		if (_array._vp != nullptr) {
			while (_size > 0) {
				PopBack();
			}
		}

	}

	size_t Datum::Size() const {
		return _size;
	}

	void Datum::SetStorage(void* newStorage, size_t pop, size_t size) {
		assert(_type != DatumType::Unknown && _type != DatumType::Table);
		if (!_hasExternalStorage) {
			Clear();
			free(_array._vp);
		}
		_hasExternalStorage = true;
		_size = pop;
		_capacity = size;
		_array._vp = newStorage;
	}

	

	

	

	bool Datum::operator!=(const Datum& other) const {
		if (_hasExternalStorage && other._hasExternalStorage) {
			return(!(_type == other._type && _size == other._size && _array._vp == other._array._vp));
		}
		else if (!_hasExternalStorage && !other._hasExternalStorage)
		{
			if (_type != DatumType::String && other._type != DatumType::String) {
				if (_size == other._size && _type == other._type) {
					if (_type == DatumType::Table && other._type == DatumType::Table) {
						for (size_t i = 0; i < _size; ++i) {
							if (*(_array._tbl + i) != nullptr && *(other._array._tbl + i) != nullptr) {
								if (!(*(_array._poi + i))->Equals(*(other._array._poi + i))) {
									return true;
								}
							}
							else {
								if (_array._tbl + i != other._array._tbl + i) {
									return true;
								}
							}

						}
						return false;
					}
					if (_type == DatumType::Pointer && other._type == DatumType::Pointer) {
						for (size_t i = 0; i < _size; ++i) {
							if (*(_array._poi + i) != nullptr && *(other._array._poi + i) != nullptr) {
								if (!((*(_array._poi + i))->Equals(*(other._array._poi + i)))) {
									return true;
								}
							}
							else {
								if (*_array._poi + i != *other._array._poi + i) {
									return true;
								}
							}

						}
						return false;
					}
					else return memcmp(_array._vp, other._array._vp, _size * _capacityTable[(int)_type]) != 0;
				}
			}
			else if(_size == other._size && _type == other._type){
				for (size_t i = 0; i < _size; ++i) {
					if (*(_array._str + i) != *(other._array._str + i)) {
						return true;
					}
				}
				return false;
			}	
			
		}
		return true;
	}

	bool Datum::operator!=(const integer_type other) const {
		if (_type == DatumType::Integer) {
			return(As<integer_type>(0) != other);
		}
		return true;
	}

	bool Datum::operator!=(const float_type other) const {
		if (_type == DatumType::Float) {
			return(As<float_type>(0) != other);
		}
		return true;
	}

	bool Datum::operator!=(const vector_type other) const {
		if (_type == DatumType::Vector) {
			return(As<vector_type>(0) != other);
		}
		return true;
	}

	bool Datum::operator!=(const matrix_type other) const {
		if (_type == DatumType::Matrix) {
			return(As<matrix_type>(0) != other);
		}
		return true;
	}

	bool Datum::operator!=(const string_type other) const {
		if (_type == DatumType::String) {
			return(As<string_type>(0) != other);
		}
		return true;
	}

	bool Datum::operator!=(const pointer_type other) const {
		if (_type == DatumType::Pointer) {
			return(As<pointer_type>(0) != other);
		}
		return true;
	}

	bool Datum::operator==(const Datum& other) const
	{
		return !(*this != other);
	}

	bool Datum::operator==(const integer_type other) const
	{
		return !(*this != other);
	}

	bool Datum::operator==(const float_type other) const
	{
		return !(*this != other);
	}

	bool Datum::operator==(const vector_type other) const
	{
		return !(*this != other);
	}

	bool Datum::operator==(const matrix_type other) const
	{
		return !(*this != other);
	}

	bool Datum::operator==(const string_type& other) const
	{
		return !(*this != other);
	}

	bool Datum::operator==(const pointer_type other) const
	{
		return !(*this != other);
	}

	void Datum::Set(const integer_type value, const size_t index) {
		if (_type != DatumType::Integer) {
			throw std::invalid_argument("parameter type does not match Datum type");
		}
		*(_array._int + index) = value;
	}

	void Datum::Set(const float_type value, const size_t index) {
		if (_type != DatumType::Float) {
			throw std::invalid_argument("parameter type does not match Datum type");
		}
		*(_array._float + index) = value;
	}

	void Datum::Set(const vector_type value, const size_t index) {
		if (_type != DatumType::Vector) {
			throw std::invalid_argument("parameter type does not match Datum type");
		}
		*(_array._vec + index) = value;
	}

	void Datum::Set(const matrix_type value, const size_t index) {
		if (_type != DatumType::Matrix) {
			throw std::invalid_argument("parameter type does not match Datum type");
		}
		*(_array._mat + index) = value;
	}

	void Datum::Set(const table_type& value, const size_t index)
	{
		if (_type != DatumType::Table) {
			throw std::invalid_argument("parameter type does not match Datum type");
		}
		*(_array._tbl + index) = value;
	}

	void Datum::Set(const string_type& value, const size_t index) {
		if (_type != DatumType::String) {
			throw std::invalid_argument("parameter type does not match Datum type");
		}
		*(_array._str + index) = value;
	}

	void Datum::Set(const pointer_type value, const size_t index) {
		if (_type != DatumType::Pointer) {
			throw std::invalid_argument("parameter type does not match Datum type");
		}
		*(_array._poi + index) = value;
	}

	void Datum::SetFromString(const std::string& str, const size_t index) {
		const char* input = str.c_str();
		char type[4];
		char data[200];
		type[3] = 0;
		sscanf_s(input, "%3s%s", &type, (uint32_t)sizeof(char) * 4, data, 200 * (uint32_t)sizeof(char));
		if (std::string(type) == "int"s) {
			integer_type value;
			sscanf_s(data, "%d", &value);
			Set(value, index);
		}
		else if (std::string(type) == "flt"s) {
			float_type value;
			sscanf_s(data, "%f", &value);
			Set(value, index);
		}
		else if (std::string(type) == "vec"s) {
			vector_type value;
			float* floats = reinterpret_cast<float*>(calloc(4, sizeof(float)));
			sscanf_s(data, "vec4(%f,%f,%f,%f)", floats, (floats + 1), (floats + 2), (floats + 3));
			value.x = *(floats);
			value.y = *(floats + 1);
			value.z = *(floats + 2);
			value.a = *(floats + 3);
			Set(value, index);
			free(floats);
		}
		else if (std::string(type) == "mat"s) {
			matrix_type value;
			float* floats = reinterpret_cast<float*>(calloc(16, sizeof(float)));
			sscanf_s(data, "mat4(vec4(%f,%f,%f,%f),vec4(%f,%f,%f,%f),vec4(%f,%f,%f,%f),vec4(%f,%f,%f,%f))",
				floats, (floats + 1), (floats + 2), (floats + 3),
				(floats + 4), (floats + 5), (floats + 6), (floats + 7),
				(floats + 8), (floats + 9), (floats + 10), (floats + 11),
				(floats + 12), (floats + 13), (floats + 14), (floats + 15));
			value = matrix_type(*floats, *(floats + 1), *(floats + 2), *(floats + 3),
				*(floats + 4), *(floats + 5), *(floats + 6), *(floats + 7),
				*(floats + 8), *(floats + 9), *(floats + 10), *(floats + 11),
				*(floats + 12), *(floats + 13), *(floats + 14), *(floats + 15));
			Set(value, index);
			free(floats);
		}
		else if (std::string(type) == "str"s) {
			char* string = reinterpret_cast<char*>(calloc(201, sizeof(char)));
			sscanf_s(input, "%*3s %200c", string, uint32_t(200 * sizeof(char)));
			string_type value(string);
			Set(value, index);
			free(string);
		}
		else if (std::string(type) == "ptr"s) {
			pointer_type value;
			sscanf_s(data, "%p", &value);
			Set(value, index);
		}
	}

	void Datum::PushBackFromString(const std::string& str)
	{
		if (_size == _capacity) {
			if (_hasExternalStorage) {
				throw std::runtime_error("External storage cannot be resized to accomodate new element");
			}
			Reserve(_capacity + 1);
		}
		SetFromString(str, _size);
		++_size;
	}

	std::string Datum::ToString(const size_t index) const
	{
		char* charPtr = reinterpret_cast<char*>(calloc(201, sizeof(char)));
		std::string str;
		switch (_type)
		{
		case fge::Datum::DatumType::Integer:
			sprintf_s(charPtr, 200, "int %d", As<integer_type>(index));
			str = charPtr;
			break;
		case fge::Datum::DatumType::Float:
			sprintf_s(charPtr, 200, "flt %f", As<float_type>(index));
			str = charPtr;
			break;
		case fge::Datum::DatumType::Vector:
			sprintf_s(charPtr, 200, "vec vec4(%f,%f,%f,%f)", As<vector_type>(index).x, As<vector_type>(index).y, As<vector_type>(index).z, As<vector_type>(index).a);
			str = charPtr;
			break;
		case fge::Datum::DatumType::Matrix:
			sprintf_s(charPtr, 200, "mat mat4(vec4(%f,%f,%f,%f),vec4(%f,%f,%f,%f),vec4(%f,%f,%f,%f),vec4(%f,%f,%f,%f))",
				As<matrix_type>(index)[0][0], As<matrix_type>(index)[0][1], As<matrix_type>(index)[0][2], As<matrix_type>(index)[0][3],
				As<matrix_type>(index)[1][0], As<matrix_type>(index)[1][1], As<matrix_type>(index)[1][2], As<matrix_type>(index)[1][3],
				As<matrix_type>(index)[2][0], As<matrix_type>(index)[2][1], As<matrix_type>(index)[2][2], As<matrix_type>(index)[2][3],
				As<matrix_type>(index)[3][0], As<matrix_type>(index)[3][1], As<matrix_type>(index)[3][2], As<matrix_type>(index)[3][3]);
			str = charPtr;
			break;
		case fge::Datum::DatumType::String:
			str = "str "s + As<string_type>(index);
			break;
		case fge::Datum::DatumType::Pointer:
			sprintf_s(charPtr, 200, "ptr %p", As<pointer_type>(index));
			str = charPtr;
			break;

		default:
			throw std::invalid_argument("invalid type cannot be parsed");
		}
		free(charPtr);
		return str;
	}

	bool Datum::IsExternalStorage() const
	{
		return _hasExternalStorage;
	}

	void Datum::PushBack(const integer_type value) {
		if (_type == DatumType::Integer) {
			if (_size == _capacity) {
				if (_hasExternalStorage) {
					throw std::runtime_error("External storage cannot be resized to accomodate new element");
				}
				Reserve(_capacity + 1);
			}
			new(_array._int + _size)integer_type(value);
			++_size;
		}
	}

	void Datum::PushBack(const float_type value) {
		if (_type == DatumType::Float) {
			if (_size == _capacity) {
				if (_hasExternalStorage) {
					throw std::runtime_error("External storage cannot be resized to accomodate new element");
				}
				Reserve(_capacity + 1);
			}
			new(_array._float + _size)float_type(value);
			++_size;
		}
	}

	void Datum::PushBack(const vector_type value) {
		if (_type == DatumType::Vector) {
			if (_size == _capacity) {
				if (_hasExternalStorage) {
					throw std::runtime_error("External storage cannot be resized to accomodate new element");
				}
				Reserve(_capacity + 1);
			}
			new(_array._vec + _size)vector_type(value);
			++_size;
		}
	}

	void Datum::PushBack(const matrix_type value) {
		if (_type == DatumType::Matrix) {
			if (_size == _capacity) {
				if (_hasExternalStorage) {
					throw std::runtime_error("External storage cannot be resized to accomodate new element");
				}
				Reserve(_capacity + 1);
			}
			new(_array._mat + _size)matrix_type(value);
			++_size;
		}
	}


	void Datum::PushBack(const string_type& value) {
		if (_type == DatumType::String) {
			if (_size == _capacity) {
				if (_hasExternalStorage) {
					throw std::runtime_error("External storage cannot be resized to accomodate new element");
				}
				Reserve(_capacity + 1);
			}
			new(_array._str + _size)string_type(value);
			++_size;
		}
	}

	void Datum::PushBack(const pointer_type value) {
		if (_type == DatumType::Pointer) {
			if (_size == _capacity) {
				if (_hasExternalStorage) {
					throw std::runtime_error("External storage cannot be resized to accomodate new element");
				}
				Reserve(_capacity + 1);
			}
			new(_array._poi + _size)pointer_type(value);
			++_size;
		}
	}

	void Datum::PushTable(const table_type value)
	{
		if (_type == DatumType::Table) {
			if (_size == _capacity) {
				if (_hasExternalStorage) {
					throw std::runtime_error("External storage cannot be resized to accomodate new element");
				}
				Reserve(_capacity + 1);
			}
			new(_array._tbl + _size)table_type(value);
			++_size;
		}
	}

	void Datum::PopBack() {
		assert(_size >= 1);

		if (_type == DatumType::String) {
			(_array._str + (_size - 1))->~string_type();
		}
		--_size;

	}

	void Datum::Remove(const integer_type value) {
		if (_type != DatumType::Integer) {
			throw std::invalid_argument("cannot remove value of invalid type");
		}
		size_t i = 0;
		for (; i < _size; ++i) {
			integer_type* temp = _array._int + i;
			if (*temp == value) {
				if (i == _size - 1) {
					PopBack();
				}
				else {
					memmove(temp, temp + 1, sizeof(integer_type) * (_size - i));
					--_size;
				}
				break;
			}
		}
	}

	void Datum::Remove(const float_type value) {
		if (_type != DatumType::Float) {
			throw std::invalid_argument("cannot remove value of invalid type");
		}
		size_t i = 0;
		for (; i < _size; ++i) {
			float_type* temp = _array._float + i;
			if (*temp == value) {
				if (i == _size - 1) {
					PopBack();
				}
				else {
					memmove(temp, temp + 1, sizeof(float_type) * (_size - i));
					--_size;
				}
				break;
			}
		}
	}

	void Datum::Remove(const vector_type value) {
		if (_type != DatumType::Vector) {
			throw std::invalid_argument("cannot remove value of invalid type");
		}
		size_t i = 0;
		for (; i < _size; ++i) {
			vector_type* temp = _array._vec + i;
			if (*temp == value) {
				if (i == _size - 1) {
					PopBack();
				}
				else {
					memmove(temp, temp + 1, sizeof(vector_type) * (_size - i));
					--_size;
				}
				break;
			}
		}
	}

	void Datum::Remove(const matrix_type value) {
		if (_type != DatumType::Matrix) {
			throw std::invalid_argument("cannot remove value of invalid type");
		}
		size_t i = 0;
		for (; i < _size; ++i) {
			matrix_type* temp = _array._mat + i;
			if (*temp == value) {
				if (i == _size - 1) {
					PopBack();
				}
				else {
					memmove(temp, temp + 1, sizeof(matrix_type) * (_size - i));
					--_size;
				}
				break;
			}
		}
	}

	void Datum::Remove(table_type value) {
		if (_type != DatumType::Table) {
			throw std::invalid_argument("cannot remove value of invalid type");
		}
		size_t i = 0;
		for (; i < _size; ++i) {
			table_type* temp = _array._tbl + i;
			if (*temp == value) {
				if (i == _size - 1) {
					PopBack();
				}
				else {
					memmove(temp, temp + 1, sizeof(matrix_type) * (_size - i));
					--_size;
				}
				break;
			}
		}
	}

	void Datum::Remove(string_type value) {
		if (_type != DatumType::String) {
			throw std::invalid_argument("cannot remove value of invalid type");
		}
		size_t i = 0;
		for (; i < _size; ++i) {
			string_type* temp = _array._str + i;
			if (*temp == value) {
				if (i == _size - 1) {
					PopBack();
				}
				else {
					temp->~string_type();
					memmove(temp, temp + 1, sizeof(string_type) * (_size - i));
					--_size;
				}
				break;
			}
		}
	}

	void Datum::Remove(const pointer_type value) {
		if (_type != DatumType::Pointer) {
			throw std::invalid_argument("cannot remove value of invalid type");
		}
		size_t i = 0;
		for (; i < _size; ++i) {
			pointer_type* temp = _array._poi + i;
			if (*temp == value) {
				if (i == _size - 1) {
					PopBack();
				}
				else {
					memmove(temp, temp + 1, sizeof(pointer_type) * (_size - i));
					--_size;
				}
				break;
			}
		}
	}
	void Datum::ShrinkToFit() {
		assert(_size < _capacity);
		void* newVp = realloc(_array._vp, _size * _capacityTable[static_cast<int>(_type)]);
		if (newVp) {
			_array._vp = newVp;
		}
		_capacity = _size;
	}
	void Datum::Reserve(size_t newSize) {
		if (newSize <= _capacity) {
			throw std::invalid_argument("cannot reserve reduced size");
		}
		if (_type == DatumType::Unknown) {

			throw std::invalid_argument("cannot resize Datum of unknown type");
		}
		void* newVp = realloc(_array._vp, newSize * _capacityTable[(int)_type]);
		if (newVp) {
			_array._vp = newVp;
		}
		else throw std::runtime_error("failed to reallocate memory for new size");
		_capacity = newSize;
		

	}
}