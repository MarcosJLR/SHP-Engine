#pragma once

#include "Kinematic.hpp"

namespace shp
{
    namespace Motion
    {
        const double DEFAULT_DECAY_FACTOR = 1.0;

        bool CanFeel(Kinematic* character, 
                     Kinematic* target,
                     double decayFactor = DEFAULT_DECAY_FACTOR);
    };
};