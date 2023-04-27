#include "IntegerParseHelper.h"

namespace UnitTests{
	using namespace fge;
	RTTI_DEFINITIONS(IntegerWrapper);

	std::unique_ptr<JsonParseCoordinator::Wrapper> IntegerWrapper::Create()
	{
		return std::make_unique<IntegerWrapper>();
	}

	bool IntegerParseHelper::StartHandler(JsonParseCoordinator::Wrapper& wrapper, std::string key, Json::Value& value, bool isArrayElement)
	{
		value, isArrayElement;
		if (wrapper.Is(IntegerWrapper::TypeIdClass())) {
			return true;
		}
		else return false;
	}
	void IntegerParseHelper::EndHandler(JsonParseCoordinator::Wrapper& wrapper, Json::Value& value)
	{
		dynamic_cast<IntegerWrapper&>(wrapper)._data = value["Integer"].asInt();
	}
	std::shared_ptr<IJsonParseHelper> IntegerParseHelper::Create()
	{
		return std::make_shared<IntegerParseHelper>();
	}

}
