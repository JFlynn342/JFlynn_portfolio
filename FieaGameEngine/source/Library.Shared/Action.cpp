#include "Action.h"
#include "EventMessageAttributed.h"
#include "GameState.h"
namespace fge {
	using namespace std::string_literals;
	RTTI_DEFINITIONS(Action);
	RTTI_DEFINITIONS(ActionList);
	RTTI_DEFINITIONS(ActionIf);
	Action::Action():
		Attributed(Action::TypeIdClass()) {
	}
	std::string Action::Name() {
		return _name;
	}
	void Action::SetName(const std::string& newName) {
		_name = newName;
	}
	Vector<Signature> Action::Signatures() {
		return Vector<Signature>{
			Signature("Name"s, Datum::DatumType::String, 1, offsetof(Action, _name)),
		};
	}
	Action::Action(RTTI::IdType type) :
		Attributed(type)
	{
	}
	ActionList::ActionList():
		Action(ActionList::TypeIdClass())
	{
	}
	void ActionList::Update(const GameTime& time) {
		Datum* actions = Find("Actions");
		if (actions != nullptr) {
			for (size_t i = 0; i < actions->As<Scope*>()->Size(); ++i) {
				Scope* action = actions->As<Scope*>()->operator[](i).As<Scope*>();
				assert(action->Is(Action::TypeIdClass()));
				reinterpret_cast<Action*>(action)->Update(time);
			}
		}
	}
	Vector<Signature> ActionList::Signatures() {
		return Vector<Signature>{
			Signature("Name"s, Datum::DatumType::String, 1, offsetof(ActionList, _name)),
			Signature("Actions"s, Datum::DatumType::Table, 0, 0)
		};
	}
	ActionList::ActionList(RTTI::IdType id):
	Action(id) {
		
	}
	ActionIf::ActionIf():
		Action(ActionIf::TypeIdClass())
	{
	}
	void ActionIf::Update(const GameTime& time) {
		Datum* actions = nullptr;
		if (_condition != 0) {
			actions = Find("Then"s);
		}
		else actions = Find("Else"s);
		if (actions != nullptr) {
			for (size_t i = 0; i < actions->As<Scope*>()->Size(); ++i) {
				Scope* action = actions->As<Scope*>()->operator[](i).As<Scope*>();
				assert(action->Is(Action::TypeIdClass()));
				reinterpret_cast<Action*>(action)->Update(time);
			}
		}
	}
	Vector<Signature> ActionIf::Signatures() {
		return Vector<Signature>{
			Signature("Name"s, Datum::DatumType::String, 1, offsetof(ActionIf, _name)),
			Signature("Condition"s, Datum::DatumType::Integer, 1, offsetof(ActionIf, _condition)),
			Signature("Then"s, Datum::DatumType::Table, 0, 0)
		};
	}

	RTTI_DEFINITIONS(ActionEvent);

	ActionEvent::ActionEvent() :
	Action(ActionEvent::TypeIdClass()) {
	}

	void ActionEvent::Update(const GameTime& time) {
		EventMessageAttributed message;
		message.SetSubtype(_subtype);
		message.SetWorld(GameState::GetWorld());
		for (size_t i = GetFirstAuxiliaryAttribute().first; i <= GetLastAuxiliaryAttribute().first; ++i) {
			auto& [name, datum] = *GetAllAttributes()[i];
			message.AppendAuxiliaryAttribute(name) = datum;
		}
		std::chrono::steady_clock::time_point tp = time.CurrentTime();
		GameState::GetWorld().GetQueue().Enqueue(std::make_shared<Event<EventMessageAttributed>>(message), tp);
	}
	Vector<Signature> ActionEvent::Signatures()
	{
		return Vector<Signature>{
			Signature("Subtype", Datum::DatumType::Integer, 1, offsetof(ActionEvent, _subtype)),
			Signature("Delay", Datum::DatumType::Integer, 1, offsetof(ActionEvent, _delay))
		};
	}
}