namespace fge {

	template<typename T>
	inline T* Factory<T>::Create(std::string className) {
		std::shared_ptr<Factory<T>> foundFactory = Find(className);
		if (foundFactory != nullptr) {
			return foundFactory->Create();
		}
		else return nullptr;
	}

	template<typename T>
	inline typename std::shared_ptr<Factory<T>> Factory<T>::Find(std::string className) {
		return _concreteFactories.At(className);
	}

	template<typename T>
	inline void Factory<T>::Add(const std::shared_ptr<Factory<T>>& concreteFactory) {
		_concreteFactories.Insert(std::make_pair(concreteFactory->ClassName(), concreteFactory));
	}
	template<typename T>
	inline void Factory<T>::Remove(const std::shared_ptr<Factory<T>>& concreteFactory) {
		_concreteFactories.Remove(concreteFactory->ClassName());
	}
}