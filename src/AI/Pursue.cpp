#include "Pursue.hpp"

namespace shp
{
    SteeringOutput Pursue::GetSteering()
    {
        Vector3 direction = m_Target->GetPosition() - m_Character->GetPosition();
        double distance = direction.norm();

        double speed = m_Character->GetVelocity().norm();
        double prediction;

        if(speed < distance / m_MaxPrediction)
            prediction = m_MaxPrediction;
        else 
            prediction = distance / speed;

        Vector3 seekPosition = m_Target->GetPosition() + 
                               m_Target->GetVelocity() * prediction;

        Seek::m_Target = new Kinematic(seekPosition, 0, 0, 0);

        return Seek::GetSteering();
    }
};