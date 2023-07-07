#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "Transition.h"
#include "TransitionRule.h"
#include "AnimationClip.h"
namespace Animation {
	class StateMachine final: public Library::GameComponent {
	public:
		class State;
		class StateLink;
		/// <summary>
		/// initializes all Transitions associated with this StateMachine
		/// </summary>
		void Initialize() override;
		/// <summary>
		/// gets the current State
		/// </summary>
		/// <returns>a pointer to the active State, nullptr if in transition</returns>
		State* CurrentState() const;
		/// <summary>
		/// gets the State with the given name
		/// </summary>
		/// <param name="name">the name of the State to look up</param>
		/// <returns>a pointer to the found State, if found, otherwise nullptr</returns>
		State* GetState(std::string name);
		/// <summary>
		/// Constructs the StateMachine
		/// </summary>
		/// <param name="player">the active AnimationPlayer</param>
		/// <param name="game">the game instance</param>
		StateMachine(Library::AnimationPlayer* player, Library::Game& game);
		/// <summary>
		/// creates a StateLink between two states
		/// </summary>
		/// <param name="from">the origin state</param>
		/// <param name="to">the target state</param>
		/// <param name="transition">the Transition to use</param>
		/// <param name="rule">the TransitionRule to use</param>
		void LinkStates(State* from, State* to, const std::shared_ptr<Transition>& transition, const TransitionRule& rule);
		/// <summary>
		/// updates the StateMachine
		/// </summary>
		/// <param name="">the current GameTime</param>
		void Update(const Library::GameTime&) override;
		/// <summary>
		/// adds a new State
		/// </summary>
		/// <param name="name">the name of the new State</param>
		/// <param name="clip">the AnimationClip to use</param>
		void AddState(std::string name, std::shared_ptr<Library::AnimationClip> clip);
		/// <summary>
		/// An object which represents a State in the StateMachine
		/// </summary>
		class State final {
			friend StateMachine;
		public:
			/// <summary>
			/// checks if the State is currently active
			/// </summary>
			/// <returns>true if the State is active, otherwise false</returns>
			bool IsActive() const;
			/// <summary>
			/// gets the AnimationClip being used by this State
			/// </summary>
			/// <returns>the AnimationClip in use</returns>
			const std::shared_ptr<Library::AnimationClip> GetClip() const;
		private:
			State() = default;
			/// <summary>
			/// the AnimationClip used by this State
			/// </summary>
			std::shared_ptr<Library::AnimationClip> _clip;
			/// <summary>
			/// all of the StateLinks originating from this State
			/// </summary>
			std::vector<StateLink> _links;
		};
		/// <summary>
		/// An object which defines a condition for and a transition to a different STate
		/// </summary>
		class StateLink final {
			friend StateMachine;
			inline StateLink(const std::shared_ptr<Transition>& transition, const TransitionRule& rule, State* target) : _transition{ transition }, _rule{ rule }, _target{ target } {};
		private:
			/// <summary>
			/// the Transition used by this StateLink
			/// </summary>
			std::shared_ptr<Transition> _transition;
			/// <summary>
			/// the rule used by this StateLink
			/// </summary>
			TransitionRule _rule;
			/// <summary>
			/// the target State of this StateLink
			/// </summary>
			State* _target;
		};
	private:
		/// <summary>
		/// all of the States in this STateMachine
		/// </summary>
		std::unordered_map <std::string, State> _states;
		/// <summary>
		/// the AnimationPlayer to which this StateMachine is bound
		/// </summary>
		inline static Library::AnimationPlayer* _player = nullptr;
		/// <summary>
		/// the current State of this StateMachine
		/// </summary>
		State* _currentState;
	};
}

