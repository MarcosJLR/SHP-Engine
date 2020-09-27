#include "Motion.hpp"

namespace shp
{
    namespace Motion
    {
        bool CanFeel(Kinematic* character, 
                     Kinematic* target, 
                     double decayFactor)
        {
            double distance = character->GetPosition().distance(target->GetPosition());
            double speed = target->GetVelocity().norm();

            return speed > decayFactor * log(distance);
        }
    };
};