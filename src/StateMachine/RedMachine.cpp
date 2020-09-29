#include "RedMachine.hpp"

#include "Engine.hpp"
#include "Sight.hpp"
#include "Motion.hpp"
#include "Iddle.hpp"
#include "BlendedSteering.hpp"
#include "LookWhereYoureGoing.hpp"
#include "GraphWander.hpp"
#include "GraphSeek.hpp"
#include "ObstacleAvoidance.hpp"

namespace shp
{
    RedPatrol::RedPatrol()
    {
        m_Transitions.clear();
        m_Transitions[RedNico::GetID()] =
            []()
            {
                return Sight::CanSee(Engine::GetInstance()->GetRed()->GetKinematic(),
                                     Engine::GetInstance()->GetNico()->GetKinematic()) ||
                       Motion::CanFeel(Engine::GetInstance()->GetRed()->GetKinematic(),
                                       Engine::GetInstance()->GetNico()->GetKinematic());
            };
        m_Transitions[RedZone::GetID()] = 
            []()
            {
                return Engine::GetInstance()->IsFranFree();
            };
        m_Transitions[RedChanged::GetID()] =
            []()
            {
                return Engine::GetInstance()->ChangActive();
            };
        
        Kinematic* kinematic = Engine::GetInstance()->GetRed()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphWander(kinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    RedNico::RedNico()
    {
        m_Transitions.clear();
        m_Transitions[RedPatrol::GetID()] =
            []()
            {
                return !(Sight::CanSee(Engine::GetInstance()->GetRed()->GetKinematic(),
                                       Engine::GetInstance()->GetNico()->GetKinematic()) ||
                         Motion::CanFeel(Engine::GetInstance()->GetRed()->GetKinematic(),
                                         Engine::GetInstance()->GetNico()->GetKinematic())) ||
                       Engine::GetInstance()->IsNicoDead();
            };
        m_Transitions[RedChanged::GetID()] =
            []()
            {
                return Engine::GetInstance()->ChangActive();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetRed()->GetKinematic();
        Kinematic* nicoKinematic = Engine::GetInstance()->GetNico()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, nicoKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    RedFran::RedFran()
    {
        m_Transitions.clear();
        m_Transitions[RedPatrol::GetID()] =
            []()
            {
                return !(Sight::CanSee(Engine::GetInstance()->GetRed()->GetKinematic(),
                                       Engine::GetInstance()->GetFran()->GetKinematic()) ||
                         Motion::CanFeel(Engine::GetInstance()->GetRed()->GetKinematic(),
                                         Engine::GetInstance()->GetFran()->GetKinematic())) ||
                       !(Engine::GetInstance()->IsFranFree());
            };
        m_Transitions[RedChanged::GetID()] =
            []()
            {
                return Engine::GetInstance()->ChangActive();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetRed()->GetKinematic();
        Kinematic* franKinematic = Engine::GetInstance()->GetFran()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, franKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    RedZone::RedZone()
    {
        m_Transitions.clear();
        m_Transitions[RedNico::GetID()] =
            []()
            {
                return Sight::CanSee(Engine::GetInstance()->GetRed()->GetKinematic(),
                                     Engine::GetInstance()->GetNico()->GetKinematic()) ||
                       Motion::CanFeel(Engine::GetInstance()->GetRed()->GetKinematic(),
                                       Engine::GetInstance()->GetNico()->GetKinematic());
            };
        m_Transitions[RedFran::GetID()] =
            []()
            {
                return Sight::CanSee(Engine::GetInstance()->GetRed()->GetKinematic(),
                                     Engine::GetInstance()->GetFran()->GetKinematic()) ||
                       Motion::CanFeel(Engine::GetInstance()->GetRed()->GetKinematic(),
                                       Engine::GetInstance()->GetFran()->GetKinematic());
            };
        m_Transitions[RedPatrol::GetID()] = 
            []()
            {
                return !(Engine::GetInstance()->IsFranFree());
            };
        m_Transitions[RedChanged::GetID()] =
            []()
            {
                return Engine::GetInstance()->ChangActive();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetRed()->GetKinematic();
        Kinematic* zoneKinematic = Engine::GetInstance()->GetZonePosition();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, zoneKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    RedChanged::RedChanged()
    {
        m_Transitions.clear();
        m_Transitions[RedPatrol::GetID()] =
            []()
            {
                return !(Engine::GetInstance()->ChangActive());
            };

        m_Behaviour = new Iddle();
    }

    void RedPatrol::Enter() { }
    void RedPatrol::Exit() { }

    void RedNico::Enter() { }
    void RedNico::Exit() { }

    void RedFran::Enter() { }
    void RedFran::Exit() { }

    void RedZone::Enter() { }
    void RedZone::Exit() { }

    void RedChanged::Enter() 
    {
        //Engine::GetInstance()->GetRed()->SetTextureID("red-chang");
    }
    void RedChanged::Exit() 
    {
        //Engine::GetInstance()->GetRed()->SetTextureID("red-normal");
    }

};