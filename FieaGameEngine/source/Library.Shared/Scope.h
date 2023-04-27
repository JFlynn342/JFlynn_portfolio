#pragma once
#include "RTTI.h"
#include "HashMap.h"
#include "Datum.h"
namespace fge {
	/// <summary>
	/// A container that can hold many Datums
	/// </summary>
	class Scope : public RTTI {
		RTTI_DECLARATIONS(Scope, RTTI);

	public:
		using pair_type = std::pair<const std::string, Datum>;
		
		/// <summary>
		/// constructor which pre-allocates a given capacity
		/// </summary>
		/// <param name="capacity">the capacity to use for the map and lookup table</param>
		explicit Scope(size_t capacity = 5);
		virtual ~Scope();
		Scope(const Scope& other);
		Scope& operator=(const Scope& other);
		Scope(Scope&& other) noexcept;
		Scope& operator=(Scope&& other) noexcept;
		/// <summary>
		/// finds a contained Datum with a given name in the map
		/// </summary>
		/// <param name="name">the name to search for</param>
		/// <returns>the address of the Datum</returns>
		Datum* Find(const std::string& name);
		const Datum* Find(const std::string& name) const;
		/// <summary>
		/// recursively searches this Scope's ancestors for a Datum with the provided name
		/// </summary>
		/// <param name="name">the name of the Datum to find</param>
		/// <param name="outScope">A Scope double pointer to be redirected 
		/// towards the Scope in which the Datum was found</param>
		/// <returns>the address of the found Datum, or nullptr if not found</returns>
		Datum* Search(const std::string& name);
		Datum* Search(const std::string& name, Scope** outScope);
		const Datum* Search(const std::string& name) const;
		/// <summary>
		/// adds a Datum with the given name, if possible
		/// </summary>
		/// <param name="name">the name to assign to the Datum</param>
		/// <returns>a reference to an existing Datum with the given name if found, 
		/// otherwise a reference to a new Datum</returns>
		Datum& Append(const std::string& name);
		/// <summary>
		/// adds a Datum of type Table with the given name and a new Scope,
		///  or adds a new Scope to an existing Datum with the given name
		/// </summary>
		/// <param name="name">the name of the Datum</param>
		/// <returns>a reference to the appended Scope</returns>
		Scope& AppendScope(const std::string& name);
		/// <summary>
		/// Adopts a given pre-initialized Scope, incorporating it into a Datum of type Table with the given name, 
		/// creating one if necessary
		/// </summary>
		/// <param name="child">a reference to the Scope to adopt</param>
		/// <param name="name">the name of the Datum to add this Scope to</param>
		/// <returns>A reference to the adopted Scope</returns>
		Scope& Adopt(Scope& child, const std::string& name);
		/// <summary>
		/// gets the parent of this Scope
		/// </summary>
		/// <returns>a pointer to this Scope's parent</returns>
		Scope* GetParent();
		const Scope* GetParent() const;
		/// <summary>
		/// Appends a Datum with the given name
		/// </summary>
		/// <param name="name">the name to assign to the appended Datum</param>
		/// <returns>a reference to the appended Datum</returns>
		Datum& operator[](const std::string& name);
		/// <summary>
		/// gets the Datum at the given index in the order vector
		/// </summary>
		/// <param name="index">the index to access</param>
		/// <returns>the Datum at the given index</returns>
		Datum& operator[](size_t index);
		const Datum& operator[](size_t index) const;
		/// <summary>
		/// Comparison operators
		/// </summary>
		/// <param name="other">the Scope to compare this one to</param>
		/// <returns>a bool indicating whether the Scopes are equal/not equal</returns>
		bool operator==(const Scope& other) const;
		bool operator!=(const Scope& other) const;
		/// <summary>
		/// Finds the Datum of type Table within this Scope that contains the given Scope
		/// </summary>
		/// <param name="value">the Scope to look for</param>
		/// <returns>the Datum containing the Scope (nullptr if not found), 
		/// and the index at which it was found</returns>
		std::pair<Datum*, size_t> FindContainedScope(const Scope& value);
		std::pair<const Datum*, size_t> FindContainedScope(const Scope& value) const;
		/// <summary>
		/// removes the given Scope from this Scope, note that this means the user is responsible for deleting it
		/// </summary>
		/// <param name="value">a reference to the Scope to orphan</param>
		/// <returns>a pointer to the orphaned Scope</returns>
		[[nodiscard]] Scope* Orphan(Scope& child);
		/// <summary>
		/// Creates a heap-allocated copy of this Scope
		/// </summary>
		/// <returns>a pointer to the copy</returns>
		[[nodiscard]] virtual Scope* Clone() const;
		size_t Size() const;
	protected:
		/// <summary>
		/// gets the order vector of the Scope
		/// </summary>
		/// <returns>the order vector</returns>
		const Vector<pair_type*>& GetOrder() const;
		/// <summary>
		/// clears this Scope's map and order vector, and deletes all nested Scopes
		/// </summary>
		void Clear();
	private:
		/// <summary>
		/// a set of functors which operate on Datums of type Table
		/// </summary>
		struct ChildFunctor {
			/// <summary>
			/// Performs an operation (clone or delete) on a Datum of type Table
			/// </summary>
			/// <param name="table">the Datum to operate on</param>
			/// <param name="other"></param>
			virtual void operator()(pair_type& table, Scope* other = nullptr);
		};
		struct CloneChildren : public ChildFunctor {
			/// <summary>
			/// clones all of this Datum's nested scopes into other
			/// </summary>
			/// <param name="other">a pointer to the Scope to clone into, should be *this</param>
			void operator()(pair_type& table, Scope* other = nullptr) override;
		};
		struct DeleteChildren : public ChildFunctor {
			/// <summary>
			/// deletes all nested scopes
			/// </summary>
			/// <param name="other">never used here, but necessary for CloneChildren</param>
			void operator()(pair_type& table, Scope* other = nullptr) override;
		};
		/// <summary>
		/// performs a given operation on all nested Scopes
		/// </summary>
		/// <param name="operation">the ChildFunctor to execute on the nested scopes</param>
		/// <param name="other">for CloneChildren, the Scope to clone into</param>
		void ForAllChildScopes(ChildFunctor* operation, Scope* other = nullptr) const;
		/// <summary>
		/// checks if this Scope is an ancestor of the given Scope, used for validation for Adopt()
		/// </summary>
		/// <param name="other">the Scope to search this Scope's descendants for</param>
		/// <returns>whether or not this Scope is an ancestor of other</returns>
		bool IsAncestorOf(const Scope& other) const;
		HashMap<std::string, Datum> _map;
		Vector<pair_type*> _order;
		Scope* _parent = nullptr;
		
	};
}