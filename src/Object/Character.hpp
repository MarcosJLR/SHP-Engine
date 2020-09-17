#pragma once

#include "GameObject.hpp"
#include "Kinematic.hpp"
#include "Collider.hpp"

namespace shp
{
    class Character : public GameObject
    {
        public: 
            Character(ObjectProperties* props, 
                      double orientation = 0.0,
                      double maxSpeed = DEFAULT_MAXSPEED, 
                      double maxRotation = DEFAULT_MAXROTATION)
                : GameObject(props), 
                  m_Kinematic(props->transform, orientation, maxSpeed, maxRotation),
                  m_Collider(props->transform, props->width, props->height, props->depth)
            {}

            virtual void Draw() override;
            virtual void Update(double dt) override;
            virtual void Clean() override;
            
        protected:
            Kinematic m_Kinematic;
            Collider m_Collider;
    };
};