#include "Hearing.hpp"

namespace shp
{
    namespace Hearing
    {
        bool CanHear(Kinematic* character,
                     Kinematic* target,
                     double radius)
        {
            double distance = character->GetPosition().distance(target->GetPosition());
            return distance < radius;
        }
    };
};