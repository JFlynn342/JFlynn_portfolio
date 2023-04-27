#pragma once
#include <cstdint>
#include "DefaultEquality.h"
namespace fge {
	/// <summary>
	/// a dynamic array class that can hold items of the same type
	/// </summary>
	/// <typeparam name="T">the item type held by the Vector</typeparam>
	template<typename T>
	class Vector final {
	public:
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = value_type&&;
		using pointer = value_type*;
		/// <summary>
		/// An iterator that can get non-const references to elements in the Vector
		/// </summary>
		class Iterator {
		public:
			friend Vector;
			using iterator_category = std::random_access_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T&;
			using pointer = T*;
			/// <summary>
			/// compares two Iterators
			/// </summary>
			/// <param name="other">the right-hand operand used for comparison</param>
			/// <returns>true if the Iterators share a container and point to the same item, otherwise false</returns>
			bool operator==(const Iterator& other) const;
			/// <summary>
			/// compares two Iterators
			/// </summary>
			/// <param name="other">the right-hand operand used for comparison</param>
			/// <returns>true if the Iterators belong to different containers or point to different items, otherwise false</returns>
			bool operator!=(const Iterator& other) const;
			/// <summary>
			/// increments the Iterator and returns it
			/// </summary>
			/// <returns>the incremented Iterator</returns>
			Iterator operator++();
			/// <summary>
			/// increments the Iterator and returns it
			/// </summary>
			/// <returns>the incremented Iterator</returns>
			Iterator operator++(int);
			/// <summary>
			/// decrements the Iterator and returns it
			/// </summary>
			/// <returns>the decremented Iterator</returns>
			Iterator operator--();
			/// <summary>
			/// decrements the Iterator and returns it
			/// </summary>
			/// <returns>the decremented Iterator</returns>
			Iterator operator--(int);
			/// <summary>
			/// increments the Iterator by a given amount
			/// </summary>
			/// <param name="inc">the amount to increment by</param>
			difference_type operator+(const Iterator& other);
			difference_type operator-(const Iterator& other);
			Iterator operator+(difference_type diff);
			Iterator operator-(difference_type diff);
			Iterator operator+=(size_type inc);
			/// <summary>
			/// increments the ConstIterator by a given amount
			/// </summary>
			/// <param name="dec">the amount to increment by</param>
			Iterator operator-=(size_type dec);
			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>a const reference to the item at the Iterator's current position</returns>
			reference operator*() const;
			/// <summary>
			/// gets the item at a specified offset from the Iterator
			/// </summary>
			/// <param name="offset">the position of the desired item relative to that of the Iterator</param>
			/// <returns>a reference to the item at the offset</returns>
			reference operator[](difference_type offset);
			/// <summary>
			/// copy constructor
			/// </summary>
			/// <param name="other">the Iterator to be copied</param>
			Iterator(const Iterator& other);
			/// <summary>
			/// copy assignment operator
			/// </summary>
			/// <param name="other">the Iterator to be copied</param>
			/// <returns>the reassigned Iterator</returns>
			Iterator operator=(const Iterator& other);
			/// <summary>
			/// default constructor
			/// </summary>
			Iterator() = default;
		private:
			/// <summary>
			/// the Vector that this Iterator is bound to
			/// </summary>
			Vector* _container;
			/// <summary>
			/// the current position of the Iterator
			/// </summary>
			size_type _index;
			/// <summary>
			/// private constructor for internal use
			/// </summary>
			/// <param name="container">the Vector the newly constructed Iterator points to</param>
			/// <param name="index">the index of the newly constructed iterator</param>
			Iterator(Vector& container, size_type index);
		};
		/// <summary>
		/// An iterator that can get const references to elements in the Vector
		/// </summary>
		class ConstIterator {
		public:
			friend Vector;
			friend Iterator;
			using iterator_category = std::random_access_iterator_tag;
			using difference_type = ptrdiff_t;
			using value_type = T;
			using reference = const T&;
			using pointer = T* const;
			/// <summary>
			/// compares two ConstIterators
			/// </summary>
			/// <param name="other">the right-hand operand used for comparison</param>
			/// <returns>true if the ConstIterators share a container and point to the same item, otherwise false</returns>
			bool operator==(const ConstIterator& other) const;
			/// <summary>
			/// compares two ConstIterators
			/// </summary>
			/// <param name="other">the right-hand operand used for comparison</param>
			/// <returns>true if the ConstIterators belong to different containers or point to different items, otherwise false</returns>
			bool operator!=(const ConstIterator& other) const;
			/// <summary>
			/// increments the ConstIterator and returns it
			/// </summary>
			/// <returns>the incremented ConstIterator</returns>
			ConstIterator operator++();
			/// <summary>
			/// increments the ConstIterator and returns it
			/// </summary>
			/// <returns>the incremented ConstIterator</returns>
			ConstIterator operator++(int);
			/// <summary>
			/// decrements the ConstIterator and returns it
			/// </summary>
			/// <returns>the decremented ConstIterator</returns>
			ConstIterator operator--();
			/// <summary>
			/// decrements the ConstIterator and returns it
			/// </summary>
			/// <returns>the decremented ConstIterator</returns>
			ConstIterator operator--(int);
			/// <summary>
			/// increments the ConstIterator by a given amount
			/// </summary>
			/// <param name="inc">the amount to increment by</param>
			ConstIterator operator+=(size_type inc);
			/// <summary>
			/// increments the ConstIterator by a given amount
			/// </summary>
			/// <param name="dec">the amount to increment by</param>
			ConstIterator operator-=(size_type dec);
			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>a const reference to the item at the ConstIterator's current position</returns>
			const_reference operator*() const;
			/// <summary>
			/// gets the item at a specified offset from the ConstIterator
			/// </summary>
			/// <param name="offset">the position of the desired item relative to that of the ConstIterator</param>
			/// <returns>a const reference to the item at the offset</returns>
			const_reference operator[](difference_type offset) const;
			/// <summary>
			/// copy constructor
			/// </summary>
			/// <param name="other">the ConstIterator to be copied</param>
			ConstIterator(const ConstIterator& other);
			/// <summary>
			/// copy assignment operator
			/// </summary>
			/// <param name="other">the ConstIterator to be copied</param>
			/// <returns>the reassigned ConstIterator</returns>
			ConstIterator operator=(const ConstIterator& other);
			/// <summary>
			/// creates a new ConstIterator based off a given Iterator
			/// </summary>
			/// <param name="other">The Iterator to base the ConstIterator on</param>
			ConstIterator(const Iterator& other);
			/// <summary>
			/// default constructor
			/// </summary>
			ConstIterator() = default;
		private:
			/// <summary>
			/// the Vector that this ConstIterator is bound to
			/// </summary>
			const Vector* _container;
			/// <summary>
			/// the current position of the ConstIterator
			/// </summary>
			size_type _index;
			/// <summary>
			/// private constructor for internal use
			/// </summary>
			/// <param name="container">the Vector the newly constructed ConstIterator points to</param>
			/// <param name="index">the index of the newly constructed ConstIterator</param>
			ConstIterator(const Vector& container, size_type index);
		};
		/// <summary>
		/// default constructor, initializes the array to be empty and of capacity 0
		/// </summary>
		Vector() = default;
		Vector(std::initializer_list<T> list);
		/// <summary>
		/// gets the item at the given index and returns a reference to it
		/// </summary>
		/// <param name="index">the position of the desired item in the array</param>
		/// <returns>a reference to the item at the given index</returns>
		reference operator[](size_type index);
		/// <summary>
		/// gets the item at the given index and returns a const reference to it
		/// </summary>
		/// <param name="index">the position of the desired item in the array</param>
		/// <returns>a const reference to the item at the given index</returns>
		const_reference operator[](size_type index) const;
		/// <summary>
		/// gets the item at the given index and returns a reference to it
		/// </summary>
		/// <param name="index">the position of the desired item in the array</param>
		/// <returns>a reference to the item at the given index</returns>
		reference At(size_type index);
		/// <summary>
		/// gets the item at the given index and returns a const reference to it
		/// </summary>
		/// <param name="index">the position of the desired item in the array</param>
		/// <returns>a const reference to the item at the given index</returns>
		const_reference At(size_type index) const;
		/// <summary>
		/// removes the last item in the array without reducing the capacity
		/// </summary>
		void pop_back();
		/// <summary>
		/// checks if the array is empty
		/// </summary>
		/// <returns>true if the array contains no items, otherwise false</returns>
		bool empty() const;
		/// <summary>
		/// gets a reference to the first item in the array
		/// </summary>
		/// <returns>a reference to the first item in the array</returns>
		reference front();
		/// <summary>
		/// gets a const reference to the first item in the array
		/// </summary>
		/// <returns>a const reference to the first item in the array</returns>
		const_reference front() const;
		/// <summary>
		/// gets a reference to the last item in the array
		/// </summary>
		/// <returns>a reference to the last item in the array</returns>
		reference back();
		/// <summary>
		/// gets a const reference to the last item in the array
		/// </summary>
		/// <returns>a const reference to the last item in the array</returns>
		const_reference back() const;
		/// <summary>
		/// gets the size of the array
		/// </summary>
		/// <returns>the number of elements currently in the array</returns>
		size_type size() const;
		/// <summary>
		/// gets the capacity of the array
		/// </summary>
		/// <returns>the maximum number of items that the array can currently hold</returns>
		size_type Capacity() const;
		/// <summary>
		/// creates and returns a start iterator
		/// </summary>
		/// <returns>an Iterator pointing to the first element in the array</returns>
		Iterator begin();
		/// <summary>
		/// creates and returns an end iterator
		/// </summary>
		/// <returns>an Iterator pointing past the last element in the array</returns>
		Iterator end();
		/// <summary>
		/// creates and returns a start iterator
		/// </summary>
		/// <returns>a ConstIterator pointing to the first element in the array</returns>
		ConstIterator begin() const;
		/// <summary>
		/// creates and returns an end iterator
		/// </summary>
		/// <returns>a ConstIterator pointing past the last element in the array</returns>
		ConstIterator end() const;
		/// <summary>
		/// creates and returns a start ConstIterator
		/// </summary>
		/// <returns>a ConstIterator pointing to the first element in the array</returns>
		ConstIterator cbegin() const;
		/// <summary>
		/// creates and returns an end ConstIterator
		/// </summary>
		/// <returns>a ConstIterator pointing past the last element in the array</returns>
		ConstIterator cend() const;
		/// <summary>
		/// adds an additional item to the back of the array
		/// </summary>
		/// <param name="value">a refererence to the value to be added</param>
		void push_back(const_reference value);
		/// <summary>
		/// adds an additional item to the back of the array
		/// </summary>
		/// <param name="value">an rvalue refererence to the value to be added</param>
		void push_back(rvalue_reference value);
		/// <summary>
		/// copy constructor
		/// </summary>
		/// <param name="other">the Vector to be copied</param>
		Vector(const Vector& other);
		/// <summary>
		/// move constructor
		/// </summary>
		/// <param name="other">an reference to the rvalue to base the new Vector on</param>
		Vector(Vector&& other) noexcept;
		/// <summary>
		/// copy assignment operator
		/// </summary>
		/// <param name="other">the Vector to be copied</param>
		Vector operator=(const Vector& other);
		/// <summary>
		/// move assignment operator
		/// </summary>
		/// <param name="other">the Vector to be copied</param>
		Vector operator=(Vector&& other) noexcept;
		/// <summary>
		/// destructor
		/// </summary>
		~Vector();
		/// <summary>
		/// extends the capacity of the array
		/// </summary>
		/// <param name="newCapacity">the new capacity</param>
		void Reserve(size_type newCapacity);
		/// <summary>
		/// reduces the capacity of the array top its current size, freeing excess memory
		/// </summary>
		void ShrinkToFit();
		/// <summary>
		/// finds an item in the array of a given value
		/// </summary>
		/// <param name="value">the value to find</param>
		/// <returns>an Iterator pointing to the desired element</returns>
		Iterator Find(const_reference value);
		/// <summary>
		/// finds an item in the array of a given value
		/// </summary>
		/// <param name="value">the value to find</param>
		/// <returns>a ConstIterator pointing to the desired element</returns>
		ConstIterator Find(const_reference value) const;
		/// <summary>
		/// removes all items in the array, without reducing capacity
		/// </summary>
		void Clear();
		/// <summary>
		/// removes the item at the given index, without reducing capacity
		/// </summary>
		/// <param name="index">the index of the item to be removed</param>
		void RemoveAt(const size_type index);
		void Remove(const value_type& value);
		private:
			pointer _array = nullptr;
			size_type _size = 0;
			size_type _capacity = 0;
	};
}

#include "Vector.inl"