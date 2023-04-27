#include "ParseCoordinator.h"
#include "gsl/gsl_util"
#include <fstream>
namespace fge {
	using namespace std::string_literals;
	RTTI_DEFINITIONS(JsonParseCoordinator::Wrapper);




	void JsonParseCoordinator::Wrapper::Initialize()
	{
	}

	size_t JsonParseCoordinator::Wrapper::Depth() {
		return _depth;
	}

	JsonParseCoordinator* JsonParseCoordinator::Wrapper::GetJsonParseCoordinator() {
		return _coordinator;
	}


	void JsonParseCoordinator::Wrapper::IncrementDepth() {
		++_depth;
	}

	void JsonParseCoordinator::Wrapper::DecrementDepth() {
		--_depth;
	}

	void JsonParseCoordinator::Wrapper::SetJsonParseCoordinator(JsonParseCoordinator& coordinator) {
		_coordinator = &coordinator;
	}

	JsonParseCoordinator::JsonParseCoordinator(Wrapper& wrapper){
		SetWrapper(wrapper);
	}

	std::shared_ptr<JsonParseCoordinator> JsonParseCoordinator::Clone() {
		return std::shared_ptr<JsonParseCoordinator>(new JsonParseCoordinator(*this));
	}

	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& other) noexcept:
		_helpers{ std::move(other._helpers) }, _wrapper{ std::move(other._wrapper)} {
		
	}

	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& other) noexcept{
		_helpers = std::move(other._helpers);
		_wrapper = std::move(other._wrapper);
		return *this;
	}


	void JsonParseCoordinator::AddHelper(IJsonParseHelper& helper) {
		_helpers.push_back(std::shared_ptr<IJsonParseHelper>(&helper));
	}

	void JsonParseCoordinator::RemoveHelper(IJsonParseHelper& helper) {
		for (std::shared_ptr<IJsonParseHelper>& h : _helpers) {
			if (h.get() == &helper) {
				_helpers.Remove(h);
			}
		}
	}

	JsonParseCoordinator::Wrapper* JsonParseCoordinator::GetWrapper() {
		return _wrapper.get();
	}

	void JsonParseCoordinator::SetWrapper(JsonParseCoordinator::Wrapper& wrapper) {
		_wrapper.reset(&wrapper);
		_wrapper->SetJsonParseCoordinator(*this);
	}

	void JsonParseCoordinator::DeserializeObject(const std::string& data) {
		std::stringstream ss;
		ss << data;
		DeserializeObject(ss);
	}

	void JsonParseCoordinator::DeserializeObjectFromFile(const std::string& filename) {
		std::ifstream fstream(filename);
		DeserializeObject(fstream);
		fstream.close();
	}

	void JsonParseCoordinator::DeserializeObject(std::istream& data) {
		Json::Value value;
		data >> value;
		_wrapper->Initialize();
		for (size_t i = 0; i < _helpers.size(); ++i) {
			_helpers[i]->Initialize();
		}
		Parse("Object"s, value);
	}

	void JsonParseCoordinator::ParseMembers(std::string name, Json::Value& value) {
		_wrapper->IncrementDepth();
		if (!value.empty()) {
			if (value.isObject()) {
				for (std::string memberName : value.getMemberNames()) {
					Parse(memberName, value[memberName], false);
				}
			}
			else if (value.isArray()) {
				for (size_t i = 0; i < value.size(); ++i) {
					Parse(name + "[" + std::to_string(i) + "]", value[gsl::narrow_cast<int32_t>(i)], true);
				}
			}
		}
		_wrapper->DecrementDepth();
	}

	void JsonParseCoordinator::Parse(std::string name, Json::Value& value, bool isArrayElement) {
		isArrayElement;
		if (!value.empty()) {
			for (size_t i = 0; i < _helpers.size(); ++i) {
				if ((_helpers[i])->StartHandler(*_wrapper, name, value, false)) {
					(_helpers[i])->EndHandler(*_wrapper, value);
					break;
				}
			}
		}
	}

	void IJsonParseHelper::Initialize()
	{
	}
}
