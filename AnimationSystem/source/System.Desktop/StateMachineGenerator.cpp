#include "StateMachineGenerator.h"
#include <filesystem>
#include <fstream>
#include "StepTransition.h"
#include "LinearTransition.h"
#include "BezierTransition.h"
#include "KeyboardComponent.h"
#include "Game.h"
#include "Model.h"
#include "json/json.h"

namespace Animation {
    std::shared_ptr<StateMachine> StateMachineGenerator::CreateStateMachine(Library::AnimationPlayer* player, Library::Game& game, std::string file)
    {
        std::shared_ptr<StateMachine> newSM = std::make_shared<StateMachine>(player, game);
        std::ifstream filestream(file, std::ios::binary);
        Json::Value root;
        filestream >> root;
        for (Json::Value value : root["States"]) {
            newSM->AddState(value["Name"].asString(), player->GetModel()->Animations()[value["Clip"].asInt()]);
        }
        for (Json::Value value : root["Links"]) {
            std::shared_ptr<Transition> t;
            if (value["Transition"]["Class"] == "Step") {
                t = std::make_shared<StepTransition>(player, game, newSM->GetState(value["Origin"].asString())->GetClip(), newSM->GetState(value["Target"].asString())->GetClip());
                game.mComponents.push_back(t);
            }

            else if (value["Transition"]["Class"] == "Linear") {
                t = std::make_shared<LinearTransition>(player, game, newSM->GetState(value["Origin"].asString())->GetClip(), newSM->GetState(value["Target"].asString())->GetClip(),
                    value["Transition"]["Duration"].asFloat(), value["Transition"]["EndFrame"].asUInt());
                game.mComponents.push_back(t);
            }

            else if (value["Transition"]["Class"] == "Bezier") {
                t = std::make_shared<BezierTransition>(player, game, newSM->GetState(value["Origin"].asString())->GetClip(), newSM->GetState(value["Target"].asString())->GetClip(),
                    value["Transition"]["Duration"].asFloat(), value["Transition"]["EndFrame"].asUInt(),
                    BezierCurve(DirectX::XMFLOAT2(value["Transition"]["Points"][0]["Position"].asFloat(), value["Transition"]["Points"][0]["Value"].asFloat()),
                        DirectX::XMFLOAT2(value["Transition"]["Points"][1]["Position"].asFloat(), value["Transition"]["Points"][1]["Value"].asFloat()),
                        DirectX::XMFLOAT2(value["Transition"]["Points"][2]["Position"].asFloat(), value["Transition"]["Points"][2]["Value"].asFloat())));
                game.mComponents.push_back(t);
            }
            newSM->LinkStates(newSM->GetState(value["Origin"].asString()), newSM->GetState(value["Target"].asString()), t, 
                TransitionRule([&game] {
                    for (std::shared_ptr<Library::GameComponent> c : game.Components()) {
                        if (c->Is(Library::KeyboardComponent::TypeIdClass())) {
                            return c->As<Library::KeyboardComponent>()->WasKeyPressedThisFrame(Library::Keys::T); //key hard coded for ez debug, need to change later
                        }
                    }
                    return false;
                }));
        }
        return newSM;
    }
}