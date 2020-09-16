#include "Collider.hpp"

#include <cassert>

#define EPS 1e-6

namespace shp
{
    bool Collider::Intersects(Collider a, Collider b)
    {
        return ((a.x <= b.x && b.x <= a.x + a.width) || (b.x <= a.x && a.x <= b.x + b.width)) &&
               ((a.y <= b.y && b.y <= a.y + a.height) || (b.y <= a.y && a.y <= b.y + b.height)) &&
               ((a.z <= b.z && b.z <= a.z + a.depth) || (b.z <= a.z && a.z <= b.z + b.depth));
    }

    Collision* Collider::RayCast(Ray ray, Collider collider)
    {
        double t1 = (collider.x - ray.origin.x) / ray.direction.x;
        double t2 = (collider.x + collider.width - ray.origin.x) / ray.direction.x;
        double t3 = (collider.y - ray.origin.y) / ray.direction.y;
        double t4 = (collider.y + collider.height - ray.origin.y) / ray.direction.y;
        double t5 = (collider.z - ray.origin.z) / ray.direction.z;
        double t6 = (collider.z + collider.depth - ray.origin.z) / ray.direction.z;

        double tMin = std::max(std::max(std::min(t1, t2), 
                                        std::min(t3, t4)), 
                                        std::min(t5, t6));
        double tMax = std::min(std::min(std::max(t1, t2), 
                                        std::max(t3, t4)), 
                                        std::max(t5, t6));

        if(tMax < 0.0 || tMin > tMax || tMin > 1.0) { return nullptr; }

        Vector3 position = ray.origin + ray.direction * tMin;
        Vector3 normal;

        if(fabs(collider.x - position.x) < EPS) normal -= Vector3::X;
        if(fabs(collider.y - position.y) < EPS) normal -= Vector3::Y;
        if(fabs(collider.z - position.z) < EPS) normal -= Vector3::Z;
        if(fabs(collider.x + collider.width - position.x) < EPS) normal += Vector3::X;
        if(fabs(collider.y + collider.height - position.y) < EPS) normal += Vector3::Y;
        if(fabs(collider.z + collider.depth - position.z) < EPS) normal += Vector3::Z;

        return new Collision(position, normal);
    }

};