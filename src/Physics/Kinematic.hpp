#pragma once

#include "vector3D.hpp"

namespace shp
{
    const double DEFAULT_MAXSPEED = 500;
    const double DEFAULT_MAXROTATION = M_PI / 4.0;
    const double DEFAULT_MAXACCELERATION = 1;
    const double DEFAULT_MAXANGULAR = 0.0075;
    const double GRAVITY = 0.2;


    struct SteeringOutput
    {
        Vector3 linear; // Linear Acceleration
        double angular; // Angular Acceleration

        // Addition
        inline SteeringOutput& operator+=(const SteeringOutput& rhs)
        {
            linear += rhs.linear;
            angular += rhs.angular;
            return *this;
        }
        inline friend SteeringOutput operator+(SteeringOutput lhs, const SteeringOutput& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        // Substraction
        inline SteeringOutput& operator-=(const SteeringOutput& rhs)
        {
            linear -= rhs.linear;
            angular -= rhs.angular;
            return *this;
        }
        inline friend SteeringOutput operator-(SteeringOutput lhs, const SteeringOutput& rhs)
        {
            lhs -= rhs;
            return lhs;
        }

        // Multiplication by a scalar
        inline SteeringOutput& operator*=(const double rhs)
        {
            linear *= rhs;
            angular *= rhs;
            return *this;
        }
        inline friend SteeringOutput operator*(SteeringOutput lhs, const double rhs)
        {
            lhs *= rhs;
            return lhs;
        }
        inline friend SteeringOutput operator*(const double lhs, SteeringOutput rhs)
        {
            rhs *= lhs;
            return rhs;
        }

        // Division by a scalar
        inline SteeringOutput& operator/=(const double rhs)
        {
            linear /= rhs;
            angular /= rhs;
            return *this;
        }
        inline friend SteeringOutput operator/(SteeringOutput lhs, const double rhs)
        {
            lhs /= rhs;
            return lhs;
        }
    };

    class Kinematic
    {
        public:
            Kinematic(Vector3 position,
                      double orientation,
                      double maxSpeed,
                      double maxRotation)
                : m_Position(position),
                  m_Orientation(orientation),
                  m_Velocity(),
                  m_Rotation(0),
                  m_MaxSpeed(maxSpeed),
                  m_MaxRotation(maxRotation)
            {}

            // Getters
            inline Vector3 GetPosition() { return m_Position; }
            inline double GetOrientation() { return m_Orientation; }
            inline Vector3 GetVelocity() { return m_Velocity; }
            inline double GetRotation() { return m_Rotation; }
            inline double GetMaxSpeed() { return m_MaxSpeed; }
            inline double GetMaxRotation() { return m_MaxRotation; }

            inline void SetPosition(Vector3& position) { m_Position = position; }
            inline void SetPositionX(double x) { m_Position.x = x; }
            inline void SetPositionY(double y) { m_Position.y = y; }
            inline void SetPositionZ(double z) { m_Position.z = z; }

            inline void SetVelocity(Vector3& velocity) { m_Velocity = velocity; }
            inline void SetVelocityX(double x) { m_Velocity.x = x; }
            inline void SetVelocityY(double y) { m_Velocity.y = y; }
            inline void SetVelocityZ(double z) { m_Velocity.z = z; }

            // Update given Accelerations and delta time
            void Update(SteeringOutput steering, double dt);

        private:
            // Static info
            Vector3 m_Position;
            double m_Orientation;

            // Kinematic info
            Vector3 m_Velocity;
            double m_Rotation;

            double m_MaxSpeed;
            double m_MaxRotation;
            double m_Drag{0.95};
    };

    inline double sgn(double x)
    {
        return x < 0.0 ? -1.0 : 1.0;
    }

    inline double MinAngularDifference(double alfa, double beta)
    {
        double result = alfa - beta;

        while(result > M_PI) { result -= 2*M_PI; }
        while(result < -M_PI) { result += 2*M_PI; }
        
        return result;
    }
};