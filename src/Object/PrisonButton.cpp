#include "PrisonButton.hpp"

#include "Engine.hpp"
#include "Collider.hpp"
#include "TextureManager.hpp"

namespace shp
{
    void PrisonButton::Draw()
    {
        TextureManager::GetInstance()->Draw(m_TextureID, 
                                            (int) m_Transform.x, 
                                            (int) m_Transform.z,
                                            m_Width, 
                                            m_Depth); 
    }
    
    void PrisonButton::Update(double dt)
    {
        Collider* NicoColider = Engine::GetInstance()->GetNico()->GetCollider(); 
        Collider* RedColider = Engine::GetInstance()->GetRed()->GetCollider(); 
        Collider* GreenColider = Engine::GetInstance()->GetGreen()->GetCollider(); 

        if(!m_Pushed && Collider::Intersects(*m_Collider, *NicoColider) &&
           !Engine::GetInstance()->IsNicoDead())
        {
            m_Pushed = true;
            m_TextureID = "button-pushed";
            Engine::GetInstance()->FreeFran();
        }
        
        if(m_Pushed && (Collider::Intersects(*m_Collider, *GreenColider) ||
                        Collider::Intersects(*m_Collider, *RedColider)))
        {
            m_Pushed = false;
            m_TextureID = "button-unpushed";
            Engine::GetInstance()->LockFran();
        }
    }

    void PrisonButton::Clean()
    {
        delete m_Collider;
    }
};