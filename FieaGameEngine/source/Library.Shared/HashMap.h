#pragma once
#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"
#include "DefaultEquality.h"
#include <utility>
#include "gsl/gsl_util"

namespace fge {
	template<typename TKey, typename TValue, typename HashFunctor = DefaultHash<TKey>>
	class HashMap final {
		friend class Iterator;
		friend class ConstIterator;

		using size_type = size_t;
		using key_type = TKey;
		using value_type = TValue;
		using pair_type = std::pair<const key_type, value_type>;
		using chain_type = SList<pair_type>;
		using hash_func = HashFunctor;
		using equality_func = DefaultEquality<key_type>;
	public:
		/// <summary>
		/// An Iterator that can get references to values within the HashMap
		/// </summary>
		class Iterator final {
			friend HashMap;
			friend class ConstIterator;
			using difference_type = std::ptrdiff_t;
			using value_type = pair_type;
			using reference = const value_type&;
			using pointer = const value_type*;
			using iterator_category = std::forward_iterator_tag;
		public:
			/// <summary>
			/// default constructor
			/// </summary>
			Iterator() = default;
			/// <summary>
			/// copy constructor
			/// </summary>
			/// <param name="other">the Iterator to copy</param>
			Iterator(const Iterator& other);
			/// <summary>
			/// increment operator
			/// </summary>
			/// <returns>the incremented Iterator; iterates through chain nodes before moving to the next chain</returns>
			Iterator operator++();
			/// <summary>
			/// increment operator
			/// </summary>
			/// <returns>the incremented Iterator; iterates through chain nodes before moving to the next chain</returns>
			Iterator operator++(int);
			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>a reference to the value at the Iterator's current position</returns>
			HashMap::pair_type& operator*() const;
			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>a reference to the value at the Iterator's current position</returns>
			HashMap::pair_type* operator->() const;
			/// <summary>
			/// equality comparison operator
			/// </summary>
			/// <param name="other">the Iterator to compare this to</param>
			/// <returns>true if the Iterators share a position within the same container, otherwise false</returns>
			bool operator==(const Iterator& other) const;
			/// <summary>
			/// inequality comparison operator
			/// </summary>
			/// <param name="other">the Iterator to compare this to</param>
			/// <returns>true if the Iterators have different positions within the same container, 
			/// or belong to different containers, otherwise false</returns>
			bool operator!=(const Iterator& other) const;
			/// <summary>
			/// copy assignment operator
			/// </summary>
			/// <param name="other">the Iterator to copy</param>
			Iterator operator=(const Iterator& other);
		private:
			/// <summary>
			/// the HashMap this Iterator is bound to
			/// </summary>
			HashMap* _container;
			/// <summary>
			/// private constructor which makes a HashMap Iterator from an SList Iterator
			/// </summary>
			/// <param name="it">the chain iterator to use</param>
			Iterator(const typename chain_type::Iterator& cit, const size_t chainIndex, HashMap& container);
			/// <summary>
			///	this iterator can navigate the chains
			/// </summary>
			typename chain_type::Iterator _chainIterator;
			/// <summary>
			/// this Iterator can navigate the bucket
			/// </summary>
			typename size_t _chainIndex;
		};
		/// <summary>
		/// An Iterator that can get const references to values within the HashMap
		/// </summary>
		class ConstIterator final {
			friend HashMap;
			using difference_type = std::ptrdiff_t;
			using value_type = pair_type;
			using reference = const value_type&;
			using pointer = const value_type*;
			using iterator_category = std::forward_iterator_tag;
		public:
			/// <summary>
			/// default constructor
			/// </summary>
			ConstIterator() = default;
			/// <summary>
			/// copy constructor
			/// </summary>
			/// <param name="other">the ConstIterator to copy</param>
			ConstIterator(const ConstIterator& other);
			/// <summary>
			/// increment operator
			/// </summary>
			/// <returns>the incremented ConstIterator; iterates through chain nodes before moving to the next chain</returns>
			ConstIterator operator++();
			/// <summary>
			/// increment operator
			/// </summary>
			/// <returns>the incremented ConstIterator; iterates through chain nodes before moving to the next chain</returns>
			ConstIterator operator++(int);
			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>a const reference to the value at the ConstIterator's current position</returns>
			const HashMap::pair_type& operator*() const;
			/// <summary>
			/// dereference operator
			/// </summary>
			/// <returns>a const reference to the value at the ConstIterator's current position</returns>
			const HashMap::pair_type* operator->() const;
			/// <summary>
			/// equality comparison operator
			/// </summary>
			/// <param name="other">the ConstIterator to compare this to</param>
			/// <returns>true if the ConstIterators share a position within the same container, otherwise false</returns>
			bool operator==(const ConstIterator& other) const;
			/// <summary>
			/// inequality comparison operator
			/// </summary>
			/// <param name="other">the ConstIterator to compare this to</param>
			/// <returns>true if the ConstIterators have different positions within the same container, 
			/// or belong to different containers, otherwise false</returns>
			bool operator!=(const ConstIterator& other) const;
			/// <summary>
			/// copy assignment operator
			/// </summary>
			/// <param name="other">the ConstIterator to copy</param>
			ConstIterator operator=(const ConstIterator& other);
			/// <summary>
			/// typecast constructor
			/// </summary>
			/// <param name="other">the Iterator to base this ConstIterator on</param>
			ConstIterator(const Iterator& other);
		private:
			/// <summary>
			/// the HashMap this ConstIterator is bound to
			/// </summary>
			const HashMap* _container = nullptr;
			/// <summary>
			/// private constructor which makes a HashMap Iterator from an SList Iterator
			/// </summary>
			/// <param name="it">the chain iterator to use</param>
			ConstIterator(const typename chain_type::ConstIterator& cit, const size_t chainIndex, const HashMap& container);
			/// <summary>
			/// this ConstIterator can navigate the chains
			/// </summary>
			typename chain_type::ConstIterator _chainIterator;
			/// <summary>
			/// this ConstIterator can navigate the chain vector
			/// </summary>
			size_t _chainIndex = 0;
		};
		/// <summary>
		/// constructor
		/// </summary>
		/// <param name="chains">the initial size of the chain Vector</param>
		explicit HashMap(size_t chains);
		~HashMap() = default;
		HashMap& operator=(const HashMap& other);
		HashMap(const HashMap& other);
		/// <summary>
		/// get the value paired with the given key
		/// </summary>
		/// <param name="key">the key of the desired value</param>
		/// <returns>an Iterator pointing at the value corresponding to the given key</returns>
		Iterator Find(const key_type& key);
		/// <summary>
		/// get the value paired with the given key
		/// </summary>
		/// <param name="key">the key of the desired value</param>
		/// <returns>a ConstIterator pointing at the value corresponding to the given key</returns>
		ConstIterator Find(const key_type& key) const;
		/// <summary>
		/// inserts a key-value pair into the HashMap
		/// </summary>
		/// <param name="pair">the key-value pair to insert</param>
		/// <returns>1) true if a new pair was added, otherwise false 2) an Iterator pointing at the new entry if successful; 
		/// if the key already exists, returns an Iterator pointing to the pair 
		/// with the given key that already exists</returns>
		std::pair<bool, Iterator> Insert(const pair_type& pair);

		std::pair<bool, Iterator> Insert(pair_type&& pair) noexcept;
		/// gets the value associated with the given key
		/// </summary>
		/// <param name="key">the key corresponding to the desired value</param>
		/// <returns>a reference to the value paired with the given key</returns>
		pair_type& operator[](const key_type& key);
		/// <summary>
		/// removes the pair with the given key from the HashMap
		/// </summary>
		/// <param name="key">the key of the pair to remove</param>
		void Remove(const key_type& key);
		/// <summary>
		/// empties the HashMap of all its contents
		/// </summary>
		void Clear();
		/// <summary>
		/// gets the current size of the HashMap
		/// </summary>
		/// <returns>the number of elements in the HashMap</returns>
		size_type Size() const;
		/// <summary>
		/// checks if the HashMap already contains a pair with the given key
		/// </summary>
		/// <param name="key">the key to check for</param>
		/// <returns>true if any entry within the HashMap has the given key, otherwise false</returns>
		bool ContainsKey(const key_type& key) const;
		/// <summary>
		/// gets the value associated with the given key
		/// </summary>
		/// <param name="key">the key corresponding to the desired value</param>
		/// <returns>a reference to the value paired with the given key</returns>
		value_type& At(const key_type& key);
		/// <summary>
		/// gets the value associated with the given key
		/// </summary>
		/// <param name="key">the key corresponding to the desired value</param>
		/// <returns>a const reference to the value paired with the given key</returns>
		const value_type& At(const key_type& key) const;
		/// <summary>
		/// gets a start Iterator
		/// </summary>
		/// <returns>An Iterator pointing at the beginning of the HashMap</returns>
		Iterator begin();
		/// <summary>
		/// gets a start ConstIterator
		/// </summary>
		/// <returns>A ConstIterator pointing at the beginning of the HashMap</returns>
		ConstIterator begin() const;
		/// <summary>
		/// gets a start ConstIterator
		/// </summary>
		/// <returns>A ConstIterator pointing at the beginning of the HashMap</returns>
		ConstIterator cbegin() const;
		/// <summary>
		/// gets an end Iterator
		/// </summary>
		/// <returns>an Iterator pointing to the end of the HashMap</returns>
		Iterator end();
		/// <summary>
		/// gets an end ConstIterator
		/// </summary>
		/// <returns>a ConstIterator pointing to the end of the HashMap</returns>
		ConstIterator end() const;
		/// <summary>
		/// gets an end ConstIterator
		/// </summary>
		/// <returns>a ConstIterator pointing to the end of the HashMap</returns>
		ConstIterator cend() const;
		/// <summary>
		/// resizes the chain Vector to the designated size, then rehashes all elements
		/// </summary>
		/// <param name="newSize">the new size of the chain Vector</param>
		void Resize(size_t newSize);
		/// <summary>
		/// gets the current load factor, collisions will cause this to be inaccurate
		/// </summary>
		/// <returns>the current estimated load factor of the Hashmap</returns>
		float GetLoadFactor() const;
	private:
		/// <summary>
		/// A Vector containing all of the HashMap's chains
		/// </summary>
		Vector<chain_type> _chains;
		/// <summary>
		/// the current number of elements in the HashMap
		/// </summary>
		size_type _size = 0;
		/// <summary>
		/// finds an element within a given chain
		/// </summary>
		/// <param name="key">the key to find</param>
		/// <param name="chain">the chain to search</param>
		/// <returns>an Iterator pointing to the pair with the desired key if found, otherwise end()</returns>
		Iterator FindAt(const key_type& key, size_t chain);
		/// <summary>
		/// finds an element within a given chain
		/// </summary>
		/// <param name="key">the key to find</param>
		/// <param name="chain">the chain to search</param>
		/// <returns>a ConstIterator pointing to the pair with the desired key if found, otherwise end()</returns>
		ConstIterator FindAt(const key_type& key, size_t chain) const;
	};
}


#include "HashMap.inl"