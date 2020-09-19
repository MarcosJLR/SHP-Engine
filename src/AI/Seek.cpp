#include "Seek.hpp"

namespace shp
{
    SteeringOutput Seek::GetSteering()
    {
        SteeringOutput result;

        result.linear = m_Target->GetPosition() - m_Character->GetPosition();

        result.linear.y = 0.0;
        result.linear.normalize();
        result.linear *= m_MaxAcceleration;
        if(m_Flee) { result.linear *= -1; }

        result.angular = 0;
        return result;
    };
};