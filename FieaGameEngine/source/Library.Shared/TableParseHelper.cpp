#include "TableParseHelper.h"
#include "Factory.h"
namespace fge {
	using namespace std::string_literals;
	std::shared_ptr<IJsonParseHelper> TableParseHelper::Create()
	{
		return std::make_shared<TableParseHelper>();
	}

	bool TableParseHelper::StartHandler(JsonParseCoordinator::Wrapper& wrapper, std::string key, Json::Value& value, bool isArrayElement)
	{
		value, isArrayElement;
		return(wrapper.Is(ScopeWrapper::TypeIdClass()));
	}
	void TableParseHelper::EndHandler(JsonParseCoordinator::Wrapper& wrapper, Json::Value& value)
	{
		ScopeWrapper& sWrapper = *dynamic_cast<ScopeWrapper*>(&wrapper);
		if (value["Type"].asString() == "Table"s) {
			Json::Value className = value["Class"];
			if (!className.isNull()) {
				Scope& newScope = *Factory<Scope>::Create(className.asString());
				sWrapper._contextStack.top()->Adopt(newScope, value["Name"].asString());
				sWrapper._contextStack.push(&newScope);
			}
			else {
				Scope& newScope = sWrapper._contextStack.top()->AppendScope(value["Name"].asString());
				sWrapper._contextStack.push(&newScope);
			}
			
			Json::Value& children = value["Children"];
			if (!children.empty()) {
				for (Json::Value child : children) {
					if (StartHandler(wrapper, "", child, true)) {
						EndHandler(wrapper, child);
					}
				}
			}
			sWrapper._contextStack.pop();
		
			
		}
		else {
			if (value["Type"] == "Integer") {
				Json::Value& v = value["Value"];
				if (v.isArray()) {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Integer);
						d.Resize(v.size());
					}
					for (size_t i = 0; i < v.size(); ++i) {
						d.Set(v[gsl::narrow_cast<int32_t>(i)].asInt(), i);
					}
				}
				else {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Integer);
						d.Resize(1);
					}
					d.Set(value["Value"].asInt());
				}
			}
			else if (value["Type"] == "Float") {
				Json::Value& v = value["Value"];
				if (value["Value"].isArray()) {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Float);
						d.Resize(v.size());
					}
					for (size_t i = 0; i < v.size(); ++i) {
						d.Set(v[gsl::narrow_cast<int32_t>(i)].asFloat(), i);
					}
				}
				else {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Float);
						d.Resize(1);
					}
					d.Set(value["Value"].asFloat());
				}
			}
			else if (value["Type"] == "Vector") {
				Json::Value& v = value["Value"];
				if (value["Value"].isArray()) {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Vector);
						d.Resize(v.size());
					}
					for (size_t i = 0; i < v.size(); ++i) {
						d.SetFromString(v[gsl::narrow_cast<int32_t>(i)].asString(), i);
					}
				}
				else {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Vector);
						d.Resize(1);
					}
					d.SetFromString(value["Value"].asString());
				}
			}
			else if (value["Type"] == "Matrix") {
				Json::Value& v = value["Value"];
				if (value["Value"].isArray()) {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Matrix);
						d.Resize(v.size());
					}
					for (size_t i = 0; i < v.size(); ++i) {
						d.SetFromString(v[gsl::narrow_cast<int32_t>(i)].asString(), i);
					}
				}
				else {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::Matrix);
						d.Resize(1);
					}
					d.SetFromString(value["Value"].asString());
				}
			}
			else if (value["Type"] == "String") {
				Json::Value& v = value["Value"];
				if (value["Value"].isArray()) {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::String);
						d.Resize(v.size());
					}
					for (size_t i = 0; i < v.size(); ++i) {
						d.Set(v[gsl::narrow_cast<int32_t>(i)].asString(), i);
					}
				}
				else {
					Datum& d = sWrapper._contextStack.top()->Append(value["Name"].asString());
					if (!d.IsExternalStorage()) {
						d.SetType(Datum::DatumType::String);
						d.Resize(1);
					}
					d.Set(value["Value"].asString());
				}
			}
		}
	}
	void ScopeWrapper::Initialize()
	{
		for (size_t i = 0; i < _contextStack.size(); ++i) {
			_contextStack.pop();
		}
		_contextStack.push(_scope.get());
	}
	std::unique_ptr<JsonParseCoordinator::Wrapper> ScopeWrapper::Create()
	{
		return std::make_unique<ScopeWrapper>();
	}
	std::shared_ptr<Scope> ScopeWrapper::GetScope() const
	{
		return _scope;
	}
	void ScopeWrapper::SetScope(Scope& s)
	{
		_scope.reset(&s);
	}
}

