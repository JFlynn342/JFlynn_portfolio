#pragma once
#include "HashMap.h"
#include <memory>
namespace fge {
	template<typename T>
	class Factory {
	public:
		Factory() = default;
		Factory(const Factory&) = delete;
		Factory& operator=(const Factory&) = delete;
		Factory(Factory&&) = default;
		Factory& operator=(Factory&&) = default;
		~Factory() = default;

		/// <summary>
		/// finds an associated Factory of the given class name and creates an instance of that class
		/// </summary>
		/// <param name="className">the name of the class to create</param>
		/// <returns>an instance of the class</returns>
		static T* Create(std::string className);
		/// <summary>
		/// finds an associated Factory of the given class name
		/// </summary>
		/// <param name="className">the class name of the Factory to find</param>
		/// <returns>a pointer to the Factory if found, otherwise nullptr</returns>
		static std::shared_ptr<Factory<T>> Find(std::string className);
		/// <summary>
		/// creates an instance of the class associated with this Factory
		/// </summary>
		/// <returns>a shared pointer to the instance</returns>
		virtual T* Create() = 0;
		/// <summary>
		/// gets the name of the class produced by this Factory
		/// </summary>
		/// <returns>the name of this Factory's class</returns>
		virtual std::string ClassName() const = 0;
	protected:
		/// <summary>
		/// Registers a concrete Factory instance with this Factory
		/// </summary>
		/// <param name="concreteFactory">the concrete Factory instance to register</param>
		static void Add(const std::shared_ptr<Factory>& concreteFactory);
		/// <summary>
		/// disassociates a registered Factory from this Factory
		/// </summary>
		/// <param name="concreteFactory">the Factory instance to remove</param>
		static void Remove(const std::shared_ptr<Factory>& concreteFactory);
	private:
		inline static HashMap<std::string, std::shared_ptr<Factory>> _concreteFactories{11};
	};
}
#include "Factory.inl"

#define ConcreteFactory(ConcreteProductType, AbstractProductType)\
class ConcreteProductType##Factory final: public fge::Factory<AbstractProductType>{\
public:\
	ConcreteProductType##Factory(){\
		fge::Factory<AbstractProductType>::Add(std::shared_ptr<fge::Factory<AbstractProductType>>(this));\
	}\
	[[nodiscard]] AbstractProductType* Create() override {\
		return new ConcreteProductType;\
	} \
	std::string ClassName() const{\
		return #ConcreteProductType;\
	}\
};