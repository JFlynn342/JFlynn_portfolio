#pragma once
#include "ParseCoordinator.h"
#include "Scope.h"
namespace fge {
	/// <summary>
	/// A Wrapper which holds a Scope
	/// </summary>
	class ScopeWrapper final: public JsonParseCoordinator::Wrapper {
		friend class TableParseHelper;
	public:
		/// <summary>
		/// Clears the context stack of the wrapper, then pushes the root Scope onto it
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// creates a new instance of this class
		/// </summary>
		/// <returns>the new instance</returns>
		std::unique_ptr<Wrapper> Create() override;
		/// <summary>
		/// gets the Scope held by this Wrapper
		/// </summary>
		/// <returns>a pointer to the associated Scope</returns>
		std::shared_ptr<Scope> GetScope() const;
		/// <summary>
		/// Sets the Scope of this Wrapper
		/// </summary>
		/// <param name="s">The Scope to assign to this Wrapper</param>
		void SetScope(Scope& s);

		~ScopeWrapper() override = default;
	private:
		std::shared_ptr<Scope> _scope = nullptr;
		std::stack<Scope*, Vector<Scope*>> _contextStack;
	};
	/// <summary>
	/// A helper that knows how to parse data into a Scope
	/// </summary>
	class TableParseHelper final : public IJsonParseHelper {
		std::shared_ptr<IJsonParseHelper> Create() override;
		/// <summary>
		/// Attempts to handle a value passed in by the ParseCoordinator
		/// </summary>
		/// <param name="wrapper">the wrapper to attempt to encapsulate the data in</param>
		/// <param name="key">the key of the value being passed in</param>
		/// <param name="value">the value to handle</param>
		/// <param name="isArrayElement">whether or not this value is an element of an array</param>
		/// <returns></returns>
		bool StartHandler(JsonParseCoordinator::Wrapper& wrapper, std::string key, Json::Value& value, bool isArrayElement = false) override;
		/// <summary>
		/// Finishes handler execution after StartHandler confirms that it is possible
		/// </summary>
		/// <param name="wrapper">the Wrapper to populate</param>
		/// <param name="value">the Json::Value passed in by ParseCoordinator</param>
		void EndHandler(JsonParseCoordinator::Wrapper& wrapper, Json::Value& value) override;
	};
}