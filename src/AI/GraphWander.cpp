#include "GraphWander.hpp"

#include <cstdlib>

namespace shp
{
    SteeringOutput GraphWander::GetSteering()
    {
        int characterNode = Graph::GetInstance()->GetNodeFromPosition(m_Character->GetPosition());
        if(m_Target == nullptr || characterNode == Graph::GetInstance()->GetNodeFromPosition(m_Target->GetPosition()))
        {
            int targetNode = rand() % Graph::GetInstance()->GetSize();
            Vector3 targetPosition = Graph::GetInstance()->GetCenter(targetNode);

            delete m_Target;
            m_Target = new Kinematic(targetPosition, 0, 0, 0);
        }

        return GraphSeek::GetSteering();
    }
};