#pragma once

#include "StateMachine.hpp"

namespace shp
{
    class FranLocked : public State
    {
        public: 
            FranLocked();

            static std::string GetID() { return "fran-locked"; }
            virtual void Enter() override;
            virtual void Exit() override;

    };

    class FranFree : public State 
    {
        public:
            FranFree();

            static std::string GetID() { return "fran-free"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class FranNico : public State
    {
        public: 
            FranNico();

            static std::string GetID() { return "fran-nico"; }
            virtual void Enter() override;
            virtual void Exit() override;
    };

    class FranMachine : public StateMachine
    {
        public: 
            FranMachine() : StateMachine()
            {
                m_StateMap[FranLocked::GetID()] = new FranLocked();
                m_StateMap[FranFree::GetID()] = new FranFree();
                m_StateMap[FranNico::GetID()] = new FranNico();
                m_CurrentState = FranLocked::GetID();
            }
    };
};