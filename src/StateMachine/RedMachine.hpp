#pragma once

#include "StateMachine.hpp"

namespace shp
{
    class RedPatrol : public State
    {
        public: 
            RedPatrol();

            static std::string GetID() { return "red-patrol"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class RedNico : public State
    {
        public: 
            RedNico();

            static std::string GetID() { return "red-nico"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class RedFran : public State
    {
        public: 
            RedFran();

            static std::string GetID() { return "red-fran"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class RedZone : public State
    {
        public: 
            RedZone();

            static std::string GetID() { return "red-zone"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class RedChanged : public State
    {
        public: 
            RedChanged();

            static std::string GetID() { return "red-changed"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class RedMachine : public StateMachine
    {
        public: 
            RedMachine() : StateMachine()
            {
                m_StateMap[RedPatrol::GetID()] = new RedPatrol();
                m_StateMap[RedNico::GetID()] = new RedNico();
                m_StateMap[RedFran::GetID()] = new RedFran();
                m_StateMap[RedZone::GetID()] = new RedZone();
                m_StateMap[RedChanged::GetID()] = new RedChanged();
                m_CurrentState = RedPatrol::GetID();
            }
    };
};