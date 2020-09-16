#include "Kinematic.hpp"

#define M_PI           3.14159265358979323846  /* pi */

namespace shp
{
    void Kinematic::Update(SteeringOutput steering, double dt)
    {
        // Update velocity and rotation
        m_Velocity += steering.linear * dt;
        m_Rotation += steering.angular * dt;

        // Apply Drag
        m_Velocity *= m_Drag;
        m_Rotation *= m_Drag;

    	// Truncate velocity
        if(m_Velocity.norm() > m_MaxSpeed){
            m_Velocity.normalize();
            m_Velocity *= m_MaxSpeed;
        }

        // Truncate rotation
        if(fabs(m_Rotation) > m_MaxRotation){
            m_Rotation = sgn(m_Rotation) * m_MaxRotation;
        }

        // Update position and orientation
        m_Position += m_Velocity * dt;
        m_Orientation += m_Rotation * dt;

        // Wrap orientation around (-pi, pi)
        while(m_Orientation > M_PI) { m_Orientation -= 2*M_PI; }
        while(m_Orientation < -M_PI) { m_Orientation += 2*M_PI; }
    }
};