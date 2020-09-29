#include "FranMachine.hpp"

#include "Engine.hpp"
#include "Sight.hpp"
#include "Iddle.hpp"
#include "BlendedSteering.hpp"
#include "LookWhereYoureGoing.hpp"
#include "GraphWander.hpp"
#include "GraphSeek.hpp"
#include "GraphFlee.hpp"
#include "ObstacleAvoidance.hpp"
#include "Hearing.hpp"

namespace shp
{
    namespace Fran
    {
        bool IsFranFree()
        {
            return Engine::GetInstance()->IsFranFree();
        }
        bool IsNicoDead()
        {
            return Engine::GetInstance()->IsNicoDead();
        }
        bool IsChangActive()
        {
            return Engine::GetInstance()->ChangActive();
        }

        bool CanSeeNico()
        {
            return Sight::CanSee(Engine::GetInstance()->GetFran()->GetKinematic(),
                                    Engine::GetInstance()->GetNico()->GetKinematic());
        }
        bool CanSeeRed()
        {
            return Sight::CanSee(Engine::GetInstance()->GetFran()->GetKinematic(),
                                    Engine::GetInstance()->GetRed()->GetKinematic());
        }
        bool CanSeeGreen()
        {
            return Sight::CanSee(Engine::GetInstance()->GetFran()->GetKinematic(),
                                    Engine::GetInstance()->GetGreen()->GetKinematic());
        }

        bool CanHearNico()
        {
            return Hearing::CanHear(Engine::GetInstance()->GetFran()->GetKinematic(),
                                    Engine::GetInstance()->GetNico()->GetKinematic());
        }
        bool CanHearRed()
        {
            return Hearing::CanHear(Engine::GetInstance()->GetFran()->GetKinematic(),
                                    Engine::GetInstance()->GetRed()->GetKinematic());
        }
        bool CanHearGreen()
        {
            return Hearing::CanHear(Engine::GetInstance()->GetFran()->GetKinematic(),
                                    Engine::GetInstance()->GetGreen()->GetKinematic());
        }
    };

    using namespace Fran;

    FranLocked::FranLocked()
    {
        m_Transitions.clear();
        m_Transitions[FranFree::GetID()] = 
            []() 
            {
                return IsFranFree();
            };
        
        m_Behaviour = new Iddle();
    }

    FranFree::FranFree()
    {
        m_Transitions.clear();
        m_Transitions[FranLocked::GetID()] = 
            []() 
            {
                return !IsFranFree();
            };

        m_Transitions[FranNico::GetID()] = 
            []()
            {
                return CanSeeNico() || CanHearNico();
            };
        m_Transitions[FranFlee::GetID()] = 
            []()
            {
                return !IsChangActive() &&
                       (CanSeeRed() || CanSeeGreen() ||
                        CanHearRed() || CanHearGreen());
            };
        
        Kinematic* kinematic = Engine::GetInstance()->GetFran()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphWander(kinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    FranFlee::FranFlee()
    {
        m_Transitions.clear();
        m_Transitions[FranLocked::GetID()] = 
            []() 
            {
                return !IsFranFree();
            };

        m_Transitions[FranNico::GetID()] = 
            []()
            {
                return CanSeeNico() || CanHearNico();
            };
        m_Transitions[FranFree::GetID()] = 
            []()
            {
                return IsChangActive() || 
                       (!CanSeeRed() && !CanSeeGreen() &&
                        !CanHearRed() && !CanHearGreen());
            };
        
        Kinematic* kinematic = Engine::GetInstance()->GetFran()->GetKinematic();
        Kinematic* redKinematic = Engine::GetInstance()->GetRed()->GetKinematic();
        Kinematic* greenKinematic = Engine::GetInstance()->GetGreen()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        GraphFlee* flee = new GraphFlee(kinematic);
        flee->AddTarget(redKinematic);
        flee->AddTarget(greenKinematic);

        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(flee);
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    FranNico::FranNico()
    {
        m_Transitions.clear();
        m_Transitions[FranLocked::GetID()] = 
            []() 
            {
                return !IsFranFree();
            };

        m_Transitions[FranFree::GetID()] = 
            []()
            {
                return IsNicoDead();
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

    void FranFlee::Enter()
    {
        Engine::GetInstance()->GetFran()->SetTextureID("fran-flee");
    } 
    void FranFlee::Exit() { }

    void FranNico::Enter()
    {
        Engine::GetInstance()->GetFran()->SetTextureID("fran-nico");
    } 
    void FranNico::Exit() { }
};