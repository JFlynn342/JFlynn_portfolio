#pragma once
#include "Scope.h"
namespace fge {
	/// <summary>
	/// Contains information about a prescribed attribute
	/// </summary>
	class Signature {
	public:
		Signature(const std::string& name, Datum::DatumType type, size_t size, size_t offset);
		std::string _name;
		Datum::DatumType _type;
		size_t _size;
		size_t _offset;
	};

	/// <summary>
	/// Contains signatures for all prescribed attributes for all Attributed-derived classes
	/// </summary>
	class TypeManager {
	public:
		/// <summary>
		/// creates the global TypeManager instance
		/// </summary>
		static void CreateInstance();
		/// <summary>
		/// gets the active instance of the TypeManager
		/// </summary>
		/// <returns>a pointer to the instance</returns>
		static TypeManager* GetInstance();
		/// <summary>
		/// deletes the TypeManager instance
		/// </summary>
		static void DestroyInstance();
		/// <summary>
		/// registers signatures with the TypeManager
		/// </summary>
		/// <param name="id">the typeId to associate the attribute with</param>
		/// <param name="s">the Signatures to register</param>
		static void RegisterTypes(const RTTI::IdType id, const Vector<Signature>& s);
		/// <summary>
		/// gets the signature with the given name
		/// </summary>
		/// <param name="name">the name to search for</param>
		/// <returns>a pointer to the Signature if found, nullptr otherwise</returns>
		const Signature* GetSignature(const RTTI::IdType id, const std::string& name);
		/// <summary>
		/// gets all signatures associated with the given typeId
		/// </summary>
		/// <param name="id">the typeId to find the signatures for</param>
		/// <returns>the signatures associated with the typeId</returns>
		static const Vector<Signature>& GetAllSignatures(const RTTI::IdType id);
	private:
		TypeManager();
		static TypeManager* _instance;
		HashMap<RTTI::IdType, Vector<Signature>> _typeData;
	};

	class Attributed : public Scope {
		RTTI_DECLARATIONS(Attributed, Scope);
	public:
		virtual ~Attributed();
		Attributed(const Attributed& other);
		Attributed& operator=(const Attributed& other);
		Attributed(Attributed&& other) noexcept;
		Attributed& operator=(Attributed&& other) noexcept;
		/// <summary>
		/// Checks if the Datum with the given name is an attribute
		/// </summary>
		/// <param name="name">the name of the Datum</param>
		/// <returns>whether the Datum is an attribute</returns>
		bool IsAttribute(const std::string& name) const;
		/// <summary>
		/// Checks if the Datum with the given name is a prescribed attribute
		/// </summary>
		/// <param name="name">the name of the Datum</param>
		/// <returns>whether the Datum is a prescibed attribute</returns>
		bool IsPrescribedAttribute(const std::string& name) const;
		/// <summary>
		/// Checks if the Datum with the given name is an attribute
		/// </summary>
		/// <param name="name">the name of the Datum</param>
		/// <returns>whether the Datum is an attribute</returns>
		bool IsAuxiliaryAttribute(const std::string& name) const;
		/// <summary>
		/// Checks if the Datum with the given name is an auxiliary attribute
		/// </summary>
		/// <param name="name">the name of the Datum</param>
		/// <returns>whether the Datum is an auxiliary attribute</returns>
		Datum& AppendAuxiliaryAttribute(const std::string& name);
		/// <summary>
		/// Gets all of this Scope's attributes
		/// </summary>
		/// <returns>all attributes that belong to the associated Scope</returns>
		const Vector<Scope::pair_type*>& GetAllAttributes() const;
		/// <summary>
		/// Gets the index of and pointer to the first auxiliary attribute (first prescribed is always 0)
		/// </summary>
		/// <returns>the index of the first auxiliary attribute in the order vector</returns>
		const std::pair<size_t, Datum*> GetFirstAuxiliaryAttribute() const;
		/// <summary>
		/// Gets the index of and pointer to the last auxiliary attribute
		/// </summary>
		/// <returns>the range of all auxiliary attributes that belong to the associated Scope</returns>
		const std::pair<size_t, Datum*> GetLastAuxiliaryAttribute() const;
		/// <summary>
		/// Populates the associated Scope with prescribed attributes
		/// </summary>
		/// <param name="attributes">the signatures of the attributes to append</param>
		void Populate(const Vector<Signature>& attributes);
	protected:
		/// <summary>
		/// Creates an Attributed (should be a derived class instance)
		/// </summary>
		/// <param name="id">The typeId to forward to the derived class constructor</param>
		Attributed(RTTI::IdType id);
	private:
		/// <summary>
		/// Switches the external storage pointers to point to values within this Attributed instance
		/// </summary>
		/// <param name="id">the typeId of the object</param>
		void UpdateExternalStorage(RTTI::IdType id);
	};
}