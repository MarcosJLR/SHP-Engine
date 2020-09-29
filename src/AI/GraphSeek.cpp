#include "GraphSeek.hpp"

#include <algorithm>
#include <iostream>

namespace shp
{
    SteeringOutput GraphSeek::GetSteering()
    {
        SteeringOutput result;

        Vector3 position = m_Character->GetPosition();
        Vector3 targetPosition = m_Target->GetPosition();
        
        int newCharacterNode = Graph::GetInstance()->GetNodeFromPosition(position);
        int newTargetNode = Graph::GetInstance()->GetNodeFromPosition(targetPosition);

        if(newTargetNode != m_TargetNode || newCharacterNode != m_CharacterNode)
        {
            m_Path.clear();
            m_Path = Graph::GetInstance()->GetShortestPath(position, targetPosition);
            m_Path = Graph::SmoothPath(m_Path);
            
            std::reverse(m_Path.begin(), m_Path.end());
            m_TargetNode = newTargetNode;
            m_CharacterNode = newCharacterNode;
        }

        while(!m_Path.empty() && position.distance(m_Path.back()) < m_Radius)
        {
            m_Path.pop_back();
        }

        if(m_Path.empty())
        {
            delete Seek::m_Target;
            Seek::m_Target = new Kinematic(m_Target->GetPosition(), 0, 0, 0);
            return Seek::GetSteering();
        }

        delete Seek::m_Target;
        Seek::m_Target = new Kinematic(m_Path.back(), 0, 0, 0);
        
        //std::cout << m_Path.back().x << " ";
        //std::cout << m_Path.back().y << " ";
        //std::cout << m_Path.back().z << "\n";

        return Seek::GetSteering();
    }
};