#pragma once
#include <string>
#include <utility>
#include "glm/common.hpp"
#include "glm/mat4x4.hpp"
#include "RTTI.h"
#include "HashMap.h"
namespace fge {
	class Scope;
	/// <summary>
	/// A dynamic storage container that can have its type set at runtime
	/// </summary>
	class Datum final {
	public:
		friend Scope;
		enum class DatumType {
			Unknown = 0,
			Integer,
			Float,
			Vector,
			Matrix,
			Table,
			String,
			Pointer,
			End = Pointer
		};

		using integer_type = int32_t;
		using float_type = float_t;
		using vector_type = glm::vec4;
		using matrix_type = glm::mat4;
		using table_type = Scope*;
		using string_type = std::string;
		using pointer_type = RTTI*;

		static constexpr size_t _capacityTable[static_cast<int>(DatumType::End) + 1] =
		{
			0,
			sizeof(integer_type),
			sizeof(float_type),
			sizeof(vector_type),
			sizeof(matrix_type),
			sizeof(table_type),
			sizeof(string_type),
			sizeof(pointer_type),
		};
		Scope& operator[](uint32_t index);
		explicit Datum(size_t startSize = 0, DatumType type = DatumType::Unknown);
		~Datum();
		Datum(const Datum& other);
		Datum& operator=(Datum& other);
		Datum(Datum&& other) noexcept;
		Datum& operator=(Datum&& other) noexcept;
		/// <summary>
		/// Assignment overload that allows for direct value assignment
		/// </summary>
		/// <param name="newValue">the value to assign to the Datum</param>
		/// <returns>the reassigned Datum</returns>
		Datum& operator=(integer_type newValue);
		Datum& operator=(float_type newValue);
		Datum& operator=(vector_type newValue);
		Datum& operator=(matrix_type newValue);
		Datum& operator=(string_type newValue);
		Datum& operator=(pointer_type newValue);
		/// <summary>
		/// Provides information as to the type of this Datum
		/// </summary>
		/// <returns>a DatumType value indicating this Datum's current type</returns>
		DatumType Type() const;
		/// <summary>
		/// Sets the type of this Datum (current type must be UNKNOWN)
		/// </summary>
		/// <param name="newType">the DatumType to set this Datum to</param>
		void SetType(DatumType newType);
		/// <summary>
		/// Gets the size of the Datum
		/// </summary>
		/// <returns>the number of elements in this Datum</returns>
		size_t Capacity() const;
		/// <summary>
		/// gets the current population of the Datum
		/// </summary>
		/// <returns>the current number of initialized elements in the Datum</returns>
		size_t Size() const;
		/// <summary>
		/// Changes the size of the Datum
		/// </summary>
		/// <param name="newSize">the new size of the Datum</param>
		void Resize(size_t newSize);
		/// <summary>
		/// Expands the size of the Datum to match the given size
		/// </summary>
		/// <param name="newSize">the new size to reserve</param>
		void Reserve(size_t newSize);
		/// <summary>
		/// Shrinks the Datum's size to match its population
		/// </summary>
		void ShrinkToFit();
		/// <summary>
		/// Clears the array, has no effect on capacity
		/// </summary>
		void Clear();
		/// <summary>
		/// Designates external storage for this Datum to point at, 
		/// the Datum no longer "owns" its storage after this call
		/// </summary>
		/// <param name="newStorage">the new array to point to</param>
		/// <param name="pop">the population of the new array</param>
		/// <param name="size">the capacity of the new array</param>
		void SetStorage(void* newStorage, size_t pop, size_t size);
		/// <summary>
		/// Comparison operator
		/// </summary>
		/// <param name="other">the Datum to compare with</param>
		/// <returns>true if the Datums have different values, otherwise false</returns>
		bool operator!=(const Datum& other) const;
		/// <summary>
		/// Comparison operator scalar overloads
		/// </summary>
		/// <param name="other">the value to compare with</param>
		/// <returns>true if the Datum's value differs from other, otherwise false</returns>
		bool operator!=(const integer_type other) const;
		bool operator!=(const float_type other) const;
		bool operator!=(const vector_type other) const;
		bool operator!=(const matrix_type other) const;
		bool operator!=(const string_type other) const;
		bool operator!=(const pointer_type other) const;
		/// <summary>
		/// Comparison operator
		/// </summary>
		/// <param name="other">the Datum to compare with</param>
		/// <returns>true if the Datums have the same value, otherwise false</returns>
		bool operator==(const Datum& other) const;
		/// <summary>
		/// Comparison operator scalar overloads
		/// </summary>
		/// <param name="other">the value to compare with</param>
		/// <returns>true if the Datum's value equals other, otherwise false</returns>
		bool operator==(const integer_type other) const;
		bool operator==(const float_type other) const;
		bool operator==(const vector_type other) const;
		bool operator==(const matrix_type other) const;
		bool operator==(const string_type& other) const;
		bool operator==(const pointer_type other) const;
		/// <summary>
		/// Sets a single entry in the Datum
		/// </summary>
		/// <param name="value">the new value of the entry</param>
		/// <param name="index">the index of the value to set</param>
		void Set(const integer_type value, const size_t index = 0);
		void Set(const float_type value, const size_t index = 0);
		void Set(const vector_type value, const size_t index = 0);
		void Set(const matrix_type value, const size_t index = 0);
		void Set(const table_type& value, const size_t index = 0);
		void Set(const string_type& value, const size_t index = 0);
		void Set(const pointer_type value, const size_t index = 0);
		/// <summary>
		/// Gets an entry from the Datum
		/// </summary>
		/// <typeparam name="T">the type of the Datum</typeparam>
		/// <param name="index">the index of the desired entry</param>
		/// <returns>the entry of the given type at the given index</returns>
		template<typename T>
		T& As(const size_t index = 0);
		template<>
		integer_type& As<integer_type>(const size_t index);
		template<>
		float_type& As<float_type>(const size_t index);
		template<>
		vector_type& As<vector_type>(const size_t index);
		template<>
		matrix_type& As<matrix_type>(const size_t index);
		template<>
		table_type& As<table_type>(const size_t index);
		template<>
		string_type& As<string_type>(const size_t index);
		template<>
		pointer_type& As<pointer_type>(const size_t index);
		template<typename T>
		const T& As(const size_t index = 0) const;
		template<>
		const integer_type& As<integer_type>(const size_t index) const;
		template<>
		const float_type& As<float_type>(const size_t index) const;
		template<>
		const vector_type& As<vector_type>(const size_t index) const;
		template<>
		const matrix_type& As<matrix_type>(const size_t index) const;
		template<>
		const table_type& As<table_type>(const size_t index) const;
		template<>
		const string_type& As<string_type>(const size_t index) const;
		template<>
		const pointer_type& As<pointer_type>(const size_t index) const;
		/// <summary>
		/// Sets the value of a Datum entry based on a given string
		/// </summary>
		/// <param name="str">the string to set the entry from</param>
		/// <param name="index">the index of the entry to set</param>
		void SetFromString(const std::string& str, const size_t index = 0);
		void PushBackFromString(const std::string& str);
		/// <summary>
		/// Parses a Datum entry into a string
		/// </summary>
		/// <param name="index">the index of the entry</param>
		/// <returns>a string representing the entry at the given index</returns>
		std::string ToString(const size_t index = 0) const;
		/// <summary>
		/// gets the storage state of this Datum
		/// </summary>
		/// <returns>whether or not this Datum has external storage</returns>
		bool IsExternalStorage() const;
		/// <summary>
		/// Adds an entry to the back of the array
		/// </summary>
		/// <param name="value">the value to add</param>
		void PushBack(const integer_type value);
		void PushBack(const float_type value);
		void PushBack(const vector_type value);
		void PushBack(const matrix_type value);
		void PushBack(const string_type& value);
		void PushBack(const pointer_type value);
		/// <summary>
		/// Removes the entry at the back of the array, 
		/// </summary>
		void PopBack();
		/// <summary>
		/// Gets the first entry of the Datum
		/// </summary>
		/// <typeparam name="T">the type of the Datum</typeparam>
		/// <returns>the first value in the array</returns>
		template<typename T>
		T& Front();
		template<>
		integer_type& Front<integer_type>();
		template<>
		float_type& Front<float_type>();
		template<>
		vector_type& Front<vector_type>();
		template<>
		matrix_type& Front<matrix_type>();
		template<>
		string_type& Front<string_type>();
		template<>
		pointer_type& Front<pointer_type>();
		template<typename T>
		const T& Front() const;
		template<>
		const integer_type& Front<integer_type>() const;
		template<>
		const float_type& Front<float_type>() const;
		template<>
		const vector_type& Front<vector_type>() const;
		template<>
		const matrix_type& Front<matrix_type>() const;
		template<>
		const string_type& Front<string_type>() const;
		template<>
		const pointer_type& Front<pointer_type>() const;
		/// <summary>
		/// Gets the last entry of the Datum
		/// </summary>
		/// <typeparam name="T">the type of the Datum</typeparam>
		/// <returns>the last value in the array</returns>
		template<typename T>
		T& Back();
		template<>
		integer_type& Back<integer_type>();
		template<>
		float_type& Back<float_type>();
		template<>
		vector_type& Back<vector_type>();
		template<>
		matrix_type& Back<matrix_type>();
		template<>
		table_type& Back<table_type>();
		template<>
		string_type& Back<string_type>();
		template<>
		pointer_type& Back<pointer_type>();
		template<typename T>
		const T& Back() const;
		template<>
		const integer_type& Back<integer_type>() const;
		template<>
		const float_type& Back<float_type>() const;
		template<>
		const vector_type& Back<vector_type>() const;
		template<>
		const matrix_type& Back<matrix_type>() const;
		template<>
		const table_type& Back<table_type>() const;
		template<>
		const string_type& Back<string_type>() const;
		template<>
		const pointer_type& Back<pointer_type>() const;
		/// <summary>
		/// Removes an entry of the given value from the Datum
		/// </summary>
		/// <param name="value">the value to remove</param>
		void Remove(integer_type value);
		void Remove(float_type value);
		void Remove(vector_type value);
		void Remove(matrix_type value);
		void Remove(table_type value);
		void Remove(string_type value);
		void Remove(pointer_type value);
		/// <summary>
		/// Removes the entry at the given index from the Datum
		/// </summary>
		/// <typeparam name="T">the type of the Datum</typeparam>
		/// <param name="index">the index of the entry to remove</param>
		template<typename T>
		void RemoveAt(size_t index);
		template<>
		void RemoveAt<integer_type>(size_t index);
		template<>
		void RemoveAt<float_type>(size_t index);
		template<>
		void RemoveAt<vector_type>(size_t index);
		template<>
		void RemoveAt<matrix_type>(size_t index);
		template<>
		void RemoveAt<string_type>(size_t index);
		template<>
		void RemoveAt<pointer_type>(size_t index);
		/// <summary>
		/// Gets the first entry of the Datum with the given value
		/// </summary>
		/// <typeparam name="T">the type of the Datum</typeparam>
		/// <returns>true and the first value in the array with the given value if successful, otherwise false along with the last element</returns>
		template<typename T>
		std::pair<bool, T*> Find(T value);
		template<>
		std::pair<bool, integer_type*> Find<integer_type>(integer_type value);
		template<>
		std::pair<bool, float_type*> Find<float_type>(float_type value);
		template<>
		std::pair<bool, vector_type*> Find<vector_type>(vector_type value);
		template<>
		std::pair<bool, matrix_type*> Find<matrix_type>(matrix_type value);
		template<>
		std::pair<bool, table_type*> Find<table_type>(table_type value);
		template<>
		std::pair<bool, string_type*> Find<string_type>(string_type value);
		template<>
		std::pair<bool, pointer_type*> Find<pointer_type>(pointer_type value);
		template<typename T>
		std::pair<bool, const T* const> Find(T value) const;
		template<>
		std::pair<bool, const integer_type* const> Find<integer_type>(integer_type value) const;
		template<>
		std::pair<bool, const float_type* const> Find<float_type>(float_type value) const;
		template<>
		std::pair<bool, const vector_type* const> Find<vector_type>(vector_type value) const;
		template<>
		std::pair<bool, const matrix_type* const> Find<matrix_type>(matrix_type value) const;
		template<>
		std::pair<bool, const table_type* const> Find<table_type>(table_type value) const;
		template<>
		std::pair<bool, const string_type* const> Find<string_type>(string_type value) const;
		template<>
		std::pair<bool, const pointer_type* const> Find<pointer_type>(pointer_type value) const;
	private:
		/// <summary>
		/// The possible value arrays for this Datum
		/// </summary>
		union Array final{
			integer_type* _int;
			float_type* _float;
			vector_type* _vec;
			matrix_type* _mat;
			table_type* _tbl;
			string_type* _str;
			pointer_type* _poi;
			void* _vp = nullptr;
		};
		void PushTable(const table_type value);
		/// <summary>
		/// The capacity of the array
		/// </summary>
		size_t _capacity = 0;
		/// <summary>
		/// The number of entries in the array
		/// </summary>
		size_t _size = 0;
		/// <summary>
		/// Whether or not this Datum has storage it is not responsible for deleting
		/// </summary>
		bool _hasExternalStorage = false;
		/// <summary>
		/// An indicator of the type held by the Datum
		/// </summary>
		DatumType _type = DatumType::Unknown;
		/// <summary>
		/// The values array for this Datum
		/// </summary>
		Array _array;
	};
}

#include "Datum.inl"