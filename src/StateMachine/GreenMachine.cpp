#include "GreenMachine.hpp"

#include "Engine.hpp"
#include "Sight.hpp"
#include "Iddle.hpp"
#include "BlendedSteering.hpp"
#include "LookWhereYoureGoing.hpp"
#include "GraphWander.hpp"
#include "GraphSeek.hpp"
#include "ObstacleAvoidance.hpp"

namespace shp
{
    GreenPatrol::GreenPatrol()
    {
        m_Transitions.clear();
        m_Transitions[GreenNico::GetID()] =
            []()
            {
                return Sight::CanSee(Engine::GetInstance()->GetGreen()->GetKinematic(),
                                     Engine::GetInstance()->GetNico()->GetKinematic());
            };
        m_Transitions[GreenButton::GetID()] = 
            []()
            {
                return Engine::GetInstance()->IsFranFree();
            };
        m_Transitions[GreenChanged::GetID()] =
            []()
            {
                return Engine::GetInstance()->ChangActive();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetGreen()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphWander(kinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    GreenNico::GreenNico()
    {
        m_Transitions.clear();
        m_Transitions[GreenPatrol::GetID()] =
            []()
            {
                return !(Sight::CanSee(Engine::GetInstance()->GetGreen()->GetKinematic(),
                                       Engine::GetInstance()->GetNico()->GetKinematic())) ||
                       Engine::GetInstance()->IsNicoDead();
            };
        m_Transitions[GreenChanged::GetID()] =
            []()
            {
                return Engine::GetInstance()->ChangActive();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetGreen()->GetKinematic();
        Kinematic* nicoKinematic = Engine::GetInstance()->GetNico()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, nicoKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    GreenButton::GreenButton()
    {
        m_Transitions.clear();
        m_Transitions[GreenNico::GetID()] =
            []()
            {
                return Sight::CanSee(Engine::GetInstance()->GetGreen()->GetKinematic(),
                                     Engine::GetInstance()->GetNico()->GetKinematic());
            };
        m_Transitions[GreenPatrol::GetID()] = 
            []()
            {
                return !(Engine::GetInstance()->IsFranFree());
            };
        m_Transitions[GreenChanged::GetID()] =
            []()
            {
                return Engine::GetInstance()->ChangActive();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetGreen()->GetKinematic();
        Kinematic* buttonKinematic = Engine::GetInstance()->GetButtonPosition();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, buttonKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    GreenChanged::GreenChanged()
    {
        m_Transitions.clear();
        m_Transitions[GreenPatrol::GetID()] =
            []()
            {
                return !(Engine::GetInstance()->ChangActive());
            };

        m_Behaviour = new Iddle();
    }

    void GreenPatrol::Enter() { }
    void GreenPatrol::Exit() { }

    void GreenNico::Enter() { }
    void GreenNico::Exit() { }

    void GreenButton::Enter() { }
    void GreenButton::Exit() { }

    void GreenChanged::Enter() 
    {
        Engine::GetInstance()->GetGreen()->SetTextureID("green-changed");
    }
    void GreenChanged::Exit() 
    {
        Engine::GetInstance()->GetGreen()->SetTextureID("green");
    }
};