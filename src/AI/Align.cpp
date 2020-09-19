#include "Align.hpp"

namespace shp
{
    SteeringOutput Align::GetSteering()
    {
        SteeringOutput result;

        double rotation = MinAngularDifference(m_Target->GetOrientation(), 
                                               m_Character->GetOrientation());
        double rotationSize = fabs(rotation);
        double maxRotation = m_Character->GetMaxRotation();

        if(rotationSize < m_TargetRadius)
            return SteeringOutput();

        double targetRotation;
        if(rotationSize < m_SlowRadius)
            targetRotation = (maxRotation * rotationSize) / m_SlowRadius;
        else
            targetRotation = maxRotation;

        targetRotation *= sgn(rotation);

        result.angular = targetRotation - m_Character->GetRotation();
        result.angular /= m_TimeToTarget;

        if(fabs(result.angular) > m_MaxAngular)
            result.angular = m_MaxAngular * sgn(result.angular);

        result.linear = Vector3::ZEROV;
        return result;
    }
};