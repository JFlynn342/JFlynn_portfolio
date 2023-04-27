#include "Scope.h"

namespace fge {
	RTTI_DEFINITIONS(Scope);

	Scope::Scope(size_t capacity):
		_map {HashMap<std::string, Datum>(capacity)} {
		_order.Reserve(capacity);
	}
	Scope::~Scope() {
		Clear();
	}
	Scope::Scope(const Scope& other):
		_map{other._map} {
		_map.Clear();
		_order.Reserve(other._order.size());
		for (size_t i = 0; i < other._order.size(); ++i) {
			Append(other._order[i]->first) = other._order[i]->second;
		}
		CloneChildren clone;
		other.ForAllChildScopes(&clone, this);
	}
	Scope& Scope::operator=(const Scope& other) {
		Clear();
		for (size_t i = 0; i < other._order.size(); ++i) {
			Append(other._order[i]->first) = other._order[i]->second;
		}
		CloneChildren clone;
		other.ForAllChildScopes(&clone, this);
		return *this;
	}
	Scope::Scope(Scope&& other) noexcept:
		_map{ other._map } {
		_order = other._order;
		Scope* parent = other.GetParent();
		if(parent != nullptr) {
			std::string name = other.GetParent()->_order[other.GetParent()->FindContainedScope(other).second]->first;
			Scope* orphan = other.GetParent()->Orphan(other);
			parent->Adopt(*this, name);
			delete orphan;
		}
	}
	Scope& Scope::operator=(Scope&& other) noexcept {
		Clear();
		_map = other._map;
		_order = other._order;
		Scope* parent = other.GetParent();
		if (parent != nullptr) {
			std::string name = other.GetParent()->_order[other.GetParent()->FindContainedScope(other).second]->first;
			Scope* orphan = other.GetParent()->Orphan(other);
			parent->Adopt(*this, name);
			delete orphan;
		}
		return *this;
	}
	Datum* Scope::Find(const std::string& name) {
		HashMap<std::string, Datum>::Iterator it = _map.Find(name);
		if (it != _map.end()) {
			return &it->second;
		}
		return nullptr;
	}
	const Datum* Scope::Find(const std::string& name) const {
		HashMap<std::string, Datum>::ConstIterator it = _map.Find(name);
		if (it != _map.end()) {
			return &it->second;
		}
		return nullptr;
	}
	Datum* Scope::Search(const std::string& name) {
		Datum* d = Find(name);
		if (d != nullptr) {
			return d;
		}
		if (_parent != nullptr) {
			return _parent->Search(name);
		}
		return nullptr;
	}
	Datum* Scope::Search(const std::string& name, Scope** outScope)
	{
		Datum* d = Find(name);
		if (d != nullptr) {
			*outScope = this;
			return d;
		}
		if (_parent != nullptr) {
			return _parent->Search(name, outScope);
		}
		return nullptr;
	}
	const Datum* Scope::Search(const std::string& name) const
	{
		const Datum* d = Find(name);
		if (d != nullptr) {
			return d;
		}
		if (_parent != nullptr) {
			return _parent->Search(name);
		}
		return nullptr;
	}
	Datum& Scope::Append(const std::string& name) {
		auto&& [success, it] = _map.Insert(std::make_pair(name, Datum()));
		if (success) {
			_order.push_back(&*it);
		}
		return it->second;
	}
	Scope& Scope::AppendScope(const std::string& name) {
		Datum* d = Find(name);
		if (d != nullptr) {
			assert(d->Type() == Datum::DatumType::Table);
		}
		return Adopt(*new Scope, name);
	}
	Scope& Scope::Adopt(Scope& child, const std::string& name) {
		if (child.GetParent() != nullptr) {
			Scope* orphan = child.GetParent()->Orphan(child);
			orphan;
		}
		assert(!child.IsAncestorOf(*this));
		HashMap<std::string, Datum>::Iterator it = _map.Find(name);
		if (it != _map.end()) {
			if (it->second.Type() == Datum::DatumType::Table) {
				it->second.PushTable(&child);
				child._parent = this;
			}
			else assert(false);
		}
		else {
			Datum& d = Append(name);
			d.SetType(Datum::DatumType::Table);
			child._parent = this;
			d.Resize(1);
			d.Set(&child);
		}
		return child;
	}

	Scope* Scope::GetParent()
	{
		return _parent;
	}

	const Scope* Scope::GetParent() const
	{
		return _parent;
	}


	Datum& Scope::operator[](const std::string& name) {
		return Append(name);
	}
	Datum& Scope::operator[](size_t index) {
		return _order.At(index)->second;
	}
	const Datum& Scope::operator[](size_t index) const {
		return _order.At(index)->second;
	}
	bool Scope::operator==(const Scope& other) const {
		if (_order.size() == other._order.size()) {
			for (size_t i = 0; i < _order.size(); ++i) {
				if (_order[i]->second != other._order[i]->second) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	bool Scope::operator!=(const Scope& other) const {
		return !(*this == other);
	}
	std::pair<Datum*, size_t> Scope::FindContainedScope(const Scope& value) {
		for (size_t i = 0; i < _order.size(); ++i) {
			if (_order[i]->second.Type() == Datum::DatumType::Table) {
				for (size_t j = 0; j < _order[i]->second.Size(); ++j) {
					if (_order[i]->second.As<Scope*>(j) == &value) {
						return std::make_pair(&_order[i]->second, i);
					}
				}
			}
		}
		return std::make_pair(nullptr, 0);
	}
	std::pair<const Datum*, size_t> Scope::FindContainedScope(const Scope& value) const {
		for (size_t i = 0; i < _order.size(); ++i) {
			if (_order[i]->second.Type() == Datum::DatumType::Table) {
				for (size_t j = 0; j < _order[i]->second.Size(); ++j) {
					if (_order[i]->second.As<Scope*>(j) == &value) {
						return std::make_pair(&_order[i]->second, i);
					}
				}
			}
		}
		return std::make_pair(nullptr, 0);
	}
	Scope* Scope::Orphan(Scope& child) {
		auto&&[datum, index] = FindContainedScope(child);
		Datum& d = _order[index]->second;
		d.Remove(&child);
		child._parent = nullptr;
		return &child;
	}
	Scope* Scope::Clone() const {
		return new Scope(*this);
	}

	size_t Scope::Size() const
	{
		return _order.size();
	}

	const Vector<Scope::pair_type*>& Scope::GetOrder() const {
		return _order;
	}

	void Scope::ForAllChildScopes(Scope::ChildFunctor* operation, Scope* other) const {
		for (size_t i = 0; i < _order.size(); ++i) {
			if (_order[i]->second.Type() == Datum::DatumType::Table) {
				operation->operator()(*_order[i], other);
			}
		}
	}
	void Scope::Clear() {
		DeleteChildren deletor;
		ForAllChildScopes(&deletor);
		_order.Clear();
		_map.Clear();
	}

	bool Scope::IsAncestorOf(const Scope& other) const {
		const Datum* foundScope = FindContainedScope(other).first;
		if (foundScope != nullptr) {
			return true;
		}
		for (size_t i = 0; i < _order.size(); ++i) {

			if (_order[i]->second.Type() == Datum::DatumType::Table) {
				for (size_t j = 0; j < _order[i]->second.Size(); ++j) {
					if (_order[i]->second.As<Scope*>(j)->IsAncestorOf(other)) {
						return true;
					}
				}
			}

		}
		return false;
	}
	void Scope::CloneChildren::operator()(pair_type& table, Scope* other) {
		auto& [name, datum] = table;
		assert(datum.Size() > 0);
		if (other != nullptr) {
			other->Find(name)->Clear();
			for (size_t i = 0; i < datum.Size(); ++i) {
				other->Adopt(*datum.As<Scope*>(i)->Clone(), name);
			}
		}
	}
	void Scope::DeleteChildren::operator()(pair_type& table, Scope* other) {
		other;
		auto& [name, datum] = table;
		for (size_t i = 0; i < datum.Size(); ++i) {
			delete datum.As<Scope*>(i);
		}
	}
	void Scope::ChildFunctor::operator()(pair_type& table, Scope* other) {
		table, other;
	}
}