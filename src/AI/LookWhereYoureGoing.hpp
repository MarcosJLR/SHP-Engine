#pragma once

#include "Kinematic.hpp"
#include "Align.hpp"

namespace shp
{
    class LookWhereYoureGoing : public Align 
    {
        public: 
            LookWhereYoureGoing(Kinematic* character,
                                double maxAngular = DEFAULT_MAXANGULAR)
                : Align(character, nullptr, maxAngular)
            {}

            virtual SteeringOutput GetSteering() override;
    };
};