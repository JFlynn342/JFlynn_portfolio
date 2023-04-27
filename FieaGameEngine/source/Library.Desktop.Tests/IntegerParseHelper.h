#pragma once

#include "ParseCoordinator.h"

namespace UnitTests {
	using namespace fge;

	class IntegerWrapper: public JsonParseCoordinator::Wrapper {
		RTTI_DECLARATIONS(IntegerWrapper, Wrapper);
	public:
		int32_t _data;
		std::unique_ptr<Wrapper> Create() override;
	};

	class IntegerParseHelper : public IJsonParseHelper {
	public:
		bool StartHandler(JsonParseCoordinator::Wrapper& wrapper, std::string key, Json::Value& value, bool isArrayElement = false) override;
		void EndHandler(JsonParseCoordinator::Wrapper& wrapper, Json::Value& key) override;
		std::shared_ptr<IJsonParseHelper> Create() override;
	};
}