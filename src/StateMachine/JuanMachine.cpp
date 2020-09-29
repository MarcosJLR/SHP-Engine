#include "JuanMachine.hpp"

#include "Engine.hpp"
#include "Sight.hpp"
#include "Motion.hpp"
#include "Collider.hpp"
#include "Iddle.hpp"
#include "BlendedSteering.hpp"
#include "LookWhereYoureGoing.hpp"
#include "GraphWander.hpp"
#include "GraphSeek.hpp"
#include "GraphFlee.hpp"
#include "ObstacleAvoidance.hpp"
#include "Hearing.hpp"

#include <cstdlib>

namespace shp
{
    namespace Juan
    {
        bool IsFranFree()
        {
            return Engine::GetInstance()->IsFranFree();
        }
        bool CanSeeNico()
        {
            return Sight::CanSee(Engine::GetInstance()->GetJuan()->GetKinematic(),
                                 Engine::GetInstance()->GetNico()->GetKinematic());
        }
    };

    using namespace Juan;

    JuanWander::JuanWander()
    {
        m_Transitions.clear();
        m_Transitions[JuanMad::GetID()] = 
            []()
            {
                return IsFranFree();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetJuan()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphWander(kinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    JuanMad::JuanMad()
    {
        m_Transitions.clear();
        m_Transitions[JuanWander::GetID()] = 
            []()
            {
                return !IsFranFree();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetJuan()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphWander(kinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    SteeringOutput JuanMad::GetSteering()
    {
        if(Engine::GetInstance()->GetPapiCup()->IsGrounded() &&
           (CanSeeNico() || rand() % 500 == 0))
        {
            Engine::GetInstance()->GetPapiCup()->ThrowCup();
        }
        return State::GetSteering();
    }

    void JuanWander::Enter() 
    { 
        Engine::GetInstance()->GetJuan()->SetTextureID("juan");
    }
    void JuanWander::Exit() { }

    void JuanMad::Enter() 
    { 
        Engine::GetInstance()->GetJuan()->SetTextureID("juan-mad");
    }
    void JuanMad::Exit() { }

};