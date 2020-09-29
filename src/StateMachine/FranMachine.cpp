#include "FranMachine.hpp"

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
    FranLocked::FranLocked()
    {
        m_Transitions.clear();
        m_Transitions[FranFree::GetID()] = 
            []() 
            {
                return Engine::GetInstance()->IsFranFree();
            };
        
        m_Behaviour = new Iddle();
    }

    FranFree::FranFree()
    {
        m_Transitions.clear();
        m_Transitions[FranLocked::GetID()] = 
            []() 
            {
                return !(Engine::GetInstance()->IsFranFree());
            };

        m_Transitions[FranNico::GetID()] = 
            []()
            {
                return Sight::CanSee(Engine::GetInstance()->GetFran()->GetKinematic(),
                                     Engine::GetInstance()->GetNico()->GetKinematic());
            };
        
        Kinematic* kinematic = Engine::GetInstance()->GetFran()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphWander(kinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    FranNico::FranNico()
    {
        m_Transitions.clear();
        m_Transitions[FranLocked::GetID()] = 
            []() 
            {
                return !(Engine::GetInstance()->IsFranFree());
            };

        m_Transitions[FranFree::GetID()] = 
            []()
            {
                return Engine::GetInstance()->IsNicoDead();
            };

        Kinematic* kinematic = Engine::GetInstance()->GetFran()->GetKinematic();
        Kinematic* nicoKinematic = Engine::GetInstance()->GetNico()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, nicoKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    void FranLocked::Enter()
    {
        Engine::GetInstance()->GetFran()->SetTextureID("fran-locked");
    }
    void FranLocked::Exit() { }

    void FranFree::Enter()
    {
        Engine::GetInstance()->GetFran()->SetTextureID("fran-free");
    } 
    void FranFree::Exit() { }

    void FranNico::Enter()
    {
        Engine::GetInstance()->GetFran()->SetTextureID("fran-nico");
    } 
    void FranNico::Exit() { }
};