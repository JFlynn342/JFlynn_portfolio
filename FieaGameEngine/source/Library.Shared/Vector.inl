#include <malloc.h>
#include <stdexcept>
#include <algorithm>
#include "Vector.h"
namespace fge {
	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> list) {
		for (const_reference item : list) {
			push_back(item);
		}
	}
	template<typename T>
	inline typename Vector<T>::reference Vector<T>::operator[](Vector::size_type index) {
		_ASSERT(_array + index != nullptr && index < _size);
		Vector::reference value = *(_array + index);
		return value;
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::operator[](Vector::size_type index) const {
		_ASSERT(_array + index != nullptr && index < _size);
		const Vector::const_reference value = *(_array + index);
		return value;
	}

	template<typename T>
	inline typename Vector<T>::reference Vector<T>::At(Vector::size_type index) {
		if (index >= _size) {
			throw std::out_of_range("invalid index");
		}
		Vector::reference value = *(_array + index);
		return value;
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::At(Vector::size_type index) const {
		if (index >= _size) {
			throw std::out_of_range("invalid index");
		}
		Vector::const_reference value = *(_array + index);
		return value;

	}

	template<typename T>
	inline void Vector<T>::Reserve(Vector::size_type newCapacity) {
		if (newCapacity > _capacity) {
			Vector::pointer newBlock = reinterpret_cast<Vector::pointer>(std::realloc(_array, newCapacity * sizeof(Vector::value_type)));
			_array = newBlock;
			_capacity = newCapacity;
		}
	}

	template<typename T>
	inline void Vector<T>::pop_back() {
		if (_size == 0) {
			return;
		}
		(_array + (_size - 1))->~T();
		_size--;
	}

	template<typename T>
	inline bool Vector<T>::empty() const {
		return _size == 0;
	}

	template <typename T>
	inline typename Vector<T>::reference Vector<T>::front() {
		return At(0);
	}

	template <typename T>
	inline typename Vector<T>::const_reference Vector<T>::front() const {
		return At(0);
	}

	template <typename T>
	inline typename Vector<T>::reference Vector<T>::back() {
		return At(_size - 1);
	}

	template <typename T>
	inline typename Vector<T>::const_reference Vector<T>::back() const {
		return At(_size - 1);
	}

	template<typename T>
	inline typename Vector<T>::size_type Vector<T>::size() const {
		return _size;
	}

	template<typename T>
	inline typename Vector<T>::size_type Vector<T>::Capacity() const {
		return _capacity;
	}

	template<typename T>
	inline void Vector<T>::push_back(Vector::const_reference value) {
		if (_size == _capacity) {
			Reserve(_size + 1);
		}
		new(_array + _size)value_type(value);
		++_size;
	}

	template<typename T>
	inline Vector<T>::~Vector() {
		Clear();
		ShrinkToFit();
	}

	template<typename T>
	inline void Vector<T>::ShrinkToFit() {
		if (_size == _capacity) {
			// no exceptions needed here, but a quick return makes things more performant
			return;
		}
		if (_size == 0) {
			std::free(_array);
			_array = nullptr;
			_capacity = 0;
			return;
		}
		_capacity = _size;
		Vector::pointer newBlock = reinterpret_cast<Vector::pointer>(std::realloc(_array, _capacity * sizeof(Vector::value_type)));
		_array = newBlock;
	}

	template<typename T>
	inline void Vector<T>::Clear() {
		while (_size > 0) {
			pop_back();
		}
	}

	template<typename T>
	inline Vector<T>::Vector(const Vector& other) {
		Reserve(other._size);
		for (size_t i = 0; i < other._size; ++i) {
			push_back(other.At(i));
		}
	}

	template<typename T>
	inline Vector<T> Vector<T>::operator=(const Vector& other) {
		if (this == &other) {
			throw std::invalid_argument("Attempted self-assignment");
		}
		Clear();
		ShrinkToFit();
		Reserve(other._capacity);
		for (size_t i = 0; i < other._size; ++i) {
			push_back(other.At(i));
		}
		return *this;
	}

	template<typename T>
	inline Vector<T>::Vector(Vector&& other) noexcept :
		_array{ other._array }, _size{ other._size }, _capacity{ other._capacity } {
		other._array = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	template<typename T>
	inline Vector<T> Vector<T>::operator=(Vector&& other) noexcept {
		Clear();
		ShrinkToFit();
		_array = other._array;
		other._array = nullptr;
		_size = other._size;
		_capacity = other._capacity;
		other._size = 0;
		other._capacity = 0;
		return* this;
	}

	template<typename T>
	inline void Vector<T>::RemoveAt(const Vector::size_type index) {
		if (index >= _size) {
			throw std::out_of_range("Attempted to remove element outside of Vector's size");
		}
		(_array + index)->~T();
		std::memmove(_array + index, _array + index + 1, sizeof(Vector::value_type) * (_size - index));
		_size--;
	}

	template<typename T>
	inline void Vector<T>::Remove(const value_type& value)
	{
		for (size_t i = 0; i < _size; ++i) {
			if ((*(_array + i)) == value) {
				RemoveAt(i);
			}
		}
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator==(const Iterator& other) const {
		return(_container == other._container && _index == other._index);
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator!=(const Iterator& other) const {
		return !(*this == other);
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator++() {
		Iterator temp = *this;
		++_index;
		return temp;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
		++_index;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::difference_type Vector<T>::Iterator::operator+(const Iterator& other)
	{
		return _index + other._index;
	}

	template<typename T>
	inline typename Vector<T>::difference_type Vector<T>::Iterator::operator-(const Iterator& other)
	{
		return _index - other._index;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator+(difference_type diff)
	{
		return Iterator(*this) += diff;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator-(difference_type diff)
	{
		return Iterator(*this) -= diff;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator+=(Vector::size_type inc) {
		_index += inc;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator--() {
		if (_index <= 0) {
			throw std::out_of_range("Iterator index underflow");
		}
		_index--;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
		if (_index <= 0) {
			throw std::out_of_range("Iterator index underflow");
		}
		Iterator temp = *this;
		--_index;
		return temp;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator-=(Vector::size_type dec) {
		_index -= dec;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::reference Vector<T>::Iterator::operator*() const{
		_ASSERT(_container != nullptr );
		return _container->At(_index);
	}

	template<typename T>
	inline typename Vector<T>::reference Vector<T>::Iterator::operator[](Vector::difference_type offset) {
		return _container->At(_index + offset);
	}

	template<typename T>
	inline Vector<T>::Iterator::Iterator(const typename Iterator& other) {
		_container = other._container;
		_index = other._index;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator=(const typename Iterator& other) {
		if (this == &other) {
			throw std::invalid_argument("Attempted self-assignment");
		}
		_container = other._container;
		_index = other._index;
		return *this;
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator==(const typename ConstIterator& other) const {
		return(_container == other._container && _index == other._index);
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator!=(const typename ConstIterator& other) const {
		return !(*this == other);
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++() {
		ConstIterator temp = *this;
		++_index;
		return temp;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int) {
		++_index;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator+=(Vector::size_type inc) {
		_index += inc;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--() {
		if (_index <= 0) {
			throw std::out_of_range("Iterator index underflow");
		}
		ConstIterator temp = *this;
		_index--;
		return temp;
	}
	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int) {
		if (_index <= 0) {
			throw std::out_of_range("Iterator index underflow");
		}
		--_index;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator-=(Vector::size_type dec) {
		_index -= dec;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::ConstIterator::operator*() const {
		_ASSERT(_container != nullptr);
		return _container->At(_index);
	}

	template<typename T>
	inline typename Vector<T>::const_reference Vector<T>::ConstIterator::operator[](Vector::difference_type offset) const {
		return _container->At(_index + offset);
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const ConstIterator& other) {
		_container = other._container;
		_index = other._index;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator=(const ConstIterator& other) {
		if (this == &other) {
			throw std::invalid_argument("Attempted self-assignment");
		}
		_container = other._container;
		_index = other._index;
		return *this;
	}


	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Iterator& other) {
		_container = other._container;
		_index = other._index;
	}

	template<typename T>
	inline Vector<T>::Iterator::Iterator(Vector& container, Vector::size_type index) {
		_container = &container;
		_index = index;
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector& container, Vector::size_type index) {
		_container = &container;
		_index = index;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::begin() {
		Iterator it(*this, size_t(0));
		return it;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::begin() const {
		ConstIterator it(*this, size_t(0));
		return it;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::end() {
		Iterator it(*this, _size);
		return it;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::end() const {
		ConstIterator it(*this, _size);
		return it;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cbegin() const {
		ConstIterator it(*this, size_t(0));
		return it;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cend() const {
		ConstIterator it(*this, _size);
		return it;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Find(Vector::const_reference value) {
		Iterator it = begin();
		while (it._index < _size) {
			if (*it == value) {
				break;
			}
			++it;
		}
		return it;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::Find(Vector::const_reference value) const {
		ConstIterator it = begin();
		while (it._index < _size) {
			if (*it == value) {
				break;
			}
			++it;
		}
		return it;
	}

	template<typename T>
	void Vector<T>::push_back(Vector::rvalue_reference value) {
		if (_size == _capacity) {
			Reserve(_size + 1);
		}
		new(_array + _size)value_type(std::move(value));
		_size++;
	}
}



