#include "GraphFlee.hpp"

#include "Graph.hpp"
#include <iostream>

namespace shp
{
    void GraphFlee::AddTarget(Kinematic* target)
    {
        int targetNode = Graph::GetInstance()->GetNodeFromPosition(target->GetPosition());
        m_Targets.push_back(target);
        m_TargetNodes.push_back(targetNode);
    }

    bool GraphFlee::UpdateTargetNodes()
    {
        bool result = false;
        for(int i = 0; i < (int) m_Targets.size(); i++)
        {
            int currentNode = m_TargetNodes[i];
            m_TargetNodes[i] = Graph::GetInstance()->GetNodeFromPosition(m_Targets[i]->GetPosition());
            result = result || (m_TargetNodes[i] != currentNode);
        }
        return result;
    }

    double GraphFlee::MinDistanceTo(int node)
    {
        double result = 1.0 / 0.0;
        for(int targetNode : m_TargetNodes)
        {
            result = std::min(result, Graph::PathLength(Graph::GetInstance()->GetShortestPath(node, targetNode)));
        }
        return result;
    }

    SteeringOutput GraphFlee::GetSteering()
    {
        int newNode = Graph::GetInstance()->GetNodeFromPosition(m_Character->GetPosition());
        if(newNode != m_CurrentNode)
        {
            m_CurrentNode = newNode;
            UpdateTargetNodes();

            delete m_Target;
            std::vector<int> neighbors = Graph::GetInstance()->GetNeighbors(m_CurrentNode);

            int targetNode = neighbors[0];
            double MaxMinDist = MinDistanceTo(targetNode);
            for(int i = 1; i < (int) neighbors.size(); i++)
            {
                double dist = MinDistanceTo(neighbors[i]);
                if(dist > MaxMinDist)
                {
                    targetNode = neighbors[i];
                    MaxMinDist = dist;
                }
            }

            m_Target = new Kinematic(Graph::GetInstance()->GetCenter(targetNode), 0.0, 0.0, 0.0);
        }

        return Seek::GetSteering();
    }
};