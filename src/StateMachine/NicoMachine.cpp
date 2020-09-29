#include "NicoMachine.hpp"

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

namespace shp
{
    namespace Nico
    {
        void ActivateChang()
        {
            if(Engine::GetInstance()->ChangAvailable() &&
            !Engine::GetInstance()->ChangActive())
            {
                Engine::GetInstance()->ActivateChang();
            }
        }

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
        bool IsChangAvailable()
        {
            return Engine::GetInstance()->ChangAvailable();
        }

        bool CanSeeFran()
        {
            return Sight::CanSee(Engine::GetInstance()->GetNico()->GetKinematic(),
                                    Engine::GetInstance()->GetFran()->GetKinematic());
        }
        bool CanSeeRed()
        {
            return Sight::CanSee(Engine::GetInstance()->GetNico()->GetKinematic(),
                                    Engine::GetInstance()->GetRed()->GetKinematic());
        }
        bool CanSeeGreen()
        {
            return Sight::CanSee(Engine::GetInstance()->GetNico()->GetKinematic(),
                                    Engine::GetInstance()->GetGreen()->GetKinematic());
        }

        bool CanHearFran()
        {
            return Hearing::CanHear(Engine::GetInstance()->GetNico()->GetKinematic(),
                                    Engine::GetInstance()->GetFran()->GetKinematic());
        }
        bool CanHearRed()
        {
            return Hearing::CanHear(Engine::GetInstance()->GetNico()->GetKinematic(),
                                    Engine::GetInstance()->GetRed()->GetKinematic());
        }
        bool CanHearGreen()
        {
            return Hearing::CanHear(Engine::GetInstance()->GetNico()->GetKinematic(),
                                    Engine::GetInstance()->GetGreen()->GetKinematic());
        }
    };

    using namespace Nico;

    NicoDead::NicoDead()
    {
        m_Transitions.clear();
        m_Transitions[NicoButton::GetID()] = 
            []()
            {
                Vector3 NicoPosition = Engine::GetInstance()->GetNico()->GetKinematic()->GetPosition();
                Vector3 RedPosition = Engine::GetInstance()->GetRed()->GetKinematic()->GetPosition();
                Vector3 GreenPosition = Engine::GetInstance()->GetGreen()->GetKinematic()->GetPosition();
                return NicoPosition.distance(RedPosition) > 128.0 &&
                       NicoPosition.distance(GreenPosition) > 128.0;
            };

        m_Behaviour = new Iddle();
    }

    NicoButton::NicoButton()
    {
        m_Transitions.clear();
        m_Transitions[NicoDead::GetID()] = 
            []()
            {
                Collider* NicoCollider = Engine::GetInstance()->GetNico()->GetCollider();
                Collider* RedCollider = Engine::GetInstance()->GetRed()->GetCollider();
                Collider* GreenCollider = Engine::GetInstance()->GetGreen()->GetCollider();
                return !Engine::GetInstance()->ChangActive() &&
                       (Collider::Intersects(*NicoCollider, *RedCollider) ||
                        Collider::Intersects(*NicoCollider, *GreenCollider));
            };
        m_Transitions[NicoFran::GetID()] = 
            []()
            {
                return IsFranFree();
            };
        m_Transitions[NicoFlee::GetID()] = 
            []()
            {
                return !IsChangAvailable() &&
                        (CanSeeGreen() || CanSeeRed() ||
                         CanHearGreen() || CanHearRed());
            };

        Kinematic* kinematic = Engine::GetInstance()->GetNico()->GetKinematic();
        Kinematic* buttonKinematic = Engine::GetInstance()->GetButtonPosition();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, buttonKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    NicoFran::NicoFran()
    {
        m_Transitions.clear();
        m_Transitions[NicoDead::GetID()] = 
            []()
            {
                Collider* NicoCollider = Engine::GetInstance()->GetNico()->GetCollider();
                Collider* RedCollider = Engine::GetInstance()->GetRed()->GetCollider();
                Collider* GreenCollider = Engine::GetInstance()->GetGreen()->GetCollider();
                return !Engine::GetInstance()->ChangActive() &&
                       (Collider::Intersects(*NicoCollider, *RedCollider) ||
                        Collider::Intersects(*NicoCollider, *GreenCollider));
            };
        m_Transitions[NicoButton::GetID()] = 
            []()
            {
                return !IsFranFree();
            };
        m_Transitions[NicoEscort::GetID()] = 
            []()
            {
                return CanSeeFran() || CanHearFran();
            };
        m_Transitions[NicoFlee::GetID()] = 
            []()
            {
                return !IsChangAvailable() &&
                       (CanSeeGreen() || CanSeeRed() ||
                        CanHearGreen() || CanHearRed());
            };

        Kinematic* kinematic = Engine::GetInstance()->GetNico()->GetKinematic();
        Kinematic* franKinematic = Engine::GetInstance()->GetFran()->GetKinematic();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, franKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    NicoEscort::NicoEscort()
    {
        m_Transitions.clear();
        m_Transitions[NicoDead::GetID()] = 
            []()
            {
                Collider* NicoCollider = Engine::GetInstance()->GetNico()->GetCollider();
                Collider* RedCollider = Engine::GetInstance()->GetRed()->GetCollider();
                Collider* GreenCollider = Engine::GetInstance()->GetGreen()->GetCollider();
                return !Engine::GetInstance()->ChangActive() &&
                       (Collider::Intersects(*NicoCollider, *RedCollider) ||
                        Collider::Intersects(*NicoCollider, *GreenCollider));
            };
        m_Transitions[NicoButton::GetID()] = 
            []()
            {
                return !IsFranFree();
            };
        m_Transitions[NicoFlee::GetID()] = 
            []()
            {
                return !IsChangAvailable() &&
                       (CanSeeGreen() || CanSeeRed() ||
                        CanHearGreen() || CanHearRed());
            };
        m_Transitions[NicoFran::GetID()] = 
            []()
            {
                return !(CanSeeFran() || CanHearFran());
            };

        Kinematic* kinematic = Engine::GetInstance()->GetNico()->GetKinematic();
        Kinematic* zoneKinematic = Engine::GetInstance()->GetZonePosition();
        BlendedSteering* behaviour = new BlendedSteering();
        behaviour->AddBehaviour(new LookWhereYoureGoing(kinematic));
        behaviour->AddBehaviour(new GraphSeek(kinematic, zoneKinematic));
        behaviour->AddBehaviour(new ObstacleAvoidance(kinematic));
        m_Behaviour = behaviour;
    }

    NicoFlee::NicoFlee()
    {
        m_Transitions.clear();
        m_Transitions[NicoDead::GetID()] = 
            []()
            {
                Collider* NicoCollider = Engine::GetInstance()->GetNico()->GetCollider();
                Collider* RedCollider = Engine::GetInstance()->GetRed()->GetCollider();
                Collider* GreenCollider = Engine::GetInstance()->GetGreen()->GetCollider();
                return !Engine::GetInstance()->ChangActive() &&
                       (Collider::Intersects(*NicoCollider, *RedCollider) ||
                        Collider::Intersects(*NicoCollider, *GreenCollider));
            };
        m_Transitions[NicoButton::GetID()] = 
            []()
            {
                Vector3 NicoPosition = Engine::GetInstance()->GetNico()->GetKinematic()->GetPosition();
                Vector3 RedPosition = Engine::GetInstance()->GetRed()->GetKinematic()->GetPosition();
                Vector3 GreenPosition = Engine::GetInstance()->GetGreen()->GetKinematic()->GetPosition();
                return NicoPosition.distance(RedPosition) > 128.0 &&
                       NicoPosition.distance(GreenPosition) > 128.0;
            };

        Kinematic* kinematic = Engine::GetInstance()->GetNico()->GetKinematic();
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

    SteeringOutput NicoButton::GetSteering()
    {
        if(CanSeeGreen() || CanSeeRed() ||
           CanHearGreen() || CanHearRed())
        {
            ActivateChang();
        }
        return State::GetSteering();
    }

    SteeringOutput NicoFran::GetSteering()
    {
        if(CanSeeGreen() || CanSeeRed() ||
           CanHearGreen() || CanHearRed())
        {
            ActivateChang();
        }
        return State::GetSteering();
    }

    SteeringOutput NicoEscort::GetSteering()
    {
        if(CanSeeGreen() || CanSeeRed() ||
           CanHearGreen() || CanHearRed())
        {
            ActivateChang();
        }
        return State::GetSteering();
    }

    void NicoDead::Enter() 
    { 
        Engine::GetInstance()->KillNico();
        Engine::GetInstance()->GetNico()->SetTextureID("nico-dead");
    }
    void NicoDead::Exit() 
    {
        Engine::GetInstance()->ReviveNico();
    }

    void NicoFran::Enter() 
    { 
        Engine::GetInstance()->GetNico()->SetTextureID("nico");
    }
    void NicoFran::Exit() { }

    void NicoFlee::Enter() 
    { 
        Engine::GetInstance()->GetNico()->SetTextureID("nico-flee");
    }
    void NicoFlee::Exit() { }

    void NicoEscort::Enter()
    { 
        Engine::GetInstance()->GetNico()->SetTextureID("nico-escort");
    }
    void NicoEscort::Exit() { }

    void NicoButton::Enter()
    { 
        Engine::GetInstance()->GetNico()->SetTextureID("nico");
    }
    void NicoButton::Exit() { }

};