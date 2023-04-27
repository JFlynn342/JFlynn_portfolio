#include "Attributed.h"

namespace fge {

	RTTI_DEFINITIONS(Attributed);

	Signature::Signature(const std::string& name, Datum::DatumType type, size_t size, size_t offset): 
		_name{ name }, _type{ type }, _size{ size }, _offset{ offset } {
	}

	TypeManager* TypeManager::_instance = nullptr;

	TypeManager::TypeManager() :
		// This is a magic number that will eventually need to be exposed to the end user
		_typeData{ 11 } {

	}

	void TypeManager::CreateInstance() {
		_instance = new TypeManager;
	}

	typename TypeManager* TypeManager::GetInstance() {
		return _instance;
	}

	void TypeManager::DestroyInstance() {
		delete _instance;
	}

	void TypeManager::RegisterTypes(const RTTI::IdType id, const Vector<Signature>& s) {
		GetInstance()->_typeData.Insert(std::make_pair(id, s));
	}

	const Signature* TypeManager::GetSignature(const RTTI::IdType id, const std::string& name) {
		const Vector<Signature>& signatures = GetAllSignatures(id);
		for (size_t i = 0; i < signatures.size(); ++i) {
			if (signatures[i]._name == name) {
				return &signatures[i];
			}
		}
		return nullptr;
	}

	const Vector<Signature>& TypeManager::GetAllSignatures(const RTTI::IdType id)
	{
		return GetInstance()->_typeData.Find(id)->second;
	}


	Attributed::~Attributed()
	{
		Scope::~Scope();
	}

	Attributed::Attributed(const Attributed& other):
	Scope(other) {
		UpdateExternalStorage(other.TypeIdInstance());
	}

	Attributed& Attributed::operator=(const Attributed& other)
	{
		assert(this != &other);
		Scope::operator=(other);
		UpdateExternalStorage(other.TypeIdInstance());
		return *this;
	}

	Attributed::Attributed(Attributed&& other) noexcept:
		Scope(other) {
		UpdateExternalStorage(other.TypeIdInstance());
	}

	Attributed& Attributed::operator=(Attributed&& other) noexcept {
		assert(this != &other);
		*static_cast<Scope*>(this) = other;
		UpdateExternalStorage(other.TypeIdInstance());
		return *this;
	}

	bool Attributed::IsAttribute(const std::string& name) const {
		return (Find(name) != nullptr);
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name) const {
		return(name == "this" || TypeManager::GetInstance()->GetSignature(TypeIdInstance(), name) != nullptr);
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& name) const {
		return (!IsPrescribedAttribute(name) && IsAttribute(name));
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name) {
		return Append(name);
	}

	const Vector<Scope::pair_type*>& Attributed::GetAllAttributes() const {
		return GetOrder();
	}

	const std::pair<size_t, Datum*> Attributed::GetFirstAuxiliaryAttribute() const
	{
		for (size_t i = 0; i < GetOrder().size(); ++i) {
			if (IsAuxiliaryAttribute(GetOrder()[i]->first)) {
				return std::make_pair(i, &GetOrder()[i]->second);
			}
		}
		return std::make_pair(GetOrder().size(), nullptr);
	}

	const std::pair<size_t, Datum*> Attributed::GetLastAuxiliaryAttribute() const
	{
		assert(GetOrder().size() > 0);
		std::string temp = GetOrder().back()->first;
		if (IsAuxiliaryAttribute(temp)) {
			return std::make_pair(GetOrder().size() - 1, &GetOrder().back()->second);
		}
		else return std::make_pair(GetOrder().size(), nullptr);
	}


	Attributed::Attributed(RTTI::IdType id) {
		Populate(TypeManager::GetAllSignatures(id));
	}

	void Attributed::UpdateExternalStorage(RTTI::IdType id) {
		this->Append("this") = this;
		for (size_t i = 0; i < GetOrder().size(); ++i) {
			Scope::pair_type& p = *GetOrder()[i];
			if (TypeManager::GetInstance()->GetSignature(id, p.first) != nullptr) {
				if (p.second.IsExternalStorage()) {
					p.second.SetStorage(reinterpret_cast<std::byte*>(this) + TypeManager::GetInstance()->GetSignature(id, p.first)->_offset, p.second.Capacity(), p.second.Capacity());
				}
			}
		}
	}

	void Attributed::Populate(const Vector<Signature>& attributes) {
		this->Append("this") = this;
		for (size_t i = 0; i < attributes.size(); ++i) {
			if (attributes[i]._type != Datum::DatumType::Table) {
				Datum& newDatum = Append(attributes[i]._name);
				newDatum.SetType(attributes[i]._type);
				if (attributes[i]._offset != 0) {
					assert(newDatum.Type() != Datum::DatumType::Table);
					newDatum.SetStorage(reinterpret_cast<std::byte*>(this) + attributes[i]._offset, attributes[i]._size, attributes[i]._size);
				}
			}
			else {
				for (size_t j = 0; j < attributes[i]._size; ++j) {
					AppendScope(attributes[i]._name);
				}
			}
		}
	}
}