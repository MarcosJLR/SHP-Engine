#include "StateMachine.hpp"

#include <iostream>

namespace shp
{
    std::string State::GetTransition()
    {
        for(auto [id, f] : m_Transitions)
        {
            if(f()) { return id; }
        }

        return "";
    }

    SteeringOutput StateMachine::GetSteering()
    {
        std::string newState = m_StateMap[m_CurrentState]->GetTransition();
        if(!newState.empty())
        {
            m_StateMap[m_CurrentState]->Exit();
            m_CurrentState = newState;
            m_StateMap[m_CurrentState]->Enter();
        }

        std::cout << m_CurrentState << std::endl;
        return m_StateMap[m_CurrentState]->GetSteering();
    }
};