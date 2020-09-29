#pragma once 

#include <map>
#include <string>
#include <functional>

#include "Behaviour.hpp"

namespace shp
{
    // Abstract class for States
    class State
    {
        public:
            virtual std::string GetTransition();

            virtual void Enter() = 0;
            virtual SteeringOutput GetSteering() { return m_Behaviour->GetSteering(); }
            virtual void Exit() = 0;

        protected:
            std::map<std::string, std::function<bool()>> m_Transitions;
            Behaviour* m_Behaviour;
    };
    
    class StateMachine
    {
        public:
            StateMachine() 
                : m_CurrentState(),
                  m_StateMap()
            {}
            virtual SteeringOutput GetSteering();

        protected:
            std::string m_CurrentState;
            std::map<std::string, State*> m_StateMap;
    };
};