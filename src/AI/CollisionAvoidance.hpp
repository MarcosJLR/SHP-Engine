#pragma once 

#include "Behaviour.hpp"
#include "Kinematic.hpp"

#include <vector>

namespace shp
{
    class CollisionAvoidance : public Behaviour
    {
        public: 
            CollisionAvoidance(Kinematic* character, 
                               double radius = DEFAULT_RADIUS,
                               double maxAcc = DEFAULT_MAXACCELERATION)
                : m_Character(character),
                  m_Targets(),
                  m_Radius(radius),
                  m_MaxAcceleration(maxAcc)
            {}

            virtual SteeringOutput GetSteering() override;

            virtual Kinematic* GetCharacter() { return m_Character; }
            virtual std::vector<Kinematic*> GetTargets() { return m_Targets; }
            virtual double GetMaxAcceleration() { return m_MaxAcceleration; }

            virtual void SetCharacter(Kinematic* character) { m_Character = character; }
            virtual void AddTarget(Kinematic* target) { m_Targets.push_back(target); }
            
        protected:
            Kinematic* m_Character;
            std::vector<Kinematic*> m_Targets;

            double m_Radius;
            double m_MaxAcceleration;

            constexpr const static double DEFAULT_RADIUS = 50.0;
    };
};