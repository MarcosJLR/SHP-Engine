#pragma once

#include "Kinematic.hpp"
#include "Behaviour.hpp"

namespace shp
{
    class Seek : public Behaviour
    {
        public:
            Seek(Kinematic* character, 
                 Kinematic* target,
                 bool flee = false,
                 double maxAcc = DEFAULT_MAXACCELERATION)
                : m_Character(character),
                  m_Target(target),
                  m_Flee(flee),
                  m_MaxAcceleration(maxAcc)
            {}

            virtual SteeringOutput GetSteering() override;

            virtual Kinematic* GetCharacter() { return m_Character; }
            virtual Kinematic* GetTarget() { return m_Target; }
            virtual bool GetFlee() { return m_Flee; }
            virtual double GetMaxAcceleration() { return m_MaxAcceleration; }

            virtual void SetCharacter(Kinematic* character) { m_Character = character; }
            virtual void SetTarget(Kinematic* target) { m_Target = target; }
            virtual void SwitchFlee() { m_Flee = !m_Flee; }
        
        protected:
            Kinematic* m_Character;
            Kinematic* m_Target;

            bool m_Flee;
            double m_MaxAcceleration;
    };
};