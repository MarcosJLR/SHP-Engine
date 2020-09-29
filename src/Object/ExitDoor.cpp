#include "ExitDoor.hpp"

#include "TextureManager.hpp"
#include "Engine.hpp"

namespace shp
{
    void ExitDoor::Draw()
    {
        TextureManager::GetInstance()->Draw(m_TextureID, 
                                            (int) m_Transform.x, 
                                            (int) m_Transform.z,
                                            m_Width, 
                                            m_Depth); 
    }

    void ExitDoor::Update(double dt)
    {
        Collider* NicoCollider = Engine::GetInstance()->GetNico()->GetCollider(); 
        Collider* FranCollider = Engine::GetInstance()->GetFran()->GetCollider(); 

        if(Collider::Intersects(*NicoCollider, *m_Collider) &&
           Collider::Intersects(*FranCollider, *m_Collider))
        {
            Engine::GetInstance()->Win();
        }
    }

    void ExitDoor::Clean()
    {
        delete m_Collider;
    }
}