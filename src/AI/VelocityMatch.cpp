#include "VelocityMatch.hpp"

namespace shp
{
    SteeringOutput VelocityMatch::GetSteering()
    {
        SteeringOutput result;

        result.linear = m_Target->GetVelocity() - m_Character->GetVelocity();
        result.linear /= m_TimeToTarget;

        if(result.linear.norm() > m_MaxAcceleration)
            result.linear.scale(m_MaxAcceleration);

        result.angular = 0.0;
        return result;
    }
};