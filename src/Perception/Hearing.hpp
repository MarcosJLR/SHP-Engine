#pragma once

#include "Kinematic.hpp"

namespace shp
{
    namespace Hearing
    {
        const double DEFAULT_HEARING_RADIUS = 64.0;

        bool CanHear(Kinematic* character, 
                     Kinematic* target,
                     double radius = DEFAULT_HEARING_RADIUS);
    };
};