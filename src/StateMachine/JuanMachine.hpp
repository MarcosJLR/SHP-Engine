#pragma once

#include "StateMachine.hpp"

namespace shp
{    
    class JuanWander : public State 
    {
        public:
            JuanWander();

            static std::string GetID() { return "juan-wander"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class JuanMad : public State 
    {
        public:
            JuanMad();

            static std::string GetID() { return "juan-mad"; }
            virtual void Enter() override;
            virtual void Exit() override;

            virtual SteeringOutput GetSteering() override;
    };

    class JuanMachine : public StateMachine
    {
        public: 
            JuanMachine() : StateMachine()
            {
                m_StateMap[JuanWander::GetID()] = new JuanWander();
                m_StateMap[JuanMad::GetID()] = new JuanMad();
                m_CurrentState = JuanWander::GetID();
            }
    };
};