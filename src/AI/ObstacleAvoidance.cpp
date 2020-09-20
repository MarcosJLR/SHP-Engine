#include "ObstacleAvoidance.hpp"

#include "CollisionHandler.hpp"

namespace shp
{
    SteeringOutput ObstacleAvoidance::GetSteering()
    {
        Vector3 position = m_Character->GetPosition();
        Vector3 longRay = m_Character->GetVelocity();
        longRay.scale(m_LongLookahead);

        double orientation = longRay.orientation(m_Character->GetOrientation());
        
        Vector3 whiskerL(orientation + m_WhiskerAngle);
        Vector3 whiskerR(orientation - m_WhiskerAngle);

        whiskerL.scale(m_ShortLookahead);
        whiskerR.scale(m_ShortLookahead);

        Collision* collision = CollisionHandler::GetInstance()->RayCast({position, longRay});
        
        if(collision == nullptr)
        {
            collision = CollisionHandler::GetInstance()->RayCast({position, whiskerL});

            if(collision == nullptr)
            {
                collision = CollisionHandler::GetInstance()->RayCast({position, whiskerR});
            }
        }

        if(collision == nullptr)
            return SteeringOutput();

        Vector3 targetPos = collision->position + collision->normal * m_AvoidDistance;
        m_Target = new Kinematic(targetPos, 0, 0, 0);
        return Seek::GetSteering();
    }
};