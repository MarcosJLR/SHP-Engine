#include "PrioritySteering.hpp"

namespace shp
{
    SteeringOutput PrioritySteering::GetSteering()
    {
        SteeringOutput result;

        for(auto behaviour : m_Behaviours)
        {
            result = behaviour->GetSteering();

            if(result.linear.norm() > EPS || fabs(result.angular) > EPS)
                return result;            
        }

        return result;
    }
};