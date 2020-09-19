#include "Arrive.hpp"

namespace shp
{
    SteeringOutput Arrive::GetSteering()
    {
        SteeringOutput result;

        double maxSpeed = m_Character->GetMaxSpeed();
        Vector3 direction = m_Target->GetPosition() - m_Character->GetPosition();
        direction.y = 0.0;
        double distance = direction.norm();

        Vector3 targetVelocity;
        double targetSpeed;

        if(distance < m_TargetRadius)
            return SteeringOutput();
        
        if(distance < m_SlowRadius)
            targetSpeed = maxSpeed * distance / m_SlowRadius;
        else 
            targetSpeed = maxSpeed;

        targetVelocity = direction;
        targetVelocity.scale(targetSpeed);

        result.linear = targetVelocity - m_Character->GetVelocity();
        result.linear /= m_TimeToTarget;

        if(result.linear.norm() > m_MaxAcceleration)
            result.linear.scale(m_MaxAcceleration);

        result.angular = 0;
        return result;
    };
};