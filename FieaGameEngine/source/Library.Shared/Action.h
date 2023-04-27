#pragma once
#include "Attributed.h"
#include "GameTime.h"
#include "Factory.h"
namespace fge {
	class Action : public Attributed {
		RTTI_DECLARATIONS(Action, Attributed);
	public:
		Action();
		Action(const Action&) = default;
		Action(Action&&) = default;
		Action& operator=(const Action&) = default;
		Action& operator=(Action&&) = default;
		virtual ~Action() = default;
		/// <summary>
		/// Executes per-frame logic for this Action
		/// </summary>
		/// <param name="time">the GameTime insdtance representing how much time has passed since the last frame</param>
		virtual void Update(const GameTime& time) = 0;
		/// <summary>
		/// get this Action's name
		/// </summary>
		/// <returns>te name of this Action</returns>
		std::string Name();
		/// <summary>
		/// sets the name of this Action
		/// </summary>
		/// <param name="newName">the new name of this Action</param>
		void SetName(const std::string& newName);
		/// <summary>
		/// Gets the list of prescribed attributes for the Action class
		/// </summary>
		/// <returns>a list of the signatures pertaining to Action</returns>
		static Vector<Signature> Signatures();
	protected:
		std::string _name;
		Action(RTTI::IdType type);
	};

	class ActionList : public Action {
		RTTI_DECLARATIONS(ActionList, Action);
	public:
		ActionList();
		ActionList(const ActionList&) = default;
		ActionList(ActionList&&) = default;
		ActionList& operator=(const ActionList&) = default;
		ActionList& operator=(ActionList&&) = default;
		virtual ~ActionList() = default;
		/// <summary>
		/// Updates the members of this ActionList
		/// </summary>
		/// <param name="time">the amount of time passed since the last frame</param>
		virtual void Update(const GameTime& time) override;
		/// <summary>
		/// Gets the list of prescribed attributes for the ActionList class
		/// </summary>
		/// <returns>a list of the signatures pertaining to ActionList</returns>
		static Vector<Signature> Signatures();
	protected:
		ActionList(RTTI::IdType id);
	};
	ConcreteFactory(ActionList, Scope);

	class ActionIf : public Action {
		RTTI_DECLARATIONS(ActionIf, Action);
	public:
		ActionIf();
		ActionIf(const ActionIf&) = default;
		ActionIf(ActionIf&&) = default;
		ActionIf& operator=(const ActionIf&) = default;
		ActionIf& operator=(ActionIf&&) = default;
		virtual ~ActionIf() = default;
		/// <summary>
		/// calls Update on the then block if _condition is true (non-zero), otherwise updates the else block (if it exists)
		/// </summary>
		/// <param name="time">the amount of time that has passed since the last frame</param>
		virtual void Update(const GameTime& time) override;
		/// <summary>
		/// Gets the list of prescribed attributes for the ActionListIf class
		/// </summary>
		/// <returns>a list of the signatures pertaining to ActionListIf</returns>
		static Vector<Signature> Signatures();
		int32_t _condition;
	};
	ConcreteFactory(ActionIf, Scope);
	
	/// <summary>
	/// An Action that enqueues an Event<EventMessageAttributed> on Update
	/// </summary>
	class ActionEvent: public Action {
		RTTI_DECLARATIONS(ActionEvent, Action);
	public:
		ActionEvent();
		ActionEvent(const ActionEvent&) = default;
		ActionEvent(ActionEvent&&) noexcept = default;
		ActionEvent& operator=(const ActionEvent&) = default;
		ActionEvent& operator=(ActionEvent&&) noexcept = default;
		void Update(const GameTime& time) override;
		static Vector<Signature> Signatures();
	private:
		int32_t _subtype = 0;
		int32_t _delay = 0;
	};
	ConcreteFactory(ActionEvent, Scope);
}