#pragma once

#include "Kinematic.hpp"

namespace shp
{
    // Class that all AI behaviours will inherit from
    class Behaviour
    {
        public:
            virtual SteeringOutput GetSteering() = 0;
    };
};