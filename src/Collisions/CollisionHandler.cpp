#include "CollisionHandler.hpp"

#include "Engine.hpp"

#include <cassert>

namespace shp
{
    const int INF = 0x3f3f3f3f;

    CollisionHandler* CollisionHandler::s_Instance = nullptr;

    CollisionHandler::CollisionHandler()
    {
        m_MapObstacles.push_back(Collider(-10, -10, -10, SCREEN_WIDTH + 20, 10, SCREEN_HEIGHT + 20));   // Floor
        m_MapObstacles.push_back(Collider(-10, -10, -10, SCREEN_WIDTH + 20, INF, 10));                  // Upper wall
        m_MapObstacles.push_back(Collider(-10, -10, -10, 10, INF, SCREEN_HEIGHT + 20));                 // Left wall
        m_MapObstacles.push_back(Collider(SCREEN_WIDTH, -10, -10, 10, INF, SCREEN_HEIGHT + 20));        // Right wall
        m_MapObstacles.push_back(Collider(-10, -10, SCREEN_HEIGHT, 1300, INF, 10));                     // Lower wall
    }

    bool CollisionHandler::Colliding(Collider* collider)
    {
        assert(collider != nullptr);
        for(Collider& obstacle : m_MapObstacles)
        {
            if(Collider::Intersects(*collider, obstacle)) 
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