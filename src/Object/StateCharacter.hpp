#pragma once

#include "Character.hpp"
#include "StateMachine.hpp"

namespace shp
{
    // Class for Character with State Machine
    class StateCharacter : public Character
    {
        public:
            StateCharacter(ObjectProperties* props,
                           StateMachine* stateMachine)
                : Character(props),
                  m_StateMachine(stateMachine)
            {}

            inline void SetMachine(StateMachine* machine) { m_StateMachine = machine; }

            virtual void Update(double dt) override
            {
                m_Kinematic->Update(m_StateMachine->GetSteering(), dt);
                Character::Update(dt);
            }

        protected: 
            StateMachine* m_StateMachine;
    };
};