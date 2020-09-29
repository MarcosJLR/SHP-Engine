#pragma once

#include "StateMachine.hpp"

namespace shp
{
    class GreenPatrol : public State
    {
        public: 
            GreenPatrol();

            static std::string GetID() { return "green-patrol"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class GreenNico : public State
    {
        public: 
            GreenNico();

            static std::string GetID() { return "green-nico"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class GreenButton : public State
    {
        public: 
            GreenButton();

            static std::string GetID() { return "green-button"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class GreenChanged : public State
    {
        public: 
            GreenChanged();

            static std::string GetID() { return "green-changed"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class GreenMachine : public StateMachine
    {
        public: 
            GreenMachine() : StateMachine()
            {
                m_StateMap[GreenPatrol::GetID()] = new GreenPatrol();
                m_StateMap[GreenNico::GetID()] = new GreenNico();
                m_StateMap[GreenButton::GetID()] = new GreenButton();
                m_StateMap[GreenChanged::GetID()] = new GreenChanged();
                m_CurrentState = GreenPatrol::GetID();
            }
    };
};