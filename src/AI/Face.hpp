#pragma once

#include "Kinematic.hpp"
#include "Align.hpp"

namespace shp
{
    class Face : public Align
    {
        public:
            Face(Kinematic* character, 
                 Kinematic* target, 
                 double maxAngular = DEFAULT_MAXANGULAR)
                : Align(character, nullptr, maxAngular),
                  m_Target(target)
            {}

            virtual SteeringOutput GetSteering() override;

            virtual Kinematic* GetTarget() override { return m_Target; }
            virtual void SetTarget(Kinematic* target) override { m_Target = target; }

        protected:
            Kinematic* m_Target;
    };
};