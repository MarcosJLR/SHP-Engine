#include "LookWhereYoureGoing.hpp"

namespace shp
{
    SteeringOutput LookWhereYoureGoing::GetSteering()
    {
        double currOrient = m_Character->GetOrientation();
        Vector3 direction = m_Character->GetVelocity();
        double orientation = direction.orientation(currOrient);
        m_Target = new Kinematic(Vector3::ZEROV, orientation, 0, 0);

        return Align::GetSteering();
    }
};