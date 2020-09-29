#include "Character.hpp"

#include "TextureManager.hpp"
#include "CollisionHandler.hpp"

namespace shp
{
    void Character::Draw()
    {
        TextureManager::GetInstance()->Draw(m_TextureID, 
                                            (int) m_Transform.x, 
                                            (int) m_Transform.z,
                                            m_Width, 
                                            m_Depth, 
                                            RadiansToDegrees(m_Kinematic->GetOrientation()), 
                                            1.0 + m_Transform.y / 32.0);
    }

    void Character::Update(double dt)
    {
        Vector3 position = m_Kinematic->GetPosition();
        Vector3 positionXZ = { position.x, m_Transform.y, position.z };
        Vector3 positionX = { position.x, m_Transform.y, m_Transform.z };
        Vector3 positionZ = { m_Transform.x, m_Transform.y, position.z };

        m_Collider->setPosition(position);
        if(!CollisionHandler::GetInstance()->Colliding(m_Collider))
        {
            m_Transform = position;
            return;
        }

        m_Collider->setPosition(positionXZ);
        if(!CollisionHandler::GetInstance()->Colliding(m_Collider))
        {
            m_Kinematic->SetPosition(positionXZ);
            m_Kinematic->SetVelocityY(0.0);
            m_Transform = positionXZ;
            return;
        }

        m_Collider->setPosition(positionX);
        if(!CollisionHandler::GetInstance()->Colliding(m_Collider))
        {
            m_Kinematic->SetPosition(positionX);
            m_Kinematic->SetVelocityY(0.0);
            m_Kinematic->SetVelocityZ(0.0);
            m_Transform = positionX;
            return;
        }

        m_Collider->setPosition(positionZ);
        if(!CollisionHandler::GetInstance()->Colliding(m_Collider))
        {
            m_Kinematic->SetPosition(positionZ);
            m_Kinematic->SetVelocityY(0.0);
            m_Kinematic->SetVelocityX(0.0);
            m_Transform = positionZ;
            return;
        }
    }

    void Character::Clean()
    {
        delete m_Kinematic;
        delete m_Collider;
    }
};