#include "CollisionHandler.hpp"

#include "Engine.hpp"

#include <cassert>

namespace shp
{
    const int INFINT = 0x3f3f3f3f;

    CollisionHandler* CollisionHandler::s_Instance = nullptr;

    CollisionHandler::CollisionHandler()
    {
        m_MapObstacles.push_back(Collider(-10, -10, -10, SCREEN_WIDTH + 20, 10, SCREEN_HEIGHT + 20));   // Floor
        m_MapObstacles.push_back(Collider(-10, -10, -10, SCREEN_WIDTH + 20, INFINT, 42));                  // Upper wall
        m_MapObstacles.push_back(Collider(-10, -10, -10, 42, INF, SCREEN_HEIGHT + 20));                 // Left wall
        m_MapObstacles.push_back(Collider(SCREEN_WIDTH - 32, -10, -10, 42, INFINT, SCREEN_HEIGHT + 20));   // Right wall
        m_MapObstacles.push_back(Collider(-10, -10, SCREEN_HEIGHT - 32, 1300, INFINT, 42));                // Lower wall

        m_MapObstacles.push_back(Collider(128, -10, 416, 128, 74, 128));
        m_MapObstacles.push_back(Collider(256, -10, 256, 96, 74, 448));
        m_MapObstacles.push_back(Collider(256, -10, 256, 480, 74, 96));
        m_MapObstacles.push_back(Collider(416, -10, 128, 128, 74, 128));
        m_MapObstacles.push_back(Collider(352, -10, 608, 192, 74, 96));
        m_MapObstacles.push_back(Collider(640, -10, 352, 96, 74, 352));
        m_MapObstacles.push_back(Collider(736, -10, 608, 416, 74, 96));
        m_MapObstacles.push_back(Collider(832, -10, 704, 128, 74, 128));
        m_MapObstacles.push_back(Collider(1056, -10, 244, 96, 74, 384));
        m_MapObstacles.push_back(Collider(832, -10, 128, 320, 74, 96));
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