#include "HashMap.h"


namespace fge {

	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>::HashMap(size_t chains) {
		if (chains <= 1) {
			throw std::invalid_argument("invalid number of chains");
		}
		_chains.Reserve(chains);
		for (size_t i = 0; i < chains; i++) {
			_chains.push_back(chain_type());
		}
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>& HashMap<TKey, TValue, HashFunctor>::operator=(const HashMap& other)
	{
		Clear();
		_chains.Clear();
		_chains.ShrinkToFit();
		_chains.Reserve(other._chains.Capacity());
		for (size_t i = 0; i < other._chains.size(); ++i) {
			_chains.push_back(chain_type());
			for (typename chain_type::ConstIterator it = other._chains[i].begin(); it != other._chains[i].end(); ++it) {
				_chains[i].PushBack(*it);
			}
		}
		return *this;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>::HashMap(const HashMap& other)
	{
		_chains.Reserve(other._chains.Capacity());
		for (size_t i = 0; i < other._chains.size(); ++i) {
			_chains.push_back(chain_type());
			for (typename chain_type::ConstIterator it = other._chains[i].begin(); it != other._chains[i].end(); ++it) {
				_chains[i].PushBack(*it);
			}
		}
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Find(const key_type& key) {
		hash_func hash;
		size_t chainIndex = hash(key) % _chains.size();
		return FindAt(key, chainIndex);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::Find(const key_type& key) const {
		hash_func hash;
		size_t chainIndex = hash(key) % _chains.size();
		return FindAt(key, chainIndex);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline std::pair<bool, typename HashMap<TKey, TValue, HashFunctor>::Iterator> HashMap<TKey, TValue, HashFunctor>::Insert(const pair_type& pair) {
		hash_func hash;
		size_t chain = hash(pair.first) % _chains.size();
		Iterator it = FindAt(pair.first, chain);
		if (it != end()) {
			return std::pair<bool, Iterator>(false, it);
		}
		_chains[chain].PushBack(pair);
		it = FindAt(pair.first, chain);
		++_size;
		return std::pair<bool, Iterator>(true, it);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline std::pair<bool, typename HashMap<TKey, TValue, HashFunctor>::Iterator> HashMap<TKey, TValue, HashFunctor>::Insert(pair_type&& pair) noexcept
	{
		hash_func hash;
		size_t chain = hash(pair.first) % _chains.size();
		Iterator it = FindAt(pair.first, chain);
		if (it != end()) {
			return std::pair<bool, Iterator>(false, it);
		}
		_chains[chain].PushBack(std::forward<pair_type>(pair));
		it = FindAt(pair.first, chain);
		++_size;
		return std::pair<bool, Iterator>(true, it);
	}


	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::pair_type& HashMap<TKey, TValue, HashFunctor>::operator[](const key_type& key) {
		return (*((Insert(pair_type(key, value_type())).second)));
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline void HashMap<TKey, TValue, HashFunctor>::Remove(const key_type& key) {
		hash_func hash;
		equality_func equal;
		chain_type& chain = _chains[hash(key) % _chains.size()];
		for (typename chain_type::Iterator it = chain.begin(); it != chain.end(); ++it) {
			if (equal((*it).first, key)) {
				chain.Remove(*it);
				--_size;
				return;
			}
		}
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline void HashMap<TKey, TValue, HashFunctor>::Clear() {
		
		for (size_t i = 0; i < _chains.size(); ++i) {
			_chains[i].Clear();
		}
		_size = 0;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::size_type HashMap<TKey, TValue, HashFunctor>::Size() const {
		return _size;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor>::ContainsKey(const key_type& key) const {
		hash_func hash;
		equality_func equal;
		typename chain_type::Iterator it;
		chain_type chain = _chains[hash(key) % _chains.size()];
		for (it = chain.begin(); it != chain.end(); it++) {
			if (equal((*it).first, key)) {
				return true;
			}
		}
		return false;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::value_type& HashMap<TKey, TValue, HashFunctor>::At(const key_type& key) {
		return (*(Find(key))).second;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline const typename HashMap<TKey, TValue, HashFunctor>::value_type& HashMap<TKey, TValue, HashFunctor>::At(const key_type& key) const {
		return (*(Find(key))).second;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::begin() {
		Iterator it(_chains[0].begin(), 0, *this);
		if (_chains[0].Size() == 0) {
			++it;
		}
		return it;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::begin() const {
		ConstIterator it(_chains[0].begin(), 0, *this);
		if (_chains[0].Size() == 0) {
			return ++it;
		}
		return it;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::cbegin() const {
		ConstIterator it(_chains[0].begin(), 0, *this);
		if (_chains[0].Size() == 0) {
			++it;
		}
		return it;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::end() {
		return Iterator(chain_type::Iterator(), _chains.size(), *this);
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::end() const {
		return ConstIterator(chain_type::ConstIterator(), _chains.size(), *this);
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::cend() const {
		return ConstIterator(chain_type::ConstIterator(), _chains.size(), *this);
	}


	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const Iterator& other) {
		_chainIterator = other._chainIterator;
		_chainIndex = other._chainIndex;
		_container = other._container;
	}


	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Iterator::operator=(const Iterator& other) {
		_chainIterator = other._chainIterator;
		_chainIndex = other._chainIndex;
		_container = other._container;
		return *this;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>::ConstIterator::ConstIterator(const ConstIterator& other) {
		_chainIterator = other._chainIterator;
		_chainIndex = other._chainIndex;
		_container = other._container;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::ConstIterator::operator=(const ConstIterator& other) {
		_chainIterator = other._chainIterator;
		_chainIndex = other._chainIndex;
		_container = other._container;
		return *this;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const typename chain_type::Iterator& ci, const size_t chainIndex, HashMap& container) {
		_chainIndex = chainIndex;
		_chainIterator = ci;
		_container = &container;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>::ConstIterator::ConstIterator(const typename chain_type::ConstIterator& cit, const size_t chainIndex, const HashMap& container) {
		_chainIndex = chainIndex;
		_chainIterator = cit;
		_container = &container;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline HashMap<TKey, TValue, HashFunctor>::ConstIterator::ConstIterator(const Iterator& other) {
		_container = other._container;
		_chainIterator = chain_type::ConstIterator(other._chainIterator);
		_chainIndex = other._chainIndex;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Iterator::operator++() {
		// check if already at end()
		if (_chainIndex != _container->_chains.size()) {
			// if so, increment at least once if possible
			if (_chainIterator != _container->_chains[_chainIndex].end()) {
				++_chainIterator;
			}
			// but if this brings us to the end of the chain...
			if (_chainIterator == _container->_chains[_chainIndex].end()) {
				// move over again
				++_chainIndex;
				// then, if we aren't at end()...
				if (_chainIndex != _container->_chains.size()) {
					// if the current chain has at least one element...
					if (_container->_chains[_chainIndex].Size() > 0) {
						// stop here at set the chain iterator to the start of the current chain
						_chainIterator = _container->_chains[_chainIndex].begin();
					}
					else {
						// otherwise keep incrementing until we find a chain with an element
						while (_container->_chains[_chainIndex].Size() == 0) {
							++_chainIndex;
							if (_chainIndex == _container->_chains.size()) {
								// set this Iterator to end()
								_chainIterator = chain_type::Iterator();
								break;
							}
							else if (_container->_chains[_chainIndex].Size() > 0) {
								// when a non-empty chain is found, set the Iterator to its start
								_chainIterator = _container->_chains[_chainIndex].begin();
							}
						}
					}
				}
				else {
					// set this Iterator to end()
					_chainIterator = chain_type::Iterator();
				}
			}
		}
		else {
			// set this Iterator to end()
			_chainIterator = chain_type::Iterator();
		}

		return *this;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Iterator::operator++(int) {
		Iterator temp = *this;
		// check if already at end()
		if (_chainIndex != _container->_chains.size()) {
			// if so, increment at least once
			if (_chainIterator != _container->_chains[_chainIndex].end()) {
				++_chainIterator;
			}
			// but if this brings us to the end of the chain...
			if (_chainIterator == _container->_chains[_chainIndex].end()) {
				// move over again
				++_chainIndex;
				// then, if we aren't at end()...
				if (_chainIndex != _container->_chains.size()) {
					// if the current chain has at least one element...
					if (_container->_chains[_chainIndex].Size() > 0) {
						// stop here at set the chain iterator to the start of the current chain
						_chainIterator = _container->_chains[_chainIndex].begin();
					}
					else {
						// otherwise keep incrementing until we find a chain with an element
						while (_container->_chains[_chainIndex].Size() == 0) {
							++_chainIndex;
							if (_chainIndex == _container->_chains.size()) {
								// set this Iterator to end()
								_chainIterator = chain_type::Iterator();
								break;
							}
							else if (_container->_chains[_chainIndex].Size() > 0) {
								// when a non-empty chain is found, set the Iterator to its start
								_chainIterator = _container->_chains[_chainIndex].begin();
							}
						}
					}
				}
				else {
					// set this Iterator to end()
					_chainIterator = chain_type::Iterator();
				}
			}
		}
		else {
			// set this Iterator to end()
			_chainIterator = chain_type::Iterator();
		}
		return temp;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::ConstIterator::operator++() {
		// check if already at end()
		if (_chainIndex != _container->_chains.size()) {
			// if so, increment at least once
			if (_chainIterator != _container->_chains[_chainIndex].end()) {
				++_chainIterator;
			}
			// but if this brings us to the end of the chain...
			if (_chainIterator == _container->_chains[_chainIndex].end()) {
				// move over again
				++_chainIndex;
				// then, if we aren't at end()...
				if (_chainIndex != _container->_chains.size()) {
					// if the current chain has at least one element...
					if (_container->_chains[_chainIndex].Size() > 0) {
						// stop here at set the chain iterator to the start of the current chain
						_chainIterator = _container->_chains[_chainIndex].begin();
					}
					else {
						// otherwise keep incrementing until we find a chain with an element
						while (_container->_chains[_chainIndex].Size() == 0) {
							++_chainIndex;
							if (_chainIndex == _container->_chains.size()) {
								// set this Iterator to end()
								_chainIterator = chain_type::ConstIterator();
								break;
							}
							else if (_container->_chains[_chainIndex].Size() > 0) {
								// when a non-empty chain is found, set the Iterator to its start
								_chainIterator = _container->_chains[_chainIndex].begin();
							}
						}
					}
				}
				else {
					// set this Iterator to end()
					_chainIterator = chain_type::ConstIterator();
				}
			}
		}
		else {
			// set this Iterator to end()
			_chainIterator = chain_type::ConstIterator();
		}
		return *this;
	}
	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::ConstIterator::operator++(int) {
		ConstIterator temp = *this;
		// check if already at end()
		if (_chainIndex != _container->_chains.size()) {
			// if so, increment at least once
			if (_chainIterator != _container->_chains[_chainIndex].end()) {
				++_chainIterator;
			}
			// but if this brings us to the end of the chain...
			if (_chainIterator == _container->_chains[_chainIndex].end()) {
				// move over again
				++_chainIndex;
				// then, if we aren't at end()...
				if (_chainIndex != _container->_chains.size()) {
					// if the current chain has at least one element...
					if (_container->_chains[_chainIndex].Size() > 0) {
						// stop here at set the chain iterator to the start of the current chain
						_chainIterator = _container->_chains[_chainIndex].begin();
					}
					else {
						// otherwise keep incrementing until we find a chain with an element
						while (_container->_chains[_chainIndex].Size() == 0) {
							++_chainIndex;
							if (_chainIndex == _container->_chains.size()) {
								// set this Iterator to end()
								_chainIterator = chain_type::ConstIterator();
								break;
							}
							else if (_container->_chains[_chainIndex].Size() > 0) {
								// when a non-empty chain is found, set the Iterator to its start
								_chainIterator = _container->_chains[_chainIndex].begin();
							}
						}
					}
				}
				else {
					// set this Iterator to end()
					_chainIterator = chain_type::ConstIterator();
				}
			}
		}
		else {
			// set this Iterator to end()
			_chainIterator = chain_type::ConstIterator();
		}
		return temp;
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator==(const Iterator& other) const {
		return(_container == other._container && _chainIterator == other._chainIterator && _chainIndex == other._chainIndex);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor>::ConstIterator::operator==(const ConstIterator& other) const {
		return(_container == other._container && _chainIterator == other._chainIterator && _chainIndex == other._chainIndex);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator!=(const Iterator& other) const {
		return(!(*this == other));
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline bool HashMap<TKey, TValue, HashFunctor>::ConstIterator::operator!=(const ConstIterator& other) const {
		return(!(*this == other));
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::pair_type& HashMap<TKey, TValue, HashFunctor>::Iterator::operator*() const {
		if (*this == _container->end()) {
			throw std::out_of_range("Attempted to dereference end()");
		}
		return (*_chainIterator);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline const typename HashMap<TKey, TValue, HashFunctor>::pair_type& HashMap<TKey, TValue, HashFunctor>::ConstIterator::operator*() const {
		if (*this == _container->end()) {
			throw std::out_of_range("Attempted to dereference end()");
		}
		return (*_chainIterator);
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline void HashMap<TKey, TValue, HashFunctor>::Resize(size_t newSize) {
		if (newSize == _chains.size()) {
			return;
		}
		Vector<pair_type> contents;
		contents.Reserve(Size());
		for (Iterator it = begin(); it != end(); ++it) {
			if(it != end()) {
				contents.push_back(*it);
			}
		}
		Clear();
		_chains.ShrinkToFit();
		_chains.Reserve(newSize);
		while (_chains.size() < _chains.Capacity()) {
			_chains.push_back(SList<pair_type>());
		}
		for (size_t i = 0; i < contents.size(); i++) {
			Insert(contents[i]);
		}
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline float HashMap<TKey, TValue, HashFunctor>::GetLoadFactor() const {
		return gsl::narrow_cast<float>(Size()) / gsl::narrow_cast<float>(_chains.size());
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::FindAt(const key_type& key, size_t chain)
	{
		equality_func equal;
		typename chain_type::Iterator cit = _chains[chain].begin();
		if (_chains[chain].Size() > 0) {
			while (cit != _chains[chain].end()) {
				if (equal((*cit).first, key)) {
					return Iterator(cit, chain, *this);
				}
				++cit;
			}
		}
		return end();
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::ConstIterator HashMap<TKey, TValue, HashFunctor>::FindAt(const key_type& key, size_t chain) const
	{
		equality_func equal;
		typename chain_type::ConstIterator cit = _chains[chain].begin();
		if (_chains[chain].Size() > 0) {
			while (cit != _chains[chain].end()) {
				if (equal((*cit).first, key)) {
					return ConstIterator(cit, chain, *this);
				}
				++cit;
			}
		}
		return end();
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline typename HashMap<TKey, TValue, HashFunctor>::pair_type* HashMap<TKey, TValue, HashFunctor>::Iterator::operator->() const {
		return &this->operator*();
	}

	template<typename TKey, typename TValue, typename HashFunctor>
	inline const typename HashMap<TKey, TValue, HashFunctor>::pair_type* HashMap<TKey, TValue, HashFunctor>::ConstIterator::operator->() const {
		return &this->operator*();
	}
}