#include <stdexcept>

template<typename T>
inline void fge::SList<T>::PushFront(const T& value) {
	Node* newFront = new Node(value, _front);
	if (_size == 0) {
		_back = newFront;
	}
	_front = newFront;
	_size++;
}

template<typename T>
inline void fge::SList<T>::PopFront() {
	
	if (_size > 1) {
		Node oldFrontCopy = *_front;
		Node* oldFrontPointer = _front;
		_front = oldFrontPointer->_next;
		delete oldFrontPointer;
		_size--;
		if (_size == 1) {
			_back = _front;
		}
	}
	else if (_size == 1) {
		Node oldFrontCopy = *_front;
		delete _front;
		_back = nullptr;
		_front = nullptr;
		_size = 0;
	}
	else throw std::runtime_error("list is empty");
}

template<typename T>
inline void fge::SList<T>::PushBack(const T& value) {
	Node* newBack = new Node(value, nullptr);
	if (_size == 0) {
		_front = newBack;
	}
	else {
		_back->_next = newBack;
	}
	_back = newBack;
	_size++;
}

template<typename T>
inline bool fge::SList<T>::IsEmpty() const{
	return _size == 0;
}

template<typename T>
inline T& fge::SList<T>::Front() {
	if (_size > 0) {
		return _front->_value;}
	else throw std::runtime_error("list is empty");
}

template<typename T>
inline T& fge::SList<T>::Back() {
	if (_size > 0) {
		return _back->_value;}
	else throw std::runtime_error("list is empty");
}

template<typename T>
inline size_t fge::SList<T>::Size() const {
	return _size;
}

template<typename T>
inline fge::SList<T>::SList(const SList& other) {
	if (&other != nullptr) {
		if (other._front == nullptr) {
			_front = nullptr;
			_back = nullptr;
			_size = 0;
			return;
		}

		Node* currentOtherNode = other._front;
		_front = new Node(currentOtherNode->_value, nullptr);
		Node* currentCopyNode = _front;
		while (currentOtherNode != other._back) {
			currentCopyNode->_next = new Node(currentOtherNode->_next->_value, nullptr);
			currentCopyNode = currentCopyNode->_next;
			currentOtherNode = currentOtherNode->_next;
		}
		_back = currentCopyNode;
		_size = other._size;
	}

}

template<typename T>
inline fge::SList<T>& fge::SList<T>::operator=(const fge::SList<T>& other) {
	if (this != &other) {
		Clear();
		Node* currentOtherNode = other._front;
		_front = new Node(currentOtherNode->_value, nullptr);
		Node* currentCopyNode = _front;
		while (currentOtherNode != other._back) {
			currentCopyNode->_next = new Node(currentOtherNode->_next->_value, nullptr);
			currentCopyNode = currentCopyNode->_next;
			currentOtherNode = currentOtherNode->_next;
		}
		_back = currentCopyNode;
		_size = other._size;
	}
	return *this;
}

template<typename T>
inline fge::SList<T>::~SList() {
	Clear();
}

template<typename T>
inline void fge::SList<T>::Clear() {
	while (_size > 0) {
		PopBack();
	}
}

template<typename T>
inline void fge::SList<T>::PopBack() {
	
	if (_size < 1) {
		throw std::runtime_error("list is empty");
	}
	else if (_size == 1) {
		PopFront();
		return;
	}
	
	Node oldBackCopy = *_back;
	Node* oldBackPointer = _back;
	Node* newBack = _front;
	while (newBack->_next != _back) {
		newBack = newBack->_next;
	}
	newBack->_next = nullptr;
	_back = newBack;
	delete oldBackPointer;
	_size--;
	if (_size == 1) {
		_front = _back;
	}
		
}

template<typename T>
inline fge::SList<T>::Node::Node(T value, Node* next):
_value(value),
_next(next)
{

}


template<typename T>
inline fge::SList<T>::Iterator::Iterator(const fge::SList<T>* container, Node* node) {
	_container = container;
	_node = node;
}

template<typename T>
inline fge::SList<T>::ConstIterator::ConstIterator(const fge::SList<T>* container, Node* node) {
	_container = container;
	_node = node;
}

template<typename T>
inline typename fge::SList<T>::Iterator fge::SList<T>::begin() {
	Iterator it(this, _front);
	return it;
}

template<typename T>
inline typename fge::SList<T>::Iterator fge::SList<T>::end() {
	Iterator it(this, _back);
	if (_size > 0) {
		++it;
	}
	return it;
}

template<typename T>
inline typename fge::SList<T>::ConstIterator fge::SList<T>::begin() const{
	ConstIterator it(this, _front);
	return it;
}

template<typename T>
inline typename fge::SList<T>::ConstIterator fge::SList<T>::end() const{
	ConstIterator it(this, _back);
	if (_size > 0) {
		it++;
	}
	return it;
}
template<typename T>
inline typename fge::SList<T>::ConstIterator fge::SList<T>::cbegin() const {
	ConstIterator it(this, _front);
	return it;
}

template<typename T>
inline typename fge::SList<T>::ConstIterator fge::SList<T>::cend() const {
	ConstIterator it(this, _back);
	if (_size > 0) {
		it++;
	}
	return it;
}

template<typename T>
inline typename fge::SList<T>::Iterator fge::SList<T>::InsertAfter(const T& value, Iterator position) {
	if (position._container != this) {
		throw std::runtime_error("container mismatch");
	}
	if (position == end()) {
		PushBack(value);
		SList<T>::Iterator it(this, _back);
		return it;
	}
	if (_size == 0) {
		PushFront(value);
		SList<T>::Iterator it(this, _front);
		return it;
	}
	Node* after = position._node->_next;
	position._node->_next = new Node(value, after);
	_size++;
	SList<T>::Iterator it(this, position._node->_next);
	return it;
}

template<typename T>
inline typename fge::SList<T>::Iterator fge::SList<T>::Find(const T& value) {
	fge::SList<T>::Iterator it = begin();
	for (size_t i = 0; i < Size(); ++i) {
		if (equality_func()(*it, value)) {
			return it;
		}
		++it;
	}
	return it;
}

template<typename T>
inline typename fge::SList<T>::ConstIterator fge::SList<T>::Find(const T& value) const {
	fge::SList<T>::ConstIterator it = begin();
	fge::SList<T>::ConstIterator it1 = end();
	while (it != it1) {
		if (*it == value) {
			return it;
		}
		it++;
	}
	return it;
}

template<typename T>
inline void fge::SList<T>::Remove(const T& value) {
	fge::SList<T>::Iterator it = Find(value);
	if (it == end()) {
		return;
	}
	if (it._node == _front) {
		PopFront();
		return;
	}
	else if (it._node == _back) {
		PopBack();
		return;
	}
	fge::SList<T>::Node* previous = _front;
	while (previous->_next != it._node) {
		previous = previous->_next;
	}
	fge::SList<T>::Node* target = it._node;
	fge::SList<T>::Node* next = (++it)._node;
	delete target;
	previous->_next = next;
	_size--;
}
template<typename T>
inline typename fge::SList<T>::Iterator fge::SList<T>::Iterator::operator++() {
	if (_node != nullptr) {
		_node = _node->_next;
		return *this;
	}
	else throw std::runtime_error("Iterator already at end of list");
}

template<typename T>
inline typename fge::SList<T>::Iterator fge::SList<T>::Iterator::operator++(int) {
	if (_node != nullptr) {
		_node = _node->_next;
		return *this;
	}
	else throw std::runtime_error("Iterator already at end of list");
}

template<typename T>
inline T& fge::SList<T>::Iterator::operator*() const {
	if (_node != nullptr) {
		return _node->_value;
	}
	else throw std::out_of_range("attempted to dereference an iterator that has passed the end of the list");
}

template<typename T>
inline bool fge::SList<T>::Iterator::operator!=(const fge::SList<T>::Iterator& other) const {
	if (_container != other._container) {
		return true;
	}
	else return _node != other._node;
}

template<typename T>
inline bool fge::SList<T>::Iterator::operator==(const fge::SList<T>::Iterator& other) const {
	if (_container != other._container) {
		return false;
	}
	else return _node == other._node;
}

template<typename T>
inline typename fge::SList<T>::ConstIterator fge::SList<T>::ConstIterator::operator++() {
	if (_node != nullptr) {
		_node = _node->_next;
		return *this;
	}
	else throw std::runtime_error("Iterator already at end of list");
}

template<typename T>
inline typename fge::SList<T>::ConstIterator fge::SList<T>::ConstIterator::operator++(int) {
	if (_node != nullptr) {
		_node = _node->_next;
		return *this;
	}
	else throw std::runtime_error("Iterator already at end of list");
}

template<typename T>
inline const T& fge::SList<T>::ConstIterator::operator*() const {
	if (_node != nullptr) {
		return _node->_value;
	}
	else throw std::runtime_error("attempted to dereference an iterator that has passed the end of the list");
}

template<typename T>
inline bool fge::SList<T>::ConstIterator::operator!=(const fge::SList<T>::ConstIterator& other) const {
	if (_container != other._container) {
		return true;
	}
	else return _node != other._node;
}

template<typename T>
inline bool fge::SList<T>::ConstIterator::operator==(const fge::SList<T>::ConstIterator& other) const {
	if (_container != other._container) {
		return false;
	}
	else return _node == other._node;
}

template<typename T>
inline fge::SList<T>::ConstIterator::ConstIterator(const fge::SList<T>::Iterator& other) :
	_container{ other._container },
	_node{ other._node }
{

}
