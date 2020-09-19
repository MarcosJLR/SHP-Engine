#include "Face.hpp"

namespace shp
{
    SteeringOutput Face::GetSteering()
    {
        Vector3 direction = m_Target->GetPosition() - m_Character->GetPosition();
        double orientation = direction.orientation(m_Character->GetOrientation());
        Align::m_Target = new Kinematic(Vector3::ZEROV, orientation, 0, 0);

        return Align::GetSteering();
    }
};