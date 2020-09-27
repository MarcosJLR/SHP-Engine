#include "Sight.hpp"

#include "CollisionHandler.hpp"

namespace shp
{
    namespace Sight
    {
        bool CanSee(Kinematic* character, 
                    Kinematic* target,
                    double maxDistance,
                    double openingAngle)
        {
            Vector3 separation = target->GetPosition() - character->GetPosition();
            double angleDifference = MinAngularDifference(character->GetOrientation(), separation.orientation());
            Ray ray(character->GetPosition(), separation);

            if(separation.norm() > maxDistance ||
               fabs(angleDifference) > openingAngle)
            {
                return false;
            }

            Collision* collision = CollisionHandler::GetInstance()->RayCast(ray);
            return collision == nullptr;
        }
    };
};