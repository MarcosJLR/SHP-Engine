#pragma once

#include "Kinematic.hpp"

namespace shp
{
    namespace Sight
    {
        const double DEFAULT_MAX_DISTANCE = 128;
        const double DEFAULT_OPENING_ANGLE = M_PI / 3.0;
        
        bool CanSee(Kinematic* character, 
                    Kinematic* target,
                    double maxDistance = DEFAULT_MAX_DISTANCE,
                    double openingAngle = DEFAULT_OPENING_ANGLE);
    };
};