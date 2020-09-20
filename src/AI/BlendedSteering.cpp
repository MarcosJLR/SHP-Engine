#include "BlendedSteering.hpp"

namespace shp
{
    SteeringOutput BlendedSteering::GetSteering()
    {
        SteeringOutput result;

        for(auto& [behaviour, weight] : m_WeightedBehaviours)
        {
            result += behaviour->GetSteering() * weight;
        }

        if(result.linear.norm() > m_MaxAcceleration)
            result.linear.scale(m_MaxAcceleration);

        if(fabs(result.angular) > m_MaxAngular)
            result.angular = m_MaxAngular * sgn(result.angular);

        return result;
    }
};