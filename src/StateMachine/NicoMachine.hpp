#pragma once

#include "StateMachine.hpp"

namespace shp
{
    class NicoDead : public State 
    {
        public:
            NicoDead();

            static std::string GetID() { return "nico-dead"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class NicoButton : public State 
    {
        public:
            NicoButton();

            static std::string GetID() { return "nico-button"; }
            virtual void Enter() override;
            virtual void Exit() override;

            virtual SteeringOutput GetSteering() override;
    };

    class NicoFran : public State 
    {
        public:
            NicoFran();

            static std::string GetID() { return "nico-fran"; }
            virtual void Enter() override;
            virtual void Exit() override;

            virtual SteeringOutput GetSteering() override;
    };

    class NicoEscort : public State 
    {
        public:
            NicoEscort();

            static std::string GetID() { return "nico-escort"; }
            virtual void Enter() override;
            virtual void Exit() override;

            virtual SteeringOutput GetSteering() override;
    };

    class NicoFlee : public State 
    {
        public:
            NicoFlee();

            static std::string GetID() { return "nico-flee"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class NicoMachine : public StateMachine
    {
        public: 
            NicoMachine() : StateMachine()
            {
                m_StateMap[NicoDead::GetID()] = new NicoDead();
                m_StateMap[NicoButton::GetID()] = new NicoButton();
                m_StateMap[NicoEscort::GetID()] = new NicoEscort();
                m_StateMap[NicoFlee::GetID()] = new NicoFlee();
                m_StateMap[NicoFran::GetID()] = new NicoFran();
                m_CurrentState = NicoButton::GetID();
            }
    };
};