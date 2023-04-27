#pragma once
#include "json/json.h"
#include "Vector.h"
#include "RTTI.h"
namespace fge {
	class IJsonParseHelper;
	/// <summary>
	/// A class responsible for high-level parsing of Json data
	/// </summary>
	class JsonParseCoordinator {
		friend class TableParseHelper;
	public:
		/// <summary>
		/// An abstract helper class which is used to hold deserialized data
		/// </summary>
		class Wrapper: public RTTI {
			RTTI_DECLARATIONS(Wrapper, RTTI);
		public:
			friend JsonParseCoordinator;
			/// <summary>
			/// creates a new instance of this class
			/// </summary>
			/// <returns>the new instance</returns>
			virtual std::unique_ptr<Wrapper> Create() = 0;
			/// <summary>
			/// initializes this Wrapper
			/// </summary>
			virtual void Initialize();
			/// <summary>
			/// gets the current nesting depth of the Coordinator
			/// </summary>
			/// <returns>the current nesting depth</returns>
			size_t Depth();
			/// <summary>
			/// gets the Coordinator associated with this Wrapper
			/// </summary>
			/// <returns>the associated JsonParseCoordinator</returns>
			JsonParseCoordinator* GetJsonParseCoordinator();
			
			virtual ~Wrapper() = default;
		private:
			/// <summary>
			/// increments the current nesting depth
			/// </summary>
			void IncrementDepth();
			/// <summary>
			/// decrements the current nesting depth
			/// </summary>
			void DecrementDepth();
			/// <summary>
			/// sets the JsonParseCoordinator associated with this Wrapper
			/// </summary>
			/// <param name="coordinator">a reference to the Coordinator</param>
			void SetJsonParseCoordinator(JsonParseCoordinator& coordinator);
			JsonParseCoordinator* _coordinator = nullptr;
			size_t _depth = 0;
		};
		JsonParseCoordinator() = default;
		/// <summary>
		/// Constructor which takes a Wrapper
		/// </summary>
		/// <param name="wrapper"></param>
		JsonParseCoordinator(Wrapper& wrapper);
		/// <summary>
		/// deep-copies this Coordinator and returns the new instance
		/// </summary>
		/// <returns>the new Coordinator instance</returns>
		virtual std::shared_ptr<JsonParseCoordinator> Clone();
		JsonParseCoordinator(JsonParseCoordinator&& other) noexcept;
		JsonParseCoordinator& operator=(JsonParseCoordinator&& other) noexcept;
		virtual ~JsonParseCoordinator() = default;
		/// <summary>
		/// gets the current Wrapper
		/// </summary>
		/// <returns>a pointer to the Wrapper</returns>
		Wrapper* GetWrapper();
		/// <summary>
		/// Sets the Wrapper of this helper
		/// </summary>
		/// <param name="wrapper">the wrapper to set</param>
		void SetWrapper(Wrapper& wrapper);
		/// <summary>
		/// Registers a Helper with this Coordinator
		/// </summary>
		/// <param name="helper">the Helper to add</param>
		void AddHelper(IJsonParseHelper& helper);
		/// <summary>
		/// Removes a Helper from the service of this Coordinator
		/// </summary>
		/// <param name="helper">the Helper to remove</param>
		void RemoveHelper(IJsonParseHelper& helper);
		/// <summary>
		/// Deserializes an object from a string
		/// </summary>
		/// <param name="data">the string data to deserialize</param>
		void DeserializeObject(const std::string& data);
		/// <summary>
		/// Deserializes a file of JSON data
		/// </summary>
		/// <param name="filename">a path to the file to deserialize</param>
		void DeserializeObjectFromFile(const std::string& filename);
		/// <summary>
		/// Deserializes an input stream
		/// </summary>
		/// <param name="data">the istream to deserialize</param>
		void DeserializeObject(std::istream& data);
	private:
		JsonParseCoordinator(const JsonParseCoordinator& other) = default;
		JsonParseCoordinator& operator=(const JsonParseCoordinator&) = delete;
		Vector<std::shared_ptr<IJsonParseHelper>> _helpers;
		std::shared_ptr<Wrapper> _wrapper = nullptr;
		/// <summary>
		/// Parses the members of an Object or Array
		/// </summary>
		/// <param name="value">the Object/Array Value to parse</param>
		void ParseMembers(std::string name, Json::Value& value);
		/// <summary>
		/// Parses a key-value pair
		/// </summary>
		/// <param name="pair">the key-value pair</param>
		/// <param name="isArrayElement">whether or not the Value is part of an Array</param>
		virtual void Parse(std::string name, Json::Value& value, bool isArrayElement = false);
	};

	/// <summary>
	/// An abstract helper class used by JsonParseCoordinator to handle and deserialize specific key-value pairs
	/// </summary>
	class IJsonParseHelper {
	public:
		/// <summary>
		/// Initializes data held by this Helper
		/// </summary>
		virtual void Initialize();
		
		/// <summary>
		/// Checks to see if a key/value pair can be handled
		/// </summary>
		/// <param name="wrapper">the Wrapper to populate</param>
		/// <param name="key">the string key corresponding to the value</param>
		/// <param name="value">the Value to attempt to handle</param>
		/// <param name="isArrayElement">whether the value is part of an array</param>
		/// <returns>whether or not the Value can be handled</returns>
		virtual bool StartHandler(JsonParseCoordinator::Wrapper& wrapper, std::string key, Json::Value& value, bool isArrayElement = false) = 0;
		/// <summary>
		/// Handles a Value
		/// </summary>
		/// <param name="wrapper">the Wrapper to populate</param>
		/// <param name="value">the Value to handle</param>
		virtual void EndHandler(JsonParseCoordinator::Wrapper& wrapper, Json::Value& value) = 0;
		/// <summary>
		/// constructs a new instance of this Helper type
		/// </summary>
		/// <returns>the new instance</returns>
		virtual std::shared_ptr<IJsonParseHelper> Create() = 0;
		virtual ~IJsonParseHelper() = default;
	
	};
}


