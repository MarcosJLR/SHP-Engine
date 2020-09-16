#pragma once

#include <vector>
#include "Collider.hpp"

namespace shp
{
    class CollisionHandler
    {
        public: 
            inline static CollisionHandler* GetInstance(){
                return s_Instance = (s_Instance == nullptr ? new CollisionHandler() : s_Instance);
            }

            bool Colliding(Collider collider);
            Collision* RayCast(Ray ray);
        
        private:
            CollisionHandler();
            static CollisionHandler* s_Instance;

            std::vector<Collider> m_MapObstacles;
    };
};