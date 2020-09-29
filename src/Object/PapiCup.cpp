#include "PapiCup.hpp"

#include "Engine.hpp"
#include "Iddle.hpp"
#include "InputHandler.hpp"
#include "TextureManager.hpp"
#include "CollisionHandler.hpp"

namespace shp
{
    void PapiCup::Draw()
    {
        TextureManager::GetInstance()->Draw(m_TextureID, 
                                            (int) m_Transform.x, 
                                            (int) m_Transform.z,
                                            m_Width, 
                                            m_Depth, 
                                            RadiansToDegrees(m_Kinematic->GetOrientation()), 
                                            1.0 + m_Transform.y / 32.0);
    }

    void PapiCup::Update(double dt)
    {
        if(m_IsGrounded && InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_T)) { ThrowCup(); }
        if(CollisionHandler::GetInstance()->Colliding(m_Collider)) { m_IsGrounded = true; }

        if(m_IsGrounded)
        {
            Kinematic* juanKinematic = Engine::GetInstance()->GetJuan()->GetKinematic();
            Vector3 offset(juanKinematic->GetOrientation());
            offset.scale(32.0);
            Vector3 position = juanKinematic->GetPosition() + offset;

            m_Kinematic->SetPosition(position);
            m_Kinematic->SetOrientation(juanKinematic->GetOrientation());
            m_Kinematic->SetVelocity(Vector3::ZEROV);
        }
        else
        {
            Collider* nicoCollider = Engine::GetInstance()->GetNico()->GetCollider();
            if(Collider::Intersects(*m_Collider, *nicoCollider))
            {
                Engine::GetInstance()->Lose();
            }

            Iddle behaviour;
            m_Kinematic->Update(behaviour.GetSteering(), dt);
        }
        

        m_Transform = m_Kinematic->GetPosition();
        m_Collider->setPosition(m_Transform);
    }

    void PapiCup::ThrowCup()
    {
        m_IsGrounded = false;
        m_Kinematic->SetDrag(0.95);
        Kinematic* juanKinematic = Engine::GetInstance()->GetJuan()->GetKinematic();
        Vector3 direction(juanKinematic->GetOrientation());
        direction.scale(m_Kinematic->GetMaxSpeed());
        direction += Vector3::Y * m_Kinematic->GetMaxSpeed();

        m_Kinematic->SetVelocity(direction);
    }

    void PapiCup::Clean()
    {
        delete m_Kinematic;
        delete m_Collider;
    }
};