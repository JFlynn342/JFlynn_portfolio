#pragma once
#include "DefaultEquality.h"
namespace fge {
	/// <summary>
	/// A singly-linked list template that can store multiple items of the same type
	/// </summary>
	/// <typeparam name="T">The type of the items that this list can contain</typeparam>
	template<typename T>
	class SList final{
		friend class Iterator;
		friend class ConstIterator;
	private:
		class Node;
	public:
		using size_type = size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const T&;
		using rvalue_reference = value_type&&;
		using equality_func = DefaultEquality<value_type>;
		
		/// <summary>
		/// An object that can be used to traverse and get item references from the list
		/// </summary>
		class Iterator {
		public:
			friend SList;
			friend class ConstIterator;
			/// <summary>
			/// Dereference operator; used to get a reference to the current item
			/// </summary>
			/// <returns>a reference to the current item pointed to by the iterator</returns>
			reference operator*() const;
			/// <summary>
			/// increment operator, used for forward traversal
			/// </summary>
			/// <returns>the incremented Iterator</returns>
			typename Iterator operator++();
			/// <summary>
			/// increment operator, used for forward traversal
			/// </summary>
			/// <returns>the incremented Iterator</returns>
			typename Iterator operator++(int);
			/// <summary>
			/// compares two Iterators
			/// </summary>
			/// <param name="other">the right hand operand of the expression</param>
			/// <returns>true if the operands are not of the same SList, or do not point to the same Node, otherwise returns false</returns>
			bool operator!=(const Iterator& other) const;
			/// <summary>
			/// compares two Iterators
			/// </summary>
			/// <param name="other">the right hand operand of the expression</param>
			/// <returns>true if the operands are of the same SList and point to the same Node, otherwise returns false</returns>
			bool operator==(const Iterator& other) const;
			/// <summary>
			/// default constructor
			/// </summary>
			Iterator() = default;
		private:
			/// <summary>
			/// The SList that this Iterator points at
			/// </summary>
			const SList<T>* _container = nullptr;
			/// <summary>
			/// The current Node that this Iterator is pointing to
			/// </summary>
			Node* _node = nullptr;
			/// <summary>
			/// specialized constructor for Iterator
			/// </summary>
			/// <param name="container">the list this Iterator will point at</param>
			/// <param name="node">the Node this Iterator will start at</param>
			Iterator(const SList* container, Node* node = nullptr);
		};
		/// <summary>
		/// An Iterator that can get constant item references from the list
		/// </summary>
		class ConstIterator final{
		public:
			friend SList;
			/// <summary>
			/// Dereference operator; used to get a const reference to the current item
			/// </summary>
			/// <returns>a const reference to the current item pointed to by the iterator</returns>
			const_reference operator*() const;
			/// <summary>
			/// increment operator, used for forward traversal
			/// </summary>
			/// <returns>the incremented ConstIterator</returns>
			typename ConstIterator operator++();
			/// <summary>
			/// increment operator, used for forward traversal
			/// </summary>
			/// <returns>the incremented ConstIterator</returns>
			typename ConstIterator operator++(int);
			/// <summary>
			/// compares two ConstIterators
			/// </summary>
			/// <param name="other">the right hand operand of the expression</param>
			/// <returns>true if the operands are not of the same SList, or do not point to the same Node, otherwise returns false</returns>
			bool operator!=(const ConstIterator& other) const;
			/// <summary>
			/// compares two ConstIterators
			/// </summary>
			/// <param name="other">the right hand operand of the expression</param>
			/// <returns>true if the operands are of the same SList and point to the same Node, otherwise returns false</returns>
			bool operator==(const ConstIterator& other) const;
			/// <summary>
			/// creates a new ConstIterator based on an existing Iterator
			/// </summary>
			/// <param name="other">the Iterator to base the new ConstIterator on</param>
			ConstIterator(const Iterator& other);
			/// <summary>
			/// public default constructor
			/// </summary>
			ConstIterator() = default;
		private:
			/// <summary>
			/// The SList that this ConstIterator points at
			/// </summary>
			const SList<T>* _container = nullptr;
			/// <summary>
			/// The current Node that this ConstIterator is pointing to
			/// </summary>
			const Node* _node = nullptr;
			/// <summary>
			/// specialized constructor for ConstIterator
			/// </summary>
			/// <param name="container">the list this ConstIterator will point at</param>
			/// <param name="node">the Node this ConstIterator will start at</param>
			ConstIterator(const SList<T>* container, Node* node = nullptr);
		};
		/// <summary>
		/// Gets an Iterator pointing to the front of the list
		/// </summary>
		/// <returns>An Iterator pointing to the front of the list</returns>
		Iterator begin();
		/// <summary>
		/// Gets an Iterator pointing past the back of the list
		/// </summary>
		/// <returns>An Iterator pointing past the back of the list</returns>
		Iterator end();
		/// <summary>
		/// Gets a ConstIterator pointing to the front of the list
		/// </summary>
		/// <returns>a ConstIterator pointing to the front of the list</returns>
		ConstIterator begin() const;
		/// <summary>
		/// Gets a ConstIterator pointing past the back of the list
		/// </summary>
		/// <returns>a ConstIterator pointing past the back of the list</returns>
		ConstIterator end() const;
		
		/// <summary>
		/// Gets a ConstIterator pointing to the front of the list
		/// </summary>
		/// <returns>a ConstIterator pointing to the front of the list</returns>
		ConstIterator cbegin() const;
		/// <summary>
		/// Gets a ConstIterator pointing past the back of the list
		/// </summary>
		/// <returns>a ConstIterator pointing past the back of the list</returns>
		ConstIterator cend() const;
		/// <summary>
		/// inserts an item at a specified location in the list
		/// </summary>
		/// <param name="value">the item to add</param>
		/// <param name="position">an Iterator pointing to the location to insert the item</param>
		/// <returns>an Iterator pointing to the new element</returns>
		Iterator InsertAfter(const_reference value, Iterator position);

		/// <summary>
		/// Finds the given value in the list and returns an Iterator pointing at it
		/// </summary>
		/// <param name="value">A reference to the value to find</param>
		/// <returns>an Iterator pointing to the Node containing the passed-in value</returns>
		Iterator Find(const_reference value);
		/// <summary>
		/// Finds the given value in the list and returns a ConstIterator pointing at it
		/// </summary>
		/// <param name="value">A reference to the value to find</param>
		/// <returns>a ConstIterator pointing to the Node containing the passed-in value</returns>
		ConstIterator Find(const_reference value) const;
		/// <summary>
		/// Removes the corresponding item from the list, if it exists
		/// </summary>
		/// <param name="value">A reference to the data to be removed</param>
		void Remove(const_reference value);
		// constant time methods

		/// <summary>
		/// default contstructor; initializes an empty list
		/// </summary>
		SList() = default;

		/// <summary>
		/// inserts the given item at the beginning of the list
		/// </summary>
		/// <param name="value">the item to be inserted</param>
		void PushFront(const_reference value);

		/// <summary>
		/// removes the item at the front of the list
		/// </summary>
		void PopFront();

		/// <summary>
		/// inserts the given item at the end of the list
		/// </summary>
		/// <param name="value">the item to be inserted</param>
		void PushBack(const_reference value);

		/// <summary>
		/// checks if the list has no elements
		/// </summary>
		/// <returns>true if the list is empty, otherwise returns false</returns>
		bool IsEmpty() const;

		/// <summary>
		/// gets the item at the front of the list
		/// </summary>
		/// <returns>a reference to the item at the front of the list</returns>
		[[nodiscard]] reference Front();

		/// <summary>
		/// gets the item at the back of the list
		/// </summary>
		/// <returns>a reference to the item at the back of the list</returns>
		[[nodiscard]] reference Back();

		// linear time methods


		/// <summary>
		/// gets the number of elements in the list
		/// </summary>
		/// <returns>the number of items in the list</returns>
		[[nodiscard]] size_t Size() const;

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="other">the SList to copy</param>
		SList(const SList& other);

		/// <summary>
		/// Copy assignment operator
		/// </summary>
		/// <param name="other">the SList to copy</param>
		/// <returns>A copy of the other list</returns>
		SList& operator=(const SList& other);

		///<summary>
		/// destructor
		///</summary>
		~SList();

		/// <summary>
		/// removes all items from the list without deleting the list itself
		/// </summary>
		void Clear();

		/// <summary>
		/// removes the item at the back of the list
		/// </summary>
		void PopBack();

	private:

		/// <summary>
		/// A class used for storage of an individual item in the list
		/// </summary>
		class Node {
		public:
			/// <summary>
			/// constructor
			/// </summary>
			/// <param name="value">the item that the Node represents</param>
			/// <param name="next">the Node after the Node being created/param>
			Node(value_type value, Node* next);
			///<summary>
			/// destructor
			///</summary>
			~Node() = default;
			/// <summary>
			/// the item contained by the Node
			/// </summary>
			value_type _value;

			/// <summary>
			/// the next Node in the list
			/// </summary>
			Node* _next;
		};

		/// <summary>
		/// the Node at the beginning of the list
		/// </summary>
		Node* _front = nullptr;

		/// <summary>
		/// the Node at the end of the list
		/// </summary>
		Node* _back = nullptr;

		/// <summary>
		/// the number of elements in the list
		/// </summary>
		size_t _size = 0;
	};
}

#include "SList.inl"