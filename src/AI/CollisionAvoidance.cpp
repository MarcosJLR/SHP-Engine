#include "CollisionAvoidance.hpp"

namespace shp
{
    SteeringOutput CollisionAvoidance::GetSteering()
    {
        SteeringOutput result;
        double shortestTime = INF;

        double firstMinSeparation;
        double firstDistance;
        Vector3 firstRelativePos;
        Vector3 firstRelativeVel;
        bool willCollide = false;

        for(Kinematic* target : m_Targets){
            Vector3 relativePos = m_Character->GetPosition() - target->GetPosition();
            Vector3 relativeVel = target->GetVelocity() - m_Character->GetVelocity();
            double relativeSpeed = relativeVel.norm();
            double timeToColission = (relativePos * relativeVel) / 
                                     (relativeSpeed * relativeSpeed);
            double distance = relativePos.norm();
            double minSeparation = distance - relativeSpeed * timeToColission;
            
            if(minSeparation > 2 * m_Radius)
                continue;

            if(timeToColission > 0 and timeToColission < shortestTime){
                shortestTime = timeToColission;
                firstMinSeparation = minSeparation;
                firstDistance = distance;
                firstRelativePos = relativePos;
                firstRelativeVel = relativeVel;
                willCollide = true;
            }
        }

        if(!willCollide)
            return result;

        Vector3 relativePos;
        if(firstMinSeparation <= 0 or firstDistance < 2 * m_Radius)
            relativePos = firstRelativePos;
        else
            relativePos = firstRelativePos + firstRelativeVel * shortestTime;

        result.linear.y = 0;
        result.angular = 0;
        result.linear.scale(m_MaxAcceleration);

        return result;
    }
};