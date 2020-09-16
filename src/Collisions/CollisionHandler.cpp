#include "CollisionHandler.hpp"

#define INF 1e9

namespace shp
{
    CollisionHandler* CollisionHandler::s_Instance = nullptr;

    CollisionHandler::CollisionHandler()
    {
        m_MapObstacles.push_back(Collider(-10, -10, -10, 1300, 10, 980)); // Floor
        m_MapObstacles.push_back(Collider(-10, -10, -10, 1300, INF, 10)); // Upper wall
        m_MapObstacles.push_back(Collider(-10, -10, -10, 10, INF, 980));  // Left wall
        m_MapObstacles.push_back(Collider(1280, -10, -10, 10, INF, 980)); // Right wall
        m_MapObstacles.push_back(Collider(-10, -10, 960, 1300, INF, 10)); // Lower wall
    }

    bool CollisionHandler::Colliding(Collider collider)
    {
        for(Collider& obstacle : m_MapObstacles)
        {
            if(Collider::Intersects(collider, obstacle)) 
                return true;
        }
        return false;
    }

    Collision* CollisionHandler::RayCast(Ray ray)
    {
        Collision* result = nullptr;
        double minDist = -1;

        for(Collider& obstacle : m_MapObstacles)
        {
            Collision* raycast = Collider::RayCast(ray, obstacle);
            if(raycast != nullptr)
            {
                double sqDist = (ray.origin - raycast->position).squareNorm();
                if(minDist == -1 || sqDist < minDist)
                {
                    delete result;
                    result = raycast;
                    minDist = sqDist;
                }
            }
        }

        return result;
    }


};