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
                                            m_Kinematic.GetOrientation(), 
                                            1.0 + m_Transform.y / 32.0);
    }

    void Character::Update(double dt)
    {
        m_Collider.setPosition(m_Kinematic.GetPosition());
        if(CollisionHandler::GetInstance()->Colliding(m_Collider))
        {
            m_Kinematic.SetPositionY(m_Transform.y);
            m_Kinematic.SetVelocityY(0.0);
        }

        m_Collider.setPosition(m_Kinematic.GetPosition());
        if(CollisionHandler::GetInstance()->Colliding(m_Collider))
        {
            m_Kinematic.SetPositionX(m_Transform.x);
            m_Kinematic.SetVelocityX(0.0);
        }

        m_Collider.setPosition(m_Kinematic.GetPosition());
        if(CollisionHandler::GetInstance()->Colliding(m_Collider))
        {
            m_Kinematic.SetPositionZ(m_Transform.z);
            m_Kinematic.SetVelocityZ(0.0);
        }

        m_Transform = m_Kinematic.GetPosition();
        m_Collider.setPosition(m_Transform);
    }

    void Character::Clean()
    {

    }
};