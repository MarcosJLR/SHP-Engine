#include "Enemy.hpp"

#include "Graph.hpp"

namespace shp
{
    void Enemy::Update(double dt)
    {
        m_Kinematic->Update(m_Behaviour->GetSteering(), dt);
        Character::Update(dt);
    }

    void Enemy::Draw()
    {
        BlendedSteering* behaviour = (BlendedSteering*) m_Behaviour;
        GraphSeek* seek = (GraphSeek*) behaviour->GetBehaviour(1);
        Graph::DrawPath(seek->GetPath());

        Character::Draw();
    }
};