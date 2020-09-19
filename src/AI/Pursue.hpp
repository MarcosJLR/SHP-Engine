#pragma once

#include "Seek.hpp"
#include "Kinematic.hpp"

namespace shp
{
    class Pursue : public Seek
    {
        public:
            Pursue(Kinematic* character,
                   Kinematic* target,
                   bool flee = false,
                   double maxAcc = DEFAULT_MAXACCELERATION)
                : Seek(character, nullptr, flee, maxAcc),
                  m_Target(target),
                  m_MaxPrediction(MAX_PREDICTION)
            {}

            virtual SteeringOutput GetSteering() override;

            virtual Kinematic* GetTarget() override { return m_Target; }
            virtual void SetTarget(Kinematic* target) override { m_Target = target; }

            virtual void SetMaxPrediction(double pred) { m_MaxPrediction = pred; }

        protected: 
            Kinematic* m_Target;
            double m_MaxPrediction;

            constexpr const static double MAX_PREDICTION = 1.0;
    };
};