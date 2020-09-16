#pragma once

#include "vector3D.hpp"

namespace shp
{
    // Ray for ray casting
    struct Ray
    {
        public:
            Ray(Vector3 origin, Vector3 direction)
                : origin(origin), direction(direction)
            {}

            Vector3 origin;
            Vector3 direction;
    };

    // Collision structure
    struct Collision
    {
        public:
            Collision() : position(), normal() {}
            Collision(Vector3 position, Vector3 normal)
                : position(position), normal(normal)
            {}

            Vector3 position;
            Vector3 normal;
    };

    // Axis-Aligned Bounding Box Collider
    class Collider
    {
        public:
            Collider(int x, int y, int z, int width, int height, int depth)
                : x(x), y(y), z(z), width(width), height(height), depth(depth)
            {}
            Collider(Vector3 position, int width, int height, int depth)
                : width(width), height(height), depth(depth)
            {
                x = (int) position.x;
                y = (int) position.y;
                z = (int) position.z;
            }

            static bool Intersects(Collider a, Collider b);
            static Collision* RayCast(Ray ray, Collider collider); 

            inline void setPosition(Vector3 position)
            {
                x = (int) position.x;
                y = (int) position.y;
                z = (int) position.z;
            }

        private:
            int x, y, z;
            int width, height, depth;

    };
};