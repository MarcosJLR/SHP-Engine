#pragma once

#include "Kinematic.hpp"
#include "Behaviour.hpp"

namespace shp
{
    class Arrive : public Behaviour
    {
        public:
            Arrive(Kinematic* character, 
                   Kinematic* target,
                   double maxAcc = DEFAULT_MAXACCELERATION)
                : m_Character(character),
                  m_Target(target),
                  m_MaxAcceleration(maxAcc),
                  m_TargetRadius(TARGET_RADIUS),
                  m_SlowRadius(SLOW_RADIUS),
                  m_TimeToTarget(TIME_TO_TARGET)
            {}

            virtual SteeringOutput GetSteering() override;

            virtual Kinematic* GetCharacter() { return m_Character; }
            virtual Kinematic* GetTarget() { return m_Target; }
            virtual double GetMaxAcceleration() { return m_MaxAcceleration; }

            virtual void SetCharacter(Kinematic* character) { m_Character = character; }
            virtual void SetTarget(Kinematic* target) { m_Target = target; }
            virtual void SetTargetRadius(double radius) { m_TargetRadius = radius; }
            virtual void SetSlowRadius(double radius) { m_SlowRadius = radius; }
            virtual void SetTimeToTarget(double t) { m_TimeToTarget = t; }
        
        protected:
            Kinematic* m_Character;
            Kinematic* m_Target;

            double m_MaxAcceleration;

            double m_TargetRadius;
            double m_SlowRadius;
            double m_TimeToTarget;

            constexpr const static double TARGET_RADIUS = 32.0;
            constexpr const static double SLOW_RADIUS = 64.0;
            constexpr const static double TIME_TO_TARGET = 0.1;
    };
};